# polynomial solution using combinatorics

from math import comb
from itertools import permutations


def count_topological_sorts(tree, root) -> int:
    count = [int(not tree[i]) for i in range(len(tree))]
    size = [int(not tree[i]) for i in range(len(tree))]
    visited = [False] * len(tree)

    stack = [root]
    while stack:
        u = stack[-1]

        if not visited[u]:
            visited[u] = True
            for v in tree[u]:
                stack.append(v)
            continue

        stack.pop()

        if count[u] > 0:
            continue

        count[u] = 1
        size[u] = 1
        for v in tree[u]:
            count[u] = comb((size[u] - 1) + size[v], size[v]) * count[u] * count[v]
            size[u] += size[v]

    return count[root]


if __name__ == "__main__":
    tree = [[]]
    assert count_topological_sorts(tree, 0) == 1

    tree = [[1, 2], [], [], []]
    assert count_topological_sorts(tree, 0) == 2

    tree = [[1], [2], [], []]
    assert count_topological_sorts(tree, 0) == 1

    tree = [[1, 3], [2], [], []]
    assert count_topological_sorts(tree, 0) == 3

    tree = [[1, 2], [3], [4, 5], [], [], []]
    assert count_topological_sorts(tree, 0) == 20

    tree = [[1, 2], [], [3, 4], [], []]
    assert count_topological_sorts(tree, 0) == 8

    print("Tests passed")
