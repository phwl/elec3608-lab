#include "atlas_misc.h"
#ifndef PFYDIST
   #define PFYDIST 4
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
void ATL_UGEMV(ATL_CINT M, ATL_CINT N, const TYPE *A, ATL_CINT lda,
               const TYPE *X, TYPE *Y)
/*
 * 48x4 unrolled mvt_c.
 * Extracted from ATLAS/tune/blas/gemv/atlas-l2g.base
 */
{
   ATL_CINT N4=(N/4)*4, M48=(M/48)*48, lda4=lda*4;
   ATL_INT j;

   for (j=N4; j; j -= 4, A += lda4, Y += 4)
   {
      const double *A0=A, *A1=A0+lda, *A2=A1+lda, *A3=A2+lda;
      register double y0=ATL_rzero, y1=ATL_rzero, y2=ATL_rzero, y3=ATL_rzero;
      ATL_INT i;
      prefY(Y+4+4-1);
      for (i=0; i < M48; i += 48)
      {
         const register double x0=X[i+0], x1=X[i+1], x2=X[i+2], x3=X[i+3],
                               x4=X[i+4], x5=X[i+5], x6=X[i+6], x7=X[i+7],
                               x8=X[i+8], x9=X[i+9], x10=X[i+10], x11=X[i+11],
                               x12=X[i+12], x13=X[i+13], x14=X[i+14],
                               x15=X[i+15], x16=X[i+16], x17=X[i+17],
                               x18=X[i+18], x19=X[i+19], x20=X[i+20],
                               x21=X[i+21], x22=X[i+22], x23=X[i+23],
                               x24=X[i+24], x25=X[i+25], x26=X[i+26],
                               x27=X[i+27], x28=X[i+28], x29=X[i+29],
                               x30=X[i+30], x31=X[i+31], x32=X[i+32],
                               x33=X[i+33], x34=X[i+34], x35=X[i+35],
                               x36=X[i+36], x37=X[i+37], x38=X[i+38],
                               x39=X[i+39], x40=X[i+40], x41=X[i+41],
                               x42=X[i+42], x43=X[i+43], x44=X[i+44],
                               x45=X[i+45], x46=X[i+46], x47=X[i+47];

         prefX(X);
         y0 += A0[i+0] * x0;
         prefA(A0);
         y1 += A1[i+0] * x0;
         prefA(A1);
         y2 += A2[i+0] * x0;
         prefA(A2);
         y3 += A3[i+0] * x0;
         prefA(A3);
         y0 += A0[i+1] * x1;
         y1 += A1[i+1] * x1;
         y2 += A2[i+1] * x1;
         y3 += A3[i+1] * x1;
         y0 += A0[i+2] * x2;
         y1 += A1[i+2] * x2;
         y2 += A2[i+2] * x2;
         y3 += A3[i+2] * x2;
         y0 += A0[i+3] * x3;
         y1 += A1[i+3] * x3;
         y2 += A2[i+3] * x3;
         y3 += A3[i+3] * x3;
         y0 += A0[i+4] * x4;
         y1 += A1[i+4] * x4;
         y2 += A2[i+4] * x4;
         y3 += A3[i+4] * x4;
         y0 += A0[i+5] * x5;
         y1 += A1[i+5] * x5;
         y2 += A2[i+5] * x5;
         y3 += A3[i+5] * x5;
         y0 += A0[i+6] * x6;
         y1 += A1[i+6] * x6;
         y2 += A2[i+6] * x6;
         y3 += A3[i+6] * x6;
         y0 += A0[i+7] * x7;
         y1 += A1[i+7] * x7;
         y2 += A2[i+7] * x7;
         y3 += A3[i+7] * x7;
         y0 += A0[i+8] * x8;
         prefA(A0);
         y1 += A1[i+8] * x8;
         prefA(A1);
         y2 += A2[i+8] * x8;
         prefA(A2);
         y3 += A3[i+8] * x8;
         prefA(A3);
         y0 += A0[i+9] * x9;
         y1 += A1[i+9] * x9;
         y2 += A2[i+9] * x9;
         y3 += A3[i+9] * x9;
         y0 += A0[i+10] * x10;
         y1 += A1[i+10] * x10;
         y2 += A2[i+10] * x10;
         y3 += A3[i+10] * x10;
         y0 += A0[i+11] * x11;
         y1 += A1[i+11] * x11;
         y2 += A2[i+11] * x11;
         y3 += A3[i+11] * x11;
         y0 += A0[i+12] * x12;
         y1 += A1[i+12] * x12;
         y2 += A2[i+12] * x12;
         y3 += A3[i+12] * x12;
         y0 += A0[i+13] * x13;
         y1 += A1[i+13] * x13;
         y2 += A2[i+13] * x13;
         y3 += A3[i+13] * x13;
         y0 += A0[i+14] * x14;
         y1 += A1[i+14] * x14;
         y2 += A2[i+14] * x14;
         y3 += A3[i+14] * x14;
         y0 += A0[i+15] * x15;
         y1 += A1[i+15] * x15;
         y2 += A2[i+15] * x15;
         y3 += A3[i+15] * x15;
         y0 += A0[i+16] * x16;
         prefA(A0);
         y1 += A1[i+16] * x16;
         prefA(A1);
         y2 += A2[i+16] * x16;
         prefA(A2);
         y3 += A3[i+16] * x16;
         prefA(A3);
         y0 += A0[i+17] * x17;
         y1 += A1[i+17] * x17;
         y2 += A2[i+17] * x17;
         y3 += A3[i+17] * x17;
         y0 += A0[i+18] * x18;
         y1 += A1[i+18] * x18;
         y2 += A2[i+18] * x18;
         y3 += A3[i+18] * x18;
         y0 += A0[i+19] * x19;
         y1 += A1[i+19] * x19;
         y2 += A2[i+19] * x19;
         y3 += A3[i+19] * x19;
         y0 += A0[i+20] * x20;
         y1 += A1[i+20] * x20;
         y2 += A2[i+20] * x20;
         y3 += A3[i+20] * x20;
         y0 += A0[i+21] * x21;
         y1 += A1[i+21] * x21;
         y2 += A2[i+21] * x21;
         y3 += A3[i+21] * x21;
         y0 += A0[i+22] * x22;
         y1 += A1[i+22] * x22;
         y2 += A2[i+22] * x22;
         y3 += A3[i+22] * x22;
         y0 += A0[i+23] * x23;
         y1 += A1[i+23] * x23;
         y2 += A2[i+23] * x23;
         y3 += A3[i+23] * x23;
         y0 += A0[i+24] * x24;
         prefA(A0);
         y1 += A1[i+24] * x24;
         prefA(A1);
         y2 += A2[i+24] * x24;
         prefA(A2);
         y3 += A3[i+24] * x24;
         prefA(A3);
         y0 += A0[i+25] * x25;
         y1 += A1[i+25] * x25;
         y2 += A2[i+25] * x25;
         y3 += A3[i+25] * x25;
         y0 += A0[i+26] * x26;
         y1 += A1[i+26] * x26;
         y2 += A2[i+26] * x26;
         y3 += A3[i+26] * x26;
         y0 += A0[i+27] * x27;
         y1 += A1[i+27] * x27;
         y2 += A2[i+27] * x27;
         y3 += A3[i+27] * x27;
         y0 += A0[i+28] * x28;
         y1 += A1[i+28] * x28;
         y2 += A2[i+28] * x28;
         y3 += A3[i+28] * x28;
         y0 += A0[i+29] * x29;
         y1 += A1[i+29] * x29;
         y2 += A2[i+29] * x29;
         y3 += A3[i+29] * x29;
         y0 += A0[i+30] * x30;
         y1 += A1[i+30] * x30;
         y2 += A2[i+30] * x30;
         y3 += A3[i+30] * x30;
         y0 += A0[i+31] * x31;
         y1 += A1[i+31] * x31;
         y2 += A2[i+31] * x31;
         y3 += A3[i+31] * x31;
         y0 += A0[i+32] * x32;
         prefA(A0);
         y1 += A1[i+32] * x32;
         prefA(A1);
         y2 += A2[i+32] * x32;
         prefA(A2);
         y3 += A3[i+32] * x32;
         prefA(A3);
         y0 += A0[i+33] * x33;
         y1 += A1[i+33] * x33;
         y2 += A2[i+33] * x33;
         y3 += A3[i+33] * x33;
         y0 += A0[i+34] * x34;
         y1 += A1[i+34] * x34;
         y2 += A2[i+34] * x34;
         y3 += A3[i+34] * x34;
         y0 += A0[i+35] * x35;
         y1 += A1[i+35] * x35;
         y2 += A2[i+35] * x35;
         y3 += A3[i+35] * x35;
         y0 += A0[i+36] * x36;
         y1 += A1[i+36] * x36;
         y2 += A2[i+36] * x36;
         y3 += A3[i+36] * x36;
         y0 += A0[i+37] * x37;
         y1 += A1[i+37] * x37;
         y2 += A2[i+37] * x37;
         y3 += A3[i+37] * x37;
         y0 += A0[i+38] * x38;
         y1 += A1[i+38] * x38;
         y2 += A2[i+38] * x38;
         y3 += A3[i+38] * x38;
         y0 += A0[i+39] * x39;
         y1 += A1[i+39] * x39;
         y2 += A2[i+39] * x39;
         y3 += A3[i+39] * x39;
         y0 += A0[i+40] * x40;
         prefA(A0);
         y1 += A1[i+40] * x40;
         prefA(A1);
         y2 += A2[i+40] * x40;
         prefA(A2);
         y3 += A3[i+40] * x40;
         prefA(A3);
         y0 += A0[i+41] * x41;
         y1 += A1[i+41] * x41;
         y2 += A2[i+41] * x41;
         y3 += A3[i+41] * x41;
         y0 += A0[i+42] * x42;
         y1 += A1[i+42] * x42;
         y2 += A2[i+42] * x42;
         y3 += A3[i+42] * x42;
         y0 += A0[i+43] * x43;
         y1 += A1[i+43] * x43;
         y2 += A2[i+43] * x43;
         y3 += A3[i+43] * x43;
         y0 += A0[i+44] * x44;
         y1 += A1[i+44] * x44;
         y2 += A2[i+44] * x44;
         y3 += A3[i+44] * x44;
         y0 += A0[i+45] * x45;
         y1 += A1[i+45] * x45;
         y2 += A2[i+45] * x45;
         y3 += A3[i+45] * x45;
         y0 += A0[i+46] * x46;
         y1 += A1[i+46] * x46;
         y2 += A2[i+46] * x46;
         y3 += A3[i+46] * x46;
         y0 += A0[i+47] * x47;
         y1 += A1[i+47] * x47;
         y2 += A2[i+47] * x47;
         y3 += A3[i+47] * x47;
      }
      for (i=M48; i < M; i++)
      {
         const register double x0 = X[i];
         y0 += A0[i] * x0;
         y1 += A1[i] * x0;
         y2 += A2[i] * x0;
         y3 += A3[i] * x0;
      }
      #ifdef BETA0
         Y[0] = y0;
         Y[1] = y1;
         Y[2] = y2;
         Y[3] = y3;
      #else
         Y[0] += y0;
         Y[1] += y1;
         Y[2] += y2;
         Y[3] += y3;
      #endif
   }
/*
 * Do remaining columns with NU=1 cleanup
 */
   for (j=N-N4; j; j--, A += lda, Y++)
   {
      const double *A0=A;
      register double y0=ATL_rzero;
      ATL_INT i;
      prefY(Y+1+1-1);
      for (i=0; i < M48; i += 48)
      {
         const register double x0=X[i+0], x1=X[i+1], x2=X[i+2], x3=X[i+3],
                               x4=X[i+4], x5=X[i+5], x6=X[i+6], x7=X[i+7],
                               x8=X[i+8], x9=X[i+9], x10=X[i+10], x11=X[i+11],
                               x12=X[i+12], x13=X[i+13], x14=X[i+14],
                               x15=X[i+15], x16=X[i+16], x17=X[i+17],
                               x18=X[i+18], x19=X[i+19], x20=X[i+20],
                               x21=X[i+21], x22=X[i+22], x23=X[i+23],
                               x24=X[i+24], x25=X[i+25], x26=X[i+26],
                               x27=X[i+27], x28=X[i+28], x29=X[i+29],
                               x30=X[i+30], x31=X[i+31], x32=X[i+32],
                               x33=X[i+33], x34=X[i+34], x35=X[i+35],
                               x36=X[i+36], x37=X[i+37], x38=X[i+38],
                               x39=X[i+39], x40=X[i+40], x41=X[i+41],
                               x42=X[i+42], x43=X[i+43], x44=X[i+44],
                               x45=X[i+45], x46=X[i+46], x47=X[i+47];

         prefX(X);
         y0 += A0[i+0] * x0;
         prefA(A0);
         y0 += A0[i+1] * x1;
         y0 += A0[i+2] * x2;
         y0 += A0[i+3] * x3;
         y0 += A0[i+4] * x4;
         y0 += A0[i+5] * x5;
         y0 += A0[i+6] * x6;
         y0 += A0[i+7] * x7;
         y0 += A0[i+8] * x8;
         prefA(A0);
         y0 += A0[i+9] * x9;
         y0 += A0[i+10] * x10;
         y0 += A0[i+11] * x11;
         y0 += A0[i+12] * x12;
         y0 += A0[i+13] * x13;
         y0 += A0[i+14] * x14;
         y0 += A0[i+15] * x15;
         y0 += A0[i+16] * x16;
         prefA(A0);
         y0 += A0[i+17] * x17;
         y0 += A0[i+18] * x18;
         y0 += A0[i+19] * x19;
         y0 += A0[i+20] * x20;
         y0 += A0[i+21] * x21;
         y0 += A0[i+22] * x22;
         y0 += A0[i+23] * x23;
         y0 += A0[i+24] * x24;
         prefA(A0);
         y0 += A0[i+25] * x25;
         y0 += A0[i+26] * x26;
         y0 += A0[i+27] * x27;
         y0 += A0[i+28] * x28;
         y0 += A0[i+29] * x29;
         y0 += A0[i+30] * x30;
         y0 += A0[i+31] * x31;
         y0 += A0[i+32] * x32;
         prefA(A0);
         y0 += A0[i+33] * x33;
         y0 += A0[i+34] * x34;
         y0 += A0[i+35] * x35;
         y0 += A0[i+36] * x36;
         y0 += A0[i+37] * x37;
         y0 += A0[i+38] * x38;
         y0 += A0[i+39] * x39;
         y0 += A0[i+40] * x40;
         prefA(A0);
         y0 += A0[i+41] * x41;
         y0 += A0[i+42] * x42;
         y0 += A0[i+43] * x43;
         y0 += A0[i+44] * x44;
         y0 += A0[i+45] * x45;
         y0 += A0[i+46] * x46;
         y0 += A0[i+47] * x47;
      }
      for (i=M48; i < M; i++)
      {
         const register double x0 = X[i];
         y0 += A0[i] * x0;
      }
      #ifdef BETA0
         Y[0] = y0;
      #else
         Y[0] += y0;
      #endif
   }
}
