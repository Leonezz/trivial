#include <iostream>
#include <utility>
namespace trivial {

struct StorageBase {
  void* objPtr{};
};
template <class T>
struct Storage : StorageBase {
  Storage(const T& t) { objPtr = new T(t); }
  ~Storage() {
    if (objPtr) delete (T*)objPtr;
  }
};

class any {
  StorageBase* storagePtr{};

 public:
  template <class T>
  any(T t) : storagePtr(new Storage<T>(std::forward<T>(t))) {}
  ~any() {
    if (storagePtr) delete storagePtr;
  }
  bool has_value() const noexcept { return storagePtr != nullptr; }
  template <class T>
  T any_cast() {
    return T(*(static_cast<T*>(storagePtr->objPtr)));
  }
};
template <class T>
T any_cast(any& a) {
  return a.any_cast<T>();
}
}  // namespace trivial
#include <any>
int main() {
  trivial::any a = 1.0;
  std::cout << trivial::any_cast<int>(a) << "\n";
  std::cout << trivial::any_cast<size_t>(a) << "\n";
  std::cout << trivial::any_cast<double>(a) << "\n";
  std::cout << trivial::any_cast<float>(a) << "\n";
}