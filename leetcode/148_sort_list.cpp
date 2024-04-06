

#include <chrono>
#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int value = 0) : val(value), next(nullptr) {}
};

ListNode *sortList(ListNode *head) {
  std::priority_queue<int, std::vector<int>, std::greater_equal<int>> que;

  for (ListNode *cur = head; cur != NULL; cur = cur->next) {
    que.push(cur->val);
  }
  ListNode *cur = head;
  while (!que.empty()) {
    cur->val = que.top();
    que.pop();
    cur = cur->next;
  }
  return head;
}

ListNode *findMid(ListNode *head) {
  ListNode *fast = head->next;
  ListNode *slow = head;
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  return slow;
}

ListNode *mergeTwoList(ListNode *l1, ListNode *l2) {
  ListNode *pre = new ListNode();
  ListNode *dummy = pre;
  while (l1 && l2) {
    if (l1->val <= l2->val) {
      pre->next = l1;
      l1 = l1->next;
    } else {
      pre->next = l2;
      l2 = l2->next;
    }
    pre = pre->next;
  }

  pre->next = l1 == nullptr ? l2 : l1;
  return dummy->next;
}

ListNode *sort_list(ListNode *head) {
  if (head == NULL || head->next == NULL) {
    return head;
  }
  ListNode *mid = findMid(head);
  ListNode *rightList = sort_list(mid->next);
  mid->next = nullptr;
  ListNode *leftList = sort_list(head);
  ListNode *new_head = mergeTwoList(leftList, rightList);
  return new_head;
}

ListNode *createList(std::vector<int> nums) {
  if (nums.size() == 0) {
    return NULL;
  }
  ListNode *head = new ListNode(nums[0]);
  ListNode *cur = head;
  for (int i = 1; i < nums.size(); i++) {
    cur->next = new ListNode(nums[i]);
    cur = cur->next;
  }
  return head;
}

int main() {
  std::vector<int> vec{4, 3, 2, 1};
  ListNode *head = createList(vec);
  // ListNode *new_head = sortList(head);
  ListNode *new_head = sort_list(head);
  while (new_head) {
    std::cout << new_head->val << ' ';
    new_head = new_head->next;
  }
  return 0;
}