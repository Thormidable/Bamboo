#ifndef __WTCUSERDEFINEDSHADERVARIABLE_H__
#define __WTCUSERDEFINEDSHADERVARIABLE_H__

class cShaderProgram;
class cUserShaderVariable;

class cUserVariable
{
protected:
	
public:
	virtual void Write(int32 liID)=0;
};


class cAttributeStore : public cUserVariable
{
protected:
 GLuint miBuffer;
 float *mpData;
public:
	cAttributeStore();
	void Write(int32 liID)=0;
	void Data(float *lpData);
};


class cUniformStore : public cUserVariable
{

public:
	void Write(int32 liID)=0;
};

class cUniformVector1 : public cUniformStore
{
public:
	void Write(int32 liID);
	float Data;
};

class cUniformVector2 : public cUniformStore
{
public:
	void Write(int32 liID);
	c2DVf Data;
};

class cUniformVector3 : public cUniformStore
{
public:
	void Write(int32 liID);
	c3DVf Data;
};

class cUniformVector4 : public cUniformStore
{
public:
	void Write(int32 liID);
	c4DVf Data;
};

class cUniformMatrix : public cUniformStore
{

public:
	void Write(int32 liID);
	cMatrix4 Data;

};

class cAttributeArray1 : public cAttributeStore
{
	
public:
	void Write(int32 liID);
};

class cAttributeArray2 : public cAttributeStore
{
	
public:
	void Write(int32 liID);
};

class cAttributeArray3 : public cAttributeStore
{
	
public:
	void Write(int32 liID);
};

class cAttributeArray4 : public cAttributeStore
{

public:
	void Write(int32 liID);
};



class cVariableStore
{
protected:
 uint32 miUniforms;
 int32 *mpUniformID;
 cUniformStore **mpUniform;

 uint32 miAttributes;
 int32 *mpAttributeID;
 cAttributeStore **mpAttribute;
 void Link(vShaderProgram *lpProg);
public:

	cVariableStore(vShaderProgram *lpProg);
	virtual void WriteUniforms();
	virtual void WriteAttributes();
	void EnableAttributeArrays();
	

	cAttributeStore &GetAttribute(uint32 liVar){return *mpAttribute[liVar];};
	cUniformStore &GetUniform(uint32 liVar){return *mpUniform[liVar];};
	template<class cX> cX *CreateUniform(uint32 liVar, cX *lpNew);
	template<class cX> cX *CreateAttribute(uint32 liVar, cX *lpNew);
	~cVariableStore();

	void ClearLink();
	
	friend class cUserShaderVariable;
	friend class cRenderObject;
};

template <class cX> cX *cVariableStore::CreateUniform(uint32 liVar, cX *lpNew)
{
 if(liVar<miUniforms) mpUniform[liVar]=lpNew;
 return lpNew;
}

template <class cX> cX *cVariableStore::CreateAttribute(uint32 liVar, cX *lpNew)
{
  if(liVar<miAttributes)
  {
	  mpAttribute[liVar]=lpNew;
  	glEnableVertexAttribArray(mpUniformID[liVar]);
  }
  return lpNew;
}



#endif
