#include <mutex>

namespace trivial {
class singleton {
  singleton* instance{};
  std::mutex mut{};
  singleton() = default;
  singleton(singleton&) = delete;
  singleton& operator=(singleton) = delete;

 public:
  singleton* getInstance() {
    std::scoped_lock<std::mutex> lock(mut);
    if (!instance) instance = new singleton;
    return instance;
  }
};
}  // namespace trivial
