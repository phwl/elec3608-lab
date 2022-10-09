<ID> <flag> <mb> <nb> <kb> <muladd> <lat> <mu> <nu> <ku> <rout> "<Contributer>"
58
  1 480 4 4  1 1 1 4 4  2 ATL_mm4x4x2US.c        "V. Nguyen & P. Strazdins"
  2   8 4 4  2 1 1 4 4  2 ATL_mm4x4x2_1_pref.c   "R. Clint Whaley"
  3 208 4 4  1 1 1 4 4  2 ATL_mm4x4x2_1_prefCU.c "R. Clint Whaley"
  5 192 4 4  8 0 4 4 4  8 ATL_mm4x4x8_bpfabc.c   "R. Clint Whaley"
  6 192 4 3  8 0 4 4 3  8 ATL_mm4x3x8p.c         "R. Clint Whaley"
  7   8 4 3  2 0 4 4 3  2 ATL_mm4x3x2p.c         "R. Clint Whaley"
  8 448 4 2 16 1 8 4 2  8 ATL_amm4x2xVL_simd.c   "R. Clint Whaley"
  9 448 8 2 16 1 8 8 2  8 ATL_amm8x2xVL_simd.c   "R. Clint Whaley"
 10 448 8 4 16 1 8 8 4  8 ATL_amm8x4xVL_simd.c   "R. Clint Whaley"
 11 448 8 5 16 1 8 8 5  8 ATL_amm8x5xVL_simd.c   "R. Clint Whaley"
 12 448 8 6 16 1 8 8 6  8 ATL_amm8x6xVL_simd.c   "R. Clint Whaley"
 13 448 4 3 16 1 8 4 3  8 ATL_amm4x3xVL_simd.c   "R. Clint Whaley"
 14 448 4 4 16 1 8 4 4  8 ATL_amm4x4xVL_simd.c   "R. Clint Whaley"
 15 448 4 5 16 1 8 4 5  8 ATL_amm4x5xVL_simd.c   "R. Clint Whaley"
 16 448 4 6 16 1 8 4 6  8 ATL_amm4x6xVL_simd.c   "R. Clint Whaley"
200   8   4   1    4 1 1 4  1 4 ATL_gemm_SSE.c       "Camm Maguire" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
201 208   1   1    4 1 1 1  1 4 ATL_gemm_SSE.c       "Camm Maguire" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
202   8   4   1  -56 1 1 4  1 56 ATL_smm_sse1_56.c   "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
203   8   4   1  -60 1 1 4  1 56 ATL_smm_sse1_60.c   "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
204   8   4   1  -64 1 1 4  1 56 ATL_smm_sse1_64.c   "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
205  16   0   2  -56 1 1 4  1 56 ATL_smm_sse1_56M.c  "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
206  16   2   0  -56 1 1 4  1 56 ATL_smm_sse1_56N.c  "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
207  16   0   2  -60 1 1 4  1 60 ATL_smm_sse1_60M.c  "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
208  16   2   0  -60 1 1 4  1 60 ATL_smm_sse1_60N.c  "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
209  16   0   2  -64 1 1 4  1 64 ATL_smm_sse1_64M.c  "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
210  16   2   0  -64 1 1 4  1 64 ATL_smm_sse1_64N.c  "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
211  16   4   1    4 1 1 4  1  4 ATL_smm_sse1_K.c "P. Soendergaard & C. Maguire" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
212   8   4   1 -112 1 1 4  1 16 ATL_smm_sse2_112.c  "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
213  16   0   1 -112 1 1 4  1 16 ATL_smm_sse2_112M.c "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
214  16   4   0 -112 1 1 4  1 16 ATL_smm_sse2_112N.c "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
215  16   4   1    4 1 1 4  1  4 ATL_smm_sse2_112N.c "P. Soendergaard & C. Maguire" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
216   8   6   1 -60 0 1 6  1 60 ATL_smm6x1x60_sse.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
217   8  14   1 -84 0 1 14  1 84 ATL_smm14x1x84_sse.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
218 208  14   1   4 0 1 14  1 84 ATL_smm14x1x84_sseCU.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
219 128 6 1 -120 1 1 6 1 120  ATL_smm6x1x120_sse.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
220 192   6   1   4 0 1 6  1 80 ATL_smm6x1x80_sse.c    "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
221 192  10   1   4 0 1 10 1 120 ATL_smm10x1x120_sse.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
222 192   4   1   4 0 1  4 1 256 ATL_smm4x1x256_sse.c   "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
223 224   2   2   4 0 1  2 2   4 ATL_smm2x2x256_sse.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
224 192   4   2   8 0 1  4 2   8 ATL_smm4x2x8_avx.c  "R. Clint Whaley"
225 224   4   2   8 0 1  4 2   8 ATL_smm4x2x256_avx.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp -mavx
226 192 2 4 4 0 1 2 4 4 ATL_smm2x4x256_fma4.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp -m64
306 192 4 4 8 0 4 4 4 8 ATL_mm4x4x8p.c     "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-O -fomit-frame-pointer -fno-schedule-insns -fno-schedule-insns2
307 192 4 4 16 1 0 4 4 16 ATL_smm4x4x16_av.c  "R. Clint Whaley"
308 192 4 4  4 1 0 4 4  4 ATL_smm4x4x4_av.c  "R. Clint Whaley"
309  16 0 0  4 1 0 4 4  4 ATL_smmMNCU_av.c  "R. Clint Whaley"
310   8 6 8 8 1 1 6 8 8 ATL_mm6x8x8_1p.c       "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-schedule-insns -fno-schedule-insns2
311 496 0 0 0 1 1 6 8 8 ATL_mm6x8x8_1p.c       "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-schedule-insns -fno-schedule-insns2
319 128 6 0 1 0 1 6 1 60 ATL_smm6x1x60_x87.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
320   8 120 120 120 1 1 8 8 2 ATL_mm8x8x2.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-schedule-insns -fno-schedule-insns2 -fno-expensive-optimizations -falign-loops=64
321 480 8 8 2 1 1 8 8 2 ATL_mm8x8x2.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-schedule-insns -fno-schedule-insns2 -fno-expensive-optimizations -falign-loops=64
324 192 4 4 16 1 1 4 4 16 ATL_smm4x4x16_hppa.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
325   8 6 8 8 1 1 6 8 8 ATL_mm6x8x8_1p.c       "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-tree-loop-optimize
326 496 0 0 0 1 1 6 8 8 ATL_mm6x8x8_1p.c       "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-tree-loop-optimize
327   8 120 120 120 1 1 8 8 2 ATL_mm8x8x2.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-tree-loop-optimize
328 480 8 8 2 1 1 8 8 2 ATL_mm8x8x2.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-tree-loop-optimize
329 192 4 4 4 1 16 4 4 4 ATL_cmm4x4x128_av.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
332 192 8 2 4 1 0 8 2 4 ATL_smm8x2x4_av.c  "IBM"
