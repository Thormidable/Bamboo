#include "../../WTBamboo.h"

void cFloatUniformStore::ClearData()
{
 if(mbGenerated) delete []mpData;
 mpData=0;
}

void cFloatUniformStore::DataPointer(void *lpData)
{
 ClearData();
 mbGenerated=false;
 mpData=(GLfloat*)lpData;
}

void cIntUniformStore::ClearData()
{
 if(mbGenerated) delete []mpData;
 mpData=0;
}


void cIntUniformStore::DataPointer(void *lpData)
{
 ClearData();
 mbGenerated=false;
 mpData=(GLint*)lpData;
}

void cBooleanUniformStore::ClearData()
{
 if(mbGenerated) delete []mpData;
 mpData=0;
}


void cBooleanUniformStore::DataPointer(void *lpData)
{
 ClearData();
 mbGenerated=false;
 mpData=(GLint*)lpData;
}

cUserVariable::cUserVariable()
{
 mbGenerated=0;
 miID=0;
}

void cUserVariable::SetID(int32 liID)
{
 miID=liID;
 mbGenerated=false;
}

cAttributeStore::cAttributeStore()
{
 glGenBuffers(1, &miBuffer);
}

cFloatAttributeStore::cFloatAttributeStore()
{
 mpData=0;
}

void cFloatAttributeStore::DataPointer(void *lpData,uint32 liElements)
{
 mpData=(GLfloat*)lpData;
 miElements=liElements;
 mbGenerated=true;
}

void cIntAttributeStore::DataPointer(void *lpData,uint32 liElements)
{
 mpData=(GLint*)lpData;
 miElements=liElements;
 mbGenerated=true;
}

void cBooleanAttributeStore::DataPointer(void *lpData,uint32 liElements)
{
 mpData=(GLint*)lpData;
 miElements=liElements;
 mbGenerated=true;
}


void cFloatAttributeStore::DataValue(void *lpData,uint32 liElements)
{
		mbGenerated=false;
 		mpData=(GLfloat*)lpData;
		miElements=liElements;
		this->Buffer();
}

cIntAttributeStore::cIntAttributeStore()
{
 mpData=0;
}

void cIntAttributeStore::DataValue(void *lpData,uint32 liElements)
{
		mbGenerated=false;
 		mpData=(GLint*)lpData;
		miElements=liElements;
		this->Buffer();
}

cBooleanAttributeStore::cBooleanAttributeStore()
{
 mpData=0;
}

void cBooleanAttributeStore::DataValue(void *lpData,uint32 liElements)
{
		mbGenerated=false;
 		mpData=(GLint*)lpData;
		miElements=liElements;
		this->Buffer();
}

uint32 cVariableStore::Variables()
{
 return miVariables;
}

cVariableStore::cVariableStore(cShaderProgram *lpProg)
{
  mpVariables=0;
  miVariables=0;
  Link(lpProg);
}


void cVariableStore::ClearLink()
{

 uint32 liCount;
 if(mpVariables)
 {
 	for(liCount=0;liCount<miVariables;++liCount)
 	{
  		delete mpVariables[liCount];
 	}
	delete []mpVariables;
	mpVariables=0;
 }

}

cVariableStore::~cVariableStore()
{
	ClearLink();
}

void cVariableStore::WriteVariables()
{
 if(mpVariables)
 {
  uint32 liCount;
  for(liCount=0;liCount<miVariables;++liCount)
  {
#warning comment Check this is safe.
	 //if(mpVariables[liCount])
		 mpVariables[liCount]->Write();
  }
 }
}

cUserVariable *cVariableStore::GetVariable(uint32 liVar)
{
	return mpVariables[liVar];

};

void cVariableStore::GenerateVariableSet(cShaderVariableSet *lpSet)
{
ClearLink();

 miVariables=lpSet->miVariables;
 mpVariables=new cUserVariable*[miVariables];
 cShaderVariable *lcPos;
 uint32 liCount;
 uint32 liOther=0;
 for(liCount=0;liCount<miVariables;++liCount)
 {
	 lcPos=&(lpSet->mpVariables[liCount]);
	if(lcPos->Uniform())
	{
		switch(lcPos->Type())
		{
			case IMF_SHADERVAR_FLOAT:
			{
		 		mpVariables[liOther]=new cUniformVector1;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_VEC2:
			{
		 		mpVariables[liOther]=new cUniformVector2;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_VEC3:
			{
		 		mpVariables[liOther]=new cUniformVector3;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_VEC4:
			{
		 		mpVariables[liOther]=new cUniformVector4;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
            case IMF_SHADERVAR_INT:
			{
		 		mpVariables[liOther]=new cUniformIntVector1;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_IVEC2:
			{
		 		mpVariables[liOther]=new cUniformIntVector2;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_IVEC3:
			{
		 		mpVariables[liOther]=new cUniformIntVector3;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_IVEC4:
			{
		 		mpVariables[liOther]=new cUniformIntVector4;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
            case IMF_SHADERVAR_BOOL:
			{
		 		mpVariables[liOther]=new cUniformBooleanVector1;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_BVEC2:
			{
		 		mpVariables[liOther]=new cUniformBooleanVector2;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_BVEC3:
			{
		 		mpVariables[liOther]=new cUniformBooleanVector3;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_BVEC4:
			{
		 		mpVariables[liOther]=new cUniformBooleanVector4;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_MATRIX2:
			{
		 		mpVariables[liOther]=new cUniformMatrix2;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
            case IMF_SHADERVAR_MATRIX3:
			{
		 		mpVariables[liOther]=new cUniformMatrix3;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_MATRIX4:
			{
		 		mpVariables[liOther]=new cUniformMatrix4;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			default :
			{
				mpVariables[liOther]=new cVoidVariable;
				mpVariables[liOther++]->SetID(lcPos->ID());
			}
		};
	}
	else
	{
		switch(lcPos->Type())
		{
			case IMF_SHADERVAR_FLOAT:
			{
		 		mpVariables[liOther]=new cAttributeArray1;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_VEC2:
			{
		 		mpVariables[liOther]=new cAttributeArray2;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_VEC3:
			{
		 		mpVariables[liOther]=new cAttributeArray3;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_VEC4:
			{
		 		mpVariables[liOther]=new cAttributeArray4;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
            case IMF_SHADERVAR_INT:
			{
		 		mpVariables[liOther]=new cAttributeIntArray1;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_IVEC2:
			{
		 		mpVariables[liOther]=new cAttributeIntArray2;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_IVEC3:
			{
		 		mpVariables[liOther]=new cAttributeIntArray3;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_IVEC4:
			{
		 		mpVariables[liOther]=new cAttributeIntArray4;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
            case IMF_SHADERVAR_BOOL:
			{
		 		mpVariables[liOther]=new cAttributeBooleanArray1;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_BVEC2:
			{
		 		mpVariables[liOther]=new cAttributeBooleanArray2;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_BVEC3:
			{
		 		mpVariables[liOther]=new cAttributeBooleanArray3;
   mpVariables[liOther++]->SetID(lcPos->ID()); }break;
			case IMF_SHADERVAR_BVEC4:
			{
		 		mpVariables[liOther]=new cAttributeBooleanArray4;
				mpVariables[liOther++]->SetID(lcPos->ID()); } break;
			default :
			{
				mpVariables[liOther]=new cVoidVariable;
				mpVariables[liOther++]->SetID(lcPos->ID());
			}
		};

	}

 }
 miVariables=liOther;
}

void cVariableStore::Link(cShaderProgram *lpProg)
{
	GenerateVariableSet(lpProg->ShaderVariableSet());
};
cFloatUniformStore::cFloatUniformStore()
{
    mpData=0;
}
cIntUniformStore::cIntUniformStore()
{
    mpData=0;
}
cBooleanUniformStore::cBooleanUniformStore()
{
    mpData=0;
}

cFloatUniformStore::~cFloatUniformStore()
{
    ClearData();
}
cIntUniformStore::~cIntUniformStore()
{
    ClearData();
}
cBooleanUniformStore::~cBooleanUniformStore()
{
    ClearData();
}

void cUniformVector1::ClearData()
{
    if(mbGenerated) delete mpData; mpData=0;
}
void cUniformIntVector1::ClearData()
{
    if(mbGenerated) delete mpData; mpData=0;
}
void cUniformBooleanVector1::ClearData()
{
    if(mbGenerated) delete mpData; mpData=0;
}
void cUniformVector1::Write()
{
	if(mpData) glUniform1f(miID,*mpData);
}
void cUniformVector2::Write()
{
	if(mpData) glUniform2fv(miID,1,mpData);
}
void cUniformVector3::Write()
{
	if(mpData) glUniform3fv(miID,1,mpData);
}
void cUniformVector4::Write()
{
	if(mpData) glUniform4fv(miID,1,mpData);
}
void cUniformIntVector1::Write()
{
	if(mpData) glUniform1i(miID,*mpData);
}
void cUniformIntVector2::Write()
{
	if(mpData) glUniform2iv(miID,1,mpData);
}
void cUniformIntVector3::Write()
{
	if(mpData) glUniform3iv(miID,1,mpData);
}
void cUniformIntVector4::Write()
{
	if(mpData) glUniform4iv(miID,1,mpData);
}

void cUniformBooleanVector1::Write()
{
	if(mpData) glUniform1i(miID,*mpData);
}
void cUniformBooleanVector2::Write()
{
	if(mpData) glUniform2iv(miID,1,mpData);
}
void cUniformBooleanVector3::Write()
{
	if(mpData) glUniform3iv(miID,1,mpData);
}
void cUniformBooleanVector4::Write()
{
	if(mpData) glUniform4iv(miID,1,mpData);
}

void cUniformMatrix4::Write()
{
	if(mpData) glUniformMatrix4fv(miID,1,0,mpData);
}

void cUniformMatrix3::Write()
{
	if(mpData) glUniformMatrix3fv(miID,1,0,mpData);
}

void cUniformMatrix2::Write()
{
	if(mpData) glUniformMatrix2fv(miID,1,0,mpData);
}



















void cUniformVector1::DataValue(void *lpData)
{
	if(!mbGenerated || !mpData) mpData=new GLfloat;
	memcpy(mpData,lpData,sizeof(GLfloat));
	mbGenerated=true;
}
void cUniformVector2::DataValue(void *lpData)
{

	if(!mbGenerated || !mpData) mpData=new GLfloat[2];
	memcpy(mpData,lpData,sizeof(GLfloat)*2);
	mbGenerated=true;
}
void cUniformVector3::DataValue(void *lpData)
{
	if(!mbGenerated || !mpData) mpData=new GLfloat[3];
	memcpy(mpData,lpData,sizeof(GLfloat)*3);
	mbGenerated=true;
}
void cUniformVector4::DataValue(void *lpData)
{
	if(!mbGenerated || !mpData) mpData=new GLfloat[4];
	memcpy(mpData,lpData,sizeof(GLfloat)*4);
	mbGenerated=true;
}
void cUniformIntVector1::DataValue(void *lpData)
{
	if(!mbGenerated || !mpData) mpData=new GLint;
	memcpy(mpData,lpData,sizeof(GLint));
	mbGenerated=true;
}
void cUniformIntVector2::DataValue(void *lpData)
{
	if(!mbGenerated || !mpData) mpData=new GLint[2];
	memcpy(mpData,lpData,sizeof(GLint)*2);
	mbGenerated=true;
}
void cUniformIntVector3::DataValue(void *lpData)
{
	if(!mbGenerated || !mpData) mpData=new GLint[3];
	memcpy(mpData,lpData,sizeof(GLint)*3);
	mbGenerated=true;
}
void cUniformIntVector4::DataValue(void *lpData)
{
	if(!mbGenerated || !mpData) mpData=new GLint[4];
	memcpy(mpData,lpData,sizeof(GLint)*4);
	mbGenerated=true;
}

void cUniformBooleanVector1::DataValue(void *lpData)
{
		if(!mbGenerated || !mpData) mpData=new GLint;
	memcpy(mpData,lpData,sizeof(GLint));
	mbGenerated=true;
}
void cUniformBooleanVector2::DataValue(void *lpData)
{
		if(!mbGenerated || !mpData) mpData=new GLint[2];
	memcpy(mpData,lpData,sizeof(GLint)*2);
	mbGenerated=true;
}
void cUniformBooleanVector3::DataValue(void *lpData)
{
        if(!mbGenerated || !mpData) mpData=new GLint[3];
	memcpy(mpData,lpData,sizeof(GLint)*3);
	mbGenerated=true;
}
void cUniformBooleanVector4::DataValue(void *lpData)
{
		if(!mbGenerated || !mpData) mpData=new GLint[4];
	memcpy(mpData,lpData,sizeof(GLint)*4);
	mbGenerated=true;
}

void cUniformMatrix4::DataValue(void *lpData)
{
    if(!mbGenerated || !mpData) mpData=new GLfloat[16];
	memcpy(mpData,lpData,sizeof(GLfloat)*16);
	mbGenerated=true;
}

void cUniformMatrix3::DataValue(void *lpData)
{
    if(!mbGenerated || !mpData) mpData=new GLfloat[9];
	memcpy(mpData,lpData,sizeof(GLfloat)*9);
	mbGenerated=true;
}

void cUniformMatrix2::DataValue(void *lpData)
{
	    if(!mbGenerated || !mpData) mpData=new GLfloat[4];
	memcpy(mpData,lpData,sizeof(GLfloat)*4);
	mbGenerated=true;
}















void cAttributeStore::Write()
{
#warning comment Have removed if(miID) before glEnableVertexAttribArray
	if(mbGenerated) Buffer();
	glEnableVertexAttribArray(miID);
}


void cAttributeArray1::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * miElements , mpData, GL_STATIC_DRAW);
	glVertexAttribPointer(miID,1,GL_FLOAT,0,0,0);
}

void cAttributeArray2::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *2* miElements , mpData, GL_STATIC_DRAW);
	glVertexAttribPointer(miID,2,GL_FLOAT,0,0,0);
}

void cAttributeArray3::Buffer()
{
		glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) *miElements *3, mpData, GL_STATIC_DRAW);
		glVertexAttribPointer(miID,3,GL_FLOAT,0,0,0);
}

void cAttributeArray4::Buffer()
{
		glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * miElements *4, mpData, GL_STATIC_DRAW);
		glVertexAttribPointer(miID,4,GL_FLOAT,0,0,0);
}

void cAttributeIntArray1::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * miElements , mpData, GL_STATIC_DRAW);
	glVertexAttribPointer(miID,1,GL_INT,0,0,0);
}

void cAttributeIntArray2::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) *2* miElements , mpData, GL_STATIC_DRAW);
	glVertexAttribPointer(miID,2,GL_INT,0,0,0);
}

void cAttributeIntArray3::Buffer()
{
		glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) *miElements *3, mpData, GL_STATIC_DRAW);
		glVertexAttribPointer(miID,3,GL_INT,0,0,0);
}

void cAttributeIntArray4::Buffer()
{
		glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * miElements *4, mpData, GL_STATIC_DRAW);
		glVertexAttribPointer(miID,4,GL_INT,0,0,0);
}

void cAttributeBooleanArray1::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bool) * miElements , mpData, GL_STATIC_DRAW);
	glVertexAttribPointer(miID,1,GL_BOOL,0,0,0);
}

void cAttributeBooleanArray2::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bool) *2* miElements , mpData, GL_STATIC_DRAW);
	glVertexAttribPointer(miID,2,GL_BOOL,0,0,0);
}

void cAttributeBooleanArray3::Buffer()
{
		glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(bool) *miElements *3, mpData, GL_STATIC_DRAW);
		glVertexAttribPointer(miID,3,GL_BOOL,0,0,0);
}

void cAttributeBooleanArray4::Buffer()
{
		glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(bool) * miElements *4, mpData, GL_STATIC_DRAW);
		glVertexAttribPointer(miID,4,GL_BOOL,0,0,0);
}
