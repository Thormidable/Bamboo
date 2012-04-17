#include "../WTBamboo.h"


cCollisionObject *cCollisionList::mpOther=0;
cCollisionList *cCollisionList::mpStaticList=0;



cCollisionListObject::cCollisionListObject(cCollisionObject *lpObj){mpObj=lpObj;mfBeamLength=10000.0f;};
	cCollisionListObject::cCollisionListObject(){mfBeamLength=10000.0f;};
	float cCollisionListObject::Distance(){return mfDistance;};
 	float cCollisionListObject::BeamLength(){return mfBeamLength;};


void cCollisionList::AddCollision(cCollisionObject *lpObject)
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



cCollisionObject *cCollisionList::NextCollisionItem()
{
++miCurPos;
 if(miCurPos==Items()){miCurPos=-1; return 0;}
 return mpList[miCurPos]->mpObj;
}

cProcess *cCollisionList::NextCollisionP()
{
cCollisionObject *lpTemp=NextCollisionItem();
while(lpTemp)
{
	if(lpTemp->GetLink()) return lpTemp->GetLink();
 lpTemp=NextCollisionItem();
}
 return 0;
}

vRenderObject *cCollisionList::NextCollisionR()
{
	cCollisionObject *lpTemp=NextCollisionItem();
	do
	{
		if(lpTemp && lpTemp->RenderObject()) return lpTemp->RenderObject();
		lpTemp=NextCollisionItem();
	}while(lpTemp);
	return 0;

}

cCollisionList::~cCollisionList()
{

}

cCollisionList::cCollisionList(cCollisionObject *lpThis)
{
    mpThisColl=lpThis;
	miCurPos=-1;
};

cCollisionObject *cCollisionList::CurrentCollisionItem()
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

void cCollisionListObject::RecalculateDistance(cCollisionObject *lpThis)
{
    mfDistance=lpThis->Following()->mmCache.Distance(mvCentre);
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
