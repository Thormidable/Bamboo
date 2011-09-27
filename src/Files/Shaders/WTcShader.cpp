#include "../../WTDivWin.h"

void cShaderArray::LoadIMF(ifstream &FileStream)
{
	uint32 liTemp=0;

	char *lpText=0;
	//Ignore Block Size
	FileStream.ignore(sizeof(uint32));

	//Read the Reference
	FileStream.read((int8 *) &liTemp,sizeof(uint32));
	mpRef=new char[liTemp+1];
	FileStream.read((int8 *) mpRef,sizeof(int8)*liTemp);
	mpRef[liTemp]=0; 

	//Read Type
	FileStream.read((char *) &liTemp,sizeof(uint32));
	SetType(liTemp);

	//Read Number of Lines
	FileStream.read((char *) &liTemp,sizeof(uint32));
	SetLines(liTemp);

	//Read Lines
	mpLines=new uint32[liTemp];
	FileStream.read((char *) mpLines,sizeof(uint32)*liTemp);
	
	//Read Character Number
	FileStream.read((char *) &liTemp,sizeof(uint32));
	SetSize(liTemp);

	lpText=new char[liTemp+1];
	memset(lpText,0,sizeof(char)*liTemp);
	//Read Character String
	FileStream.read(lpText,sizeof(char)*liTemp);
	lpText[liTemp]=0;
	SetText(lpText);
}

cShaderArray::cShaderArray()
{
miCharCount=0;
mpShaderText=0;
miShaderType=0;
miLines=0;
mpLines=0;
mpRef=0;
};

cShaderArray::~cShaderArray()
{
if(mpLines){delete []mpLines; mpLines=0;}
delete []mpRef; mpRef=0;
};

cShader::~cShader()
{
if(mpShaderText) {delete []mpShaderText[0]; delete []mpShaderText; mpShaderText=0;}
if(miShaderID) {glDeleteShader(miShaderID); miShaderID=0;}
}

cShader::cShader(cShaderArray *lpData)
{
uint32 liCount;
miShaderID=0;
miCharCount=lpData->miCharCount;
miShaderType=lpData->miShaderType;
miLines=lpData->miLines;
strcpy(mpFileName,lpData->mpRef);

printf("Shader Reference %s\n",mpFileName);

mpShaderText=new const char*[miLines];

mpShaderText[0]=lpData->mpShaderText;
  for(liCount=0;liCount<miLines;++liCount)
  {
    mpShaderText[liCount]=&(lpData->mpShaderText[lpData->mpLines[liCount]]);
  }

if(miShaderType == IMF_SHADER_TYPE_NULL) {miShaderID=0; return;}
if(miShaderType == IMF_SHADER_TYPE_VERTEX) miShaderID=glCreateShader(GL_VERTEX_SHADER);
if(miShaderType == IMF_SHADER_TYPE_FRAGMENT) miShaderID=glCreateShader(GL_FRAGMENT_SHADER);
//if(miShaderType == IMF_SHADER_TYPE_GEOMETRY) miShaderID=glCreateShader(GL_GEOMETRY_SHADER);

 if(!miShaderID){trace("Failed to Create Shader "<<mpFileName);}
 else trace("Shader "<<mpFileName<<" Created Successfully");

 //glShaderSource(miShaderID,0,mpShaderText,0);

 glShaderSource(miShaderID,miLines,mpShaderText,0);
 glCompileShader(miShaderID);
int liID;
 glGetShaderiv(miShaderID, GL_COMPILE_STATUS, &liID);
 if(!liID)
  {trace("Shader "<<mpFileName<<" Failed to Compile");
    char lpLog[256];
    GLsizei liLength;
    glGetShaderInfoLog(miShaderID,256,&liLength,lpLog);
    trace(lpLog);
  }
 else trace("Shader "<<mpFileName<<" Compiled Successfully");


};


