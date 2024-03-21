
#include <compare>
#include <concepts>
#include <cstddef>
#include <forward_list>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>

#ifdef NDEBUG
#define DEBUG_INIT_DEADBEAF(T)
#else
#define DEBUG_INIT_DEADBEAF(T) \
  { (T *)0xdeadbeaf }
#endif

// 全局
template <class T>
struct ListBaseNode {
  ListBaseNode *m_next DEBUG_INIT_DEADBEAF(ListBaseNode);
  ListBaseNode *m_prev DEBUG_INIT_DEADBEAF(ListBaseNode);

  T &value();
  T const &value() const;
};
template <class T>
struct ListValueNode : public ListBaseNode<T> {
  union {
    T m_value;
  };
};

template <class T>
inline T &ListBaseNode<T>::value() {
  return static_cast<ListValueNode<T> &>(*this).m_value;
}

template <class T>
inline T const &ListBaseNode<T>::value() const {
  return static_cast<ListValueNode<T> const &>(*this).m_value;
}

template <class T, class Alloc = std::allocator<T>>
struct List {
  using value_type = T;
  using allocator_type = Alloc;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = T *;
  using const_pointer = T const *;
  using reference = T &;
  using const_reference = T const &;

 private:
  using ListNode = ListBaseNode<T>;
  // todo

  using AllocNode =
      std::allocator_traits<Alloc>::template rebind_alloc<ListValueNode<T>>;
  // 方案1.
  // struct PrivateConstruct {
  //   // 防止() 调用
  //   explicit PrivateConstruct() = default;
  // };

  // ListNode *m_head;
  ListNode m_dummy;  // 伪节点
  size_t m_size;
  [[no_unique_address]] Alloc m_alloc;

  ListNode *newNode() {
    return AllocNode{m_alloc}.allocate(1);
    //  new ListValueNode<T>;
  }

  void deleteNode(ListNode *node) noexcept {
    AllocNode{m_alloc}.deallocate(static_cast<ListValueNode<T> *>(node), 1);
  }

 public:
  List() noexcept {
    m_size = 0;
    m_dummy.m_prev = m_dummy.m_next = &m_dummy;
  }

  explicit List(Alloc const &alloc) noexcept : m_size(0), m_alloc(alloc) {
    m_dummy.m_prev = m_dummy.m_next = &m_dummy;
  }

  explicit List(size_t n, Alloc const &alloc = Alloc()) : m_alloc(alloc) {
    _uninit_assign(n);
    // ListNode *prev = &m_dummy;
    // while (n > 0) {
    //   ListNode *node = newNode();
    //   prev->next = node;
    //   node->m_prev = prev;
    //   std::construct_at(&node->value(), T());  // int() ---> 等价于 0
    //   prev = node;
    //   --n;
    // }

    // // last->m_next = nullptr;  // 双向链表
    // m_dummy.m_prev = prev;
    // prev->next = &m_dummy;
    // m_size = n;
  }

  List(size_t n, T const &value, Alloc const &alloc = Alloc())
      : m_alloc(alloc) {
    _uninit_assign(n, value);

    // ListNode *prev = &m_dummy;
    // while (n > 0) {
    //   ListNode *node = newNode();
    //   prev->next = node;
    //   node->m_prev = prev;
    //   // node->value() = value;
    //   std::construct_at(&node->value(), value);
    //   prev = node;
    //   --n;
    // }

    // // last->m_next = nullptr;  // 双向链表
    // m_dummy.m_prev = prev;
    // prev->next = &m_dummy;
    // m_size = n;
  }
  ~List() noexcept {
    // 循环链表 如何遍历
    // ListNode *curr = m_dummy.m_next;
    // while (curr != &m_dummy) {
    //   // // T 析构两次的问题
    //   // curr->value().~T();
    //   std::destroy_at(&curr->value());
    //   auto next = curr->m_next;
    //   deleteNode(curr);
    //   curr = next;
    // }
    clear();
  }

  void clear() noexcept {
    // 循环链表 如何遍历
    ListNode *curr = m_dummy.m_next;
    while (curr != &m_dummy) {
      // // T 析构两次的问题
      // curr->value().~T();
      std::destroy_at(&curr->value());
      auto next = curr->m_next;
      deleteNode(curr);
      curr = next;
    }
    // 继续使用
    m_dummy.m_prev = m_dummy.m_next = &m_dummy;
    m_size = 0;
  }

  // input_iterator = *it it++ ++it it!=it it==it
  // output_iterator = *it=val it++ ++it it!=it it==it
  // forward_iterator = *it *it=val it++ ++it it!=it it==it
  // bidirectional_iterator = *it *it=val it++ ++it it-- --it it!=it it==it
  // random_access_iterator = *it *it=val it[n] it[n]=val it++ ++it it-- --it
  // it+=n it-=n it+n it-n it!=it it==it

  template <std::input_iterator InputIt>
  List(InputIt first, InputIt last, Alloc const &alloc = Alloc()) {
    _uninit_assign(first, last);
  }

  List(std::initializer_list<T> ilist, Alloc const &alloc = Alloc())
      : List(ilist.begin(), ilist.end(), alloc) {}

  // 移动构造
  List(List &&that) : m_alloc(std::move(that.alloc)) {
    _uninit_move_assign(std::move(that));
  }

  List(List &&that, Alloc const &alloc) : m_alloc(alloc) {
    _uninit_move_assign(std::move(that));
  }

  // 移动赋值
  List &operator=(List &&that) {
    m_alloc = std::move(that.m_alloc);
    clear();
    _uninit_move_assign(std::move(that));
  }

  List(List const &that) : m_alloc(that.m_alloc) {
    _uninit_assign(that.begin(), that.end());
  }

  List(List const &that, Alloc const &alloc) : m_alloc(alloc) {
    _uninit_assign(that.begin(), that.end());
  }

  List &operator=(List &that) { assign(that.begin(), that.end()); }

  List &operator=(std::initializer_list<T> ilist) { assign(ilist); }

 private:
  // why?
  void _uninit_move_assign(List &&that) {
    auto prev = that.m_dummy.m_prev;
    auto next = that.m_dummy.m_next;
    prev->m_next = &m_dummy;
    next->m_prev = &m_dummy;
    m_dummy = that.m_dummy;
    that.m_dummy.m_prev = that.m_dummy.m_next = &that.m_dummy;
    m_size = that.m_size;
    that.m_size = 0;
  }
  template <std::input_iterator InputIt>
  void _uninit_assign(InputIt first, InputIt last) {
    // clear(); // bug
    m_size = 0;
    ListNode *prev = &m_dummy;
    while (first != last) {
      ListNode *node = newNode();
      prev->m_next = node;
      node->m_prev = prev;
      std::construct_at(&node->value(), *first);
      prev = node;
      ++first;
      ++m_size;
    }
    // last->m_next = nullptr;  // 双向链表
    m_dummy.m_prev = prev;
    prev->m_next = &m_dummy;
  }

  void _uninit_assign(size_t n, T const &val) {
    ListNode *prev = &m_dummy;
    while (n) {
      ListNode *node = newNode();
      prev->m_next = node;
      node->m_prev = prev;
      std::construct_at(&node->value(), val);
      prev = node;
      --n;
    }
    m_dummy.m_prev = prev;
    prev->m_next = &m_dummy;
    m_size = n;
  }

  void _uninit_assign(size_t n) {
    ListNode *prev = &m_dummy;
    while (n) {
      ListNode *node = newNode();
      prev->m_next = node;
      node->m_prev = prev;
      std::construct_at(&node->value());
      prev = node;
      --n;
    }
    m_dummy.m_prev = prev;
    prev->m_next = &m_dummy;
    m_size = n;
  }

 public:
  size_t size() const noexcept { return m_size; }

  static constexpr size_t max_size() noexcept {
    return std::numeric_limits<size_t>::max();
  }

  template <std::input_iterator InputIt>
  void assign(InputIt first, InputIt last) {
    clear();
    _uninit_assign(first, last);
  }

  void assign(std::initializer_list<T> ilist) {
    clear();
    _uninit_assign(ilist.begin(), ilist.end());
  }

  void assign(size_t n, T const &val) {
    clear();
    _uninit_assign(n, val);
  }

  void push_back(T const &value) { emplace_back(value); }
  void push_back(T &&value) { emplace_back(std::move(value)); }

  template <class... Args>
  T &emplace_back(Args &&...args) {
    ListNode *node = newNode();
    node->m_prev = m_dummy.m_prev;
    node->m_next = &m_dummy;  // 最后一个节点
    std::construct_at(&node->value(), std::forward<Args>(args)...);
    m_dummy.m_prev = node;
    ++m_size;
    return node->value();
  }

  void push_front(T const &value) { emplace_front(value); }
  void push_front(T &&value) { emplace_front(std::move(value)); }

  // todo
  template <class... Args>
  T &emplace_front(Args &&...args) {
    ListNode *node = newNode();
    node->m_next = m_dummy.m_next;
    node->m_prev = &m_dummy;  // 最后一个节点 don't repeat yourself(DRY)
    std::construct_at(&node->value(), std::forward<Args>(args)...);
    m_dummy.m_next = node;
    --m_size;
    return node->value();
  }

  T &front() noexcept {
    return m_dummy.m_next->value();  //
  }

  T &back() noexcept { return m_dummy.m_prev->value(); }

  T const &front() const noexcept {
    return m_dummy.m_next->value();  //
  }

  T const &back() const noexcept { return m_dummy.m_prev->value(); }

  bool empty() noexcept { return m_dummy.m_prev == m_dummy.m_next; }

  // template <class Visitor>
  // void foreach (Visitor visit) {
  //   // 循环链表 如何遍历
  //   ListNode *curr = m_dummy.m_next;
  //   while (curr != &m_dummy) {
  //     visit(curr->value());
  //     curr = curr->m_next;
  //   }
  // }

  struct iterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    // PrivateConstruct 是私有的， 所以你无法构造出迭代器
    // List<int>::const_iterator(PrivateConstruct{}, nullptr);
    // PrivateConstruct 是私有的，所以你拿不到 ，只有begin 和 end才能拿到
   private:
    ListNode *m_curr;
    friend List;
    // 方案1.
    //  explicit iterator(PrivateConstruct, ListNode *curr) : m_curr(curr) {}
    // 方案2.
    explicit iterator(ListNode *curr) noexcept : m_curr(curr) {}

   public:
    iterator() = default;  // std::default_initialize

    iterator &operator++() noexcept {  // 默认是前置++iterators
      m_curr = m_curr->m_next;
      return *this;
    }

    iterator operator++(int) noexcept {  // 后置++
      auto tmp = *this;
      ++*this;
      return tmp;
    }

    iterator &operator--() noexcept {  // 默认是前置--iterators
      m_curr = m_curr->m_prev;
      return *this;
    }

    iterator operator--(int) noexcept {  // 后置++
      auto tmp = *this;
      ++*this;
      return tmp;
    }
    T &operator*() const noexcept { return m_curr->value(); }

    bool operator!=(iterator const &that) const noexcept {
      return m_curr != that.m_curr;
    }

    bool operator==(iterator const &that) const noexcept {
      return !(*this != that);
    }
  };

  struct const_iterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T *;
    using reference = T &;

   private:
    ListNode const *m_curr;
    friend List;
    // 方案1.
    // explicit const_iterator(PrivateConstruct, ListNode const *curr)
    //     : m_curr(curr) {}
    // 方案2.
    explicit const_iterator(ListNode const *curr) noexcept : m_curr(curr) {}

   public:
    const_iterator() = default;

    explicit operator iterator() noexcept {
      return iterator{const_cast<ListNode *>(m_curr)};
    }

    const_iterator(iterator that) noexcept : m_curr(that.m_curr) {}

    const_iterator &operator++() noexcept {  // 默认是前置++iterators
      m_curr = m_curr->m_next;
      return *this;
    }

    const_iterator operator++(int) noexcept {  // 后置++
      auto tmp = *this;
      ++*this;
      return tmp;
    }

    const_iterator &operator--() noexcept {  // 默认是前置--iterators
      m_curr = m_curr->m_prev;
      return *this;
    }

    const_iterator operator--(int) noexcept {  // 后置--
      auto tmp = *this;
      --*this;
      return tmp;
    }
    T const &operator*() const { return m_curr->value(); }

    bool operator!=(const_iterator const &that) const noexcept {
      return m_curr != that.m_curr;
    }

    bool operator==(const_iterator const &that) const noexcept {
      return !(*this != that);
    }
  };
  // 方案1.
  // iterator begin() { return iterator{PrivateConstruct{}, m_dummy.m_next}; }

  // iterator end() { return iterator{PrivateConstruct{}, &m_dummy}; }

  // const_iterator begin() const {
  //   return const_iterator{PrivateConstruct{}, m_dummy.m_next};
  // }

  // const_iterator end() const {
  //   return const_iterator{PrivateConstruct{}, &m_dummy};
  // }

  //-----------方案2-----------------------------------------------------
  iterator begin() noexcept { return iterator{m_dummy.m_next}; }

  iterator end() noexcept { return iterator{&m_dummy}; }

  const_iterator cbegin() const noexcept {
    return const_iterator{m_dummy.m_next};
  }

  const_iterator cend() const noexcept { return const_iterator{&m_dummy}; }

  const_iterator begin() const noexcept { return cbegin(); }

  const_iterator end() const noexcept { return cend(); }

  using reverse_iterator = std::reverse_iterator<iterator>;
  using reverse_const_iterator = std::reverse_iterator<const_iterator>;

  reverse_iterator rbegin() noexcept {
    return std::make_reverse_iterator(end());
  }

  reverse_iterator rend() noexcept {
    return std::make_reverse_iterator(begin());
  }

  reverse_const_iterator crbegin() const noexcept {
    return std::make_reverse_iterator(cend());
  }

  reverse_const_iterator crend() const noexcept {
    return std::make_reverse_iterator(cbegin());
  }

  reverse_const_iterator rbegin() const noexcept { return crbegin(); }

  reverse_const_iterator rend() const noexcept { return crend(); }

  // 移到 const_iterator 后面 ，不然显示没有迭代器
  iterator erase(const_iterator pos) {
    // 去掉const
    ListNode *node = const_cast<ListNode *>(pos.m_curr);
    auto next = node->m_next;
    auto prev = node->m_prev;
    prev->m_next = next;
    next->m_prev = prev;
    std::destroy_at(&node->value());
    deleteNode(node);
    --m_size;
    // 删除完后，指向下一个
    return iterator{next};
  }

  iterator erase(const_iterator first, const_iterator last) {
    while (first != last) {
      // auto node = first.m_curr;
      // auto next = node->m_next;
      // auto prev = node->m_prev;
      // prev->m_next = next;
      // next->m_prev = prev;
      // std::destroy_at(&node->value());
      // deleteNode(node);
      // ++first;
      first = erase(first);
    }
    return iterator{first};
  }

  void pop_front() noexcept { erase(begin()); }
  // todo std::prev
  void pop_back() noexcept { std::prev(end()); }

  size_t remove(T const &value) {
    auto first = begin();
    auto last = end();
    size_t count = 0;
    while (first != last) {
      if (*first == value) {
        first = erase(first);
        ++count;
      } else {
        ++first;
      }
    }
    return count;
  }

  // todo ?
  // template <std::invocable<T &> Pred>
  template <class Pred>
  size_t remove_if(Pred &&pred) noexcept {
    auto first = begin();
    auto last = end();
    size_t count = 0;
    while (first != last) {
      if (pred(*first)) {
        first = erase(first);
        ++count;
      } else {
        ++first;
      }
    }
    return count;
  }

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    ListNode *curr = newNode();
    ListNode *next = const_cast<ListNode *>(pos.m_curr);
    ListNode *prev = next->m_prev;
    curr->m_prev = prev;
    prev->m_next = curr;
    curr->m_next = next;
    next->m_prev = curr;
    std::construct_at(&curr->value(), std::forward<Args>(args)...);
    ++m_size;
    return iterator{curr};
  }

  iterator insert(const_iterator pos, const T &value) { emplace(pos, value); }
  iterator insert(const_iterator pos, T &&value) {
    emplace(pos, std::move(value));
  }

  template <std::input_iterator InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    auto orig = pos;
    bool had_orig = false;
    while (first != last) {
      pos = emplace(pos, *first);
      if (!had_orig) {
        had_orig = true;
        orig = pos;
      }
      ++pos;
      ++first;
    }
    return iterator(orig);
  }

  iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
    return insert(pos, ilist.begin(), ilist.end());
  }

  // todo
  void splice(const_iterator pos, List &&that) {
    insert(pos, std::make_move_iterator(that.begin()),
           std::make_move_iterator(that.end()));
  }

  Alloc get_allocator() const { return m_alloc; }

  bool operator==(List const &that) noexcept {
    return std::equal(begin(), end(), that.begin(), that.end());
  }

  // auto operator<= > (List const &that) noexcept {
  //   return std::lexicographical_compare_three_way(begin(), end(),
  //   that.begin(),
  //                                                 that.end());
  // }
};

// int main() {
//   List<int> arr{1, 2, 3, 4, 5, 6};

//   size_t i = 0;
//   // arr.foreach ([&](int &val) {
//   //   printf("arr[%zd] = %d\n", i, val);
//   //   ++i;
//   // });
//   // for (auto it = arr.begin(); it != arr.end(); ++it) {
//   //   int &val = *it;
//   //   printf("arr[%zd] = %d\n", i, val);
//   //   ++i;
//   // }
//   // for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
//   //   int &val = *it;
//   //   printf("arr[%zd] = %d\n", i, val);
//   //   ++i;
//   // }
//   for (auto it = arr.cbegin(); it != arr.cend(); ++it) {
//     int const &val = *it;
//     printf("arr[%zd] = %d\n", i, val);
//     ++i;
//   }
//   // arr.erase(arr.cbegin());
//   // todo next advance
//   arr.erase(arr.cbegin(), std::next(arr.cbegin(), 2));
//   for (auto it = arr.crbegin(); it != arr.crend(); ++it) {
//     int const &val = *it;
//     --i;
//     printf("arr[%zd] = %d\n", i, val);
//   }
//   // List<int>::const_iterator(PrivateConstruct{}, nullptr);
//   return 0;
// }