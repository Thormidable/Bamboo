#ifndef __WTCVOXELMODEL_H__
#define __WTCVOXELMODEL_H__


class cVoxelOctTreeBase
{
public:
	cVoxelOctTreeBase();
	~cVoxelOctTreeBase();

	inline uint8 GetNodeIndex(float &liX,float &liY,float &liZ,float32 siNodeSize);
	inline uint8 GetNodeIndex(float &liX,float &liY,float &liZ);
	virtual uint8 &GetNode(float &liX,float &liY,float &liZ) = 0;

};

class cVoxelOctTree : public cVoxelOctTreeBase
{
public:
	cVoxelOctTreeBase *mpNodes;
	uint32 miNodes;
public:
	cVoxelOctTree(float XSize,float YSize,float ZSize);
	uint8 &GetNode(float liX,float liY,float liZ);

	template<class tLambda> IterateTreeCollision(tLambda NodeCheckFunction, uint8 lpValues[8] = {0,1,2,3,4,5,6,7})
	{
		//TODO : This will need something to order the nodes based on the requirements. This is likely to take different parameters.... 
		for(uint8 liNode = 0;liNode < miNodes;++liNode)
		{
			if (NodeCheckFunction(mpNodes[lpValues[liNode]])) mpNodes[lpValues[liNode]].IterateTreeCollision(NodeCheckFunction,lpValues);
		}
	}

	template<class tLambda> IterateWholeTree(tLambda NodeCheckFunction)
	{
		for(uint8 liNode = 0;liNode < miNodes;++liNode)
		{
			mpNodes[liNode].IterateWholeTree(NodeCheckFunction);
		}
	}

	uint8 &GetNode(float &liX,float &liY,float &liZ) override;

	void GenerateTree(cMesh &lcMesh);
	void SetSurfaceVoxelsFromMesh(cMesh &lcMesh);
	void FloodFillFromEdge();
	~cVoxelOctTree();
};



template<uint8 tLevel> class cVoxelOctTreeLevel : public cVoxelOctTreeBase
{
private:
	static const uint32 NodeSize(){return pow(2,tLevel)};
	static const uint8 TreeLevel(){return tLevel;};

	cVoxelOctTreeLevel<tLevel-1> mcNodes[8];
	uint8 LevelBeneathValid;

	template<class tLambda> IterateTreeCollision(tLambda NodeCheckFunction, uint8 lpValues[8] = {0,1,2,3,4,5,6,7})
	{
		for(uint8 liNode = 0;liNode < 8;++liNode)
		{
			cVoxelOctTreeLevel<tLevel-1> &lcCurrent = mcNodes[lpValues[liNode]];
			if (lcCurrent.ContainsVoxels() && NodeCheckFunction(lcCurrent)) lcCurrent.IterateTreeCollision(NodeCheckFunction,lpValues);
		}
	}

	template<class tLambda> IterateWholeTree(tLambda NodeCheckFunction)
	{
		for(uint8 liNode = 0;liNode < miNodes;++liNode)
		{
			mpNodes[liNode].IterateWholeTree(NodeCheckFunction);
		}
	}


	bool ContainsVoxels()
	{
		return LevelBeneathValid > 0;
	}

	uint8 &GetNode(float &liX,float &liY,float &liZ) override{GetNodeInternal(liX,liY,liZ);}
	uint8 &GetNodeInternal(float liX,float liY,float liZ)
	{
		uint8 liNode = GetNodeIndex(liX,liY,liZ,siNodeSize);
		return mcNodes[liNode].GetNodeInternal(liX,liY,liZ);
	}

};

template<> class cVoxelOctTreeLevel<0> : public cVoxelOctTreeBase
{
private:
	cVoxelOctTreeLevel<0>
	uint8 miValues[8];
	uint8 miVoxelsContained;
public:
	static const uint32 NodeSize(){return 1;};
	static const uint8 TreeLevel(){return 0;};

	template<class tLambda> IterateTreeCollision(tLambda NodeCheckFunction, uint8 lpValues[8] = {0,1,2,3,4,5,6,7})
	{
		for(uint8 liNode = 0;liNode < 8;++liNode)
		{
			//Check Each Node For Collision
		}
	}

	template<class tLambda> IterateWholeTree(tLambda NodeCheckFunction)
	{
		for(uint8 liNode = 0;liNode < 8;++liNode)
		{
			NodeCheckFunction(miValues[liNode]);
		}
	}
	

	bool ContainsVoxels()
	{
		return miVoxelsContained > 0;
	}

	uint8 &GetNode(float &liX,float &liY,float &liZ) override{GetNodeInternal(liX,liY,liZ);}

	uint8 &GetNodeInternal(float liX,float liY,float liZ)
	{
		uint8 liNode = GetNodeIndex(liX,liY,liZ);
		return miValues[liNode];
	}
};



/**
* \brief A standard Textured Model renderable object.
*/
class cVoxelModel :public cModel
{
	cVoxelOctTree mcVoxelModel;
	
public:
 /// cModel constructor
 cVoxelModel();
 /// cModel constructor. Will be owned by lpRenderer.
 cVoxelModel(vRenderNode *lpRenderer);
 /// cModel constructor. Will be owned by the cRenderNode of the cCamera lpCamera.
 cVoxelModel(cCamera *lpCamera);

	

};

#endif
