#include "../WTDivWin.h"



void cCollisionList::AddCollision(cCollisionObject *lpObject)
{
	mpCollisionList->Insert(lpObject);
}

cCollisionObject *cCollisionList::NextCollisionItem()
{
 if(!mpCurPos)
 {
	 mpCurPos=mpCollisionList->Start();
 }
 else { mpCurPos=mpCurPos->Next();}
 if(mpCurPos) return mpCurPos->mpData;

 return 0;
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



void cCollisionList::ResetList()
{
 mpCollisionList->ClearAll();
 mpCurPos=0;
}

cCollisionList::~cCollisionList()
{
	ResetList();
	delete mpCollisionList;
}

cCollisionList::cCollisionList()
{
	mpCollisionList=new cLinkedList<cCollisionObject>;
	mpCurPos=0;

};

void cCollisionList::SortByDistance()
{
 uint32 THIS_IS_FAIRLY_USEFUL_FOR_BEAMS;

};
