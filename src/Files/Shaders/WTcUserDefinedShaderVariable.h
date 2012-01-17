#ifndef __WTCUSERDEFINEDSHADERVARIABLE_H__
#define __WTCUSERDEFINEDSHADERVARIABLE_H__

class cShaderProgram;
class cUserShaderVariable;

/**
 *\brief This is the general class for buffering an instance of a User defined cShaderProgram Variable.
 * This will store the bindings for the variable as well as the current value of the data. This has generic bindings to allow the system to update the variables with the values the user has set.
 * This is a virtual class and so an instance of this class cannot be created. see cAttributeStore, cAttributeArray1, cAttributeArray2, cAttributeArray3, cAttributeArray4, cUniformMatrix, cUniformStore, cUniformVector1, cUniformVector2, cUniformVector3 and cUniformVector4.
 **/
class cUserVariable
{
protected:
	int32 miID;
public:
	///Function to write the buffered value to the graphics card.
	virtual void Write()=0;
	///This will set the Variable ID that this variable should use.
	void SetID(int32 liID);
};

/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute Values.
 * This is a virtual class type of cUserVariable. It is still virtual but is specialised for Attribute variables.
 * This will store a pointer to the array of data. This means the user can hand the array to the class and update it, resulting in update every frame. The user must not delete the array or the system will end up reading random data.
 * Attribute Variables are variables which are set for every vertex in the object.
 **/
class cAttributeStore : public cUserVariable
{
protected:
 GLuint miBuffer;
 float *mpData;
 uint32 miElements;
public:
	///Constructor.
	cAttributeStore();
	///This will write the data to the cShaderProgram for use by the grpahics card.
	void Write()=0;
	///This will set the location of the array to use along with the number of elements in teh array.
	void Data(float *lpData,uint32 liElements);
	///This is an empty virtual function, but would normally buffer the array to the graphics card.
	virtual void Buffer()=0;
};

/**
 *\brief This is a specific type of cUserVariable for Controlling Uniform variables.
 * This is a virtual class type of cUserVariable. It is still virtual but is specialised for Uniform variables.
 * This will store a copy of the data set by the user. This means the user must pass the new values to this when they are changed.
 * Uniform Variables are variables which are the same for every vertex in the object.
 **/
class cUniformStore : public cUserVariable
{

public:
	///This is an empty virtual function but would normally write the buffered data to the graphics card to be used by a cShaderProgram.
	void Write()=0;
};

class cUniformTexture : public cUniformStore
{
protected:
 uint8 miTextureSlot;
public:

	cUniformTexture(uint8 miTextureSlot);
	void Write();
	void UpdateShaderState();
	cTexture *Data;

};

class cUniformFont : public cUniformTexture
{

public:
	cUniformFont(uint8 liTex);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore. *
 * This Object holds a single float to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformVector1 : public cUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	///The data is buffered here.
	float Data;
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a two float vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformVector2 : public cUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	///The data is buffered here.
	c2DVf Data;
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a two float vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformVector3 : public cUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	///The data is buffered here.
	c3DVf Data;
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a two float vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformVector4 : public cUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	///The data is buffered here.
	c4DVf Data;
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a 4x4 Matrix of floats to be used by cShaderProgram. WARNING: Data points to the Array instead of buffering the data. This means the Array must not be deleted, but will be automatically updated.
 **/
class cUniformMatrix : public cUniformStore
{

public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	///The data is buffered here.
	float *Data;
};

/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with a single value per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of single floats with total number of elements equal to verteces in the object.
 **/
class cAttributeArray1 : public cAttributeStore
{

public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	///This will Buffer the Data to the graphics card.
	void Buffer();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with two values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of two floats with total number of elements equal to twice the verteces in the object.
 **/
class cAttributeArray2 : public cAttributeStore
{

public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	///This will Buffer the Data to the graphics card.
	void Buffer();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with three values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of three floats with total number of elements equal to three times the verteces in the object.
 **/
class cAttributeArray3 : public cAttributeStore
{

public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	///This will Buffer the Data to the graphics card.
	void Buffer();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with four values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of four floats with total number of elements equal to four times the verteces in the object.
 **/
class cAttributeArray4 : public cAttributeStore
{

public:
///This will Write the buffered value to the Graphics card.
	void Write();
	///This will Buffer the Data to the graphics card.
	void Buffer();
};




/**
 *\brief This is the class through which the user will access Variables in cShaderProgram's.
 *
 *
 *
 **/
class cVariableStore
{
protected:
 uint32 miUniforms;
 int32 *mpUniformID;
 cUniformStore **mpUniform;

 uint32 miAttributes;
 int32 *mpAttributeID;
 cAttributeStore **mpAttribute;

public:
	void Link(cShaderProgram *lpProg);
	cVariableStore(cShaderProgram *lpProg);
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
	  mpAttribute[liVar]->Write();

  }
  return lpNew;
}


#endif
