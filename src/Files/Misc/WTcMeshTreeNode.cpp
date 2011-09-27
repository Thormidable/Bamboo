#include "../../WTDivWin.h"

float cMeshTreeNode::mpStartPos[3]={0.0f,0.0f,0.0f};
float cMeshTreeNode::mpStartRot[9]={1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f};

void cMeshTreeNode::Initialise()
{
 miFormat=0;
 mpMesh=0;
 mpTexture=0;
 miLevel=0;
 mpPosition=0;
 mpRotation=0;
}

cMeshTreeNode::cMeshTreeNode()
{
 Initialise();
}

cMeshTreeNode::~cMeshTreeNode()
{
 RemoveMesh();
 RemoveTexture();
 RemoveStackLevel();
 RemovePosition();
 RemoveRotation();
}

void cMeshTreeNode::RemoveMesh()
{if(mpMesh) {delete []mpMesh; mpMesh=0;} miFormat=miFormat&(!WT_MESHTREE_MESH); mpMeshPoint=0;}

void cMeshTreeNode::RemoveTexture()
{if(mpTexture) {delete []mpTexture; mpTexture=0; miFormat=miFormat&(!WT_MESHTREE_TEXTURE); mpTexturePoint=0;}}

void cMeshTreeNode::RemoveStackLevel()
{miLevel=0;
 miFormat=miFormat&(!WT_MESHTREE_LEVEL);
}

void cMeshTreeNode::RemovePosition()
{if(mpPosition) {delete []mpPosition; mpPosition=0; miFormat=miFormat&(!WT_MESHTREE_POSITION);}}

void cMeshTreeNode::RemoveRotation()
{if(mpRotation) {delete []mpRotation; mpRotation=0; miFormat=miFormat&(!WT_MESHTREE_ROTATION);}}


void cMeshTreeNode::ReadIMF(ifstream &FileStream)
{
 uint32 liTemp;
 //Write the Format
 FileStream.read((int8*) &miFormat,sizeof(uint32));
 if(miFormat<WT_MESHTREE_TOPVALUE)
 {
  //Ignore the uint32 holding the size of the Node
  FileStream.read((int8*) &liTemp,sizeof(uint32));

  //If there is a model Reference Read it
  if(miFormat&WT_MESHTREE_MESH)
  {
   FileStream.read((int8*) &liTemp,sizeof(uint32));
   mpMesh=new char[liTemp+1];
   FileStream.read(mpMesh,sizeof(int8)*liTemp);
   mpMesh[liTemp]=0;
   mpMeshPoint=_GET_FILE(vMesh,mpMesh);
  }

  //If there is a Texture Reference Write it
  if(miFormat&WT_MESHTREE_TEXTURE)
  {
   FileStream.read((int8*) &liTemp,sizeof(uint32));
   mpTexture=new char[liTemp+1];
   FileStream.read(mpTexture,sizeof(int8)*liTemp);
   mpTexture[liTemp]=0;
   mpTexturePoint=_GET_FILE(vTexture,mpTexture);
  }

  //If there is a Level Command read it
  if(miFormat&WT_MESHTREE_LEVEL) {FileStream.read((int8*) &miLevel,sizeof(uint32));}
  //If there is a Position read it
  if(miFormat&WT_MESHTREE_POSITION) {mpPosition=new float[3];FileStream.read((int8*) mpPosition,sizeof(float)*3);}
  //If there is a Rotation read it
  if(miFormat&WT_MESHTREE_ROTATION) {mpRotation=new float[9]; FileStream.read((int8*) mpRotation,sizeof(float)*9);}
 }
 else
 {
  FileStream.read((int8*) &liTemp,sizeof(uint32));
  FileStream.ignore(liTemp);
  miFormat=0;
  mpMesh=0;
  mpTexture=0;
  miLevel=0;
  mpPosition=0;
  mpRotation=0;
 }
}

vMesh *cMeshTreeNode::Mesh()
{
if(mpMeshPoint) return mpMeshPoint;
if(mpMesh)
{
 mpMeshPoint=_GET_FILE(vMesh,mpMesh);
 return mpMeshPoint;
}
return 0;

}

vTexture *cMeshTreeNode::Texture()
{
if(mpTexturePoint) return mpTexturePoint;
if(mpTexture)
{
 mpTexturePoint=_GET_FILE(vTexture,mpTexture);
 return mpTexturePoint;
}
return 0;
}

float cMeshTreeNode::GetSize()
{
if(Mesh()) return Mesh()->GetSize();
return 0.0f;
}