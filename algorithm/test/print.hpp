#include <iostream>
#include <string>
template <typename Cont>
void print(const Cont& c, const std::string& sp = " ") {
  for (int i = 0; i < c.size() - 1; ++i) std::cout << c[i] << sp;
  endl(std::cout << c.back());
}
