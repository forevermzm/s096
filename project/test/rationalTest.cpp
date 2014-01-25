#include "nbody/rational.h"
#include <gtest/gtest.h>

TEST( rationalTests, rational ) {
  auto a = Rational{ 1, 1 };
  auto b = Rational{ 1, -4 };
  ASSERT_EQ( ( a + b ).num(), 3 ) << "wanted " << Rational{ 3, 4 } << " got " << a + b;
  ASSERT_EQ( ( a + b ).den(), 4 ) << "wanted " << Rational{ 3, 4 } << " got " << a + b;

}
