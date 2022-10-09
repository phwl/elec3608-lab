#include "atlas_misc.h"

void ATL_zaxpby_xp0yp0aXbX
   (const int, const SCALAR, const TYPE*, const int, const SCALAR, TYPE*, const int);
void ATL_zaxpy(const int, const SCALAR, const TYPE*, const int, TYPE*, const int);
void ATL_zcpsc(const int, const SCALAR, const TYPE*, const int, TYPE*, const int);
void ATL_zscal(const int, const SCALAR, TYPE*, const int);
void Mjoin(PATLU,axpby)
   (const int, const TYPE, const TYPE*, const int, const TYPE, TYPE*, const int);

void ATL_zaxpby(const int N, const SCALAR alpha, const TYPE *X, const int incX,
               const SCALAR beta, TYPE *Y, const int incY)
{
   int incx=incX, incy=incY;
   const TYPE ralpha=(*alpha), ialpha=alpha[1], rbeta=(*beta), ibeta=beta[1];

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
      if (ibeta == ATL_rzero) /* real beta */
      {
         if (rbeta == ATL_rone)
         {
            ATL_zaxpy(N, alpha, X, incx, Y, incy);
            return;
         }
         else if (rbeta == ATL_rzero)
         {
            ATL_zcpsc(N, alpha, X, incx, Y, incy);
            return;
         }
         else if (ialpha == ATL_rzero) /* both scalars real */
         {
            if (incX == 1 && incY == 1)
            {
               Mjoin(PATLU,axpby)(N+N, ralpha, X, 1, rbeta, Y, 1);
               return;
            }
         }
      }
      else if (ialpha == ATL_rzero) /* real alpha, cplx beta */
      {
         if (ralpha == ATL_rzero)
         {
            ATL_zscal(N, beta, Y, incy);
            return;
         }
      }

      ATL_zaxpby_xp0yp0aXbX(N, alpha, X, incx, beta, Y, incy);
   }
}
