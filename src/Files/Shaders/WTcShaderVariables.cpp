#include "../../WTBamboo.h"


uint32 cShaderVariableSet::GetVariablePosition(string Name)
{
uint32 liCount;
 for(liCount=0;liCount<miVariables;++liCount)
 {
	if(CompareVariables(mpVariables[liCount].Start(),Name.c_str()," ,;")) return liCount+1;
 }
 return 0;

}

uint32 cShaderVariableSet::GetUniformPosition(string Name)
{
 uint32 liCount;
 for(liCount=0;liCount<miVariables;++liCount)
 {
	if(mpVariables[liCount].Uniform() && CompareVariables(mpVariables[liCount].Start(),Name.c_str()," ,;")) return liCount+1;
 }
 return 0;

}

uint32 cShaderVariableSet::GetAttributePosition(string Name)
{
uint32 liCount;
 for(liCount=0;liCount<miVariables;++liCount)
 {
	if(mpVariables[liCount].Attribute() && CompareVariables(mpVariables[liCount].Start(),Name.c_str()," ,;")) return liCount+1;
 }
 return 0;

}

void cShaderVariableSet::GetVariableLocations(uint32 liProgramID,cShader **lpShader,uint32 liShaders)
{
	delete []mpVariables;

	uint32 liCount;
	uint32 liLoop;
	uint32 liVars;
	uint32 liOther;
	miVariables=0;
	for(liCount=0;liCount<liShaders;++liCount)
	{
		miVariables+=lpShader[liCount]->Variables();
	}
	mpVariables=new cShaderVariable[miVariables];
 liOther=0;
 for(liLoop=0;liLoop<liShaders;++liLoop)
 {
	 liVars=lpShader[liLoop]->Variables();
 	for(liCount=0;liCount<liVars;++liCount)
 	{
		mpVariables[liOther]=lpShader[liLoop]->Variable(liCount);
		if(lpShader[liLoop]->Variable(liCount).Uniform()) mpVariables[liOther].SetID(glGetUniformLocation(liProgramID,mpVariables[liOther].Start()));
		if(lpShader[liLoop]->Variable(liCount).Attribute()) mpVariables[liOther].SetID(glGetAttribLocation(liProgramID,mpVariables[liOther].Start()));
  		if(mpVariables[liOther].ID()==-1)
		{
			trace("Error Getting Shader Variable " << mpVariables[liOther].Start());
		}
  		else
		{
			printf("Program ID %lu : Variable ID %li : %s\n",liProgramID,mpVariables[liOther].ID(),mpVariables[liOther].Start());
			++liOther;
		}
 	}
 }
 miVariables=liOther;
}
/*
void cShaderVariableSet::SetUniform(uint32 liUniform,float Value0){if(liUniform<miUniforms) glUniform1f(mpUniforms[liUniform],Value0);}
void cShaderVariableSet::SetUniform(uint32 liUniform,float Value0,float Value1){if(liUniform<miUniforms) glUniform2f(mpUniforms[liUniform],Value0,Value1);}
void cShaderVariableSet::SetUniform(uint32 liUniform,float Value0,float Value1,float Value2){if(liUniform<miUniforms) glUniform3f(mpUniforms[liUniform],Value0,Value1,Value2);}
void cShaderVariableSet::SetUniform(uint32 liUniform,float Value0,float Value1,float Value2,float Value3){if(liUniform<miUniforms) glUniform4f(mpUniforms[liUniform],Value0,Value1,Value2,Value3);}

void cShaderVariableSet::SetUniform1(uint32 liUniform,float *Value,uint16 liItems){if(liUniform<miUniforms) glUniform1fv(mpUniforms[liUniform],liItems,Value);}
void cShaderVariableSet::SetUniform2(uint32 liUniform,float *Value,uint16 liItems){if(liUniform<miUniforms) glUniform2fv(mpUniforms[liUniform],liItems,Value);}
void cShaderVariableSet::SetUniform3(uint32 liUniform,float *Value,uint16 liItems){if(liUniform<miUniforms) glUniform3fv(mpUniforms[liUniform],liItems,Value);}
void cShaderVariableSet::SetUniform4(uint32 liUniform,float *Value,uint16 liItems){if(liUniform<miUniforms) glUniform4fv(mpUniforms[liUniform],liItems,Value);}

void cShaderVariableSet::SetMatrix2(uint32 liUniform,float *Value){if(liUniform<miUniforms) glUniformMatrix2fv(mpUniforms[liUniform],1,0,Value);}
void cShaderVariableSet::SetMatrix3(uint32 liUniform,float *Value){if(liUniform<miUniforms) glUniformMatrix3fv(mpUniforms[liUniform],1,0,Value);}
void cShaderVariableSet::SetMatrix4(uint32 liUniform,float *Value){if(liUniform<miUniforms) glUniformMatrix4fv(mpUniforms[liUniform],1,0,Value);}
void cShaderVariableSet::SetMatrix(uint32 liUniform,cMatrix4 *lpMatrix,uint32 liMatricesInArray){if(liUniform<miUniforms) glUniformMatrix4fv(mpUniforms[liUniform],liMatricesInArray,0,lpMatrix->Matrix());}


void cShaderVariableSet::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,float *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_FLOAT,0,liStride,lpData);}
void cShaderVariableSet::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,uint32 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_UNSIGNED_INT,0,liStride,lpData);}
void cShaderVariableSet::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,uint16 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_UNSIGNED_SHORT,0,liStride,lpData);}
void cShaderVariableSet::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,uint8 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_UNSIGNED_BYTE,0,liStride,lpData);}
void cShaderVariableSet::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,int32 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_INT,0,liStride,lpData);}
void cShaderVariableSet::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,int16 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_SHORT,0,liStride,lpData);}
void cShaderVariableSet::SetAttribute(uint32 liAttribute,uint8 Size,uint16 liStride,int8 *lpData){if(liAttribute<miAttributes) glVertexAttribPointer(mpAttributes[liAttribute],Size,GL_BYTE,0,liStride,lpData);}
*/

cShaderVariableSet::cShaderVariableSet()
{
 miVariables=0;
 mpVariables=0;
}

cShaderVariableSet::~cShaderVariableSet()
{
delete []mpVariables; mpVariables=0;
}

int32 cShaderVariableSet::GetID(uint32 liVariableNumber)
{
    if(liVariableNumber<miVariables) return mpVariables[liVariableNumber].ID();
    return -1;
};



void cShaderVariableSet::BindAttributes(uint32 liProgramID)
{
if(mpVariables)
 {
 uint32 liCount;
 for(liCount=0;liCount<miVariables;++liCount)
 {
		if(mpVariables[liCount].Attribute()) glBindAttribLocation(liProgramID,mpVariables[liCount].ID(),mpVariables[liCount].Start());
 }
 }
}

