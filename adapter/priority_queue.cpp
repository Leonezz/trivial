#include <functional>
#include <utility>
#include <vector>

namespace trivial {
template <typename Cont, typename Cmp>
void heapify(Cont& arr, size_t l, size_t r, Cmp cmp) {
  using std::swap;
  auto parent{l};
  auto child{2 * parent + 1};
  while (child < r) {
    if (child + 1 < r && cmp(arr[child], arr[child + 1])) ++child;
    if (cmp(arr[parent], arr[child]))
      swap(arr[parent], arr[child]);
    else
      return;
    parent = child;
    child = 2 * parent + 1;
  }
}

template <typename T, typename Cont = std::vector<T>,
          typename Cmp = std::less<T>>
class priority_queue {
  Cont cont{};
  Cmp cmp{};

 private:
  void make_heap() {
    const auto size{this->size()};
    for (int i = size / 2 - 1; i > -1; --i) heapify(cont, i, size, cmp);
  }
  void push_heap() {
    using std::swap;
    int size = cont.size();
    int child{size - 1};
    int parent{(child - 1) / 2};
    while (child > 0) {
      if (cmp(cont[parent], cont[child]))
        swap(cont[parent], cont[child]);
      else
        return;
      child = parent;
      parent = (child - 1) / 2;
    }
  }
  void pop_heap() { heapify(cont, 0, size(), cmp); }

 public:
  priority_queue() = default;
  ~priority_queue() = default;
  priority_queue(const Cont& c, Cmp cp) : cont(c), cmp(std::move(cp)) {
    make_heap();
  }
  explicit priority_queue(Cmp cp) : cmp(std::move(cp)){};
  priority_queue(const priority_queue& other)
      : cont(other.cont), cmp(other.cmp) {}
  priority_queue(priority_queue&& other) noexcept {
    priority_queue().swap(other);
  }

  priority_queue& operator=(priority_queue other) noexcept {
    swap(other);
    return *this;
  }

  void swap(priority_queue& other) noexcept {
    using std::swap;
    swap(other.cont, cont);
    swap(other.cmp, cmp);
  }

  bool empty() const noexcept { return cont.empty(); }
  size_t size() const noexcept { return cont.size(); }
  T& front() { return cont.front(); };
  const T& front() const { return const_cast<priority_queue*>(this)->front(); }
  void push(const T& t) {
    cont.push_back(t);
    push_heap();
  }
  void pop() {
    using std::swap;
    swap(cont.front(), cont.back());
    cont.pop_back();
    pop_heap();
  }
};
template class priority_queue<int, std::vector<int>, std::less<int>>;
}  // namespace trivial
