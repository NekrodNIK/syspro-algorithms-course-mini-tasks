from math import comb
from itertools import permutations


# polynomial solution using combinatorics
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


def naive_count_topological_sorts(tree) -> int:
    count = 0
    edges = []

    for i in range(len(tree)):
        for j in tree[i]:
            edges.append((i, j))

    for p in permutations(range(len(tree))):
        if all(p[u] < p[v] for u, v in edges):
            count += 1

    return count


def test_tree(tree):
    return count_topological_sorts(tree, 0) == naive_count_topological_sorts(tree)


if __name__ == "__main__":
    assert test_tree([[]])
    assert test_tree([[1, 2], [], []])
    assert test_tree([[1], [2], []])
    assert test_tree([[1, 3], [2], [], []])
    assert test_tree([[1, 2], [3], [4, 5], [], [], []])
    assert test_tree([[1, 2], [], [3, 4], [], []])
    assert test_tree([[1, 2], [3, 4], [5], [], [6], [], []])
    assert test_tree([[1, 2], [3, 4], [5], [], [6], [8, 7], [9], [], [], []])
    print("Tests passed")
