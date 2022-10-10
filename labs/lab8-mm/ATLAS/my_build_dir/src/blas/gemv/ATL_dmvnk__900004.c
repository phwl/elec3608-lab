#include "atlas_misc.h"
#ifndef PFYDIST
   #define PFYDIST 12
#endif
#ifndef PFXDIST
   #define PFXDIST 0
#endif
#ifndef PFADIST
   #define PFADIST 0
#endif

#if !defined(ATL_3DNow) && !defined(ATL_SSE1) && \
    (PFADIST != 0 || PFXDIST != 0 || PFYDIST != 0)
   #include "atlas_prefetch.h"
#endif

#if defined(ATL_3DNow) || defined(ATL_SSE1)
   #ifndef PFIY
      #define PFIY prefetchnta
   #endif
   #ifndef PFIX
      #define PFIX prefetchnta
   #endif
   #ifndef PFIA
      #ifdef ATL_3DNow
         #define PFIA prefetchw
      #else
         #define PFIA prefetcht0
      #endif
   #endif
#endif
/*
 * X & A are prefetched in M loop PF[A,X]DIST (in bytes) ahead
 */
#if PFADIST == 0                /* flag for no prefetch */
   #define prefA(mem)
#else
   #if defined(ATL_3DNow) || defined(ATL_SSE1)
      #define prefA(mem) __asm__ __volatile__ \
         (Mstr(PFIA) " %0" : : "m" (*(((char *)(mem))+PFADIST)))
   #else
      #if PFLVL == 2
         #define prefA(mem) ATL_pfl2W(((char*)mem)+PFADIST)
      #else
         #define prefA(mem) ATL_pfl1W(((char*)mem)+PFADIST)
      #endif
   #endif
#endif
#if PFXDIST == 0                /* flag for no prefetch */
   #define prefX(mem)
#else
   #if defined(ATL_3DNow) || defined(ATL_SSE1)
      #define prefX(mem) __asm__ __volatile__ \
         (Mstr(PFIX) " %0" : : "m" (*(((char *)(mem))+PFXDIST)))
   #else
      #if PFLVL == 2
         #define prefX(mem) ATL_pfl2R(((char*)mem)+PFXDIST)
      #else
         #define prefX(mem) ATL_pfl1R(((char*)mem)+PFXDIST)
      #endif
   #endif
#endif
/*
 * Y is prefetched in N-loop, and always fetches next NU piece
 */
#if PFYDIST == 0                /* flag for no prefetch */
   #define prefY(mem)
#else
   #if defined(ATL_3DNow) || defined(ATL_SSE1)
      #define prefY(mem) \
         __asm__ __volatile__ (Mstr(PFIY) " %0" : : "m" (*(((char *)(mem)))))
   #else
      #if PFLVL == 2
         #define prefY(mem) ATL_pfl2R(mem)
      #else
         #define prefY(mem) ATL_pfl1R(mem)
      #endif
   #endif
#endif
#ifndef ATL_CINT
   #define ATL_CINT const int
#endif
#ifndef ATL_INT
   #define ATL_INT int
#endif
/* Need to handle BETA=0 case by assigning y to zero outside of loop */
void ATL_UGEMV(ATL_CINT M, ATL_CINT N, const TYPE *A, ATL_CINT lda,
               const TYPE *X, TYPE *Y)
/*
 * 4x12 unrolled mvn_c.
 * Extracted from ATLAS/tune/blas/gemv/atlas-l2g.base
 */
{
   ATL_CINT N12=(N/12)*12, M4=(M/4)*4, lda12=lda*12;
   ATL_INT j;

   #ifdef BETA0
      for (j=0; j < M; j++)
         Y[j] = ATL_rzero;
   #endif
   for (j=N12; j; j -= 12, A += lda12, X += 12)
   {
      const double *A0=A, *A1=A0+lda, *A2=A1+lda, *A3=A2+lda, *A4=A3+lda,
                   *A5=A4+lda, *A6=A5+lda, *A7=A6+lda, *A8=A7+lda, *A9=A8+lda,
                   *A10=A9+lda, *A11=A10+lda;
      const register double x0=X[0], x1=X[1], x2=X[2], x3=X[3], x4=X[4],
                            x5=X[5], x6=X[6], x7=X[7], x8=X[8], x9=X[9],
                            x10=X[10], x11=X[11];
      ATL_INT i;
      prefY(Y+12+12-1);
      for (i=0; i < M4; i += 4)
      {
         const double a0_0=A0[i+0], a1_0=A0[i+1], a2_0=A0[i+2], a3_0=A0[i+3],
                      a0_1=A1[i+0], a1_1=A1[i+1], a2_1=A1[i+2], a3_1=A1[i+3],
                      a0_2=A2[i+0], a1_2=A2[i+1], a2_2=A2[i+2], a3_2=A2[i+3],
                      a0_3=A3[i+0], a1_3=A3[i+1], a2_3=A3[i+2], a3_3=A3[i+3],
                      a0_4=A4[i+0], a1_4=A4[i+1], a2_4=A4[i+2], a3_4=A4[i+3],
                      a0_5=A5[i+0], a1_5=A5[i+1], a2_5=A5[i+2], a3_5=A5[i+3],
                      a0_6=A6[i+0], a1_6=A6[i+1], a2_6=A6[i+2], a3_6=A6[i+3],
                      a0_7=A7[i+0], a1_7=A7[i+1], a2_7=A7[i+2], a3_7=A7[i+3],
                      a0_8=A8[i+0], a1_8=A8[i+1], a2_8=A8[i+2], a3_8=A8[i+3],
                      a0_9=A9[i+0], a1_9=A9[i+1], a2_9=A9[i+2], a3_9=A9[i+3],
                      a0_10=A10[i+0], a1_10=A10[i+1], a2_10=A10[i+2],
                      a3_10=A10[i+3], a0_11=A11[i+0], a1_11=A11[i+1],
                      a2_11=A11[i+2], a3_11=A11[i+3];
         register double y0=Y[i+0], y1=Y[i+1], y2=Y[i+2], y3=Y[i+3];

         prefX(X);
         y0 += a0_0 * x0;
         prefA(A0);
         y1 += a1_0 * x0;
         y2 += a2_0 * x0;
         y3 += a3_0 * x0;
         y0 += a0_1 * x1;
         prefA(A1);
         y1 += a1_1 * x1;
         y2 += a2_1 * x1;
         y3 += a3_1 * x1;
         y0 += a0_2 * x2;
         prefA(A2);
         y1 += a1_2 * x2;
         y2 += a2_2 * x2;
         y3 += a3_2 * x2;
         y0 += a0_3 * x3;
         prefA(A3);
         y1 += a1_3 * x3;
         y2 += a2_3 * x3;
         y3 += a3_3 * x3;
         y0 += a0_4 * x4;
         prefA(A4);
         y1 += a1_4 * x4;
         y2 += a2_4 * x4;
         y3 += a3_4 * x4;
         y0 += a0_5 * x5;
         prefA(A5);
         y1 += a1_5 * x5;
         y2 += a2_5 * x5;
         y3 += a3_5 * x5;
         y0 += a0_6 * x6;
         prefA(A6);
         y1 += a1_6 * x6;
         y2 += a2_6 * x6;
         y3 += a3_6 * x6;
         y0 += a0_7 * x7;
         prefA(A7);
         y1 += a1_7 * x7;
         y2 += a2_7 * x7;
         y3 += a3_7 * x7;
         y0 += a0_8 * x8;
         prefA(A8);
         y1 += a1_8 * x8;
         y2 += a2_8 * x8;
         y3 += a3_8 * x8;
         y0 += a0_9 * x9;
         prefA(A9);
         y1 += a1_9 * x9;
         y2 += a2_9 * x9;
         y3 += a3_9 * x9;
         y0 += a0_10 * x10;
         prefA(A10);
         y1 += a1_10 * x10;
         y2 += a2_10 * x10;
         y3 += a3_10 * x10;
         y0 += a0_11 * x11;
         prefA(A11);
         y1 += a1_11 * x11;
         y2 += a2_11 * x11;
         y3 += a3_11 * x11;
         Y[i+0] = y0;
         Y[i+1] = y1;
         Y[i+2] = y2;
         Y[i+3] = y3;
      }
      for (i=M4; i < M; i++)
      {
         const double a0_0=A0[i], a0_1=A1[i], a0_2=A2[i], a0_3=A3[i],
                      a0_4=A4[i], a0_5=A5[i], a0_6=A6[i], a0_7=A7[i],
                      a0_8=A8[i], a0_9=A9[i], a0_10=A10[i], a0_11=A11[i];
         register double y0 = Y[i];

         y0 += a0_0 * x0;
         y0 += a0_1 * x1;
         y0 += a0_2 * x2;
         y0 += a0_3 * x3;
         y0 += a0_4 * x4;
         y0 += a0_5 * x5;
         y0 += a0_6 * x6;
         y0 += a0_7 * x7;
         y0 += a0_8 * x8;
         y0 += a0_9 * x9;
         y0 += a0_10 * x10;
         y0 += a0_11 * x11;
         Y[i] = y0;
      }
   }
/*
 * Do remaining columns with NU=1 cleanup
 */
   for (j=N-N12; j; j--, A += lda, X++)
   {
      const double *A0=A;
      const register double x0=X[0];
      ATL_INT i;
      prefY(Y+1+1-1);
      for (i=0; i < M4; i += 4)
      {
         const double a0_0=A0[i+0], a1_0=A0[i+1], a2_0=A0[i+2], a3_0=A0[i+3];
         register double y0=Y[i+0], y1=Y[i+1], y2=Y[i+2], y3=Y[i+3];

         prefX(X);
         y0 += a0_0 * x0;
         prefA(A0);
         y1 += a1_0 * x0;
         y2 += a2_0 * x0;
         y3 += a3_0 * x0;
         Y[i+0] = y0;
         Y[i+1] = y1;
         Y[i+2] = y2;
         Y[i+3] = y3;
      }
      for (i=M4; i < M; i++)
      {
         const double a0_0=A0[i];
         register double y0 = Y[i];

         y0 += a0_0 * x0;
         Y[i] = y0;
      }
   }
}
