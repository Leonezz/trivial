#include <iostream>

#include "../string.cpp"

int main() {
  trivial::string s{""};
  std::cout << "Empty string: " << s.c_str() << std::endl;
  std::cout << s.size() << " " << s.empty() << std::endl;
  trivial::string h{"hello world"};
  std::cout << h.c_str() << " " << h.size() << " " << h.empty() << std::endl;
  trivial::string hc(h);
  std::cout << hc.c_str() << " " << hc.size() << " " << hc.empty() << std::endl;
  trivial::string hh{"Greetings"};
  std::cout << hh.c_str() << " " << hh.size() << " " << hh.empty() << std::endl;
  hc = hh;
  std::cout << hc.c_str() << " " << hc.size() << " " << hc.empty() << std::endl;
  hc = std::move(trivial::string("move str"));
  std::cout << hc.c_str() << " " << hc.size() << " " << hc.empty() << std::endl;
}