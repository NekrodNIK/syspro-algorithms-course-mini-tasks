#include <vector>

class Solution {
public:
  bool isBipartite(std::vector<std::vector<int>>& graph) {
    std::vector<int> visited(graph.size(), -1);

    auto dfs = [&graph, &visited](this auto self, int ind, bool color) {
      if (visited[ind] != -1) {
        return true;
      }

      visited[ind] = color;
      for (auto i : graph[ind]) {
        if (visited[i] == color || !self(i, !color)) {
          return false;
        }
      }

      return true;
    };

    for (int i = 0; i < graph.size(); i++) {
      if (!dfs(i, 0)) {
        return false;
      };
    }

    return true;
  }
};
