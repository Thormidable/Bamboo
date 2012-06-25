#include "../../WTBamboo.h"

cSphereCollision::cSphereCollision(){mfSize=0.0f;};
cSphereCollision::~cSphereCollision(){};
void cSphereCollision::SetSize(float lfSize){mfSize=lfSize;};
float cSphereCollision::CollisionSize(){return mfSize;};
cSphereCollision *cSphereCollision::Sphere(){return this;};

#if WT_FULL_VERSION_BAMBOO
    cBeamCollision *cSphereCollision::Beam(){return 0;};
    cMeshCollision *cSphereCollision::Mesh(){return 0;};
    cRayCollision *cSphereCollision::Ray(){return 0;};
    cCompoundCollision *cSphereCollision::Compound(){return 0;};
	cMouseCollision *cSphereCollision::Mouse(){return 0;};
#endif

void cSphereCollision::Update(cMatrix4 &New){(void) New;};

uint8 cSphereCollision::Type(){return WT_COLLISION_RADIUS;}



