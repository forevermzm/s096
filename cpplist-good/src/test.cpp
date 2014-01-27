#include "list.h"
#include "apply.h"
#include "reduce.h"
#include <iostream>

int main() {
  try { 
    int N = 100;
    List olist{};

    for( int i = 0; i < N; ++i ) {
      olist.append( i );
    }

    List olist2{};
    olist2.append( 5 );
    olist2 = olist;
    List list{olist2};

    std::cout << "value(0)=" << list.value( 0 ) << '\n';
    std::cout << "value(1)=" << list.value( 1 ) << '\n';
    std::cout << "value(" << list.length() - 1 << ")=" << list.value( list.length() - 1 ) << '\n';
    list = list;
    list.apply( SquareApply{} );
    std::cout << "apply^2 & reduce+: " << list.reduce( SumReduce{} ) << "\n";
    return 0;
  } catch( const std::exception &e ) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
