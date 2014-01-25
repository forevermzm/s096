#include "externals.h"
#include "internals.h"

int Externals::data1() const {
  return pimpl->data1();
}

double Externals::thing() const { 
  return pimpl->thing();
}

int Externals::item( size_t i ) const { 
  return pimpl->item( i ); 
}
