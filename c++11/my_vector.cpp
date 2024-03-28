

#include <cstddef>
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

  void reverse(size_t n) {
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
    delete old_data;
  }

  void push_back(int val) {
    if (m_size + 1 > m_capacity) {
      reverse(m_size + 1);
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

  // 添加[]
  int& operator[](int index) noexcept { return m_date[index]; }
  int const& operator[](int index) const noexcept { return m_date[index]; }
  int size() { return m_size; }
};

int main() {
  MyVector vec;
  vec.push_back(1);
  vec.push_back(2);

  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << std::endl;
  }
}
