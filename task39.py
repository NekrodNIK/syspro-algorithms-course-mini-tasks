from random import randint
from dataclasses import dataclass, field
from typing import Iterable
import sys

class PriorityGenerator:    
    def __init__(self):
        self._priority_set = set()
        
    def __call__(self) -> int:
        new_pr = randint(0, sys.maxsize)
        while new_pr in self._priority_set:
            new_pr = randint(0, sys.maxsize)

        self._priority_set.add(new_pr)
        return new_pr

_generator = PriorityGenerator()

@dataclass
class Node:
    value: int
    priority: float = field(default_factory=_generator)
    size: int = 1
    left: "Node | None" = None
    right: "Node | None" = None

    sum: int = 0

    def __post_init__(self):
        self.sum = self.value

    @staticmethod
    def merge(x: "Node | None", y: "Node | None") -> "Node | None":
        if x is None:
            return y
        if y is None:
            return x

        if x.priority > y.priority:
            x.right = Node.merge(x.right, y)
            Node.update(x)
            return x
        else:
            y.left = Node.merge(x, y.left)
            Node.update(y)
            return y

    @staticmethod
    def update(node: "Node | None"):
        if node is None:
            return

        node.size = (
            (node.left.size if node.left else 0)
            + (node.right.size if node.right else 0)
            + 1
        )
        node.sum = (
            (node.left.sum if node.left else 0)
            + (node.right.sum if node.right else 0)
            + node.value
        )

    @staticmethod
    def splitBySize(
        node: "Node | None", count: int
    ) -> tuple["Node | None", "Node | None"]:
        if not node:
            return None, None

        left_size = node.left.size if node.left else 0
        if count <= left_size:
            LL, LR = Node.splitBySize(node.left, count)
            node.left = LR
            Node.update(node)
            return LL, node
        else:
            RL, RR = Node.splitBySize(node.right, count - left_size - 1)
            node.right = RL
            Node.update(node)
            return node, RR


class Treap:
    root: Node | None

    def __init__(self, initial: Iterable[int] | None = None, root: Node | None = None):
        self.root = root
        if not initial:
            return

        for item in initial:
            self.root = Node.merge(self.root, Node(item))

    def merge(self, other: "Treap"):
        self.root = Node.merge(self.root, other.root)

    def splitBySize(self, count) -> tuple["Treap", "Treap"]:
        x, y = Node.splitBySize(self.root, count)
        return Treap(root=x), Treap(root=y)

    def sum(self, from_: int, to: int) -> int:
        L, R = Node.splitBySize(self.root, from_)
        RL, RR = Node.splitBySize(R, to - from_ + 1)
        res = RL.sum if RL else 0
        self.root = Node.merge(L, Node.merge(RL, RR))
        return res


def test1():
    treap = Treap([1, 2, 3, 4, 5])
    assert treap.sum(0, 4) == 15
    assert treap.sum(1, 3) == 9

    treap = Treap([10])
    assert treap.sum(0, 0) == 10

    treap = Treap()
    assert treap.sum(0, 0) == 0

    treap = Treap([1, 2, 3, 4])
    left, right = treap.splitBySize(2)
    assert left.sum(0, 1) == 3
    assert right.sum(0, 1) == 7

    left.merge(right)
    assert left.sum(0, 3) == 10

    treap = Treap([-1, 5, -3])
    assert treap.sum(0, 2) == 1


def test2():
    treap = Treap(list(range(1, 11)))

    left, right = treap.splitBySize(5)
    assert left.sum(0, 4) == 15
    assert right.sum(0, 4) == 40

    left1, left2 = left.splitBySize(2)
    assert left1.sum(0, 1) == 3
    assert left2.sum(0, 2) == 12

    result = left2
    result.merge(left1)
    result.merge(right)
    assert result.sum(0, 9) == 55


def test3():
    treap = Treap(list(range(1, 101)))

    assert treap.sum(0, 99) == sum(range(1, 101))
    assert treap.sum(0, 0) == 1
    assert treap.sum(99, 99) == 100
    assert treap.sum(24, 25) == 25 + 26


if __name__ == "__main__":
    test1()
    test2()
    test3()
    print("All tests passed")
