#include <assert.h>
#include <atomic>
#include <utility>
namespace trivial {
using std::atomic;
using ull = unsigned long long;
class RefCount {
  atomic<ull> use_cnt{1};

 public:
  RefCount() = default;
  ~RefCount() = default;
  void increment() { this->use_cnt.fetch_add(1, std::memory_order_release); }
  void decrement() { this->use_cnt.fetch_sub(1, std::memory_order_release); }
  ull get() { return this->use_cnt.load(std::memory_order_acquire); }
};

template <typename T>
class shared_ptr {
  RefCount* _ref_cnt{};
  T* _ptr{};
  void release() {
    if (!_ref_cnt) return;
    _ref_cnt->decrement();
    if (_ref_cnt->get() == 0) {
      delete _ref_cnt;
      if (_ptr) delete _ptr;
    }
  }
  void use() {
    assert(_ref_cnt);
    _ref_cnt->increment();
  }

 public:
  shared_ptr() = default;
  ~shared_ptr() { release(); }
  explicit shared_ptr(T* ptr) try : _ptr(ptr), _ref_cnt(new RefCount) {
  } catch (...) {
    delete ptr;
    throw;
  }
  shared_ptr(const shared_ptr& other)
      : _ptr(other._ptr), _ref_cnt(other._ref_cnt) {
    use();
  }
  shared_ptr(shared_ptr&& other) : _ptr(other._ptr), _ref_cnt(other._ref_cnt) {
    shared_ptr().swap(other);
  }
  shared_ptr& operator=(shared_ptr other) {
    release();
    other.swap(*this);
    return *this;
  }
  void swap(shared_ptr& other) noexcept {
    using std::swap;
    swap(other._ptr, _ptr);
    swap(other._ref_cnt, _ref_cnt);
  }
  T* operator->() const noexcept { return _ptr; };
  T& operator*() const { return *_ptr; };
  explicit operator bool() const noexcept { return _ptr; }
  ull use_cnt() { return _ref_cnt->get(); }
  void reset(T* ptr = {}) {
    release();
    _ptr = ptr;
    if (!_ptr) return;
    try {
      _ref_cnt = new RefCount;
    } catch (...) {
      delete ptr;
    }
  }
};
}  // namespace trivial
