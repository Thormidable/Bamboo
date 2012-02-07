#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

void cRayCollision::Update(cMatrix4 &New)
 {
	 //Damn the slowness of this. DAMN.
	 uint32 DAMN_THE_SLOWNESS_OF_THIS_NEED_TO_FIX_EITHER_HOW_BEAMS_WORK_OR_HOW_TO_CALCULATE_THIS;
		 mfRaySize[0]=New[12]-GLastPos[0];
		 mfRaySize[1]=New[13]-GLastPos[1];
		 mfRaySize[2]=New[14]-GLastPos[2];

		 mfLength=sqrt(mfRaySize[0]*mfRaySize[0]+mfRaySize[1]*mfRaySize[1]+mfRaySize[2]*mfRaySize[2]);

		 float lfTemp=1.0f/mfLength;
		 mfRaySize[0]*=lfTemp;
		 mfRaySize[1]*=lfTemp;
		 mfRaySize[2]*=lfTemp;

	memcpy(GLastPos,New.Position(),sizeof(float)*3);
};

cRayCollision::cRayCollision(){lbCreated=true;}
cRayCollision::~cRayCollision(){};
cRayCollision *cRayCollision::Ray(){return this;};
bool cRayCollision::CreatedThisFrame(){return lbCreated;}

uint8 cRayCollision::Type(){return WT_COLLISION_RAY;};
#endif
