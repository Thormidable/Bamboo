
#include "../../WTBamboo.h"

template<class tD> bool cVoxelOctTreeLevelBase<tD>::ContainsVoxels()
{
	return LevelBeneathValid > 0;
}

template<uint8 tLevel, class tD> bool cVoxelOctTreeLevelGeneric<tLevel, tD>::GenerateCounts()
{
	LevelBeneathValid = 0;
	uint8 lID = 0x1;
	for (uint8 liNode = 0; liNode < 8; ++liNode)
	{
		if (mcNodes[liNode].GenerateCounts())
		{			
			LevelBeneathValid+=lID;
			lID << 1;
		}
	}
	return LevelBeneathValid > 0;
}

template<uint8 tLevel, class tD> void cVoxelOctTreeLevelGeneric<tLevel, tD>::IterateAllLevels(LevelIterator LevelCheckFunction)
{
	for (uint8 liNode = 0; liNode < 8; ++liNode)
	{
		mcNodes[liNode].IterateAllLevels(LevelCheckFunction);
	}
}

template<uint8 tLevel, class tD> void cVoxelOctTreeLevelGeneric<tLevel, tD>::IterateAllNodes(NodeIterator NodeCheckFunction)
{
	for (uint8 liNode = 0; liNode < 8; ++liNode)
	{
		mcNodes[liNode].IterateAllNodes(NodeCheckFunction);
	}
}

template<uint8 tLevel, class tD> tD &cVoxelOctTreeLevelGeneric<tLevel, tD>::GetNode(uint32 liX, uint32 liY, uint32 liZ)
{
	return mcNodes[GetNodeID(liX,liY,liZ)].GetNode(liX,liY,liZ);
}




template<class tD> bool cVoxelOctTreeLevel<0, tD>::GenerateCounts() { return mNode>0; }

template<class tD> tD &cVoxelOctTreeLevel<0, tD>::GetNode(uint32 liX, uint32 liY, uint32 liZ) { return mNode; }

template<class tD> void cVoxelOctTreeLevel<0, tD>::IterateAllLevels(LevelIterator LevelCheckFunction)
{
	
}


template<class tD> void cVoxelOctTreeLevel<0, tD>::IterateAllNodes(NodeIterator NodeCheckFunction)
{
	for (uint8 liNode = 0; liNode < 8; ++liNode)
	{
		NodeCheckFunction(mNode);
	}
}

template class cVoxelOctTreeLevelGeneric<8, uint8 >;
template class cVoxelOctTreeLevelGeneric<7, uint8 >;
template class cVoxelOctTreeLevelGeneric<6, uint8 >;
template class cVoxelOctTreeLevelGeneric<5, uint8 >;
template class cVoxelOctTreeLevelGeneric<4, uint8 >;
template class cVoxelOctTreeLevelGeneric<3, uint8 >;
template class cVoxelOctTreeLevelGeneric<2, uint8 >;
template class cVoxelOctTreeLevelGeneric<1, uint8 >;

template class cVoxelOctTreeLevel<8, uint8 >;
template class cVoxelOctTreeLevel<7, uint8 >;
template class cVoxelOctTreeLevel<6, uint8 >;
template class cVoxelOctTreeLevel<5, uint8 >;
template class cVoxelOctTreeLevel<4, uint8 >;
template class cVoxelOctTreeLevel<3, uint8 >;
template class cVoxelOctTreeLevel<2, uint8 >;
template class cVoxelOctTreeLevel<1, uint8 >;
template class cVoxelOctTreeLevel<0, uint8 >;

