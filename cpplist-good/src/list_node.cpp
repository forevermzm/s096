#include "list_node.h"

ListNode::ListNode() : _value{0}, _next{nullptr} {}
ListNode::ListNode( int theValue ) : _value{theValue}, _next{nullptr} {}
ListNode::~ListNode() {}
int& ListNode::value() { return _value; }
int ListNode::value() const { return _value; }
ListNode* ListNode::next() { return _next; }

void ListNode::insertAfter( ListNode *before ) {
  _next = before->next();
  before->_next = this;
}

void ListNode::setNext( ListNode *nextNode ) {
  _next = nextNode;
}

void ListNode::deleteNext( ListNode *before ) {
  auto *after = before->next()->next();
  delete before->next();
  before->_next = after;
}

void ListNode::deleteSection( ListNode *before, ListNode *after ) {
  auto *deleteFront = before->next();
  while( deleteFront != after ) {
    auto *nextDelete = deleteFront->next();
    delete deleteFront;
    deleteFront = nextDelete;
  }
}

ListNode* ListNode::create( int theValue ) {
  return new ListNode{ theValue };
}
