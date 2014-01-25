#include <vector>
#include <iostream>

int main() {
  std::vector<int> intArray;

  for( int i = 0; i < 100; ++i ) {
    intArray.push_back( i * i );
  }

  // for val in list:
  for( auto val : intArray ) {
    val = 5;
  }

  std::cout << intArray[0] << "\n";
  return 0;
}
