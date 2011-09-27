#include "../WTDivWin.h"

cRenderObject::~cRenderObject()
{

Delete();
 
}

void cRenderObject::LinkCollisionObject(cCollisionObject *lpObj)
{
  mpCollisionObject=lpObj;
  
};

cRenderObject::cRenderObject()
{
 mpRenderer=cCamera::Instance()->RenderList();
 mpNode=mpRenderer->Add(this);
 Shader(0);
Initialise();
}

cRenderObject::cRenderObject(cRenderNode *lpNode)
{

  mpRenderer=lpNode;
  mpNode=lpNode->Add(this);
  Shader(0);
Initialise();
}

void cRenderObject::Initialise()
{
  mbAwake=true;
  mbAlive=true;

if(WT_USE_PAINTER_ALGORITHM)
{
	mpPainterData= new cRenderPointer();
	_PAINTER->Add(mpPainterData);
	mpPainterData->SetObject(this);
}
 mpCollisionObject=0;
 Shader(0);
}

void cRenderObject::Delete()
{
	
	if(mpCollisionObject)
	{
		_KILL(mpCollisionObject);
		mpCollisionObject=0;
	}

//mpRenderer->Remove(mpNode);
if(WT_USE_PAINTER_ALGORITHM)
{
	_PAINTER->Remove(mpPainterData);
	delete mpPainterData;
	mpPainterData=0;
}

}

cLinkedNode<vRenderObject> *cRenderObject::SetRenderNode(cRenderNode *lpRenderer)
{
 if(mpRenderer==lpRenderer) return mpNode;
 if(mpRenderer) mpRenderer->Remove(mpNode);
 mpRenderer=lpRenderer;
 mpNode=lpRenderer->Add(this);
 return mpNode;
}


void cRenderObject::AdditionalRenderFunctions()
{
 UpdateCache();
}

void cRenderObject::AdditionalKillFunctionality()
{
	//Delete();

	if(Renderer() && mpNode) Renderer()->Remove(mpNode);else trace("Cannot _S_Kill this Node, Is it the Camera List?\n");
}

void cRenderObject::AdditionalSleepFunctionality()
{
	uint32 IS_THIS_OPTIMISING_Sending_Render_Objects_to_Sleep;
	
if(WT_USE_PAINTER_ALGORITHM)
{
	_PAINTER->Remove(mpPainterData);
	delete mpPainterData;
	mpPainterData=0;
}
 

}

void cRenderObject::AdditionalWakeFunctionality()
{
	
if(WT_USE_PAINTER_ALGORITHM)
{
	mpPainterData=new cRenderPointer;
	_PAINTER->Add(mpPainterData);
	mpPainterData->SetObject(this);
}
	
}

void cRenderObject::UpdateCache()
{

	if(mpCollisionObject)
	{
		mpCollisionObject->NotCreatedThisFrame();
		mpCollisionObject->PreUpdateCache();
		glGetFloatv(GL_MODELVIEW_MATRIX,mmCache.Matrix());
		mpCollisionObject->PostUpdateCache();
	}
	else
	{
		glGetFloatv(GL_MODELVIEW_MATRIX,mmCache.Matrix());
	}
	
};



void cRenderObject::Shader(vShaderProgram *lpShader)
{
  mpShader=lpShader;
  
}

vShaderProgram *cRenderObject::Shader()
{
  return mpShader;
  
}

cRenderNode *cRenderObject::Renderer()
{
  return mpRenderer;
  
}


float *cRenderObject::GetPos()
{
  return Position();
  
};

float *cRenderObject::GetGlobalPos()
{
  return mmCache.Position();

};
