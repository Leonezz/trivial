#include <map>
#include <unordered_map>
#include <utility>
namespace trivial {
template <typename K, typename V>
struct DNode {
  K key{};
  V value{};
  std::size_t cnt{};
  using Node = DNode<K, V>;
  Node* next{};
  Node* prev{};
  DNode() = default;
  DNode(const K& k, const V& v) : key(k), value(v) {}
};

template <typename K, typename V>
struct DList {
  using Node = typename DNode<K, V>::Node;
  Node head{};
  DList() {
    head.next = &head;
    head.prev = &head;
  }
  bool empty() const { return head.next == &head; }
  void push_front(Node* node) {
    if (!node) return;
    node->next = head.next;
    node->prev = &head;
    head.next = node;
    node->next->prev = node;
  }
  static void remove(Node* node) {
    if (!node) return;
    node->next->prev = node->prev;
    node->prev->next = node->next;
  }
  Node* end() { return &head; }
  Node* begin() { return empty() ? end() : head.next; }
};

template <typename K, typename V>
class LFUCache {
  std::size_t _capacity{};
  using List = DList<K, V>;
  using Node = typename List::Node;
  std::unordered_map<K, Node*> cache;
  std::map<size_t, List*> freq;
  void _update(const K& k) {
    if (!cache.count(k)) return;
    auto node = cache[k];
    if (freq.count(node->cnt)) {
      auto list = freq[node->cnt];
      list->remove(node);
      if (list->empty()) {
        freq.erase(node->cnt);
        delete list;
      }
    }
    ++node->cnt;
    if (!freq.count(node->cnt)) freq[node->cnt] = new List;
    freq[node->cnt]->push_front(node);
  }

 public:
  LFUCache(size_t capacity) : _capacity(capacity) {}
  V get(const K& key) {
    if (!cache.count(key)) return -1;
    _update(key);
    return cache[key]->value;
  }
  void set(const K& k, const V& v) {
    if (cache.count(k)) {
      _update(k);
      cache[k]->value = v;
      return;
    }
    if (cache.size() == _capacity) {
      auto [cnt, list] = *freq.begin();
      auto toRemove = list->end()->prev;
      list->remove(toRemove);
      if (list->empty()) {
        freq.erase(cnt);
        delete list;
      }
      cache.erase(toRemove->key);
      delete toRemove;
    }
    auto newNode = new Node(k, v);
    cache[k] = newNode;
    _update(k);
  }
};
}