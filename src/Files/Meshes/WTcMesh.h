#ifndef __WTCMESH_H__
#define __WTCMESH_H__

/// This indicates that the model has vertex position dat ato be used when rendering.
#define WT_MESH_FORMAT_VERTECES 0x1
/// This indicates that the model has texture co-ordinates to be used when rendering.
#define WT_MESH_FORMAT_UVS 0x2
/// This indicates that the model has vertex normal data to be used when rendering.
#define WT_MESH_FORMAT_NORMALS 0x4
/// This indicates that the model has eh? WTF? Why did i put this here?
#define WT_MESH_FORMAT_POSITIVE 0x8

/// This is a temporary storage class to ease transformation of data from the hdd to the cMesh class.
class cMeshArray : public cIMFLoader
{
public:
 cMeshArray();
 // This is a pointer to the array holding vertex position data for the mesh.
  float *mpVertex;
 // This is a pointer to the array holding vertex normal vector data for the mesh.
  float *mpNormals;
// This is a pointer to the array holding texture co-ordinates for the mesh.
  float *mpUV;
 // This is an array holding the face data (list of verteces used to form each polygon. see cMesh::mpFaces.
  uint16 *mpFaces;
 // This stores the number of verteces in this mesh.
  uint32 miVertex;
 // This stores the number of faces in this mesh.
  uint32 miFaces;
 // This string stores either the filename or file reference.
  char *mpRef;
///This will load the data from an IMF File.
void LoadIMF(ifstream &FileStream);

  ~cMeshArray();
};
/**
* \brief This class stores the data for a 3D model.
* \param lpMesh This is a pointer to a cMeshArray object which holds the mesh data for this object.
* This holds the data for a 3D model in a format suitable for rendering. The data is stored in 2 large arrays with the face data stored in the array mpFaces while all the remaining data stored is stored consecutively in mpVertex. mpVertex points to the start of the array while mpNormals and mpUV point to the start of their respective data blocks.
*/
class cMesh : public cFile
{

protected:
/**
* \brief This stores the format which determines what data is used to render the model.
* The flags in this variable determine what data is present to be used by the renderer * relative to this object. see flags WT_MESH_FORMAT_VERTECES, WT_MESH_FORMAT_UVS,
* WT_MESH_FORMAT_NORMALS and WT_MESH_FORMAT_POSITIVE.

*/
uint8 miFormat;
// This is a pointer to the array holding vertex position data for the mesh.
  float *mpVertex;
// This is a pointer to the array holding vertex normal vector data for the mesh.
  float *mpNormals;
// This is a pointer to the array holding texture co-ordinates for the mesh.
  float *mpUV;
 // This is an array holding the face data (list of verteces used to form each polygon. see cMesh::mpFaces.
  uint16 *mpFaces;
 // This stores the number of verteces in this mesh.
  uint32 miVertex;
 // This stores the number of faces in this mesh.
  uint32 miFaces;
 // This string stores either the filename or file reference.

// This stores the 3D vector of the total change in the models centre of rotation.
float miModelCentre[3];
//This is the minimum radius required to forma sphere containing this object.
float mfSize;

public:

GLuint mBuffer1;
GLuint mBuffer2;

	/// This will create an empty mesh. No verteces, no faces, nothing.
	cMesh();
	/// This will load the data in lpMesh to be used by this object.
	cMesh(cMeshArray *lpMesh);
	~cMesh();

	/// This will return the models rendering format.
       void SetFormat();

	/**
	* \brief This will produce an array of vertex normal data for a mesh.
	* This will require the mesh to have vertex and face data and produces
	* normal vectors for all the verteces.
	*/
       void CreateNormalArray();

 /// This will return the number of verteces in the vertex position array mpVertex.
 uint32 Vertex();
/// This will return the number of faces in the face array mpFaces.
 uint32 Faces();
 /// This will return a pointer to the vertex position array.
 float *VertexData();
/// This will return a pointer to the face array..
uint16 *FaceData();
 /// This will return a pointer to the array of vertex normals.
 float *NormalData();
 /// This will return a pointer to the array of texture co-ordinates.
 float *UVData();

 /// This will move the objects centre of rotation by lfX,lfY,lfZ.
 void Position(float lfX,float lfY,float lfZ);
 /// This will move the objects centre of rotation along its X axis lfX distance.
 void PositionX(float lfX);
/// This will move the objects centre of rotation along its Y axis lfY distance.
void PositionY(float lfY);
/// This will move the objects centre of rotation along its Z axis lfZ distance.
 void PositionZ(float lfZ);
 /// This will restore the objects original centre of rotation.
 void ResetPosition();

// This will move the mesh data to the graphics card memory.
void BufferMesh();

// This will render the mesh directly from graphics memory.
void RenderMesh();

/// This will return the size of the Mesh. Size being the radius of the sphere required to contain the cMesh object.
float GetSize();
///This will calculate the size of the Mesh. Size being the radius of the sphere required to contain the cMesh object.
void FindSize();

};
#endif
