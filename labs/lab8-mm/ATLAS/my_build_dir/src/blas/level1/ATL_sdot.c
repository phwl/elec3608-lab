#include "atlas_misc.h"

TYPE ATL_sdot_xp1yp1aXbX
   (const int, const TYPE*, const int, const TYPE*, const int);
TYPE ATL_sdot_xp0yp0aXbX
   (const int, const TYPE*, const int, const TYPE*, const int);

TYPE ATL_sdot(const int N, const TYPE *X, const int incX,
              const TYPE *Y, const int incY)
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
      else if (!incX || !incY) return(ATL_rzero);
L1:

      if (incx == 1 && incy == 1)
         return(ATL_sdot_xp1yp1aXbX(N, X, incx, Y, incy));
      else
         return(ATL_sdot_xp0yp0aXbX(N, X, incx, Y, incy));
   }
   else return(ATL_rzero);
}
