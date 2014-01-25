#include "list.h"
#include "apply.h"

// This works fine, but iterating over a list like this is
// fairly slow. See if you can speed it up!
void ApplyFunction::apply( List &list ) const {
  for( size_t p = 0; p < list.length(); ++p ) {
    list.value( p ) = function( list.value( p ) );
  }
}

int SquareApply::function( int x ) const {
  return x * x;
}
