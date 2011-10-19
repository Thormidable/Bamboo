#ifndef __WTVMESH_H__
#define __WTVMESH_H__

/// This is the virtual base class for a cMesh object.
class vMesh : public cFile
{
public:
virtual ~vMesh(){};
/// Will return the number of verteces in the mesh.
virtual uint32 Vertex()=0;
/// Will return the number of Faces in the mesh.
virtual uint32 Faces()=0;
/// Will return a pointer to the vertex position data array.
virtual float *VertexData()=0;
/// Will return a pointer to the face array.
virtual uint16 *FaceData()=0;
/// Will return a pointer to the vertex normal array.
virtual float *NormalData()=0;
/// Will return a pointer to the texture co-ordinate array.
virtual float *UVData()=0;

/// Will move the meshes centre of rotation by lfX,lfY,lfZ.
virtual void Position(float lfX,float lfY,float Z)=0;
/// Will move the meshes centre of rotation by lfX along its X axis.
virtual void PositionX(float lfX)=0;
/// Will move the meshes centre of rotation by lfX along its Y axis.
virtual void PositionY(float lfX)=0;
/// Will move the meshes centre of rotation by lfX along its Z axis.
virtual void PositionZ(float lfX)=0;

/// This will move the mesh data to the graphics card memory.
virtual void BufferMesh()=0;

/// This will render the mesh directly from graphics memory.
virtual void RenderMesh(cVariableStore *lpNew)=0;

/// Will reset the meshes centre of rotation to its original position.
virtual void ResetPosition()=0;

/// Will return the Size of the Mesh.
virtual float GetSize()=0;

/// Will Generate the normal array from faces and verteces.
virtual void CreateNormalArray()=0;
};
#endif
