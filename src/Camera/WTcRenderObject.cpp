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
 mpVariables=0;
 Shader(0);
Initialise();
}

cRenderObject::cRenderObject(cRenderNode *lpNode)
{
 mpVariables=0;
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
// UpdateCache();
// SetShaderVariables();
	
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

		mmCache=_MATRIX_STACK->Current();

		mpCollisionObject->PostUpdateCache();
	}
	else
	{
		mmCache=_MATRIX_STACK->Current();
	}
	
};



void cRenderObject::Shader(vShaderProgram *lpShader)
{
  mpShader=lpShader;
  
  if(mpVariables)
  {
	if(mpShader) mpVariables->Link(mpShader);
	else mpVariables->ClearLink();
  }
  if(mpShader)
  {
  	mpShader->Use();
  	AddUniform<cUniformMatrix>("mmProj")->Data=_CAMERA->Perspective();
  	AddUniform<cUniformMatrix>("mmGlob")->Data=mmCache.Matrix();
  }
  
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

cVariableStore *cRenderObject::Variables()
{
 if(!mpVariables) mpVariables=new cVariableStore(mpShader);
 return mpVariables;

}

void cRenderObject::SetShaderVariables()
{
 if(mpVariables)
 {
  mpVariables->WriteUniforms();
  mpVariables->WriteAttributes();
 }

}

