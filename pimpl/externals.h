#include <memory>
// Forward declaration
class Internals;

// pimpl = pointer to implementation
typedef std::unique_ptr<Internals> InternalsPtr;
class Externals {
  InternalsPtr _pimpl;
public:
  Externals() : _pimpl{new Internals{}} {}
  int data1() const;
  double thing() const;
  int item( size_t i ) const;
};
