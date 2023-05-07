#include <random>
#include <utility>

namespace trivial {
template <typename K, typename V>
struct SkiplistNode {
  K key{};
  V value{};
  using Node = SkiplistNode<K, V>;
  Node** forward{};
  SkiplistNode() = default;
  ~SkiplistNode() {
    if (forward) delete[] forward;
  }
  SkiplistNode(const K& k, const V& v, std::size_t lv, Node* next = {})
      : key(k), value(v), forward(new Node*[lv + 1]) {
    for (int i = 0; i < lv + 1; ++i) forward[i] = next;
  }
};

template <typename K, typename V, typename Cmp>
class Skiplist {
  static constexpr std::size_t MaxLevel{100};
  static constexpr int P{4};
  static constexpr int S{0xFFFF};
  static constexpr int PS{S / P};

  using Node = typename SkiplistNode<K, V>::Node;
  Node tail{{}, {}, 0};
  Node head{{}, {}, MaxLevel, &tail};

  std::size_t level{};
  std::size_t _size{};

  Cmp cmp{};

  static auto randomLevel() {
    std::size_t lv{1};
    while ((rand() & S) > PS) ++lv;
    return lv > MaxLevel ? MaxLevel : lv;
  }
  Node* _find(const K& k, Node** update = {}) {
    auto node{&head};
    for (int i = level; i > -1; --i) {
      while (node->forward[i] != &tail && cmp(node->forward[i]->key, k))
        node = node->forward[i];
      if (update) update[i] = node;
    }
    return node->forward[0];
  }

 public:
  Skiplist() { srand(time(0)); };
  bool search(const K& k) {
    auto node = _find(k);
    return node != &tail && node->key == k;
  }
  V get(const K& k) {
    auto node = _find(k);
    return (node == &tail || node->key != k) ? V{} : node->value;
  }
  void set(const K& k, const V& v) {
    Node* update[MaxLevel + 1]{};
    auto node = _find(k, update);
    auto lv{randomLevel()};
    if (lv > level) {
      lv = ++level;
      update[lv] = &head;
    }
    auto newNode = new Node(k, v, lv);
    for (int i = lv; i > -1; --i) {
      newNode->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = newNode;
    }
    ++_size;
  }
  bool remove(const K& k) {
    Node* update[MaxLevel + 1]{};
    auto node = _find(k, update);
    if (node == &tail || node->key != k) return false;
    for (int i = 0; i < level + 1; ++i) {
      if (update[i]->forward[i] != node) break;
      update[i]->forward[i] = node->forward[i];
    }
    delete node;
    while (level && head.forward[level] == &tail) --level;
    --_size;
    return true;
  }
  auto size() const noexcept { return _size; }
  bool empty() const noexcept { return size() > 0; }
};
}  // namespace trivial
