
#include <iostream>
#include <vector>
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int value = 0) : val(value), next(nullptr) {}
};

ListNode *createList(std::vector<int> nums) {
  ListNode *head = new ListNode(nums[0]);
  ListNode *cur = head;
  for (int i = 1; i < nums.size(); i++) {
    cur->next = new ListNode(nums[i]);
    cur = cur->next;
  }
  return head;
}

ListNode *addTwoList(ListNode *l1, ListNode *l2) {
  ListNode *pre = new ListNode(-1);
  ListNode *dummy = pre;
  int carry = 0;
  while (l1 || l2 || carry) {
    int x = l1 == nullptr ? 0 : l1->val;
    int y = l2 == nullptr ? 0 : l2->val;
    int sum = x + y + carry;
    carry = sum / 10;
    pre->next = new ListNode(sum % 10);
    pre = pre->next;
    if (l1) {
      l1 = l1->next;
    }
    if (l2) {
      l2 = l2->next;
    }
  }
  return dummy->next;
}

int main() {
  std::vector<int> nums1{2, 4, 3};
  std::vector<int> nums2{5, 6, 4};

  ListNode *l1 = createList(nums1);
  ListNode *l2 = createList(nums2);
  ListNode *res = addTwoList(l1, l2);
  while (res) {
    std::cout << res->val << ' ';
    res = res->next;
  }
  return 0;
}