/*
 * This file generated on line 432 of /config/ATLAS/my_build_dir/..//tune/blas/ger/r1hgen.c
 */
#ifndef ATLAS_DSYR1_L2_H
   #define ATLAS_DSYR1_L2_H

#include "atlas_dr1_L2.h"

#define ATL_s1U_NU 8

#define ATL_s1L_NU 8
#define ATL_MIN_RESTRICTED_M 56
#define ATL_URGERK ATL_dgerk__3
#define ATL_GENGERK ATL_dgerk__3

#define ATL_SYR1U_nu(A_, lda_, x_, y_) \
{ \
   TYPE *aa=(A_); \
   ATL_CINT lda0_ = 0, lda1_ = lda0_+(lda_), lda2_ = lda1_+(lda_), lda3_ = lda2_+(lda_), lda4_ = lda3_+(lda_), lda5_ = lda4_+(lda_), lda6_ = lda5_+(lda_), lda7_ = lda6_+(lda_); \
   const TYPE x0_=*(x_), x1_=(x_)[1], x2_=(x_)[2], x3_=(x_)[3], x4_=(x_)[4], x5_=(x_)[5], x6_=(x_)[6], x7_=(x_)[7]; \
   const TYPE y0_=*(y_), y1_=(y_)[1], y2_=(y_)[2], y3_=(y_)[3], y4_=(y_)[4], y5_=(y_)[5], y6_=(y_)[6], y7_=(y_)[7]; \
   aa[lda0_+0] += x0_*y0_; \
   aa[lda1_+0] += x0_*y1_; \
   aa[lda1_+1] += x1_*y1_; \
   aa[lda2_+0] += x0_*y2_; \
   aa[lda2_+1] += x1_*y2_; \
   aa[lda2_+2] += x2_*y2_; \
   aa[lda3_+0] += x0_*y3_; \
   aa[lda3_+1] += x1_*y3_; \
   aa[lda3_+2] += x2_*y3_; \
   aa[lda3_+3] += x3_*y3_; \
   aa[lda4_+0] += x0_*y4_; \
   aa[lda4_+1] += x1_*y4_; \
   aa[lda4_+2] += x2_*y4_; \
   aa[lda4_+3] += x3_*y4_; \
   aa[lda4_+4] += x4_*y4_; \
   aa[lda5_+0] += x0_*y5_; \
   aa[lda5_+1] += x1_*y5_; \
   aa[lda5_+2] += x2_*y5_; \
   aa[lda5_+3] += x3_*y5_; \
   aa[lda5_+4] += x4_*y5_; \
   aa[lda5_+5] += x5_*y5_; \
   aa[lda6_+0] += x0_*y6_; \
   aa[lda6_+1] += x1_*y6_; \
   aa[lda6_+2] += x2_*y6_; \
   aa[lda6_+3] += x3_*y6_; \
   aa[lda6_+4] += x4_*y6_; \
   aa[lda6_+5] += x5_*y6_; \
   aa[lda6_+6] += x6_*y6_; \
   aa[lda7_+0] += x0_*y7_; \
   aa[lda7_+1] += x1_*y7_; \
   aa[lda7_+2] += x2_*y7_; \
   aa[lda7_+3] += x3_*y7_; \
   aa[lda7_+4] += x4_*y7_; \
   aa[lda7_+5] += x5_*y7_; \
   aa[lda7_+6] += x6_*y7_; \
   aa[lda7_+7] += x7_*y7_; \
}
#define ATL_SYR1L_nu(A_, lda_, x_, y_) \
{ \
   TYPE *aa=(A_); \
   ATL_CINT lda0_ = 0, lda1_ = lda0_+(lda_), lda2_ = lda1_+(lda_), lda3_ = lda2_+(lda_), lda4_ = lda3_+(lda_), lda5_ = lda4_+(lda_), lda6_ = lda5_+(lda_), lda7_ = lda6_+(lda_); \
   const TYPE x0_=*(x_), x1_=(x_)[1], x2_=(x_)[2], x3_=(x_)[3], x4_=(x_)[4], x5_=(x_)[5], x6_=(x_)[6], x7_=(x_)[7]; \
   const TYPE y0_=*(y_), y1_=(y_)[1], y2_=(y_)[2], y3_=(y_)[3], y4_=(y_)[4], y5_=(y_)[5], y6_=(y_)[6], y7_=(y_)[7]; \
   aa[lda0_+0] += x0_*y0_; \
   aa[lda0_+1] += x1_*y0_; \
   aa[lda0_+2] += x2_*y0_; \
   aa[lda0_+3] += x3_*y0_; \
   aa[lda0_+4] += x4_*y0_; \
   aa[lda0_+5] += x5_*y0_; \
   aa[lda0_+6] += x6_*y0_; \
   aa[lda0_+7] += x7_*y0_; \
   aa[lda1_+1] += x1_*y1_; \
   aa[lda1_+2] += x2_*y1_; \
   aa[lda1_+3] += x3_*y1_; \
   aa[lda1_+4] += x4_*y1_; \
   aa[lda1_+5] += x5_*y1_; \
   aa[lda1_+6] += x6_*y1_; \
   aa[lda1_+7] += x7_*y1_; \
   aa[lda2_+2] += x2_*y2_; \
   aa[lda2_+3] += x3_*y2_; \
   aa[lda2_+4] += x4_*y2_; \
   aa[lda2_+5] += x5_*y2_; \
   aa[lda2_+6] += x6_*y2_; \
   aa[lda2_+7] += x7_*y2_; \
   aa[lda3_+3] += x3_*y3_; \
   aa[lda3_+4] += x4_*y3_; \
   aa[lda3_+5] += x5_*y3_; \
   aa[lda3_+6] += x6_*y3_; \
   aa[lda3_+7] += x7_*y3_; \
   aa[lda4_+4] += x4_*y4_; \
   aa[lda4_+5] += x5_*y4_; \
   aa[lda4_+6] += x6_*y4_; \
   aa[lda4_+7] += x7_*y4_; \
   aa[lda5_+5] += x5_*y5_; \
   aa[lda5_+6] += x6_*y5_; \
   aa[lda5_+7] += x7_*y5_; \
   aa[lda6_+6] += x6_*y6_; \
   aa[lda6_+7] += x7_*y6_; \
   aa[lda7_+7] += x7_*y7_; \
}

#endif