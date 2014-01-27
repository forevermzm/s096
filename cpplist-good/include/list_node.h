#ifndef _6S096_CPPLIST_NODE_H
#define _6S096_CPPLIST_NODE_H
#include "list.h"

class ListNode {
	int _value;
	ListNode *_next;
	ListNode( const ListNode & ) = delete;
	ListNode& operator=( const ListNode & ) = delete;
public:
	ListNode() : _value{0}, _next{nullptr} {}
	ListNode( int theValue ) : _value{theValue}, _next{nullptr} {}
	~ListNode() {}
	int& value() { return _value; }
	int value() const { return _value; }
	ListNode* next() { return _next; }
	void insertAfter( ListNode *before ) {
			_next = before->next();
			before->_next = this;
	}
	void spliceIn( ListNode *before );
	void setNext( ListNode *nextNode ) {
		_next = nextNode;
	}
	static void deleteNext( ListNode *before ) {
		auto *after = before->next()->next();
		delete before->next();
		before->_next = after;
	}
	static void deleteSection( ListNode *before, ListNode *after ) {
		auto *deleteFront = before->next();
		while( deleteFront != after ) {
			auto *nextDelete = deleteFront->next();
			delete deleteFront;
			deleteFront = nextDelete;
		}
	}
	static ListNode* create( int theValue = 0 ) {
		return new ListNode{ theValue };
	}
};

#endif // _6S096_CPPLIST_NODE_H
