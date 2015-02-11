
#include "../WTBamboo.h"

cRenderObject::cRenderObject(cCamera *lpCamera)
{
 mpCamera=lpCamera;
 mpRenderer=lpCamera->RenderList();
 mcOwnerNode=mpRenderer->Add(this);

Initialise();

};

cRenderObject::cRenderObject(cCamera *lpCamera,bool lbNoTextures)  : cTextureStack(lbNoTextures)
{
 mpCamera=lpCamera;
 mpRenderer=lpCamera->RenderList();
 mcOwnerNode=mpRenderer->Add(this);
Initialise();

};

vRenderObject::vRenderObject()
{
 mpCollisionObject=0;
 mpProcess=0;
 mmTotalCache.Identity();
}

cRenderObject::~cRenderObject()
{
    mbAlive=false;
    mbAwake=false;
    if(mpCollisionObject)
	{
		_KILL(mpCollisionObject);
		mpCollisionObject=0;
	}

    if(mpPainterData)
    {
		mpRenderer->Camera()->Painter()->Remove(mpPainterData);
	delete mpPainterData;
	mpPainterData=0;
    }

	delete mpVariables;
	mpVariables=0;

}

float vRenderObject::GetSize(){return 0.0f;};
double vRenderObject::GetSizeSq(){return 0.0f;};

void vRenderObject::LinkCollisionObject(cCollisionObject *lpObj)
{
// printf("This : %p, Linked : %p\n",this,lpObj);
  mpCollisionObject=lpObj;

};

cRenderObject::cRenderObject()
{
 mpCamera=cCamera::Instance();
 mpRenderer=cCamera::Instance()->RenderList();
 mcOwnerNode=mpRenderer->Add(this);

Initialise();
}

cRenderObject::cRenderObject(vRenderNode *lpNode)
{
  mpCamera=lpNode->Camera();
  mpRenderer=lpNode;
  mcOwnerNode=lpNode->Add(this);
Initialise();
}


cRenderObject::cRenderObject(bool lbNoTextures): cTextureStack(lbNoTextures)
{
 mpCamera=cCamera::Instance();
	 mpRenderer=cCamera::Instance()->RenderList();
 mcOwnerNode=mpRenderer->Add(this);

Initialise();
}

cRenderObject::cRenderObject(vRenderNode *lpNode,bool lbNoTextures) : cTextureStack(lbNoTextures)
{
  mpCamera=lpNode->Camera();
  mpRenderer=lpNode;
  mcOwnerNode=lpNode->Add(this);
Initialise();

}
void cRenderObject::AddTexture(string lsTextureSlot,cTexture *lpTexture)
{
 if(mpShader)
 {
 	uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lsTextureSlot);
 	if(liPos)
 	{
    AddTexture(mpShader->ShaderVariableSet()->GetID(liPos-1),lpTexture);
 	//if(liPos) AddTexture(liPos-1,lpTexture);
 	//SetVariablePointer(lsTextureSlot.c_str(),&(mpTextures[liPos-1].miUniform));
 	}
  }
}

void cRenderObject::RemoveTexture(string lsTextureSlot)
{
  	if(mpShader)
	{
		uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lsTextureSlot);
		if(liPos) RemoveTextureByUniform(liPos-1);
	}
}

void cRenderObject::RemoveTexture(uint8 liSlot)
{
	RemoveTextureBySlot(liSlot);
}

void cRenderObject::AddTexture(cTexture *lpTexture)
{

 int32 liSlot=ReturnFreeSlot();

 if(liSlot>=0 && mpShader)
 {
 		string lsTextureSlot="Texture";
		std::stringstream out;
		out << liSlot;
		lsTextureSlot.append(out.str());
		AddTexture(lsTextureSlot,lpTexture);
 }
}



void cRenderObject::Initialise()
{
  mbAwake=true;
  mbAlive=true;
mpVariables=0;
		mpShader=0;
	mpPainterData= new cRenderPointer();
	mpRenderer->Camera()->Painter()->Add(mpPainterData);
	mpPainterData->SetObject(this);

    mbNormalArray=false;
    mbUVArray=false;

 Transparency(0);
 Lighting(1);
}

void cRenderObject::Delete()
{

}

void cRenderObject::AdditionalRenderFunctions()
{
// UpdateCache();
// SetShaderVariables();

}

void cRenderObject::Stop()
{
	if(mpCollisionObject)
	{
		_KILL(mpCollisionObject);
		mpCollisionObject=0;
	}

    if(mpPainterData)
    {
    mpRenderer->Camera()->Painter()->Remove(mpPainterData);
	delete mpPainterData;
	mpPainterData=0;
    }

	delete mpVariables;
	mpVariables=0;

}




void cRenderObject::KillAll()
{
	_KILL_THIS();
//    mpRenderer->Remove(mcOwnerNode);
//delete this;
};



void cRenderObject::OnSleep()
{
    if(mpPainterData)
    {
        mpRenderer->Camera()->Painter()->Remove(mpPainterData);
        delete mpPainterData;
        mpPainterData=0;
    }

if(mpCollisionObject)
{
    _SLEEP(mpCollisionObject);
}


}

void cRenderObject::OnWake()
{

	mpPainterData=new cRenderPointer;
	mpRenderer->Camera()->Painter()->Add(mpPainterData);
	mpPainterData->SetObject(this);

if(mpCollisionObject)
{
    _WAKE(mpCollisionObject);
}

}

void vRenderObject::UpdateCache()
{
	//printf("This : %p, mpCollisionObject : %p\n",this,mpCollisionObject);
	if(mpCollisionObject)
	{
		//mpCollisionObject->PreUpdateCache();

		mmCache=_MATRIX_STACK->Current();
		mmTotalCache=_COMBINED_MATRIX;
        mmTotalCache.Multiply(mmCache);

		mpCollisionObject->PostUpdateCache();
	}
	else
	{
		mmCache=_MATRIX_STACK->Current();
		mmTotalCache=_COMBINED_MATRIX;
        mmTotalCache.Multiply(mmCache);
	}

};

void cRenderObject::CalculateMatrices()
{
    UpdateMatrix();
	UpdateCache();
};

void cRenderObject::RecalculateTotalMatrix()
{
	mmTotalCache=_COMBINED_MATRIX;
	mmTotalCache.Multiply(mmCache);
};

void cRenderObject::Shader(string lcString)
{
	Shader(_GET_SHADER_FILE(lcString.c_str()));
}

void cRenderObject::Shader(cShaderProgram *lpShader)
{
 if(!lpShader && mpShader) ClearTextureStack();


  mpShader=lpShader;

  if(mpShader)
  {
	   if(!mpVariables) mpVariables=new cVariableStore(lpShader);
  	   else
       {
  			if(mpShader) mpVariables->Link(mpShader);
  			else mpVariables->ClearLink();
  		}

	mpShader->Use();
	SetVariablePointer("mmGlobal",mmCache.Matrix());
    SetVariablePointer("mmTotal",mmTotalCache.Matrix());
  }

}

cShaderProgram *cRenderObject::Shader()
{
  return mpShader;

}


float *vRenderObject::GetPos()
{
  return Position();

};

float *vRenderObject::GetCachedGlobalMatrix()
{
  //return mmCache.Position();
  return mmCache.Matrix();

};

void cRenderObject::RenderToPainter()
{
if(Shader())
{
 UpdateMatrix();
 mpPainterData->SetObject(this);
 SetPainterVariables();
}

}




void cRenderObject::Transparency(uint8 lbTrans){miAlpha=lbTrans;}
uint8 cRenderObject::Transparency(){return miAlpha;}

void cRenderObject::SetPainterVariables()
{
    mpPainterData->SetAlpha(miAlpha);
    mpPainterData->SetShader(mpShader);
}

vRenderNode* vRenderObject::Renderer(){return mpRenderer;};

cMatrix4 *vRenderObject::CalculateGlobalMatrix()
{

    if(Renderer())
    {
	 cMatrix4 *lpMat=Renderer()->CalculateGlobalMatrix();
	 if(lpMat)
	 {
     	mmCache=(*lpMat)*ThisMatrix();
     	mmTotalCache=_COMBINED_MATRIX;
		mmTotalCache.Multiply(mmCache);
     	return &mmCache;
	 }
	 return 0;
    }
    else
    {
        mmCache=ThisMatrix();
        return &mmCache;
    }
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

  mpVariables->WriteVariables();
 }

}


void cRenderObject::SetAttribute(string lcString,void *Data,uint32 liElements)
{
	if(mpShader)
	{
		uint32 liPos=mpShader->ShaderVariableSet()->GetAttributePosition(lcString);
		if(liPos) mpVariables->GetVariable(liPos-1)->DataValue(Data,liElements);
	}
};

void cRenderObject::SetVariable(string lcString,void *Data,uint32 liElements)
{
	SetAttribute(lcString,Data,liElements);
};

void cRenderObject::SetUniform(string lcString,void *Data)
{
	if(mpShader)
	{
		uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lcString);
		if(liPos) mpVariables->GetVariable(liPos-1)->DataValue(Data);
	}
};

void cRenderObject::SetVariable(string lcString,void *Data)
{
	SetUniform(lcString,Data);
};

void cRenderObject::SetUniformPointer(string lcString,void *Data)
{
	if(mpShader)
	{
		uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lcString);
		if(liPos) mpVariables->GetVariable(liPos-1)->DataPointer(Data);
	}
};
void cRenderObject::SetAttributePointer(string lcString,void *Data,uint32 liElements)
{
	if(mpShader)
	{
		uint32 liPos=mpShader->ShaderVariableSet()->GetAttributePosition(lcString);
		if(liPos) mpVariables->GetVariable(liPos-1)->DataPointer(Data,liElements);
	}
};
void cRenderObject::SetVariablePointer(string lcString,void *Data)
{
	SetUniformPointer(lcString,Data);
};
void cRenderObject::SetVariablePointer(string lcString,void *Data,uint32 liElements)
{
	SetAttributePointer(lcString,Data,liElements);
};

void cRenderObject::AddTexture(string lcTextureReference)
{
	AddTexture(_GET_TEXTURE_FILE(lcTextureReference.c_str()));
};
void cRenderObject::AddTexture(string lsTextureSlot,string lcTextureReference)
{
	AddTexture(lsTextureSlot,_GET_TEXTURE_FILE(lcTextureReference.c_str()));
};

bool cRenderObject::NormalArray()
{
    return mbNormalArray;
};

bool cRenderObject::UVArray()
{
    return mbUVArray;
};

#if WT_FULL_VERSION_BAMBOO

c3DVf vRenderObject::GetScreenPosition()
{
	 c3DVf lfReturn;
 //if(mpCamera)
// {
 float lfPos[4];

 lfReturn.X(1.0f/mmTotalCache[15]);

 lfPos[0]=mmTotalCache[12]*lfReturn.X();
 lfPos[1]=mmTotalCache[13]*lfReturn.X();
 lfPos[2]=mmTotalCache[14];

 lfReturn.X(mpCamera->ViewportX() + mpCamera->ViewportWidth() * (lfPos[0]+1.0f)*0.5f);
 lfReturn.Y(mpCamera->ViewportY() + mpCamera->ViewportHeight() *(lfPos[1]+1.0f)*0.5f);
 lfReturn.Z(mpCamera->Near() + (mpCamera->Far()-mpCamera->Near())*lfPos[2]);
// }
 return lfReturn;
}

float vRenderObject::GetScreenX()
{
 return mpCamera->ViewportX() + mpCamera->ViewportWidth() * ((mmTotalCache[12]/mmTotalCache[15])+1.0f)*0.5f;
};

float vRenderObject::GetScreenY()
{
 return mpCamera->ViewportY() + mpCamera->ViewportHeight() * ((mmTotalCache[13]/mmTotalCache[15])+1.0f)*0.5f;
};


c3DVf vRenderObject::GetScreenPosition(cViewport *lpView)
{
 c3DVf lfReturn;
 float lfPos[4];

 lfReturn.X(1.0f/mmTotalCache[15]);

 lfPos[0]=mmTotalCache[12]*lfReturn.X();
 lfPos[1]=mmTotalCache[13]*lfReturn.X();
 lfPos[2]=mmTotalCache[14];

 lfReturn.X(lpView->ViewportX() + lpView->ViewportWidth() * (lfPos[0]+1.0f)*0.5f);
 lfReturn.Y(lpView->ViewportY() + lpView->ViewportHeight() *(lfPos[1]+1.0f)*0.5f);
 lfReturn.Z(lpView->Near() + (lpView->Far()-lpView->Near())*(lfPos[2]));
 return lfReturn;
}

float vRenderObject::GetScreenX(cViewport *lpView)
{
 return lpView->ViewportX() + lpView->ViewportWidth() * ((mmTotalCache[12]/mmTotalCache[15])+1.0f)*0.5f;
};

float vRenderObject::GetScreenY(cViewport *lpView)
{
  return lpView->ViewportY() + lpView->ViewportHeight() * ((mmTotalCache[13]/mmTotalCache[15])+1.0f)*0.5f;
};

bool NormalArray();
bool UVArray();

#endif


cCamera *vRenderObject::Camera()
{
    return mpCamera;
}

void vRenderObject::Renderer(vRenderNode *lpNode)
{
 if(mpRenderer) mcOwnerNode=mpRenderer->MoveItem(this,lpNode);

}

cRenderOwner vRenderObject::RenderOwner(){return mcOwnerNode;}


void vRenderObject::RenderOwner(cRenderOwner lcNew)
{
	mcOwnerNode=lcNew;
};

void vRenderObject::Process(cProcess *lpProcess)
{
 mpProcess=lpProcess;
};

cProcess *vRenderObject::Process()
{
 return mpProcess;
};

c3DVf vRenderObject::FindRelativeCoord(c3DVf GlobalPos)
{
    return mmCache.FindPointRelative(GlobalPos);
};

void vRenderObject::TreeProcessUserSignal(SIGNAL lsSignal,void *lpData)
{
 if(mpProcess) mpProcess->UserSignal(lsSignal,lpData);
}
void vRenderObject::TreeProcessSignal(SIGNAL lsSignal)
{
 if(mpProcess) mpProcess->Signal(lsSignal);
}
void vRenderObject::TreeSignal(SIGNAL lsSignal)
{
 Signal(lsSignal);
}
