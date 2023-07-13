
#include <vector>
namespace trivial {
std::vector<std::vector<int>> floyd(std::vector<std::vector<int>>& grid) {
  const auto size{grid.size()};
  constexpr int INF = 0x3f3f3f3f;
  std::vector<std::vector<int>> ans(size, std::vector<int>(size, INF));
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (!grid[i][j]) continue;
      ans[i][j] = grid[i][j];
    }
  }
  for (int k = 0; k < size; ++k) {
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        using std::min;
        ans[i][j] = min(ans[i][j], ans[i][k] + ans[k][j]);
      }
    }
  }
  return ans;
}
}