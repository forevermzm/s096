/*
PROG: matrix
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXN 100

typedef struct Matrix {
  size_t R, C;
  int index[MAXN][MAXN];
} Matrix;

void read_matrix( FILE *fin, Matrix *matrix ) {
  fscanf( fin, "%zu %zu", &matrix->R, &matrix->C );

  if( matrix->R >= MAXN || matrix->C >= MAXN ) {
    printf( "Error: tried to read matrix with a dimension larger than %d\n", MAXN );
    exit( EXIT_FAILURE );
  }

  for( size_t r = 0; r < matrix->R; ++r ) {
    for( size_t c = 0; c < matrix->C; ++c ) {
      fscanf( fin, "%d", &matrix->index[r][c] );
    }
  }
}

void print_matrix( FILE *fout, Matrix *matrix ) {
  for( size_t r = 0; r < matrix->R; ++r ) {
    for( size_t c = 0; c < matrix->C - 1; ++c ) {
      fprintf( fout, "%d ", matrix->index[r][c] );
    }
    fprintf( fout, "%d\n", matrix->index[r][matrix->C - 1] );
  }
}

void mult_matrix( Matrix *a, Matrix *b, Matrix *product ) {
  if( a->C != b->R ) {
    printf( "Error: tried to multiply (%zu x %zu) x (%zu x %zu)\n", a->R, a->C, b->R, b->C );
    exit( EXIT_FAILURE );
  }

  size_t inner = a->C;
  product->R = a->R;
  product->C = b->C;

  for( size_t r = 0; r < product->R; ++r ) {
    for( size_t c = 0; c < product->C; ++c ) {
      product->index[r][c] = 0;
      for( size_t i = 0; i < inner; ++i ) {
        product->index[r][c] += a->index[r][i] * b->index[i][c];
      }
    }
  }
}

int main(void) {
  FILE *fin = fopen( "matrix.in", "r" ),
       *fout = fopen( "matrix.out", "w" );

  if( fin == NULL ) {
    printf( "Error: could not open matrix.in\n" );
    exit( EXIT_FAILURE );
  }

  if( fin == NULL ) {
    printf( "Error: could not open matrix.out\n" );
    exit( EXIT_FAILURE );
  }

  Matrix a, b, c;

  read_matrix( fin, &a );
  read_matrix( fin, &b );
  fclose( fin );

  mult_matrix( &a, &b, &c );

  print_matrix( fout, &a );
  print_matrix( fout, &b );
  print_matrix( fout, &c );
  fclose( fout );

  return 0;
}
