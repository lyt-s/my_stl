#include <iostream>
#include <map>

using namespace std;

class LRUCache {
 public:
  LRUCache(int capacity) {
    size = capacity;
    cnt = 0;
    head = new Node(-1, -1);
    tail = new Node(-1, -1);
    head->next = head->pre = tail;
    tail->next = tail->pre = head;
  }

  // ~LRUCache() {
  //     for (auto item : q) {
  //         delete item.second;
  //     }
  // }

  int get(int key) {
    if (q.count(key)) {
      Node *cur = q[key];
      // cout << cur->key << ' ' << cur->val << endl;
      if (head->next != cur) {
        // 从原来位置移除
        cur->pre->next = cur->next;
        cur->next->pre = cur->pre;

        // 插到head后
        cur->next = head->next;
        cur->pre = head;
        cur->next->pre = cur;
        head->next = cur;

        // Node *p = head->next;
        // cout << "in get(): " << endl;
        // while (p != tail) {
        //   cout << p->key << " " << p->val << endl;
        //   p = p->next;
        // }
        // cout << endl;
      }
      return q[key]->val;
    } else {
      return -1;
    }
  }

  void put(int key, int value) {
    if (q.count(key)) {
      q[key]->val = value;
      get(key);
    } else {
      if (cnt < size) {
        Node *node = new Node(key, value);
        q[key] = node;
        node->next = head->next;
        node->pre = head;
        head->next = node;
        node->next->pre = node;
        // Node *p = head->next;
        // cout << "in put(): new node" << endl;
        // while (p != tail) {
        //   cout << p->key << " " << p->val << endl;
        //   p = p->next;
        // }
        // cout << endl;
        cnt += 1;
      } else {
        // for (auto item : q) {
        //   cout << item.second->key << " " << item.second->val << endl;
        // }
        // Node *p = head->next;
        // while (p != tail) {
        //   cout << p->key << " " << p->val << endl;
        //   p = p->next;
        // }
        // cout << endl;
        // tail 移除，并更换为新的值
        int t = tail->pre->key;  // 为了后面删除map对应项
        Node *cur = tail->pre;   // 待删除的节点
        cur->key = key, cur->val = value;
        cur->pre->next = tail;
        tail->pre = cur->pre;

        // 将cur插到head后
        cur->next = head->next;
        cur->pre = head;
        cur->next->pre = cur;
        cur->pre->next = cur;

        // 更新 map
        // for (auto item : q) {
        //   cout << item.second->key << " " << item.second->val << endl;
        // }
        auto iter = q.find(t);
        q.erase(iter);
        q.insert({key, head->next});
      }
    }
  }

 private:
  typedef struct Node {
    int key;
    int val;
    Node *pre;
    Node *next;
    Node(int key, int val) : key(key), val(val) {}
  } Node;

 private:
  int size;
  int cnt;
  map<int, Node *> q;
  Node *head;
  Node *tail;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
  LRUCache *lRUCache = new LRUCache(2);
  lRUCache->put(1, 1);               // 缓存是 {1=1}
  lRUCache->put(2, 2);               // 缓存是 {1=1, 2=2}
  cout << lRUCache->get(1) << endl;  // 返回 1
  lRUCache->put(3, 3);  // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
  cout << lRUCache->get(2) << endl;  // 返回 -1 (未找到)
  lRUCache->put(4, 4);  // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
  cout << lRUCache->get(1) << endl;  // 返回 -1 (未找到)
  cout << lRUCache->get(3) << endl;  // 返回 3
  cout << lRUCache->get(4) << endl;  // 返回 4
  return 0;
}