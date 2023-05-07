#include <assert.h>

#include <functional>
#include <random>
#include <type_traits>
#include <vector>
using std::vector;

namespace trivial {
template <typename Cont, typename Cmp>
void quick_sort(Cont& arr, size_t, size_t, Cmp, std::true_type);

template <typename Cont, typename Cmp>
void quick_sort(Cont& arr, size_t, size_t, Cmp, std::false_type);

// using std::swap;
// template <typename Cont, typename Cmp>
// size_t partition(Cont& arr, size_t l, size_t r, Cmp cmp) {
//   size_t pivoit{l};
//   size_t idx{pivoit + 1};
//   for (int i = idx; i < r; ++i) {
//     if (cmp(arr[i], arr[pivoit])) swap(arr[idx++], arr[i]);
//   }
//   swap(arr[pivoit], arr[--idx]);
//   return idx;
// }
// template <typename Cont, typename Cmp>
// void quick_sort_partition(Cont& arr, size_t l, size_t r, Cmp cmp) {
//   if (l >= r) return;
//   auto divide{partition(arr, l, r, cmp)};
//   quick_sort_partition(arr, l, divide, cmp);
//   quick_sort_partition(arr, divide + 1, r, cmp);
// }
//
// template <typename Cont, typename Cmp>
// void quick_sort_three_way(Cont& arr, size_t l, size_t r, Cmp cmp) {
//   if (l >= r) return;
//   auto pivot{arr[(rand() % (r - l)) + l]};
//
//   /**
//    * | less then pivot | equal to pivot | greater then pivot |
//    * | l ...           | mid ...        | end ...            | r
//    */
//
//   auto cur{l};
//   auto mid{l};
//   auto end{r};
//
//   while (cur < end) {
//     if (cmp(arr[cur], pivot))
//       swap(arr[cur++], arr[mid++]);
//     else if (cmp(pivot, arr[cur]))
//       swap(arr[cur], arr[--end]);
//     else
//       ++cur;
//   }
//   quick_sort_three_way(arr, l, mid, cmp);
//   quick_sort_three_way(arr, end, r, cmp);
// }

// template <typename Cont, typename Cmp>
// void quick_sort(Cont& arr, size_t l, size_t r, Cmp cmp, std::true_type) {
//   quick_sort_partition(arr, l, r, cmp);
// }
// template <typename Cont, typename Cmp>
// void quick_sort(Cont& arr, size_t l, size_t r, Cmp cmp, std::false_type) {
//   quick_sort_three_way(arr, l, r, cmp);
// }

}  // namespace trivial

#include "print.hpp"
int main() {
  vector<int> arr;
  for (int i = 0; i < 10; ++i) arr.push_back(rand() % 10000);
  print(arr);
  trivial::quick_sort(arr, 0, arr.size(), std::less<int>{}, std::true_type{});
  print(arr);
  for (int i = 0; i < arr.size() - 1; ++i)
    assert(std::less_equal<int>{}(arr[i], arr[i + 1]));
  trivial::quick_sort(arr, 0, arr.size(), std::greater<int>{},
                      std::true_type{});
  for (int i = 0; i < arr.size() - 1; ++i)
    assert(std::greater_equal<int>{}(arr[i], arr[i + 1]));

  // std::shuffle(begin(arr), end(arr), std::mt19937{});

  trivial::quick_sort(arr, 0, arr.size(), std::less<int>{}, std::false_type{});
  for (int i = 0; i < arr.size() - 1; ++i)
    assert(std::less_equal<int>{}(arr[i], arr[i + 1]));
  trivial::quick_sort(arr, 0, arr.size(), std::greater<int>{},
                      std::false_type{});
  for (int i = 0; i < arr.size() - 1; ++i)
    assert(std::greater_equal<int>{}(arr[i], arr[i + 1]));
}
