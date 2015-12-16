
#include "../../WTBamboo.h"

template<uint8 tLevel, class tD> bool cVoxelOctTreeLevelGeneric<tLevel, tD>::GenerateCounts()
{
	bool lbPartial = false;
	bool lbEmpty = true;

	if (mcNodes[0].GenerateCounts())
	{
		if (mcNodes[0].IsDense())
		{
			lbEmpty = false;
			LevelBeneathValid = 0xFF;
		}
		else 
		{
			lbPartial = true; 
			LevelBeneathValid = 1;
		}
	}
	else
	{
		LevelBeneathValid = 0;
	}

	for (uint8 liNode = 1; liNode < 8; ++liNode)
	{
		mcNodes[liNode].GenerateCounts();

		if (!lbPartial)
		{
			if ((lbEmpty && !mcNodes[liNode].IsEmpty()) || (!lbEmpty && !mcNodes[liNode].IsDense()))
			{
				lbPartial = true; 
				LevelBeneathValid = 1;
			}
		}
	}

	return LevelBeneathValid > 0;
}

template<class tD> uint8 cVoxelOctTreeLevel<1,tD>::NodeLayout(){ return LevelBeneathValid; };
template<class tD> bool cVoxelOctTreeLevel<1, tD>::GenerateCounts()
{
	uint8 lID = 1;
	for (uint8 liNode = 0; liNode < 8; ++liNode)
	{
		if (mcNodes[liNode].GenerateCounts())
		{
			LevelBeneathValid += lID;
		}
		lID <<= 1;
	}

	return LevelBeneathValid > 0;
}

template<uint8 tLevel, class tD> void cVoxelOctTreeLevelGeneric<tLevel, tD>::IterateAllLevels(LevelIterator LevelCheckFunction, VoxelSkip lSkip)
{
	LevelCheckFunction(this);
	for (uint8 liNode = 0; liNode < 8; ++liNode)
	{
		if(!mcNodes[liNode].ShouldSkip(lSkip)) mcNodes[liNode].IterateAllLevels(LevelCheckFunction, lSkip);
	}
}

template<uint8 tLevel, class tD> void cVoxelOctTreeLevelGeneric<tLevel, tD>::IterateAllNodes(NodeIterator NodeCheckFunction, VoxelSkip lSkip)
{
	for (uint8 liNode = 0; liNode < 8; ++liNode)
	{
		if (!mcNodes[liNode].ShouldSkip(lSkip)) mcNodes[liNode].IterateAllNodes(NodeCheckFunction, lSkip);
	}
}

template<uint8 tLevel, class tD> tD &cVoxelOctTreeLevelGeneric<tLevel, tD>::GetNode(uint32 liX, uint32 liY, uint32 liZ)
{
	return mcNodes[GetNodeID(liX,liY,liZ)].GetNode(liX,liY,liZ);
}




template<class tD> bool cVoxelOctTreeLevel<0, tD>::GenerateCounts() { return mNode>0; }

template<class tD> tD &cVoxelOctTreeLevel<0, tD>::GetNode(uint32 liX, uint32 liY, uint32 liZ) { return mNode; }

template<class tD> void cVoxelOctTreeLevel<0, tD>::IterateAllLevels(LevelIterator LevelCheckFunction, VoxelSkip lSkip)
{

}
template<class tD> void cVoxelOctTreeLevel<0, tD>::IterateAllNodes(NodeIterator LevelCheckFunction, VoxelSkip lSkip)
{
	LevelCheckFunction(mNode);
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

