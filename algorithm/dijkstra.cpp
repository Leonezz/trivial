#include <map>
#include <queue>
#include <vector>
namespace trivial {
using Node = std::pair<int, int>;
using Edge = std::pair<int, int>;

std::vector<int> dijkstra(std::vector<std::vector<int>>& grid, int source) {
  const auto size{grid.size()};
  std::vector<std::vector<int>> adjList{size};
  constexpr int INF = 0x3f3f3f3f;
  std::vector<int> ans(size, INF);
  for (auto i = 0; i < size; ++i) {
    for (auto j = 0; j < size; ++j) {
      if (!grid[i][j]) continue;
      adjList[i].push_back(j);
    }
  }
  ans[source] = 0;
  auto cmp = [&ans](int l, int r) { return ans[l] > ans[r]; };
  std::priority_queue<int, std::deque<int>, decltype(cmp)> que(cmp);
  que.push(source);
  while (!que.empty()) {
    auto node = que.top();
    que.pop();
    for (auto nei : adjList[node]) {
      if (ans[nei] > ans[node] + grid[node][nei]) {
        ans[nei] = ans[node] + grid[node][nei];
        que.push(nei);
      }
    }
  }
  return ans;
}
}