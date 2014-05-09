#include "stdafx.h"
#include "../../WTBamboo.h"



void cShaderVariable::LoadIMF(ifstream &FileStream)
{
    FileStream.read((char*)&miType,sizeof(uint8));
    FileStream.read((char*)&miID,sizeof(uint32));
    mpStart=0;
}


uint32 cShaderVariable::Size()
{
    return sizeof(uint8)*sizeof(uint32);
}

void cShaderVariable::UpdateStart(char* lpStart)
{
	if(!mpStart)
	{
    	char *mpRef=&lpStart[miID];

		uint16 liStringLength;
		liStringLength=StringLength(mpRef," ,;");
		mpStart=new char[liStringLength+1];
		memcpy(mpStart,mpRef,sizeof(char)*liStringLength);
		mpStart[liStringLength]=0;
	}
}

int32 cShaderVariable::ID()
{
 return miID;
}

cShaderVariable::~cShaderVariable()
{
 delete []mpStart;
 mpStart=0;
}

cShaderVariable &cShaderVariable::operator=(cShaderVariable &lcOther)
{
 mpStart=new char[strlen(lcOther.mpStart)+1];
 strcpy(mpStart,lcOther.mpStart);
 miType=lcOther.miType;
 miID=lcOther.miID;
 return *this;
}

void cShaderVariable::SetID(int32 liID)
{
 miID=liID;
};

uint32 cShader::Variables()
{
    return miVariables;
}

cShaderVariable &cShader::Variable(uint32 liPos)
{
    return mpVariables[liPos];
}

cShader::~cShader()
{
delete []mpShaderText[0]; mpShaderText[0]=0;
delete []mpShaderText; mpShaderText=0;
delete []mpLines; mpLines=0;
delete []mpVariables; mpVariables=0;
}

cShader::cShader()
{
    mpLines=0;
    miCharCount=0;
    mpShaderText=0;
    miShaderType=0;
    mpLines=0;
    mpVariables=0;
    miVariables=0;

}

cShaderVariable::cShaderVariable()
{
 miType=0;
 mpStart=0;
}

void cShaderVariable::Set(bool lbUniform,uint8 liType,char* liStart)
{
    miType=liType;
    miType=miType|(0x80*lbUniform);
    mpStart=new char[strlen(liStart)+1];
	strcpy(mpStart,liStart);
}

void cShaderVariable::SetType(uint8 liType)
{
    bool lbUniform;
    lbUniform=Uniform();
    miType=liType;
    miType=miType|(0x80*lbUniform);
}

void cShaderVariable::SetScope(bool lbUniform)
{
    miType=((miType&0x7F)|(0x80*lbUniform));
}

uint8 cShaderVariable::Type(){return (miType&0x7F);};
bool cShaderVariable::Uniform(){return (miType&0x80);};
bool cShaderVariable::Attribute(){return !(miType&0x80);};
char* cShaderVariable::Start(){return mpStart;};
void cShaderVariable::AdjustStart(char *liChangeStart,int32 liChange)
{
    if(liChangeStart<mpStart) mpStart=&mpStart[liChange];
}


void cShader::LoadIMF(ifstream &FileStream)
{

        uint32 liTemp=0;
        //Ignore Block Size
        FileStream.ignore(sizeof(uint32));

        //Read the Reference
        FileStream.read((int8 *) &liTemp,sizeof(uint32));
        FileStream.read((int8 *) mpFileName,sizeof(int8)*liTemp);
        mpFileName[liTemp]=0;

        FileStream.read((char *) &miShaderType,sizeof(uint32));


        FileStream.read((char *) &miLines,sizeof(uint32));

        mpLines=new uint32[miLines];
        FileStream.read((char *) mpLines,sizeof(uint32)*miLines);


        FileStream.read((char *) &miVariables,sizeof(uint32));
        if(miVariables)
        {
                mpVariables=new cShaderVariable[miVariables];
                uint32 liCount;
                for(liCount=0;liCount<miVariables;++liCount)
                {
                    mpVariables[liCount].LoadIMF(FileStream);
                }
        }
        else mpVariables=0;


        char *lpShaderText;
        FileStream.read((char *) &miCharCount,sizeof(uint32));
        lpShaderText=new char[miCharCount+1];
        FileStream.read(lpShaderText,sizeof(char)*miCharCount);
        lpShaderText[miCharCount]=0;

        BreakIntoLines(lpShaderText);
        uint32 liCount;
        for(liCount=0;liCount<miVariables;++liCount)
        {
            mpVariables[liCount].UpdateStart(lpShaderText);
        }

}


/*
void cShader::DisplayShader()
{
	uint32 liTempRemoveThis;
	printf("Shader : %s\n",mpFileName);
for(liTempRemoveThis=0;liTempRemoveThis<miLines;++liTempRemoveThis)
{
 printf("%s\n",mpShaderText[liTempRemoveThis]);
}
printf("Code Finished\n");

};
*/
void cShader::BufferAndCompile()
{


if(miShaderType == IMF_SHADER_TYPE_NULL) {miShaderID=0; return;}
if(miShaderType == IMF_SHADER_TYPE_VERTEX)
{
    miShaderID=glCreateShader(GL_VERTEX_SHADER);
}
if(miShaderType == IMF_SHADER_TYPE_FRAGMENT) miShaderID=glCreateShader(GL_FRAGMENT_SHADER);
//if(miShaderType == IMF_SHADER_TYPE_GEOMETRY) miShaderID=glCreateShader(GL_GEOMETRY_SHADER);

 if(!miShaderID){TRACE("Failed to Create Shader " << mpFileName);}
 else TRACE("Shader " << mpFileName << " Created Successfully");

 //glShaderSource(miShaderID,0,mpShaderText,0);
const GLchar** lpTemp=mpShaderText;
 glShaderSource(miShaderID,miLines,lpTemp,0);
 glCompileShader(miShaderID);
int liID;
 glGetShaderiv(miShaderID, GL_COMPILE_STATUS, &liID);
 if(!liID)
  {TRACE("Shader " << mpFileName << " Failed to Compile");
    char lpLog[1024];
    GLsizei liLength;
    glGetShaderInfoLog(miShaderID,1024,&liLength,lpLog);
    trace(lpLog);
  }
 else trace("Shader " << mpFileName << " Compiled Successfully");


}

void cShader::Clear()
{
 delete[] mpLines;
 mpLines=0;
 miLines=0;
 delete[] mpShaderText;
 mpShaderText=0;

}

void cShader::SetLines(int liL)
{
 mpLines=new uint32[liL];
 miLines=liL;

}

void cShader::BreakIntoLines(char *lpShaderText)
{
    uint32 liCount;
    mpShaderText=new const char*[miLines];
    mpShaderText[0]=lpShaderText;
  for(liCount=0;liCount<miLines;++liCount)
  {
    mpShaderText[liCount]=&(lpShaderText[mpLines[liCount]]);
  }
}

uint8 cShader::ShaderType(){return miShaderType;};
void cShader::SetType(uint8 liType){miShaderType=liType;};
GLuint cShader::ID(){return miShaderID;};
	uint8 cShader::Type(){return miShaderType;};
/*
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
	//Uniform Variable Loading
	FileStream.read((char *) &miUniforms,sizeof(uint32));
	if(miUniforms)
	{
		mpUniforms=new int32[miUniforms];
		FileStream.read((char *) mpUniforms,sizeof(uint32)*miUniforms);
	}
	else mpUniforms=0;

	//Attribute Variable Loading
	FileStream.read((char *) &miAttributes,sizeof(uint32));
	if(miAttributes)
	{
		mpAttributes=new int32[miAttributes];
		FileStream.read((char *) mpAttributes,sizeof(uint32)*miAttributes);
	}
	else mpAttributes=0;

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
delete []mpUniforms; mpUniforms=0;
delete []mpAttributes; mpAttributes=0;
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
if(miShaderType == IMF_SHADER_TYPE_VERTEX)
{
    miShaderID=glCreateShader(GL_VERTEX_SHADER);
}
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

 miAttributes=lpData->miAttributes;
 mpAttributes=lpData->mpAttributes;
 miUniforms=lpData->miUniforms;
 mpUniforms=lpData->mpUniforms;

};

*/
