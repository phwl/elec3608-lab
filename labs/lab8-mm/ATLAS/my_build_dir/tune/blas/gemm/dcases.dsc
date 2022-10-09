<ID> <flag> <mb> <nb> <kb> <muladd> <lat> <mu> <nu> <ku> <rout> "<Contributer>"
79
  1 480 4 4  1 1 1 4 4  2 ATL_mm4x4x2US.c        "V. Nguyen & P. Strazdins"
  2   8 4 4  2 1 1 4 4  2 ATL_mm4x4x2_1_pref.c   "R. Clint Whaley"
  3 208 4 4  1 1 1 4 4  2 ATL_mm4x4x2_1_prefCU.c "R. Clint Whaley"
  5 192 4 4  8 0 4 4 4  8 ATL_mm4x4x8_bpfabc.c   "R. Clint Whaley"
  6 192 4 3  8 0 4 4 3  8 ATL_mm4x3x8p.c         "R. Clint Whaley"
  7   8 4 3  2 0 4 4 3  2 ATL_mm4x3x2p.c         "R. Clint Whaley"
  8 448 4 2  8 1 8 4 2  4 ATL_amm4x2xVL_simd.c   "R. Clint Whaley"
  9 448 8 2  8 1 8 8 2  4 ATL_amm8x2xVL_simd.c   "R. Clint Whaley"
 10 448 8 4  8 1 8 8 4  4 ATL_amm8x4xVL_simd.c   "R. Clint Whaley"
 11 448 8 5  8 1 8 8 5  4 ATL_amm8x5xVL_simd.c   "R. Clint Whaley"
 12 448 8 6  8 1 8 8 6  4 ATL_amm8x6xVL_simd.c   "R. Clint Whaley"
 13 448 4 3  8 1 8 4 3  4 ATL_amm4x3xVL_simd.c   "R. Clint Whaley"
 14 448 4 4  8 1 8 4 4  4 ATL_amm4x4xVL_simd.c   "R. Clint Whaley"
 15 448 4 5  8 1 8 4 5  4 ATL_amm4x5xVL_simd.c   "R. Clint Whaley"
 16 448 4 6  8 1 8 4 6  4 ATL_amm4x6xVL_simd.c   "R. Clint Whaley"
200   8   4   1   4 1 1 4  1  4 ATL_gemm_SSE.c          "Camm Maguire" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
201 208   1   1   4 1 1 1  1  4 ATL_gemm_SSE.c          "Camm Maguire" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
202   8 -80 -80 -80 0 3 1  4  8 ATL_dmm_sse2_80.c       "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
203  80   0 -80 -80 0 3 1  4  8 ATL_dmm_sse2_80M.c      "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
204 144 -80   0 -80 0 3 1  4  8 ATL_dmm_sse2_80N.c      "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
205  16   4   1   4 1 1 1  4  4 ATL_dmm_sse2_K.c "P. Soendergaard & C. Maguire" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
206  16   4   1  -2 1 1 1  4  2 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
207  16   4   1  -6 1 1 1  4  2 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
208  16   4   1 -10 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
209  16   4   1 -14 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
210  16   4   1 -18 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
211  16   4   1 -22 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
212  16   4   1 -26 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
213  16   4   1 -30 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
214  16   4   1 -34 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
215  16   4   1 -38 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
216  16   4   1 -42 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
217  16   4   1 -46 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
218  16   4   1 -50 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
219  16   4   1 -54 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
220  16   4   1 -58 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
221  16   4   1 -62 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
222  16   4   1 -66 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
223  16   4   1 -70 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
224  16   4   1 -74 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
225  16   4   1 -78 1 1 1  4  8 ATL_dmm_sse2_K.c        "Peter Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O
228 192   6   1   2 0 1 6  1 72 ATL_dmm6x1x72_sse2.c    "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
229 208 14 1 -56 1 1 14 1 56 ATL_dmm14x1x56_sse2pABC_MN.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-m64 -x assembler-with-cpp
230  16 -56 -56  1 1 1 28 1 2 ATL_dmm14x1x56_sse2pABC_K.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-m64 -x assembler-with-cpp
231   8 -56 -56 -56 1 1 14 1 56 ATL_dmm14x1x56_sse2pABC.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-m64 -x assembler-with-cpp
232 128   6   1 -60 1 1  6 1 60 ATL_dmm6x1x60_sse2_32.c   "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-m32 -x assembler-with-cpp
233  80   1   6 -72 0 1 1  6 72 ATL_dmm1x6x72_sse2.c      "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
234  16   6   1 2 0 1 6  1 72 ATL_dmm6x1x72_sse2_K.c      "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
235 208 1 14 -56 1 1 1 14 56 ATL_dmm1x14x56_sse2pABC.c    "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-m64 -x assembler-with-cpp
236 192   6   1 -72 0 1 6  1 72 ATL_dmm6x1x72_sse2.c      "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
237 128   6   1 -60 1 1  6 1 60 ATL_dmm6x1x60_sse2_32.c   "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
238 192   4   1 -44 0 4  4 1 44 ATL_dmm4x1x44_4_sse2.c    "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
239 736 8 0 2 0 1 8 1 2 ATL_dmm8x1x120_L1pf.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp -m64
241 224 4 2 2 0 1 4 2 2 ATL_dmm4x2x128_sse2.c "Whaley & Voronenko" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp -m64
242 480 2 2 2 0 1 2 2 2 ATL_dmm2x2x2_sse2.c   "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
243 224 2 2 2 0 1 2 2 2 ATL_dmm2x2x128_sse2.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
244 192   4   2   4 0 1  4 2   4 ATL_dmm4x2x4_avx.c  "R. Clint Whaley"
245 224 4 2 4 0 1 4 2 4 ATL_dmm4x2x256_avx.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp -mavx
246 192 2 4 2 0 1 2 4 2 ATL_dmm2x4x256_fma4.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp -m64
308 192 4 4 8 0 4 4 4 8 ATL_mm4x4x8p.c     "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-O -fno-schedule-insns -fno-schedule-insns2 -fomit-frame-pointer
309 192 4 4 -56 1 0 4 4 56 ATL_mm4x4x56_av.c  "R. Clint Whaley"
310 192 4 4 8 1 0 4 4 8   ATL_mm4x4x8_av.c    "R. Clint Whaley"
311 192 4 4 4 1 0 4 4 4   ATL_mm4x4x4_av.c    "R. Clint Whaley"
312 496 4 4 2 1 0 4 4 2   ATL_mm4x4x4_av.c    "R. Clint Whaley"
313   8 6 8 8 1 1 6 8 8 ATL_mm6x8x8_1p.c       "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-schedule-insns -fno-schedule-insns2
314 496 0 0 0 1 1 6 8 8 ATL_mm6x8x8_1p.c       "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-schedule-insns -fno-schedule-insns2
316   8 -30   0 -30 0 4 30 1 30 ATL_dmm_julian_gas_30.c "Julian Ruhe & P. Soendergaard" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O1 -fno-schedule-insns -fno-schedule-insns2
317 192 4 1 -40 0 4 2 1 40 ATL_dmm2x1x40_5pABC.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
319 128 6 0 1 0 1 6 1 30 ATL_dmm6x1x30_x87.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
320   8 120 120 120 1 1 8 8 2 ATL_mm8x8x2.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-schedule-insns -fno-schedule-insns2 -fno-expensive-optimizations -falign-loops=64
321 480 8 8 2 1 1 8 8 2 ATL_mm8x8x2.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-schedule-insns -fno-schedule-insns2 -fno-expensive-optimizations -falign-loops=64
325 192 4 4 16 1 1 4 4 16 ATL_dmm4x4x16_hppa.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
327 224 4 0 1 0 1 4 1 60 ATL_dmm4x1x90_x87.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
328 224 8 0 2 0 1 4 1 2 ATL_dmm8x1x120_sse2.c "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
329   8 6 8 8 1 1 6 8 8 ATL_mm6x8x8_1p.c       "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-tree-loop-optimize
330 496 0 0 0 1 1 6 8 8 ATL_mm6x8x8_1p.c       "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-tree-loop-optimize
331   8 120 120 120 1 1 8 8 2 ATL_mm8x8x2.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-tree-loop-optimize
332 480 8 8 2 1 1 8 8 2 ATL_mm8x8x2.c  "R. Clint Whaley" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-fomit-frame-pointer -O2 -fno-tree-loop-optimize
337 192 4 4 1 1 16 4 4 1 ATL_dmm4x4x80_ppc.c "Whaley & Castaldo" \
/usr/bin/gcc -fomit-frame-pointer -mfpmath=387 -O2 -msse3 -m64 -m64
-x assembler-with-cpp
