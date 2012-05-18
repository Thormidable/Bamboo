#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

void cBeamCollision::Update(cMatrix4 &New)
{
 memcpy(mfRaySize.v,&New[8],sizeof(float)*3);
};



cBeamCollision::cBeamCollision(){mfLength=1.0f;mfRaySize=c3DVf(0.0f,0.0f,1.0f);};
cBeamCollision::~cBeamCollision(){};
void cBeamCollision::BuildObject(float lfLength,float lfRadius){mfLength=lfLength; SetSize(lfRadius);};
cBeamCollision *cBeamCollision::Beam(){return this;};
cRayCollision *cBeamCollision::Ray(){return 0;};
float cBeamCollision::RayVector(uint8 liPos){return mfRaySize[liPos];};
float *cBeamCollision::RayVector(){return mfRaySize.v;};
float cBeamCollision::Length(){return mfLength;};

uint8 cBeamCollision::Type(){return WT_COLLISION_BEAM;}

float cBeamCollision::Radius(){return mfSize;}
void cBeamCollision::Radius(float lfRadius){SetSize(lfRadius);}
void cBeamCollision::PrepForCollision(){};
#endif
