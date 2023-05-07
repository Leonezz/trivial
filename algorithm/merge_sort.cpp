#include <functional>
#include <utility>
#include <vector>
namespace trivial {
template <typename Cont, typename Cmp>
void merge(Cont& arr1, size_t l1, size_t r1, Cont& arr2, size_t l2, size_t r2,
           Cont& dest, size_t d, Cmp cmp) {
  while (l1 < r1 && l2 < r2) {
    if (cmp(arr1[l1], arr2[l2]))
      dest[d++] = arr1[l1++];
    else
      dest[d++] = arr2[l2++];
  }
  while (l1 < r1) dest[d++] = arr1[l1++];
  while (l2 < r2) dest[d++] = arr2[l2++];
}
template <typename Cont, typename Cmp>
void merge_sort(Cont& arr, size_t l, size_t r, Cmp cmp) {
  if (l + 1 >= r) return;
  size_t mid{((r - l) >> 1) + l};
  merge_sort(arr, l, mid, cmp);
  merge_sort(arr, mid, r, cmp);
  std::vector<typename Cont::value_type> tmp(r - l);
  merge(arr, l, mid, arr, mid, r, tmp, 0, cmp);
  for (auto i{l}; i < r; ++i) arr[i] = tmp[i - l];
}
template void merge_sort<std::vector<int>, std::less<int>>(std::vector<int>&,
                                                           size_t, size_t,
                                                           std::less<int>);
template void merge_sort<std::vector<int>, std::greater<int>>(
    std::vector<int>&, size_t, size_t, std::greater<int>);
}  // namespace trivial
