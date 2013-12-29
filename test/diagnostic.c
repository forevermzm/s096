#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

/* == PROBLEM 8 == */
bool is_prime( int n ) {
  if( n <= 2 || n % 2 == 0 ) {
    return ( n == 2 );
  }

  for( int i = 3; i * i <= n; i += 2 ) {
    if( n % i == 0 ) {
      return false;
    }
  }

  return true;
}

/* == PROBLEM 9 == */

#define swap( type, a, b ) \
  do { \
    type tmp = a; a = b; b = tmp; \
  } while ( 0 ) 

void permute( int *digits, int n, int p ) {
  if( p == n ) {
    for( int i = 0; i < n; ++i ) {
      printf( "%d ", digits[i] );
    }
    printf( "\n" );
  } else {
    for( int i = p; i < n; ++i ) {
      //swap( int, digits[i], digits
    }
  }
}

void print_permutations( int n ) {

}

/* == PROBLEM 10 == */

size_t search( int *data, size_t N, int value ) {
  for( size_t i = 0; i < N; ++i ) {
    if( data[i] == value ) {
      return i;
    }
  }
  return N;
}

/* binary_search: Assumes data is sorted */
size_t binary_search( int *data, size_t N, int value ) {
  size_t lo = 0, hi = N - 1;

  while( lo < hi ) {
    size_t mid = lo + ( hi - lo ) / 2;

    if( data[mid] < value ) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }

  return ( hi == lo && data[lo] == value ) ? lo : N;
}

int main(void) {
  return 0;
}

/* Notes: as we will be doing in the class, this should be compiled using
 * "gcc -std=c99 -m64 -Wall -Wextra -Wshadow -Werror -pedantic"
 * (in particular: we are coding by the C99 standard)
 */
