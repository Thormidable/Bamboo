
#pragma once


template<class tD> class cVoxelOctTreeBase : public cVoxelIteratorTypes<tD>
{
public:
	cVoxelOctTreeBase();
	~cVoxelOctTreeBase();

	static cVoxelOctTreeBase<tD> *GetVoxelOctTree(float32 XSize, float32 YSize, float32 ZSize);
	static cVoxelOctTreeBase<tD> *GenerateTree(cMesh *lcMesh);

	virtual tD &GetNode(float32 liX, float32 liY, float32 liZ) = 0;

	virtual void IterateAllLevels(LevelIterator NodeCheckFunction) = 0;
	virtual void IterateAllNodes(NodeIterator NodeCheckFunction) = 0;

	virtual void GenerateCounts() = 0;
	
	virtual cMesh *GenerateMeshFromTree() = 0;

protected:
	struct PolygonInfo
	{
		c3DVf Normal;
		float32 Value;
		c3DVf Verteces[3];
	};

	virtual void GenerateTree(const cLimitedList<PolygonInfo> &lFace) = 0;
};

template<uint8 tLevels,class tD> class cVoxelOctTree  : public cVoxelOctTreeBase<tD>, public cVoxelBaseFunctions
{
public:
	cVoxelOctTreeLevel<tLevels,tD> *mpNodes;
	c3DVf *mpCentres;
	uint32 miNodes;
	c3DVf mNodeHalfDims;
	c3DVu mNodeDims;
public:
	static const uint32 OctSize(){ return pow(2, tLevels); }
	static const float32 InvOctSize(){ return 1.0f/pow(2, tLevels); }

	~cVoxelOctTree();

	void Resize(float32 XSize, float32 YSize, float32 ZSize);
	
	tD &GetNode(float32 liX, float32 liY, float32 liZ) override;

	void GenerateCounts() override;

	void IterateAllLevels(typename cVoxelOctTreeBase<tD>::LevelIterator NodeCheckFunction) override;
	void IterateAllNodes(typename cVoxelOctTreeBase<tD>::NodeIterator NodeCheckFunction) override;

	template<uint8 tTargetLevel, typename FuncType> void IterateAllOneLevel(FuncType lOperate);
	template<uint8 tTargetLevel, typename FuncType> void IterateAllOneLevelCentre(FuncType lOperate,const c3DVf &lcCentre);
	
	cMesh *GenerateMeshFromTree();

	friend class cVoxelOctTreeBase<tD>;
protected:
	
	void GenerateTree(const cLimitedList<PolygonInfo> &lFace);
	
	cVoxelOctTreeLevel<tLevels, tD> &GetSuperNode(float32 liX, float32 liY, float32 liZ);

	cVoxelOctTree(float32 XSize, float32 YSize, float32 ZSize);
	
};



