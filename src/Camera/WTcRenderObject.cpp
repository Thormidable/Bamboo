#include "../WTBamboo.h"

cRenderObject::~cRenderObject()
{
    if(mpCollisionObject)
	{
		_KILL(mpCollisionObject);
		mpCollisionObject=0;
	}

    if(mpPainterData)
    {
    _PAINTER->Remove(mpPainterData);
	delete mpPainterData;
	mpPainterData=0;
    }

	delete mpVariables;
	mpVariables=0;

}

void cRenderObject::LinkCollisionObject(cCollisionObject *lpObj)
{
  mpCollisionObject=lpObj;

};

cRenderObject::cRenderObject()
{
	printf("This:%p\n",this);
 mpRenderer=cCamera::Instance()->RenderList();
 printf("cRenderObject::cRenderObject()\n");
 printf("Renderer() : %p\n",mpRenderer);
 mcOwnerNode=mpRenderer->Add(this);

Initialise();
}

cRenderObject::cRenderObject(vRenderNode *lpNode)
{
	printf("This:%p\n",this);
 printf("cRenderObject::cRenderObject(vRenderNode *lpNode)\n");
 printf("Renderer() : %p\n",lpNode);
  mpRenderer=lpNode;
  mcOwnerNode=lpNode->Add(this);
Initialise();
}


cRenderObject::cRenderObject(bool lbNoTextures): cTextureStack(lbNoTextures)
{
	printf("This:%p\n",this);
	 mpRenderer=cCamera::Instance()->RenderList();
	  printf("cRenderObject::cRenderObject()\n");
 printf("Renderer() : %p\n",mpRenderer);
 mcOwnerNode=mpRenderer->Add(this);

Initialise();
}

cRenderObject::cRenderObject(vRenderNode *lpNode,bool lbNoTextures) : cTextureStack(lbNoTextures)
{
	printf("This:%p\n",this);
	 printf("cRenderObject::cRenderObject(vRenderNode *lpNode)\n");
 printf("Renderer() : %p\n",lpNode);
  mpRenderer=lpNode;
  mcOwnerNode=lpNode->Add(this);
Initialise();

}
void cRenderObject::AddTexture(string lsTextureSlot,cTexture *lpTexture)
{
 if(mpShader)
 {
 	uint32 liPos=mpShader->ShaderVariables()->GetUniformPosition(lsTextureSlot);
 	if(liPos) AddTexture(liPos-1,lpTexture);
 }
}

void cRenderObject::RemoveTexture(string lsTextureSlot)
{
  	if(mpShader)
	{
		uint32 liPos=mpShader->ShaderVariables()->GetUniformPosition(lsTextureSlot);
		if(liPos) RemoveTextureByUniform(liPos-1);
	}
}

void cRenderObject::RemoveTexture(uint8 liSlot)
{
	RemoveTextureBySlot(liSlot);
}


void cRenderObject::AddTexture(cTexture *lpTexture)
{

 int8 liSlot=ReturnFreeSlot();
 if(liSlot && mpShader)
 {
 		string lsTextureSlot="Texture";
 		std::stringstream out;
 		out << miTextures;
		lsTextureSlot.append(out.str());
		uint32 liPos=mpShader->ShaderVariables()->GetUniformPosition(lsTextureSlot);
	 	if(liPos) AddTexture(liPos-1,lpTexture);
 }
}



void cRenderObject::Initialise()
{
  mbAwake=true;
  mbAlive=true;
mpVariables=0;
		mpShader=0;
	mpPainterData= new cRenderPointer();
	_PAINTER->Add(mpPainterData);
	mpPainterData->SetObject(this);
 mpCollisionObject=0;

 Transparency(0);
 Lighting(1);
}

void cRenderObject::Delete()
{

}


vRenderNode* vRenderNode::Renderer(){return mpRenderer;};
void vRenderNode::RenderPainter(){};
void vRenderNode::UpdateCache()
{
	mmCache=_MATRIX_STACK->Current();
	mmTotalCache=_CAMERA->PerspectiveCameraMatrix();
	mmTotalCache.Multiply(mmCache);
}
float* vRenderNode::GetPos(){return Position();};
float* vRenderNode::GetCachedGlobalMatrix(){return mmCache.Matrix();}

void vRenderNode::AdditionalKillFunctionality()
{

}

cVariableStore* vRenderNode::Variables(){return 0;}

cRenderOwner &cRenderObject::SetRenderNode(vRenderNode *lpRenderer)
{
 if(mpRenderer==lpRenderer) return mcOwnerNode;
 //if(mpRenderer) mpRenderer->Remove(mcOwnerNode);
 mpRenderer=lpRenderer;
 mcOwnerNode=lpRenderer->Add(this);
 return mcOwnerNode;
}


void cRenderObject::AdditionalRenderFunctions()
{
// UpdateCache();
// SetShaderVariables();

}

void cRenderObject::AdditionalKillFunctionality()
{
	    if(mpCollisionObject)
	{
		_KILL(mpCollisionObject);
		mpCollisionObject=0;
	}

    if(mpPainterData)
    {
    _PAINTER->Remove(mpPainterData);
	delete mpPainterData;
	mpPainterData=0;
    }

	delete mpVariables;
	mpVariables=0;

    /*
    if(mpCollisionObject)
	{
		_KILL(mpCollisionObject);
		mpCollisionObject=0;
	}

    if(mpPainterData)
    {
    _PAINTER->Remove(mpPainterData);
	delete mpPainterData;
	mpPainterData=0;
    }
    */
/*
	if(Renderer() && mcOwnerNode.Node)
        Renderer()->Remove(mcOwnerNode);
    else
        trace("Cannot _S_Kill this Node, Is it the Camera List\n");
*/
}



void cRenderObject::AdditionalSleepFunctionality()
{
    if(mpPainterData)
    {
        _PAINTER->Remove(mpPainterData);
        delete mpPainterData;
        mpPainterData=0;
    }

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
		mmTotalCache=_CAMERA->PerspectiveCameraMatrix();
		mmTotalCache.Multiply(mmCache);

		mpCollisionObject->PostUpdateCache();
	}
	else
	{
		mmCache=_MATRIX_STACK->Current();
		mmTotalCache=_CAMERA->PerspectiveCameraMatrix();
	    mmTotalCache.Multiply(mmCache);
	}

};



void cRenderObject::Shader(cShaderProgram *lpShader)
{
 if(!lpShader && mpShader) ClearTextureStack();

  mpShader=lpShader;

  if(mpVariables)
  {
	if(mpShader) mpVariables->Link(mpShader);
	else mpVariables->ClearLink();
  }
  if(mpShader)
  {
	  mpShader->Use();
	cUniformMatrix *lpMatrix=AddUniform<cUniformMatrix>("mmGlobal");
		if(lpMatrix) lpMatrix->Data=mmCache.Matrix();
	lpMatrix=AddUniform<cUniformMatrix>("mmTotal");
		if(lpMatrix) lpMatrix->Data=mmTotalCache.Matrix();
  }

}

cShaderProgram *cRenderObject::Shader()
{
  return mpShader;

}

vRenderNode *cRenderObject::Renderer()
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

void cRenderObject::RenderToPainter()
{
if(Shader())
{
 UpdateMatrix();
 mpPainterData->SetObject(this);
 SetPainterVariables();
 mpPainterData->RenderAgain();
}

}




void cRenderObject::Transparency(bool lbTrans){mbAlpha=lbTrans;}
bool cRenderObject::Transparency(){return mbAlpha;}

void cRenderObject::SetPainterVariables()
{
	//mpPainterData->SetTexture(mpTextures);
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


   void cRenderObject::Lighting(bool lbLighting){mbLighting=lbLighting;};

   bool cRenderObject::Lighting(){return mbLighting;};




cVariableStore *cRenderObject::Variables()
{
 if(!mpVariables) mpVariables=new cVariableStore(mpShader);
 return mpVariables;
}

void cRenderObject::SetShaderVariables()
{
 if(mpVariables)
 {
  mpShader->Use();
  mpVariables->WriteUniforms();
  mpVariables->WriteAttributes();
 }

}


