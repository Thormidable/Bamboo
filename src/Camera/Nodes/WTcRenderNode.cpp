
#include "../../WTBamboo.h"

void cRenderNode::Initialise()
{
	mbAwake=true;
	mbAlive=true;
	mpObjects=0;
}


cRenderNode::cRenderNode()
{

 Initialise();
}

cRenderNode::cRenderNode(vRenderNode *lpRenderer) : vRenderNode(lpRenderer)
{
 Initialise();
}

cRenderNode::cRenderNode(bool lpTopLevel,cCamera *lpCamera) : vRenderNode(lpTopLevel,lpCamera)
{
 Initialise();

}
cRenderNode::cRenderNode(cCamera *lpCamera) : vRenderNode(lpCamera)
{
Initialise();
}


cRenderNode::~cRenderNode()
{
	KillAll();
	delete mpObjects;
	mpObjects=0;
	mpRenderer=0;
	mcOwnerNode.Node=0;
	mpCamera=0;

}

void cRenderNode::DeleteAll(){ delete mpObjects; mpObjects=0;}

cRenderOwner cRenderNode::Add(vRenderObject *lpNew)
{
 cRenderOwner lcOwner;
 if(!mpObjects) {mpObjects=new cLinkedList<vRenderObject>(lpNew); lcOwner.Node=mpObjects->Start();}
 else lcOwner.Node=mpObjects->Insert(lpNew);
 lcOwner.List=0;
 return lcOwner;
}


void cRenderNode::Delete(cRenderOwner lpOld)
{
	mpObjects->Delete(lpOld.Node);
}

void cRenderNode::StartKillAll()
{
    KillAll();
    //if(mpRenderer) mpRenderer->Delete(mcOwnerNode);
    //else trace("This is the Camera cRenderNode. Cannot Delete.");
}

void cRenderNode::KillAll()
{
    if(mpObjects)
    {
        mpCursor=mpObjects->Start();
        if(mpCursor)
        {
        while(mpCursor->Next())
        {
            mpCursor->Data()->KillAll();
            mpCursor=mpCursor->Next();
            delete mpCursor->Previous();
        }
            mpCursor->Data()->KillAll();
            delete mpCursor;

        mpObjects->Initialise();
        delete mpObjects;
        }
    }
    mpObjects=0;
}

void cRenderNode::RecalculateTotalMatrix()
{
	mmTotalCache=_COMBINED_MATRIX;
	mmTotalCache.Multiply(mmCache);
 if(mpObjects)
 {
  mpCursor=mpObjects->Start();
  while(mpCursor)
  {
	if(mpCursor->Data()->Awake())
	{
		mpCursor->Data()->RecalculateTotalMatrix();
		mpCursor=mpCursor->Next();
	}
	else
	{
		if(!(mpCursor->Data()->Alive()))
		{

			if(mpCursor->Next())
			{
				mpCursor=mpCursor->Next();
				mpObjects->Delete(mpCursor->Previous());
			}
			else
			{

				mpObjects->Delete(mpCursor);
				mpCursor=0;
			}
		}
		else
		{
			mpCursor=mpCursor->Next();
		}
	}


  }
  //AdditionalRenderFunctions();

 }

}


void cRenderNode::CalculateMatrices()
{
  UpdateMatrix();
  UpdateCache();
 if(mpObjects)
 {

  mpCursor=mpObjects->Start();
  while(mpCursor)
  {
		_MATRIX_STACK->Push();
	if(mpCursor->Data()->Awake())
	{

		mpCursor->Data()->CalculateMatrices();
		mpCursor=mpCursor->Next();
	}
	else
	{
		if(!(mpCursor->Data()->Alive()))
		{

			if(mpCursor->Next())
			{
				mpCursor=mpCursor->Next();
				mpObjects->Delete(mpCursor->Previous());
			}
			else
			{

				mpObjects->Delete(mpCursor);
				mpCursor=0;
			}
		}
		else
		{
			mpCursor=mpCursor->Next();
		}
	}
	_MATRIX_STACK->Pop();
  }
 }
}

void cRenderNode::RenderToPainter()
{

  UpdateMatrix();
  UpdateCache();
 if(mpObjects)
 {
  mpCursor=mpObjects->Start();
  while(mpCursor)
  {
		_MATRIX_STACK->Push();

	if(mpCursor->Data()->Awake())
	{
		mpCursor->Data()->RenderToPainter();
		mpCursor->Data()->UpdateCache();
		mpCursor=mpCursor->Next();
	}
	else
	{
		if(!(mpCursor->Data()->Alive()))
		{

			if(mpCursor->Next())
			{
				mpCursor=mpCursor->Next();
				mpObjects->Delete(mpCursor->Previous());
			}
			else
			{

				mpObjects->Delete(mpCursor);
				mpCursor=0;
			}
		}
		else
		{
			mpCursor=mpCursor->Next();
		}
	}

	_MATRIX_STACK->Pop();

  }

 }
}

void cRenderNode::AdditionalRenderFunctions(){};



cLinkedList<vRenderObject> *cRenderNode::RenderList(){ return mpObjects;};

//void cRenderNode::LinkCollisionObject(cCollisionObject *lpObj){  (void) lpObj; uint32 MAKE_RENDER_NODES_SUITABLE_FOR_COLLISION_OBJECTS;};

cRenderOwner cRenderNode::MoveItem(vRenderObject *lpObj, vRenderNode *lpRenderer)
{
 mpObjects->Remove(lpObj->RenderOwner().Node);
 lpObj->RenderOwner(lpRenderer->Add(lpObj));
 lpObj->mpRenderer=lpRenderer;
 return lpObj->RenderOwner();
};

void cRenderNode::MoveAll(vRenderNode *lpRender)
{

 if(mpObjects)
 {
  for(mpCursor=mpObjects->Start();mpCursor;mpCursor=mpCursor->Next())
  {
	  vRenderObject *lpObj=mpCursor->Data();
	  	lpObj->mpRenderer=lpRender;
	lpObj->RenderOwner(lpRender->Add(lpObj));

  }
  mpObjects->ClearAll();
 }

};

vRenderObject *cRenderNode::FindStart()
{
 if(mpObjects) return mpObjects->FindStart();
 return 0;
};
vRenderObject *cRenderNode::FindNext()
{
 if(mpObjects) return mpObjects->FindNext();
 return 0;
};

bool cRenderNode::ContainsItems()
{
	if(mpObjects)
	{
		return mpObjects->FindStart();
	}
	return 0;
};


float cRenderNode::GetSize()
{
 float lfSize=0.0f;
 if(mpObjects)
 {
    for(vRenderObject *lpCur=mpObjects->FindStart();lpCur;lpCur=mpObjects->FindNext())
    {
        float lfTemp=lpCur->GetSize()+lpCur->Distance();
        if(lfTemp>lfSize) lfSize=lfTemp;
    }
 }
 return lfSize;
};

double cRenderNode::GetSizeSq()
{
 double lfSize=0.0f;
 if(mpObjects)
 {
    for(vRenderObject *lpCur=mpObjects->FindStart();lpCur;lpCur=mpObjects->FindNext())
    {
        double lfTemp=lpCur->GetSizeSq()+lpCur->DistanceSq();
        if(lfTemp>lfSize) lfSize=lfTemp;
    }
 }
 return lfSize;
};


void cRenderNode::TreeProcessUserSignal(SIGNAL lsSignal,void *lpData)
{
if(mpProcess) mpProcess->UserSignal(lsSignal,lpData);
 if(mpObjects)
 {
    for(vRenderObject *lpCur=mpObjects->FindStart();lpCur;lpCur=mpObjects->FindNext())
    {
       lpCur->TreeProcessUserSignal(lsSignal,lpData);
    }
 }
};

void cRenderNode::TreeProcessSignal(SIGNAL lsSignal)
{
 if(mpProcess) mpProcess->Signal(lsSignal);
    if(mpObjects)
 {
    for(vRenderObject *lpCur=mpObjects->FindStart();lpCur;lpCur=mpObjects->FindNext())
    {
        lpCur->TreeProcessSignal(lsSignal);
    }
 }
};


void cRenderNode::TreeSignal(SIGNAL lsSignal)
{
 Signal(lsSignal);
     if(mpObjects)
 {
    for(vRenderObject *lpCur=mpObjects->FindStart();lpCur;lpCur=mpObjects->FindNext())
    {
        lpCur->TreeSignal(lsSignal);
    }
 }
}
