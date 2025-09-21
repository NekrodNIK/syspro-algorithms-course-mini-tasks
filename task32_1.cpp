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
  findRedundantConnection(std::vector<std::vector<int>>& edges) {
    UnionFind uf;
    for (const auto& edge : edges)
      if (!uf.unite(edge[0], edge[1]))
        return edge;
    return {};
  }
};
