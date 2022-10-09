#include "atlas_misc.h"

void ATL_dset_xp1yp0aXbX
   (const int, const SCALAR, TYPE*, const int);
void ATL_dset_xp0yp0aXbX
   (const int, const SCALAR, TYPE*, const int);
void Mjoin(PATLU,set)
   (const int, const TYPE, TYPE*, const int);

void ATL_dset(const int N, const SCALAR alpha, TYPE *X, const int incX)
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
      if (incx == 1)
         ATL_dset_xp1yp0aXbX(N, alpha, X, incx);
      else
         ATL_dset_xp0yp0aXbX(N, alpha, X, incx);
   }
}

void ATL_dzero(const int N, TYPE *X, const int incX)
{
   ATL_dset(N, ATL_rzero, X, incX);
}
