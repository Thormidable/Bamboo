#ifndef __WTCATTRTIBUTEARRAYDATA_H__
#define __WTCATTRTIBUTEARRAYDATA_H__


/**
* \brief A class for storing generated Attribute data for RenderObjects.
*/
template<class tType> class cAttributeData
{
	tType *mpData;
	uint32 miElements;
	string DataName;

	void Initialise(uint32 liElements){mpData=new tType[liElements]; memset(mpData,0,sizeof(tType)*liElements); miElements=liElements;};
public:
	///Constructor for creating an instance of the class. Takes number of verteces in the linked mesh.
	cAttributeData(uint32 liElements)
	{
		Initialise(liElements);
	};

	///Constructor for creating an instance of the class. Takes number of verteces in the linked mesh and text reference of the attribute variable to link to.
	cAttributeData(uint32 liElements,string lsName)
	{
		Initialise(liElements);
		DataName=lsName;
	};

	/// Returns a pointer to the type of data.
	tType *Data(){return mpData;};
	/// Returns the number of elements in this cAttributeData object
	uint32 Elements(){return miElements;};
	/// Returns the text reference of the attribute variable to link to
	string Name(){return DataName;};

	/// This will Link this array of data to the cRenderObject lpObject.
	void LinkToShader(cRenderObject *lpObject)
	{
		uint32 liPos=lpObject->Shader()->ShaderVariableSet()->GetAttributePosition(DataName.c_str());
		if(liPos)
		{

		    lpObject->Variables()->GetVariable(liPos-1)->DataPointer(mpData,miElements);
            lpObject->Variables()->GetVariable(liPos-1)->Buffer();
		}
	}
	/// This will Link this array of data to the atrribute variable with the text reference lsName within the shader used by the cRenderObject lpObject.
	void LinkToShader(cRenderObject *lpObject,string lsName)
	{
		uint32 liPos=lpObject->Shader()->ShaderVariableSet()->GetAttributePosition(lsName.c_str());
		if(liPos) lpObject->Variables()->GetVariable(liPos-1)->DataPointer(mpData,miElements);
	}
	///Will return the data item at position liPos.
	tType &operator[](uint32 liPos){return mpData[liPos];};

	///Will return the data item at position liPos.
	tType &Get(uint32 liPos){return mpData[liPos];};

	~cAttributeData()
	{
        delete []mpData;
        mpData=0;
	}
};

/**
 * \brief This class wil generate TBN Vectors for a mesh. Inherits from cAttributeData.
 * This requires the mesh to have UV co-ordinates and Normals.
 * TBN stands for Tangent, Binormal and Normal vectors. These are used in Normal Mapping shaders.
 * This data will automatically be linked to Bb_Tangent,Bb_Binormal and Bb_Normal.
 */
class cTBNVectors
{
 cAttributeData<c3DVf> *Tangent;
 cAttributeData<c3DVf> *Bitangent;
 cAttributeData<c3DVf> *Normal;
///This will calculate the data for the object.
 void GenerateTBNVectors(cMesh *lpMesh);
public:
 cTBNVectors(cMesh *lpMesh);
 ~cTBNVectors();
 ///This will Link the TBN data to the object lpObj. This will use the default names for the various arrays of data.
 void LinkToShader(cRenderObject *lpObj);

};

class cInterleavedAttributeArray;
class cManualInterleavedAttributeArray;
class cAutoInterleavedAttributeArray;

class cAttributeArrayComponentData
{

 friend class cInterleavedAttributeArray;
 friend class cManualInterleavedAttributeArray;
 friend class cAutoInterleavedAttributeArray;

protected:
    uint8 miItems;
    string msName;
public:
    cAttributeArrayComponentData(uint8 liItems,string lsName);

    uint8 Items();
    string Name();

    virtual void Write(int32 liID,char *liStart,uint16 liElementSize)=0;
    virtual uint32 Size()=0;
};

class cInterleavedFloatArray : public cAttributeArrayComponentData
{

public:
    cInterleavedFloatArray(uint8 liItems,string lsName);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};


class cInterleavedDoubleArray : public cAttributeArrayComponentData
{

public:
    cInterleavedDoubleArray(uint8 liItems,string lsName);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};


class cInterleavedInt8Array : public cAttributeArrayComponentData
{

public:
    cInterleavedInt8Array(uint8 liItems,string lsName);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};

class cInterleavedInt16Array : public cAttributeArrayComponentData
{

public:
    cInterleavedInt16Array(uint8 liItems,string lsName);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};

class cInterleavedInt32Array : public cAttributeArrayComponentData
{

public:
    cInterleavedInt32Array(uint8 liItems,string lsName);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};


class cInterleavedUint8Array : public cAttributeArrayComponentData
{

public:
    cInterleavedUint8Array(uint8 liItems,string lsName);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};

class cInterleavedUint16Array : public cAttributeArrayComponentData
{

public:
    cInterleavedUint16Array(uint8 liItems,string lsName);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};

class cInterleavedUint32Array : public cAttributeArrayComponentData
{

public:
    cInterleavedUint32Array(uint8 liItems,string lsName);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};

class cInterleavedVertexArray : public cAttributeArrayComponentData
{
public:
    cInterleavedVertexArray(uint8 liItems);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};

class cInterleavedNormalArray : public cAttributeArrayComponentData
{
public:
    cInterleavedNormalArray();
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};

class cInterleavedTexCoordArray : public cAttributeArrayComponentData
{
public:
   cInterleavedTexCoordArray(uint8 liItems);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};

class cInterleavedColorArray : public cAttributeArrayComponentData
{
public:
   cInterleavedColorArray(uint8 liItems);
    void Write(int32 liID,char *liStart,uint16 liElementSize);
    uint32 Size();
};

class cInterleavedAttributeArray : public cLimitedPointerList<cAttributeArrayComponentData>
{
protected:
  GLuint miBuffer;
  uint32 miElementSize;
  uint32 miElements;
  char *mpData;

public:
    cInterleavedAttributeArray(uint32 liElements);
    ~cInterleavedAttributeArray();

    void Buffer();

    cAttributeArrayComponentData *Component(uint16 liPos);
    uint16 operator[](string lsName);
    uint16 Component(string lsName);
    uint16 Components();
    void Write(int32 *mpAttributeIDs);

};

class cManualInterleavedAttributeArray : public cInterleavedAttributeArray
{
public:
    cManualInterleavedAttributeArray(uint32 liElements);
    ~cManualInterleavedAttributeArray();
    void AddComponent(cAttributeArrayComponentData *lpComponent);
    void AddComponents(uint16 liComponents,cAttributeArrayComponentData **lpComponent);
    void PointData(char *lpData);
    void Elements(uint32 liElements);
    void DeleteComponent(uint16 liComponent);
    void DeleteComponent(string lsName);
};

class cAutoInterleavedAttributeArray : public cInterleavedAttributeArray
{
    public:
    cAutoInterleavedAttributeArray(uint32 liElements);
    ~cAutoInterleavedAttributeArray();
    void Elements(uint32 liElements);
    void AddComponent(cAttributeArrayComponentData *lpComponent,char *lpData);
    void AddComponents(uint16 liComponents,cAttributeArrayComponentData **lpComponent,char *lpData);
    void UpdateComponentData(uint16 liComponent,char *lpData);
    void UpdateComponentData(string lsName,char *lpData);
    void DeleteComponent(uint16 liComponent);
    void DeleteComponent(string lsName);
    void DeleteComponentsData(uint16 liComponent);
    void RemoveComponentsData(uint16 liComponent);


};



class cAttributeLinker
{
 int32 miProgramID;
 int32 *mpAttributeIDs;
 cInterleavedAttributeArray *mpArray;
public:
    cAttributeLinker(cInterleavedAttributeArray *lpArray,cShaderProgram *lpProgram=0);
    ~cAttributeLinker();
    void Shader(cShaderProgram *lpProgram);
    void AttributeArray(cInterleavedAttributeArray *lpArray);
    void ShaderAndAttributeArray(cShaderProgram *lpProgram,cInterleavedAttributeArray *lpArray);
    void AttributeArrayUpdated();
    void Write();
	int32 ProgramID();
};

class cElementArray
{
 uint16 *mpData;
 uint32 miElements;
 GLuint miBuffer;
public:
	cElementArray();
	~cElementArray();
	void PointData(uint16 *lpData);
	void Elements(uint32 liElements);
	uint16 *Data();
	uint32 Elements();

	void Buffer();
	void Render();
	void Render(uint32 liElements);

};


#endif
