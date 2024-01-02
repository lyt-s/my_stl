#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <type_traits>
#include <utility>

// #include "foo.h"

template <class T, class Alloc = std::allocator<T>>
struct Vector {
  using value_type = T;
  using allocator_type = Alloc;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = T*;
  using const_pointer = T const*;
  using reference = T&;
  using const_reference = T const&;
  using iterator = T*;
  using const_iterator = T const*;
  using reverse_iterator = std::reverse_iterator<T*>;
  using const_reverse_iterator = std::reverse_iterator<T const*>;

  T* m_data;
  size_t m_size;
  size_t m_capacity;
  [[no_unique_address]] Alloc m_alloc;

  Vector() noexcept {
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
  }

  // arr = Vector({1, 2, 3, 4, 5, 6});
  // 在构造函数内调用另一个构造函数，必须再 : 中调用
  Vector(std::initializer_list<T> ilist, Alloc const& alloc = Alloc())
      : Vector(ilist.begin(), ilist.end(), alloc) {}

  explicit Vector(size_t n, Alloc const& alloc = Alloc()) : m_alloc(alloc) {
    m_data = m_alloc.allocate(n);
    m_size = n;
    m_capacity = n;
    for (size_t i = 0; i != n; i++) {
      std::construct_at(&m_data);  // == m_data[i] = 0;
    }
  }
  // explicit 禁止 =  进行隐式类型转换
  explicit Vector(size_t n, int value = 0) {
    m_data = new int[n];
    m_capacity = m_size = n;
    for (size_t i = 0; i < n; ++i) {
      m_data[i] = value;
    }
    m_size = n;
    m_capacity = n;
  }

  // insert 需要
  template <std::random_access_iterator InputIt>
  explicit Vector(InputIt first, InputIt last, Alloc const& alloc = Alloc())
      : m_alloc(alloc) {
    // size_t n = std::distance(first, last);
    size_t n = last - first;
    m_data = m_alloc.allocate(n);  // 申请空间
    // m_data = new int[n];  // 申请空间
    m_capacity = m_size = n;
    for (size_t i = 0; i < n; ++i) {
      m_data[i] = *first;
      ++first;
    }
  }

  void clear() noexcept {
    for (size_t i = 0; i != m_size; i++) {
      std::destroy_at(&m_data[i]);
    }
    m_size = 0;
  }

  void resize(size_t n) {
    if (n < m_size) {
      for (size_t i = n; i != m_size; ++i) {
        std::destroy_at(&m_data[i]);
      }
    } else if (n > m_size) {
      reserve(n);
      for (size_t i = m_size; i < n; ++i) {
        std::construct_at(&m_data[i]);  // m_data[i] = 0
      }
    }
    m_size = n;
  }

  void resize(size_t n, T const& value) {
    if (n < m_size) {
      // resize 变小了，需要删除
      for (size_t i = n; i != m_size; ++i) {
        std::destroy_at(&m_data[i]);
      }
    } else if (n > m_size) {
      reserve(n);
      // 扩大部分置为value
      for (size_t i = m_size; i < n; ++i) {
        std::construct_at(&m_data[i], value);  // m_data[i] = value;
      }
    }
    m_size = n;
  }

  // 请求移除未使用的容量。
  //   它是减少 capacity() 到 size() 非强制性请求。请求是否达成依赖于实现。
  void shrink_to_fit() noexcept {
    auto old_data = m_data;
    auto old_capacity = m_capacity;
    m_capacity = m_size;
    if (m_size == 0) {
      m_data = nullptr;
    } else {
      // m_data = new int[m_size];
      m_data = m_alloc.allocate(m_size);
    }
    if (old_capacity != 0) {
      for (size_t i = 0; i != m_size; i++) {
        // memcpy(m_data, old_data, m_size);
        std::construct_at(
            &m_data[i],
            std::move_if_noexcept(
                old_data[i]));  // m_data[i] = std::move(old_data[i]);
        std::destroy_at(&old_data[i]);
      }
      // delete old_data;
      m_alloc.deallocate(old_data, old_capacity);
    }
  }

  void reserve(size_t n) {
    if (n <= m_capacity) [[likely]] {
      return;
    }
    n = std::max(n, m_capacity * 2);
    // printf("grow from %zd to %zd\n", m_capacity, n);
    auto old_data = m_data;
    auto old_capacity = m_capacity;
    // resize(0)
    if (n == 0) {
      m_data = nullptr;
      m_capacity = 0;

    } else {
      m_data = new int[n];
      m_capacity = n;
    }
    if (old_capacity != 0) {
      for (size_t i = 0; i < m_size; ++i) {
        // memcpy(m_data, old_data, std::min(old_size, m_size) * sizeof(int));
        std::construct_at(&m_data[i], std::move_if_noexcept(old_data[i]));
      }
      for (size_t i = 0; i < m_size; ++i) {
        std::destroy_at(&m_data[i]);
      }
      // delete[] old_data;
      m_alloc.deallocate(old_data, old_capacity);
    }
  }

  size_t capacity() const noexcept { return m_capacity; }

  //   void resize(size_t n) {
  //     // 1. 防止内存泄漏
  //     //  if (m_data) {
  //     //    //  Vector arr{3};
  //     //    // arr.resize(3);
  //     //    // 防止内存泄漏
  //     //    delete[] m_data;
  //     //  }
  //     // 2. 解决resize后，老数据丢失问题。
  //     auto old_data = m_data;
  //     auto old_size = m_size;
  //     // resize(0)
  //     if (n == 0) {
  //       m_data = nullptr;
  //       m_size = 0;
  //     } else {
  //       m_data = new int[n]{};
  //       m_size = n;
  //     }
  //     if (old_data) {
  //       //   // 将旧数据拷贝到进内存中。
  //       //   memcpy(m_data, old_data, old_size * sizeof(int));
  //       // 将旧数据拷贝到进内存中。这里解决，  resize(6)后resize(3)的情况处理
  //       size_t copy_size = std::min(old_size, n);
  //       if (copy_size != 0) {
  //         memcpy(m_data, old_data, std::min(old_size, n) * sizeof(int));
  //       }
  //       delete[] old_data;
  //     }
  //   }
  size_t size() const noexcept {
    // size(Vector *this)
    // return sizeof(m_data) / sizeof(m_data[0]);
    return m_size;
  }

  bool empty() const noexcept { return m_size == 0; }

  static constexpr size_t max_size() noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(int);
  }

  //   // 这里返回纯右值
  //   int operator[](size_t i) const {
  //     return m_data[i];
  //   }  // 这里添加const ， 否则 const Vector &v = v; 无法赋值

  // 这里返回纯右值 , 防止多余拷贝 ，和上面功能是一样的
  T const& operator[](size_t i) const noexcept {
    return m_data[i];
  }  // 这里添加const ， 否则 const Vector &v = v; 无法赋值

  // 这里返回左值引用
  T& operator[](size_t i) noexcept {
    return m_data[i];
    //
  }

  T const& at(size_t i) const {
    if (i >= m_size) [[unlikely]] {
      throw std::out_of_range("index out of range(vector::at)");
    }
    return m_data[i];
  }

  T& at(size_t i) {
    // 小概率事件，编译器优化
    if (i >= m_size) [[unlikely]] {
      throw std::out_of_range("index out of range(vector::at)");
    }
    return m_data[i];
  }

  Vector(Vector&& v) noexcept : m_alloc(v.m_alloc) {
    m_data = v.m_data;
    m_size = v.m_size;
    m_capacity = v.m_capacity;
    v.m_data = nullptr;
    v.m_size = 0;
    v.m_capacity = 0;
  }

  Vector(Vector&& that, Alloc const& alloc) noexcept : m_alloc(alloc) {
    m_data = that.m_data;
    m_size = that.m_size;
    m_capacity = that.m_capacity;
    that.m_data = nullptr;
    that.m_size = 0;
    that.m_capacity = 0;
  }

  Vector& operator=(Vector&& v) noexcept {
    if (&v == this) [[unlikely]] {
      return *this;
    }
    // if (m_size != 0) {
    //   delete[] m_data;
    // }
    for (size_t i = 0; i != m_size; ++i) {
      std::destroy_at(&m_data[i]);
    }
    if (m_capacity != 0) {
      m_alloc.deallocate(m_data, m_capacity);
    }
    m_data = v.m_data;
    m_size = v.m_size;
    m_capacity = v.m_capacity;
    v.m_data = nullptr;
    v.m_size = 0;
    v.m_capacity = 0;
    return *this;
  }

  void swap(Vector& other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }

  Vector(const Vector& v) : m_alloc(v.m_alloc) {
    // 浅拷贝
    // m_data = v.m_data;
    // m_size = v.m_size;
    // 深拷贝
    m_capacity = m_size = v.size();
    if (m_size != 0) {
      // m_data = new int[v.size()];
      m_data = m_alloc.allocate(m_size);
      // memcpy(m_data, v.m_data, m_size * sizeof(int));
      for (size_t i = 0; i != m_size; i++) {
        std::construct_at(&m_data[i], std::as_const(v.m_data[i]));
      }
    } else {
      m_data = nullptr;
    }
  }

  Vector(Vector const& that, Alloc const& alloc) : m_alloc(alloc) {
    m_capacity = m_size = that.m_size;
    if (m_size != 0) {
      m_data = m_alloc.allocate(m_size);
      // memcpy(m_data, that.m_data, m_size * sizeof(int));
      for (size_t i = 0; i != m_size; i++) {
        std::construct_at(&m_data[i], std::as_const(that.m_data[i]));
      }
    } else {
      m_data = nullptr;
    }
  }

  Vector& operator=(Vector const& v) {
    if (&v == this) [[unlikely]] {
      return *this;
    }
    reserve(v.m_size);
    m_size = v.m_size;
    m_capacity = v.m_capacity;
    if (m_size != 0) {
      // m_data = new int[v.size()];
      // memcpy(m_data, v.m_data, m_size * sizeof(int));
      for (size_t i = 0; i != m_size; i++) {
        std::construct_at(&m_data[i], std::as_const(v.m_data[i]));
      }
    }
    return *this;
  }

  T const& front() const noexcept {
    // return m_data[0];
    // return operator[](0);
    return *m_data;
  }

  T& front() noexcept {
    // return m_data[0];
    // return operator[](0);
    return *m_data;
  }

  T const& back() const noexcept {
    // return m_data[m_size - 1];
    return operator[](m_size - 1);
  }

  T& back() noexcept {
    // return m_data[m_size - 1];
    return operator[](m_size - 1);
  }

  void push_back(T const& val) {
    if (m_size + 1 >= m_capacity) [[unlikely]] {
      reserve(m_size + 1);
    }
    std::construct_at(&m_data[m_size], val);
    m_size = m_size + 1;
    // back() = val;
    // m_data[m_size] = val; // todo 有问题
  }

  template <class... Args>
  T& emplace_back(Args&&... args) {
    if (m_size + 1 >= m_capacity) [[unlikely]] {
      reserve(m_size + 1);
    }
    T* p = &m_data[m_size];
    std::construct_at(p, std::forward<Args>(args)...);
    m_size = m_size + 1;
    return *p;
  }

  T* data() noexcept { return m_data; }

  T const* data() const noexcept { return m_data; }

  T const* cdata() const noexcept { return m_data; }

  T* begin() noexcept { return m_data; }

  T* end() noexcept { return m_data + m_size; }

  T const* begin() const noexcept { return m_data; }

  T const* end() const noexcept { return m_data + m_size; }

  T const* cbegin() const noexcept { return m_data; }

  T const* cend() const noexcept { return m_data + m_size; }

  std::reverse_iterator<T*> rbegin() noexcept {
    return std::make_reverse_iterator(m_data + m_size);
  }

  std::reverse_iterator<T*> rend() noexcept {
    return std::make_reverse_iterator(m_data);
  }

  std::reverse_iterator<T const*> rbegin() const noexcept {
    return std::make_reverse_iterator(m_data + m_size);
  }

  std::reverse_iterator<T const*> rend() const noexcept {
    return std::make_reverse_iterator(m_data);
  }

  std::reverse_iterator<T const*> crbegin() const noexcept {
    return std::make_reverse_iterator(m_data + m_size);
  }

  std::reverse_iterator<T const*> crend() const noexcept {
    return std::make_reverse_iterator(m_data);
  }

  void pop_back() noexcept {
    m_size -= 1;
    std::destroy_at(&m_data[m_size]);
  }

  T* erase(T const* it) noexcept(std::is_nothrow_move_assignable_v<T>) {
    size_t i = it - m_data;

    for (size_t j = i + 1; j != m_size; j++) {
      m_data[j - 1] = std::move(m_data[j]);
    }
    m_size -= 1;
    std::destroy_at(&m_data[m_size]);
    return const_cast<T*>(it);
  }

  T* erase(T const* first,
           T const* last) noexcept(std::is_nothrow_move_assignable_v<T>) {
    size_t i = first - m_data;
    size_t j = last - m_data;
    size_t diff = j - i;
    for (; j != m_size; j++) {
      m_data[j - diff] = std::move(m_data[j]);
    }
    m_size -= diff;
    for (size_t j = m_size; j != m_size + diff; j++) {
      std::destroy_at(&m_data[j]);
    }
    return const_cast<T*>(first);
  }

  // 下标删除
  //   void erase(size_t i) {
  //     if (i >= m_size) [[unlikely]] {
  //       throw std::out_of_range("out of range");
  //     }
  //     for (size_t j = i; j < m_size - 1; ++j) {
  //       operator[](j) = std::move(operator[](j + 1));
  //     }
  //     resize(m_size - 1);
  //   }
  //   // 删除区间
  //   void erase(size_t ibeg, size_t iend) {
  //     if (ibeg >= m_size) [[unlikely]] {
  //       throw std::out_of_range("out of range");
  //     }
  //     if (iend >= m_size) [[unlikely]] {
  //       throw std::out_of_range("out of range");
  //     }
  //     size_t diff = iend - ibeg;
  //     for (size_t i = iend; i < m_size; ++i) {
  //       operator[](i - diff) = std::move(operator[](i));
  //     }
  //     resize(m_size - diff);
  //     // return diff;
  //   }

  void assign(size_t n, T value) {
    clear();
    reserve(n);
    m_size = n;
    for (size_t i = 0; i < n; ++i) {
      //   m_data[i] = value;
      std::construct_at(&m_data[i], value);
    }
  }

  template <std::random_access_iterator InputIt>
  void assign(InputIt first, InputIt last) {
    // 将原来的内容清空
    clear();
    size_t n = last - first;
    reserve(n);
    m_size = n;
    for (size_t i = 0; i < n; ++i) {
      //   m_data[i] = *first++;
      std::construct_at(&m_data[i], *first);
      ++first;
    }
  }

  void assign(std::initializer_list<T> ilist) {
    assign(ilist.begin(), ilist.end());
  }

  Vector& operator=(std::initializer_list<T> ilist) {
    assign(ilist.begin(), ilist.end());
    return *this;
  }

  // ----------------------------------------------------------------

  template <class... Args>
  T* emplace(T const* it, Args&&... args) {
    size_t j = it - m_data;
    reserve(m_size + 1);
    if (j >= m_size) [[unlikely]] {
      throw std::out_of_range("out of range");
    }
    // j ~ m_size => j + 1 ~ m_size + 1
    for (size_t i = m_size; i != j; --i) {
      std::construct_at(&m_data[i], std::move(m_data[i - 1]));
      std::destroy_at(&m_data[i - 1]);
    }
    std::construct_at(&m_data[j], std::forward<Args>(args)...);
    ++m_size;
    return m_data + j;
  }

  // insert 一个
  T* insert(T const* it, T&& value) {
    size_t j = it - m_data;

    reserve(m_size + 1);
    // j ~ m_size => j + 1 ~ m_size + n
    for (size_t i = m_size; i != j; i--) {
      std::construct_at(&m_data[i], std::move(m_data[i - 1]));
      std::destroy_at(&m_data[i - 1]);
    }
    m_size += 1;

    std::construct_at(&m_data[j], std::move(value));
    return m_data + j;
  }

  T* insert(T const* it, T const& value) {
    size_t j = it - m_data;

    reserve(m_size + 1);
    // j ~ m_size => j + 1 ~ m_size + n
    for (size_t i = m_size; i != j; i--) {
      std::construct_at(&m_data[i], std::move(m_data[i - 1]));
      std::destroy_at(&m_data[i - 1]);
    }
    m_size += 1;

    std::construct_at(&m_data[j], std::move(value));
    return m_data + j;
  }

  T* insert(T const* it, size_t n, T const& val) {
    size_t j = it - m_data;
    if (n == 0) [[unlikely]]
      return const_cast<T*>(it);
    reserve(m_size + n);
    // j ~ m_size => j + n ~ m_size + n
    for (size_t i = m_size; i != j; i--) {
      std::construct_at(&m_data[i + n - 1], std::move(m_data[i - 1]));
      std::destroy_at(&m_data[i - 1]);
    }
    m_size += n;
    for (size_t i = j; i != j + n; i++) {
      std::construct_at(&m_data[i], val);
    }
    return m_data + j;
  }

  template <std::random_access_iterator InputIt>
  T* insert(T const* it, InputIt first, InputIt last) {
    size_t j = it - m_data;
    size_t n = last - first;
    if (n == 0) [[unlikely]] {
      return const_cast<T*>(it);
    }
    reserve(m_size + n);
    // j ~ m_size => j + 1 ~ m_size + n
    for (size_t i = m_size; i != j; i--) {
      std::construct_at(&m_data[i + n - 1], std::move(m_data[i - 1]));
      std::destroy_at(&m_data[i - 1]);
    }
    m_size += n;
    for (size_t i = j; i != j + n; i++) {
      std::construct_at(&m_data[i], *first++);
    }
    return m_data + j;
  }

  T* insert(T const* it, std::initializer_list<T> ilist) {
    return insert(it, ilist.begin(), ilist.end());
  }
  ~Vector() noexcept { delete[] m_data; }

  Alloc get_allocator() const noexcept { return m_alloc; }

  bool operator==(Vector const& that) noexcept {
    return std::equal(begin(), end(), that.begin(), that.end());
  }

  //   auto operator<= > (Vector const& that) noexcept {
  //     return std::lexicographical_compare_three_way(begin(), end(),
  //     that.begin(),
  //                                                   that.end());
  //   }
};

int main() {
  // 实现 operator[] size()
  auto print_list = [&](Vector<int>& vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
      printf("arr[%zd] = %d\n ", i, vector[i]);
    }
  };

  auto push_list = [&](Vector<int>& vector) {
    for (size_t i = 0; i < 16; ++i) {
      vector.push_back(i);
    }
  };
  // 1. test resize [] 构造函数
  // // explicit Vector(size_t n)
  // //   Vector arr2 = 3; // error
  // // 1. Vector(size_t n)
  // Vector<int> arr{3};
  // // 2. 默认构造函数， resize()
  // Vector<int> arr2;
  // // 防止内存泄漏
  // arr.resize(3);
  // // arr.size() -- size() 函数
  // for (size_t i = 0; i < arr.size(); ++i) {
  //   // 重载operator[]，  --- int &operator[]
  //   arr[i] = i;
  //   // Expression is not
  //   // assignableclang(typecheck_expression_not_modifiable_lvalue)
  //   //
  //   //
  //   通常在尝试将值赋给不是lvalue的表达式或尝试修改常量或只读变量时会出现此错误。
  //   // todo : 添加  --- int &operator[] ， 来返回左值引用
  // }
  // // 3. resize 要保存原来的内容，
  // arr.resize(4);  // 这里解决 resize后，print 0 0 0 0
  // arr.resize(2);
  // // 4. resize(6) 后 resize(3) ,的情况处理
  // for (size_t i = 0; i < arr2.size(); i++) {
  //   printf("a[%zd] = %d\n", i, arr[i]);  // arr[i] 和
  //   arr.operator[](i);等价
  // }
  // // 5. resize(0);
  // arr.resize(0);
  // arr.clear();

  // 2. test 默认构造，reserve
  //   Vector arr;
  //   // size =0 cap =0
  //   // size =1 cap =1 *
  //   // size = 2 cap = 2 *
  //   // size = 3 cap = 4
  //   // size = 4 cap = 4
  //   // size = 5 cap = 8 *
  //   // ...
  //   // size =9 cap = 16 *
  //   // 平均复杂度，o(n);
  //   arr.reserve(16);
  //   auto arr2 = arr;
  //   arr2.resize(2);  // 深拷贝，--->只会改变 arr2的值,互不影响
  //   for (int i = 0; i < 16; i++) {
  //     // printf("arr[%zd] = %d\n", i, arr[i]);
  //     printf("arr.push_back(%d)\n", i);
  //     arr.push_back(i);
  //   }
  //   for (size_t i = 0; i < arr2.size(); i++) {
  //     printf("arr2[%zd] = %d\n", i, arr2[i]);
  //   }  // 未定义拷贝构造函数时，
  //      // error : free(): double free detected in tcache
  //      // todo 定义析构函数后，要记着定义拷贝构造和移动构造

  // 3. test push_back erase
  // for (int i = 0; i < 16; i++) {
  //   // printf("arr[%zd] = %d\n", i, arr[i]);
  //   printf("arr.push_back(%d)\n", i);
  //   arr.push_back(i);
  // }
  // for (size_t i = 0; i < 16; i++) {
  //   printf("arr[%zd] = %d\n", i, arr[i]);
  // }
  // arr.erase(arr.begin());
  // arr.erase(arr.begin() + 2, arr.begin() + 5);
  // for (size_t i = 0; i < arr.size(); i++) {
  //   printf("arr[%zd] = %d\n", i, arr[i]);
  // }

  // 4. test move
  // Vector<int> bar;
  // printf("std::move before\n");
  // printf("arr.size() = %zd\n", arr.size());
  // printf("bar.size() = %zd\n", bar.size());
  // bar = std::move(arr);  // arr 变为空
  // printf("std::move after\n");
  // printf("arr.size() = %zd\n", arr.size());
  // printf("bar.size() = %zd\n", bar.size());

  // 5. test  Vector{std::initializer_list<int> ilist}
  //   // 添加: Vector{std::initializer_list<int> ilist}
  //   arr = Vector({1, 2, 3, 4, 5});
  //   arr = {1, 2, 3};

  // 6. test  shrink_to_fit
  Vector<int> bar;
  bar.reserve(100);
  bar.resize(100);
  std::cout << "Capacity of a 100-element vector is " << bar.capacity() << '\n';
  bar.resize(50);
  std::cout << "Capacity after resize(50) is " << bar.capacity() << '\n';
  bar.shrink_to_fit();
  std::cout << "Capacity after shrink_to_fit() is" << bar.capacity() << '\n';
  bar.clear();
  std::cout << "Capacity after clear() is " << bar.capacity() << '\n';
  bar.shrink_to_fit();
  std::cout << "Capacity after shrink_to_fit() is " << bar.capacity() << '\n';

  // 7.  test assign
  // Vector<int> arr3;
  // auto print_list = [&]() {
  //   for (auto const& it : arr3) {
  //     std::cout << it << ' ';
  //   }
  //   std::cout << '\n';
  // };
  // arr3 = {1, 2, 3, 4, 5};
  // print_list();
  // arr3.assign(5, 9);
  // print_list();
  // const Vector<int> extra = {6, 7, 8, 9, 10};
  // arr3.assign(extra.begin(), extra.end());
  // print_list();

  // // 8. test insert  pop_back() arr.capacity arr.size() front back data
  // Vector<int> arr;
  // for (int i = 0; i < 16; i++) {
  //   printf("arr.push_back(%d)\n", i);
  //   arr.push_back(i);  // O(n)
  // }
  // arr.insert(arr.begin() + 3, {40, 41, 42});
  // arr.pop_back();
  // for (size_t i = 0; i < arr.size(); i++) {
  //   printf("arr[%zd] = %d\n", i, arr[i]);
  // }
  // std::cout << "arr.capacity = " << arr.capacity() << '\n';
  // std::cout << "arr.size = " << arr.size() << '\n';
  // std::cout << "arr.front() = " << arr.front() << '\n';
  // std::cout << "arr.back() = " << arr.back() << '\n';
  // std::cout << "arr.data() = " << arr.data() << '\n'
  //           << "*arr.data() = " << *arr.data() << '\n';

  return 0;
}