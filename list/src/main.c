#include "list.h"

int main(void) {
  int N = 5;
  List list = empty_list();

  for( int i = 0; i < N; ++i ) {
    list_append( &list, i );
  }

  list_print( list );
  list_clear( &list );
  return 0;
}
