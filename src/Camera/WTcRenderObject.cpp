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
 mpRenderer=cCamera::Instance()->RenderList();
 mcOwnerNode=mpRenderer->Add(this);

Initialise();
}

cRenderObject::cRenderObject(vRenderNode *lpNode)
{
  mpRenderer=lpNode;
  mcOwnerNode=lpNode->Add(this);
Initialise();
}


cRenderObject::cRenderObject(bool lbNoTextures): cTextureStack(lbNoTextures)
{
	 mpRenderer=cCamera::Instance()->RenderList();
 mcOwnerNode=mpRenderer->Add(this);

Initialise();
}

cRenderObject::cRenderObject(vRenderNode *lpNode,bool lbNoTextures) : cTextureStack(lbNoTextures)
{
  mpRenderer=lpNode;
  mcOwnerNode=lpNode->Add(this);
Initialise();

}
void cRenderObject::AddTexture(string lsTextureSlot,cTexture *lpTexture)
{
 if(mpShader)
 {
 	uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lsTextureSlot);
 	if(liPos) AddTexture(liPos-1,lpTexture);
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
		uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lsTextureSlot);
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

void cRenderObject::Stop()
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

void cRenderObject::KillAll()
{
//    mpRenderer->Remove(mcOwnerNode);
//delete this;
};



void cRenderObject::OnSleep()
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

void cRenderObject::OnWake()
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
		RecalculateTotalMatrix();

		mpCollisionObject->PostUpdateCache();
	}
	else
	{
		mmCache=_MATRIX_STACK->Current();
		RecalculateTotalMatrix();
	}

};

void cRenderObject::CalculateMatrices()
{
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
}

}




void cRenderObject::Transparency(bool lbTrans){mbAlpha=lbTrans;}
bool cRenderObject::Transparency(){return mbAlpha;}

void cRenderObject::SetPainterVariables()
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
