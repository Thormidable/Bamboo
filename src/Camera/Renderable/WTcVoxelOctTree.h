
#pragma once

template<class tD> class cVoxelOctTree 
{
public:
	cVoxelOctTreeBase<tD> *mpNodes;
	c3DVf *mpCentres;
	uint32 miNodes;
	uint32 miOctTreeSize;
	float32 miInvOctTreeSize;
	c3DVf mNodeHalfDims;
	c3DVu mNodeDims;
public:
	cVoxelOctTree();

	cVoxelOctTree(float32 XSize, float32 YSize, float32 ZSize);
	~cVoxelOctTree();

	void Resize(float32 XSize, float32 YSize, float32 ZSize);
	
	cVoxelOctTreeBase<tD> &GetSuperNode(float32 liX, float32 liY, float32 liZ);
	tD &GetNode(float32 liX, float32 liY, float32 liZ);
	
	void GenerateTree(cMesh &lcMesh);
	void ZeroAllNodes();

	void GenerateCounts();

	void IterateWholeTree(typename cVoxelOctTreeBase<tD>::NodeIterator NodeCheckFunction);
	
	cMesh *GenerateMesh();
};



