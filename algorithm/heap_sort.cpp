#include <functional>
#include <utility>
#include <vector>

namespace trivial {
template <typename Cont, typename Cmp>
void heapify(Cont& arr, size_t l, size_t r, Cmp cmp) {
  using std::swap;
  auto parent{l};
  auto child{parent * 2 + 1};
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
template <typename Cont, typename Cmp>
void heap_sort(Cont& arr, size_t l, size_t r, Cmp cmp) {
  if (l + 1 >= r) return;
  using std::swap;
  const auto size{r - l};
  for (int i = size / 2 - 1; i > -1; --i) heapify(arr, i, size, cmp);
  for (int i = size - 1; i > -1; --i) {
    swap(arr[0], arr[i]);
    heapify(arr, 0, i, cmp);
  }
}
template void heap_sort<std::vector<int>, std::less<int>>(std::vector<int>&,
                                                          size_t, size_t,
                                                          std::less<int>);
template void heap_sort<std::vector<int>, std::greater<int>>(std::vector<int>&,
                                                             size_t, size_t,
                                                             std::greater<int>);
}  // namespace trivial
