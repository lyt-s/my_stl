#include <cstddef>
#include <utility>

template <typename T>
class SharedPtr {
 private:
  size_t* m_count;
  T* m_ptr;

 public:
  SharedPtr() : m_ptr(nullptr), m_count(new size_t) {}
  SharedPtr(T* ptr) : m_ptr(ptr), m_count(new size_t) { *m_count = 1; }

  ~SharedPtr() {
    --(*m_count);
    if (*m_count == 0) {
      delete m_ptr;
      delete m_count;
      m_ptr = nullptr;
      m_count = nullptr;
    }
  }

  // 拷贝构造函数
  SharedPtr(const SharedPtr& ptr) {
    m_count = ptr.m_count;
    m_ptr = ptr.m_ptr;
    ++(*m_count);
  }

  // 拷贝赋值
  void operator=(const SharedPtr& ptr) { SharedPtr(std::move(ptr)); }

  // 移动构造
  SharedPtr(SharedPtr&& ptr) : m_ptr(ptr.m_ptr), m_count(ptr.m_count) {
    ++(*m_count);
  }

  // 移动赋值
  void operator=(const SharedPtr&& ptr) { ++(*m_count); }

  // 解引用
  T& operator*() { return *m_ptr; }

  // 箭头
  T* operator->() { return m_ptr; }

  // bool
  operator bool() { return m_ptr == nullptr; }

  T* get() { return m_ptr; }

  size_t use_count() { return *m_count; }

  bool unique() { return *m_count == 1; }

  void swap(SharedPtr& ptr) { std::swap(*this, ptr); }
};