#include "../../WTBamboo.h"



void cShaderProgram::LoadIMF(ifstream &FileStream)
{


	uint32 liBuff;
 FileStream.ignore(sizeof(uint32));

 FileStream.read((int8 *)&liBuff,sizeof(uint32));
 FileStream.read(mpFileName,sizeof(int8)*liBuff);
 mpFileName[liBuff]=0;


 mcList.LoadIMF(FileStream);
	delete []mpShader;
 mpShader = new cShader*[Size()];
 	delete mpVariableSet;
 mpVariableSet = new cShaderVariableSet;

 for(liBuff=0;liBuff<mcList.Size();++liBuff)
  {
    cShader* lpTemp=0;
    //lpTemp=reinterpret_cast<cShader*>(cFileHandler::Instance()->File(mcList.Reference(liBuff)));
    lpTemp=_GET_FILE(cShader,mcList.Reference(liBuff));
    if(lpTemp) {mpShader[liBuff]=lpTemp; AttachShader(lpTemp);}
    else {mpShader[liBuff]=0; TRACE("Reference : "<<mcList.Reference(liBuff)<<"Not Found");}
  }
 Link();

TRACE("Loaded and Processed ShaderProgram : " << mpFileName);

	StoredVariables()->Link(this);

 	Use();

	SetVariablePointer("mm2DProjection",_2DPROJECTION_MATRIX);
    SetVariablePointer("mmProjection",_PROJECTION_MATRIX);
    SetVariablePointer("mmCamera",_CAMERA_MATRIX);
   	SetVariablePointer("mmCombined",_COMBINED_MATRIX);
   	SetVariablePointer("Bb_Camera_Zoom",&_CAMERA_ZOOM);
/*
    miVertexID=glGetAttribLocation(miProgramID, "VertexPosition");
   	miNormalID=glGetAttribLocation(miProgramID, "VertexNormal");
   	miUVID=glGetAttribLocation(miProgramID, "VertexUV");
   	miFragID=glGetFragDataLocation(miProgramID,"FragColor");*/

}

GLuint cShaderProgram::VertexPositionID()
{
 return miVertexID;
};

GLuint cShaderProgram::VertexNormalID()
{
 return miNormalID;
};

GLuint cShaderProgram::VertexUVID()
{
  return miUVID;
};


cVariableStore *cShaderProgram::StoredVariables()
{
 if(!mpStoredVariables) mpStoredVariables=new cVariableStore(this);
 return mpStoredVariables;
}

cShaderProgram::cShaderProgram()
{
miProgramID=glCreateProgram();
TRACE("Shader Program ID: " << miProgramID);
mpShader=0;
mpVariableSet=0;
mpStoredVariables=0;
    miVertexID=0;
    miNormalID=0;
}

cShaderProgram::~cShaderProgram()
{
glUseProgram(0);
 if(miProgramID){glDeleteProgram(miProgramID); miProgramID=0;}
 delete []mpShader; mpShader=0;
 delete mpVariableSet;
 mpVariableSet=0;
 delete mpStoredVariables; mpStoredVariables=0;
}

void cShaderProgram::AttachShader(cShader *lpShader)
{
 glAttachShader(miProgramID,lpShader->ID());

}

void cShaderProgram::DetachShader(cShader *lpShader)
{
 glDetachShader(miProgramID,lpShader->ID());
}

void cShaderProgram::Link()
{
 int liStatus;

 mpVariableSet->BindAttributes(miProgramID);
 glLinkProgram(miProgramID);
 glGetProgramiv(miProgramID,GL_LINK_STATUS,&liStatus);
 if(!liStatus)
 {
	 bool Types[2];
	 Types[0]=1;
	 Types[1]=1;
	 for(liStatus=0;liStatus<Size();++liStatus)
	 {
		if(mpShader[liStatus]->Type()==IMF_SHADER_TYPE_VERTEX) Types[0]=0;
		if(mpShader[liStatus]->Type()==IMF_SHADER_TYPE_FRAGMENT) Types[1]=0;
	 }
	 if(Types[0]) TRACE("No Vertex Shader Linked to Program. This is required.");
	 if(Types[1]) TRACE("No Fragment Shader Linked to Program. This is required.");

	 TRACE("Shader Program failed to Link");

 }
 else
 {
	 TRACE("Shader Program Linked");
	 Use();
 	 mpVariableSet->GetVariableLocations(miProgramID,mpShader,Size());
 }
}

void cShaderProgram::Use()
{
 glUseProgram(miProgramID);
}


cShaderVariableSet *cShaderProgram::ShaderVariableSet()
{
	return mpVariableSet;
}





void cShaderProgram::SetShaderVariables()
{
 if(mpStoredVariables)
 {
  mpStoredVariables->WriteVariables();
 }
}


void cShaderProgram::SetUniform(string lcString,void *Data)
{
	uint32 liPos=mpVariableSet->GetUniformPosition(lcString);
	if(liPos) mpStoredVariables->GetVariable(liPos-1)->DataValue(Data);
};
void cShaderProgram::SetAttribute(string lcString,void *Data,uint32 liElements)
{
	uint32 liPos=mpVariableSet->GetAttributePosition(lcString);
	if(liPos) mpStoredVariables->GetVariable(liPos-1)->DataValue(Data,liElements);
};
void cShaderProgram::SetVariable(string lcString,void *Data)
{
	SetUniform(lcString,Data);
};
void cShaderProgram::SetVariable(string lcString,void *Data,uint32 liElements)
{
	SetAttribute(lcString,Data,liElements);
};


void cShaderProgram::SetUniformPointer(string lcString,void *Data)
{
		uint32 liPos=mpVariableSet->GetUniformPosition(lcString);
		if(liPos) mpStoredVariables->GetVariable(liPos-1)->DataPointer(Data);
};
void cShaderProgram::SetAttributePointer(string lcString,void *Data,uint32 liElements)
{
		uint32 liPos=mpVariableSet->GetAttributePosition(lcString);
		if(liPos) mpStoredVariables->GetVariable(liPos-1)->DataPointer(Data,liElements);
};
void cShaderProgram::SetVariablePointer(string lcString,void *Data)
{
	SetUniformPointer(lcString,Data);
};
void cShaderProgram::SetVariablePointer(string lcString,void *Data,uint32 liElements)
{
	SetAttributePointer(lcString,Data,liElements);
};


