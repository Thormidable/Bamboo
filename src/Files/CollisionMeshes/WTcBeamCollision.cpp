#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

void cBeamCollision::Update(cMatrix4 &New)
{
/*
	 mfRaySize[0]=New[8]*mfLength;
	 mfRaySize[1]=New[9]*mfLength;
	 mfRaySize[2]=New[10]*mfLength;
*/
mfRaySize[0]=New[8];
mfRaySize[1]=New[9];
mfRaySize[2]=New[10];

/*
	mfRaySize[0]=0.0f;
	mfRaySize[1]=0.0f;
	mfRaySize[2]=mfLength;*/
};



cBeamCollision::cBeamCollision(){mfLength=1.0f;mfRaySize[0]=0.0f;mfRaySize[1]=0.0f;mfRaySize[2]=1.0f;};
cBeamCollision::~cBeamCollision(){};
void cBeamCollision::BuildObject(float lfLength,float lfRadius){mfLength=lfLength; SetSize(lfRadius);};
cBeamCollision *cBeamCollision::Beam(){return this;};
cRayCollision *cBeamCollision::Ray(){return 0;};
float cBeamCollision::RayVector(uint8 liPos){return mfRaySize[liPos];};
float *cBeamCollision::RayVector(){return mfRaySize;};
float cBeamCollision::Length(){return mfLength;};

#endif
