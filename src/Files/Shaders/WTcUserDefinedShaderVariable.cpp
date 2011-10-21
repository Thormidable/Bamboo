#include "../../WTDivWin.h"

void cUserVariable::SetID(int32 liID)
{
 miID=liID;
}

cAttributeStore::cAttributeStore()
{
 mpData=0;
 glGenBuffers(1, &miBuffer);
}

void cAttributeStore::Data(float *lpmpData,uint32 liElements)
{
 		mpData=lpmpData;
		miElements=liElements;
		this->Buffer();
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
	 if(mpUniform[liCount]) mpUniform[liCount]->Write();
	 
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
	if(mpAttribute[liCount]) mpAttribute[liCount]->Write();
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



void cUniformVector1::Write()
{
	glUniform1f(miID,Data);
}
void cUniformVector2::Write()
{
	glUniform2fv(miID,1,Data.v);
}
void cUniformVector3::Write()
{
	glUniform3fv(miID,1,Data.v);
}
void cUniformVector4::Write()
{
	glUniform4fv(miID,1,Data.v);
}
void cUniformMatrix::Write()
{
	glUniformMatrix4fv(miID,1,0,Data);
}

void cAttributeArray1::Write()
{
	
	if(miID)
	{
		glEnableVertexAttribArray(miID);
	}
}

void cAttributeArray2::Write()
{
	if(miID)
	{
		glEnableVertexAttribArray(miID);
	}
}

void cAttributeArray3::Write()
{
	if(miID)
	{
		glEnableVertexAttribArray(miID);
	}
}

void cAttributeArray4::Write()
{
	if(miID)
	{
		glEnableVertexAttribArray(miID);
	}
}


void cAttributeArray1::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * miElements , mpData, GL_STATIC_DRAW);
	glVertexAttribPointer(miID,1,GL_FLOAT,0,0,0);
}

void cAttributeArray2::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) *2* miElements , mpData, GL_STATIC_DRAW);
	glVertexAttribPointer(miID,2,GL_FLOAT,0,0,0);
}

void cAttributeArray3::Buffer()
{
		glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) *miElements *3, mpData, GL_STATIC_DRAW);
		glVertexAttribPointer(miID,3,GL_FLOAT,0,0,0);
}

void cAttributeArray4::Buffer()
{
		glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * miElements *4, mpData, GL_STATIC_DRAW);
		glVertexAttribPointer(miID,4,GL_FLOAT,0,0,0);
}

