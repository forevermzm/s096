#include "list.h"
#include "list_node.h"
#include "apply.h"
#include "reduce.h"

#include <iostream>

List::List() : _length{0}, _begin{ nullptr }, _back{ nullptr } {}

List::List( const List &list ) : _length{0}, _begin{nullptr}, _back{nullptr} {
  for( auto it = list.begin(); it != list.end(); ++it ) {
    append( *it );
  } 
}

List& List::operator=( const List &list ) {
  if( this != &list ) {
    clear();
    for( auto it = list.begin(); it != list.end(); ++it ) {
      append( *it );
    } 
  }
  return *this;
}

List::~List() { clear(); }

size_t List::length() const { return _length; }

int& List::value( size_t pos ) {
  auto it = begin();
  for( size_t i = 0; i < pos && it != end(); ++it, ++i );
  if( it == end() ) {
    throw ListOutOfBounds();
  }

  return *it;
}

int List::value( size_t pos ) const {
  auto it = begin();
  for( size_t i = 0; i < pos && it != end(); ++it, ++i );
  if( it == end() ) {
    throw ListOutOfBounds();
  }

  return *it;
}

bool List::empty() const {
  return _length == 0;
}

List::iterator List::begin() { return iterator{ _begin }; }
List::const_iterator List::begin() const { return const_iterator{ _begin }; }
List::iterator List::back() { return iterator{ _back }; }
List::const_iterator List::back() const { return const_iterator{ _back }; }
List::iterator List::end() { return iterator{ nullptr }; }
List::const_iterator List::end() const { return const_iterator{ nullptr }; }

void List::append( int theValue ) {
  auto *newNode = ListNode::create( theValue );

  if( empty() ) {
    newNode->setNext( _back );
    _begin = newNode;
  } else {
    newNode->insertAfter( _back );
  }

  _back = newNode;
  ++_length;
}

void List::deleteAll( int theValue ) {
  if( !empty() ) {
    // Delete from the front
    while( _begin->value() == theValue && _begin != _back ) {
      auto *newBegin = _begin->next();
      delete _begin;
      _begin = newBegin;
      --_length;
    }

    auto *p = _begin;

    if( _begin != _back ) {
      // Normal deletion from interior of list
      for( ; p->next() != _back; ) {
        if( p->next()->value() == theValue ) {
          ListNode::deleteNext( p );
          --_length;
        } else {
          p = p->next();
        }
      }

      // Deleting the last item
      if( _back->value() == theValue ) {
        ListNode::deleteNext( p );
        _back = p;
        --_length;
      }
    } else if( _begin->value() == theValue ) {
      // Deal with the case where we deleted the whole list
      _begin = _back = nullptr;
      _length = 0;
    }
  }
}

List::iterator List::find( iterator s, iterator t, int needle ) {
  for( auto it = s; it != t; ++it ) {
    if( *it == needle ) {
      return it;
    }
  }
  return t;
}

void List::insert( iterator pos, int theValue ) {
  auto *posPtr = node( pos );
  auto *newNode = ListNode::create( theValue );
  newNode->insertAfter( posPtr );
  ++_length;
}

void List::insertBefore( int theValue, int before ) {
  if( !empty() ) {
    if( _begin->value() == before ) {
      auto *newNode = ListNode::create( theValue );
      newNode->setNext( _begin );
      _begin = newNode;
      ++_length;
    } else {
      auto *p = _begin;
      for( ; p != _back && p->next()->value() != before; p = p->next() );
      if( p != _back && p->next()->value() == before ) {
        auto *newNode = ListNode::create( theValue );
        newNode->insertAfter( p );
        ++_length;
      }
    }
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
  for( auto it = begin(); it != back(); ++it ) {
    std::cout << *it << " -> ";
  }
  if( !empty() ) {
    std::cout << *back() << " ";
  }
  std::cout << "}\n";
}

void List::clear() {
  for( auto *p = _begin; p != nullptr; ) {
    auto *p_next = p->next();
    delete p;
    p = p_next;
  }
  _length = 0;
  _begin = nullptr;
  _back = nullptr;
}
