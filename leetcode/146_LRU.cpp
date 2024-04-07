

#include <list>
#include <unordered_map>
#include <utility>
class LRUCache {
 private:
  int m_capacity;
  std::list<std::pair<int, int>> m_list;
  std::unordered_map<int, decltype(m_list.begin())> m_map;

  void getRecentPage(int key) {
    auto it = m_map.find(key);
    if (it != m_map.end()) {
      auto temp_it =
          m_list.insert(m_list.end(), std::make_pair(key, it->second->second));
      m_list.erase(it->second);
      m_map[key] = temp_it;
    }
  }

  void update(int key, int value) {
    m_map[key]->second = value;
    getRecentPage(key);
  }

  void deleteOldestPage() {
    m_map.erase(m_list.begin()->first);
    m_list.pop_front();
  }

  void addNewPage(int key, int value) {
    auto it = m_list.insert(m_list.end(), std::make_pair(key, value));
    m_map[key] = std::move(it);
  }

 public:
  LRUCache(int capacity) : m_capacity(capacity) {}

  void put(int key, int value) {
    auto it = m_map.find(key);
    if (it == m_map.end()) {
      if (m_capacity == m_list.size()) {
        deleteOldestPage();
      }
      addNewPage(key, value);
    } else {
      update(key, value);
    }
  }
  int get(int key) {
    auto it = m_map.find(key);
    if (it != m_map.end()) {
      getRecentPage(key);
      return it->second->second;
    }
    return -1;
  }
};

int main() {
  LRUCache *lRUCache = new LRUCache(2);
  lRUCache->put(1, 1);  // 缓存是 {1=1}
  lRUCache->put(2, 2);  // 缓存是 {1=1, 2=2}
  lRUCache->get(1);     // 返回 1
  lRUCache->put(3, 3);  // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
  lRUCache->get(2);  // 返回 -1 (未找到)
  lRUCache->put(4, 4);  // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
  lRUCache->get(1);  // 返回 -1 (未找到)
  lRUCache->get(3);  // 返回 3
  lRUCache->get(4);  // 返回 4
  return 0;
}