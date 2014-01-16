#ifndef _6S096_RATIONAL_H
#define _6S096_RATIONAL_H

#include <cstdint>
#include <iosfwd>
#include <stdexcept>
#include <iostream>

class Rational {
  intmax_t _num, _den;

public:
  enum sign_type { POSITIVE, NEGATIVE };
  Rational() : _num{0}, _den{1} {}
  Rational( intmax_t numer ) : _num{numer}, _den{1} {}
  Rational( intmax_t numer, intmax_t denom ) : _num{numer}, _den{denom} { normalize(); }

//  Rational( float f );
//  Rational( double d );

  inline intmax_t num() const { return _num; }
  inline intmax_t den() const { return _den; }
  inline Rational inverse() const { return Rational{ _den, _num }; }
  void normalize();

  float to_float() const;
  double to_double() const;
  sign_type sign() const;
};

std::ostream& operator<<( std::ostream& os, const Rational &ratio );

inline bool operator==( const Rational &lhs, const Rational &rhs ) {
  return lhs.num() * rhs.den() == rhs.num() * lhs.den();
}

inline bool operator<( const Rational &lhs, const Rational &rhs ) {
  if( lhs.sign() == Rational::POSITIVE && rhs.sign() == Rational::POSITIVE ) {
      return lhs.num() * rhs.den() < rhs.num() * lhs.den();
  } else if( lhs.sign() == Rational::NEGATIVE && rhs.sign() == Rational::NEGATIVE ) {
    return lhs.num() * rhs.den() > rhs.num() * lhs.den();
  } else {
    return lhs.sign() == Rational::NEGATIVE;
  }
}

inline Rational operator*( const Rational &a, const Rational &b ) {
  return Rational{ a.num() * b.num(), a.den() * b.den() };
}

inline Rational operator+( const Rational &a, const Rational &b ) {
  return Rational{ a.num() * b.den() + b.num() * a.den(), a.den() * b.den() };
}

inline Rational operator-( const Rational &a, const Rational &b ) {
  return Rational{ a.num() * b.den() - b.num() * a.den(), a.den() * b.den() };
}

inline Rational operator/( const Rational &a, const Rational &b ) {
  return a * b.inverse();
}

class bad_rational : public std::domain_error {
public:
  explicit bad_rational() : std::domain_error( "Bad rational: zero denominator" ) {}
};

#endif // _6S096_RATIONAL_H
