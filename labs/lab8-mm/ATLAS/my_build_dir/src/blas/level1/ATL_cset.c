#include "atlas_misc.h"

void ATL_cset_xp0yp0aXbX
   (const int, const SCALAR, TYPE*, const int);
void Mjoin(PATLU,set)
   (const int, const TYPE, TYPE*, const int);

void ATL_cset(const int N, const SCALAR alpha, TYPE *X, const int incX)
{
   int incx;

   if (N > 0)
   {
      if (incX > 0) incx = incX;
      else if (incX < 0)
      {
         X += ((N-1)SHIFT) * incX;
         incx = -incX;
      }
      else return;
      if (incx==1 && alpha[1] == *alpha)
      {
         Mjoin(PATLU,set)(N+N, *alpha, X, 1);
         return;
      }
      ATL_cset_xp0yp0aXbX(N, alpha, X, incx);
   }
}

void ATL_czero(const int N, TYPE *X, const int incX)
{
   TYPE zero[2] = {ATL_rzero, ATL_rzero};
   ATL_cset(N, zero, X, incX);
}
