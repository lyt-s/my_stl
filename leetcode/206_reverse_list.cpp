#include <iostream>
#include <sstream>
#include <string>
#include <vector>
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int value = 0) : val(value), next(nullptr) {}
};

ListNode* createList(std::vector<int>& nums) {
  if (nums.size() == 0) {
    return nullptr;
  }

  ListNode* head = new ListNode(nums[0]);
  ListNode* curNode = head;
  for (int i = 1; i < nums.size(); i++) {
    curNode->next = new ListNode(nums[i]);
    curNode = curNode->next;
  }
  return head;
}

ListNode* reverseList(ListNode* head) {
  ListNode* pre = new ListNode(-1);
  pre->next = nullptr;
  ListNode* cur = head;
  while (cur) {
    ListNode* tmp = cur->next;
    cur->next = pre->next;
    pre->next = cur;
    cur = tmp;
  }
  return pre->next;
}

int main() {
  std::string line;
  std::getline(std::cin, line);

  std::stringstream ss(line);

  int num;
  std::vector<int> nums;
  char ch;
  while (ss >> ch) {
    if (ch == '[' || ch == ']' || ch == ',') {
      continue;
    } else {
      ss.unget();
      ss >> num;
      nums.push_back(num);
    }
  }

  ListNode* head = createList(nums);
  ListNode* new_head = reverseList(head);
  while (new_head) {
    std::cout << new_head->val << " ";
    new_head = new_head->next;
  }
  std::cout << '\n';
  return 0;
}