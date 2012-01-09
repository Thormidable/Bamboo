#ifndef __WTVMESHTREE_H__
#define __WTVMESHTREE_H__

#if WT_FULL_VERSION_BAMBOO

/**
*\brief This is a virtual class for inherited by cMeshTree().

*/
class vMeshTree : public cMesh //public cFile,
{
public:
 virtual ~vMeshTree(){};

 virtual uint32 Size()=0;
 virtual cMeshTreeNode *NodeList()=0;
 virtual cMeshTreeNode *NodeList(uint32 liCount)=0;


virtual uint32 Vertex(){return 0;};
virtual uint32 Faces(){return 0;};
virtual float *VertexData(){return 0;};
virtual uint16 *FaceData(){return 0;};
virtual float *NormalData(){return 0;};
virtual float *UVData(){return 0;};

virtual void Position(float lfX,float lfY,float lfZ){(void) lfX;(void) lfY;(void) lfZ;};
virtual void PositionX(float lfX){(void) lfX;};
virtual void PositionY(float lfY){(void) lfY;};
virtual void PositionZ(float lfZ){(void) lfZ;};

virtual void BufferMesh(){(void) 0;};
virtual void RenderMesh(){(void) 0;};

virtual void ResetPosition(){(void) 0;};

};

#endif

#endif
