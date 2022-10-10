#ifndef ATLAS_DMVT_L2_H
#define ATLAS_DMVT_L2_H

#include "atlas_type.h"

#ifndef ATL_MVKERN_DEF
   #define ATL_MVKERN_DEF
   typedef void (*ATL_mvkern_t)
      (ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);

#endif
void ATL_dmvtk__900009(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvtk__900009_b0(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvtk__900003(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvtk__900003_b0(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvtk__1(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvtk__1_b0(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);

static ATL_mvkern_t ATL_GetMVTKern
   (ATL_CINT M, ATL_CINT N, const void *A, ATL_CINT lda,
    ATL_mvkern_t *mvk_b0, 
    int *mu, int *nu, int *minM, int *minN, int *alignX, int *ALIGNX2A,
    int *alignY, int *FNU, ATL_INT *CacheElts) 
{
   if ((((((((size_t)(A))) >> 4)) << 4)) == (size_t)(A))
   {
      if ((((((ATL_MulBySize(lda)) >> 4)) << 4)) == ATL_MulBySize(lda))
      {
         if (N >= 4)
         {
            if (M >= 8)
            {
               *minM = 8;   *minN = 4;
               *mu = 8;     *nu = 4;
               *alignX = 16;  *alignY = 16;
               *ALIGNX2A = 0;
               *FNU = 1;
               *CacheElts = 24576;
               *mvk_b0 = ATL_dmvtk__900009_b0;
               return(ATL_dmvtk__900009);
            } /* end if on minimal N guard */
         } /* end if on minimal M guard */
      } /* end if on lda multiple restriction */
   } /* end if on align of A */
   if ((((((((size_t)(A))) >> 4)) << 4)) == (size_t)(A))
   {
      if ((((((ATL_MulBySize(lda)) >> 4)) << 4)) == ATL_MulBySize(lda))
      {
         if (N >= 2)
         {
            if (M >= 16)
            {
               *minM = 16;   *minN = 2;
               *mu = 16;     *nu = 2;
               *alignX = 16;  *alignY = 16;
               *ALIGNX2A = 0;
               *FNU = 1;
               *CacheElts = 24576;
               *mvk_b0 = ATL_dmvtk__900003_b0;
               return(ATL_dmvtk__900003);
            } /* end if on minimal N guard */
         } /* end if on minimal M guard */
      } /* end if on lda multiple restriction */
   } /* end if on align of A */
   *minM = 0;   *minN = 0;
   *mu = 16;     *nu = 1;
   *alignX = 8;  *alignY = 8;
   *ALIGNX2A = 0;
   *FNU = 0;
   *CacheElts = 24576;
   *mvk_b0 = ATL_dmvtk__1_b0;
   return(ATL_dmvtk__1);
}

#define ATL_GetPartMVT(A_, lda_, mb_, nb_) { *(mb_) = 6128; *(nb_) = 1; }

#endif  /* end protection around header file contents */
