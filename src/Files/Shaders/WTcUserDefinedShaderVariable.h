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
	bool mbGenerated;
public:

	cUserVariable();
	///Function to write the buffered value to the graphics card.
	virtual void Write()=0;
	///This will set the Variable ID that this variable should use.
	void SetID(int32 liID);
	///This will return the Variable ID that this Variable is using.
	int32 ID();
	///This will Set the Data a Uniform Variable will Use. This will copy the data. It will not automatically update, but the data can be deallocated at any time.
	virtual void DataValue(void *lpData)=0;
	///This will Set the Data a Uniform Variable will Use. This will not copy the data, but will store a pointer to the data. It will automatically update, but the data passed to it should not be deallocated while the shader is in use.
	virtual void DataPointer(void *lpData)=0;
	///This will Set the Array of Data an Attribute Variable will Use. This will copy the data. It will not automatically update, but the data can be deallocated at any time.
	virtual void DataValue(void *lpData,uint32 liElements)=0;
	///This will Set the Array of Data an Attribute Variable will Use. This will not copy the data, but will store a pointer to the data. It will automatically update, but the data passed to it should not be deallocated while the shader is in use.
	virtual void DataPointer(void *lpData,uint32 liElements)=0;
	///This will return the data the Function is pointing at.
	virtual void *Data()=0;

	virtual void Buffer()=0;

};
/**
 * \brief This is a type of cUserVariable for types handled in other parts of the program. (Usually cPainter).
 * This is for types such as sampler1D, sampler2D, sampler3D etc. These are handled in another part of the program.
 */
class cVoidVariable : public cUserVariable
{
 void Write();
 void DataValue(void *lpData);
 void DataPointer(void *lpData);
 void DataValue(void *lpData,uint32 liElements);
 void DataPointer(void *lpData,uint32 liElements);
 void *Data();

 void Buffer(){};

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
 uint32 miElements;
public:
	//Constructor.
	cAttributeStore();
	~cAttributeStore();
	//This will write the data to the cShaderProgram for use by the grpahics card.
	void Write();
	//This will buffer the number of elements liElements stored in lpData into the graphics card.
	void DataValue(void *lpData,uint32 liElements)=0;
	//This will set the location of the array to use along with the number of elements in teh array.
	void DataValue(void *lpData){(void) lpData;};

	void DataPointer(void *lpData){(void) lpData;};
	void DataPointer(void *lpData,uint32 liElements)=0;

	virtual void Bind()=0;

};
/**
 * \brief More Specific Base class for Attribute Handling classes. Suitable for float Variables.
 * see cAttributeArray1, cAttributeArray2, cAttributeArray3, cAttributeArray4
 * */
class cFloatAttributeStore : public cAttributeStore
{
protected:
    GLfloat *mpData;
public:
    cFloatAttributeStore();
    void DataValue(void *lpData,uint32 liElements);
	void DataPointer(void *lpData,uint32 liElements);
	void *Data();
};

/**
 * \brief More Specific Base class for Attribute Handling classes. Suitable for integer Variables.
 * see cAttributeIntArray1, cAttributeIntArray2, cAttributeIntArray3, cAttributeIntArray4
 * */
class cIntAttributeStore : public cAttributeStore
{
protected:
    GLint *mpData;
public:
    cIntAttributeStore();
    void DataValue(void *lpData,uint32 liElements);
	void DataPointer(void *lpData,uint32 liElements);
	void *Data();
};

/**
 * \brief More Specific Base class for Attribute Handling classes. Suitable for bool Variables.
 * see cAttributeBooleanArray1, cAttributeBooleanArray2, cAttributeBooleanArray3, cAttributeBooleanArray4
 * */
class cBooleanAttributeStore : public cAttributeStore
{
protected:
    GLint *mpData;
public:
    cBooleanAttributeStore();
    void DataValue(void *lpData,uint32 liElements);
	void DataPointer(void *lpData,uint32 liElements);
	void *Data();
};

/**
 *\brief This is a specific type of cUserVariable for Controlling Uniform variables.
 * This is a virtual class type of cUserVariable. It is still virtual but is specialised for Uniform variables.
 * This will store a copy of the data set by the user. This means the user must pass the new values to this when they are changed.
 * Uniform Variables are variables which are the same for every vertex in the object.
 * see cFloatUniformStore, cIntUniformStore, cBooleanUniformStore.
 **/
class cUniformStore : public cUserVariable
{

public:
	///This is an empty virtual function but would normally write the buffered data to the graphics card to be used by a cShaderProgram.
	void Write()=0;
	//Does nothing for Uniforms
	void DataValue(void *lpData,uint32 liElements){(void) lpData;(void)liElements;};
	void DataPointer(void *lpData,uint32 liElements){(void) lpData; (void) liElements;};
	//Does nothing for Attributes.
	void DataValue(void *lpData)=0;

	virtual void ClearData();
	virtual void DataPointer(void *lpData)=0;

	~cUniformStore();
    void Buffer(){};
};
/**
 * \brief More Specific Base class for Uniform Handling classes. Suitable for float Variables.
 * see cUniformVector1, cUniformVector2, cUniformVector3, cUniformVector4.
 * */
class cFloatUniformStore : public cUniformStore
{
protected:
  GLfloat *mpData;
public:

	void ClearData();
	void DataPointer(void *lpData);
    void *Data();
    cFloatUniformStore();
    ~cFloatUniformStore();
};
/**
 * \brief More Specific Base class for Uniform Handling classes. Suitable for Integer Variables.
 * see cUniformIntVector1, cUniformIntVector2, cUniformIntVector3, cUniformIntVector4.
 * */
class cIntUniformStore : public cUniformStore
{
protected:
  GLint *mpData;
public:
	void ClearData();
	void DataPointer(void *lpData);
	void *Data();
    cIntUniformStore();
    ~cIntUniformStore();
};

/**
 * \brief More Specific Base class for Uniform Handling classes. Suitable for Boolean Variables
 * see cUniformBooleanVector1, cUniformBooleanVector2, cUniformBooleanVector3, cUniformBooleanVector4.
 * */
class cBooleanUniformStore : public cUniformStore
{
protected:
  GLint *mpData;
public:
	void ClearData();
	void DataPointer(void *lpData);
	void *Data();
    cBooleanUniformStore();
    ~cBooleanUniformStore();
};

/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * This Object holds a single float to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformVector1 : public cFloatUniformStore
{
public:
    void ClearData();
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * This Object holds a two float vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformVector2 : public cFloatUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a three float vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformVector3 : public cFloatUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a four float vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformVector4 : public cFloatUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};

/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore. *
 * This Object holds a single GLint to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformIntVector1 : public cIntUniformStore
{
public:
    void ClearData();
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a two GLint vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformIntVector2 : public cIntUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a three GLint vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformIntVector3 : public cIntUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a four GLint vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformIntVector4 : public cIntUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};


/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore. *
 * This Object holds a single boolean to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformBooleanVector1 : public cBooleanUniformStore
{
public:
    void ClearData();
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a two Boolean vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformBooleanVector2 : public cBooleanUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a three Boolean vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformBooleanVector3 : public cBooleanUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a four Boolean vector to be used by cShaderProgram. Data must be updated by the end of every frame if the data is changed.
 **/
class cUniformBooleanVector4 : public cBooleanUniformStore
{
public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};

/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a 4x4 Matrix of floats to be used by cShaderProgram. WARNING: Data points to the Array instead of buffering the data. This means the Array must not be deleted, but will be automatically updated.
 **/
class cUniformMatrix4 : public cFloatUniformStore
{

public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a 3x3 Matrix of floats to be used by cShaderProgram. WARNING: Data points to the Array instead of buffering the data. This means the Array must not be deleted, but will be automatically updated.
 **/
class cUniformMatrix3 : public cFloatUniformStore
{

public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};
/**
 *\brief This is a specific type of cUniformStore for Controlling Uniform variable from a cShaderProgram.
 * See cUniformStore.
 *
 * This Object holds a 2x2 Matrix of floats to be used by cShaderProgram. WARNING: Data points to the Array instead of buffering the data. This means the Array must not be deleted, but will be automatically updated.
 **/
class cUniformMatrix2 : public cFloatUniformStore
{

public:
	///This will Write the buffered value to the Graphics card.
	void Write();
	void DataValue(void *lpData);
};

/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with a single value per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of single floats with total number of elements equal to verteces in the object.
 **/
class cAttributeArray1 : public cFloatAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with two values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of two floats with total number of elements equal to twice the verteces in the object.
 **/
class cAttributeArray2 : public cFloatAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();

};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with three values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of three floats with total number of elements equal to three times the verteces in the object.
 **/
class cAttributeArray3 : public cFloatAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with four values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of four floats with total number of elements equal to four times the verteces in the object.
 **/
class cAttributeArray4 : public cFloatAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
};

/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with a single value per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of single GLint with total number of elements equal to verteces in the object.
 **/
class cAttributeIntArray1 : public cIntAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with two values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of two GLints with total number of elements equal to twice the verteces in the object.
 **/
class cAttributeIntArray2 : public cIntAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with three values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of three GLints with total number of elements equal to three times the verteces in the object.
 **/
class cAttributeIntArray3 : public cIntAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with four values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of four GLints with total number of elements equal to four times the verteces in the object.
 **/
class cAttributeIntArray4 : public cIntAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with a single value per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of single booleans with total number of elements equal to verteces in the object.
 **/
class cAttributeBooleanArray1 : public cBooleanAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with two values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of two booleans with total number of elements equal to twice the verteces in the object.
 **/
class cAttributeBooleanArray2 : public cBooleanAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with three values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of three booleans with total number of elements equal to three times the verteces in the object.
 **/
class cAttributeBooleanArray3 : public cBooleanAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
};
/**
 *\brief This is a specific type of cUserVariable for Controlling an array of Attribute with four values per vertex.
 * See cAttributeStore.
 *
 * This Object holds an array of four booleans with total number of elements equal to four times the verteces in the object.
 **/
class cAttributeBooleanArray4 : public cBooleanAttributeStore
{
public:
	///This will Buffer the Data to the graphics card.
	void Buffer();
	void Bind();
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
 uint32 miVariables;
 cUserVariable **mpVariables;


public:

	void GenerateVariableSet(cShaderVariableSet *lpSet);
	void Link(cShaderProgram *lpProg);
	cVariableStore(cShaderProgram *lpProg);
	virtual void WriteVariables();

	cUserVariable *GetVariable(uint32 liVar);
	~cVariableStore();

	void ClearLink();
	uint32 Variables();

	friend class cUserShaderVariable;
	friend class cRenderObject;

	template <class cType> cType* GetVariable(uint32 liPos);
	template <class cType> cType* GetUniform(uint32 liPos);
	template <class cType> cType* GetAttribute(uint32 liPos);

};


template <class cType> cType* cVariableStore::GetVariable(uint32 liPos)
{
 if(liPos<miVariables)
 {
		return dynamic_cast<cType*>(&mpVariables[liPos]);
 }
 return 0;

}

template <class cType> cType* cVariableStore::GetUniform(uint32 liPos)
{
	if(liPos<miVariables)
	{
		cUniformStore *lpReturn=dynamic_cast<cUniformStore*>(&mpVariables[liPos]);
		if(lpReturn) return dynamic_cast<cType*>(lpReturn);
	}
 return 0;
}

template <class cType> cType* cVariableStore::GetAttribute(uint32 liPos)
{
	if(liPos<miVariables)
	{
		cAttributeStore *lpReturn=dynamic_cast<cAttributeStore*>(&mpVariables[liPos]);
		if(lpReturn) return dynamic_cast<cType*>(&lpReturn);
	}
 return 0;
}


#endif
