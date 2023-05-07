#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
namespace trivial {
template <typename Cont, typename Sort>
void bucket_sort(Cont& arr, size_t l, size_t r, Sort srt) {
  if (l + 1 >= r) return;
  const auto minVal{*min_element(begin(arr) + l, begin(arr) + r)};
  const auto maxVal{*max_element(begin(arr) + l, begin(arr) + r)};
  const auto buckets_cnt{100};
  const auto bucket_size{(maxVal - minVal) / buckets_cnt + 1};
  std::vector<typename Cont::value_type> buckets[buckets_cnt]{};
  for (auto i{l}; i < r; ++i)
    buckets[(arr[i] - minVal) / bucket_size].push_back(arr[i]);
  auto idx{l};
  for (auto& vec : buckets) {
    srt(vec, 0, vec.size(), std::less<typename Cont::value_type>{});
    for (auto i : vec) arr[idx++] = i;
  }
}

template <typename Cont, typename Cmp>
void insertion_sort(Cont&, size_t, size_t, Cmp);
using ins_sort_vec_dec =
    decltype(insertion_sort<std::vector<int>, std::less<int>>);
template void bucket_sort<std::vector<int>, ins_sort_vec_dec>(std::vector<int>&,
                                                              size_t, size_t,
                                                              ins_sort_vec_dec);
}  // namespace trivial
