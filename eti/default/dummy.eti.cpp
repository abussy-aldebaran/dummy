#include "dummy.hpp"

#ifndef DUMMY_ETI_SCALAR
#define DUMMY_ETI_SCALAR double
#endif

DUMMY_ETI_SCALAR foo(DUMMY_ETI_SCALAR const x)
{
  return x;
}

template struct dummy::bar<DUMMY_ETI_SCALAR>;
