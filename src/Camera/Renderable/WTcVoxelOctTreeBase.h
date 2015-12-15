
#pragma once

template<class tD> class cVoxelOctTreeBase
{
public:
	cVoxelOctTreeBase();
	~cVoxelOctTreeBase();
	
	typedef bool(*CollisionCheckFunction)(cVoxelOctTreeBase &);
	typedef void(*NodeIterator)(tD &);

	virtual tD &GetNode(uint32 liX, uint32 liY, uint32 liZ) = 0;
	
	virtual void IterateWholeTree(NodeIterator NodeCheckFunction) = 0;

	virtual bool GenerateCounts() = 0;
};

