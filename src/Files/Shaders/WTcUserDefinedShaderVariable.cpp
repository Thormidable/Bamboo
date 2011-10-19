#include "../../WTDivWin.h"

cAttributeStore::cAttributeStore()
{
 mpData=0;
 glGenBuffers(1, &miBuffer);
}

void cAttributeStore::Data(float *lpmpData)
{
 		mpData=lpmpData;
 		glBindBuffer(GL_ARRAY_BUFFER,miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4, mpData, GL_STATIC_DRAW);
}

cVariableStore::cVariableStore(vShaderProgram *lpProg)
{
  mpAttributeID=mpUniformID=0;
  mpUniform=0;
  mpAttribute=0;
  Link(lpProg);
}


void cVariableStore::ClearLink()
{
	
 uint32 liCount;
 if(mpUniform)
 {
 	for(liCount=0;liCount<miUniforms;++liCount)
 	{
  		delete mpUniform[liCount];
 	}
	delete []mpUniform;
	mpUniform=0;
 }
 
 if(mpAttribute)
 {
 	for(liCount=0;liCount<miAttributes;++liCount)
 	{
		delete mpAttribute[liCount];
  	}
  	delete []mpAttribute;
	mpAttribute=0;
 }
 
}

cVariableStore::~cVariableStore()
{
	ClearLink();
}

void cVariableStore::WriteUniforms()
{
 if(mpUniform)
 {
  uint32 liCount;
  for(liCount=0;liCount<miUniforms;++liCount)
  {
	 if(mpUniform[liCount]) mpUniform[liCount]->Write(mpUniformID[liCount]);
	 
  }
 }
}

void cVariableStore::EnableAttributeArrays()
{
if(mpAttribute)
 {
 uint32 liCount;
 for(liCount=0;liCount<miAttributes;++liCount)
 {
	if(mpAttribute[liCount])
	{
		glEnableVertexAttribArray(mpAttributeID[liCount]);
	}
 }
 }
}

void cVariableStore::WriteAttributes()
{
 if(mpAttribute)
 {
 uint32 liCount;
 for(liCount=0;liCount<miAttributes;++liCount)
 {
	if(mpAttribute[liCount])
	{
		
		mpAttribute[liCount]->Write(mpAttributeID[liCount]);
	}
 }
 }
}

void cVariableStore::Link(vShaderProgram *lpProg)
{
	cShaderVariables *lpLink=lpProg->ShaderVariables();
	ClearLink();
	
	miUniforms=lpLink->miUniforms;
	mpUniformID=lpLink->mpUniforms;
	mpUniform= new cUniformStore*[miUniforms];
	memset(mpUniform,0,sizeof(cUserVariable*)*miUniforms);

	miAttributes=lpLink->miAttributes;
	mpAttributeID=lpLink->mpAttributes;
	mpAttribute= new cAttributeStore*[miAttributes];
	memset(mpAttribute,0,sizeof(cUserVariable*)*miAttributes);


};



void cUniformVector1::Write(int32 liID)
{
	glUniform1f(liID,Data);
}
void cUniformVector2::Write(int32 liID)
{
	glUniform2fv(liID,1,Data.v);
}
void cUniformVector3::Write(int32 liID)
{
	glUniform3fv(liID,1,Data.v);
}
void cUniformVector4::Write(int32 liID)
{
	glUniform4fv(liID,1,Data.v);
}
void cUniformMatrix::Write(int32 liID)
{
	glUniformMatrix4fv(liID,1,0,Data.Matrix());
}


void cAttributeArray1::Write(int32 liID)
{
	
	if(mpData)
	{
		glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 1, mpData, GL_STATIC_DRAW);
		glBindVertexArray(miBuffer);
		glEnableVertexAttribArray(liID);
		glVertexAttribPointer(liID,1,GL_FLOAT,0,0,0);
	}
}

void cAttributeArray2::Write(int32 liID)
{
	if(mpData) glVertexAttribPointer(liID,2,GL_FLOAT,0,0,mpData);
}

void cAttributeArray3::Write(int32 liID)
{
	if(mpData) glVertexAttribPointer(liID,3,GL_FLOAT,0,0,mpData);
}

void cAttributeArray4::Write(int32 liID)
{
	if(mpData)
	{
		glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 27*4, mpData, GL_STATIC_DRAW);
		glBindVertexArray(miBuffer);
		glEnableVertexAttribArray(liID);
		glVertexAttribPointer(liID,4,GL_FLOAT,0,0,0);
	}
}
