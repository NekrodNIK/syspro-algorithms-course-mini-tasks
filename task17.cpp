#include <functional>
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
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;

    for (auto ptr : lists) {
      while (ptr != nullptr) {
        q.push(ptr->val);
        ptr = ptr->next;
      }
    }

    if (q.size() == 0) {
      return nullptr;
    }

    ListNode* head = new ListNode();
    head->val = q.top();

    ListNode* cur = head;
    q.pop();

    while (q.size() > 0) {
      cur->next = new ListNode();
      cur->next->val = q.top();
      cur = cur->next;
      q.pop();
    }
    cur->next = nullptr;

    return head;
  }
};
