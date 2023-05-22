#include <utility>
namespace trivial {
template <class T>
class unique_ptr {
  T* ptr{};

 public:
  unique_ptr() = default;
  ~unique_ptr() {
    if (ptr) delete ptr;
  }
  explicit unique_ptr(T* p) : ptr(p) {}
  unique_ptr(const unique_ptr&) = delete;
  unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
    unique_ptr().swap(other);
  }

  unique_ptr& operator=(const unique_ptr& other) = delete;
  unique_ptr& operator=(unique_ptr&& other) {
    other.swap(*this);
    return *this;
  }

  T* get() const noexcept { return ptr; }
  T* operator->() const noexcept { return get(); }
  T& operator*() const { return *get(); }

  T* release() {
    T* p{};
    std::swap(p, ptr);
    return p;
  }

  explicit operator bool() { return get(); }
  void swap(unique_ptr& other) noexcept {
    using std::swap;
    swap(other.ptr, ptr);
  }
};
};  // namespace trivial
