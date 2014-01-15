#include "list.h"

/* This is a sample main.c file for you to test your code.
 * This file will be ignored and overwritten by the grader
 * and replaced with testing code, so feel to change this up
 * as much as you want for local testing purposes.
 */

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
