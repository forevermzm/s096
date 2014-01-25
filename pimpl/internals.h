#include <vector>

class Internals {
  int _data1;
  double _thing;
  std::vector<int> _items;
  // not sure we're using a vector
public:
  int data1() const { return _data1; }
  double thing() const { return _thing; }
  int item( size_t i ) const {
    return _items[i];
  }
};
