#include "atlas_misc.h"

void ATL_sscal_xp1yp0aXbX
   (const int, const SCALAR, TYPE*, const int);
void ATL_sscal_xp0yp0aXbX
   (const int, const SCALAR, TYPE*, const int);
void ATL_sset(const int, const SCALAR, TYPE*, const int);

void ATL_sscal(const int N, const SCALAR alpha, TYPE *X, const int incX)
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
         ATL_sscal_xp1yp0aXbX(N, alpha, X, incx);
      else
         ATL_sscal_xp0yp0aXbX(N, alpha, X, incx);
   }
}
