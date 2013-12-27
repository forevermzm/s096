#ifndef _AKESSLER_LIST_H
#define _AKESSLER_LIST_H

#include <stdlib.h>

typedef struct List_node_s List_node;

struct List_s {
  size_t length;
  List_node *front;
};
typedef struct List_s List;

List empty_list( void );
void list_append( List *list, int value );
void list_clear( List *list );
void list_print( List *list );

#endif // _AKESSLER_LIST_H
