#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_random( float *a, size_t N ) {
  for( size_t i = 0; i < N; ++i ) {
    a[i] = (float) rand();
  }
}

void vector_add( float *a, float *b, float *c, size_t N ) {
  for( size_t i = 0; i < N; ++i ) {
    c[i] = a[i] + b[i];
  }
}

void usage( char *path ) {
  printf( "Usage: %s [VECTOR_SIZE]\n", path );
}

int main( int argc, char **argv ) {
  srand( 0 );
  if( argc != 2 ) {
    usage( argv[0] ); 
    exit( EXIT_FAILURE );
  }

  size_t N;
  sscanf( argv[1], "%zu", &N );

  float *a = malloc( N * sizeof( float ) );
  float *b = malloc( N * sizeof( float ) );
  float *c = malloc( N * sizeof( float ) );

  double start, stop;

  start = clock();
  fill_random( a, N );
  fill_random( b, N );
  stop = clock();
  printf( "Generated %zu elements in %.3f seconds.\n", 2 * N, ( stop - start ) / CLOCKS_PER_SEC );

  start = clock();
  vector_add( a, b, c, N );
  stop = clock();
  printf( "Added %zu elements in %.3f seconds.\n", N, ( stop - start ) / CLOCKS_PER_SEC );

  free( a );
  free( b );
  free( c );
  return 0;
}
