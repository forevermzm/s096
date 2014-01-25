/*
PROG: loop
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 128

void encrypt( char *string ) {
  /* This is the encryption function;
   * Fill this out!
   */
}

void resize_string( char **str, size_t chars_to_read ) {
  if( *str == NULL ) {
    *str = malloc( chars_to_read );
  } else {
    char *tmp = realloc( *str, chars_to_read );
    // If realloc failed, return str as before the failled realloc
    if( tmp == NULL ) {
      fprintf( stderr, "Failed realloc to size %zu.\n", chars_to_read );
    } else {
      *str = tmp;
    }
  }
}

/* Safe way of reading the contents of 'input'
 * into a string 'str'. Your job is to read and
 * understand how this works and why is it safe,
 * and then fill out the body of the while() loop.
 * Feel free to use the resize_string function
 * provided above.
 */
size_t getstr( char **str, FILE *input ) {
  size_t chars_to_read = BLOCK_SIZE;
  size_t length = 0;

  // If str already exists, we'll append to it by making
  if( *str != NULL ) {
    length = strlen( *str );
    while( chars_to_read < length ) {
      chars_to_read <<= 1;
    }
  }

  resize_string( str, chars_to_read << 1 );

  // Try to read in the number of 'chars_to_read'; store # of 
  // chars actually read from input in 'chars'
  size_t chars = 0;
  while( ( chars = fread( *str + length, 1, chars_to_read, input ) ) ) {
    // If we were successful, double the number of characters to read
    // and repeat (doubling means there will be fewer memory reallocs)
    length += chars;
    if( chars == chars_to_read ) {
      chars_to_read <<= 1;
      resize_string( str, chars_to_read << 1 );
    } else {
      // we're at the end of the file
      break;
    }
  }

  // Add a terminating '\0' and resize to save space
  (*str)[length] = '\0';
  char *tmp = realloc( *str, length + 1 );

  if( tmp != NULL ) {
    *str = tmp;
  }

  return length;
}

int main(void) {
  FILE *input = fopen( "loop.in", "r" );
  char *string = NULL;
  size_t length = getstr( &string, input );
  fclose( input );

  free( string );
  //FILE *output = fopen( "loop.out", "w" );
  //fclose( output );
  return 0;
}
