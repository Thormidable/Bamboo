#include "../../WTBamboo.h"

void cRenderNode::Initialise()
{
	mbAwake=true;
	mbAlive=true;
	mpObjects=0;
}


cRenderNode::cRenderNode()
{
 mpRenderer=cCamera::Instance()->RenderList();
 mcOwnerNode=mpRenderer->Add(this);
 Initialise();
 Identity();
}

cRenderNode::cRenderNode(vRenderNode *lpRenderer)
{

 if(lpRenderer)
 {
  mpRenderer=lpRenderer;
  mcOwnerNode=lpRenderer->Add(this);
 }
 else
 {
  mpRenderer=0; //This represents the top level
  mcOwnerNode.Node=0;
 }
 Initialise();
 Identity();
}


cRenderNode::~cRenderNode()
{

	delete mpObjects;
	mpObjects=0;
	mpRenderer=0;
	mcOwnerNode.Node=0;

}

void cRenderNode::DeleteAll(){ delete mpObjects; mpObjects=0;}

cRenderOwner cRenderNode::Add(vRenderObject *lpNew)
{
 cRenderOwner lcOwner;
 if(!mpObjects) {mpObjects=new cLinkedList<vRenderObject>(lpNew); lcOwner.Node=mpObjects->Start();}
 else lcOwner.Node=mpObjects->Insert(lpNew);
 return lcOwner;
}


void cRenderNode::Remove(cRenderOwner lpOld)
{
	mpObjects->Delete(lpOld.Node);
}

void cRenderNode::StartKillAll()
{
    KillAll();
    if(mpRenderer) mpRenderer->Remove(mcOwnerNode);
    else trace("This is the Camera cRenderNode. Cannot Delete.");
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
 if (mpObjects)
 {

  UpdateMatrix();
  UpdateCache();
  mpCursor=mpObjects->Start();
  while(mpCursor)
  {
		_MATRIX_STACK->Push();

	if(mpCursor->Data()->Awake())
	{
		mpCursor->Data()->UpdateMatrix();
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
 if (mpObjects)
 {

  UpdateMatrix();
  UpdateCache();
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
  //AdditionalRenderFunctions();

 }
}

void cRenderNode::AdditionalRenderFunctions(){};



cLinkedList<vRenderObject> *cRenderNode::RenderList(){ return mpObjects;};

void cRenderNode::LinkCollisionObject(cCollisionObject *lpObj){  (void) lpObj; uint32 MAKE_RENDER_NODES_SUITABLE_FOR_COLLISION_OBJECTS;};

