#include <assert.h>

#include <random>
#include "../priority_queue.cpp"
int main() {
  trivial::priority_queue<int>* pq = new trivial::priority_queue<int>;
  for (int i = 0; i < 100; ++i) pq->push(rand() % 1000);
  int pre{0x003f3f3f};
  while (!pq->empty()) {
    auto v = pq->front();
    pq->pop();
    assert(pre >= v);
    pre = v;
  }
}
