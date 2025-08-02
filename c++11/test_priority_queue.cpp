#include <concepts>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <ranges>
#include <string_view>
#include <vector>

template <typename T>
void print(std::string_view name, T const& q) {
  std::cout << name << ": \t";
  for (auto const& n : q) std::cout << n << ' ';
  std::cout << '\n';
}

template <typename Adaptor>
requires(std::ranges::input_range<typename Adaptor::container_type>) void print(
    std::string_view name, const Adaptor& adaptor) {
  struct Printer : Adaptor  // to access protected Adaptor::Container c;
  {
    void print(std::string_view name) const { ::print(name, this->c); }
  };

  static_cast<Printer const&>(adaptor).print(name);
}

/**
priority_queue<Type, Container, Functional>;

Type是要存放的数据类型

Container是实现底层堆的容器，必须是数组实现的容器，如vector、deque

Functional是比较方式/比较函数/优先级

priority_queue<Type>;

此时默认的容器是vector，默认的比较方式是大顶堆less<type>

// 对于基础类型 默认是大顶堆 降序队列
priority_queue<int> a;
// 等同于 priority_queue<int, vector<int>, less<int> > a;

priority_queue<int, vector<int>, greater<int>> c;  // 这样就是小顶堆,升序队列
priority_queue<string> b;
*/

int main() {
  std::queue<int> que;
  std::deque<int> c;
  std::vector<int> vec;
  const auto data = {9, 41, 10, 73, 66, 63, 84, 96};
  // print("data", data);

  std::priority_queue<int, std::vector<int>, std::greater<int>>
      q1;  // Max priority queue
  for (int n : data) q1.push(n);
  q1.push(34);

  print("q1", q1);

  // // Min priority queue
  // // std::greater<int> makes the max priority queue act as a min priority
  // queue std::priority_queue<int, std::vector<int>, std::greater<int>> minq1(
  //     data.begin(), data.end());

  // print("minq1", minq1);

  // // Second way to define a min priority queue
  // std::priority_queue maxq2(data.begin(), data.end(), std::less<int>());

  // print("minq2", maxq2);

  // // Using a custom function object to compare elements.
  // struct {
  //   bool operator()(const int l, const int r) const { return l > r; }
  // } customLess;
  // std::priority_queue minq3(data.begin(), data.end(), customLess);

  // print("minq3", minq3);

  // // Using lambda to compare elements.
  // auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
  // std::priority_queue<int, std::vector<int>, decltype(cmp)> q5(cmp);

  // for (int n : data) q5.push(n);

  // print("q5", q5);

  dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
  dp[i][(j + nums[i - 1]) % x] =
      min(dp[i][(j + nums[i - 1]) % x], dp[i - 1][j]);
  dp[i][(j + nums[i - 1] + 1) % x] =
  min(dp[i][(j + nums[i - 1] + 1) % x], dp[i - 1][j] + 1);
}
