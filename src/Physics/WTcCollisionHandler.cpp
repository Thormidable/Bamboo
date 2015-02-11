
#include "../WTBamboo.h"

cCollisionHandler *cCollisionHandler::spInstance=0;

uint8 cCollisionHandlerBSP::msCoords[3]={0,0,0};
uint8 cCollisionHandlerBSP::mpAxisOrder[3]={0,1,2};

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
int16 *cCollisionHandlerBSP::mpSlotArray=0;

cCollisionList *cCollisionHandlerBSP::GeneratePossibleCollisionList(cCollisionBase *lpCheck,uint32 lpCol,cCollisionList *lpList)
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
                if(mpColCur->Data()!=lpCheck) cCollisionList::mpStaticList->AddCollision(mpColCur->Data());
            }
        }
	}

	return cCollisionList::mpStaticList;
};

cCollisionList *cCollisionHandlerBSP::GenerateDetailedCollisionList(cCollisionBase *lpCheck,uint32 lpCol,cCollisionList *lpList)
{
       if(!lpList) cCollisionList::mpStaticList=new cCollisionList(lpCheck);
	else cCollisionList::mpStaticList=lpList;

	if(lpCheck->Awake() && !lpCheck->IsDelayed())
	{
	    ResetSlotCursor(lpCheck);
	    {
            while(miCurCurrentSlot)
            {
                ResetCursors();
                uint32 liSlot=NextSlot();

                while(NextListItem(liSlot))
                {
                    if(mpColCur->Data()->CollisionFilter()==lpCol || !lpCol)
                    {
                        cCollisionList::mpOther=mpColCur->Data();
                        if(mpColCur->Data()!=lpCheck) lpCheck->CheckCollisionDetail();
                    }
                }
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
	    ResetSlotCursor(lpCheck);
	    {
            while(miCurCurrentSlot)
            {
                ResetCursors();
                uint32 liSlot=NextSlot();

                while(NextListItem(liSlot))
                {
                    if(mpColCur->Data()->CollisionFilter()==lpCol || !lpCol)
                    {
                        cCollisionList::mpOther=mpColCur->Data();
                        if(lpCheck->CheckCollision()) cCollisionList::mpStaticList->AddCollision();
                    }
                }
            }
	    }
	}
	return cCollisionList::mpStaticList;
}

cCollisionList *cCollisionHandlerType::GeneratePossibleCollisionList(cCollisionBase *lpObj,uint32 lpType,cCollisionList *lpList)
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
                        cCollisionList::mpStaticList->AddCollision(mpColCur->Data());
                    }
                }
            }
            else
            {
            while(NextListItem())
            {
                if(mpColCur->Data()!=lpObj)
                {
                 cCollisionList::mpStaticList->AddCollision(mpColCur->Data());
                }
            }
            }
        }
  }
  return cCollisionList::mpStaticList;
};

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

	if(mpSlotArray) delete []mpSlotArray;
	mpSlotArray=0;
	if(mpCurSlotArray) delete []mpCurSlotArray;
	mpCurSlotArray=0;
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
 if(miCurPos>=WT_COLLISION_HANDLER_ARRAY_SIZE)
 {
   printf("ERROR HANDLER : ERROR HANDLER : ERROR HANDLER : ERROR HANDLER : %u\n",miCurPos);
 }
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
//printf("Slot : %u, Max : %u\n",FindSlot(lpObject),WT_COLLISION_HANDLER_ARRAY_SIZE);
return mpList[FindSlot(lpObject)].Insert(lpObject);
}




cCollisionHandlerType::cCollisionHandlerType()
{
if(!spInstance) spInstance=this;
mpList=new cLinkedList<cCollisionBase>[WT_COLLISION_HANDLER_ARRAY_SIZE];
ResetCursors();

}


cCollisionHandlerBSP::cCollisionHandlerBSP()
{
	mfCentre[1]=mfCentre[2]=mfCentre[0]=0.0f;
	mfOffSet[1]=mfOffSet[2]=mfOffSet[0]=WT_COLLISION_HANDLER_SIZE*WT_COLLISION_SPACE_SIZE*0.5f;
    if(!mpSlotArray)
    {
        GenerateSlotArray();
    }

    mpCurSlotArray=0;
    if(WT_COLLISION_HANDLER_DIMENSIONS==WT_COLLISION_HANDLER_DIMENSIONS_1D) mpCurSlotArray=new uint32[3];
    if(WT_COLLISION_HANDLER_DIMENSIONS==WT_COLLISION_HANDLER_DIMENSIONS_2D) mpCurSlotArray=new uint32[9];
    if(WT_COLLISION_HANDLER_DIMENSIONS==WT_COLLISION_HANDLER_DIMENSIONS_3D) mpCurSlotArray=new uint32[27];

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

uint32 cCollisionHandlerBSP::FindSlot(float *lpPos)
{

uint32 liCount;
uint32 liCount2=1;
float lfPos;
uint32 liPosition=0;
uint32 liRound;

for(liCount=0;liCount<WT_COLLISION_HANDLER_DIMENSIONS;++liCount)
{
 //lfPos=(lpPos[mpAxisOrder[liCount]]-mfCentre[mpAxisOrder[liCount]]+mfOffSet[mpAxisOrder[liCount]]);
 lfPos=(lpPos[mpAxisOrder[liCount]]-mfCentre[mpAxisOrder[liCount]]+mfOffSet[mpAxisOrder[liCount]])*WT_COLLISION_SPACE_SIZE_INV;

if(lfPos<0.0f){liRound=0;}
 else
 {

   if(lfPos>(WT_COLLISION_HANDLER_SIZE-1)) {liRound=WT_COLLISION_HANDLER_SIZE-1;}
    else {liRound=lfPos;}
 }

    liPosition+=liRound*liCount2;
    liCount2*=WT_COLLISION_HANDLER_SIZE;

}

return liPosition;

}


void cCollisionHandlerBSP::FindSlotCoord(float *lpPos)
{


float lfPos;
uint32 liRound;
mbEdgecase=false;
for(uint32 liCount=0;liCount<WT_COLLISION_HANDLER_DIMENSIONS;++liCount)
{

 //lfPos=(lpPos[mpAxisOrder[liCount]]-mfCentre[mpAxisOrder[liCount]]+mfOffSet[mpAxisOrder[liCount]])*(WT_COLLISION_HANDLER_SIZE/2);
  lfPos=(lpPos[mpAxisOrder[liCount]]-mfCentre[mpAxisOrder[liCount]]+mfOffSet[mpAxisOrder[liCount]])*WT_COLLISION_SPACE_SIZE_INV;
if(lfPos<1.0f){liRound=0; mbEdgecase=true;}
else
{
  liRound=lfPos;
  if(liRound>=WT_COLLISION_HANDLER_SIZE-1){liRound=WT_COLLISION_HANDLER_SIZE-1; mbEdgecase=true;}
}

msCoords[liCount]=liRound;

}

}

uint32 cCollisionHandlerBSP::FindSlot(cCollisionBase *lpObj)
{
	return FindSlot(lpObj->RenderObject()->mmCache.Position());
}



cLinkedList<cCollisionBase> *cCollisionHandlerBSP::FindSlot(uint32 *lpPos)
{
 uint32 liTemp=0;
 uint32 liState=1;
uint32 liCount;
 for(liCount=0;liCount<WT_COLLISION_HANDLER_DIMENSIONS;++liCount)
 {
  if(lpPos[mpAxisOrder[liCount]]>=WT_COLLISION_HANDLER_SIZE) liTemp+=liState*(WT_COLLISION_HANDLER_SIZE-1);
  else  liTemp+=liState*lpPos[mpAxisOrder[liCount]];
  liState*=WT_COLLISION_HANDLER_SIZE;
 }
 return &mpList[liTemp];

}


uint8 *cCollisionHandlerBSP::SlotIndexToCoord(uint32 liSlot)
{
    //printf("SlotIndexCoord\n");
    //printf("liSlot : %u\n",liSlot);
msCoords[cCollisionHandlerBSP::mpAxisOrder[0]]=liSlot%WT_COLLISION_HANDLER_SIZE;
liSlot-=msCoords[cCollisionHandlerBSP::mpAxisOrder[0]];
//printf("liSlot : %u\n",liSlot);
msCoords[cCollisionHandlerBSP::mpAxisOrder[1]]=liSlot%(WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE);
msCoords[cCollisionHandlerBSP::mpAxisOrder[1]]/=WT_COLLISION_HANDLER_SIZE;
liSlot-=msCoords[cCollisionHandlerBSP::mpAxisOrder[1]];

//printf("liSlot : %u\n",liSlot);
msCoords[cCollisionHandlerBSP::mpAxisOrder[2]]=liSlot/(WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE);
return msCoords;
};

void cCollisionHandlerBSP::ResetSlotCursor(cCollisionBase *lpPos)
{
    ResetSlotCursor(lpPos->RenderObject()->mmCache.Position());
}

void cCollisionHandlerBSP::ResetSlotCursor(cMatrix4 *lpPos)
{
    ResetSlotCursor(lpPos->Position());
}

void cCollisionHandlerBSP::ResetSlotCursor(c3DVf &lfPos)
{
    ResetSlotCursor(lfPos.v);
}

void cCollisionHandlerBSP::ResetSlotCursor(float *lpPos)
{
    //lpPos=&lpPos[12];
    FindSlotCoord(lpPos);
    if(mbEdgecase)
    {
        switch(WT_COLLISION_HANDLER_DIMENSIONS)
        {

          case WT_COLLISION_HANDLER_DIMENSIONS_1D:
          {
                uint8 liXS;
                uint8 liX2;
                miCurCurrentSlot=0;
                if(!msCoords[0]){liXS=0;liX2=2;}
                else
                {
                    liXS=msCoords[0]-1;
                    if(msCoords[0]>WT_COLLISION_HANDLER_SIZE-2) liX2=WT_COLLISION_HANDLER_SIZE;
                    else liX2=msCoords[0]+2;
                }
              for(uint8 liX=liXS;liX<liX2;++liX)
              {
                mpCurSlotArray[miCurCurrentSlot++]=liX;
                ++liX;
              }
          };break;
          case WT_COLLISION_HANDLER_DIMENSIONS_2D:
          {
                uint8 liXS,liYS;
                uint8 liX2,liY2;
                miCurCurrentSlot=0;

                if(!msCoords[0]){liXS=0;liX2=2;}
                else
                {
                    liXS=msCoords[0]-1;
                    if(msCoords[0]>WT_COLLISION_HANDLER_SIZE-2) liX2=WT_COLLISION_HANDLER_SIZE;
                    else liX2=msCoords[0]+2;
                }
                if(!msCoords[1]){liYS=0; liY2=2;}
                else
                {
                    liYS=msCoords[1]-1;
                    if(msCoords[1]>WT_COLLISION_HANDLER_SIZE-2) liY2=WT_COLLISION_HANDLER_SIZE;
                    else liY2=msCoords[1]+2;
                }

              for(uint8 liX=liXS;liX<liX2;++liX)
              {
                  for(uint8 liY=liYS;liY<liY2;++liY)
                  {
                        mpCurSlotArray[miCurCurrentSlot++]=liX+liY*WT_COLLISION_HANDLER_SIZE;
                        ++liY;
                  }
                ++liX;
              }
          };break;
          case WT_COLLISION_HANDLER_DIMENSIONS_3D:
          {
                uint8 liXS,liYS,liZS;
                uint8 liX2,liY2,liZ2;
                miCurCurrentSlot=0;

                if(!msCoords[0]){liXS=0;liX2=2;}
                else
                {
                    liXS=msCoords[0]-1;
                    if(msCoords[0]>WT_COLLISION_HANDLER_SIZE-2) liX2=WT_COLLISION_HANDLER_SIZE;
                    else liX2=msCoords[0]+2;
                }
                if(!msCoords[1]){liYS=0;liY2=2;}
                else
                {
                    liYS=msCoords[1]-1;
                    if(msCoords[1]>WT_COLLISION_HANDLER_SIZE-2) liY2=WT_COLLISION_HANDLER_SIZE;
                    else liY2=msCoords[1]+2;
                }
                if(!msCoords[2]){liZS=0;liZ2=2;}
                else
                {
                    liZS=msCoords[2]-1;
                    if(msCoords[2]>WT_COLLISION_HANDLER_SIZE-2) liZ2=WT_COLLISION_HANDLER_SIZE;
                    else liZ2=msCoords[2]+2;
                }

              for(uint8 liX=liXS;liX<liX2;++liX)
              {
                  for(uint8 liY=liYS;liY<liY2;++liY)
                  {
                      for(uint8 liZ=liZS;liZ<liZ2;++liZ)
                      {
                        mpCurSlotArray[miCurCurrentSlot++]=liX+liY*WT_COLLISION_HANDLER_SIZE+liZ*WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
                            if(mpCurSlotArray[miCurCurrentSlot-1]>WT_COLLISION_HANDLER_ARRAY_SIZE)
                                {
                                    printf("ERROR : ERROR EdgeCase : %u\n",miCurCurrentSlot-1);
                                }
                      }
                  }
              }
          };break;
        };
    }
    else
    {
        miCurCentreSlot=msCoords[0]+msCoords[1]*WT_COLLISION_HANDLER_SIZE+msCoords[2]*WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        switch(WT_COLLISION_HANDLER_DIMENSIONS)
        {
          case WT_COLLISION_HANDLER_DIMENSIONS_1D:
          {
              miCurCurrentSlot=3;
              for(uint8 liCount=0;liCount<3;++liCount)
              {
                  mpCurSlotArray[liCount]=mpSlotArray[liCount]+miCurCentreSlot;
              }
          };break;
          case WT_COLLISION_HANDLER_DIMENSIONS_2D:
          {
              miCurCurrentSlot=9;
              for(uint8 liCount=0;liCount<9;++liCount)
              {
                  mpCurSlotArray[liCount]=mpSlotArray[liCount]+miCurCentreSlot;
              }

          };break;
          case WT_COLLISION_HANDLER_DIMENSIONS_3D:
          {
              miCurCurrentSlot=27;
              for(uint8 liCount=0;liCount<27;++liCount)
              {
                  mpCurSlotArray[liCount]=mpSlotArray[liCount]+miCurCentreSlot;
                  if(mpCurSlotArray[liCount]>WT_COLLISION_HANDLER_ARRAY_SIZE)
                    {
                        printf("ERROR : ERROR MiddleCase : %u\n",miCurCentreSlot-1);
			printf("mpCurSlotArray[%u] : %u\n",liCount,mpCurSlotArray[liCount]);
                    }
              }
          };break;
        };
    }
};

uint32 cCollisionHandlerBSP::NextSlot()
{
    if(mpCurSlotArray[miCurCurrentSlot-1]>WT_COLLISION_HANDLER_ARRAY_SIZE)
    {
        printf("ERROR : ERROR : %u\n",miCurCurrentSlot-1);
    }
 return mpCurSlotArray[--miCurCurrentSlot];
};

void cCollisionHandlerBSP::GenerateSlotArray()
{
switch(WT_COLLISION_HANDLER_DIMENSIONS)
{
    case WT_COLLISION_HANDLER_DIMENSIONS_1D:
    {
        if(mpSlotArray){delete []mpSlotArray;}
        mpSlotArray= new int16[3];
        mpSlotArray[0]=-1;
        mpSlotArray[1]=0;
        mpSlotArray[2]=1;
    };break;
    case WT_COLLISION_HANDLER_DIMENSIONS_2D:
    {
        if(mpSlotArray){delete []mpSlotArray;}
        mpSlotArray= new int16[9];
        mpSlotArray[0]=-WT_COLLISION_HANDLER_SIZE-1;
        mpSlotArray[1]=-WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[2]=1-WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[3]=-1;
        mpSlotArray[4]=0;
        mpSlotArray[5]=1;
        mpSlotArray[6]=WT_COLLISION_HANDLER_SIZE-1;
        mpSlotArray[7]=WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[8]=WT_COLLISION_HANDLER_SIZE+1;
    };break;
    case WT_COLLISION_HANDLER_DIMENSIONS_3D:
    {
        if(mpSlotArray)
        {
            delete []mpSlotArray;
        }
        mpSlotArray= new int16[27];
        mpSlotArray[0]=-WT_COLLISION_HANDLER_SIZE-1-WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[1]=-WT_COLLISION_HANDLER_SIZE-WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[2]=1-WT_COLLISION_HANDLER_SIZE-WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[3]=-1-WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[4]=-WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[5]=1-WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[6]=WT_COLLISION_HANDLER_SIZE-1-WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[7]=WT_COLLISION_HANDLER_SIZE-WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[8]=WT_COLLISION_HANDLER_SIZE+1-WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;

        mpSlotArray[9]=-WT_COLLISION_HANDLER_SIZE-1;
        mpSlotArray[10]=-WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[11]=1-WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[12]=-1;
        mpSlotArray[13]=0;
        mpSlotArray[14]=1;
        mpSlotArray[15]=WT_COLLISION_HANDLER_SIZE-1;
        mpSlotArray[16]=WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[17]=WT_COLLISION_HANDLER_SIZE+1;

        mpSlotArray[18]=-WT_COLLISION_HANDLER_SIZE-1+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[19]=-WT_COLLISION_HANDLER_SIZE+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[20]=1-WT_COLLISION_HANDLER_SIZE+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[21]=-1+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[22]=WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[23]=1+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[24]=WT_COLLISION_HANDLER_SIZE-1+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[25]=WT_COLLISION_HANDLER_SIZE+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;
        mpSlotArray[26]=WT_COLLISION_HANDLER_SIZE+1+WT_COLLISION_HANDLER_SIZE*WT_COLLISION_HANDLER_SIZE;

    };break;
};

};

c3DVf cCollisionHandlerBSP::FindSlotCentre(uint8 liX,uint8 liY,uint8 liZ)
{
    c3DVf lfReturn;
    lfReturn[0]=liX*WT_COLLISION_SPACE_SIZE+mfCentre[mpAxisOrder[0]]-mfOffSet[mpAxisOrder[0]]+0.5f*WT_COLLISION_SPACE_SIZE;
    lfReturn[1]=liY*WT_COLLISION_SPACE_SIZE+mfCentre[mpAxisOrder[1]]-mfOffSet[mpAxisOrder[1]]+0.5f*WT_COLLISION_SPACE_SIZE;
    lfReturn[2]=liZ*WT_COLLISION_SPACE_SIZE+mfCentre[mpAxisOrder[2]]-mfOffSet[mpAxisOrder[2]]+0.5f*WT_COLLISION_SPACE_SIZE;
    return lfReturn;

};

c3DVf cCollisionHandlerBSP::FindSlotCentre(uint8 *lpX)
{
    c3DVf lfReturn;
    lfReturn[0]=lpX[mpAxisOrder[0]]*WT_COLLISION_SPACE_SIZE+mfCentre[mpAxisOrder[0]]-mfOffSet[mpAxisOrder[0]]+0.5f*WT_COLLISION_SPACE_SIZE;
    lfReturn[1]=lpX[mpAxisOrder[1]]*WT_COLLISION_SPACE_SIZE+mfCentre[mpAxisOrder[1]]-mfOffSet[mpAxisOrder[1]]+0.5f*WT_COLLISION_SPACE_SIZE;
    lfReturn[2]=lpX[mpAxisOrder[2]]*WT_COLLISION_SPACE_SIZE+mfCentre[mpAxisOrder[2]]-mfOffSet[mpAxisOrder[2]]+0.5f*WT_COLLISION_SPACE_SIZE;
    return lfReturn;

};

c3DVf cCollisionHandlerBSP::FindSlotCentre(uint32 liSlot)
{
 return FindSlotCentre(SlotIndexToCoord(liSlot));
};
