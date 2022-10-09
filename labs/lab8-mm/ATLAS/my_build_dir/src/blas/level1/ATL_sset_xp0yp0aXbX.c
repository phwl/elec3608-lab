#define ATL_USET ATL_sset_xp0yp0aXbX

#include "atlas_misc.h"
void ATL_USET(const int N, const SCALAR alpha, TYPE *X, const int incX)
{
   int i;
   for (i=N; i; i--, X += incX) *X = alpha;
}
