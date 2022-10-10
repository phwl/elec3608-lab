#ifndef ATLAS_DR1_L2_H
#define ATLAS_DR1_L2_H

#include "atlas_type.h"

typedef void (*ATL_r1kern_t)
   (ATL_CINT, ATL_CINT, const double*, const double*, double*, ATL_CINT);
void ATL_dgerk__900003
   (ATL_CINT, ATL_CINT, const double*, const double*, double*, ATL_CINT);
void ATL_dgerk__900009
   (ATL_CINT, ATL_CINT, const double*, const double*, double*, ATL_CINT);
void ATL_dgerk__3
   (ATL_CINT, ATL_CINT, const double*, const double*, double*, ATL_CINT);

static ATL_r1kern_t ATL_GetR1Kern
   (ATL_CINT M, ATL_CINT N, const void *A, ATL_CINT lda,
    int *mu, int *nu, int *minM, int *minN, int *alignX, int *ALIGNX2A,
    int *alignY, int *FNU, ATL_INT *CacheElts) 
{
   if ((((((((size_t)(A))) >> 4)) << 4)) == (size_t)(A))
   {
      if ((((((ATL_MulBySize(lda)) >> 4)) << 4)) == ATL_MulBySize(lda))
      {
         if (M >= 56)
         {
            *minM = 56;   *minN = 1;
            *mu = 56;     *nu = 1;
            *alignX = 16;  *alignY = 16;
            *ALIGNX2A = 0;
            *FNU = 1;
            *CacheElts = 16384;
            return(ATL_dgerk__900003);
         } /* end if on minimal N guard */
      } /* end if on lda multiple restriction */
   } /* end if on align of A */
   if ((((((((size_t)(A))) >> 4)) << 4)) == (size_t)(A))
   {
      if ((((((ATL_MulBySize(lda)) >> 4)) << 4)) == ATL_MulBySize(lda))
      {
         if (N >= 8)
         {
            if (M >= 8)
            {
               *minM = 8;   *minN = 8;
               *mu = 8;     *nu = 8;
               *alignX = 16;  *alignY = 16;
               *ALIGNX2A = 0;
               *FNU = 1;
               *CacheElts = 16384;
               return(ATL_dgerk__900009);
            } /* end if on minimal N guard */
         } /* end if on minimal M guard */
      } /* end if on lda multiple restriction */
   } /* end if on align of A */
   *minM = 0;   *minN = 0;
   *mu = 1;     *nu = 4;
   *alignX = 8;  *alignY = 8;
   *ALIGNX2A = 0;
   *FNU = 0;
   *CacheElts = 16384;
   return(ATL_dgerk__3);
}

#define ATL_GetPartR1(A_, lda_, mb_, nb_) { (mb_) = 1637; (nb_) = 4; }

#endif  /* end protection around header file contents */
