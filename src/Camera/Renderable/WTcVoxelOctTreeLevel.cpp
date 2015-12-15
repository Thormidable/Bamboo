
#include "../../WTBamboo.h"

template<uint8 tLevel, class tD> bool cVoxelOctTreeLevel<tLevel, tD>::ContainsVoxels()
{
	return LevelBeneathValid > 0;
}

template<uint8 tLevel, class tD> bool cVoxelOctTreeLevel<tLevel, tD>::GenerateCounts()
{
	LevelBeneathValid = 0;
	for (uint8 liNode = 0; liNode < 8; ++liNode)
	{
		if(mcNodes[liNode].GenerateCounts()) LevelBeneathValid++;
	}
	return LevelBeneathValid > 0;
}

template<uint8 tLevel, class tD> void cVoxelOctTreeLevel<tLevel, tD>::IterateWholeTree(NodeIterator NodeCheckFunction)
{
	for (uint8 liNode = 0; liNode < 8; ++liNode)
	{
		mcNodes[liNode].IterateWholeTree(NodeCheckFunction);
	}
}

template<uint8 tLevel, class tD> tD &cVoxelOctTreeLevel<tLevel, tD>::GetNode(uint32 liX, uint32 liY, uint32 liZ)
{
	uint32 lReturn = 0;
	if (liX&LevelBitMask()) lReturn += 1;
	if (liY&LevelBitMask()) lReturn += 2;
	if (liZ&LevelBitMask()) lReturn += 4;
	return mcNodes[lReturn].GetNode(liX,liY,liZ);
}


template<class tD> bool cVoxelOctTreeLevel<0, tD>::GenerateCounts() { return mNode>0; }

template<class tD> tD &cVoxelOctTreeLevel<0, tD>::GetNode(uint32 liX, uint32 liY, uint32 liZ) { return mNode; }


template<class tD> void cVoxelOctTreeLevel<0, tD>::IterateWholeTree(NodeIterator NodeCheckFunction)
{
	for (uint8 liNode = 0; liNode < 8; ++liNode)
	{
		NodeCheckFunction(mNode);
	}
}

template class cVoxelOctTreeLevel<8, uint8 >;
template class cVoxelOctTreeLevel<7, uint8 >;
template class cVoxelOctTreeLevel<6, uint8 >;
template class cVoxelOctTreeLevel<5, uint8 >;
template class cVoxelOctTreeLevel<4, uint8 >;
template class cVoxelOctTreeLevel<3, uint8 >;
template class cVoxelOctTreeLevel<2, uint8 >;
template class cVoxelOctTreeLevel<1, uint8 >;
template class cVoxelOctTreeLevel<0, uint8 >;

