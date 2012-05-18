#include "../WTBamboo.h"
/*
void cCollisionHandler::MouseCollisionCheck(c3DVf lpRayVector,c3DVf lpStart,float lfRadius,cMatrix4 &lmOtherMatrix)
{
 if(cCollisionList::mpOther->Asleep() || cCollisionList::mpOther->IsDelayed()) return;
double lfEq[2];

    c3DVf lpRayTemp=lpStart-lmOtherMatrix.Position();

	lpStart[0]=(lpRayTemp[0]*lmOtherMatrix[0]+lpRayTemp[1]*lmOtherMatrix[1]+lpRayTemp[2]*lmOtherMatrix[2]);
	lpStart[1]=(lpRayTemp[0]*lmOtherMatrix[4]+lpRayTemp[1]*lmOtherMatrix[5]+lpRayTemp[2]*lmOtherMatrix[6]);
 	lpStart[2]=(lpRayTemp[0]*lmOtherMatrix[8]+lpRayTemp[1]*lmOtherMatrix[9]+lpRayTemp[2]*lmOtherMatrix[10]);

        c3DVf lpRV;
        lpRV[0]=(lpRayVector[0]*lmOtherMatrix[0]+lpRayVector[1]*lmOtherMatrix[1]+lpRayVector[2]*lmOtherMatrix[2]);
        lpRV[1]=(lpRayVector[0]*lmOtherMatrix[4]+lpRayVector[1]*lmOtherMatrix[5]+lpRayVector[2]*lmOtherMatrix[6]);
        lpRV[2]=(lpRayVector[0]*lmOtherMatrix[8]+lpRayVector[1]*lmOtherMatrix[9]+lpRayVector[2]*lmOtherMatrix[10]);


//Find the number of Ray vectors to reach the sphere.
lfEq[0]=(lpStart[0]*lpRV[0]+
		lpStart[1]*lpRV[1]+
		lpStart[2]*lpRV[2]);

		lpRV[0]=lpRV[0]*lfEq[0];
		lpRV[1]=lpRV[1]*lfEq[0];
		lpRV[2]=lpRV[2]*lfEq[0];

		lfEq[1]=0.0f;
		lfEq[1]+=(lpStart[0]-lpRV[0])*(lpStart[0]-lpRV[0]);
		lfEq[1]+=(lpStart[1]-lpRV[1])*(lpStart[1]-lpRV[1]);
		lfEq[1]+=(lpStart[2]-lpRV[2])*(lpStart[2]-lpRV[2]);

    lfRadius+=cCollisionList::mpOther->Sphere()->CollisionSize();

	if(lfEq[1]<lfRadius)
	{
        lfEq[1]=sqrt(lfEq[1]);
        cCollisionListObject *lpTemp=new cCollisionListObject;
        lpTemp->mpObj=cCollisionList::mpOther;
        lpTemp->mvCentre=lmOtherMatrix.Position();
        lpTemp->mfBeamLength=lfEq[0];
        lpTemp->mfDistance=c3DVf(lpStart+lpRV-lpTemp->mvCentre).Magnitude();
        cCollisionList::mpStaticList->AddCollision(lpTemp);
	}

}
*/
cCollisionHandler *cCollisionHandler::spInstance=0;

cCollisionHandler *cCollisionHandler::Instance()
{
 if(!spInstance)
 {
	 if (WT_COLLISION_HANDLER_TYPE==WT_COLLISION_HANDLER_TYPE_TYPE)	 spInstance=new cCollisionHandlerType();
	 if (WT_COLLISION_HANDLER_TYPE==WT_COLLISION_HANDLER_TYPE_BSP) spInstance=new cCollisionHandlerBSP();
 }
 return spInstance;
}

uint32 cCollisionHandlerType::FindSlot(cCollisionBase *lpObj)
{
 return lpObj->CollisionFilter();
}

cCollisionList *cCollisionHandlerBSP::GenerateDetailedCollisionList(cCollisionBase *lpCheck,uint32 lpCol,cCollisionList *lpList)
{
    if(!lpList) cCollisionList::mpStaticList=new cCollisionList(lpCheck);
	else cCollisionList::mpStaticList=lpList;
	if(lpCheck->Awake() && !lpCheck->IsDelayed())
	{
        ResetCursors();

        uint32 liSlot=FindSlot(lpCheck);

        while(NextListItem(liSlot))
        {
            if(mpColCur->Data()->CollisionFilter()==lpCol || !lpCol)
            {
                cCollisionList::mpOther=mpColCur->Data();
                if(mpColCur->Data()!=lpCheck) lpCheck->CheckCollisionDetail();
            }
        }
	}

	return cCollisionList::mpStaticList;
}

cCollisionList *cCollisionHandlerBSP::GenerateCollisionList(cCollisionBase *lpCheck,uint32 lpCol,cCollisionList *lpList)
{
	if(!lpList) cCollisionList::mpStaticList=new cCollisionList(lpCheck);
	else cCollisionList::mpStaticList=lpList;

	if(lpCheck->Awake() && !lpCheck->IsDelayed())
	{
        ResetCursors();

        uint32 liSlot=FindSlot(lpCheck);

        while(NextListItem(liSlot))
        {
            if(mpColCur->Data()->CollisionFilter()==lpCol || !lpCol)
            {
                cCollisionList::mpOther=mpColCur->Data();
                if(lpCheck->CheckCollision()) cCollisionList::mpStaticList->AddCollision();
            }
        }
	}
	return cCollisionList::mpStaticList;
}

/*
cCollisionList *cCollisionHandlerBSP::GenerateMouseSelection(c3DVf MouseVector,c3DVf MouseStart,float lfRadius,uint32 lpCol,cCollisionList *lpList)
{
if(!lpList) cCollisionList::mpStaticList=new cCollisionList(0);
else cCollisionList::mpStaticList=lpList;

        ResetCursors();

        uint32 liTopPos=0;
        if(WT_COLLISION_HANDLER_DIMENSIONS==WT_COLLISION_HANDLER_DIMENSIONS_1D) liTopPos=WT_COLLISION_HANDLER_SIZE;
        if(WT_COLLISION_HANDLER_DIMENSIONS==WT_COLLISION_HANDLER_DIMENSIONS_2D) liTopPos=WT_COLLISION_HANDLER_SIZE+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        if(WT_COLLISION_HANDLER_DIMENSIONS==WT_COLLISION_HANDLER_DIMENSIONS_3D) liTopPos=WT_COLLISION_HANDLER_SIZE+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        for(uint32 liSlot=0;liSlot<liTopPos;++liSlot)
        {
            ResetCursors();
            while(NextListItem(liSlot))
            {
                if(mpColCur->Data()->CollisionFilter()==lpCol || !lpCol)
                {
                    cCollisionList::mpOther=mpColCur->Data();
                    MouseCollisionCheck(MouseVector,MouseStart,lfRadius,cCollisionList::mpOther->CacheMatrix());
                }
            }
        }
	return cCollisionList::mpStaticList;
};*/

/*
cCollisionList *cCollisionHandlerBSP::GenerateMouseSelection(cMouseCollisionObject *lpMouse,uint32 lpCol,cCollisionList *lpList)
{
if(!lpList) cCollisionList::mpStaticList=new cCollisionList(0);
else cCollisionList::mpStaticList=lpList;

        ResetCursors();

        uint32 liTopPos=0;
        if(WT_COLLISION_HANDLER_DIMENSIONS==WT_COLLISION_HANDLER_DIMENSIONS_1D) liTopPos=WT_COLLISION_HANDLER_SIZE;
        if(WT_COLLISION_HANDLER_DIMENSIONS==WT_COLLISION_HANDLER_DIMENSIONS_2D) liTopPos=WT_COLLISION_HANDLER_SIZE+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        if(WT_COLLISION_HANDLER_DIMENSIONS==WT_COLLISION_HANDLER_DIMENSIONS_3D) liTopPos=WT_COLLISION_HANDLER_SIZE+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        for(uint32 liSlot=0;liSlot<liTopPos;++liSlot)
        {
            ResetCursors();
            while(NextListItem(liSlot))
            {
                if(mpColCur->Data()->CollisionFilter()==lpCol || !lpCol)
                {
                    cCollisionList::mpOther=mpColCur->Data();
                    lpMouse->CheckCollision();
                }
            }
        }
	return cCollisionList::mpStaticList;
};
*/
cCollisionList *cCollisionHandlerType::GenerateCollisionList(cCollisionBase *lpObj,uint32 lpType,cCollisionList *lpList)
{
	if(!lpList) cCollisionList::mpStaticList=new cCollisionList(lpObj);
	else cCollisionList::mpStaticList=lpList;

  if(lpObj->Awake() && !lpObj->IsDelayed())
  {
        ResetCursors();
        if(lpType<WT_COLLISION_HANDLER_ARRAY_SIZE)
        {
            if(lpType)
            {
            while(NextListItem(lpType))
                {

                    if(mpColCur->Data()!=lpObj)
                    {
                        cCollisionList::mpOther=mpColCur->Data();
                        if(lpObj->CheckCollision()) cCollisionList::mpStaticList->AddCollision();
                    }
                }
            }
            else
            {
            while(NextListItem())
            {

                if(mpColCur->Data()!=lpObj)
                {
                    cCollisionList::mpOther=mpColCur->Data();
                    if(lpObj->CheckCollision()) cCollisionList::mpStaticList->AddCollision();
                }
            }
            }
        }
  }
  return cCollisionList::mpStaticList;
}
/*
cCollisionList *cCollisionHandlerType::GenerateMouseSelection(cMouseCollisionObject *lpMouse,uint32 lpType,cCollisionList *lpList)
{
	if(!lpList) cCollisionList::mpStaticList=new cCollisionList(0);
	else cCollisionList::mpStaticList=lpList;

    ResetCursors();
        if(lpType<WT_COLLISION_HANDLER_ARRAY_SIZE && lpType)
        {
            while(NextListItem(lpType))
                {
                        cCollisionList::mpOther=mpColCur->Data();
                        lpMouse->CheckCollision();
                }
        }
        else
        {
            while(NextListItem())
            {
                    cCollisionList::mpOther=mpColCur->Data();
                    MouseCollisionCheck(MouseVector,MouseStart,lfRadius,cCollisionList::mpOther->CacheMatrix());
            }
        }
  return cCollisionList::mpStaticList;
};
*/

cCollisionList *cCollisionHandlerType::GenerateDetailedCollisionList(cCollisionBase *lpObj,uint32 lpType,cCollisionList *lpList)
{
	if(!lpList) cCollisionList::mpStaticList=new cCollisionList(lpObj);
	else cCollisionList::mpStaticList=lpList;
    if(lpObj->Awake() && !lpObj->IsDelayed())
	{
        ResetCursors();
        if(lpType<WT_COLLISION_HANDLER_ARRAY_SIZE && lpType)
        {
            while(NextListItem(lpType))
                {
                    if(mpColCur->Data()!=lpObj)
                    {
                        cCollisionList::mpOther=mpColCur->Data();
                        lpObj->CheckCollisionDetail();
                    }
                }
        }
        else
        {
            while(NextListItem())
            {
                if(mpColCur->Data()!=lpObj)
                {
                    cCollisionList::mpOther=mpColCur->Data();
                    lpObj->CheckCollisionDetail();
                }
            }
        }
	}
  return cCollisionList::mpStaticList;
}

cCollisionHandler::~cCollisionHandler()
{


}

cCollisionHandlerType::~cCollisionHandlerType()
{
	for(miCurPos=0;miCurPos<WT_COLLISION_HANDLER_ARRAY_SIZE;++miCurPos)
	{
		mpList[miCurPos].ClearAll();
		mpList[miCurPos].Initialise();
	}
	delete []mpList;mpList=0;
}

cCollisionHandlerBSP::~cCollisionHandlerBSP()
{
	for(miCurPos=0;miCurPos<WT_COLLISION_HANDLER_ARRAY_SIZE;++miCurPos)
	{
		mpList[miCurPos].ClearAll();
		mpList[miCurPos].Initialise();
	}
	delete []mpList;mpList=0;
}



bool cCollisionHandlerType::NextListItem()
{

 if(NextListItem(miCurPos)) {return 1;}

for(++miCurPos;miCurPos<WT_COLLISION_HANDLER_ARRAY_SIZE && !NextListItem(miCurPos);++miCurPos)
 {
  mpColCur=mpList[miCurPos].Start();
  if(mpColCur) return 1;
 }
 if(mpColCur) return 1;
 return 0;
}

bool cCollisionHandlerType::NextListItem(uint32 lpType)
{
 miCurPos=lpType;
 if(!mpColCur) {mpColCur=mpList[miCurPos].Start();}
 else {mpColCur=mpColCur->Next();}
 if(mpColCur) return true;
 else return false;

}

void cCollisionHandlerType::RemoveFromList(cLinkedNode<cCollisionBase> *lpOld)
{
 if(lpOld->Data())
 mpList[FindSlot(lpOld->Data())].Remove(lpOld);

}

cLinkedNode<cCollisionBase> *cCollisionHandlerType::Add(cCollisionBase *lpObject)
{

return mpList[FindSlot(lpObject)].Insert(lpObject);
}




cCollisionHandlerType::cCollisionHandlerType()
{
mpList=new cLinkedList<cCollisionBase>[WT_COLLISION_HANDLER_ARRAY_SIZE];
ResetCursors();
if(!spInstance) spInstance=this;

}


cCollisionHandlerBSP::cCollisionHandlerBSP()
{
	mfCentre[1]=mfCentre[2]=mfCentre[0]=0.0f;

}

void cCollisionHandlerType::ResetCursors()
{
miCurPos=0;
mpColCur=0;
}

void cCollisionHandlerType::Remove(cLinkedNode<cCollisionBase> *lpOld)
{
 lpOld->Data()->Signal(_S_KILL);
}




uint32 cCollisionHandlerBSP::mpAxisOrder[3]={0,2,1};

uint32 cCollisionHandlerBSP::FindSlot(float *lpPos)
{

uint32 liCount;
uint32 liCount2=0;
float lfPos;
uint32 liPosition=0;
uint32 liRound;

for(liCount=0;liCount<WT_COLLISION_HANDLER_DIMENSIONS;++liCount)
{
 lfPos=lpPos[mpAxisOrder[liCount]]-mfCentre[mpAxisOrder[liCount]]+(WT_COLLISION_HANDLER_SIZE*WT_COLLISION_SPACE_SIZE/2);
 lfPos=lfPos*WT_COLLISION_SPACE_SIZE_INV;

if(lfPos<0.0f){liRound=0;}
 else
 {

   if(lfPos>WT_COLLISION_HANDLER_SIZE) {liRound=WT_COLLISION_HANDLER_SIZE;}
    else {liRound=lfPos;}
 }

  if(!liCount) liCount2=1;
  else  liCount2*=WT_COLLISION_HANDLER_SIZE;

  liPosition+=liRound*liCount2;
}

return liPosition;

}

uint32 cCollisionHandlerBSP::FindSlot(cCollisionBase *lpObj)
{
	return FindSlot(lpObj->RenderObject()->GetCachedGlobalMatrix());
}



cLinkedList<cCollisionBase> *cCollisionHandlerBSP::FindSlot(uint32 *lpPos)
{
 uint32 liTemp=0;
 uint32 liState=1;
uint32 liCount;
 for(liCount=0;liCount<WT_COLLISION_HANDLER_DIMENSIONS;++liCount)
 {
  liTemp+=liState*lpPos[mpAxisOrder[liCount]];
  liState*=WT_COLLISION_HANDLER_SIZE;
 }
 return &mpList[liTemp];

}

