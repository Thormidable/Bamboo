#include "stdafx.h"
#include "../WTBamboo.h"


cCollisionBase *cCollisionList::mpOther=0;
cCollisionList *cCollisionList::mpStaticList=0;



cCollisionListObject::cCollisionListObject(cCollisionBase *lpObj){mpObj=lpObj;mfBeamLength=10000.0f;};
	cCollisionListObject::cCollisionListObject(){mfBeamLength=10000.0f;};
	float cCollisionListObject::Distance(){return mfDistance;};
 	float cCollisionListObject::BeamLength(){return mfBeamLength;};


void cCollisionList::AddCollision(cCollisionBase *lpObject)
{
	Add(new cCollisionListObject(lpObject));
}

void cCollisionList::AddCollision()
{
    Add(new cCollisionListObject(mpOther));
};

void cCollisionList::AddCollision(cCollisionListObject *lpObj)
{
    Add(lpObj);
};

void cCollisionList::ResetCursor()
{
    miCurPos=-1;
};

void cCollisionList::SetCursorPosition(int32 liCursorPos)
{
    if(--liCursorPos<miItems) miCurPos=liCursorPos;
    else miCurPos=miItems-2;
};

cCollisionBase *cCollisionList::NextCollisionItem()
{
++miCurPos;
 if(miCurPos>=Items()){miCurPos=-1; return 0;}
 return mpList[miCurPos]->mpObj;
}

cProcess *cCollisionList::NextCollisionP()
{
cCollisionBase *lpTemp=NextCollisionItem();
while(lpTemp)
{
	if(lpTemp->GetLink()) return lpTemp->GetLink();
 lpTemp=NextCollisionItem();
}
 return 0;
}

vRenderObject *cCollisionList::NextCollisionR()
{
	cCollisionBase *lpTemp=NextCollisionItem();
	while(lpTemp)
	{
		if(lpTemp->RenderObject()) return lpTemp->RenderObject();
		lpTemp=NextCollisionItem();
	}
	return 0;

}

cCollisionList::~cCollisionList()
{

}

cCollisionList::cCollisionList(cCollisionBase *lpThis)
{
    mpThisColl=lpThis;
	miCurPos=-1;
};

cCollisionBase *cCollisionList::CurrentCollisionItem()
{
    if(miCurPos>-1) return mpList[miCurPos]->mpObj;
    return 0;
}

cCollisionListObject *cCollisionList::NextCollisionDetail()
{
 ++miCurPos;
 if(miCurPos==Items()){miCurPos=-1; return 0;}
 return mpList[miCurPos];
};

cCollisionListObject *cCollisionList::CurrentCollisionDetail()
{
    if(miCurPos>-1) return mpList[miCurPos];
    return 0;
}

cProcess *cCollisionList::CurrentCollisionP()
{
    if(miCurPos>-1) return mpList[miCurPos]->mpObj->GetLink();
    return 0;
}

vRenderObject *cCollisionList::CurrentCollisionR()
{
    if(miCurPos>-1) return mpList[miCurPos]->mpObj->RenderObject();
    return 0;
}

void cCollisionList::SortByDistance()
{

if(Items()>1)
{
    SelectionSort(mpList,Items(),CompareDistances);
}

};

void cCollisionList::SortByBeamLength()
{
if(Items()>1)
{
    SelectionSort(mpList,Items(),CompareDistances);
}

};

void cCollisionList::RecalculateDistances()
{
 if(mpThisColl)
 {
    for(uint32 liCount=0;liCount<Items();++liCount)
    {
        mpList[liCount]->RecalculateDistance(mpThisColl);
    }
 }
}

void cCollisionListObject::RecalculateDistance(cCollisionBase *lpThis)
{
    mfDistance=lpThis->RenderObject()->mmCache.Distance(mvCentre);
};

c3DVf cCollisionListObject::Centre(){return mvCentre;};

bool cCollisionList::CompareDistances(cCollisionListObject *lp1,cCollisionListObject *lp2)
{
    return (lp1->Distance()<lp2->Distance());
};

bool cCollisionList::CompareBeamLengths(cCollisionListObject *lp1,cCollisionListObject *lp2)
{
    return (lp1->BeamLength()<lp2->BeamLength());
};
