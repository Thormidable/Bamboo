#ifndef __WTCSHADER_H__
#define __WTCSHADER_H__

using namespace std;


using namespace std;

class cShader;
class cShaderVariableSet;

class cShaderVariable
{
protected:
    uint8 miType;
    char *mpStart;
	int32 miID;
	void SetID(int32 liID);
public:
    cShaderVariable();
	~cShaderVariable();
    void Set(bool lbUniform,uint8 liType,char* liStart);
    uint8 Type();
    bool Uniform();
    bool Attribute();
    char *Start();
    void SetType(uint8 liType);
    void SetScope(bool lbUniform);
    void AdjustStart(char *liChangeStart,int32 liChange);
	int32 ID();

	cShaderVariable &operator=(cShaderVariable &lcOther);

    void UpdateStart(char *lpStart);

    void LoadIMF(ifstream &FileStream);
    static uint32 Size();
    friend class cShader;
	friend class cShaderVariableSet;
};


class cShader : public cFile
{
protected:
   uint32 miCharCount;
   uint32 *mpLines;
   const GLchar **mpShaderText;
   uint8 miShaderType;
  uint32 miLines;

   uint32 miVariables;
   uint32 miVariableSpaces;
   cShaderVariable *mpVariables;
   GLuint miShaderID;

public:
        cShader();

	~cShader();
        void LoadIMF(ifstream &FileStream);

	uint8 ShaderType();
	 void SetType(uint8 liType);
	 GLuint ID();

	void Clear();
	void SetLines(int liL);
    uint8 Type();


	void BufferAndCompile();

	void BreakIntoLines(char *lpShaderText);

	uint32 Variables();
	cShaderVariable &Variable(uint32 liPos);


};

/*
class cShaderArray
{

public:
   uint32 miCharCount;
   char *mpShaderText;
   uint8 miShaderType;
   char *mpRef;
    uint32 miLines;
   uint32 *mpLines;


   uint32 miUniforms;
   int32 *mpUniforms;

   uint32 miAttributes;
   int32 *mpAttributes;


	cShaderArray();
	~cShaderArray();

	uint8 Type(){return miShaderType;};
	//This will set the total number of characters in the entire shader program. (Every line).
	void SetSize(uint32 liCharCount){miCharCount=liCharCount;};
	//This will set the type of this cShaderArray() object
	void SetType(uint8 liShaderType){miShaderType=liShaderType;};
	//This will set the character array storing the text for the Shader code to be the array pointed at by lpShaderText.
	void SetText(char *lpShaderText){mpShaderText=lpShaderText;};
	//This will set the number of lines in this Shader Program.
	void SetLines(uint32 liLines){miLines=liLines;};
	//This will set the array of line lengths to be the array pointed to by lpLines.
	void SetLineLengths(uint32 *lpLines){mpLines=lpLines;};
	//This will load the Shader code from the IMF file. FileStream should just be at the start of a Shader object in an IMF file.
	void LoadIMF(ifstream &FileStream);

};	uint8 Type(){return miShaderType;};


class cShader : public cFile
{

	friend class cShaderVariables;
protected:
  //This is the total number of characters in this shader code.
   uint32 miCharCount;
  //This will point to an array of strings for each line of code.
   const char **mpShaderText;
    //This is the type of Shader object for this object.It can be IMF_SHADER_TYPE_NULL or IMF_SHADER_TYPE_VERTEX or IMF_SHADER_TYPE_FRAGMENT or IMF_SHADER_TYPE_GEOMETRY.
    uint8 miShaderType;
   //This is the OpenGL ID for this object.
   uint32 miShaderID;
  //This is the number of lines in the Shader code.
   uint32 miLines;

   uint32 miUniforms;
   int32 *mpUniforms;

   uint32 miAttributes;
   int32 *mpAttributes;

public:
	cShader(){};
	//This will create a cShader() object from the data in cShaderArray().
	cShader(cShaderArray *lpData);
	//Destructor. Will delete mpShaderText and all arrays storing code.
	~cShader();
	//This will return the OpenGL Shader ID.
	uint32 ID(){return miShaderID;};
	//Will return the type of this shader.
	uint8 Type(){return miShaderType;};


};
*/

#endif
