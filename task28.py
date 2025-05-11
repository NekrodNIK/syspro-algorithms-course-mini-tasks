"""
foo: bar, baz, qux
bar: baz, foo, bar
qux: qux
"""

import sys
import io
from collections import defaultdict

type adj_dict = dict[str, list[str]]
type scc_list = list[list[int]]


def reverse_adj(adj: adj_dict) -> adj_dict:
    result = defaultdict(lambda: [])
    for i in adj:
        for j in adj[i]:
            if not result.get(j, None):
                result[j] = []
            result[j].append(i)

    return result


def dfs(v: str, adj: adj_dict, visited: dict[str, bool], path: list[str]):
    visited[v] = True
    for i in adj[v]:
        if not visited[i]:
            dfs(i, adj, visited, path)
    path.append(v)


def kosaraju(adj: adj_dict) -> scc_list:
    rev = reverse_adj(adj)
    visited = defaultdict(lambda: False)

    path = []
    for v in list(rev.keys()):
        if not visited[v]:
            dfs(v, rev, visited, path)

    visited = defaultdict(lambda: False)

    result = []
    while path:
        v = path.pop()
        if not visited[v]:
            scc = []
            dfs(v, adj, visited, scc)
            result.append(scc)

    return result


def main(in_s, out_s):
    adj = defaultdict(lambda: [])

    for line in in_s:
        line = line.strip()
        if not line:
            break

        name, args = line.split(":")
        adj[name] = [i.strip() for i in args.split(",")]
    else:
        print(file=out_s)

    result = kosaraju(adj)
    max_scc: list = max(result, key=lambda x: len(x))

    print(f"RESULT", file=out_s)
    print(f"max scc:", ", ".join(max_scc), file=out_s)
    for scc in result:
        if len(scc) == 1:
            if adj[scc[0]] == scc:
                print(f"{scc[0]}: recursive", file=out_s)
            else:
                print(f"{scc[0]}: non-recursive", file=out_s)
            continue

        for v in scc:
            print(f"{v}: recursive", file=out_s)


if __name__ == "__main__":
    in_s = io.StringIO(
        """foo: bar, baz, qux
    bar: baz, foo, bar
    qux: qux
    """
    )
    out_s = io.StringIO()
    expected = """RESULT
max scc: foo, bar
qux: recursive
baz: non-recursive
foo: recursive
bar: recursive
"""

    main(in_s, out_s)
    out_s.seek(0)
    assert out_s.read() == expected

    main(sys.stdin, sys.stdout)
