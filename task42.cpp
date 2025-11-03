// https://leetcode.com/problems/create-sorted-array-through-instructions/
#include <algorithm>
#include <vector>

class Solution {
private:
  const int mod = 1e9 + 7;
  std::vector<int> s;

  void inc(int pos) {
    int i = pos;
    while (i < s.size()) {
      s[i]++;
      i |= i + 1;
    }
  }

  int sum(int pos) {
    int ans = 0;
    int cur = pos;
    while (cur >= 0) {
      ans += s[cur];
      cur = (cur & (cur + 1)) - 1;
    }
    return ans;
  }

  int sum(int left, int right) {
    return sum(right) - sum(left - 1);
  }

public:
  int createSortedArray(std::vector<int>& instrs) {
    int max = *std::max_element(instrs.begin(), instrs.end());
    s.resize(max + 1, 0);

    int ans = 0;
    for (int i : instrs) {
      ans += std::min(sum(0, i-1), sum(i+1, max));
      ans %= mod;
      inc(i);
    }

    return ans;
  }
};
