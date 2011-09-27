#include "../../WTDivWin.h"

void cShaderProgram::LoadIMF(ifstream &FileStream)
{
 uint32 liBuff;
 FileStream.ignore(sizeof(uint32));

 FileStream.read((int8 *)&liBuff,sizeof(uint32));
 FileStream.read(mpFileName,sizeof(int8)*liBuff);
 mpFileName[liBuff]=0;
 

 mcList.LoadIMF(FileStream);

 mpShader = new cShader*[Size()];
 
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


}


cShaderProgram::cShaderProgram()
{
miProgramID=glCreateProgram();
printf("Shader Program ID: %lu\n",miProgramID);
mpShader=0;
}

cShaderProgram::~cShaderProgram()
{
glUseProgram(0);
 if(miProgramID){glDeleteProgram(miProgramID); miProgramID=0;}
 if(mpShader) delete []mpShader;
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
 glLinkProgram(miProgramID);
 glGetProgramiv(miProgramID,GL_LINK_STATUS,&liStatus);
 if(!liStatus){trace("Shader Program failed to Link");}
 else trace("Shader Program Linked");
}

void cShaderProgram::Use()
{
 glUseProgram(miProgramID);
}
