#include "rational.h"
#include "gcd.h"

#include <stdexcept>
#include <ostream>
#include <iostream>

/* By default, initialize to zero. */

Rational::sign_type Rational::sign() const {
  return _num >= 0 ? POSITIVE : NEGATIVE;
}

std::ostream& operator<<( std::ostream& os, const Rational &ratio ) {
  if( ratio.sign() == Rational::NEGATIVE ) {
    os << "-";
  }
  os << std::abs( ratio.num() ) << "/" << std::abs( ratio.den() );
  return os;
}

void Rational::normalize() {
  if( _den == 0 ) {
    throw bad_rational();
  }

  if( _num == 0 ) {
    _den = 1; return;
  }

  auto g = gcd( abs( _num ), abs( _den ) );
  _num /= g; _den /= g;

  if( _den < 0 ) {
    _num = -_num;
    _den = -_den;
  }
}

float Rational::to_float() const {
  return static_cast<float>( _num ) / static_cast<float>( _den );
}

double Rational::to_double() const {
  return static_cast<double>( _num ) / static_cast<double>( _den );
}
