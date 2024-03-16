#include <cstddef>
#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x = 0) : val(x) {}
};

ListNode* reverse(ListNode* head) {
  ListNode* pre = nullptr;
  ListNode* cur = head;
  while (cur) {
    ListNode* tmp = cur->next;
    cur->next = pre;
    pre = cur;
    cur = tmp;
  }

  // 最后cur == nullptr , pre指向了反转后的头结点，而head指向末尾
  return pre;
}

// ListNode* reverseKGroup(ListNode* head, int k) {
//   ListNode* pre = new ListNode(-1);
//   pre->next = head;
//   ListNode* dummy = pre;

//   ListNode* fast = head;
//   ListNode* slow = head;

//   while (fast) {
//     // k 次 道 k组的最后一个
//     for (int i = 1; i < k; i++) {
//       if (fast) {
//         fast = fast->next;
//       } else {
//         break;
//       }
//     }
//     if (fast == nullptr) {
//       break;
//     }
//     // 防止断链
//     ListNode* temp = fast->next;

//     // 限制翻转的
//     fast->next = NULL;
//     pre->next = reverse(slow);

//     // 尾节点，和temp链接，防止断链
//     slow->next = temp;
//     // 新一轮的头节点前面的节点
//     pre = slow;
//     slow = temp;

//     fast = temp;
//   }
//   return dummy->next;
// }

ListNode* reverseKGroup(ListNode* head, int k) {
  // 统计节点个数
  int count = 0;
  ListNode* count_node = head;
  while (count_node) {
    count_node = count_node->next;
    count++;
  }

  ListNode* pre = new ListNode(-1);
  pre->next = nullptr;
  ListNode* dummy = pre;
  ListNode* next_k_start = head;
  ListNode* cur = head;
  for (; count >= k; count -= k) {
    for (int j = 0; j < k; j++) {
      ListNode* temp = cur->next;
      cur->next = pre->next;
      pre->next = cur;
      cur = temp;
    }
    // 防止断链
    next_k_start->next = cur;
    // 下一次k次反转，pre所在的位置
    pre = next_k_start;
    std::cout << pre->next->val << '\n';
    // 记录k次反转前，第一个节点
    next_k_start = cur;
  }
  return dummy->next;
}

int main() {
  int n, x;
  // std::cin >> n;
  // std::cin >> k;
  ListNode* dummy = new ListNode(0);
  ListNode* pre = dummy;
  // while (n--) {
  //   std::cin >> x;
  //   pre->next = new ListNode(x);
  //   pre = pre->next;
  // }
  int k = 2;
  for (int i = 1; i < 6; i++) {
    // std::cin >> x;
    pre->next = new ListNode(i);
    pre = pre->next;
  }

  ListNode* newHead = reverseKGroup(dummy->next, k);
  while (newHead) {
    std::cout << newHead->val << " ";
    newHead = newHead->next;
  }

  return 0;
}