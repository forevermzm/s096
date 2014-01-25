#include "list.h"
#include "apply.h"
#include "reduce.h"

#include <list>
#include <algorithm>
#include <iostream>

List::List() : _length{0}, _list{} {}

List::~List() {}

size_t List::length() const {
  return _list.size();
}

int& List::value( size_t pos ) {
  if( pos >= length() ) {
    throw ListOutOfBounds();
  }

  auto it = std::begin( _list );

  while( it != std::end( _list ) && pos > 0 ) {
    ++it; --pos;
  }

  return *it;
}

int List::value( size_t pos ) const {
  if( pos >= length() ) {
    throw ListOutOfBounds();
  }

  auto it = std::begin( _list );

  while( it != std::end( _list ) && pos > 0 ) {
    ++it; --pos;
  }

  return *it;
}

void List::append( int theValue ) {
  _list.push_back( theValue );
}

void List::deleteAll( int theValue ) {
  _list.remove( theValue );
}

void List::insertBefore( int theValue, int before ) {
  auto pos = std::find( std::begin( _list ), std::end( _list ), before );

  if( pos != std::end( _list ) ) {
    _list.insert( pos, theValue );
  }
}

void List::apply( const ApplyFunction &interface ) {
  interface.apply( *this );
}

int List::reduce( const ReduceFunction &interface ) const {
  return interface.reduce( *this );
}

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
