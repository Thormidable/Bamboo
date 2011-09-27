#include "../WTDivWin.h"

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

uint32 cCollisionHandlerType::FindSlot(cCollisionObject *lpObj)
{
 return lpObj->CollisionFilter();
}

cCollisionList *cCollisionHandlerBSP::GenerateCollisionList(cCollisionObject *lpCheck,uint32 lpCol)
{
	
	printf("cCollisionHandler::GenerateCollisionList Start\n");
	cCollisionList *lpList=new cCollisionList;
	ResetCursors();
	
	uint32 liSlot=FindSlot(lpCheck);
	
	while(NextListItem(liSlot)) {if(mpColCur->mpData->Collision(lpCheck,lpCol))lpList->AddCollision(mpColCur->mpData);}
	
	return lpList;
}

cCollisionList *cCollisionHandlerType::GenerateCollisionList(cCollisionObject *lpObj,uint32 lpType)
{
cCollisionList *lpList=new cCollisionList;
ResetCursors();
if(lpType)
{
	while(NextListItem(lpType))
		{
		
			if(mpColCur->mpData!=lpObj)
			{	
				if(mpColCur->mpData->Collision(lpObj)){lpList->AddCollision(mpColCur->mpData);}
			}
		}
}
else
	while(NextListItem())
	{
		printf("Next Item\n");
	if(mpColCur->mpData!=lpObj)
	{printf("Is not original object\n");
		if(mpColCur->mpData->Collision(lpObj)) lpList->AddCollision(mpColCur->mpData);
		
	}
  }
  return lpList;
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

void cCollisionHandlerType::RemoveFromList(cLinkedNode<cCollisionObject> *lpOld)
{  
 if(lpOld->mpData)
 mpList[FindSlot(lpOld->mpData)].Remove(lpOld);

}

cLinkedNode<cCollisionObject> *cCollisionHandlerType::Add(cCollisionObject *lpObject)
{

return mpList[FindSlot(lpObject)].Insert(lpObject);
}




cCollisionHandlerType::cCollisionHandlerType()
{
mpList=new cLinkedList<cCollisionObject>[WT_COLLISION_HANDLER_ARRAY_SIZE];
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

void cCollisionHandlerType::Remove(cLinkedNode<cCollisionObject> *lpOld)
{
 lpOld->mpData->Signal(_S_KILL);
}




uint32 cCollisionHandlerBSP::mpAxisOrder[3]={0,2,1};

uint32 cCollisionHandlerBSP::FindSlot(float *lpPos)
{

uint32 liCount;
uint32 liCount2;
float lfPos;
uint32 liPosition=0;
uint32 liRound;

for(liCount=0;liCount<WT_COLLISION_HANDLER_DIMENSIONS;++liCount)
{
 lfPos=lpPos[mpAxisOrder[liCount]]-mfCentre[mpAxisOrder[liCount]]+(WT_COLLISION_HANDLER_SIZE*WT_COLLISION_SPACE_SIZE/2);
 lfPos=lfPos*WT_COLLISION_SPACE_SIZE_INV;

if(lfPos<0.0f) liRound=0;
 else 
   if(lfPos>WT_COLLISION_HANDLER_SIZE) liRound=WT_COLLISION_HANDLER_SIZE;
    else liRound=lfPos;

  if(!liCount) liCount2=1;
  else  liCount2*=WT_COLLISION_HANDLER_SIZE;

  liPosition+=liRound*liCount2;
}

return liPosition;

}

uint32 cCollisionHandlerBSP::FindSlot(cCollisionObject *lpObj)
{
	return FindSlot(lpObj->RenderObject()->GetGlobalPos());
}



cLinkedList<cCollisionObject> *cCollisionHandlerBSP::FindSlot(uint32 *lpPos)
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



cCollisionObject *cCollisionHandler::NextCollision(cCollisionObject *lpObj,uint32 lpType)
{
	(void) lpObj;
	(void) lpType;
uint32 SERIOUSLY_FILL_THIS_OUT;
return 0;
}
