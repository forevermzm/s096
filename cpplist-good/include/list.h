#ifndef _6S096_CPPLIST_H
#define _6S096_CPPLIST_H
#include <cstddef>
#include <stdexcept>

// Forward declaration of apply/reduce
class ApplyFunction;
class ReduceFunction;
class ListNode;

class List {
  size_t _length;
  ListNode *_begin;
  ListNode *_back;
public: 
  class iterator {
    ListNode *_node;
  public:
    friend ListNode* node( iterator it );
    iterator( ListNode *theNode );
    iterator& operator++();
    int& operator*();
    bool operator==( const iterator &rhs );
    bool operator!=( const iterator &rhs );
  };

  class const_iterator {
    ListNode *_node;
  public:
    friend ListNode* node( const_iterator it );
    const_iterator( const iterator &it ) : _node{it.node()} {}
    const_iterator( ListNode *theNode );
    const_iterator& operator++();
    const int& operator*();
    bool operator==( const const_iterator &rhs );
    bool operator!=( const const_iterator &rhs );
  };

  List();
  ~List();
  List( const List &list ) = delete;
  List& operator=( const List &list ) = delete;
  size_t length() const;
  int& value( size_t pos );
  int value( size_t pos ) const;
  bool empty() const;

  iterator begin();
  const_iterator begin() const;
  iterator back();
  const_iterator back() const;
  iterator end();
  const_iterator end() const;

  iterator find( iterator s, iterator t, int needle );
  void append( int theValue );
  void deleteAll( int theValue );
  void insertBefore( int theValue, int before );
  void insert( iterator pos, int theValue );

  void apply( const ApplyFunction &interface );
  int reduce( const ReduceFunction &interface ) const;
  void print() const;
private:
  ListNode* node( iterator it ) { return it._node; }
  ListNode* node( const_iterator it ) { return it._node; }
};

class ListOutOfBounds : public std::range_error {
public:
  explicit ListOutOfBounds() : std::range_error( "List index out of bounds" ) {}
};

#endif // _6S096_CPPLIST_H
