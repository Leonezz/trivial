#include <queue>
#include <vector>
namespace trivial {
bool topological_sort(const std::vector<std::vector<int>>& grid,
                      std::vector<std::vector<int>>& ans) {
  const auto size{grid.size()};
  std::vector<std::vector<int>> adjList(size);
  std::vector<int> indegree(size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (!grid[i][j]) continue;
      adjList[i].push_back(j);
      ++indegree[j];
    }
  }
  std::queue<int> que{};
  for (int i = 0; i < size; ++i) {
    if (indegree[i] == 0) que.push(i);
  }

  int hasTopoSort{};
  while (!que.empty()) {
    const auto s{que.size()};
    hasTopoSort += s;
    ans.emplace_back();
    for (int i = 0; i < s; ++i) {
      const auto node = que.front();
      que.pop();
      for (auto const nei : adjList[node]) {
        if (--indegree[nei] == 0) {
          ans.back().push_back(nei);
          que.push(nei);
        }
      }
    }
  }
  return hasTopoSort == size;
}
}