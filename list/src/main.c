#include "list.h"

int main(void) {
  int N = 5;
  int items[] = { 1, 2, 3, 4, 5};
  List list = empty_list();

  for( int i = 0; i < N; ++i ) {
    list_append( &list, items[i] );
  }

  list_print( &list );
  list_clear( &list );
  return 0;
}
