#include "atlas_asm.h"
/*
 * This file does a 1x5 unrolled r2_sse with these params:
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
#define pA0     %r10
#define lda     %rax
#define pX      %rdx
#define pY      %rbp
#define pW      %r8
#define pZ      %r9
#define II      %rbx
#define M0      %r11
#define Mr      %rcx
#define incM    $-64
#define incII   %r15
#define incAn   %r14
#define lda3    %r12
/*
 * SSE register assignment
 */
#define rA0     %xmm0
#define rX0     %xmm1
#define rW0     %xmm2
#define ryt     %xmm3
#define rY0     %xmm4
#define rZ0     %xmm5
#define rY1     %xmm6
#define rZ1     %xmm7
#define rY2     %xmm8
#define rZ2     %xmm9
#define rY3     %xmm10
#define rZ3     %xmm11
#define rY4     %xmm12
#define rZ4     %xmm13
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
   #define PFIY prefetchnta
#endif
#ifndef PFIA
   #ifdef ATL_3DNow
      #define PFIA prefetchw
   #else
      #define PFIA prefetcht0
   #endif
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
 *                       %rdi        %rsi           %rdx          %rcx
 * void ATL_UGER2K(ATL_CINT M, ATL_CINT N, const TYPE *X, const TYPE *Y,
 *                     %r8                  %r9  8(%rsp)       16(%rsp)
 *                 const TYPE *W, const TYPE *Z, TYPE *A, ATL_CINT lda)
 */
.text
.text
.global ATL_asmdecor(ATL_UGER2K)
ALIGN64
ATL_asmdecor(ATL_UGER2K):

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
   movq   8(%rsp), pA0   /* load A ptr */
   movslq 16(%rsp), lda /* move lda to assigned register, rax */
   mov %rcx, pY         /* move pY to assigned register, rbp */
   mov M, M0            /* save full M for W/X restoration */
   shl $3, M0           /* M0 *= sizeof */
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
   sub $-128, pX        /* code compaction by using signed 1-byte offsets */
   sub $-128, pW
   lea (lda, lda,2), lda3       /* lda3 = 3*lda */
   lea (incAn, lda,4), incAn    /* incAn = (5*lda-M)*sizeof */
   mov $8*1, incII      /* code comp: use reg rather than constant */
   mov M, II

   ALIGN32
   LOOPN:
      movddup 0(pY), rY0
      movddup 0(pZ), rZ0
      movddup 8(pY), rY1
      movddup 8(pZ), rZ1
      movddup 16(pY), rY2
      movddup 16(pZ), rZ2
      movddup 24(pY), rY3
      movddup 24(pZ), rZ3
      movddup 32(pY), rY4
      movddup 32(pZ), rZ4

      LOOPM:
         movapd 0-128(pX), rX0
         movapd rX0, rA0
         mulpd rY0, rA0
         addpd 0-128(pA0), rA0
         movapd 0-128(pW), rW0
         movapd rZ0, ryt
         mulpd  rW0, ryt
         addpd  ryt, rA0
         MOVA   rA0, 0-128(pA0)
         prefA(PFADIST+0(pA0))
         movapd rX0, rA0
         mulpd rY1, rA0
         addpd 0-128(pA0,lda), rA0
         movapd rZ1, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 0-128(pA0,lda)
         prefA(PFADIST+0(pA0,lda))
         movapd rX0, rA0
         mulpd rY2, rA0
         addpd 0-128(pA0,lda,2), rA0
         movapd rZ2, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 0-128(pA0,lda,2)
         prefA(PFADIST+0(pA0,lda,2))
         movapd rX0, rA0
         mulpd rY3, rA0
         addpd 0-128(pA0,lda3), rA0
         movapd rZ3, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 0-128(pA0,lda3)
         prefA(PFADIST+0(pA0,lda3))
         movapd rX0, rA0
         mulpd rY4, rA0
         addpd 0-128(pA0,lda,4), rA0
         movapd rZ4, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 0-128(pA0,lda,4)
         prefA(PFADIST+0(pA0,lda,4))

         movapd 16-128(pX), rX0
         movapd rX0, rA0
         mulpd rY0, rA0
         addpd 16-128(pA0), rA0
         movapd 16-128(pW), rW0
         movapd rZ0, ryt
         mulpd  rW0, ryt
         addpd  ryt, rA0
         MOVA   rA0, 16-128(pA0)
         movapd rX0, rA0
         mulpd rY1, rA0
         addpd 16-128(pA0,lda), rA0
         movapd rZ1, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 16-128(pA0,lda)
         movapd rX0, rA0
         mulpd rY2, rA0
         addpd 16-128(pA0,lda,2), rA0
         movapd rZ2, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 16-128(pA0,lda,2)
         movapd rX0, rA0
         mulpd rY3, rA0
         addpd 16-128(pA0,lda3), rA0
         movapd rZ3, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 16-128(pA0,lda3)
         movapd rX0, rA0
         mulpd rY4, rA0
         addpd 16-128(pA0,lda,4), rA0
         movapd rZ4, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 16-128(pA0,lda,4)

         movapd 32-128(pX), rX0
         movapd rX0, rA0
         mulpd rY0, rA0
         addpd 32-128(pA0), rA0
         movapd 32-128(pW), rW0
         movapd rZ0, ryt
         mulpd  rW0, ryt
         addpd  ryt, rA0
         MOVA   rA0, 32-128(pA0)
         movapd rX0, rA0
         mulpd rY1, rA0
         addpd 32-128(pA0,lda), rA0
         movapd rZ1, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 32-128(pA0,lda)
         movapd rX0, rA0
         mulpd rY2, rA0
         addpd 32-128(pA0,lda,2), rA0
         movapd rZ2, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 32-128(pA0,lda,2)
         movapd rX0, rA0
         mulpd rY3, rA0
         addpd 32-128(pA0,lda3), rA0
         movapd rZ3, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 32-128(pA0,lda3)
         movapd rX0, rA0
         mulpd rY4, rA0
         addpd 32-128(pA0,lda,4), rA0
         movapd rZ4, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 32-128(pA0,lda,4)

         movapd 48-128(pX), rX0
         movapd rX0, rA0
         mulpd rY0, rA0
         addpd 48-128(pA0), rA0
         movapd 48-128(pW), rW0
         movapd rZ0, ryt
         mulpd  rW0, ryt
         addpd  ryt, rA0
         MOVA   rA0, 48-128(pA0)
         movapd rX0, rA0
         mulpd rY1, rA0
         addpd 48-128(pA0,lda), rA0
         movapd rZ1, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 48-128(pA0,lda)
         movapd rX0, rA0
         mulpd rY2, rA0
         addpd 48-128(pA0,lda,2), rA0
         movapd rZ2, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 48-128(pA0,lda,2)
         movapd rX0, rA0
         mulpd rY3, rA0
         addpd 48-128(pA0,lda3), rA0
         movapd rZ3, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 48-128(pA0,lda3)
         movapd rX0, rA0
         mulpd rY4, rA0
         addpd 48-128(pA0,lda,4), rA0
         movapd rZ4, ryt
         mulpd rW0, ryt
         addpd ryt, rA0
         MOVA   rA0, 48-128(pA0,lda,4)

         sub incM, pX
         sub incM, pW
         sub incM, pA0
      sub incII, II
      jnz LOOPM

      cmp $0, Mr
      jz  MCLEANED

      mov Mr, II
      LOOPMCU:
         movsd -128(pX), rX0
         movsd rX0, rA0
         mulsd rY0, rA0
         addsd -128(pA0), rA0
         movsd -128(pW), rW0
         movsd rZ0, ryt
         mulsd rW0, ryt
         addsd ryt, rA0
         movsd rA0, -128(pA0)
         movsd rX0, rA0
         mulsd rY1, rA0
         addsd -128(pA0,lda), rA0
         movsd rZ1, ryt
         mulsd rW0, ryt
         addsd ryt, rA0
         movsd rA0, -128(pA0,lda)
         movsd rX0, rA0
         mulsd rY2, rA0
         addsd -128(pA0,lda,2), rA0
         movsd rZ2, ryt
         mulsd rW0, ryt
         addsd ryt, rA0
         movsd rA0, -128(pA0,lda,2)
         movsd rX0, rA0
         mulsd rY3, rA0
         addsd -128(pA0,lda3), rA0
         movsd rZ3, ryt
         mulsd rW0, ryt
         addsd ryt, rA0
         movsd rA0, -128(pA0,lda3)
         movsd rX0, rA0
         mulsd rY4, rA0
         addsd -128(pA0,lda,4), rA0
         movsd rZ4, ryt
         mulsd rW0, ryt
         addsd ryt, rA0
         movsd rA0, -128(pA0,lda,4)
         add $8, pX
         add $8, pW
         add $8, pA0
      dec II
      jnz LOOPMCU

MCLEANED:
      prefY(5*8+PFYDIST(pY))
      add $5*8, pY
      sub M0, pX
      prefY(5*8+PFYDIST(pZ))
      add $5*8, pZ
      add incAn, pA0
      sub M0, pW
      mov M, II
   sub $5, N
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
