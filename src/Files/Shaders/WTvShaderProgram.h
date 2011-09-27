#ifndef __WTVSHADERPROGRAM_H__
#define __WTVSHADERPROGRAM_H__
/**
*\brief This is a virtual class for a Shader Program.
*A shader program is a series of cShader() objects to be compiled into a single Shader Program.
*/
class vShaderProgram
{

public:
 ~vShaderProgram(){};
  /// This will make the system Use this Shader Program, until another is set or a shader program is turned off.
  virtual void Use()=0;
  /// This will return the Program ID of this Shader Program.
  virtual uint32 ID()=0;
};

#endif
