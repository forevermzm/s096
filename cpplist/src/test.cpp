#include "list.h"
#include <iostream>

int main() {
  int N = 5;
  auto list = List{};

  for( int i = 0; i < N; ++i ) {
    list.append( i );
  }

  list.print();
  return 0;
}
