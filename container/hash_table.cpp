#include <cstddef>
#include <vector>
namespace trivial {
using std::size_t;
using std::vector;
template <typename K, typename V>
struct LNode {
  K key{};
  V value{};
  using Node = LNode<K, V>;
  Node* next{};
  LNode() = default;
  LNode(const K& k, const V& v) : key(k), value(v) {}
};

template <typename K, typename V>
class HashTable {
  size_t buckets_cnt{100};
  using Node = typename LNode<K, V>::Node;
  vector<Node*> buckets{buckets_cnt, {}};
  size_t hash(const K& k) { return k % buckets_cnt; }

 public:
  HashTable() = default;
  void put(const K& k, const V& v) {
    auto list = buckets[hash(k)];
    while (list && list->key != k) list = list->next;
    if (!list) {
      auto newNode = new Node(k, v);
      newNode->next = buckets[hash(k)];
      buckets[hash(k)] = newNode;
      return;
    }
    list->value = v;
  }
  V get(const K& k) {
    auto list = buckets[hash(k)];
    while (list && list->key != k) list = list->next;
    if (!list) return -1;
    return list->value;
  }
  void remove(const K& k) {
    auto list = buckets[hash(k)];
    if (list && list->key == k) {
      buckets[hash(k)] = list->next;
      delete list;
      return;
    }
    while (list && list->next && list->next->key != k) list = list->next;
    if (list && list->next) {
      auto toRemove = list->next;
      list->next = toRemove->next;
      delete toRemove;
    }
  }
};
}