#include "../../WTBamboo.h"



void cShaderProgram::LoadIMF(ifstream &FileStream)
{
 uint32 liBuff;
 FileStream.ignore(sizeof(uint32));

 FileStream.read((int8 *)&liBuff,sizeof(uint32));
 FileStream.read(mpFileName,sizeof(int8)*liBuff);
 mpFileName[liBuff]=0;


 mcList.LoadIMF(FileStream);

 mpShader = new cShader*[Size()];
 mpVariables = new cShaderVariables;

 for(liBuff=0;liBuff<mcList.Size();++liBuff)
  {
    cShader* lpTemp=0;
    //lpTemp=reinterpret_cast<cShader*>(cFileHandler::Instance()->File(mcList.Reference(liBuff)));
    lpTemp=_GET_FILE(cShader,mcList.Reference(liBuff));
    if(lpTemp) {mpShader[liBuff]=lpTemp; AttachShader(lpTemp);}
    else {mpShader[liBuff]=0; trace("Reference : "<<mcList.Reference(liBuff)<<"Not Found");}
  }
 Link();

trace("Loaded and Processed ShaderProgram : " << mpFileName);


	StoredVariables()->Link(this);

 	Use();

	cUniformMatrix *lpTemp;

	  lpTemp=AddUniform<cUniformMatrix>("mm2DProjection");
	  if(lpTemp) lpTemp->Data=_CAMERA->Perspective2D();

      lpTemp=AddUniform<cUniformMatrix>("mmProjection");
	  if(lpTemp) lpTemp->Data=_CAMERA->Perspective();

      lpTemp=AddUniform<cUniformMatrix>("mmCamera");
	  if(lpTemp)lpTemp->Data=_CAMERA->CameraMatrix();

   	  lpTemp=AddUniform<cUniformMatrix>("mmCombined");
	  if(lpTemp) lpTemp->Data=_CAMERA->PerspectiveCameraMatrix();

}

cShaderProgram::cShaderProgram()
{
miProgramID=glCreateProgram();
printf("Shader Program ID: %u\n",miProgramID);
mpShader=0;
mpVariables=0;
mpStoredVariables=0;
}

cShaderProgram::~cShaderProgram()
{
glUseProgram(0);
 if(miProgramID){glDeleteProgram(miProgramID); miProgramID=0;}
 delete []mpShader; mpShader=0;
 delete mpVariables; mpVariables=0;
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

 mpVariables->BindAttributes(miProgramID);
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
	 if(Types[0]) trace("No Vertex Shader Linked to Program");
	 if(Types[1]) trace("No Fragment Shader Linked to Program");

	 trace("Shader Program failed to Link");

 }
 else
 {
	 trace("Shader Program Linked");
	 Use();
 	 mpVariables->GetAttributeLocations(miProgramID,mpShader,Size());
	 mpVariables->GetUniformLocations(miProgramID,mpShader,Size());
 }
}

void cShaderProgram::Use()
{
 glUseProgram(miProgramID);
}


cShaderVariables *cShaderProgram::ShaderVariables()
{
	return mpVariables;
}




cVariableStore *cShaderProgram::StoredVariables()
{
 if(!mpStoredVariables) mpStoredVariables=new cVariableStore(this);
 return mpStoredVariables;
}

void cShaderProgram::SetShaderVariables()
{
 if(mpStoredVariables)
 {
  Use();
  mpStoredVariables->WriteUniforms();
  mpStoredVariables->WriteAttributes();
 }

}




