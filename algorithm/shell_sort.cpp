#include <functional>
#include <utility>
#include <vector>

namespace trivial {
template <typename Cont, typename Cmp>
void shell_sort(Cont& arr, size_t l, size_t r, Cmp cmp) {
  using std::swap;
  const auto size{r - l};
  int gap{1};
  while (gap * 3 < size) gap = gap * 3 + 1;

  while (gap > 0) {
    for (int i = l + gap; i < r; ++i) {
      for (int j = i; j - gap > -1 && cmp(arr[j], arr[j - gap]); j -= gap) {
        swap(arr[j], arr[j - gap]);
      }
    }
    gap /= 3;
  }
}

template void shell_sort<std::vector<int>, std::less<int>>(std::vector<int>&,
                                                           size_t, size_t,
                                                           std::less<int>);
template void shell_sort<std::vector<int>, std::greater<int>>(
    std::vector<int>&, size_t, size_t, std::greater<int>);
}  // namespace trivial
