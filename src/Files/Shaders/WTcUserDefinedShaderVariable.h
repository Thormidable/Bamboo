#ifndef __WTCUSERDEFINEDSHADERVARIABLE_H__
#define __WTCUSERDEFINEDSHADERVARIABLE_H__

class cShaderProgram;
class cUserShaderVariable;

class cUserVariable
{
protected:
	int32 miID;
public:
	virtual void Write()=0;
	void SetID(int32 liID);
};


class cAttributeStore : public cUserVariable
{
protected:
 GLuint miBuffer;
 float *mpData;
 uint32 miElements;
public:
	cAttributeStore();
	void Write()=0;
	void Data(float *lpData,uint32 liElements);
	virtual void Buffer()=0;
};


class cUniformStore : public cUserVariable
{

public:
	void Write()=0;
};

class cUniformVector1 : public cUniformStore
{
public:
	void Write();
	float Data;
};

class cUniformVector2 : public cUniformStore
{
public:
	void Write();
	c2DVf Data;
};

class cUniformVector3 : public cUniformStore
{
public:
	void Write();
	c3DVf Data;
};

class cUniformVector4 : public cUniformStore
{
public:
	void Write();
	c4DVf Data;
};

class cUniformMatrix : public cUniformStore
{

public:
	void Write();
	cMatrix4 Data;

};

class cAttributeArray1 : public cAttributeStore
{
	
public:
	void Write();
	void Buffer();
};

class cAttributeArray2 : public cAttributeStore
{
	
public:
	void Write();
	void Buffer();
};

class cAttributeArray3 : public cAttributeStore
{
	
public:
	void Write();
	void Buffer();
};

class cAttributeArray4 : public cAttributeStore
{

public:
	void Write();
	void Buffer();
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
 if(liVar<miUniforms)
 {
	 mpUniform[liVar]=lpNew;
	 mpUniform[liVar]->SetID(mpUniformID[liVar]);
 }
 return lpNew;
}

template <class cX> cX *cVariableStore::CreateAttribute(uint32 liVar, cX *lpNew)
{
  if(liVar<miAttributes)
  {
	  mpAttribute[liVar]=lpNew;
	  mpAttribute[liVar]->SetID(mpAttributeID[liVar]);
  	glEnableVertexAttribArray(mpUniformID[liVar]);
  }
  return lpNew;
}



#endif
