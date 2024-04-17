#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

std::vector<std::string> processCards(const std::vector<std::string>& cards) {
  std::stack<std::string> st;
  std::vector<std::string> processed;

  for (const auto& card : cards) {
    if (st.size() < 2) {
      st.push(card);
    } else {
      if (card == st.top()) {
        std::string topCard = st.top();
        st.pop();
        if (topCard == st.top()) {
          while (!st.empty() && st.top() == topCard) {
            st.pop();
          }
          if (!st.empty() && st.top() == card) {
            continue;
          }
        } else {
          st.push(topCard);
          st.push(card);
        }
      } else {
        st.push(card);
      }
    }
  }

  // Transfer the stack to the vector in the right order.
  while (!st.empty()) {
    processed.push_back(st.top());
    st.pop();
  }

  std::reverse(processed.begin(), processed.end());
  return processed;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::string> cards(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> cards[i];
  }

  std::vector<std::string> current = cards;
  std::vector<std::string> next = processCards(current);

  while (next.size() != current.size()) {
    current = next;
    next = processCards(current);
  }

  if (current.empty()) {
    std::cout << "0" << std::endl;
  } else {
    for (size_t i = 0; i < current.size(); ++i) {
      std::cout << current[i];
      if (i < current.size() - 1) {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }

  return 0;
}