#ifndef ATL_RESTRICT
#if defined(__STDC_VERSION__) && (__STDC_VERSION__/100 >= 1999)
   #define ATL_RESTRICT restrict
#else
   #define ATL_RESTRICT
#endif
#endif
#include "atlas_prefetch.h"

void ATL_dJIK24x24x24NT0x0x0_a1_b1
   (const int M, const int N, const int K, const double alpha, const double * ATL_RESTRICT A, const int lda, const double * ATL_RESTRICT B, const int ldb, const double beta, double * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=N, TB=T, MB=24, NB=24, KB=24, 
 * lda=0, ldb=0, ldc=0, mu=4, nu=1, ku=4, pf=1
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.3)
 */
{
   const double *stM = A + 24;
   const double *stN = B + 24;
   const double *pfA = A + lda*M;
   const int incAk = (lda);
   const int incAm = 4 - (((lda) << 4)+((lda) << 3)), incAn = -24;
   const int incBk = (ldb), incBm = -(((ldb) << 4)+((ldb) << 3));
   #define incBn 1
   #define incCm 4
   const int incCn = (ldc) - 24;
   double *pC0=C;
   const double *pA0=A;
   const double *pB0=B;
   register int k;
   register double rA0, rA1, rA2, rA3;
   register double rB0;
   register double rC0_0, rC1_0, rC2_0, rC3_0;
   do /* N-loop */
   {
      ATL_pfl1R(pfA+0);
      ATL_pfl1R(pfA+8);
      ATL_pfl1R(pfA+16);
      pfA += lda;
      do /* M-loop */
      {
         rC0_0 = *pC0;
         rC1_0 = pC0[1];
         rC2_0 = pC0[2];
         rC3_0 = pC0[3];
         for (k=0; k < 6; k++) /* easy loop to unroll */
         {
            rA0 = *pA0;
            rB0 = *pB0;
            rC0_0 += rA0 * rB0;
            rA1 = pA0[1];
            rA2 = pA0[2];
            rC1_0 += rA1 * rB0;
            rA3 = pA0[3];
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rC0_0 += rA0 * rB0;
            rA1 = pA0[1];
            rA2 = pA0[2];
            rC1_0 += rA1 * rB0;
            rA3 = pA0[3];
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rC0_0 += rA0 * rB0;
            rA1 = pA0[1];
            rA2 = pA0[2];
            rC1_0 += rA1 * rB0;
            rA3 = pA0[3];
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            pA0 += incAk;
            pB0 += incBk;
            rA0 = *pA0;
            rB0 = *pB0;
            rC0_0 += rA0 * rB0;
            rA1 = pA0[1];
            rA2 = pA0[2];
            rC1_0 += rA1 * rB0;
            rA3 = pA0[3];
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            pA0 += incAk;
            pB0 += incBk;
         }
         pA0 -= 0*incAk;
         pB0 -= 0*incBk;
         *pC0 = rC0_0;
         pC0[1] = rC1_0;
         pC0[2] = rC2_0;
         pC0[3] = rC3_0;
         pC0 += incCm;
         pA0 += incAm;
         pB0 += incBm;
      }
      while(pA0 != stM);
      pC0 += incCn;
      pA0 += incAn;
      pB0 += incBn;
   }
   while(pB0 != stN);
}
#ifdef incAm
   #undef incAm
#endif
#ifdef incAn
   #undef incAn
#endif
#ifdef incAk
   #undef incAk
#endif
#ifdef incBm
   #undef incBm
#endif
#ifdef incBn
   #undef incBn
#endif
#ifdef incBk
   #undef incBk
#endif
#ifdef incCm
   #undef incCm
#endif
#ifdef incCn
   #undef incCn
#endif
#ifdef incCk
   #undef incCk
#endif
#ifdef Mb
   #undef Mb
#endif
#ifdef Nb
   #undef Nb
#endif
#ifdef Kb
   #undef Kb
#endif