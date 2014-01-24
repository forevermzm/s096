#include "rational.h"
#include <gtest/gtest.h>

TEST( rationalTests, rational ) {
  auto a = Rational{ 1, 1 };
  auto b = Rational{ 1, -4 };
  ASSERT_EQ( ( a + b ).num(), 3 );
  ASSERT_EQ( ( a + b ).den(), 4 );
}
