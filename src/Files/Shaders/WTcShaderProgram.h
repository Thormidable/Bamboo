#ifndef __WTCSHADERPROGRAMFILE_H__
#define __WTCSHADERPROGRAMFILE_H__
/**
*\brief A cShaderProgram() is a series of cShader() objects compiled into a program. cShaderProgram is a cFile() object.
*The cShaderProgram() finds a pointer to all the Shaders that compose it and compile them into a program.
*A cShader() object can be used in many different programs.
*The cShaderProgram() can be produced manually using the AttachShader() and Link() functions.
*The cShaderProgram() can be turned on with the use function.

*/
class cShaderProgram : public cFile, public vShaderProgram
{
///This stores the cShaderPrograms() OpenGL ID;
uint32 miProgramID;
/// This stores a cReferenceList() object to store an array of string references specifying the Shaders to be linked together;
cReferenceList mcList;
/// This points to an array of pointers pointing to all the Shaders required to be linked to create this Shader Program.
cShader **mpShader;

cShaderVariables *mpVariables;

public:
  ///Public Constructor.
  cShaderProgram();
  ///Public Destructor.
 ~cShaderProgram();
  ///This will return the OpenGL Shader Program ID for this cShaderProgram() object.
  uint32 ID(){return miProgramID;};
  ///This will manually Attach the cShader() object lpShader to the OpenGL Shader Program miProgramID.
  void AttachShader(cShader *lpShader);
  /// This will manually remove the cShader() object lpShader from the OpenGL Shader Program miProgramID.
  void DetachShader(cShader *lpShader);
  /// This will Link() the compiled cShader() objects together.
  void Link();
  ///This will turn on shaders and make this shader the current shader system.
  void Use();
 ///This will return the number of cShader() objects used by this system.
  uint32 Size(){return mcList.Size();};
  ///This will turn off the usuage of shaders and return the system to using the Fixed Function Pipeline.
  static void UseFixedFunction();

  ///This will return a pointer to the cShader() object in position liCount of the cShader() List;
  cShader* operator[](uint32 liCount){if(mpShader) return mpShader[liCount]; else return 0;};
 /// This will allow the cShaderProgram() to extract a list of string references for Shaders. It will then find pointers to the cShader() objects and compile the program using them.
 void LoadIMF(ifstream &FileStream);

 cShaderVariables *ShaderVariables();



};

#endif
