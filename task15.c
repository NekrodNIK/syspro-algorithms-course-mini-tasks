#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode* next;
};
typedef struct ListNode ListNode;

void* nc(void* ptr) {
  if (ptr == NULL)
    exit(1);
  return ptr;
}

ListNode* reverseBetween(ListNode* head, int left, int right) {
  ListNode *tmp_head = (ListNode*) nc(malloc(sizeof(ListNode)));
  tmp_head->next = head;

  ListNode* prev = tmp_head;
  for (int i = 0; i < left - 1; i++) {
    prev = prev->next;
  }
  
  ListNode* cur = prev->next;
  for (int i = 0; i < right-left; i++) {
    ListNode* tmp = prev->next;
    prev->next = cur->next;
    cur->next = cur->next->next;
    prev->next->next = tmp;
  }
  
  ListNode* result = tmp_head->next;
  free(tmp_head);
  return result;
}
