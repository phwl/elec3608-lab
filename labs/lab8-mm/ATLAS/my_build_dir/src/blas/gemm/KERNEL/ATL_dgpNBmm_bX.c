#ifdef ATL_UCLEANN
#define ATL_dJIK56x0x56TN56x56x0_a1_bX ATL_dgpNBmm_bX
#else
#define ATL_dJIK56x0x56TN56x56x0_a1_bX ATL_dpNBmm_bX
#endif

#ifndef ATL_RESTRICT
#if defined(__STDC_VERSION__) && (__STDC_VERSION__/100 >= 1999)
   #define ATL_RESTRICT restrict
#else
   #define ATL_RESTRICT
#endif
#endif
#include "atlas_prefetch.h"

void ATL_dJIK56x0x56TN56x56x0_a1_bX
   (const int M, const int N, const int K, const double alpha, const double * ATL_RESTRICT A, const int lda, const double * ATL_RESTRICT B, const int ldb, const double beta, double * ATL_RESTRICT C, const int ldc)
/*
 * matmul with TA=T, TB=N, MB=56, NB=0, KB=56, 
 * lda=56, ldb=56, ldc=0, mu=4, nu=1, ku=24, pf=1
 * Generated by ATLAS/tune/blas/gemm/emit_mm.c (3.10.3)
 */
{
   #define Nb N
   const double *stM = A + 3136;
   const double *stN = B + (56*(Nb));
   const double *pfA = stM;
   const int incPFA0 = (((int)(stM - A))*4*1)/(56*N*sizeof(double));
   const int incPFA = (1 > incPFA0) ? 1 : incPFA0;
   #define incAk 24
   const int incAm = 176, incAn = -3136;
   #define incBk 24
   const int incBm = -48, incBn = 56;
   #define incCm 4
   const int incCn = (ldc) - 56;
   double *pC0=C;
   const double *pA0=A;
   const double *pB0=B;
   register int k;
   register double rA0, rA1, rA2, rA3;
   register double rB0;
   register double rC0_0, rC1_0, rC2_0, rC3_0;
   do /* N-loop */
   {
      do /* M-loop */
      {
         ATL_pfl1R(pfA);
         pfA += incPFA;
         rA0 = beta;
         rC0_0 = *pC0;
         rC0_0 *= rA0;
         rC1_0 = pC0[1];
         rC1_0 *= rA0;
         rC2_0 = pC0[2];
         rC2_0 *= rA0;
         rC3_0 = pC0[3];
         rC3_0 *= rA0;
         for (k=0; k < 2; k++) /* easy loop to unroll */
         {
            rA0 = *pA0;
            rB0 = *pB0;
            rA1 = pA0[56];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[112];
            rA3 = pA0[168];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[1];
            rB0 = pB0[1];
            rA1 = pA0[57];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[113];
            rA3 = pA0[169];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[2];
            rB0 = pB0[2];
            rA1 = pA0[58];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[114];
            rA3 = pA0[170];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[3];
            rB0 = pB0[3];
            rA1 = pA0[59];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[115];
            rA3 = pA0[171];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[4];
            rB0 = pB0[4];
            rA1 = pA0[60];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[116];
            rA3 = pA0[172];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[5];
            rB0 = pB0[5];
            rA1 = pA0[61];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[117];
            rA3 = pA0[173];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[6];
            rB0 = pB0[6];
            rA1 = pA0[62];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[118];
            rA3 = pA0[174];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[7];
            rB0 = pB0[7];
            rA1 = pA0[63];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[119];
            rA3 = pA0[175];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[8];
            rB0 = pB0[8];
            rA1 = pA0[64];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[120];
            rA3 = pA0[176];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[9];
            rB0 = pB0[9];
            rA1 = pA0[65];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[121];
            rA3 = pA0[177];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[10];
            rB0 = pB0[10];
            rA1 = pA0[66];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[122];
            rA3 = pA0[178];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[11];
            rB0 = pB0[11];
            rA1 = pA0[67];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[123];
            rA3 = pA0[179];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[12];
            rB0 = pB0[12];
            rA1 = pA0[68];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[124];
            rA3 = pA0[180];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[13];
            rB0 = pB0[13];
            rA1 = pA0[69];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[125];
            rA3 = pA0[181];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[14];
            rB0 = pB0[14];
            rA1 = pA0[70];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[126];
            rA3 = pA0[182];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[15];
            rB0 = pB0[15];
            rA1 = pA0[71];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[127];
            rA3 = pA0[183];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[16];
            rB0 = pB0[16];
            rA1 = pA0[72];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[128];
            rA3 = pA0[184];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[17];
            rB0 = pB0[17];
            rA1 = pA0[73];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[129];
            rA3 = pA0[185];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[18];
            rB0 = pB0[18];
            rA1 = pA0[74];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[130];
            rA3 = pA0[186];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[19];
            rB0 = pB0[19];
            rA1 = pA0[75];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[131];
            rA3 = pA0[187];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[20];
            rB0 = pB0[20];
            rA1 = pA0[76];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[132];
            rA3 = pA0[188];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[21];
            rB0 = pB0[21];
            rA1 = pA0[77];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[133];
            rA3 = pA0[189];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[22];
            rB0 = pB0[22];
            rA1 = pA0[78];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[134];
            rA3 = pA0[190];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            rA0 = pA0[23];
            rB0 = pB0[23];
            rA1 = pA0[79];
            rC0_0 += rA0 * rB0;
            rA2 = pA0[135];
            rA3 = pA0[191];
            rC1_0 += rA1 * rB0;
            rC2_0 += rA2 * rB0;
            rC3_0 += rA3 * rB0;
            pA0 += incAk;
            pB0 += incBk;
         }
         rA0 = *pA0;
         rB0 = *pB0;
         rA1 = pA0[56];
         rC0_0 += rA0 * rB0;
         rA2 = pA0[112];
         rA3 = pA0[168];
         rC1_0 += rA1 * rB0;
         rC2_0 += rA2 * rB0;
         rC3_0 += rA3 * rB0;
         rA0 = pA0[1];
         rB0 = pB0[1];
         rA1 = pA0[57];
         rC0_0 += rA0 * rB0;
         rA2 = pA0[113];
         rA3 = pA0[169];
         rC1_0 += rA1 * rB0;
         rC2_0 += rA2 * rB0;
         rC3_0 += rA3 * rB0;
         rA0 = pA0[2];
         rB0 = pB0[2];
         rA1 = pA0[58];
         rC0_0 += rA0 * rB0;
         rA2 = pA0[114];
         rA3 = pA0[170];
         rC1_0 += rA1 * rB0;
         rC2_0 += rA2 * rB0;
         rC3_0 += rA3 * rB0;
         rA0 = pA0[3];
         rB0 = pB0[3];
         rA1 = pA0[59];
         rC0_0 += rA0 * rB0;
         rA2 = pA0[115];
         rA3 = pA0[171];
         rC1_0 += rA1 * rB0;
         rC2_0 += rA2 * rB0;
         rC3_0 += rA3 * rB0;
         rA0 = pA0[4];
         rB0 = pB0[4];
         rA1 = pA0[60];
         rC0_0 += rA0 * rB0;
         rA2 = pA0[116];
         rA3 = pA0[172];
         rC1_0 += rA1 * rB0;
         rC2_0 += rA2 * rB0;
         rC3_0 += rA3 * rB0;
         rA0 = pA0[5];
         rB0 = pB0[5];
         rA1 = pA0[61];
         rC0_0 += rA0 * rB0;
         rA2 = pA0[117];
         rA3 = pA0[173];
         rC1_0 += rA1 * rB0;
         rC2_0 += rA2 * rB0;
         rC3_0 += rA3 * rB0;
         rA0 = pA0[6];
         rB0 = pB0[6];
         rA1 = pA0[62];
         rC0_0 += rA0 * rB0;
         rA2 = pA0[118];
         rA3 = pA0[174];
         rC1_0 += rA1 * rB0;
         rC2_0 += rA2 * rB0;
         rC3_0 += rA3 * rB0;
         rA0 = pA0[7];
         rB0 = pB0[7];
         rA1 = pA0[63];
         rC0_0 += rA0 * rB0;
         rA2 = pA0[119];
         rA3 = pA0[175];
         rC1_0 += rA1 * rB0;
         rC2_0 += rA2 * rB0;
         rC3_0 += rA3 * rB0;
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