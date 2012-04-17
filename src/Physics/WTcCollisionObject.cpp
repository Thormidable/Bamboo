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


vRenderObject *cCollisionObject::Following(){return mpFollowing;};


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
if(miDelay) --miDelay;
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
	void cCollisionObject::Delay(uint8 liDelay){miDelay=liDelay;};
	uint8 cCollisionObject::Delay(){return miDelay;};



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

void cCollisionObject::CheckCollisionDetail()
{
 	if(cCollisionList::mpOther->Asleep() || cCollisionList::mpOther->IsDelayed()) return;
	if(!TouchCollision()) return;


	if(Type()==WT_COLLISION_MODEL)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_RADIUS) {SphereModelDetail(cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->CacheMatrix(),Mesh(),CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL)  {ModelModelDetail(Mesh(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_BEAM || cCollisionList::mpOther->Type()==WT_COLLISION_RAY) {RayModelDetail(cCollisionList::mpOther->Beam(),cCollisionList::mpOther->CacheMatrix(),Mesh(),CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) {CompoundCollisionDetail(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->mpFollowing->mmCache,mpObject,mpFollowing->mmCache); return;}
	}
	if(Type()==WT_COLLISION_BEAM || Type()==WT_COLLISION_RAY)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL) {RayModelDetail(Beam(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) {CompoundCollisionDetail(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->mpFollowing->mmCache,mpObject,mpFollowing->mmCache); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_RAY || cCollisionList::mpOther->Type()==WT_COLLISION_BEAM) {RayRayDetail(Beam(),CacheMatrix(),cCollisionList::mpOther->Beam(),cCollisionList::mpOther->CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_RADIUS) {SphereRayDetail(cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->mpFollowing->mmCache,Beam(),mpFollowing->mmCache); return;}
	}

	if(Type()==WT_COLLISION_RADIUS)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL) {SphereModelDetail(Sphere(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix()); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) {CompoundCollisionDetail(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->mpFollowing->mmCache,mpObject,mpFollowing->mmCache); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_RADIUS) {SphereSphereDetail(Sphere(),mpFollowing->mmCache,cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->mpFollowing->mmCache); return;}
		if(cCollisionList::mpOther->Type()==WT_COLLISION_BEAM || cCollisionList::mpOther->Type()==WT_COLLISION_RAY) {SphereRayDetail(Sphere(),mpFollowing->mmCache,cCollisionList::mpOther->Beam(),cCollisionList::mpOther->mpFollowing->mmCache); return;}
	}

	if(Type()==WT_COLLISION_COMPOUND)
	{
        CompoundCollisionDetail(Compound(),mpFollowing->mmCache,cCollisionList::mpOther->CollisionData(),cCollisionList::mpOther->mpFollowing->mmCache);
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
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) return CompoundCollision(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->mpFollowing->mmCache,mpObject,mpFollowing->mmCache);
	}
	if(Type()==WT_COLLISION_BEAM || Type()==WT_COLLISION_RAY)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL) return RayModel(Beam(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix());
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) return CompoundCollision(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->mpFollowing->mmCache,mpObject,mpFollowing->mmCache);
	}

	if(Type()==WT_COLLISION_RADIUS)
	{
		if(cCollisionList::mpOther->Type()==WT_COLLISION_MODEL) return SphereModel(Sphere(),CacheMatrix(),cCollisionList::mpOther->Mesh(),cCollisionList::mpOther->CacheMatrix());
		if(cCollisionList::mpOther->Type()==WT_COLLISION_COMPOUND) return CompoundCollision(cCollisionList::mpOther->Compound(),cCollisionList::mpOther->mpFollowing->mmCache,mpObject,mpFollowing->mmCache);
	}

	if(Type()==WT_COLLISION_COMPOUND)
	{
        return CompoundCollision(Compound(),mpFollowing->mmCache,cCollisionList::mpOther->CollisionData(),cCollisionList::mpOther->mpFollowing->mmCache);
    }

	return 0;
}

bool cCollisionObject::TouchCollision()
{
	if(Beam() || cCollisionList::mpOther->Beam())
	{

		if(Beam() && cCollisionList::mpOther->Beam()){ return RayRay(Beam(),mpFollowing->mmCache,cCollisionList::mpOther->Beam(),cCollisionList::mpOther->mpFollowing->mmCache); }
		else
		{

			return SphereRay(cCollisionList::mpOther);
		}
	}
	else
	{
		return SphereSphere(Sphere(),mpFollowing->mmCache,cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->mpFollowing->mmCache);
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

bool cCollisionObject::CompoundCollision(cCompoundCollision* lpCompound,cMatrix4 &lcCompoundMatrix, vCollisionData *lpOther,cMatrix4 &lcOtherMatrix)
{
 vCollisionData *lpNode=0;
 switch(lpOther->Type())
 {
     case WT_COLLISION_RADIUS :
     {
         uint32 liPos;
         for(liPos=0;liPos<lpCompound->Items();++liPos)
         {
                lpNode=lpCompound->GetObject(liPos);
                switch(lpNode->Type())
                {
                    case WT_COLLISION_RADIUS: {if(SphereSphere(lpNode->Sphere(),lcCompoundMatrix,lpOther->Sphere(),lcOtherMatrix)) return 1;} break;
                    case WT_COLLISION_RAY:
                    case WT_COLLISION_BEAM: {if(SphereRay(lpOther->Sphere(),lcOtherMatrix,lpNode->Beam(),lcCompoundMatrix)) return 1;} break;
                    case WT_COLLISION_MODEL: {if(SphereModel(lpOther->Sphere(),lcOtherMatrix,lpNode->Mesh(),lcCompoundMatrix)) return 1;} break;
                    case WT_COLLISION_COMPOUND: {if(CompoundCollision(lpNode->Compound(),lcCompoundMatrix,lpOther,lcOtherMatrix)) return 1;} break;
                };
         }
     }break;
     case WT_COLLISION_RAY :
     case WT_COLLISION_BEAM :
     {
         uint32 liPos;
         for(liPos=0;liPos<lpCompound->Items();++liPos)
         {
                lpNode=lpCompound->GetObject(liPos);
                switch(lpNode->Type())
                {
                    case WT_COLLISION_RADIUS: {if(SphereRay(lpNode->Sphere(),lcCompoundMatrix,lpOther->Beam(),lcOtherMatrix)) return 1;} break;
                    case WT_COLLISION_RAY:
                    case WT_COLLISION_BEAM: {if(RayRay(lpOther->Beam(),lcOtherMatrix,lpNode->Beam(),lcCompoundMatrix)) return 1;} break;
                    case WT_COLLISION_MODEL: {if(RayModel(lpOther->Beam(),lcOtherMatrix,lpNode->Mesh(),lcCompoundMatrix)) return 1;} break;
                    case WT_COLLISION_COMPOUND: {if(CompoundCollision(lpNode->Compound(),lcCompoundMatrix,lpOther,lcOtherMatrix)) return 1;} break;
                };
         }
     }break;
     case WT_COLLISION_MODEL :
     {
         uint32 liPos;
         for(liPos=0;liPos<lpCompound->Items();++liPos)
         {
                lpNode=lpCompound->GetObject(liPos);
                switch(lpNode->Type())
                {
                    case WT_COLLISION_RADIUS: {if(SphereModel(lpNode->Sphere(),lcCompoundMatrix,lpOther->Mesh(),lcOtherMatrix)) return 1;} break;
                    case WT_COLLISION_RAY:
                    case WT_COLLISION_BEAM: {if(RayModel(lpOther->Beam(),lcOtherMatrix,lpNode->Mesh(),lcCompoundMatrix)) return 1;} break;
                    case WT_COLLISION_MODEL: {if(ModelModel(lpOther->Mesh(),lcOtherMatrix,lpNode->Mesh(),lcCompoundMatrix)) return 1;} break;
                    case WT_COLLISION_COMPOUND: {if(CompoundCollision(lpNode->Compound(),lcCompoundMatrix,lpOther,lcOtherMatrix)) return 1;} break;
                };
         }
     }break;
     case WT_COLLISION_COMPOUND :
     {
		// lpNode=
        // if(CompoundCollision(lpNode->Compound(),lcCompoundMatrix,lpOther,lcOtherMatrix)) return 1;
     }break;
 };
 return 0;

}





void cCollisionObject::CompoundCollisionDetail(cCompoundCollision* lpCompound,cMatrix4 &lcCompoundMatrix, vCollisionData *lpOther,cMatrix4 &lcOtherMatrix)
{
 uint32 liItems=cCollisionList::mpStaticList->Items();
 vCollisionData *lpNode=0;
 switch(lpOther->Type())
 {
     case WT_COLLISION_RADIUS :
     {
         uint32 liPos;
         for(liPos=0;liPos<lpCompound->Items();++liPos)
         {
                lpNode=lpCompound->GetObject(liPos);
                switch(lpNode->Type())
                {
                    case WT_COLLISION_RADIUS: (SphereSphereDetail(lpNode->Sphere(),lcCompoundMatrix,lpOther->Sphere(),lcOtherMatrix)); break;
                    case WT_COLLISION_RAY:
                    case WT_COLLISION_BEAM: (SphereRayDetail(lpOther->Sphere(),lcOtherMatrix,lpNode->Beam(),lcCompoundMatrix)); break;
                    case WT_COLLISION_MODEL: (SphereModelDetail(lpOther->Sphere(),lcOtherMatrix,lpNode->Mesh(),lcCompoundMatrix)); break;
                    case WT_COLLISION_COMPOUND: (CompoundCollisionDetail(lpNode->Compound(),lcCompoundMatrix,lpOther,lcOtherMatrix)); break;
                };
                if( liItems<cCollisionList::mpStaticList->Items()) return;
         }
     }break;
     case WT_COLLISION_RAY :
     case WT_COLLISION_BEAM :
     {
         uint32 liPos;
         for(liPos=0;liPos<lpCompound->Items();++liPos)
         {
                lpNode=lpCompound->GetObject(liPos);
                switch(lpNode->Type())
                {
                    case WT_COLLISION_RADIUS: (SphereRayDetail(lpNode->Sphere(),lcCompoundMatrix,lpOther->Beam(),lcOtherMatrix));break;
                    case WT_COLLISION_RAY:
                    case WT_COLLISION_BEAM: (RayRayDetail(lpOther->Beam(),lcOtherMatrix,lpNode->Beam(),lcCompoundMatrix));break;
                    case WT_COLLISION_MODEL: (RayModelDetail(lpOther->Beam(),lcOtherMatrix,lpNode->Mesh(),lcCompoundMatrix)); break;
                    case WT_COLLISION_COMPOUND: (CompoundCollisionDetail(lpNode->Compound(),lcCompoundMatrix,lpOther,lcOtherMatrix)); break;
                };
                if( liItems<cCollisionList::mpStaticList->Items()) return;
         }
     }break;
     case WT_COLLISION_MODEL :
     {
         uint32 liPos;
         for(liPos=0;liPos<lpCompound->Items();++liPos)
         {
                lpNode=lpCompound->GetObject(liPos);
                switch(lpNode->Type())
                {
                    case WT_COLLISION_RADIUS: (SphereModelDetail(lpNode->Sphere(),lcCompoundMatrix,lpOther->Mesh(),lcOtherMatrix)); break;
                    case WT_COLLISION_RAY:
                    case WT_COLLISION_BEAM: (RayModelDetail(lpOther->Beam(),lcOtherMatrix,lpNode->Mesh(),lcCompoundMatrix)); break;
                    case WT_COLLISION_MODEL: (ModelModelDetail(lpOther->Mesh(),lcOtherMatrix,lpNode->Mesh(),lcCompoundMatrix)); break;
                    case WT_COLLISION_COMPOUND: (CompoundCollisionDetail(lpNode->Compound(),lcCompoundMatrix,lpOther,lcOtherMatrix)); break;
                };
                if( liItems<cCollisionList::mpStaticList->Items()) return;
         }
     }break;
     case WT_COLLISION_COMPOUND :
     {
        CompoundCollisionDetail(lpNode->Compound(),lcCompoundMatrix,lpOther,lcOtherMatrix);
     }break;
 };

}

#else

bool cCollisionObject::CheckCollision()
{

	if(Asleep() || cCollisionList::mpOther->Asleep() || IsDelayed() || cCollisionList::mpOther->IsDelayed()) return 0;
	return TouchCollision();

}

bool cCollisionObject::TouchCollision()
{
		return SphereSphere(Sphere(),mpFollowing->mmCache,cCollisionList::mpOther->Sphere(),cCollisionList::mpOther->mpFollowing->mmCache);
};

#endif

bool cCollisionObject::CheckCollision(cCollisionObject *lpOther)
{
    cCollisionList::mpOther=lpOther;
    return CheckCollision();
}

bool cCollisionObject::TouchCollision(cCollisionObject *lpOther)
{
    cCollisionList::mpOther=lpOther;
    return TouchCollision();
};

cCollisionList *cCollisionObject::CheckCollisionDetail(cCollisionObject *lpOther,cCollisionList *lpList)
{
    if(!lpList) cCollisionList::mpStaticList=new cCollisionList(lpOther);
    else cCollisionList::mpStaticList=lpList;
    cCollisionList::mpOther=lpOther;
    CheckCollisionDetail();
    return cCollisionList::mpStaticList;
}
