
#include "../WTBamboo.h"


float cCollisionObject::mfStaticSize[3]={0.0f,0.0f,0.0f};
float cCollisionObject::CollisionDistance=0.0f;

float *cCollisionObject::GetPos()
{
    #pragma warning This Does not seem right. This should be the objects Local matrix...Surely
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
  if(liID!=miID)
  {
    mpOwner->List()->StitchOut(mpOwner);
    miID=liID;
    cCollisionHandler::Instance()->mpList[miID].StitchIn(mpOwner);
  }
}
else miID=liID;
}



void cCollisionObject::PostUpdateCache()
{
 if(miDelay) --miDelay;
if(cCollisionHandler::Instance()->RequiresSlotUpdate())
{
 cLinkedList<cCollisionBase> *lpList=&(cCollisionHandler::Instance()->mpList[cCollisionHandler::Instance()->FindSlot(this)]);
    if(mpOwner && lpList!=mpOwner->List())
    {
        mpOwner->List()->StitchOut(mpOwner);
        lpList->StitchIn(mpOwner);
    }
}

if(mpObject) mpObject->Update(mpFollowing->mmCache);

}



bool cCollisionObject::CompareRanges(float lf1,float lf2,float lfR)
{
if(lf1+lf2<lfR) return true;
return false;
}

cCollisionObject::~cCollisionObject()
{

	mbAlive=false;
	mbAwake=false;
	mpLinked=0;


if(mpOwner){ cCollisionHandler::Instance()->RemoveFromList(mpOwner); mpOwner=0;}

mpFollowing->LinkCollisionObject(0);


};

void cCollisionObject::Stop()
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

	mbAlive=true;
	mbAwake=true;
	if(mpFollowing) mpFollowing->LinkCollisionObject(0);
	mpFollowing=lpFollow;
	mpFollowing->LinkCollisionObject(this);
	miID=liFilterType;

			mpOwner=cCollisionHandler::Instance()->Add(this);

    miDelay=1;

}

	cMatrix4& cCollisionObject::CacheMatrix(){return mpFollowing->mmCache;};
	vRenderObject *cCollisionObject::RenderObject(){return mpFollowing;};
	uint32 cCollisionObject::CollisionFilter(){return miID;};


	bool cCollisionObject::IsDelayed(){return miDelay;};
	void cCollisionObject::Delay(int8 liDelay){miDelay=liDelay;};
	int8 cCollisionObject::Delay(){return miDelay;};



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



#if WT_FULL_VERSION_BAMBOO


	bool cCollisionObject::ModelModel(cCollisionBase *lpOther)
	{
	    return ModelModel(Mesh(),(RenderObject()->mmCache),lpOther->Mesh(),(lpOther->RenderObject()->mmCache));
	};

	bool cCollisionObject::RayRay(cCollisionBase *lpOther)
	{
	    return RayRay(Beam(),(RenderObject()->mmCache),lpOther->Beam(),(lpOther->RenderObject()->mmCache));
	};

	bool cCollisionObject::SphereModel(cCollisionBase *lpOther)
	{
	    if(Mesh()){return SphereModel(lpOther->Sphere(),(lpOther->RenderObject()->mmCache),Mesh(),(RenderObject()->mmCache));}
	    else{return SphereModel(Sphere(),(RenderObject()->mmCache),lpOther->Mesh(),(lpOther->RenderObject()->mmCache));}
	};

	bool cCollisionObject::SphereRay(cCollisionBase *lpOther)
	{
        if(Beam()){return SphereRay(lpOther->Sphere(),(lpOther->RenderObject()->mmCache),Beam(),(RenderObject()->mmCache));}
	    else{return SphereRay(Sphere(),(RenderObject()->mmCache),lpOther->Beam(),(lpOther->RenderObject()->mmCache));}
	};

	bool cCollisionObject::RayModel(cCollisionBase *lpOther)
	{
	    if(Mesh()){return RayModel(lpOther->Beam(),(lpOther->RenderObject()->mmCache),Mesh(),(RenderObject()->mmCache));}
	    else{return RayModel(Beam(),(RenderObject()->mmCache),lpOther->Mesh(),(lpOther->RenderObject()->mmCache));}
	};


void cCollisionObject::CheckCollisionDetail()
{
 	if(cCollisionList::mpOther->Asleep() || cCollisionList::mpOther->IsDelayed()) return;

	if(!TouchCollision()) return;

	if(Type()==WT_COLLISION_MODEL)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_RADIUS) {SphereModelDetail(cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->CacheMatrix(),Mesh(),CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL)  {ModelModelDetail(Mesh(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_BEAM || cCollisionList::mpOther->Type()==WT_COLLISION_RAY) {RayModelDetail(cCollisionList::mpOther->Beam(),cCollisionList::mpOther->CacheMatrix(),Mesh(),CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) {CompoundCollisionDetail(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->RenderObject()->mmCache,mpObject,RenderObject()->mmCache); return;}
	}
	if(Type()==WT_COLLISION_BEAM || Type()==WT_COLLISION_RAY)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL) {RayModelDetail(Beam(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) {CompoundCollisionDetail(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->RenderObject()->mmCache,mpObject,RenderObject()->mmCache); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_RAY || cCollisionList::mpOther->Type()==WT_COLLISION_BEAM) {RayRayDetail(Beam(),CacheMatrix(),cCollisionList::mpOther->Beam(),cCollisionList::mpOther->CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_RADIUS) {SphereRayDetail(cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->RenderObject()->mmCache,Beam(),RenderObject()->mmCache); return;}
	}

	if(Type()==WT_COLLISION_RADIUS)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL) {SphereModelDetail(Sphere(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) {CompoundCollisionDetail(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->RenderObject()->mmCache,mpObject,RenderObject()->mmCache); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_RADIUS) {SphereSphereDetail(Sphere(),RenderObject()->mmCache,cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->RenderObject()->mmCache); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_BEAM || cCollisionList::mpOther->Type()==WT_COLLISION_RAY) {SphereRayDetail(Sphere(),RenderObject()->mmCache,cCollisionList::mpOther->Beam(),cCollisionList::mpOther->RenderObject()->mmCache); return;}
	}

	if(Type()==WT_COLLISION_COMPOUND)
	{
        CompoundCollisionDetail(Compound(),RenderObject()->mmCache,cCollisionList::mpOther->CollisionData(),cCollisionList::mpOther->RenderObject()->mmCache);
        return;
    }

}


bool cCollisionObject::CheckCollision()
{
 	if(cCollisionList::mpOther->Asleep() || cCollisionList::mpOther->IsDelayed()) return 0;

	if(!TouchCollision()) return 0;

	if((Type()==WT_COLLISION_RADIUS || Type()==WT_COLLISION_BEAM || Type()==WT_COLLISION_RAY) && (cCollisionList::mpOther->Type()==WT_COLLISION_RADIUS || cCollisionList::mpOther->Type()==WT_COLLISION_BEAM || cCollisionList::mpOther->Type()==WT_COLLISION_RAY)) return 1;
	if(Type()==WT_COLLISION_MODEL)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_RADIUS) return SphereModel(cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->CacheMatrix(),Mesh(),CacheMatrix());
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL)  return ModelModel(Mesh(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix());
		if(cCollisionList::mpOther->Type()==WT_COLLISION_BEAM || cCollisionList::mpOther->Type()==WT_COLLISION_RAY) return RayModel(cCollisionList::mpOther->Beam(),cCollisionList::mpOther->CacheMatrix(),Mesh(),CacheMatrix());
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) return CompoundCollision(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->RenderObject()->mmCache,mpObject,RenderObject()->mmCache);
	}
	if(Type()==WT_COLLISION_BEAM || Type()==WT_COLLISION_RAY)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL) return RayModel(Beam(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix());
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) return CompoundCollision(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->RenderObject()->mmCache,mpObject,RenderObject()->mmCache);
	}

	if(Type()==WT_COLLISION_RADIUS)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL) return SphereModel(Sphere(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix());
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) return CompoundCollision(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->RenderObject()->mmCache,mpObject,RenderObject()->mmCache);
	}

	if(Type()==WT_COLLISION_COMPOUND)
	{
        return CompoundCollision(Compound(),RenderObject()->mmCache,cCollisionList::mpOther->CollisionData(),cCollisionList::mpOther->RenderObject()->mmCache);
    }

	return 0;
}

bool cCollisionObject::TouchCollision()
{
	if(Beam() || cCollisionList::mpOther->Beam())
	{

		if(Beam() && cCollisionList::mpOther->Beam())
		{
		    Beam()->PrepForCollision();
		    cCollisionList::mpOther->Beam()->PrepForCollision();
		     return RayRay(Beam(),RenderObject()->mmCache,cCollisionList::mpOther->Beam(),cCollisionList::mpOther->RenderObject()->mmCache);
        }
		else
		{
            if(Beam()) Beam()->PrepForCollision();
            else cCollisionList::mpOther->Beam()->PrepForCollision();
			return SphereRay(cCollisionList::mpOther);
		}
	}
	else
	{
		return SphereSphere(Sphere(),RenderObject()->mmCache,cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->RenderObject()->mmCache);
	}
};


cCollisionObject::cCollisionObject(cBeam *lpFollow,cProcess *lpLinked,uint32 liFilterType)
{

	mpOwner=0;

	mpLinked=0;
	mpFollowing=0;

	Initialise(lpFollow,lpLinked,liFilterType);
	SetType(lpFollow);
};

cRayCollision *cCollisionObject::SetType(cRenderObject *lpObj)
{
 return SetType(lpObj,1.0f);
};


cRayCollision *cCollisionObject::SetTypeRay(cRenderObject *lpObj)
{
	return SetType(lpObj,1.0f);
};

cRayCollision *cCollisionObject::SetType(cRenderObject *lpObj,float lfRadius)
{
    mpFollowing=lpObj;
	OnProcedural();
	mpObject=new cRayCollision;
	Ray()->SetSize(lfRadius);
	return Ray();
};

cRayCollision *cCollisionObject::SetTypeRay(cRenderObject *lpObj,float lfRadius)
{
    return SetType(lpObj,lfRadius);
};

cCompoundCollision *cCollisionObject::SetTypeCompound(string lcReference)
{
	return SetType(_GET_COMPOUND_COLLISION_FILE(lcReference.c_str()));
};
cCompoundCollision *cCollisionObject::SetType(cCompoundCollisionFile *lpData)
{
	OnProcedural();
	cCompoundCollision *lpNew;
	lpNew=new cCompoundCollision;
	mpObject=lpNew;
	uint32 liCount;
	for(liCount=0;liCount<lpData->Items();++liCount)
	{
		lpNew->AddType(lpData->GetPointer(liCount));
	};
	return lpNew;

};

cCompoundCollision *cCollisionObject::SetTypeCompound(cCompoundCollisionFile *lpData)
{
	return SetType(lpData);
};


#else

bool cCollisionObject::CheckCollision()
{

	if(Asleep() || cCollisionList::mpOther->Asleep() || IsDelayed() || cCollisionList::mpOther->IsDelayed()) return 0;
	return TouchCollision();

}

bool cCollisionObject::TouchCollision()
{
		return SphereSphere(Sphere(),mpFollowing->mmCache,cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->RenderObject()->mmCache);
};

#endif

bool cCollisionObject::CheckCollision(cCollisionBase *lpOther)
{
    cCollisionList::mpOther=lpOther;
    return CheckCollision();
}

bool cCollisionObject::TouchCollision(cCollisionBase *lpOther)
{
    cCollisionList::mpOther=lpOther;
    return TouchCollision();
};

cCollisionList *cCollisionObject::CheckCollisionDetail(cCollisionBase *lpOther,cCollisionList *lpList)
{
    if(!lpList) cCollisionList::mpStaticList=new cCollisionList(lpOther);
    else cCollisionList::mpStaticList=lpList;
    cCollisionList::mpOther=lpOther;
    CheckCollisionDetail();
    return cCollisionList::mpStaticList;
}



bool cCollisionObject::SphereSphere(cCollisionBase *lpOther)
{
    return SphereSphere(Sphere(),RenderObject()->mmCache,lpOther->Sphere(),lpOther->RenderObject()->mmCache);
};

void cCollisionObject::ForceInitialisation(cMatrix4 &lmGlobal)
{
    if(mpFollowing)
    {
        mpFollowing->mmCache=lmGlobal;
        miDelay=0;
    }
};
