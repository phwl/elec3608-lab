#include "atlas_asm.h"
/*
 * This file does a 1x6 unrolled mvn_sse with these params:
 *    CL=8, ORDER=clmajor
 */
#ifndef ATL_GAS_x8664
   #error "This kernel requires x86-64 assembly!"
#endif
/*
 * Integer register assignment
 */
#define M       %rdi
#define N       %rsi
#define pA0     %rdx
#define lda     %rax
#define pX      %r8
#define pY      %r9
#define II      %rbx
#define pY0     %r11
#define Mr      %rcx
#define incAYm  %r10
#define incII   %r15
#define incAn   %r14
#define lda3    %r12
#define lda5    %r13
/*
 * SSE register assignment
 */
#define rA0     %xmm0
#define rY      %xmm1
#define rX0     %xmm2
#define rX1     %xmm3
#define rX2     %xmm4
#define rX3     %xmm5
#define rX4     %xmm6
#define rX5     %xmm7
/*
 * macros
 */
#ifndef MOVA
   #define MOVA movaps
#endif
#define movapd movaps
#define movupd movups
#define xorpd xorps
/*
 * Define macros controlling prefetch
 */
#ifndef PFDIST
   #define PFDIST 256
#endif
#ifndef PFADIST
   #define PFADIST PFDIST
#endif
#ifndef PFYDIST
   #define PFYDIST 64
#endif
#ifndef PFXDIST
   #define PFXDIST 64
#endif
#ifndef PFIY
   #ifdef ATL_3DNow
      #define PFIY prefetchw
   #else
      #define PFIY prefetcht0
   #endif
#endif
#ifndef PFIX
   #define PFIX prefetchnta
#endif
#ifndef PFIA
   #define PFIA prefetchnta
#endif
#if PFADIST == 0                /* flag for no prefetch */
   #define prefA(mem)
#else
   #define prefA(mem) PFIA mem
#endif
#if PFYDIST == 0                /* flag for no prefetch */
   #define prefY(mem)
#else
   #define prefY(mem) PFIY mem
#endif
#if PFXDIST == 0                /* flag for no prefetch */
   #define prefX(mem)
#else
   #define prefX(mem) PFIX mem
#endif
/*
 *                      %rdi        %rsi           %rdx          %rcx
 * void ATL_UGEMV(ATL_CINT M, ATL_CINT N, const TYPE *A, ATL_CINT lda,
 *                          %r8      %r9
 *                const TYPE *X, TYPE *Y)
 */
.text
.text
.global ATL_asmdecor(ATL_UGEMV)
ALIGN64
ATL_asmdecor(ATL_UGEMV):

/*
 * Save callee-saved iregs
 */
   movq %rbp, -8(%rsp)
   movq %rbx, -16(%rsp)
   movq %r12, -24(%rsp)
   movq %r13, -32(%rsp)
   movq %r14, -40(%rsp)
   movq %r15, -48(%rsp)
/*
 * Compute M = (M/MU)*MU, Mr = M - (M/MU)*MU
 * NOTE: Mr is %rcx reg, so we can use jcx to go to cleanup loop
 */
   mov  %rcx, lda       /* move lda to assigned register, rax */
   mov  M, Mr           /* Mr = M */
   shr $3, M            /* M = M / MU */
   shl $3, M            /* M = (M/MU)*MU */
   sub M, Mr            /* Mr = M - (M/MU)*MU */
/*
 * Setup constants
 */
   mov lda, incAn       /* incAn = lda */
   sub M, incAn         /* incAn = lda - (M/MU)*MU */
   sub Mr, incAn        /* incAn = lda - M */
   shl $3, incAn        /* incAn = (lda-M)*sizeof */
   shl $3, lda          /* lda *= sizeof */
   sub $-128, pA0       /* code compaction by using signed 1-byte offsets */
   sub $-128, pY        /* code compaction by using signed 1-byte offsets */
   mov pY, pY0          /* save for restore after M loops */
   mov $-64, incAYm     /* code comp: use reg rather than constant */
   lea (lda, lda,2), lda3       /* lda3 = 3*lda */
   lea (lda, lda,4), lda5       /* lda5 = 5*lda */
   add lda5, incAn              /* incAn = (6*lda-M)*sizeof */
   mov $8*1, incII      /* code comp: use reg rather than constant */
   mov M, II
/*
 * Zero Y if beta = 0;  Has error if there is Mr and/or M isn't mul of veclen
 */
   #ifdef BETA0
       add Mr, II
      shr $1, II
      xorpd rY, rY
      LOOPZERO:
         movapd rY, -128(pY)
         add $16, pY
      dec II
      jnz LOOPZERO
      lea (M, Mr), II
      bt $0, II
      jnc DONE_ZERO_CLEAN
      movsd rY, -128(pY)
DONE_ZERO_CLEAN:
      mov pY0, pY
      mov M, II
   #endif

   ALIGN32
   LOOPN:
      movddup 0(pX), rX0
      movddup 8(pX), rX1
      movddup 16(pX), rX2
      movddup 24(pX), rX3
      movddup 32(pX), rX4
      movddup 40(pX), rX5

      LOOPM:
         MOVA   0-128(pA0), rY
         mulpd rX0, rY
         addpd 0-128(pY), rY
         prefA(PFADIST+0(pA0))

         MOVA   0-128(pA0,lda), rA0
         mulpd rX1, rA0
         addpd rA0, rY
         prefA(PFADIST+0(pA0,lda))
         MOVA   0-128(pA0,lda,2), rA0
         mulpd rX2, rA0
         addpd rA0, rY
         prefA(PFADIST+0(pA0,lda,2))
         MOVA   0-128(pA0,lda3), rA0
         mulpd rX3, rA0
         addpd rA0, rY
         prefA(PFADIST+0(pA0,lda3))
         MOVA   0-128(pA0,lda,4), rA0
         mulpd rX4, rA0
         addpd rA0, rY
         prefA(PFADIST+0(pA0,lda,4))
         MOVA   0-128(pA0,lda5), rA0
         mulpd rX5, rA0
         addpd rA0, rY
         prefA(PFADIST+0(pA0,lda5))
         movapd rY, 0-128(pY)

         MOVA   16-128(pA0), rY
         mulpd rX0, rY
         addpd 16-128(pY), rY

         MOVA   16-128(pA0,lda), rA0
         mulpd rX1, rA0
         addpd rA0, rY
         MOVA   16-128(pA0,lda,2), rA0
         mulpd rX2, rA0
         addpd rA0, rY
         MOVA   16-128(pA0,lda3), rA0
         mulpd rX3, rA0
         addpd rA0, rY
         MOVA   16-128(pA0,lda,4), rA0
         mulpd rX4, rA0
         addpd rA0, rY
         MOVA   16-128(pA0,lda5), rA0
         mulpd rX5, rA0
         addpd rA0, rY
         movapd rY, 16-128(pY)

         MOVA   32-128(pA0), rY
         mulpd rX0, rY
         addpd 32-128(pY), rY

         MOVA   32-128(pA0,lda), rA0
         mulpd rX1, rA0
         addpd rA0, rY
         MOVA   32-128(pA0,lda,2), rA0
         mulpd rX2, rA0
         addpd rA0, rY
         MOVA   32-128(pA0,lda3), rA0
         mulpd rX3, rA0
         addpd rA0, rY
         MOVA   32-128(pA0,lda,4), rA0
         mulpd rX4, rA0
         addpd rA0, rY
         MOVA   32-128(pA0,lda5), rA0
         mulpd rX5, rA0
         addpd rA0, rY
         movapd rY, 32-128(pY)

         MOVA   48-128(pA0), rY
         mulpd rX0, rY
         addpd 48-128(pY), rY

         MOVA   48-128(pA0,lda), rA0
         mulpd rX1, rA0
         addpd rA0, rY
         MOVA   48-128(pA0,lda,2), rA0
         mulpd rX2, rA0
         addpd rA0, rY
         MOVA   48-128(pA0,lda3), rA0
         mulpd rX3, rA0
         addpd rA0, rY
         MOVA   48-128(pA0,lda,4), rA0
         mulpd rX4, rA0
         addpd rA0, rY
         MOVA   48-128(pA0,lda5), rA0
         mulpd rX5, rA0
         addpd rA0, rY
         movapd rY, 48-128(pY)

         sub incAYm, pY
         sub incAYm, pA0
      sub incII, II
      jnz LOOPM

      #ifdef ATL_OS_OSX     /* workaround retarded OS X assembly */
         cmp $0, Mr
         jz  MCLEANED
      #else
         jecxz MCLEANED        /* skip cleanup loop if Mr == 0 */
      #endif

      mov Mr, II
      LOOPMCU:
         movsd -128(pY), rY
         movsd -128(pA0), rA0
         mulsd rX0, rA0
         addsd rA0, rY
         movsd  -128(pA0,lda), rA0
         mulsd rX1, rA0
         addsd rA0, rY
         movsd  -128(pA0,lda,2), rA0
         mulsd rX2, rA0
         addsd rA0, rY
         movsd  -128(pA0,lda3), rA0
         mulsd rX3, rA0
         addsd rA0, rY
         movsd  -128(pA0,lda,4), rA0
         mulsd rX4, rA0
         addsd rA0, rY
         movsd  -128(pA0,lda5), rA0
         mulsd rX5, rA0
         addsd rA0, rY
         movsd rY, -128(pY)
         add $8, pY
         add $8, pA0
      dec II
      jnz LOOPMCU

MCLEANED:
      prefX(6*8+PFXDIST(pX))
      add $6*8, pX
      add incAn, pA0
      mov pY0, pY
      mov M, II
   sub $6, N
   jnz LOOPN
/*
 * EPILOGUE: restore registers and return
 */
   movq -8(%rsp), %rbp
   movq -16(%rsp), %rbx
   movq -24(%rsp), %r12
   movq -32(%rsp), %r13
   movq -40(%rsp), %r14
   movq -48(%rsp), %r15
   ret
