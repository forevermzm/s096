#include <stdio.h>
#include <math.h>
#include <stdbool.h>

union float_bits {
  float f;
  unsigned int bits;
};

void print_binary( unsigned int num, int num_digits ) {
  for( unsigned int mask = 1 << ( num_digits - 1 ); mask > 0; mask >>= 1 ) {
    if( mask & num ) {
      printf( "1" );
    } else {
      printf( "0" );
    }
  }
}

void print_float( float f ) {
  union float_bits t; t.f = f;

  unsigned int sign_bit = t.bits & 0x80000000u,
               exponent = t.bits & 0x7f000000u,
               mantissa = t.bits & 0x00ffffffu;

  print_binary( sign_bit >> 31, 1 );
  printf( " | " );
  print_binary( exponent >> 23, 8 );
  printf( " | " );
  print_binary( mantissa, 23 );
  printf( "\n" );
}

void usage( char *path ) {
  printf( "Usage: %s [FLOAT]\n", path );
}

int main( int argc, char **argv ) {
  if( argc != 2 ) {
    usage( argv[0] ); 
    return 1;
  }

  float value;
  sscanf( argv[1], "%f", &value );

  print_float( value );
  return 0;
}
