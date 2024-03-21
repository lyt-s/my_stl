#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

template <class T, class Alloc = std::allocator<T>>
struct Vector {
  using value_type = T;
  using allocator_type = Alloc;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = T *;
  using const_pointer = T const *;
  using reference = T &;
  using const_reference = T const &;
  using iterator = T *;
  using const_iterator = T const *;
  using reverse_iterator = std::reverse_iterator<T *>;
  using const_reverse_iterator = std::reverse_iterator<T const *>;

  T *m_data;
  size_t m_size;
  size_t m_capacity;
  [[no_unique_address]] Alloc m_alloc;

  // 默认构造函数
  Vector() noexcept : m_data(nullptr), m_size(0), m_capacity(0) {}

  ~Vector() {
    if (m_size) {
      for (size_t i = 0; i < m_size; ++i) {
        std::destroy_at(&m_data[i]);
      }
    }
    if (m_capacity != 0) {
      m_alloc.deallocate(m_data, m_capacity);

      // delete[] m_data;
    }
  }

  // 有参构造,不给初始化值时，默认给0
  explicit Vector(size_t n, Alloc const &alloc = Alloc())
      : m_size(n), m_capacity(n), m_alloc(alloc) {
    // m_data(new T[n])
    m_data = m_alloc.allocate(n);
    for (size_t i = 0; i < n; ++i) {
      std::construct_at(&m_data[i]);  // == m_data[i] = 0;
    }
  }

  Vector(size_t n, const T &value, Alloc const &alloc = Alloc()) noexcept
      : m_alloc(alloc), m_size(n), m_capacity(n) {
    m_data = m_alloc.allocate(n);
    for (size_t i = 0; i < n; ++i) {
      std::construct_at(&m_data[i], value);
    }
  }

  // explicit 后， vec = vec2 后报错， 防止其进行隐式类型转换
  Vector(const Vector &other) noexcept : m_alloc(other.m_alloc) {
    m_capacity = m_size = other.m_size;
    if (m_size != 0) {
      // m_data = new T[other.m_size];
      m_data = m_alloc.allocate(other.m_size);
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
    // 将自己清空，防止发生内存泄漏
    if (m_capacity) {
      m_alloc.deallocate(m_data, m_capacity);
    }
    // m_data = new T[other.m_size];
    m_data = m_alloc.allocate(other.m_size);
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
    if (m_capacity != 0) {
      m_alloc.deallocate(m_data, m_capacity);
    }
    m_data = other.m_data;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    other.m_data = nullptr;
    other.m_capacity = 0;
    other.m_size = 0;
    return *this;
  }

  Vector(std::initializer_list<T> ilist) : Vector(ilist.begin(), ilist.end()) {}

  template <std::random_access_iterator InputIt>
  explicit Vector(InputIt first, InputIt last, Alloc const &alloc = Alloc())
      : m_alloc(alloc) {
    size_t n = std::distance(first, last);
    // m_data = new T[n];
    m_data = m_alloc.allocate(n);
    m_capacity = m_size = n;
    for (size_t i = 0; i < n; ++i) {
      std::construct_at(&m_data[i], *first);
      ++first;
    }
  }

  size_t size() const noexcept { return m_size; }

  T &operator[](size_t index) noexcept { return m_data[index]; }

  T const &operator[](size_t index) const noexcept { return m_data[index]; }

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
      // m_data = new T[n];
      m_data = m_alloc.allocate(n);
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
      m_alloc.deallocate(old_date, old_capacity);
    }
  }

  void push_back(const T &value) {
    if (m_size + 1 >= m_capacity) [[unlikely]] {
      reserve(m_size + 1);
    }
    std::construct_at(&m_data[m_size], value);
    ++m_size;
  }

  void push_back(T &&value) {
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
  void resize(size_t n, const T &value) {
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
      // m_data = new T[m_capacity];
      m_data = m_alloc.allocate(m_size);
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
      // delete[] old_data;
      m_alloc.deallocate(old_data, old_capacity);
    }
  }

  T &front() noexcept { return m_data[0]; }
  T const &front() const noexcept { return m_data[0]; }

  T &back() noexcept { return m_data[m_size - 1]; }
  T const &back() const noexcept { return m_data[m_size - 1]; }

  T *data() noexcept { return m_data; }
  T const *data() const noexcept { return m_data; }
  T *begin() noexcept { return m_data; }
  T const *begin() const noexcept { return m_data; }
  T *end() noexcept { return m_data + m_size; }
  T const *end() const noexcept { return m_data + m_size; }
  T const *cbegin() const noexcept { return m_data; }
  T const *cend() const noexcept { return m_data + m_size; }
  // 最后一个元素的迭代器
  std::reverse_iterator<T *> rbegin() noexcept {
    return std::make_reverse_iterator(m_data + m_size);
  }

  std::reverse_iterator<T *> rend() noexcept {
    return std::make_reverse_iterator(m_data);
  }

  std::reverse_iterator<T const *> rbegin() const noexcept {
    return std::make_reverse_iterator(m_data + m_size);
  }

  std::reverse_iterator<T const *> rend() const noexcept {
    return std::make_reverse_iterator(m_data);
  }

  std::reverse_iterator<T const *> crbegin() const noexcept {
    return std::make_reverse_iterator(m_data + m_size);
  }

  std::reverse_iterator<T const *> crend() const noexcept {
    return std::make_reverse_iterator(m_data);
  }

  size_t capacity() const noexcept { return m_capacity; }
  bool empty() const noexcept { return m_size == 0; }

  // 这段代码是一个静态成员函数 max_size() 的实现，用于返回类型 T
  // 的对象或容器所能容纳的最大元素数量。

  // 在这段代码中，std::numeric_limits<size_t>::max() 返回 size_t
  // 类型的最大值，即 size_t 类型能够表示的最大正整数。

  // sizeof(T) 返回类型 T 对象所占用的字节数。

  // 因此，std::numeric_limits<size_t>::max() / sizeof(T) 表示类型 T
  // 对象或容器所能容纳的最大元素数量，即使用类型 T
  // 的对象或容器来存储一个大型数组时，数组能够容纳的最大元素数量。

  // constexpr
  // 的，意味着它可以在编译时求值，并且不会引发任何异常。这使得在编译时就可以获取到类型
  // T 对象或容器的最大容量，而无需在运行时进行计算。
  static constexpr size_t max_size() noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(T);
  }

  T &at(size_t index) {
    if (index >= m_size) [[unlikely]] {
      throw std::out_of_range("Index out of range vector::at");
    }
    return m_data[index];
  }

  T const &at(size_t index) const {
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

  T *erase(T const *iterator) noexcept(std::is_nothrow_move_assignable_v<T>) {
    size_t i = iterator - m_data;
    for (size_t j = i + 1; j != m_size; ++j) {
      m_data[j - 1] = std::move_if_noexcept(m_data[j]);
    }
    m_size -= 1;
    std::destroy_at(&m_data[m_size]);
    return const_cast<T *>(iterator);
  }

  T *erase(T const *first,
           T const *last) noexcept(std::is_nothrow_move_assignable_v<T>) {
    size_t diff = last - first;
    for (size_t j = last - m_data; j < m_size; ++j) {
      m_data[j - diff] = std::move_if_noexcept(m_data[j]);
    }
    m_size -= diff;
    for (size_t j = m_size; j < m_size + diff; ++j) {
      std::destroy_at(&m_data[j]);
    }
    return const_cast<T *>(first);
  }

  void assign(size_t n, const T &value) {
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

  void assign(std::initializer_list<T> ilist) {
    assign(ilist.begin(), ilist.end());
  }

  // ?
  Vector &operator=(std::initializer_list<T> ilist) {
    assign(ilist.begin(), ilist.end());
    return *this;
  }

  template <class... Args>
  T *emplace(T const *iterator, Args... args) {
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
  template <class... Args>
  T &emplace_back(Args &&...args) {
    if (m_size + 1 > m_capacity) [[unlikely]] {
      reserve(m_size + 1);
    }
    T *p = &m_data[m_size];
    std::construct_at(&m_data[m_size], std::forward<Args>(args)...);
    m_size += 1;
    return *p;
  }

  T *insert(T const *iterator, const T &value) {
    size_t j = iterator - m_data;
    reserve(m_size + 1);
    // j~m_size => j + 1 ~ m_size + 1
    for (size_t i = m_size; i != j; i--) {
      std::construct_at(&m_data[i], std::move(m_data[i - 1]));
      std::destroy_at(&m_data[i - 1]);
    }
    m_size += 1;
    // 插入数据
    std::construct_at(&m_data[j], value);
    return m_data + j;
  }

  T *insert(T const *iterator, T &&value) {
    size_t j = iterator - m_data;
    reserve(m_size + 1);
    // j~m_size => j + 1 ~ m_size + 1
    for (size_t i = m_size; i != j; i--) {
      std::construct_at(&m_data[i], std::move(m_data[i - 1]));
      std::destroy_at(&m_data[i - 1]);
    }
    m_size += 1;
    std::construct_at(&m_data[j], std::move(value));
    return m_data + j;
  }
  // 一次性插入 n个元素
  T *insert(T const *iterator, size_t n, T const &value) {
    size_t j = iterator - m_data;
    reserve(m_size + n);
    for (size_t i = m_size; i != j; i--) {
      std::construct_at(&m_data[i + n - 1], std::move(m_data[i - 1]));
      std::destroy_at(&m_data[i - 1]);
    }
    m_size += n;
    for (size_t i = j; i != j + n; i++) {
      std::construct_at(&m_data[i], value);
    }
    return m_data + j;
  }

  template <std::random_access_iterator InputIt>
  T *insert(T const *iterator, InputIt first, InputIt last) {
    size_t j = iterator - m_data;
    size_t n = last - first;
    reserve(m_size + n);
    for (size_t i = m_size; i != j; i--) {
      std::construct_at(&m_data[i + n - 1], m_data[i - 1]);
      std::destroy_at(&m_data[i - 1]);
    }
    m_size += n;
    for (size_t i = j; i != j + n; i++) {
      std::construct_at(&m_data[i], *first);
      ++first;
    }
    return m_data + j;
  }
  T *insert(T const *iterator, std::initializer_list<T> ilist) {
    return insert(iterator, ilist.begin(), ilist.end());
  }

  Alloc get_allocator() const noexcept { return m_alloc; }
  bool operator==(Vector const &that) noexcept {
    return std::equal(begin(), end(), that.begin(), that.end());
  }

  // auto operator<= > (Vector const &that) noexcept {
  //   return std::lexicographical_compare_three_way(begin(), end(),
  //   that.begin(),
  //                                                 that.end());
  // }
};