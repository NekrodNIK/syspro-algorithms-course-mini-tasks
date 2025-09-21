#include <utility>
#include <vector>

class UnionFind {
private:
  struct Unit {
    int parent;
    int rank;
  };
  std::vector<Unit> vec;

public:
  int makeOrfind(int x) {
    if (vec.size() < x + 1)
      vec.resize(x + 1);

    if (!vec[x].parent) {
      vec[x] = {x, 0};
      return x;
    }

    int root = vec[x].parent;
    while (vec[root].parent != root) {
      root = vec[root].parent;
    }

    while (vec[x].parent != root) {
      int p = vec[x].parent;
      vec[x].parent = root;
      x = p;
    }

    return root;
  }

  bool unite(int x, int y) {
    x = makeOrfind(x);
    y = makeOrfind(y);

    if (x == y)
      return false;

    if (vec[x].rank < vec[y].rank)
      std::swap(x, y);

    if (vec[x].rank == vec[y].rank)
      vec[x].rank++;

    vec[y].parent = x;
    return true;
  }
};

class Solution {
public:
  std::vector<int>
  findRedundantDirectedConnection(std::vector<std::vector<int>>& edges) {
    std::vector<int> parent(edges.size() + 1, 0);
    std::vector<int> c1, c2;

    for (const auto& edge : edges) {
      int from = edge[0];
      int to = edge[1];

      if (parent[to]) {
        c1 = {parent[to], to};
        c2 = edge;
        break;
      }

      parent[to] = from;
    }

    UnionFind uf;
    std::vector<int> cyclic;

    for (const auto& edge : edges) {
      if (edge == c2)
        continue;

      if (!uf.unite(edge[0], edge[1])) {
        cyclic = edge;
        break;
      }
    }

    if (c2.empty())
      return cyclic;

    if (!cyclic.empty())
      return c1;

    return c2;
  }
};
