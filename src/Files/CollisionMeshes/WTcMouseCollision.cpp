#include "../../WTBamboo.h"

#if WT_FULL_BAMBOO_VERSION
void cMouseCollision::PrepForCollision()
{
  if(!mbNormalised)
    {
        mfRaySize.Normalise();

        mbNormalised=true;
    }
}

cMouseCollision::cMouseCollision()
{
 mbNormalised=false;
 SetSize(0.01f);
}

cMouseCollision *cMouseCollision::Mouse(){return this;};

#endif
