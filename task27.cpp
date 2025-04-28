#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
  bool topSort(vector<vector<int>>& adj, vector<int>& deg, vector<int>& res) {
    queue<int> q;
    for (int i = 0; i < deg.size(); i++) {
      if (!deg[i]) {
        q.push(i);
      }
    }

    int count = 0;
    while (!q.empty()) {
      int n = q.front();
      q.pop();

      for (int v : adj[n]) {
        --deg[v];
        if (!deg[v]) {
          q.push(v);
        }
      }

      res.push_back(n);
      count++;
    }

    return count == adj.size();
  }

  vector<int> sortItems(int n, int m, vector<int>& group,
                        vector<vector<int>>& beforeItem) {
    for (int i = 0; i < n; i++)
      if (group[i] == -1)
        group[i] = m++;

    vector<vector<int>> itemAdj(n), groupAdj(m);
    vector<int> itemDeg(n, 0), groupDeg(m, 0);

    for (int i = 0; i < n; i++) {
      for (int k : beforeItem[i]) {
        itemAdj[k].push_back(i);
        itemDeg[i]++;

        if (group[k] != group[i]) {
          groupAdj[group[k]].push_back(group[i]);
          groupDeg[group[i]]++;
        }
      }
    }

    vector<int> sortedItems, sortedGroups;
    bool s1 = topSort(itemAdj, itemDeg, sortedItems);
    bool s2 = topSort(groupAdj, groupDeg, sortedGroups);

    if (!s1 || !s2) {
      return {};
    }

    vector<vector<int>> groupToItem(m);
    for (int i : sortedItems) {
      groupToItem[group[i]].push_back(i);
    }

    vector<int> res;
    for (int g : sortedGroups) {
      for (int i : groupToItem[g]) {
        res.push_back(i);
      }
    }

    return res;
  }
};
