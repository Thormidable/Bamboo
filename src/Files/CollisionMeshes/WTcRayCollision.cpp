#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

void cRayCollision::Update(cMatrix4 &New)
 {
    mfRaySize[0]=New[12]-GLastPos[0];
    mfRaySize[1]=New[13]-GLastPos[1];
    mfRaySize[2]=New[14]-GLastPos[2];

    mfLength=1.1f;
    mbNormalised=false;
	memcpy(GLastPos,New.Position(),sizeof(float)*3);
};

cRayCollision::cRayCollision(){lbCreated=true; memset(GLastPos,0,sizeof(float)*3); mbNormalised=false;}
cRayCollision::~cRayCollision(){};
cRayCollision *cRayCollision::Ray(){return this;};
bool cRayCollision::CreatedThisFrame(){return lbCreated;}

uint8 cRayCollision::Type(){return WT_COLLISION_RAY;};

void cRayCollision::PrepForCollision()
{
    if(!mbNormalised)
    {
        float lfSize=mfRaySize.Magnitude();
        mfLength*=lfSize;
        mfRaySize/=lfSize;
        mbNormalised=true;
    }
};

#endif
