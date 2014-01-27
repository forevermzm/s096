#include "list.h"
#include "apply.h"

void ApplyFunction::apply( List &list ) const {
	for( auto it = list.begin(); it != list.end(); ++it ) {
    *it = function( *it );
  }
}

int SquareApply::function( int x ) const {
  return x * x;
}
