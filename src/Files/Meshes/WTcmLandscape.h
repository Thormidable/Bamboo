#ifndef __WTCMLANDSCAPEMESH_H__
#define __WTCMLANDSCAPEMESH_H__

#define WT_LANDSCAPE_NODES miXSteps*miZSteps
#define WT_LANDSCAPE_POLYGONS (miXSteps-1)*(miZSteps-1)

class cLandscapeMeshFile;

/**
* \brief This is a class to transfer data from a hdd file to memory in a format that is quick and easy to render.
This is a temporary storage class to ease transformation of data from the hdd to the cmLandscape class.
*/
class cmLandscapeArray
{
public:
 // This array will store the vertex position data for the landscape.
 float *mpVertex;
// This array will store the texture co-ordinates for the landscape.
 float *mpUV;
 // This stores the number of landscape segments along the landscapes X axis.
 uint32 miXSteps;
// This stores the number of landscape segments along the landscapes Z axis.
 uint32 miZSteps;
 // This stores the size of a single landscape segment along the landscapes X axis.
 float mfXSize;
// This stores the size of a single landscape segment along the landscapes Z axis.
 float mfZSize;
 // This stores the maximum height of the landscape. The range is 0 - mfHeightRange.
 float mfHeightRange;
 // This stores the filename or file reference for this landscape.
  char *mpRef;

 cmLandscapeArray();
 ~cmLandscapeArray();
};



/**
* \brief This will store the data for a landscape mesh.
* The data can be rendered through cLandscape.
*/
class cmLandscape
{
protected:
 // This stores the number of custom landscapes the user has produced.
static uint32 miCustomLandscapes;

float *mpVertex;
// This is a pointer to the array holding vertex normal vector data for the mesh.
float *mpNormals;
// This is a pointer to the array holding texture co-ordinates for the mesh.
float *mpUV;

 uint32 miXSteps;
// This stores the number of landscape segments along the landscapes Z axis.
 uint32 miZSteps;
 // This stores the size of a single landscape segment along the landscapes X axis.
 float mfXSize;
// This stores the size of a single landscape segment along the landscapes Z axis.
 float mfZSize;
 // This stores the maximum height of the landscape. The range is 0 - mfHeightRange.
 float mfHeightRange;
/* // This stores the filename or file reference for this landscape.
  char *mpRef;*/
 // This array stores the face data for the landscape.
 uint16 *mpQuads;
 // This stores the number of quadrilateral faces in the landscape. (Actually seems to be the number of nodes in the face data array.
 uint16 miQuads;
 // This stores the Inverse of the landscape segment size along the landscapes X axis to avoid using divide.
 float mfXSizeI;
 // This stores the Inverse of the landscape segment size along the landscapes Z axis to avoid using divide.
 float mfZSizeI;


 GLuint *mpBufferIDs;

cmLandscape();

public:


	virtual uint32 GetNode(uint32 liX,uint32 liZ);

	inline virtual uint32 VertexDataSize(){return 8*miXSteps*miZSteps;};
	inline uint32 Verteces(){return (miXSteps)*(miZSteps);};
	/// This will return a pointer to the landscapes face data array.
	uint16 *FaceData(){return mpQuads;};
	/// This will return the number of quadrilateral faces in the landscape. (actually this appears to be the number of nodes in the face data array.
	uint32 Faces(){return miQuads;};

	/**
	 * \brief Constructor to make Landscape Mesh out of an IMF File.
	 *Will Make a Landscape from an Landscape Array.
	 *
	 */
	cmLandscape(cmLandscapeArray *lpArray);
	/**
	* \brief * This will create a new landscape mesh using the data in lpArray.
	* \param lpArray This is the cmLandscapeArray holding landscape data for this object.
	**/
	cmLandscape(cmLandscape *lpArray);
	/**
	*\brief * This will create a new landscape array to the resolution and size specified.
	* \param liXSteps Number of Nodes to form the landscape along the Landscapes X axis.
	* \param liZSteps Number of Nodes to form the landscape along the Landscapes Z axis.
	* \param lfXSize Size of landscape polygons along the landscapes X axis.
	* \param lfZSize Size of landscape polygons along the landscapes Z axis.
	**/
	cmLandscape(uint32 liXSteps,uint32 liZSteps,float lfXSize,float lfZSize);

	cmLandscape *operator=(cmLandscape *lpNew);

	~cmLandscape();
	/// This will create all the absent data for the landscape. Vertex Positions, Normals, UVs and face data.
	virtual void PrepareLandscape();

	virtual void GenerateVerteces();
	virtual void GenerateUVs();
	virtual void GenerateNormals();
	virtual void GenerateFaces();

	/// This will return the height of the landscape (using interpolation) at the position lfX,lfZ relative to the landscapes 0,0 corner.
	virtual float GetHeightLocal(float lfX,float lfZ);
	/// This will return the height of the landscapes vertex numbered liX,liZ in the array.
	float GetVertexHeight(uint32 liX,uint32 liZ);

	/// This will set the height of the landscapes vertex numbered liX,liZ in the array.
	inline virtual void SetHeight(uint32 liX,uint32 liZ,float lfHeight);

	///Will scale the landscape to fit the new height range.
	void SetHeightRange(float lfRange);

	///Will scale the landscape step size along the X axis to be lfStep.
	void SetXStep(float lfStep);
	///Will scale the landscape step size along the Z axis to be lfStep.
	void SetZStep(float lfStep);
	/// This will reinitialise the landscapes normal values.
	void CreateNormalArray();

	/// This will scale the landscape step size along both the X and Z axis to be lfXStep and lfZStep respectively.
	void SetXZStep(float lfXStep,float lfZStep);

	/// This will randomise the landscape to a maximum height of liheight and then smooth the heights within liSize of each vertex.
	void Randomize(float liHeight,uint8 liSize);
	/// This will just randomise the landscape up to a maximum height of liHeight.
	void Randomize(float liHeight);
	/// This will randomise the landscape, by laying Lines number of random bisecting lines, which raise the landscape by lfHeightRange each. lfHeightRange is 0.001 by default.
	void Randomize(uint32 Lines,float lfHeightRange);

/// This will move the mesh data to the graphics card memory.
void BufferMesh();

/// This will render the mesh directly from graphics memory.
virtual void RenderMesh();

	/// This will return miXSteps.
	uint32 Width(){return miXSteps;};
	/// This will reutrn miZSteps.
	uint32 Length(){return miZSteps;};

	float GetXSize(){return miXSteps*mfXSize;};
	float GetYSize(){return mfHeightRange;};
	float GetZSize(){return miZSteps*mfZSize;};

	void GenerateRandomUVs();

	cmLandscape *Duplicate();
	friend class cLandscapeMeshFile;

};









/// This is the class which the Landscape File is stored in. This can be passed to any of cmLandscape, cLandscapeMeshIndividual or cLandscapeMeshRandom.
class cLandscapeMeshFile : public cmLandscape, public cFile
{

public:
	cLandscapeMeshFile(cmLandscapeArray *lpArray);

friend class cmLandscape;

};

#endif
