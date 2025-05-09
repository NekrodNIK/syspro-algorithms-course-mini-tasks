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
  struct Compare {
    bool operator()(ListNode* a, ListNode* b) { return a->val > b->val; };
  };

  ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    std::priority_queue<ListNode*, std::vector<ListNode*>, Compare> queue;

    for (auto head : lists) {
      if (head)
        queue.push(head);
    }

    ListNode head;
    ListNode* cur = &head;
    while (!queue.empty()) {
      ListNode* min = queue.top();
      queue.pop();

      cur->next = min;
      cur = min;

      if (min->next)
        queue.push(min->next);
    }

    return head.next;
  }
};
