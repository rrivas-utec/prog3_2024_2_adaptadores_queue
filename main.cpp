#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <deque>
#include <list>
#include <type_traits>

namespace utec {
  template <
      typename T,
      template<typename...>typename ContainerType = std::deque,
      typename std::enable_if<!std::is_same_v<ContainerType<T>, std::vector<T>>, bool>::type x = true
      >
  class Cola {
    ContainerType<T> cnt;
  public:
    Cola() = default;
    explicit Cola(const ContainerType<T>& cnt): cnt(cnt) {}
    explicit Cola(ContainerType<T>&& cnt): cnt(std::move(cnt)) {}
    template<typename Iterator>
    Cola(Iterator start, Iterator stop): cnt(start, stop){}
    
    using value_type = T;
   
    size_t size() { return cnt.size(); }
    void push(T value) { cnt.push_back(value); }
    template<typename...Args>
    void emplace(Args ...args) { cnt.emplace_back(args...); }
    void pop() { cnt.pop_front(); }
    T front() { return cnt.front(); }
    T back() { return cnt.back(); }
    bool empty() { return cnt.size() == 0; }
  };
}

template <typename AdapterType, typename T = typename AdapterType::value_type>
void print_adapter(AdapterType adapter) {
//  using T = typename AdapterType::value_type;
  while (!adapter.empty()) {
    if constexpr (std::is_same_v<std::queue<T>, AdapterType> == true || std::is_same_v<utec::Cola<T>, AdapterType> == true) {
      std::cout << adapter.front() << " ";
    }
    else {
      std::cout << adapter.top() << " ";
    }
    adapter.pop();
  }
  std::cout << std::endl;
}

void ejemplo_1_queue () {
  std::deque d1 = {1, 2, 3, 4, 5};
  std::queue<int> q1(d1);
  print_adapter(q1);

  std::vector v1 = {1, 2, 3, 4, 5};
  std::queue<int, std::vector<int>> q2(v1);
  std::cout << q2.front();
}
template <typename AdapterType, typename UnaryFunction>
void foreach_adapter(AdapterType adapter, UnaryFunction func) {
  using T = typename AdapterType::value_type;
  while (!adapter.empty()) {
    if constexpr (std::is_same_v<std::queue<T>, AdapterType> == true) {
      func(adapter.front());
    }
    else {
      func(adapter.top());
    }
    adapter.pop();
  }
  std::cout << std::endl;
}

void ejemplo_2_queue () {
  std::deque d3 = {1, 2, 3, 4, 5, 7, 8, 9, 10};
  std::queue<int> q3(d3);
  auto total = 0;
  foreach_adapter(q3, [&total](auto item) {
    total += item;
  });
  std::cout << total << std::endl;
}

void ejemplo_3_queue () {
  std::queue<int> q1;
  q1.push(10);
  std::cout << q1.front() << ", " << q1.back() << std::endl;
  q1.push(20);
  std::cout << q1.front() << ", " << q1.back() << std::endl;
  q1.push(30);
  std::cout << q1.front() << ", " << q1.back() << std::endl;
  q1.pop();
  std::cout << q1.front() << ", " << q1.back() << std::endl;
}

template <typename T, template<typename...> typename ContainerType = std::basic_string>
ContainerType<T> processed_by_queue(const ContainerType<T>& cnt, T push_indicator) {
  // Variables iniciales
  std::queue<T> q;
  ContainerType<T> result;
  // Recorrer el contenedor de entrada
  for (const auto& item: cnt) {
    if (item == push_indicator) {
      if (q.empty()) break;
      result.push_back(q.front());
      q.pop();
    }
    else {
      q.push(item);
    }
  }
  return result;
}
void ejemplo_4_queue() {
  std::string text = "EAS*Y*QUE***ST***IO*N***";
  auto result1 = processed_by_queue(text, '*');
  for (const auto& item: result1)
    std::cout << item << " ";
  std::cout << std::endl;
  
  std::vector nums = {1, 2, 3, 0, 0, 4, 0, 0, 5, 0, 0};
  auto result2 = processed_by_queue(nums, 0);
  for (const auto& item: result2)
    std::cout << item << " ";
  std::cout << std::endl;
}

void ejemplo_5_queue() {
  utec::Cola<int> c1;
  c1.push(10);
  c1.emplace(20);
  c1.emplace(30);
  c1.emplace(40);
  print_adapter(c1);
  utec::Cola<int, std::deque> c2;
}

int main() {
//  ejemplo_1_queue();
//  ejemplo_2_queue();
//  ejemplo_3_queue();
//  ejemplo_4_queue();
  ejemplo_5_queue();
  return 0;
}
