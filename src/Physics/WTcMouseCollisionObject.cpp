#include "stdafx.h"
#include "../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO


float *cMouseCollisionObject::GetPos()
{
    return mpObject->Mouse()->mpMatrix.Position();
}


cCollisionList * cMouseCollisionObject::GenerateCollisionList(uint32 liType)
{
  return _COLLISION_HANDLER->GenerateCollisionList(this,liType);
}

cMouseCollisionObject::~cMouseCollisionObject()
{

	mbAlive=false;
	mbAwake=false;

};

void cMouseCollisionObject::Stop()
{
    //delete this;
}

cMouseCollisionObject::cMouseCollisionObject(cCamera *lpCamera)
{
    mpObject=new cMouseCollision();
	Initialise(lpCamera);
};


void cMouseCollisionObject::Initialise(cCamera *lpCamera)
{
    mpCamera=lpCamera;
	mbAlive=true;
	mbAwake=true;

	mpObject->Mouse()->mfLength=mpCamera->Far();
	CalculateVector();
	CalculateStart();
}

void cMouseCollisionObject::CalculateVector()
{
    if((_MOUSE->X()>mpCamera->ViewportX() && _MOUSE->X()<mpCamera->ViewportX()+mpCamera->ViewportWidth())&&(_MOUSE->Y()>mpCamera->ViewportY() && _MOUSE->Y()<mpCamera->ViewportY()+mpCamera->ViewportHeight()))
    {
        float lfWidthMod=(((_MOUSE->X()-mpCamera->ViewportX())/mpCamera->ViewportWidth())-0.5f)*mpCamera->Width();
        float lfHeightMod=(((_MOUSE->Y()-mpCamera->ViewportY())/mpCamera->ViewportHeight())-0.5f)*mpCamera->Height();
        float lfDepthMod=(mpCamera->Near());

        printf("WidthMod : %f\n",lfWidthMod);
        printf("HeightMod : %f\n",lfHeightMod);
        printf("DepthMod : %f\n",lfDepthMod);

        float* lpMatrix=mpCamera->Matrix();
      mpObject->Mouse()->mfRaySize=c3DVf((lpMatrix[0]*lfWidthMod+lpMatrix[1]*lfHeightMod+lpMatrix[2]*lfDepthMod),
                                    -(lpMatrix[4]*lfWidthMod+lpMatrix[5]*lfHeightMod+lpMatrix[6]*lfDepthMod),
                                    -(lpMatrix[8]*lfWidthMod+lpMatrix[9]*lfHeightMod+lpMatrix[10]*lfDepthMod));
printf("Vector X: %f,%f,%f\n",(lpMatrix[0]*lfWidthMod+lpMatrix[1]*lfHeightMod+lpMatrix[2]*lfDepthMod),
-(lpMatrix[4]*lfWidthMod+lpMatrix[5]*lfHeightMod+lpMatrix[6]*lfDepthMod),
-(lpMatrix[8]*lfWidthMod+lpMatrix[9]*lfHeightMod+lpMatrix[10]*lfDepthMod));


        mpObject->Mouse()->mbNormalised=false;
    }
}


void cMouseCollisionObject::CalculateStart()
{
    mpObject->Mouse()->mpMatrix[12]=mpCamera->X();
    mpObject->Mouse()->mpMatrix[13]=mpCamera->Y();
    mpObject->Mouse()->mpMatrix[14]=mpCamera->Z();
}


void cMouseCollisionObject::Signal(SIGNAL liFlags)
{

	if(liFlags&WT_SIGNAL_VALUE_WAKE && Asleep())
	{
		if(mpObject) mbAwake=true;
		else cCollisionBase::SetType(1.0f);

	}
	if(liFlags&WT_SIGNAL_VALUE_SLEEP)
	{
		if(Awake())
		{
			mbAwake=false;
		}
	}

	if(liFlags&WT_SIGNAL_VALUE_KILL) {delete this;}

}

void cMouseCollisionObject::CheckCollisionDetail()
{
 	if(cCollisionList::mpOther->Asleep() || cCollisionList::mpOther->IsDelayed()) return;

	if(!TouchCollision()) return;

	if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL) {cCollisionBase::RayModelDetail(mpObject->Mouse(),mpObject->Mouse()->mpMatrix,cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix()); return;}
	if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) {cCollisionObject::CompoundCollisionDetail(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->RenderObject()->mmCache,mpObject->Mouse(),mpObject->Mouse()->mpMatrix); return;}
	if(cCollisionList::mpOther->Type()==WT_COLLISION_RAY || cCollisionList::mpOther->Type()==WT_COLLISION_BEAM) {cCollisionBase::RayRayDetail(mpObject->Mouse(),mpObject->Mouse()->mpMatrix,cCollisionList::mpOther->Beam(),cCollisionList::mpOther->CacheMatrix()); return;}
	if(cCollisionList::mpOther->Type()==WT_COLLISION_RADIUS) {cCollisionBase::SphereRayDetail(cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->RenderObject()->mmCache,mpObject->Mouse(),mpObject->Mouse()->mpMatrix); return;}
}


bool cMouseCollisionObject::CheckCollision()
{
 	if(cCollisionList::mpOther->Asleep() || cCollisionList::mpOther->IsDelayed()) return 0;

	if(!TouchCollision()) return 0;


	if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL) return cCollisionBase::RayModel(mpObject->Mouse(),mpObject->Mouse()->mpMatrix,cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix());
	if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) return cCollisionObject::CompoundCollision(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->RenderObject()->mmCache,mpObject->Mouse(),mpObject->Mouse()->mpMatrix);



	return 0;
}

bool cMouseCollisionObject::TouchCollision()
{
    mpObject->Mouse()->PrepForCollision();
    if(cCollisionList::mpOther->Beam())
    {
        cCollisionList::mpOther->Beam()->PrepForCollision();
		return RayRay(mpObject->Mouse(),mpObject->Mouse()->mpMatrix,cCollisionList::mpOther->Beam(),cCollisionList::mpOther->RenderObject()->mmCache);
    }
    else
    {
        return cCollisionObject::SphereRay(cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->RenderObject()->mmCache,mpObject->Mouse(),mpObject->Mouse()->mpMatrix);
    }
};


bool cMouseCollisionObject::CheckCollision(cCollisionObject *lpOther)
{
    cCollisionList::mpOther=lpOther;
    return CheckCollision();
}

bool cMouseCollisionObject::TouchCollision(cCollisionObject *lpOther)
{
    cCollisionList::mpOther=lpOther;
    return TouchCollision();
};

cCollisionList *cMouseCollisionObject::CheckCollisionDetail(cCollisionObject *lpOther,cCollisionList *lpList)
{
    if(!lpList) cCollisionList::mpStaticList=new cCollisionList(lpOther);
    else cCollisionList::mpStaticList=lpList;
    cCollisionList::mpOther=lpOther;
    CheckCollisionDetail();
    return cCollisionList::mpStaticList;
}

cMatrix4 &cMouseCollisionObject::CacheMatrix()
{
    return mpObject->Mouse()->mpMatrix;
};

#endif
