
#pragma once


template<uint8 tLevel, class tD> class cVoxelOctTreeLevel : public cVoxelOctTreeBase<tD>
{
private:
	cVoxelOctTreeLevel<tLevel - 1, tD> mcNodes[8];
	uint8 LevelBeneathValid;
public:
	static const uint32 NodeSize(){ return pow(2, tLevel); };
	static const uint8 TreeLevel(){return tLevel;};
	static const uint32 LevelBitMask(){ return 0x1 << tLevel;}
	
	bool ContainsVoxels();
	tD &GetNode(uint32 liX, uint32 liY, uint32 liZ);

	void IterateWholeTree(NodeIterator NodeCheckFunction)override;

	bool GenerateCounts() override;

};

template<class tD> class cVoxelOctTreeLevel<0,tD> : public cVoxelOctTreeBase<tD>
{
private:
		tD mNode;
public:
	static const uint32 NodeSize(){return 1;};
	static const uint8 TreeLevel(){return 0;};

	void IterateWholeTree(NodeIterator NodeCheckFunction) override;

	tD &GetNode(uint32 liX, uint32 liY, uint32 liZ) override;
	bool GenerateCounts() override;
};

