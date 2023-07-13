#include <unordered_map>
namespace trivial {
using std::unordered_map;
template <typename K, typename V>
struct DNode {
  K key{};
  V value{};
  using Node = DNode<K, V>;
  Node* prev{};
  Node* next{};
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
    node->prev = &head;
    node->next = head.next;
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

class LRU {
  using List = DList<int, int>;
  using Node = typename List::Node;
  List list{};
  unordered_map<int, Node*> cache;
  size_t _capacity{};

 public:
  LRU(int capacity) : _capacity(capacity) {}
  int get(int key) {
    if (!cache.count(key)) return -1;
    auto node = cache[key];
    list.remove(node);
    list.push_front(node);
    return node->value;
  }
  void set(int key, int value) {
    if (cache.count(key)) {
      auto node = cache[key];
      node->value = value;
      list.remove(node);
      list.push_front(node);
      return;
    }
    if (cache.size() == _capacity) {
      if (!list.empty()) {
        auto toRemove = list.end()->prev;
        cache.erase(toRemove->key);
        list.remove(toRemove);
        delete toRemove;
      }
    }

    auto newNode = new Node(key, value);
    list.push_front(newNode);
    cache[key] = newNode;
  }
};
}