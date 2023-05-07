#include <functional>
#include <utility>
#include <vector>
namespace trivial {
template <typename Cont, typename Cmp>
void quick_sort_three_way(Cont& arr, size_t l, size_t r, Cmp cmp) {
  using std::swap;
  if (l >= r) return;
  const auto pivot{arr[rand() % (r - l) + l]};
  /**
   * | * * * * * * * * * * mid * * * * * * * * * end * * * * * * * * |
   * |   less than pivot   |   equal to pivot  |   greater than pivot  |
   */
  size_t cur{l};
  size_t mid{l};
  size_t end{r};
  while (cur < end) {
    if (cmp(arr[cur], pivot))
      swap(arr[cur++], arr[mid++]);
    else if (cmp(pivot, arr[cur]))
      swap(arr[cur], arr[--end]);
    else
      ++cur;
  }
  quick_sort_three_way(arr, l, mid, cmp);
  quick_sort_three_way(arr, end, r, cmp);
}

template void quick_sort_three_way<std::vector<int>, std::less<int>>(
    std::vector<int>&, size_t, size_t, std::less<int>);
template void quick_sort_three_way<std::vector<int>, std::greater<int>>(
    std::vector<int>&, size_t, size_t, std::greater<int>);

template <typename Cont, typename Cmp>
size_t partition(Cont& arr, size_t l, size_t r, Cmp cmp) {
  using std::swap;
  const auto pivot{l};
  auto idx{pivot + 1};
  for (auto i{idx}; i < r; ++i) {
    if (cmp(arr[i], arr[pivot])) swap(arr[i], arr[idx++]);
  }
  swap(arr[pivot], arr[--idx]);
  return idx;
}

template <typename Cont, typename Cmp>
void quick_sort_partition(Cont& arr, size_t l, size_t r, Cmp cmp) {
  if (l >= r) return;
  auto divide{partition(arr, l, r, cmp)};
  quick_sort_partition(arr, l, divide, cmp);
  quick_sort_partition(arr, divide + 1, r, cmp);
}

template void quick_sort_partition<std::vector<int>, std::less<int>>(
    std::vector<int>&, size_t, size_t, std::less<int>);
template void quick_sort_partition<std::vector<int>, std::greater<int>>(
    std::vector<int>&, size_t, size_t, std::greater<int>);

template <typename Cont, typename Cmp>
void quick_sort(Cont& arr, size_t l, size_t r, Cmp cmp, std::true_type) {
  quick_sort_three_way(arr, l, r, cmp);
}
template <typename Cont, typename Cmp>
void quick_sort(Cont& arr, size_t l, size_t r, Cmp cmp, std::false_type) {
  quick_sort_partition(arr, l, r, cmp);
}

template void quick_sort<std::vector<int>, std::less<int>>(std::vector<int>&,
                                                           size_t, size_t,
                                                           std::less<int>,
                                                           std::true_type);

template void quick_sort<std::vector<int>, std::less<int>>(std::vector<int>&,
                                                           size_t, size_t,
                                                           std::less<int>,
                                                           std::false_type);

template void quick_sort<std::vector<int>, std::greater<int>>(std::vector<int>&,
                                                              size_t, size_t,
                                                              std::greater<int>,
                                                              std::true_type);

template void quick_sort<std::vector<int>, std::greater<int>>(std::vector<int>&,
                                                              size_t, size_t,
                                                              std::greater<int>,
                                                              std::false_type);

}  // namespace trivial
