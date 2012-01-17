#include "../../WTBamboo.h"

uint32 cShaderVariables::GetUniformPosition(string Name)
{
 uint32 liCount;
 for(liCount=0;liCount<miUniforms;++liCount)
 {
	if(mpUniformText[liCount]==Name) return liCount+1;
 }
 return 0;

}

uint32 cShaderVariables::GetAttributePosition(string Name)
{
uint32 liCount;
 for(liCount=0;liCount<miAttributes;++liCount)
 {
	if(mpAttributeText[liCount]==Name) return liCount+1;

}
 return 0;

}

void cShaderVariables::GetUniformLocations(uint32 liProgramID,cShader **lpShader,uint32 liShaders)
{
	delete []mpUniforms;
	delete []mpUniformText;

	uint32 liCount;
	uint32 liLoop;
	uint32 liUni;
	uint32 liOther;
	miUniforms=0;
	for(liCount=0;liCount<liShaders;++liCount)
	{
		miUniforms+=lpShader[liCount]->miUniforms;
	}

	mpUniforms=new int32[miUniforms];
	mpUniformText=new string[miUniforms];
 char Variable[256];
 char *Text;
 liOther=0;
 for(liLoop=0;liLoop<liShaders;++liLoop)
 {
	 Text=(char*)lpShader[liLoop]->mpShaderText[0];
	 liUni=lpShader[liLoop]->miUniforms;
 	for(liCount=0;liCount<liUni;++liCount)
 	{
  		LineCopy(Variable,&Text[lpShader[liLoop]->mpUniforms[liCount]],"; ,@([");
  		mpUniforms[liOther]=glGetUniformLocation(liProgramID,Variable);
		mpUniformText[liOther]=Variable;
  		if(mpUniforms[liOther]==-1) {trace("Error Getting Shader Variable " << Variable);}
  		else printf("Program ID %lu : Variable ID %li : %s\n",liProgramID,mpUniforms[liOther],Variable);
		++liOther;
 	}
 }
}

void cShaderVariables::GetAttributeLocations(uint32 liProgramID,cShader **lpShader,uint32 liShaders)
{

	delete []mpAttributes;
	delete []mpAttributeText;
	uint32 liCount;
	uint32 liLoop;
	uint32 liUni;
	uint32 liOther;
	miAttributes=0;
	for(liCount=0;liCount<liShaders;++liCount)
	{
		miAttributes+=lpShader[liCount]->miAttributes;
	}

	mpAttributes=new int32[miAttributes];
	mpAttributeText=new string[miAttributes];
 char Variable[256];

char *Text;
 liOther=0;
 for(liLoop=0;liLoop<liShaders;++liLoop)
 {
	 Text=(char*)lpShader[liLoop]->mpShaderText[0];
	 liUni=lpShader[liLoop]->miAttributes;
 	for(liCount=0;liCount<liUni;++liCount)
 	{
  		LineCopy(Variable,&Text[lpShader[liLoop]->mpAttributes[liCount]],"; ,@([");
  		mpAttributes[liOther]=glGetAttribLocation(liProgramID,Variable);
		mpAttributeText[liOther]=Variable;
  		if(mpAttributes[liOther]==-1) {trace("Error Getting Shader Variable " << Variable);}
  		else printf("Program ID %lu : Variable ID %li : %s\n",liProgramID,mpAttributes[liOther],Variable);
		++liOther;
 	}
 }
	/*
	miAttributes=lpShader->miAttributes;
	mpAttributes=new int32[miAttributes];
char Variable[256];
char *Text=(char*)lpShader->mpShaderText[0];
 uint32 liCount;
 for(liCount=0;liCount<miAttributes;++liCount)
 {
  LineCopy(Variable,&Text[lpShader->mpAttributes[liCount]],"; ,@([");
  mpAttributes[liCount]=glGetAttribLocation(liProgramID,Variable);
  if(mpAttributes[liCount]==-1) {trace("Error Getting Shader Variable " << Variable);}
  else
  {
	  printf("Program ID %u : Variable ID %i : %s\n",liProgramID,liCount,Variable);
	  glEnableVertexAttribArray(mpAttributes[liCount]);
  }
 }
 */
}


void cShaderVariables::SetUniform(uint32 liUniform,float Value0){if(liUniform<miUniforms) glUniform1f(mpUniforms[liUniform],Value0);}
void cShaderVariables::SetUniform(uint32 liUniform,float Value0,float Value1){if(liUniform<miUniforms) glUniform2f(mpUniforms[liUniform],Value0,Value1);}
void cShaderVariables::SetUniform(uint32 liUniform,float Value0,float Value1,float Value2){if(liUniform<miUniforms) glUniform3f(mpUniforms[liUniform],Value0,Value1,Value2);}
void cShaderVariables::SetUniform(uint32 liUniform,float Value0,float Value1,float Value2,float Value3){if(liUniform<miUniforms) glUniform4f(mpUniforms[liUniform],Value0,Value1,Value2,Value3);}

void cShaderVariables::SetUniform1(uint32 liUniform,float *Value,uint16 liItems){if(liUniform<miUniforms) glUniform1fv(mpUniforms[liUniform],liItems,Value);}
void cShaderVariables::SetUniform2(uint32 liUniform,float *Value,uint16 liItems){if(liUniform<miUniforms) glUniform2fv(mpUniforms[liUniform],liItems,Value);}
void cShaderVariables::SetUniform3(uint32 liUniform,float *Value,uint16 liItems){if(liUniform<miUniforms) glUniform3fv(mpUniforms[liUniform],liItems,Value);}
void cShaderVariables::SetUniform4(uint32 liUniform,float *Value,uint16 liItems){if(liUniform<miUniforms) glUniform4fv(mpUniforms[liUniform],liItems,Value);}

void cShaderVariables::SetMatrix2(uint32 liUniform,float *Value){if(liUniform<miUniforms) glUniformMatrix2fv(mpUniforms[liUniform],1,0,Value);}
void cShaderVariables::SetMatrix3(uint32 liUniform,float *Value){if(liUniform<miUniforms) glUniformMatrix3fv(mpUniforms[liUniform],1,0,Value);}
void cShaderVariables::SetMatrix4(uint32 liUniform,float *Value){if(liUniform<miUniforms) glUniformMatrix4fv(mpUniforms[liUniform],1,0,Value);}
void cShaderVariables::SetMatrix(uint32 liUniform,cMatrix4 *lpMatrix,uint32 liMatricesInArray){if(liUniform<miUniforms) glUniformMatrix4fv(mpUniforms[liUniform],liMatricesInArray,0,lpMatrix->Matrix());}

/*
void cShaderVariables::SetAttribute(uint32 liAttribute,float Value){if(liAttribute<miAttributes) glVertexAttrib1f(mpAttributes[liAttribute],Value);}
void cShaderVariables::SetAttribute(uint32 liAttribute,float Value,float Value1){if(liAttribute<miAttributes) glVertexAttrib2f(mpAttributes[liAttribute],Value,Value1);}
void cShaderVariables::SetAttribute(uint32 liAttribute,float Value,float Value1,float Value2){if(liAttribute<miAttributes) glVertexAttrib3f(mpAttributes[liAttribute],Value,Value1,Value2);}
void cShaderVariables::SetAttribute(uint32 liAttribute,float Value,float Value1,float Value2,float Value3){if(liAttribute<miAttributes) glVertexAttrib4f(mpAttributes[liAttribute],Value,Value1,Value2,Value3);}

void cShaderVariables::SetAttribute1(uint32 liAttribute,float *Value){if(liAttribute<miAttributes) glVertexAttrib1fv(mpAttributes[liAttribute],Value);}
void cShaderVariables::SetAttribute2(uint32 liAttribute,float *Value){if(liAttribute<miAttributes) glVertexAttrib2fv(mpAttributes[liAttribute],Value);}
void cShaderVariables::SetAttribute3(uint32 liAttribute,float *Value){if(liAttribute<miAttributes) glVertexAttrib3fv(mpAttributes[liAttribute],Value);}
void cShaderVariables::SetAttribute4(uint32 liAttribute,float *Value){if(liAttribute<miAttributes) glVertexAttrib4fv(mpAttributes[liAttribute],Value);}
*/





void cShaderVariables::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,float *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_FLOAT,0,liStride,lpData);}
void cShaderVariables::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,uint32 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_UNSIGNED_INT,0,liStride,lpData);}
void cShaderVariables::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,uint16 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_UNSIGNED_SHORT,0,liStride,lpData);}
void cShaderVariables::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,uint8 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_UNSIGNED_BYTE,0,liStride,lpData);}
void cShaderVariables::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,int32 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_INT,0,liStride,lpData);}
void cShaderVariables::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,int16 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_SHORT,0,liStride,lpData);}
void cShaderVariables::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,int8 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_BYTE,0,liStride,lpData);}

cShaderVariables::cShaderVariables()
{
 miUniforms=miAttributes=0;
 mpUniforms=mpAttributes=0;
 mpUniformText=mpAttributeText=0;
}

cShaderVariables::~cShaderVariables()
{
delete []mpUniforms; mpUniforms=0;
delete []mpAttributes; mpAttributes=0;
}

int32 cShaderVariables::GetUniformID(uint32 liVariableNumber){if(liVariableNumber<miUniforms) return mpUniforms[liVariableNumber]; return -1;};
int32 cShaderVariables::GetAttributeID(uint32 liVariableNumber){if(liVariableNumber<miAttributes) return mpAttributes[liVariableNumber]; return -1;};



void cShaderVariables::BindAttributes(uint32 liProgramID)
{
if(mpAttributes)
 {
 uint32 liCount;
 for(liCount=0;liCount<miAttributes;++liCount)
 {
		glBindAttribLocation(liProgramID,mpAttributes[liCount],mpAttributeText[liCount].c_str());
 }

 }
}

