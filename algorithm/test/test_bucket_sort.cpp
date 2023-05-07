#include <assert.h>

#include <functional>
#include <random>
#include <vector>
using std::vector;

namespace trivial {
template <typename Cont, typename Cmp>
void insertion_sort(Cont&, size_t, size_t, Cmp);

template <typename Cont, typename Sort>
void bucket_sort(Cont&, size_t, size_t, Sort);
}  // namespace trivial
int main() {
  vector<int> arr;
  for (int i = 0; i < 10000; ++i) arr.push_back(rand() % 10000);
  using ins_sort =
      decltype(trivial::insertion_sort<std::vector<int>, std::less<int>>);
  trivial::bucket_sort<std::vector<int>, ins_sort>(
      arr, 0, arr.size(),
      trivial::insertion_sort<std::vector<int>, std::less<int>>);
  for (int i = 0; i < arr.size() - 1; ++i)
    assert(std::less_equal<int>{}(arr[i], arr[i + 1]));
}
