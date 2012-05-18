#include "../../WTBamboo.h"

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
