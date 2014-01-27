#include "list.h"
#include "reduce.h"

int ReduceFunction::reduce( const List &list ) const {
  int result = identity();
	for( auto it = list.begin(); it != list.end(); ++it ) {
    result = function( result, *it );
	}
  return result;
}

int SumReduce::function( int x, int y ) const { 
  return x + y; 
}

int ProductReduce::function( int x, int y ) const { 
  return x * y; 
}
