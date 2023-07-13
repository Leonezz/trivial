#include <string>
#include <vector>

namespace trivial {
std::vector<int> prefix(std::string p) {
  const auto size{p.size()};
  std::vector<int> next(size);
  for (auto i{1}; i < size; ++i) {
    int j = next[i];
    while (j > 0 && p[i] != p[j]) j = next[j - 1];
    if (p[i] == p[j]) ++j;
    next[i] = j;
  }
  return next;
}
std::vector<int> prefix2(std::string p) {
  const auto size{p.size()};
  std::vector<int> next(size);
  for (int pre{}, cur{1}; cur < size;) {
    if (p[pre] == p[cur]) {
      ++pre;
      next[cur++] = pre;
    } else if (pre > 0)
      pre = next[pre - 1];
    else
      next[cur++] = 0;
  }
  return next;
}
std::vector<int> KMP_find(std::string str, std::string pat) {
  const auto str_len{str.size()};
  const auto pat_len{pat.size()};
  const auto next{prefix(pat)};
  std::vector<int> ans{};
  for (int pat_idx{}, str_idx{}; str_idx < str_len;) {
    if (str[str_idx] == pat[pat_idx]) {
      ++str_idx;
      ++pat_idx;
    } else if (pat_idx > 0)
      pat_idx = next[pat_idx - 1];
    else
      ++str_idx;
    if (pat_idx == pat_len) {
      ans.push_back(str_idx - pat_len);
      pat_idx = next[pat_idx - 1];
    }
  }
  return ans;
}
std::vector<int> KMP_find2(std::string str, std::string pat) {
  const auto str_len{str.size()};
  const auto pat_len{pat.size()};
  const auto patstr{pat + '#' + str};
  const auto next{prefix2(patstr)};
  std::vector<int> ans{};
  for (auto i{pat_len + 1}; i < patstr.size(); ++i) {
    if (next[i] == pat_len) ans.push_back(i - 2 * pat_len);
  }
  return ans;
}
}  // namespace trivial