#include "list.h"
#include "apply.h"
#include "reduce.h"

#include <iostream>

// complete the constructor!
List::List() {}

// complete the destructor, as necessary
List::~List() {}

size_t List::length() const {
  // you fill out!
}

// Throw ListOutOfBounds() if pos >= length().
int& List::value( size_t pos ) {
  // you fill out!
}

// Throw ListOutOfBounds() if pos >= length().
int List::value( size_t pos ) const {
  // you fill out!
}

void List::append( int theValue ) {
  // you fill out!
}

void List::deleteAll( int theValue ) {
  // you fill out!
}


void List::insertBefore( int theValue, int before ) {
  // you fill out!
}

// See apply.cpp
void List::apply( const ApplyFunction &interface ) {
  interface.apply( *this );
}

// See reduce.cpp
int List::reduce( const ReduceFunction &interface ) const {
  return interface.reduce( *this );
}

// Already written for you, but kind of slow on large
// lists. Only for debugging purposes (function will
// not be tested on the grader)
void List::print() const {
  std::cout << "{ ";
  for( size_t p = 0; p < length() - 1; ++p ) {
    std::cout << value( p ) << " -> ";
  }
  if( length() > 0 ) {
    std::cout << value( length() - 1 ) << " ";
  }
  std::cout << "}\n";
}
