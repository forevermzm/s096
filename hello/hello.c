/*
PROG: hello
LANG: C
*/
#include <stdio.h>

int main(void) {
  FILE *fout = fopen( "hello.out", "w" );
  fprintf( fout, "Hello, world!\n" );
  fclose( fout );
  return 0;
}
