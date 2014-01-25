/*
PROG: loop
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 128

void reverse( char *start, char *end ) {
  for( char *s = start, *e = end - 1; s < e; ++s, --e ) {
    char c = *e;
    *e = *s;
    *s = c;
  }
}

void encrypt( char *string, size_t length ) {
  /* This is the encryption function;
   * Fill this out!
   */
  if( length <= 1 ) {
    return;
  }

  size_t k = length / 2;

  reverse( string, string + k );
  encrypt( string, k );

  reverse( string + k, string + length );
  encrypt( string + k, length - k );
}

/* Resize a string using realloc;
 * if realloc fails, do not change the string.
 */
void resize_string( char **str, size_t newsize ) {
  if( *str == NULL ) {
    *str = malloc( newsize );
  } else {
    char *tmp = realloc( *str, newsize );
    // If realloc failed, do not change str
    if( tmp == NULL ) {
      fprintf( stderr, "Failed realloc to size %zu.\n", newsize );
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
 *
 * Parameters:
 *   str: pointer to string that will be filled
 *        up; if the string is NULL, it will be
 *        created, else it'll be appended to.
 *   input: input FILE pointer
 * Returns:
 *   length of new string str
 */
size_t getstr( char **str, FILE *input ) {
  size_t chars_to_read = BLOCK_SIZE;
  size_t length = 0;

  // If str already exists, we'll append to the end
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
    /* What you need to do:
     * We've just read # 'chars' into str. If we're at the end of
     * the file, we should exit the loop. Otherwise, we should
     * resize the string to read in more chars. Certain methods
     * will be faster than others, so try out a couple of different
     * ways of doing this and pick the fastest one. DO NOT LEAK MEMORY!
     */
    length += chars;
    if( chars == chars_to_read ) {
      chars_to_read <<= 1;
      resize_string( str, chars_to_read << 1 );
    } else {
      // we're at the end of the file
      break;
    }
  }

  // Add a terminating '\0' (removing the final newline)
  // and resize to save space
  if( length > 0 ) {
    length = length - 1;
    (*str)[length] = '\0';
    char *tmp = realloc( *str, length + 1 );
    if( tmp != NULL ) {
      *str = tmp;
    }
  }
  return length;
}

int main(void) {
  FILE *input = fopen( "loop.in", "r" );
  if( input == NULL ) {
    fprintf( stderr, "Could not open loop.in.\n" );
    exit( EXIT_FAILURE );
  }
  char *string = NULL;
  size_t length = getstr( &string, input );
  fclose( input );

  encrypt( string, length );

  FILE *output = fopen( "loop.out", "w" );
  fprintf( output, "%zu\n", length );
  fprintf( output, "%s\n", string );
  fclose( output );

  free( string );
  return 0;
}
