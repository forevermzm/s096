#include <memory>
#include <vector>

typedef std::shared_ptr<int> IntPtr;

int main() {
  std::vector<IntPtr> ints;
  for( int i = 0; i < 10; ++i ) {
    ints.push_back( IntPtr( new int ) );
  }
  return 0;
}
