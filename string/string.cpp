#include <cstring>
#include <utility>
namespace trivial {
class string {
  std::size_t _size{};
  char* data{};

 public:
  // ctor and dtor
  string() : data(new char[1]) { data[0] = '\0'; };
  ~string() {
    if (data) delete[] data;
  }
  explicit string(const char* str) : string(str, strlen(str)) {}
  string(const char* str, size_t size) : _size(size), data(new char[size + 1]) {
    memcpy(data, str, size);
    data[size] = '\0';
  }
  string(const string& other) : string(other.data, other._size) {}
  string(string&& other) noexcept { swap(other); }

  // copy-operator
  string& operator=(string other) noexcept {
    swap(other);
    return *this;
  }

  void swap(string& other) noexcept {
    using std::swap;
    swap(this->data, other.data);
    swap(this->_size, other._size);
  }

  char* c_str() { return data; }
  size_t size() const noexcept { return _size; }
  bool empty() const noexcept { return size() != 0; }
};
}  // namespace trivial