#include <iostream>

struct ListNode {
  int val;
  ListNode *next;

  ListNode(int x = 0) : val(x) {}
};

ListNode *swapPairs(ListNode *head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }

  ListNode *dummy = new ListNode(-1);
  ListNode *pre = dummy;
  ListNode *cur = head;

  while (cur && cur->next) {
    ListNode *next = cur->next;
    ListNode *temp = next->next;

    cur->next = temp;
    next->next = cur;
    pre->next = next;
    pre = cur;
    cur = temp;
  }
  return dummy->next;
}

int main() {
  int n, x;
  ListNode *prev = new ListNode(0);
  ListNode *dummy = prev;
  std::cin >> n;
  while (n--) {
    std::cin >> x;
    prev->next = new ListNode(x);
    prev = prev->next;
  }

  ListNode *new_head = swapPairs(dummy->next);

  while (new_head) {
    std::cout << new_head->val << " ";
    new_head = new_head->next;
  }
  return 0;
}