#ifndef __WTCMESHTREENODE_H__
#define __WTCMESHTREENODE_H__
/**
*\brief This object will store the data for a single item in a cMeshTree().
*This stores the Position, Rotation, Mesh, Texture, Tree Level, for this object.
*/
class cMeshTreeNode
{
 /// This will store the position of this object.
 static float mpStartPos[3];
 /// This will store the rotation vectors for the object.
 static float mpStartRot[9];
public:
 cMeshTreeNode();
 ~cMeshTreeNode();

 /// This will Initialise the objects data.
 void Initialise();

 uint32 miFormat;
 char *mpMesh;
  vMesh *mpMeshPoint;
 char *mpTexture;
  vTexture *mpTexturePoint;
 uint32 miLevel;
 float *mpPosition;
 float *mpRotation;
 /// This will Remove and Delete the Mesh.
 void RemoveMesh();
/// This will Remove and Delete the Texture.
 void RemoveTexture();
/// This will reset the Tree Level.
 void RemoveStackLevel();
/// This will Reset the Position.
 void RemovePosition();
///This will Reset the Rotation.
 void RemoveRotation();
///This will Load a cMeshTreeNode() from an IMF File. FileStream should just have reached the start of the Mesh Tree Node.
 void ReadIMF(ifstream &FileStream);

 /// This will return the Mesh for this object.
 vMesh *Mesh();
/// This will return the Texture for this object.
 vTexture *Texture();
/// This will return the Spatial Size for this object.
 float GetSize();


};

#endif
