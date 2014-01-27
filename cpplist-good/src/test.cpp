#include "list.h"
#include "apply.h"
#include "reduce.h"
#include <iostream>

int main() {
	try { 
		int N = 50000;
		List list{};

		for( int i = 0; i < N; ++i ) {
			list.append( i );
		}

		//std::cout << "apply: \n";
		//list.apply( SquareApply{} ); //list.print();
		std::cout << "reduce+: " << list.reduce( SumReduce{} ) << "\n";
		return 0;
	} catch( const std::exception &e ) {
		std::cerr << e.what() << "\n";
		return 1;
	}
}
