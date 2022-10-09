#include "atlas_misc.h"

void ATL_ccpsc_xp0yp0aXbX
   (const int, const SCALAR, const TYPE*, const int, TYPE*, const int);
void ATL_czero(const int, TYPE*, const int);
void ATL_ccopy(const int, const TYPE*, const int, TYPE*, const int);
void Mjoin(PATLU,cpsc)
   (const int, const TYPE, const TYPE*, const int, TYPE*, const int);

void ATL_ccpsc(const int N, const SCALAR alpha, const TYPE *X, const int incX,
               TYPE *Y, const int incY)
{
   int incx=incX, incy=incY;

   if (N > 0 && !SCALAR_IS_ZERO(alpha) && !SCALAR_IS_ONE(alpha))
   {
/*
 *    Manipulate incX and inxY such that:
 *    -  Both are positive
 *    -  else if incX or incY has abs()=1, make it positive
 *    -  if both abs(inc) are 1, or if neither, make incY positive
 */
      if (incX >= 0 && incY >= 0) goto L1;
      else if (incY < 0)
      {
         if (incX < 0) /* make both positive */
         {
            incx = -incX;
            incy = -incY;
            X += ((N-1)SHIFT)*incX;
            Y += ((N-1)SHIFT)*incY;
         }
         else if (incX != 1 || incY == -1)
         {
            incy = -incY;
            Y += ((N-1)SHIFT)*incY;
            incx = -incX;
            X += ((N-1)SHIFT)*incX;
         }
      }
      else if (incX == -1 && incY != 1)
      {
         incx = 1;
         X -= ((N-1)SHIFT);
         incy = -incY;
         Y += ((N-1)SHIFT)*incY;
      }
      else if (!incX || !incY) return;
L1:
      if (incx==1 && incy==1 && alpha[1] == ATL_rzero)
      {
         Mjoin(PATLU,cpsc)(N+N, *alpha, X, 1, Y, 1);
         return;
      }

      ATL_ccpsc_xp0yp0aXbX(N, alpha, X, incx, Y, incy);
   }
   else if ( SCALAR_IS_ONE(alpha) ) ATL_ccopy(N, X, incX, Y, incY);
   else if ( SCALAR_IS_ZERO(alpha) ) ATL_czero(N, Y, incY);
}
