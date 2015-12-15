
#pragma once

template<uint8 tLevel, class tD> class cVoxelOctTreeLevelGeneric;


template<uint8 tLevel, class tD> class cVoxelOctTreeLevel : public cVoxelOctTreeLevelGeneric<tLevel, tD>
{
public:
	template<uint8 tTargetLevel, typename FuncType> void IterateAllOneLevel(FuncType lOperate)
	{
		if (tLevel == tTargetLevel)
		{
			lOperate(*reinterpret_cast<cVoxelOctTreeLevel<tTargetLevel, tD>*>(this));
			return;
		}
		for (uint8 lNode = 0; lNode < 8; ++lNode)
		{
			mcNodes[lNode].IterateAllOneLevel<tTargetLevel>(lOperate);
		}
	}

	template<uint8 tTargetLevel, typename FuncType> void IterateAllOneLevelCentre(FuncType lOperate,c3DVf lcCentre)
	{
		if (tLevel == tTargetLevel)
		{
			lOperate(*reinterpret_cast<cVoxelOctTreeLevel<tTargetLevel, tD>*>(this),lcCentre);
			return;
		}
		for (uint8 lNode = 0; lNode < 8; ++lNode)
		{ 
			mcNodes[lNode].IterateAllOneLevelCentre<tTargetLevel>(lOperate, NewCentre(lcCentre, lNode));
		}
	}
};

template<uint8 tLevel, class tD> class cVoxelOctTreeLevelGeneric : public cVoxelOctTreeLevelBase<tD>, public cVoxelIteratorTypes<tD>, public cVoxelBaseFunctions
{
protected:
	cVoxelOctTreeLevel<tLevel - 1, tD> mcNodes[8];
	
public:
	static const uint32 NodeSize(){ return pow(2, tLevel); };
	static const float32 HalfNodeSize(){ return pow(2, tLevel)*0.5f; };
	static const uint8 TreeLevel(){return tLevel;};
	static const uint32 LevelBitMask(){ return 0x1 << tLevel;}
	static const c3DVf NewCentre(const c3DVf &lcCentre, uint8 lNodeID)
	{
		c3DVf lcTemp;
		GetXFromNodeID(lNodeID) ? lcTemp[0] = lcCentre[0] + HalfNodeSize() : lcTemp[0] = lcCentre[0] - HalfNodeSize();
		GetYFromNodeID(lNodeID) ? lcTemp[1] = lcCentre[1] + HalfNodeSize() : lcTemp[1] = lcCentre[1] - HalfNodeSize();
		GetZFromNodeID(lNodeID) ? lcTemp[2] = lcCentre[2] + HalfNodeSize() : lcTemp[2] = lcCentre[2] - HalfNodeSize();
		return lcTemp;
	};

	static inline uint8 GetNodeMask(uint32 lX, uint32 lY, uint32 lZ)
	{
		return GetNodeMask(lX&LevelBitMask(), lY&LevelBitMask(), lZ&LevelBitMask());
	}
	
	tD &GetNode(uint32 liX, uint32 liY, uint32 liZ);

	void IterateAllLevels(LevelIterator NodeCheckFunction);
	void IterateAllNodes(NodeIterator NodeCheckFunction);



	bool GenerateCounts();

};

template<class tD> class cVoxelOctTreeLevel<0, tD> : public cVoxelIteratorTypes<tD>
{
private:
		tD mNode;
public:
	
	static const uint32 NodeSize(){ return pow(2, 0); };
	static const uint8 TreeLevel(){ return 0; };
	static const uint32 LevelBitMask(){ return 0x1 << 0; }

	void IterateAllLevels(LevelIterator NodeCheckFunction);
	void IterateAllNodes(NodeIterator NodeCheckFunction);

	template<uint8 tTargetLevel, typename FuncType> void IterateAllOneLevel(FuncType lOperate)
	{
		if (0 == tTargetLevel)
		{
			lOperate(*reinterpret_cast<cVoxelOctTreeLevel<tTargetLevel, tD>*>(this));
			return;
		}
	}

	template<uint8 tTargetLevel, typename FuncType> void IterateAllOneLevelCentre(FuncType lOperate,c3DVf lcCentre)
	{
		if (0 == tTargetLevel)
		{
			lOperate(*reinterpret_cast<cVoxelOctTreeLevel<tTargetLevel, tD>*>(this),lcCentre);
			return;
		}
	}

	tD &GetNode(uint32 liX, uint32 liY, uint32 liZ);
	bool GenerateCounts();
};

