#define ATL_INT int
#include <stdio.h>
#include <stdint.h>
#include <pmmintrin.h>

#define I_UNROLL 12
#define J_UNROLL 1
/* Is prefetched data written or just read? */
#define PF_READONLY 0
#define PF_READWRITE 1
#define PF_NO_REUSE 0

/* Default temporality of cache prefetch (1-3) */
#define PF_DEF 1
#define CACHE_LINE_SIZE 64
#define MMCAST( a ) (a)
#define MMCASTStore( a ) (a)
#define MMCASTStoreintrin( a ) (a)
#define TYPE float
void ATL_USERMM( const ATL_INT M, const ATL_INT N, const ATL_INT K,
                 const TYPE alpha, const TYPE *A, const ATL_INT lda,
                 const TYPE *B, const ATL_INT ldb,
                 const TYPE beta, TYPE *C, const ATL_INT ldc )
{
   register ATL_INT i, j, k;
   
   /* Vector registers to hold the elements of C */
   __m128 c0_0, c0_1, c0_2, c0_3, c0_4, c0_5, c0_6, c0_7, c0_8, c0_9, c0_10, c0_11;
   /* Vector register to hold C*beta */
   __m128 bc0_0, bc0_4, bc0_8, bc0_9, bc0_10, bc0_11;
   /* Temporary vector registers for use in inner loop */
   __m128 temp; 
   const __m128 betaV = _mm_set1_ps( beta ); 
   /* Pointer adjustments */  
   register const ATL_INT ldc_bytes = ldc;
   
   register TYPE const *B0_off = B;
      
   register void const * prefetchABlock =  (void*)(A + 72*KB); 
   
   /* Unroll A */
   __m128 A0, a0, A1, a1, A2, a2, A3, a3, A4, a4, A5, a5, A6, a6, A7, a7, A8, a8, A9, a9, A10, a10, A11, a11;
   /* Unroll B */
   __m128 B0, B1;
   

   register const ATL_INT unroll_a = I_UNROLL*KB;
   register TYPE* cPtr = C;
   

   const ATL_INT pfBlockDistance = (12 * 1 * KB * 4) / 72;
   /* =======================================
    * Begin generated inner loops for case Non aligned
    * ======================================= */
   for( j=-72; j!=0; j+=J_UNROLL) 
   {
      register TYPE const *A0_off = A; 
      
      register TYPE *cPtrI0 = cPtr;
      

      for( i=-72; i != 0; i+= I_UNROLL )
      {
         /* K_Unrolling0 */
         A0 = _mm_load_ps( MMCAST(A0_off) );
         A1 = _mm_load_ps( MMCAST(A0_off + 72) );
         A2 = _mm_load_ps( MMCAST(A0_off + 144) );
         A3 = _mm_load_ps( MMCAST(A0_off + 216) );
         A4 = _mm_load_ps( MMCAST(A0_off + 288) );
         A5 = _mm_load_ps( MMCAST(A0_off + 360) );
         A6 = _mm_load_ps( MMCAST(A0_off + 432) );
         A7 = _mm_load_ps( MMCAST(A0_off + 504) );
         A8 = _mm_load_ps( MMCAST(A0_off + 576) );
         A9 = _mm_load_ps( MMCAST(A0_off + 648) );
         A10 = _mm_load_ps( MMCAST(A0_off + 720) );
         A11 = _mm_load_ps( MMCAST(A0_off + 792) );
         B0 = _mm_load_ps( MMCAST(B0_off) );
         c0_0 = B0;
         c0_0 = _mm_mul_ps( A0, c0_0 );
         c0_1 = B0;
         c0_1 = _mm_mul_ps( A1, c0_1 );
         c0_2 = B0;
         c0_2 = _mm_mul_ps( A2, c0_2 );
         c0_3 = B0;
         c0_3 = _mm_mul_ps( A3, c0_3 );
         c0_4 = B0;
         c0_4 = _mm_mul_ps( A4, c0_4 );
         c0_5 = B0;
         c0_5 = _mm_mul_ps( A5, c0_5 );
         c0_6 = B0;
         c0_6 = _mm_mul_ps( A6, c0_6 );
         c0_7 = B0;
         c0_7 = _mm_mul_ps( A7, c0_7 );
         c0_8 = B0;
         c0_8 = _mm_mul_ps( A8, c0_8 );
         c0_9 = B0;
         c0_9 = _mm_mul_ps( A9, c0_9 );
         c0_10 = B0;
         c0_10 = _mm_mul_ps( A10, c0_10 );
         c0_11 = B0;
         c0_11 = _mm_mul_ps( A11, c0_11 );
         
         /* Prefetch one element from the next block of A */
         __builtin_prefetch( prefetchABlock + 0*pfBlockDistance,PF_READONLY, PF_DEF );
         /* K_Unrolling: 4 */
         A0 = _mm_load_ps( MMCAST(A0_off + 4) );
         A1 = _mm_load_ps( MMCAST(A0_off + 76) );
         A2 = _mm_load_ps( MMCAST(A0_off + 148) );
         A3 = _mm_load_ps( MMCAST(A0_off + 220) );
         A4 = _mm_load_ps( MMCAST(A0_off + 292) );
         A5 = _mm_load_ps( MMCAST(A0_off + 364) );
         A6 = _mm_load_ps( MMCAST(A0_off + 436) );
         A7 = _mm_load_ps( MMCAST(A0_off + 508) );
         A8 = _mm_load_ps( MMCAST(A0_off + 580) );
         A9 = _mm_load_ps( MMCAST(A0_off + 652) );
         A10 = _mm_load_ps( MMCAST(A0_off + 724) );
         A11 = _mm_load_ps( MMCAST(A0_off + 796) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 4) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 8 */
         A0 = _mm_load_ps( MMCAST(A0_off + 8) );
         A1 = _mm_load_ps( MMCAST(A0_off + 80) );
         A2 = _mm_load_ps( MMCAST(A0_off + 152) );
         A3 = _mm_load_ps( MMCAST(A0_off + 224) );
         A4 = _mm_load_ps( MMCAST(A0_off + 296) );
         A5 = _mm_load_ps( MMCAST(A0_off + 368) );
         A6 = _mm_load_ps( MMCAST(A0_off + 440) );
         A7 = _mm_load_ps( MMCAST(A0_off + 512) );
         A8 = _mm_load_ps( MMCAST(A0_off + 584) );
         A9 = _mm_load_ps( MMCAST(A0_off + 656) );
         A10 = _mm_load_ps( MMCAST(A0_off + 728) );
         A11 = _mm_load_ps( MMCAST(A0_off + 800) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 8) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 12 */
         A0 = _mm_load_ps( MMCAST(A0_off + 12) );
         A1 = _mm_load_ps( MMCAST(A0_off + 84) );
         A2 = _mm_load_ps( MMCAST(A0_off + 156) );
         A3 = _mm_load_ps( MMCAST(A0_off + 228) );
         A4 = _mm_load_ps( MMCAST(A0_off + 300) );
         A5 = _mm_load_ps( MMCAST(A0_off + 372) );
         A6 = _mm_load_ps( MMCAST(A0_off + 444) );
         A7 = _mm_load_ps( MMCAST(A0_off + 516) );
         A8 = _mm_load_ps( MMCAST(A0_off + 588) );
         A9 = _mm_load_ps( MMCAST(A0_off + 660) );
         A10 = _mm_load_ps( MMCAST(A0_off + 732) );
         A11 = _mm_load_ps( MMCAST(A0_off + 804) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 12) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 16 */
         A0 = _mm_load_ps( MMCAST(A0_off + 16) );
         A1 = _mm_load_ps( MMCAST(A0_off + 88) );
         A2 = _mm_load_ps( MMCAST(A0_off + 160) );
         A3 = _mm_load_ps( MMCAST(A0_off + 232) );
         A4 = _mm_load_ps( MMCAST(A0_off + 304) );
         A5 = _mm_load_ps( MMCAST(A0_off + 376) );
         A6 = _mm_load_ps( MMCAST(A0_off + 448) );
         A7 = _mm_load_ps( MMCAST(A0_off + 520) );
         A8 = _mm_load_ps( MMCAST(A0_off + 592) );
         A9 = _mm_load_ps( MMCAST(A0_off + 664) );
         A10 = _mm_load_ps( MMCAST(A0_off + 736) );
         A11 = _mm_load_ps( MMCAST(A0_off + 808) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 16) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 20 */
         A0 = _mm_load_ps( MMCAST(A0_off + 20) );
         A1 = _mm_load_ps( MMCAST(A0_off + 92) );
         A2 = _mm_load_ps( MMCAST(A0_off + 164) );
         A3 = _mm_load_ps( MMCAST(A0_off + 236) );
         A4 = _mm_load_ps( MMCAST(A0_off + 308) );
         A5 = _mm_load_ps( MMCAST(A0_off + 380) );
         A6 = _mm_load_ps( MMCAST(A0_off + 452) );
         A7 = _mm_load_ps( MMCAST(A0_off + 524) );
         A8 = _mm_load_ps( MMCAST(A0_off + 596) );
         A9 = _mm_load_ps( MMCAST(A0_off + 668) );
         A10 = _mm_load_ps( MMCAST(A0_off + 740) );
         A11 = _mm_load_ps( MMCAST(A0_off + 812) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 20) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 24 */
         A0 = _mm_load_ps( MMCAST(A0_off + 24) );
         A1 = _mm_load_ps( MMCAST(A0_off + 96) );
         A2 = _mm_load_ps( MMCAST(A0_off + 168) );
         A3 = _mm_load_ps( MMCAST(A0_off + 240) );
         A4 = _mm_load_ps( MMCAST(A0_off + 312) );
         A5 = _mm_load_ps( MMCAST(A0_off + 384) );
         A6 = _mm_load_ps( MMCAST(A0_off + 456) );
         A7 = _mm_load_ps( MMCAST(A0_off + 528) );
         A8 = _mm_load_ps( MMCAST(A0_off + 600) );
         A9 = _mm_load_ps( MMCAST(A0_off + 672) );
         A10 = _mm_load_ps( MMCAST(A0_off + 744) );
         A11 = _mm_load_ps( MMCAST(A0_off + 816) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 24) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 28 */
         A0 = _mm_load_ps( MMCAST(A0_off + 28) );
         A1 = _mm_load_ps( MMCAST(A0_off + 100) );
         A2 = _mm_load_ps( MMCAST(A0_off + 172) );
         A3 = _mm_load_ps( MMCAST(A0_off + 244) );
         A4 = _mm_load_ps( MMCAST(A0_off + 316) );
         A5 = _mm_load_ps( MMCAST(A0_off + 388) );
         A6 = _mm_load_ps( MMCAST(A0_off + 460) );
         A7 = _mm_load_ps( MMCAST(A0_off + 532) );
         A8 = _mm_load_ps( MMCAST(A0_off + 604) );
         A9 = _mm_load_ps( MMCAST(A0_off + 676) );
         A10 = _mm_load_ps( MMCAST(A0_off + 748) );
         A11 = _mm_load_ps( MMCAST(A0_off + 820) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 28) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 32 */
         A0 = _mm_load_ps( MMCAST(A0_off + 32) );
         A1 = _mm_load_ps( MMCAST(A0_off + 104) );
         A2 = _mm_load_ps( MMCAST(A0_off + 176) );
         A3 = _mm_load_ps( MMCAST(A0_off + 248) );
         A4 = _mm_load_ps( MMCAST(A0_off + 320) );
         A5 = _mm_load_ps( MMCAST(A0_off + 392) );
         A6 = _mm_load_ps( MMCAST(A0_off + 464) );
         A7 = _mm_load_ps( MMCAST(A0_off + 536) );
         A8 = _mm_load_ps( MMCAST(A0_off + 608) );
         A9 = _mm_load_ps( MMCAST(A0_off + 680) );
         A10 = _mm_load_ps( MMCAST(A0_off + 752) );
         A11 = _mm_load_ps( MMCAST(A0_off + 824) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 32) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 36 */
         A0 = _mm_load_ps( MMCAST(A0_off + 36) );
         A1 = _mm_load_ps( MMCAST(A0_off + 108) );
         A2 = _mm_load_ps( MMCAST(A0_off + 180) );
         A3 = _mm_load_ps( MMCAST(A0_off + 252) );
         A4 = _mm_load_ps( MMCAST(A0_off + 324) );
         A5 = _mm_load_ps( MMCAST(A0_off + 396) );
         A6 = _mm_load_ps( MMCAST(A0_off + 468) );
         A7 = _mm_load_ps( MMCAST(A0_off + 540) );
         A8 = _mm_load_ps( MMCAST(A0_off + 612) );
         A9 = _mm_load_ps( MMCAST(A0_off + 684) );
         A10 = _mm_load_ps( MMCAST(A0_off + 756) );
         A11 = _mm_load_ps( MMCAST(A0_off + 828) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 36) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 40 */
         A0 = _mm_load_ps( MMCAST(A0_off + 40) );
         A1 = _mm_load_ps( MMCAST(A0_off + 112) );
         A2 = _mm_load_ps( MMCAST(A0_off + 184) );
         A3 = _mm_load_ps( MMCAST(A0_off + 256) );
         A4 = _mm_load_ps( MMCAST(A0_off + 328) );
         A5 = _mm_load_ps( MMCAST(A0_off + 400) );
         A6 = _mm_load_ps( MMCAST(A0_off + 472) );
         A7 = _mm_load_ps( MMCAST(A0_off + 544) );
         A8 = _mm_load_ps( MMCAST(A0_off + 616) );
         A9 = _mm_load_ps( MMCAST(A0_off + 688) );
         A10 = _mm_load_ps( MMCAST(A0_off + 760) );
         A11 = _mm_load_ps( MMCAST(A0_off + 832) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 40) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 44 */
         A0 = _mm_load_ps( MMCAST(A0_off + 44) );
         A1 = _mm_load_ps( MMCAST(A0_off + 116) );
         A2 = _mm_load_ps( MMCAST(A0_off + 188) );
         A3 = _mm_load_ps( MMCAST(A0_off + 260) );
         A4 = _mm_load_ps( MMCAST(A0_off + 332) );
         A5 = _mm_load_ps( MMCAST(A0_off + 404) );
         A6 = _mm_load_ps( MMCAST(A0_off + 476) );
         A7 = _mm_load_ps( MMCAST(A0_off + 548) );
         A8 = _mm_load_ps( MMCAST(A0_off + 620) );
         A9 = _mm_load_ps( MMCAST(A0_off + 692) );
         A10 = _mm_load_ps( MMCAST(A0_off + 764) );
         A11 = _mm_load_ps( MMCAST(A0_off + 836) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 44) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 48 */
         A0 = _mm_load_ps( MMCAST(A0_off + 48) );
         A1 = _mm_load_ps( MMCAST(A0_off + 120) );
         A2 = _mm_load_ps( MMCAST(A0_off + 192) );
         A3 = _mm_load_ps( MMCAST(A0_off + 264) );
         A4 = _mm_load_ps( MMCAST(A0_off + 336) );
         A5 = _mm_load_ps( MMCAST(A0_off + 408) );
         A6 = _mm_load_ps( MMCAST(A0_off + 480) );
         A7 = _mm_load_ps( MMCAST(A0_off + 552) );
         A8 = _mm_load_ps( MMCAST(A0_off + 624) );
         A9 = _mm_load_ps( MMCAST(A0_off + 696) );
         A10 = _mm_load_ps( MMCAST(A0_off + 768) );
         A11 = _mm_load_ps( MMCAST(A0_off + 840) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 48) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 52 */
         A0 = _mm_load_ps( MMCAST(A0_off + 52) );
         A1 = _mm_load_ps( MMCAST(A0_off + 124) );
         A2 = _mm_load_ps( MMCAST(A0_off + 196) );
         A3 = _mm_load_ps( MMCAST(A0_off + 268) );
         A4 = _mm_load_ps( MMCAST(A0_off + 340) );
         A5 = _mm_load_ps( MMCAST(A0_off + 412) );
         A6 = _mm_load_ps( MMCAST(A0_off + 484) );
         A7 = _mm_load_ps( MMCAST(A0_off + 556) );
         A8 = _mm_load_ps( MMCAST(A0_off + 628) );
         A9 = _mm_load_ps( MMCAST(A0_off + 700) );
         A10 = _mm_load_ps( MMCAST(A0_off + 772) );
         A11 = _mm_load_ps( MMCAST(A0_off + 844) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 52) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 56 */
         A0 = _mm_load_ps( MMCAST(A0_off + 56) );
         A1 = _mm_load_ps( MMCAST(A0_off + 128) );
         A2 = _mm_load_ps( MMCAST(A0_off + 200) );
         A3 = _mm_load_ps( MMCAST(A0_off + 272) );
         A4 = _mm_load_ps( MMCAST(A0_off + 344) );
         A5 = _mm_load_ps( MMCAST(A0_off + 416) );
         A6 = _mm_load_ps( MMCAST(A0_off + 488) );
         A7 = _mm_load_ps( MMCAST(A0_off + 560) );
         A8 = _mm_load_ps( MMCAST(A0_off + 632) );
         A9 = _mm_load_ps( MMCAST(A0_off + 704) );
         A10 = _mm_load_ps( MMCAST(A0_off + 776) );
         A11 = _mm_load_ps( MMCAST(A0_off + 848) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 56) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 60 */
         A0 = _mm_load_ps( MMCAST(A0_off + 60) );
         A1 = _mm_load_ps( MMCAST(A0_off + 132) );
         A2 = _mm_load_ps( MMCAST(A0_off + 204) );
         A3 = _mm_load_ps( MMCAST(A0_off + 276) );
         A4 = _mm_load_ps( MMCAST(A0_off + 348) );
         A5 = _mm_load_ps( MMCAST(A0_off + 420) );
         A6 = _mm_load_ps( MMCAST(A0_off + 492) );
         A7 = _mm_load_ps( MMCAST(A0_off + 564) );
         A8 = _mm_load_ps( MMCAST(A0_off + 636) );
         A9 = _mm_load_ps( MMCAST(A0_off + 708) );
         A10 = _mm_load_ps( MMCAST(A0_off + 780) );
         A11 = _mm_load_ps( MMCAST(A0_off + 852) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 60) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 64 */
         A0 = _mm_load_ps( MMCAST(A0_off + 64) );
         A1 = _mm_load_ps( MMCAST(A0_off + 136) );
         A2 = _mm_load_ps( MMCAST(A0_off + 208) );
         A3 = _mm_load_ps( MMCAST(A0_off + 280) );
         A4 = _mm_load_ps( MMCAST(A0_off + 352) );
         A5 = _mm_load_ps( MMCAST(A0_off + 424) );
         A6 = _mm_load_ps( MMCAST(A0_off + 496) );
         A7 = _mm_load_ps( MMCAST(A0_off + 568) );
         A8 = _mm_load_ps( MMCAST(A0_off + 640) );
         A9 = _mm_load_ps( MMCAST(A0_off + 712) );
         A10 = _mm_load_ps( MMCAST(A0_off + 784) );
         A11 = _mm_load_ps( MMCAST(A0_off + 856) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 64) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         /* K_Unrolling: 68 */
         A0 = _mm_load_ps( MMCAST(A0_off + 68) );
         A1 = _mm_load_ps( MMCAST(A0_off + 140) );
         A2 = _mm_load_ps( MMCAST(A0_off + 212) );
         A3 = _mm_load_ps( MMCAST(A0_off + 284) );
         A4 = _mm_load_ps( MMCAST(A0_off + 356) );
         A5 = _mm_load_ps( MMCAST(A0_off + 428) );
         A6 = _mm_load_ps( MMCAST(A0_off + 500) );
         A7 = _mm_load_ps( MMCAST(A0_off + 572) );
         A8 = _mm_load_ps( MMCAST(A0_off + 644) );
         A9 = _mm_load_ps( MMCAST(A0_off + 716) );
         A10 = _mm_load_ps( MMCAST(A0_off + 788) );
         A11 = _mm_load_ps( MMCAST(A0_off + 860) );
         
         B0 = _mm_load_ps( MMCAST(B0_off + 68) );
         A0 = _mm_mul_ps( B0, A0 );
         c0_0 = _mm_add_ps( A0, c0_0 );
         A1 = _mm_mul_ps( B0, A1 );
         c0_1 = _mm_add_ps( A1, c0_1 );
         A2 = _mm_mul_ps( B0, A2 );
         c0_2 = _mm_add_ps( A2, c0_2 );
         A3 = _mm_mul_ps( B0, A3 );
         c0_3 = _mm_add_ps( A3, c0_3 );
         A4 = _mm_mul_ps( B0, A4 );
         c0_4 = _mm_add_ps( A4, c0_4 );
         A5 = _mm_mul_ps( B0, A5 );
         c0_5 = _mm_add_ps( A5, c0_5 );
         A6 = _mm_mul_ps( B0, A6 );
         c0_6 = _mm_add_ps( A6, c0_6 );
         A7 = _mm_mul_ps( B0, A7 );
         c0_7 = _mm_add_ps( A7, c0_7 );
         A8 = _mm_mul_ps( B0, A8 );
         c0_8 = _mm_add_ps( A8, c0_8 );
         A9 = _mm_mul_ps( B0, A9 );
         c0_9 = _mm_add_ps( A9, c0_9 );
         A10 = _mm_mul_ps( B0, A10 );
         c0_10 = _mm_add_ps( A10, c0_10 );
         A11 = _mm_mul_ps( B0, A11 );
         c0_11 = _mm_add_ps( A11, c0_11 );
         prefetchABlock += 1*pfBlockDistance;
         /* Single Scalar Compression */
         c0_0 = _mm_hadd_ps( c0_0, c0_1 );
         c0_2 = _mm_hadd_ps( c0_2, c0_3 );
         c0_0 = _mm_hadd_ps( c0_0, c0_2 );
         
         c0_4 = _mm_hadd_ps( c0_4, c0_5 );
         c0_6 = _mm_hadd_ps( c0_6, c0_7 );
         c0_4 = _mm_hadd_ps( c0_4, c0_6 );
         
         c0_8 = _mm_hadd_ps( c0_8, c0_9 );
         c0_10 = _mm_hadd_ps( c0_10, c0_11 );
         c0_8 = _mm_hadd_ps( c0_8, c0_10 );
         
         /* Applying Beta */
            /* Apply Beta Factor */
            /* Load C from memory */
            bc0_0 = _mm_loadu_ps( cPtrI0+0 );
            bc0_0 = _mm_mul_ps( betaV, bc0_0 );
            bc0_4 = _mm_loadu_ps( cPtrI0+4 );
            bc0_4 = _mm_mul_ps( betaV, bc0_4 );
            bc0_8 = _mm_loadu_ps( cPtrI0+8 );
            bc0_8 = _mm_mul_ps( betaV, bc0_8 );
            /* C = (beta*C) + (matrix multiply) */
            c0_0 = _mm_add_ps( bc0_0, c0_0 );
            c0_4 = _mm_add_ps( bc0_4, c0_4 );
            c0_8 = _mm_add_ps( bc0_8, c0_8 );
         /* Move pointers to next iteration */  
         A0_off += unroll_a;
         
         /* Store results back to memory  */
         _mm_storeu_ps( MMCAST( cPtrI0 ),  MMCASTStoreintrin( c0_0 ) );
         _mm_storeu_ps( MMCAST( cPtrI0+4 ),  MMCASTStoreintrin( c0_4 ) );
         _mm_storeu_ps( MMCAST( cPtrI0+8 ),  MMCASTStoreintrin( c0_8 ) );
         cPtrI0 += I_UNROLL;
         

      } /* End i/MB loop */

      B0_off += J_UNROLL*KB;
      cPtr += J_UNROLL*ldc_bytes;
   } /* End j/NB loop */
   /* End of generated inner loops */
}
