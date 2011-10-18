#include "../../WTDivWin.h"

void cRenderNode::Initialise()
{
	mbAwake=true;
	mbAlive=true;

}



cRenderNode::cRenderNode()
{
 mpObjects=0;
 mpRenderer=cCamera::Instance()->RenderList();
 mpNode=mpRenderer->Add(this);
 Initialise();
 Identity();
}

cRenderNode::cRenderNode(cRenderNode *lpRenderer)
{
	mpObjects=0;
 if(lpRenderer)
 {
  mpRenderer=lpRenderer;
  mpNode=lpRenderer->Add(this);
 }
 else
 {
  mpRenderer=0; //This represents the top level
  mpNode=0;
 }
 Initialise();
 Identity();
}


cRenderNode::~cRenderNode()
{
//	if(mpRenderer) mpRenderer->Remove(mpNode);
 DeleteAll();
}

void cRenderNode::DeleteAll()
{
	
// mpObjects->DeleteAll();
// mpObjects->Initialise();
 delete mpObjects; mpObjects=0;
 
}

cLinkedNode<vRenderObject> *cRenderNode::Add(vRenderObject *lpNew)
{
 if(!mpObjects) {mpObjects=new cLinkedList<vRenderObject>(lpNew); return mpObjects->Start();}
 else return mpObjects->Insert(lpNew);
}

void cRenderNode::Remove(cLinkedNode<vRenderObject> *lpOld)
{
	mpObjects->Delete(lpOld);
}


void cRenderNode::RenderToPainter()
{
 if (mpObjects)
 {

	_MATRIX_STACK->Push();

  //glMultMatrixf(Matrix());
  UpdateMatrix();
  UpdateCache();
  mpCursor=mpObjects->Start();
  while(mpCursor)
  {
		_MATRIX_STACK->Push();

	if(mpCursor->mpData->Awake())
	{
		mpCursor->mpData->RenderToPainter();
		mpCursor->mpData->UpdateCache();
		mpCursor=mpCursor->Next();
	}
	else
	{
		if(!(mpCursor->mpData->Alive()))
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
  AdditionalRenderFunctions();

	_MATRIX_STACK->Pop();

 }
}


void cRenderNode::Render()
{
 if (mpObjects)
 {
//Are these neccessary as Node beneath will glPush and gl Pop
  //glPushMatrix();
  //ResetSize();
  UpdateMatrix();
  AdditionalRenderFunctions();
  mpCursor=mpObjects->Start();
  while(mpCursor)
  {

		_MATRIX_STACK->Push();

	if(mpCursor->mpData->Awake())
	{
		mpCursor->mpData->Render();
		mpCursor->mpData->UpdateCache();
		mpCursor=mpCursor->Next();
	}
	else
	{
		if(!(mpCursor->mpData->Alive())) 
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
  //Are these neccessary as Node beneath will glPush and gl Pop
  //glPopMatrix();
 }
}

void cRenderNode::AdditionalRenderFunctions()
{
  
};

void cRenderNode::RenderPainter(uint8 liLevel){(void) liLevel;};    
void cRenderNode::RenderPainter(){};

	
cLinkedList<vRenderObject> *cRenderNode::RenderList()
{
  return mpObjects;
  
};

cRenderNode *cRenderNode::Renderer()
{
  return mpRenderer;
  
}

void cRenderNode::LinkCollisionObject(cCollisionObject *lpObj)
{
  (void) lpObj; uint32 MAKE_RENDER_NODES_SUITABLE_FOR_COLLISION_OBJECTS;
  
};

void cRenderNode::UpdateCache()
{
	mmCache=_MATRIX_STACK->Current();
  //glGetFloatv(GL_MODELVIEW_MATRIX,mmCache.Matrix());  
}


float *cRenderNode::GetPos()
{
  return Position();
  
};

float *cRenderNode::GetGlobalPos()
{
  return mmCache.Position();
  
};

cVariableStore *cRenderNode::Variables()
{
 return 0;
}
