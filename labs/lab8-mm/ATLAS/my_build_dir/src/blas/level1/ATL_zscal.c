#include "atlas_misc.h"

void ATL_zscal_xp1yp0aXbX
   (const int, const SCALAR, TYPE*, const int);
void ATL_zscal_xp0yp0aXbX
   (const int, const SCALAR, TYPE*, const int);
void ATL_zset(const int, const SCALAR, TYPE*, const int);
void Mjoin(PATLU,scal)
   (const int, const TYPE, TYPE*, const int);

void ATL_zscal(const int N, const SCALAR alpha, TYPE *X, const int incX)
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
      if (incx==1 && alpha[1] == ATL_rzero)
      {
         Mjoin(PATLU,scal)(N+N, *alpha, X, 1);
         return;
      }
      if (incx == 1)
         ATL_zscal_xp1yp0aXbX(N, alpha, X, incx);
      else
         ATL_zscal_xp0yp0aXbX(N, alpha, X, incx);
   }
}
