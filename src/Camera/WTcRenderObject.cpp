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

	mpPainterData= new cRenderPointer();
	_PAINTER->Add(mpPainterData);
	mpPainterData->SetObject(this);
 mpCollisionObject=0;
 Shader(0);
 Transparency(0);
}

void cRenderObject::Delete()
{

	if(mpCollisionObject)
	{
		_KILL(mpCollisionObject);
		mpCollisionObject=0;
	}

	_PAINTER->Remove(mpPainterData);
	delete mpPainterData;
	mpPainterData=0;

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
	if(mpCollisionObject)
	{
		_KILL(mpCollisionObject);
		mpCollisionObject=0;
	}
}



void cRenderObject::AdditionalSleepFunctionality()
{

	_PAINTER->Remove(mpPainterData);
	delete mpPainterData;
	mpPainterData=0;

if(mpCollisionObject)
{
    _SLEEP(mpCollisionObject);
}


}

void cRenderObject::AdditionalWakeFunctionality()
{

	mpPainterData=new cRenderPointer;
	_PAINTER->Add(mpPainterData);
	mpPainterData->SetObject(this);

if(mpCollisionObject)
{
    _WAKE(mpCollisionObject);
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



void cRenderObject::Shader(cShaderProgram *lpShader)
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
  	cMatrix4 Temp;
  	if(mb3D)
  	{
  	  AddUniform<cUniformMatrix>("mmProj")->Data=_CAMERA->TotalPositionMatrix();
  	  AddUniform<cUniformMatrix>("mmGlob")->Data=mmCache.Matrix();
  	}
  	else
  	{
  	 AddUniform<cUniformMatrix>("mmProj")->Data=_CAMERA->Perspective();
     AddUniform<cUniformMatrix>("mmGlob")->Data=mmCache.Matrix();
  	}

  }

}

cShaderProgram *cRenderObject::Shader()
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

float *cRenderObject::GetCachedGlobalMatrix()
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

void cRenderObject::Transparency(bool lbTrans){mbAlpha=lbTrans;}
bool cRenderObject::Transparency(){return mbAlpha;}

void cRenderObject::SetOtherRenderVariables()
{
    mpPainterData->SetAlpha(mbAlpha);
    mpPainterData->SetShader(mpShader);
}

cMatrix4 vRenderObject::CalculateGlobalMatrix()
{
    if(Renderer())
    {
     return Renderer()->CalculateGlobalMatrix()*ThisMatrix();
    }
    else return ThisMatrix();
}
