

#include <climits>
#include <cstddef>
#include <deque>
#include <iostream>
#include <memory>
class MyVector {
 private:
  int* m_date;
  size_t m_size;
  size_t m_capacity;

 public:
  MyVector() : m_date(nullptr), m_size(0), m_capacity(0) {}

  MyVector(size_t n, int value = 0) {
    m_date = new int[n];
    m_capacity = n;
    m_size = n;

    for (int i = 0; i < n; i++) {
      std::construct_at(&m_date[i], value);
    }
  }

  ~MyVector() { delete[] m_date; }

  MyVector(const MyVector& other) {
    m_capacity = m_size = other.m_size;
    if (m_size != 0) {
      m_date = new int[m_size];
      for (int i = 0; i < m_size; ++i) {
        std::construct_at(&m_date[i], other.m_date[i]);
      }
    } else {
      m_date = nullptr;
    }
  }

  MyVector& operator=(const MyVector& other) {
    if (this != &other) {
      delete[] m_date;
      m_size = m_capacity = other.m_size;
      m_date = new int[m_size];

      for (int i = 0; i < m_size; i++) {
        std::construct_at(&m_date[i], other.m_date[i]);
      }
    }
    return *this;
  }

  MyVector(MyVector&& other) noexcept {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_date = other.m_date;
    other.m_date = nullptr;
    other.m_capacity = 0;
    other.m_size = 0;
  }

  MyVector& operator=(MyVector&& other) noexcept {
    if (this != &other) {
      delete[] m_date;
      m_date = other.m_date;
      m_size = other.m_size;
      m_capacity = other.m_capacity;
      other.m_date = nullptr;
      other.m_capacity = 0;
      other.m_size = 0;
    }
    return *this;
  }

  void reserve(size_t n) {
    if (n <= m_capacity) {
      return;
    }
    n = std::max(n, m_capacity * 2);
    auto old_data = m_date;
    if (n == 0) {
      m_date = nullptr;
      m_size = 0;
    } else {
      m_date = new int[n];
      m_capacity = n;
    }
    for (int i = 0; i < m_size; i++) {
      std::construct_at(&m_date[i], old_data[i]);
    }
    delete[] old_data;
  }

  void resize(size_t n) {
    if (n < m_size) {
      for (size_t i = n; i < m_size; i++) {
        std::destroy_at(&m_date[i]);
      }
    } else if (n > m_size) {
      reserve(n);
      for (int i = m_size; i < n; i++) {
        std::construct_at(&m_date[i], 0);
      }
    }
    m_size = n;
  }
  void push_back(int val) {
    if (m_size + 1 > m_capacity) {
      reserve(m_size + 1);
    }
    std::construct_at(&m_date[m_size], val);
    m_size++;
  }

  void pop_back() {
    if (m_size == 0) {
      return;
    }
    std::destroy_at(&m_date[m_size - 1]);
    m_size--;
  }

  int* begin() { return m_date; }
  int* end() { return m_date + m_size; }

  int* erase(int const* it) {
    size_t i = it - m_date;
    for (size_t j = i + 1; j < m_size; j++) {
      m_date[j - 1] = std::move(m_date[j]);
    }
    m_size--;
    std::destroy_at(&m_date[m_size]);
    return const_cast<int*>(it);
  }

  // 删除成功多少值
  int* erase(int const* first, int const* last) {
    size_t diff = last - first;
    size_t iend = last - m_date;
    for (size_t j = iend; j < m_size; j++) {
      m_date[j - diff] = std::move(m_date[j]);
    }
    m_size -= diff;
    for (int i = m_size; i < m_size + diff; i++) {
      std::destroy_at(&m_date[i]);
    }
    return const_cast<int*>(first);
  }

  void clear() {
    for (int i = 0; i < m_size; i++) {
      std::destroy_at(&m_date[i]);
    }
    m_size = 0;
  }

  int* insert(int const* it, int value) {
    int j = it - m_date;
    reserve(m_size + 1);

    for (size_t i = m_size; i != j; i++) {
      std::construct_at(&m_date[i], std::move(i - 1));
      std::destroy_at(&m_date[i - 1]);
    }
    m_size += 1;
    // 插入数据
    std::construct_at(&m_date[j], value);
    return m_date + j;
  }

  int* insert(int const* it, size_t n, int val) {
    size_t j = it - m_date;
    reserve(m_size + n);
    for (size_t i = m_size; i != j; i++) {
      std::construct_at(&m_date[i + n - 1], std::move(m_date[i - 1]));
      std::destroy_at(&m_date[i - 1]);
    }
    m_size += n;
    for (size_t i = j; i != j + n; i++) {
      std::construct_at(&m_date[i], val);
    }
    return m_date + j;
  }
  // 添加[]
  int& operator[](int index) noexcept { return m_date[index]; }
  int const& operator[](int index) const noexcept { return m_date[index]; }
  int size() { return m_size; }
};

int main() {
  MyVector vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(5);
  vec.push_back(7);
  vec.erase(vec.begin());
  vec.pop_back();
  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << std::endl;
  }
}
