
#include <functional>
#include <iostream>
#include <new>
#include <utility>
namespace trivial {

template <class ReturnType, class... Args>
class FunctorHolderBase {
 public:
  virtual ~FunctorHolderBase() = default;
  virtual ReturnType operator()(Args&&... args) = 0;
};

template <class ReturnType, class Functor, class... Args>
class FuntorHolder final : public FunctorHolderBase<ReturnType, Args...> {
  Functor f{};

 public:
  ~FuntorHolder() override = default;
  FuntorHolder(Functor fun) : f(std::move(fun)){};
  ReturnType operator()(Args&&... args) override {
    return std::invoke(f, std::forward<Args>(args)...);
  }
};

template <class>
class function;

template <class ReturnType, class... Args>
class function<ReturnType(Args...)> {
  FunctorHolderBase<ReturnType, Args...>* functorBase{};

 public:
  template <class Functor>
  function(Functor fun)
      : functorBase(new FuntorHolder<ReturnType, Functor, Args...>(fun)) {}
  ~function() {
    if (functorBase) delete functorBase;
  }

  ReturnType operator()(Args&&... args) {
    return (*functorBase)(std::forward<Args>(args)...);
  }
};

}  // namespace trivial

void normal_fun(int i) { std::cout << i << "\n"; }
struct Foo {
  Foo(int number) : num(number) {}
  void print_add(int i) const { std::cout << num + i << '\n'; }
  int num;
};
#include <any>
int main() {
  trivial::function<void()> f1([]() { return; });
  f1();
  trivial::function<void(int)> f2 = normal_fun;
  f2(-9);
  trivial::function<void()> f3 = std::bind(normal_fun, 31337);
  f3();
  trivial::function<void(Foo&, int)> f4 = &Foo::print_add;
  Foo foo(314159);
  f4(foo, 1);
  std::function<int(Foo const&)> f5 = &Foo::num;
  std::cout << "num: " << f5(foo) << '\n';
}
