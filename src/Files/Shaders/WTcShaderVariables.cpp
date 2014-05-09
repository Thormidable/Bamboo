#include "stdafx.h"
#include "../../WTBamboo.h"


uint32 cShaderVariableSet::GetVariablePosition(string Name)
{
uint32 liCount;
 for(liCount=0;liCount<miVariables;++liCount)
 {
	if(CompareVariables(mpVariables[liCount].Start(),Name.c_str()," ,;"))
	{
	    return liCount+1;
	}
 }
 return 0;

}

uint32 cShaderVariableSet::GetUniformPosition(string Name)
{
 uint32 liCount;
 for(liCount=0;liCount<miVariables;++liCount)
 {

	if(mpVariables[liCount].Uniform() && CompareVariables(mpVariables[liCount].Start(),Name.c_str()," ,;"))
	{
	    return liCount+1;
	}
 }
 return 0;

}

uint32 cShaderVariableSet::GetAttributePosition(string Name)
{
uint32 liCount;
 for(liCount=0;liCount<miVariables;++liCount)
 {
	if(mpVariables[liCount].Attribute() && CompareVariables(mpVariables[liCount].Start(),Name.c_str()," ,;"))
	{
	    return liCount+1;
	}
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

