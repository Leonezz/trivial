#include <assert.h>

#include <functional>
#include <random>
#include <vector>
using std::vector;

namespace trivial {
template <typename Cont, typename Cmp>
void insertion_sort(Cont&, size_t, size_t, Cmp);
}
int main() {
  vector<int> arr;
  for (int i = 0; i < 10000; ++i) arr.push_back(rand() % 10000);
  trivial::insertion_sort(arr, 0, arr.size(), std::less<int>{});
  for (int i = 0; i < arr.size() - 1; ++i)
    assert(std::less_equal<int>{}(arr[i], arr[i + 1]));
  trivial::insertion_sort(arr, 0, arr.size(), std::greater<int>{});
  for (int i = 0; i < arr.size() - 1; ++i)
    assert(std::greater_equal<int>{}(arr[i], arr[i + 1]));
}
