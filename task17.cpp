#include <queue>

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    std::priority_queue<int> queue;

    for (auto ptr : lists) {
      while (ptr != nullptr) {
        queue.push(ptr->val);
        ptr = ptr->next;
      }
    }

    if (queue.size() == 0) {
      return nullptr;
    }

    ListNode* cur = nullptr;
    while (queue.size() > 0) {
      cur = new ListNode(queue.top(), cur);
      queue.pop();
    }

    return cur;
  }
};
