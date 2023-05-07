#include <functional>
#include <utility>
#include <vector>
namespace trivial {
template <typename Cont, typename Cmp>
void insertion_sort(Cont& arr, size_t l, size_t r, Cmp cmp) {
  for (int i = l + 1; i < r; ++i) {
    int j = i - 1;
    auto k{arr[i]};
    while (j >= (int)l && cmp(k, arr[j])) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = k;
  }
}

using Cont = std::vector<int>;
using Inc = std::less<int>;
using Dec = std::greater<int>;
template void insertion_sort<Cont, Inc>(Cont&, size_t, size_t, Inc);
template void insertion_sort<Cont, Dec>(Cont&, size_t, size_t, Dec);
}  // namespace trivial
