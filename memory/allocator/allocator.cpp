#include <utility>
namespace trivial {
class trivial_memalloc {
 public:
  using size_type = std::size_t;
  using pointer = void*;
  static void* _allocate_impl(size_type size) {
    if (size == 0) [[unlikely]]
      return nullptr;
    return ::operator new(size);
  }
  static void _deallocate_impl(pointer p) noexcept {
    if (p == nullptr) [[unlikely]]
      return;
    ::operator delete(p);
  }
};

template <class T>
class trivial_constructor {
 public:
  using value_type = std::decay_t<T>;
  using pointer = value_type*;
  using size_type = std::size_t;
  using nothrow_destructible = std::is_nothrow_destructible<value_type>;
  static void _construct_impl(pointer, std::true_type) noexcept {}
  static void _construct_impl(pointer p, std::false_type) noexcept(
      std::is_nothrow_default_constructible_v<value_type>) {
    ::new (static_cast<void*>(p)) value_type();
  }
  template <class... Args>
  static void _construct_impl(pointer p, Args... args) noexcept(
      std::is_nothrow_constructible_v<value_type, Args...>) {
    ::new (static_cast<void*>(p)) value_type(std::forward<Args>(args)...);
  }
  static void _destroy_one_impl(pointer p) {
    using is_trivially_destructible =
        std::is_trivially_destructible<value_type>;
    _destroy_one_impl_aux(p, is_trivially_destructible{});
  }

  static void _destroy_one_impl_aux(pointer, std::true_type) noexcept {}
  static void _destroy_one_impl_aux(pointer p, std::false_type) noexcept(
      nothrow_destructible{}) {
    if (p == nullptr) [[unlikely]]
      return;
    p->~value_type();
  }

  static void _destroy_range_impl(pointer p, size_type cnt) noexcept(
      nothrow_destructible{}) {
    if (p == nullptr) [[unlikely]]
      return;
    for (auto i{0}; i < cnt; ++i) _destroy_one_impl(p + i);
  }
};
template <class T, class Construcor = trivial_constructor<T>,
          class Alloc = trivial_memalloc>
class allocator {
 public:
  using value_type = std::decay_t<T>;
  using pointer = value_type*;
  using reference = value_type&;
  using const_point = const pointer;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

 private:
  using nothrow_destructible = typename Construcor::nothrow_destructible;

 public:
  static pointer allocate() {
    return static_cast<pointer>(Alloc::_allocate_impl(sizeof(value_type)));
  }
  static pointer allocate(size_type cnt) {
    return static_cast<pointer>(
        Alloc::_allocate_impl(cnt * sizeof(value_type)));
  }
  static void deallocate(pointer p) noexcept { Alloc::_deallocate_impl(p); }
  static void deallocate(pointer p, size_type) noexcept { deallocate(p); }
  static void construct(pointer p) noexcept(
      std::is_nothrow_default_constructible_v<value_type>) {
    Construcor::_construct_impl(p);
  }
  template <class... Args>
  static void construct(pointer p, Args&&... args) noexcept(
      std::is_nothrow_constructible_v<value_type, Args...>) {
    Construcor::_construct_impl(p, std::forward<Args>(args)...);
  }

  static void destroy(pointer p) noexcept(nothrow_destructible{}) {
    Construcor::_destroy_one_impl(p);
  }
  static void destroy(pointer begin,
                      size_type cnt) noexcept(nothrow_destructible{}) {
    Construcor::_destroy_range_impl(begin, cnt);
  }
};

}  // namespace trivial

#include <vector>
int main() {
  {
    std::vector<int, trivial::allocator<int>> vec;
    vec.push_back(1);
    for (int i = 0; i < 1000; ++i) vec.push_back(i);
  }
}