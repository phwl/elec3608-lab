#ifndef ATLAS_DMVN_L2_H
#define ATLAS_DMVN_L2_H

#include "atlas_type.h"

#ifndef ATL_MVKERN_DEF
   #define ATL_MVKERN_DEF
   typedef void (*ATL_mvkern_t)
      (ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);

#endif
void ATL_dmvnk__900009(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvnk__900009_b0(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvnk__900007(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvnk__900007_b0(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);

static ATL_mvkern_t ATL_GetMVNKern
   (ATL_CINT M, ATL_CINT N, const void *A, ATL_CINT lda,
    ATL_mvkern_t *mvk_b0, int *DOTBASED,
    int *mu, int *nu, int *minM, int *minN, int *alignX, int *ALIGNX2A,
    int *alignY, int *FNU, ATL_INT *CacheElts) 
{
   if ((((((((size_t)(A))) >> 4)) << 4)) == (size_t)(A))
   {
      if ((((((ATL_MulBySize(lda)) >> 4)) << 4)) == ATL_MulBySize(lda))
      {
         if (N >= 6)
         {
            if (M >= 8)
            {
               *minM = 8;   *minN = 6;
               *mu = 8;     *nu = 6;
               *alignX = 16;  *alignY = 16;
               *ALIGNX2A = 0;
               *FNU = 1;
               *CacheElts = 49152;
               *mvk_b0 = ATL_dmvnk__900009_b0;
               *DOTBASED = 0;
               return(ATL_dmvnk__900009);
            } /* end if on minimal N guard */
         } /* end if on minimal M guard */
      } /* end if on lda multiple restriction */
   } /* end if on align of A */
   *minM = 4;   *minN = 20;
   *mu = 4;     *nu = 20;
   *alignX = 8;  *alignY = 8;
   *ALIGNX2A = 0;
   *FNU = 1;
   *CacheElts = 49152;
   *mvk_b0 = ATL_dmvnk__900007_b0;
   *DOTBASED = 0;
   return(ATL_dmvnk__900007);
}

#define ATL_GetPartMVN(A_, lda_, mb_, nb_) { *(mb_) = 1168; *(nb_) = 20; }

#endif  /* end protection around header file contents */
