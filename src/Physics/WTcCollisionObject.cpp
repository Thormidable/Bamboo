#include "../WTBamboo.h"


float cCollisionObject::mfStaticSize[3]={0.0f,0.0f,0.0f};
float cCollisionObject::CollisionDistance=0.0f;




float *cCollisionObject::GetPos()
{
    #warning comment This Does not seem right. This should be the objects Local matrix...Surely
 return mpFollowing->GetCachedGlobalMatrix();
}

cCollisionList * cCollisionObject::GenerateCollisionList(uint32 liType)
{
  return _COLLISION_HANDLER->GenerateCollisionList(this,liType);
}




void cCollisionObject::CollisionFilter(uint32 liID)
{

if(mpOwner)
{
  cCollisionHandler::Instance()->mpList[miID].StitchOut(mpOwner);
  miID=liID;
  cCollisionHandler::Instance()->mpList[miID].StitchIn(mpOwner);
}
else miID=liID;
}



void cCollisionObject::PreUpdateCache()
{

if(mpOwner) cCollisionHandler::Instance()->mpList[cCollisionHandler::Instance()->FindSlot(this)].StitchOut(mpOwner);

}

void cCollisionObject::PostUpdateCache()
{

if(mpOwner) cCollisionHandler::Instance()->mpList[cCollisionHandler::Instance()->FindSlot(this)].StitchIn(mpOwner);

if(mpObject) mpObject->Update(mpFollowing->mmCache);

}



bool cCollisionObject::CompareRanges(float lf1,float lf2,float lfR)
{
if(lf1+lf2<lfR) return true;
return false;
}

bool cCollisionObject::Collision(cCollisionObject *lpOther,uint32 lpCol)
{
	uint32 THIS_SHOULD_NOT_BE_NECCESSARY;
	if(!lpCol || CollisionFilter()==lpCol)
	{

		if(CheckCollision(lpOther)) return 1;
	}
	return 0;
}

bool cCollisionObject::Collision(cCollisionObject *lpOther)
{
	if(CheckCollision(lpOther)) return 1;
	return 0;
}


cCollisionObject::~cCollisionObject()
{

	mbAlive=false;
	mbAwake=false;
	mpLinked=0;


if(mpOwner){ cCollisionHandler::Instance()->RemoveFromList(mpOwner); mpOwner=0;}

mpFollowing->LinkCollisionObject(0);


};

void cCollisionObject::AdditionalKillFunctionality()
{
    //delete this;
}

cCollisionObject::cCollisionObject(vRenderObject *lpFollow,cProcess *lpLinked,uint32 liFilterType)
{

		mpOwner=0;

		mpLinked=0;
		mpFollowing=0;

	Initialise(lpFollow,lpLinked,liFilterType);
	SetType(1.0f);

};


void cCollisionObject::Initialise(vRenderObject *lpFollow,cProcess *lpLinked,uint32 liFilterType)
{

	ClearProcedural();


	if(mpOwner){ cCollisionHandler::Instance()->RemoveFromList(mpOwner); mpOwner=0;}


	SetLink(lpLinked);

	miType=0;
	mbAlive=true;
	mbAwake=true;
	if(mpFollowing) mpFollowing->LinkCollisionObject(0);
	mpFollowing=lpFollow;
	mpFollowing->LinkCollisionObject(this);
	miID=liFilterType;

			mpOwner=cCollisionHandler::Instance()->Add(this);

    mbCreatedThisFrame=true;

}

	cMatrix4& cCollisionObject::CacheMatrix(){return mpFollowing->mmCache;};
	vRenderObject *cCollisionObject::RenderObject(){return mpFollowing;};
	uint32 cCollisionObject::CollisionFilter(){return miID;};


	bool cCollisionObject::CreatedThisFrame(){return mbCreatedThisFrame;};

	void cCollisionObject::NotCreatedThisFrame(){mbCreatedThisFrame=false;};



void cCollisionObject::Signal(SIGNAL liFlags)
{

	if(liFlags&WT_SIGNAL_VALUE_WAKE && Asleep())
	{
		if(mpObject) mbAwake=true;
		else cCollisionBase::SetType(1.0f);

		if(!mpOwner) mpOwner=cCollisionHandler::Instance()->Add(this);

	}
	if(liFlags&WT_SIGNAL_VALUE_SLEEP)
	{
		if(Awake())
		{
			mbAwake=false;

			if(mpOwner){ cCollisionHandler::Instance()->RemoveFromList(mpOwner); mpOwner=0;}

		}
	}

	if(liFlags&WT_SIGNAL_VALUE_KILL) {delete this;}

}

	bool cCollisionObject::SphereSphere(cCollisionObject *lpOther)
	{
        return SphereSphere(Sphere(),mpFollowing->mmCache,lpOther->Sphere(),lpOther->mpFollowing->mmCache);
	};

#if WT_FULL_VERSION_BAMBOO

bool cCollisionObject::CheckCollision(cCollisionObject *lpOther)
{

	if(Asleep() || lpOther->Asleep() || CreatedThisFrame() || lpOther->CreatedThisFrame()) return 0;
	if(!TouchCollision(lpOther)) return 0;

	if((Type()==WT_COLLISION_RADIUS || Type()==WT_COLLISION_BEAM) && (lpOther->Type()==WT_COLLISION_RADIUS || lpOther->Type()==WT_COLLISION_BEAM)) return 1;
	if(Type()==WT_COLLISION_MODEL)
	{
		if(lpOther->Type()==WT_COLLISION_RADIUS) return SphereModel(lpOther->Sphere(),lpOther->CacheMatrix(),Mesh(),CacheMatrix());
		if(lpOther->Type()==WT_COLLISION_MODEL) return ModelModel(Mesh(),CacheMatrix(),lpOther->Mesh(),lpOther->CacheMatrix());
		if(lpOther->Type()==WT_COLLISION_BEAM) return RayModel(lpOther->Beam(),lpOther->CacheMatrix(),Mesh(),CacheMatrix());
	}
	if(Type()==WT_COLLISION_BEAM)
	{
		if(lpOther->Type()==WT_COLLISION_MODEL) return RayModel(Beam(),CacheMatrix(),lpOther->Mesh(),lpOther->CacheMatrix());
	}

	if(Type()==WT_COLLISION_RADIUS)
	{
		if(lpOther->Type()==WT_COLLISION_MODEL) return SphereModel(Sphere(),CacheMatrix(),lpOther->Mesh(),lpOther->CacheMatrix());
	}

	return 0;
}

bool cCollisionObject::TouchCollision(cCollisionObject *lpOther)
{

	if(Beam() || lpOther->Beam())
	{

		if(Beam() && lpOther->Beam()){ return RayRay(Beam(),mpFollowing->mmCache,lpOther->Beam(),lpOther->mpFollowing->mmCache); }
		else
		{

			return SphereRay(lpOther);
		}
	}
	else
	{
		return SphereSphere(Sphere(),mpFollowing->mmCache,lpOther->Sphere(),lpOther->mpFollowing->mmCache);
	}
};


cCollisionObject::cCollisionObject(cBeamMesh *lpFollow,cProcess *lpLinked,uint32 liFilterType)
{

	mpOwner=0;

	mpLinked=0;
	mpFollowing=0;

	Initialise(lpFollow,lpLinked,liFilterType);
	SetType(lpFollow);
};

cRayCollision *cCollisionObject::SetType(cRenderObject *lpObj)
{

	mpFollowing=lpObj;
	OnProcedural();
	miType=WT_COLLISION_RAY;
	mpObject=new cRayCollision;
	Ray()->SetSize(1.0f);
	return Ray();

};



	bool cCollisionObject::ModelModel(cCollisionObject *lpOther)
	{
	    return ModelModel(Mesh(),(mpFollowing->mmCache),lpOther->Mesh(),(lpOther->mpFollowing->mmCache));
	};

	bool cCollisionObject::RayRay(cCollisionObject *lpOther)
	{
	    return RayRay(Beam(),(mpFollowing->mmCache),lpOther->Beam(),(lpOther->mpFollowing->mmCache));
	};

	bool cCollisionObject::SphereModel(cCollisionObject *lpOther)
	{
	    if(Mesh()){return SphereModel(lpOther->Sphere(),(lpOther->mpFollowing->mmCache),Mesh(),(mpFollowing->mmCache));}
	    else{return SphereModel(Sphere(),(mpFollowing->mmCache),lpOther->Mesh(),(lpOther->mpFollowing->mmCache));}
	};

	bool cCollisionObject::SphereRay(cCollisionObject *lpOther)
	{
        if(Beam()){return SphereRay(lpOther->Sphere(),(lpOther->mpFollowing->mmCache),Beam(),(mpFollowing->mmCache));}
	    else{return SphereRay(Sphere(),(mpFollowing->mmCache),lpOther->Beam(),(lpOther->mpFollowing->mmCache));}
	};

	bool cCollisionObject::RayModel(cCollisionObject *lpOther)
	{
	    if(Mesh()){return RayModel(lpOther->Beam(),(lpOther->mpFollowing->mmCache),Mesh(),(mpFollowing->mmCache));}
	    else{return RayModel(Beam(),(mpFollowing->mmCache),lpOther->Mesh(),(lpOther->mpFollowing->mmCache));}
	};

#else

bool cCollisionObject::CheckCollision(cCollisionObject *lpOther)
{

	if(Asleep() || lpOther->Asleep() || CreatedThisFrame() || lpOther->CreatedThisFrame()) return 0;
	return TouchCollision(lpOther);

}

bool cCollisionObject::TouchCollision(cCollisionObject *lpOther)
{
		return SphereSphere(Sphere(),mpFollowing->mmCache,lpOther->Sphere(),lpOther->mpFollowing->mmCache);
};

#endif
