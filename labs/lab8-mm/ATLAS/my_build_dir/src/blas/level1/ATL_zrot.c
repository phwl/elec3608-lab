#include "atlas_misc.h"

void ATL_zrot_xp0yp0aXbX
   (const int, TYPE*, const int, TYPE*, const int, const TYPE, const TYPE);
void Mjoin(PATLU,rot)
   (const int, TYPE*, const int, TYPE*, const int, const TYPE, const TYPE);
void ATL_zdrot(const int N, TYPE *X, const int incX, TYPE *Y, const int incY,
              const TYPE alpha, const TYPE beta)
{
   int incx=incX, incy=incY;

   if ((N > 0) && ((alpha != ATL_rone) || (beta != ATL_rzero)) )
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
      if (incx==1 && incy==1)
      {
         Mjoin(PATLU,rot)(N+N, X, 1, Y, 1, alpha, beta);
         return;
      }

      ATL_zrot_xp0yp0aXbX(N, X, incx, Y, incy, alpha, beta);
   }
}
