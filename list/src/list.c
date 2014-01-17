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

void list_insert_before( List *list, int insert, int before ) {
  List_node *front = list->front;

  if( front != NULL && front->value == before ) {
    List_node *new_node = create_node( insert );
    new_node->next = front;
    list->front = new_node;
    ++list->length;
    return;
  }

  size_t length = list->length;

  while( front != NULL && length > 0 ) {
    List_node *next = front->next;
    if( next != NULL && next->value == before ) {
      List_node *new_node = create_node( insert );
      new_node->next = next;
      front->next = new_node;
      ++list->length;
      return;
    }
    front = next;
    --length;
  }

  if( length != 0 ) {
    printf( "Error: failed to insert node properly.\n" );
    exit( EXIT_FAILURE );
  }
}

void list_delete( List *list, int value ) {
  List_node *front = list->front;

  if( front != NULL && front->value == value ) {
    if( front->next != NULL ) {
      list->front = front->next;
      --list->length;
      free( front );
      front = list->front;
      list_delete( list, value );
    } else {
      --list->length;
      free( front );
      list->front = NULL;
      if( list->length != 0 ) {
        fprintf( stderr, "Bad list length during delete!\n" );
        exit( EXIT_FAILURE );
      }
    }
  }

  size_t length = list->length;

  while( front != NULL && length > 0 ) {
    List_node *next = front->next;
    if( next != NULL && next->value == value ) {
      front->next = next->next;
      free( next );
      --list->length;
      --length;
    }
    front = next;
    --length;
  }

  if( length != 0 ) {
    printf( "Error: failed to delete value properly.\n" );
    exit( EXIT_FAILURE );
  }
}

void list_apply( List *list, int (*function_ptr)(int) ) {
  List_node *front = list->front;
  size_t length = list->length;

  while( front != NULL && length > 0 ) {
    List_node *next = front->next;
    front->value = (*function_ptr)( front->value );
    front = next;
    --length;
  }

  if( length != 0 ) {
    printf( "Error: failed to APPLY properly.\n" );
    exit( EXIT_FAILURE );
  }
}

int list_reduce( List *list, int (*function_ptr)(int, int) ) {
  List_node *front = list->front;
  size_t length = list->length;
  int result = front->value;

  while( front != NULL && length > 0 ) {
    List_node *next = front->next;
    result = (*function_ptr) ( result, front->value );
    front = next; --length;
  }

  if( length != 0 ) {
    printf( "Error: could not reduce list properly.\n" );
    exit( EXIT_FAILURE );
  }

  return result;
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
