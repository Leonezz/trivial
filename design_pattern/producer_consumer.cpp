#include <pthread.h>

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
namespace trivial {
template <class T>
class SharedQueue {
  std::queue<T> que{};
  std::mutex mut{};
  std::condition_variable cv_producer{};
  std::condition_variable cv_consumer{};
  size_t capacity{100};
  bool empty() const noexcept { return que.empty(); }
  bool full() const noexcept { return que.size() == capacity; }

 public:
  SharedQueue() = default;
  SharedQueue(size_t cap) : capacity(cap) {}
  ~SharedQueue() {
    cv_producer.notify_all();
    cv_consumer.notify_all();
  }
  void put(const T& t) {
    std::unique_lock<std::mutex> lock(mut);
    if (full()) {
      cv_producer.wait(lock, [this] {
        if (!full()) return true;
        cv_consumer.notify_one();
        return false;
      });
    }
    que.push(t);
    cv_consumer.notify_one();
  }
  T take() {
    std::unique_lock<std::mutex> lock(mut);
    if (empty()) {
      cv_consumer.wait(lock, [this] {
        if (!empty()) return true;
        cv_producer.notify_one();
        return false;
      });
    }
    auto ans{que.front()};
    que.pop();
    cv_producer.notify_one();
    return ans;
  }
};

SharedQueue<int> SQ{};
std::mutex consoleMutex{};
void producer() {
  while (true) {
    int val = rand() % 1000;
    {
      std::lock_guard<std::mutex> _(consoleMutex);
      std::cout << "producing " << val
                << " from thread: " << std::this_thread::get_id() << '\n';
    }
    SQ.put(val);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void consumer() {
  while (true) {
    auto v = SQ.take();
    {
      std::lock_guard<std::mutex> _(consoleMutex);
      std::cout << "consuming data ";
      std::cout << v << " from thread: " << std::this_thread::get_id() << '\n';
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
}
}  // namespace trivial
using namespace trivial;
int main() {
  int numProducer{};
  int numConsumer{};
  std::cin >> numProducer >> numConsumer;
  std::vector<std::thread> threads{};
  for (int i = 0; i < numProducer; ++i) threads.emplace_back(producer);
  for (int i = 0; i < numConsumer; ++i) threads.emplace_back(consumer);

  std::shuffle(threads.begin(), threads.end(), std::mt19937{});
  for (auto& t : threads) t.join();
}
