#ifndef _6S096_CPPLIST_H
#define _6S096_CPPLIST_H
#include <list>
#include <cstddef>
#include <stdexcept>

// Forward declaration of apply/reduce
class ApplyFunction;
class ReduceFunction;

class List {
  // ... put whatever private data members you need here
  // can add any private member functions you'd like
  size_t _length;
  std::list<int> _list;
public: 
  List();
  ~List();
  size_t length() const;
  int& value( size_t pos );
  int value( size_t pos ) const;

  void append( int value );
  void deleteAll( int value );
  void insertBefore( int value, int before );

  void apply( const ApplyFunction &interface );
  int reduce( const ReduceFunction &interface ) const;
  void print() const;
};

// Exception to throw if given a bad position
class ListOutOfBounds : public std::range_error {
public:
  explicit ListOutOfBounds() : std::range_error( "List index out of bounds" ) {}
};

#endif // _6S096_CPPLIST_H
