#include "list.h"
#include "apply.h"

void ApplyFunction::apply( List &list ) const {
  for( size_t p = 0; p < list.length(); ++p ) {
    list.value( p ) = function( list.value( p ) );
  }
}

int SquareApply::function( int x ) const {
  return x * x;
}
