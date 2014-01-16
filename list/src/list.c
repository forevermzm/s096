#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct List_node_s {
  List_node *next;
  int value;
};

List empty_list( void ) {
  return (List) { .length = 0, .front = NULL };
}

List_node* create_node( int value ) {
  List_node *new_node = malloc( sizeof( List_node ) );
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

void list_print( List list ) {
  if( list.front == NULL ) {
    printf( "{}\n" );
  } else {
    printf( "{ " );

    List_node *p = list.front;
    size_t length = list.length;

    while( p->next != NULL && length > 0 ) {
      printf( "%d -> ", p->value );
      p = p->next; --length;
    }
    printf( "%d }\n", p->value );

    if( length != 1 ) {
      printf( "Error: badly formed list.\n" );
      exit( EXIT_FAILURE );
    }
  }
}

void list_append( List *list, int value ) {
  List_node *new_node = create_node( value );

  if( list->front == NULL ) {
    list->front = new_node;
    list->length = 1;
  } else {
    List_node *p = list->front;
    size_t length = list->length;

    while( p->next != NULL && length > 0 ) {
      p = p->next; --length;
    }

    if( length != 1 ) {
      printf( "Error: failed to append item.\n" );
      printf( "(wanted length 1, got %zu)\n", length );
      exit( EXIT_FAILURE );
    }

    p->next = new_node;
    ++list->length;
  }
}

void list_clear( List *list ) {
  List_node *front = list->front;
  size_t length = list->length;

  while( front != NULL && length > 0 ) {
    List_node *next = front->next;
    free( front );
    front = next;
    --length;
  }

  if( length != 0 ) {
    printf( "Error: failed to clean up list properly.\n" );
    exit( EXIT_FAILURE );
  }
}
