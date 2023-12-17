#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

struct Vector {
  int *m_data;
  size_t m_size;
  size_t m_capacity;

  // 默认构造函数
  explicit Vector() noexcept : m_data(nullptr), m_size(0), m_capacity(0) {}

  ~Vector() { delete[] m_data; }

  // 有参构造,不给初始化值时，默认给0
  explicit Vector(size_t n) : m_data(new int[n]), m_size(n), m_capacity(n) {
    for (size_t i = 0; i < n; ++i) {
      std::construct_at(&m_data[i]);  // == m_data[i] = 0;
    }
  }

  Vector(size_t n, const int &value) noexcept
      : m_data(new int[n]), m_size(n), m_capacity(n) {
    for (size_t i = 0; i < n; ++i) {
      std::construct_at(&m_data[i], value);
    }
  }

  // explicit 后， vec = vec2 后报错， 防止其进行隐式类型转换
  Vector(const Vector &other) {
    m_capacity = m_size = other.m_size;
    if (m_size != 0) {
      m_data = new int[other.m_size];
      for (size_t i = 0; i < m_size; ++i) {
        std::construct_at(&m_data[i], std::as_const(other.m_data[i]));
      }
    } else {
      m_data = nullptr;
    }
  }

  Vector &operator=(const Vector &other) {
    if (this == &other) {
      return *this;
    }
    m_data = new int[other.m_size];
    for (size_t i = 0; i < other.size(); ++i) {
      // const Vector 类型没有合适的重载
      // operator[]，同时，试图使用的方法没有被标记为 const。
      // 问题出现在您尝试使用 [] 运算符来访问 const Vector
      //   对象的元素时，但是没有合适的方法可以实现这个操作。根据错误提示，您需要将该方法标记为
      // const，以允许在 const Vector 对象上进行访问操作。
      //   No viable overloaded operator[] for type 'const Vector'
      std::construct_at(&m_data[i], std::as_const(other[i]));
    }
    m_capacity = m_size = other.m_size;
    return *this;
  }

  // 移动构造
  Vector(Vector &&other) noexcept {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = other.m_data;
    other.m_data = nullptr;
    other.m_capacity = 0;
    other.m_size = 0;
  }

  // 移动赋值
  Vector &operator=(Vector &&other) noexcept {
    if (this == &other) [[unlikely]] {
      return *this;
    }
    // 先将自己的数据销毁
    for (size_t i = 0; i != m_size; i++) {
      std::destroy_at(&m_data[i]);
    }
    // deallocate capacity todo 存在泄露
    // delete[] m_data;
    m_data = other.m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    other.m_data = nullptr;
    other.m_capacity = 0;
    other.m_size = 0;
    return *this;
  }

  Vector(std::initializer_list<int> ilist) {
    Vector(ilist.begin(), ilist.end());
  }

  template <std::random_access_iterator InputIt>
  explicit Vector(InputIt first, InputIt last) {
    size_t n = std::distance(first, last);
    m_data = new int[n];
    m_capacity = m_size = n;
    for (size_t i = 0; i < n; ++i) {
      std::construct_at(&m_data[i], *first);
      ++first;
    }
  }

  size_t size() const noexcept { return m_size; }

  int &operator[](size_t index) noexcept { return m_data[index]; }

  int const &operator[](size_t index) const noexcept { return m_data[index]; }

  void clear() noexcept {
    for (size_t i = 0; i < m_size; ++i) {
      std::destroy_at(&m_data[i]);
    }
    m_size = 0;
  }

  void reserve(size_t n) {
    if (n <= m_capacity) [[likely]] {
      return;
    }
    n = std::max(n, m_capacity * 2);
    auto old_date = m_data;
    auto old_capacity = m_capacity;
    if (n == 0) {
      m_data = nullptr;
      m_size = 0;
    } else {
      m_data = new int[n];
      m_capacity = n;
    }
    // 将原来的数据，保存到新的内存空间中
    if (old_capacity != 0) {
      for (size_t i = 0; i < m_size; ++i) {
        std::construct_at(&m_data[i], std::move_if_noexcept(old_date[i]));
      }
      for (size_t i = 0; i != m_size; ++i) {
        std::destroy_at(&old_date[i]);
      }
      //   delete[] old_date;
      // 存在泄露
    }
  }

  void push_back(const int &value) {
    if (m_size + 1 >= m_capacity) [[unlikely]] {
      reserve(m_size + 1);
    }
    std::construct_at(&m_data[m_size], value);
    ++m_size;
  }

  void push_back(int &&value) {
    if (m_size + 1 >= m_capacity) [[unlikely]] {
      reserve(m_size + 1);
    }
    std::construct_at(&m_data[m_size], std::move(value));
    m_size += 1;
  }

  void pop_back() {
    if (m_size == 0) [[unlikely]] {
      return;
    }
    std::destroy_at(&m_data[m_size - 1]);
    --m_size;
  }
  void resize(size_t n) {
    if (n < m_size) {
      for (size_t i = n; i < m_size; ++i) {
        std::destroy_at(&m_data[i]);
      }
      m_capacity = n;
    } else if (n > m_size) {
      reserve(n);
      for (size_t i = m_size; i < n; ++i) {
        std::construct_at(&m_data[i]);  // m_data[i] = 0;
      }
    }
    m_size = n;
  }
  void resize(size_t n, const int &value) {
    if (n < m_size) {
      for (size_t i = n; i < m_size; ++i) {
        std::destroy_at(&m_data[i]);
      }
      //   m_size = n;
    } else if (n > m_size) {
      reserve(n);
      for (size_t i = m_size; i < n; ++i) {
        std::construct_at(&m_data[i], value);
      }
    }
    m_size = n;
  }

  void shrink_to_fit() noexcept {
    auto old_data = m_data;
    auto old_capacity = m_capacity;
    m_capacity = m_size;
    if (m_size == 0) [[unlikely]] {
      m_data = nullptr;
    } else {
      m_data = new int[m_capacity];
    }
    if (old_capacity != 0) [[likely]] {
      for (size_t i = 0; i < m_size; ++i) {
        //   memcpy(m_data, old_data, m_size);
        std::construct_at(
            &m_data[i],
            std::move_if_noexcept(
                old_data[i]));  // m_data[i] = std::move(old_data[i])
        std::destroy_at(&old_data[i]);
      }
      delete[] old_data;
    }
  }

  int &front() noexcept { return m_data[0]; }
  int const &front() const noexcept { return m_data[0]; }

  int &back() noexcept { return m_data[m_size - 1]; }
  int const &back() const noexcept { return m_data[m_size - 1]; }

  int *data() noexcept { return m_data; }
  int const *data() const noexcept { return m_data; }
  int *begin() noexcept { return m_data; }
  int const *begin() const noexcept { return m_data; }
  int *end() noexcept { return m_data + m_size; }
  int const *end() const noexcept { return m_data + m_size; }
  int const *cbegin() const noexcept { return m_data; }
  int const *cend() const noexcept { return m_data + m_size; }
  // 最后一个元素的迭代器
  std::reverse_iterator<int *> rbegin() noexcept {
    return std::make_reverse_iterator(m_data + m_size);
  }

  std::reverse_iterator<int *> rend() noexcept {
    return std::make_reverse_iterator(m_data);
  }

  std::reverse_iterator<int const *> rbegin() const noexcept {
    return std::make_reverse_iterator(m_data + m_size);
  }

  std::reverse_iterator<int const *> rend() const noexcept {
    return std::make_reverse_iterator(m_data);
  }

  std::reverse_iterator<int const *> crbegin() const noexcept {
    return std::make_reverse_iterator(m_data + m_size);
  }

  std::reverse_iterator<int const *> crend() const noexcept {
    return std::make_reverse_iterator(m_data);
  }

  size_t capacity() const noexcept { return m_capacity; }
  bool empty() const noexcept { return m_size == 0; }

  static constexpr size_t max_size() noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(int);
  }

  int &at(size_t index) {
    if (index >= m_size) [[unlikely]] {
      throw std::out_of_range("Index out of range vector::at");
    }
    return m_data[index];
  }

  int const &at(size_t index) const {
    if (index >= m_size) [[unlikely]] {
      throw std::out_of_range("Index out of range vector::at");
    }
    return m_data[index];
  }

  void swap(Vector &other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_size, other.m_size);
  }

  int *erase(int const *iterator) noexcept(
      std::is_nothrow_move_assignable_v<int>) {
    size_t i = iterator - m_data;
    for (size_t j = i + 1; j != m_size; ++j) {
      m_data[j - 1] = std::move_if_noexcept(m_data[j]);
    }
    m_size -= 1;
    std::destroy_at(&m_data[m_size]);
    return const_cast<int *>(iterator);
  }

  int *erase(int const *first,
             int const *last) noexcept(std::is_nothrow_move_assignable_v<int>) {
    size_t diff = last - first;
    for (size_t j = last - m_data; j < m_size; ++j) {
      m_data[j - diff] = std::move_if_noexcept(m_data[j]);
    }
    m_size -= diff;
    for (size_t j = m_size; j < m_size + diff; ++j) {
      std::destroy_at(&m_data[j]);
    }
    return const_cast<int *>(first);
  }

  void assign(size_t n, const int &value) {
    clear();
    reserve(n);
    m_size = n;
    for (size_t i = 0; i < m_size; ++i) {
      std::construct_at(&m_data[i], value);
    }
  }

  template <std::random_access_iterator InputIt>
  void assign(InputIt first, InputIt last) {
    clear();
    size_t n = last - first;
    reserve(n);
    m_size = n;
    for (size_t i = 0; i < n; ++i) {
      std::construct_at(&m_data[i], *first);
      ++first;
    }
  }

  void assign(std::initializer_list<int> ilist) {
    assign(ilist.begin(), ilist.end());
  }

  // ?
  Vector &operator=(std::initializer_list<int> ilist) {
    assign(ilist.begin(), ilist.end());
  }

  template <class... Args>
  int *emplace(int const *iterator, Args... args) {
    size_t j = iterator - m_data;
    reserve(m_size + 1);
    // j~m_size => j + 1 ~ m_size + 1
    for (size_t i = m_size; i != j; i--) {
      std::construct_at(&m_data[i], std ::move(m_data[i - 1]));
      std::destroy_at(&m_data[i - 1]);
    }
    m_size += 1;
    std::construct_at(&m_data[j], std::forward<Args>(args)...);
    return m_data + j;
  }

  // todo insert emplace_back
};

int main() {
  // 实现 operator[] size()
  auto print_list = [&](Vector &vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
      printf("arr[%zd] = %d\n ", i, vector[i]);
    }
  };

  auto push_list = [&](Vector &vector) {
    for (size_t i = 0; i < 16; ++i) {
      vector.push_back(i);
    }
  };

  //   // test  默认构造函数
  //   Vector vec;
  //   // 有参构造函数
  //   Vector vec2(5, 9);
  //   print_list(vec2);
  //   // 拷贝构造  实现深拷贝 --如果没有就会
  //   // free(): double free detected in tcache 2
  //   // 拷贝赋值 深拷贝 这里
  //   Vector vec3(vec2);
  //   print_list(vec3);
  //   // 会调用 拷贝构造函数
  //   Vector vec4 = vec3;
  //   vec4[3] = 0;
  //   print_list(vec4);
  //   vec4 = std::move(vec3);
  //   print_list(vec4);

  //   //   todo
  //   initializer list
  //   Vector vec5{1, 2, 3, 4, 5, 6};
  //   std::cout << vec5[1] << "\n";
  //   print_list(vec5);

  // test clear() push_back() resize() pop_back()
  //   Vector vec(4, 3);
  //   print_list(vec);
  //   vec.clear();
  //   print_list(vec);
  //   std::cout << "vec.size() = " << vec.size() << std::endl;
  //   push_list(vec);
  //   print_list(vec);
  //   std::cout << "vec.resize(8) = " << std::endl;
  //   vec.resize(8);
  //   print_list(vec);
  //   std::cout << "vec.resize(16) = " << std::endl;
  //   vec.resize(16);
  //   print_list(vec);
  //   std::cout << "vec.resize(16,1) = " << std::endl;
  //   vec.resize(16, 1);
  //   print_list(vec);
  //   vec.resize(8);
  //   vec.resize(17, 1);
  //   vec[16] = 2;
  //   print_list(vec);
  //   vec.pop_back();
  //   print_list(vec);

  // test shrink_to_fit capacity()
  //   Vector bar;
  //   bar.reserve(100);
  //   bar.resize(100);
  //   std::cout << "Capacity of a 100-element vector is " << bar.capacity() <<
  //   '\n'; bar.resize(50); std::cout << "Capacity after resize(50) is " <<
  //   bar.capacity() << '\n'; bar.shrink_to_fit(); std::cout <<
  //   "Capacity_after_shrink_to_fit() is" << bar.capacity() << '\n';
  //   bar.clear();
  //   std::cout << "Capacity after clear() is " << bar.capacity() << '\n';
  //   bar.shrink_to_fit();
  //   std::cout << "Capacity after shrink_to_fit() is " << bar.capacity() <<
  //   '\n';

  //   // test assign() erase()
  //   Vector vec;
  //   Vector vec2;
  //   push_list(vec2);
  //   vec.assign(4, 4);
  //   print_list(vec);
  //   vec.assign(vec2.begin(), vec2.end());
  //   print_list(vec);
  //   vec.erase(vec.begin());
  //   print_list(vec);
  //   vec.erase(vec.begin(), vec.begin() + 3);
  //   print_list(vec);
  return 0;
}