#ifndef ATLAS_DR2_L2_H
#define ATLAS_DR2_L2_H

#include "atlas_type.h"

typedef void (*ATL_r2kern_t)
   (ATL_CINT, ATL_CINT, const double*, const double*, const double*,
    const double*, double*, ATL_CINT);
void ATL_dger2k__900009
   (ATL_CINT, ATL_CINT, const double*, const double*, const double*,
    const double*, double*, ATL_CINT);
void ATL_dger2k__3
   (ATL_CINT, ATL_CINT, const double*, const double*, const double*,
    const double*, double*, ATL_CINT);
void ATL_dger2k__900007
   (ATL_CINT, ATL_CINT, const double*, const double*, const double*,
    const double*, double*, ATL_CINT);

static ATL_r2kern_t ATL_GetR2Kern
   (ATL_CINT M, ATL_CINT N, const void *A, ATL_CINT lda,
    int *mu, int *nu, int *minM, int *minN, int *alignX, int *ALIGNX2A,
    int *alignY, int *FNU, ATL_INT *CacheElts) 
{
   if ((((((((size_t)(A))) >> 4)) << 4)) == (size_t)(A))
   {
      if ((((((ATL_MulBySize(lda)) >> 4)) << 4)) == ATL_MulBySize(lda))
      {
         if (N >= 5)
         {
            if (M >= 8)
            {
               *minM = 8;   *minN = 5;
               *mu = 8;     *nu = 5;
               *alignX = 16;  *alignY = 16;
               *ALIGNX2A = 0;
               *FNU = 1;
               *CacheElts = 45056;
               return(ATL_dger2k__900009);
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
            *minM = 0;   *minN = 2;
            *mu = 2;     *nu = 2;
            *alignX = 16;  *alignY = 16;
            *ALIGNX2A = 0;
            *FNU = 1;
            *CacheElts = 45056;
            return(ATL_dger2k__3);
         } /* end if on minimal M guard */
      } /* end if on lda multiple restriction */
   } /* end if on align of A */
   *minM = 2;   *minN = 12;
   *mu = 2;     *nu = 12;
   *alignX = 8;  *alignY = 8;
   *ALIGNX2A = 0;
   *FNU = 1;
   *CacheElts = 45056;
   return(ATL_dger2k__900007);
}

#define ATL_GetPartR2(A_, lda_, mb_, nb_) { (mb_) = 1730; (nb_) = 12; }

#endif  /* end protection around header file contents */
