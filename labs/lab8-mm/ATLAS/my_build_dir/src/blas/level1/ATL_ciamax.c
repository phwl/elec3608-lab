#include "atlas_misc.h"

int ATL_ciamax_xp1yp0aXbX(const int, const TYPE*, const int);
int ATL_ciamax_xp0yp0aXbX(const int, const TYPE*, const int);

int ATL_icamax(const int N, const TYPE *X, const int incX)
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
      else return(0);
      if (incx == 1)
         return(ATL_ciamax_xp1yp0aXbX(N, X, incx));
      else
         return(ATL_ciamax_xp0yp0aXbX(N, X, incx));
   }
   return(0);
}
