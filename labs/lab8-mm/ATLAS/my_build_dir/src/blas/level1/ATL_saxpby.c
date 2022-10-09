#include "atlas_misc.h"

void ATL_saxpby_xp1yp1a1bX
   (const int, const SCALAR, const TYPE*, const int, const SCALAR, TYPE*, const int);
void ATL_saxpby_xp0yp0aXbX
   (const int, const SCALAR, const TYPE*, const int, const SCALAR, TYPE*, const int);
void ATL_saxpy(const int, const SCALAR, const TYPE*, const int, TYPE*, const int);
void ATL_scpsc(const int, const SCALAR, const TYPE*, const int, TYPE*, const int);
void ATL_sscal(const int, const SCALAR, TYPE*, const int);

void ATL_saxpby(const int N, const SCALAR alpha, const TYPE *X, const int incX,
               const SCALAR beta, TYPE *Y, const int incY)
{
   int incx=incX, incy=incY;

   if (N > 0)
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
      if (beta == ATL_rone)
      {
         ATL_saxpy(N, alpha, X, incx, Y, incy);
         return;
      }
      else if (beta == ATL_rzero)
      {
         ATL_scpsc(N, alpha, X, incx, Y, incy);
         return;
      }
      else if (alpha == ATL_rzero)
      {
         ATL_sscal(N, beta, Y, incy);
         return;
      }
      else if (alpha == ATL_rone)
      {
         if (incx == 1 && incy == 1)
         {
            ATL_saxpby_xp1yp1a1bX(N, alpha, X, incx, beta, Y, incy);
            return;
         }
      }

      ATL_saxpby_xp0yp0aXbX(N, alpha, X, incx, beta, Y, incy);
   }
}
