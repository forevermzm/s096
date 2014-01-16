#include "rational.h"

#include <iostream>

int main() {
  auto a = Rational{ 1, 7 };
  auto b = Rational{ 2, 3 };
  std::cout << a / ( a - b ) << "\n";
  return 0;
}
