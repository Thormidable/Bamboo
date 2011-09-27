#ifndef __WTVSHADER_H__
#define __WTVSHADER_H__

///This is the virutal base class for the Shader Files - both Vertex and Fragment.
class vShader : public cFile
{
public:
///Public Destructor
virtual ~vShader(){};
	/// Will return the Shaders ID number.
virtual uint32 ID()=0;
};

#endif
