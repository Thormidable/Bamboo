
#include "../../WTBamboo.h"

template<class tD> cVoxelOctTreeBase<tD>::cVoxelOctTreeBase()
{

}

template<class tD> cVoxelOctTreeBase<tD>::~cVoxelOctTreeBase()
{

}

template class cVoxelOctTreeBase<uint8>;


template<uint8 tLevels, class tD> cVoxelOctTree<tLevels,tD>::cVoxelOctTree(float32 XSize, float32 YSize, float32 ZSize) : mpNodes(nullptr), mpCentres(nullptr)
{
	Resize(XSize, YSize, ZSize);
}

template<class tD> cVoxelOctTreeBase<tD> *cVoxelOctTreeBase<tD>::GetVoxelOctTree(float32 XSize, float32 YSize, float32 ZSize)
{
	static const uint8 sMinimumLevels = 4;
	static const uint8 sMaxLevels = 8;

	//Calculate Levels required for minimum dimension (to allow efficient generation of non cubic objects.
	float32 lfMin = min(min(XSize, YSize), ZSize);
	uint32 liLevels = 0;
	while (pow(2, ++liLevels) < lfMin);
	liLevels = max(min(liLevels, sMaxLevels), sMinimumLevels);

	int lT;
	switch (liLevels)
	{
	case 4:
		lT = sizeof(cVoxelOctTreeLevel<4, tD>);
		return new cVoxelOctTree<4, tD>(XSize, YSize, ZSize);
	case 5:
		lT = sizeof(cVoxelOctTreeLevel<5, tD>);
		return new cVoxelOctTree<5, tD>(XSize, YSize, ZSize);
	case 6:
		lT = sizeof(cVoxelOctTreeLevel<6, tD>);
		return new cVoxelOctTree<6, tD>(XSize, YSize, ZSize);
	case 7:
		lT = sizeof(cVoxelOctTreeLevel<7, tD>);
		return new cVoxelOctTree<7, tD>(XSize, YSize, ZSize);
	case 8:
		lT = sizeof(cVoxelOctTreeLevel<8, tD>);
		return new cVoxelOctTree<8, tD>(XSize, YSize, ZSize);
	default:
		return nullptr;
	}
}

template<uint8 tLevels, class tD> void cVoxelOctTree<tLevels,tD>::Resize(float32 XSize, float32 YSize, float32 ZSize)
{
	delete[]mpNodes;
	delete[]mpCentres;

	mNodeDims.X(static_cast<uint32>(ceil(XSize / OctSize())));
	mNodeDims.Y(static_cast<uint32>(ceil(YSize / OctSize())));
	mNodeDims.Z(static_cast<uint32>(ceil(ZSize / OctSize())));

	miNodes = mNodeDims.X();
	miNodes *= mNodeDims.Y();
	miNodes *= mNodeDims.Z();

	mpNodes = new cVoxelOctTreeLevel<tLevels, tD>[miNodes];

	// Generate Centre Points for Each 'node'
	c3DVf lStepStart;
	lStepStart.X(-(static_cast<float32>((mNodeDims.X() - 1)*OctSize()) / 2.0f));
	lStepStart.Y(-(static_cast<float32>((mNodeDims.Y() - 1)*OctSize()) / 2.0f));
	lStepStart.Z(-(static_cast<float32>((mNodeDims.Z() - 1)*OctSize()) / 2.0f));

	mpCentres = new c3DVf[miNodes];
	uint32 lCentre = 0;
	for (uint32 lXC = 0; lXC < mNodeDims.X(); ++lXC)
	{
		for (uint32 lYC = 0; lYC < mNodeDims.Y(); ++lYC)
		{
			for (uint32 lZC = 0; lZC < mNodeDims.Z(); ++lZC)
			{
				mpCentres[lCentre].X(lStepStart.X() + static_cast<float32>(OctSize()*lXC));
				mpCentres[lCentre].Y(lStepStart.Y() + static_cast<float32>(OctSize()*lYC));
				mpCentres[lCentre].Z(lStepStart.Z() + static_cast<float32>(OctSize()*lZC));
			}
		}

	}

	mNodeHalfDims.X(OctSize()*mNodeDims[0] / 2);
	mNodeHalfDims.Y(OctSize()*mNodeDims[1] / 2);
	mNodeHalfDims.Z(OctSize()*mNodeDims[2] / 2);

}

template<uint8 tLevels, class tD> cVoxelOctTreeLevel<tLevels,tD> &cVoxelOctTree<tLevels,tD>::GetSuperNode(float32 liX, float32 liY, float32 liZ)
{
	uint32 lX = min((static_cast<float32>(liX + mNodeHalfDims[0]) * InvOctSize()),mNodeDims[0]);
	uint32 lY = min((static_cast<float32>(liY + mNodeHalfDims[1]) * InvOctSize()), mNodeDims[1]);
	uint32 lZ = min((static_cast<float32>(liZ + mNodeHalfDims[2]) * InvOctSize()), mNodeDims[2]);

	return mpNodes[lX + lY*mNodeDims[0] + lZ*mNodeDims[0] * mNodeDims[1]];
}

template<uint8 tLevels, class tD> tD &cVoxelOctTree<tLevels,tD>::GetNode(float32 liX, float32 liY, float32 liZ)
{
	uint32 lX = static_cast<uint32>((liX + mNodeHalfDims[0])) % OctSize();
	uint32 lY = static_cast<uint32>((liY + mNodeHalfDims[1])) % OctSize();
	uint32 lZ = static_cast<uint32>((liZ + mNodeHalfDims[2])) % OctSize();

	return GetSuperNode(liX, liY, liZ).GetNode(lX, lY, lZ);
}

template<uint8 tLevels, class tD> void cVoxelOctTree<tLevels,tD>::GenerateCounts()
{
	for (uint32 lNode = 0; lNode < miNodes; ++lNode)
	{
		mpNodes[lNode].GenerateCounts();
	}
}

template<class tD> cVoxelOctTreeBase<tD> *cVoxelOctTreeBase<tD>::GenerateTree(cMesh *lcMeshIn)
{
	cMesh &lcMesh = *lcMeshIn;

	//PreCalculations for RayCasting

	cLimitedList<PolygonInfo> lFace(lcMesh.Faces());

	c3DVf lMaxSize(0, 0, 0);

	for (uint32 lPolygon = 0; lPolygon < lcMesh.Faces(); ++lPolygon)
	{
		uint16 *lVertexIDs = lcMesh.Face(lPolygon);
		lFace[lPolygon].Verteces[0] = lcMesh.Vertex(lVertexIDs[0]);
		lFace[lPolygon].Verteces[1] = lcMesh.Vertex(lVertexIDs[1]);
		lFace[lPolygon].Verteces[2] = lcMesh.Vertex(lVertexIDs[2]);

		c3DVf lV[2];
		lV[0] = lFace[lPolygon].Verteces[1] - lFace[lPolygon].Verteces[0];
		lV[1] = lFace[lPolygon].Verteces[2] - lFace[lPolygon].Verteces[0];

		lFace[lPolygon].Normal = lV[0] * lV[1];
		lFace[lPolygon].Normal.Normalise();
		lFace[lPolygon].Value = lFace[lPolygon].Normal.Dot(lFace[lPolygon].Verteces[0]);

		for (uint32 lV = 0; lV < 3; ++lV)
		{
			if (lMaxSize.X() < abs(lFace[lPolygon].Verteces[lV].X())) lMaxSize.X(abs(lFace[lPolygon].Verteces[lV].X()));
			if (lMaxSize.Y() < abs(lFace[lPolygon].Verteces[lV].Y())) lMaxSize.Y(abs(lFace[lPolygon].Verteces[lV].Y()));
			if (lMaxSize.Z() < abs(lFace[lPolygon].Verteces[lV].Z())) lMaxSize.Z(abs(lFace[lPolygon].Verteces[lV].Z()));
		}
	}

	cVoxelOctTreeBase<tD> *lpNewObject = GetVoxelOctTree(lMaxSize.X(), lMaxSize.Y(), lMaxSize.Z());

	lpNewObject->GenerateTree(lFace);

	return lpNewObject;
}

template<uint8 tLevels, class tD> void cVoxelOctTree<tLevels, tD>::GenerateTree(const cLimitedList<PolygonInfo> &lFace)
{
	IterateAllNodes([](tD &lcValue){lcValue = 1; });

	//Do RayCasts
	c3DVf lcStart;
	lcStart.Z(0.0f);
	cLimitedList<c3DVf> lcCollisions(50);
	for (float32 lX = -mNodeHalfDims[0]; lX < mNodeHalfDims[0]; lX+=1.0f)
	{
		lcStart.X(lX);
		for (float32 lY = -mNodeHalfDims[1]; lY < mNodeHalfDims[1]; lY += 1.0f)
		{
			lcStart.Y(lY);
			lcCollisions.SetItems(0);
			
			for (uint32 lPolygon = 0; lPolygon < lFace.Items(); ++lPolygon)
			{
				const PolygonInfo &lPoly = lFace[lPolygon];
				float32 lZ = (lPoly.Value - lPoly.Normal.Dot(lcStart)) / lPoly.Normal[2];
				
				c3DVf lcCollision(lcStart.X(), lcStart.Y(), lZ);

				c3DVf lV[3];
				lV[0] = lPoly.Verteces[0] - lcCollision;
				lV[1] = lPoly.Verteces[1] - lcCollision;
				lV[2] = lPoly.Verteces[2] - lcCollision;

				float32 lfAngle = lV[0].Angle(lV[1]) + lV[1].Angle(lV[2]) + lV[0].Angle(lV[2]);

				if (lfAngle >= 2 * WT_PI*0.999)
				{
					lcCollisions.Add(lcCollision);
				}
			}

			if (lcCollisions.Items() % 2 > 0)
			{
				throw; 
			}

			float32 lStart = -mNodeHalfDims[2];
			if (lcCollisions.Items() > 0)
			{
				ShellSort(lcCollisions.mpList, lcCollisions.Items(),
					[](c3DVf *l1, c3DVf *l2)->bool
				{
					return l1->Z() < l2->Z();
				});

				for (uint32 lCol = 0; lCol < lcCollisions.Items(); lCol += 2)
				{
					for (float32 lCur = lStart; lCur < lcCollisions[lCol].Z(); lCur+=1.0f){ GetNode(lX, lY, lCur) = 0; }
					if (lCol + 1 < lcCollisions.Items()) lStart = lcCollisions[lCol + 1].Z() + 1.0f;
				}
			}

			for (float32 lCur = lStart; lCur < mNodeHalfDims[2]; lCur += 1.0f)
			{
				GetNode(lX, lY, lCur) = 0;
			}
			

		}
	}

	GenerateCounts();
}

 
template<uint8 tLevels, class tD> cMesh *cVoxelOctTree<tLevels, tD>::GenerateMeshFromTree() 
{
 // Level 1 put vertex at the centre of mass of all incomplete blocks of nodes.
//  Level 2 put a vertex between all fully solid and fully empty blocks. (three maybe four cases allows it to do hard edges too...)
	cMesh *lpNew = new cMesh;

	cLimitedList<c3DVf> lVerteces(OctSize()*OctSize());
	lVerteces.SetItems(0);

	c3DVf *lpList = VoxelBlockCentreOfMass::Instance()->mfCentre;

	auto Func = [&](cVoxelOctTreeLevel<1, tD> &lNode,const c3DVf &lCentre)
	{
		if (lNode.NodeLayout() != 0 && lNode.NodeLayout() != 0xFF)
		{
			lVerteces.Add(lCentre + lpList[lNode.NodeLayout()] * lNode.NodeSize());
		}
	};

	IterateAllOneLevelCentre<1>(Func, c3DVf(0,0,0));

	return lpNew;
}


template<uint8 tLevels, class tD> cVoxelOctTree<tLevels,tD>::~cVoxelOctTree()
{
	delete[] mpNodes;
	delete[] mpCentres;
}

template<uint8 tLevels, class tD>  void cVoxelOctTree<tLevels, tD>::IterateAllLevels(typename cVoxelOctTreeBase<tD>::LevelIterator LevelCheck)
{
	for (uint8 liNode = 0; liNode < miNodes; ++liNode)
	{
		mpNodes[liNode].IterateAllLevels(LevelCheck);
	}
}

template<uint8 tLevels, class tD>  void cVoxelOctTree<tLevels, tD>::IterateAllNodes(typename cVoxelOctTreeBase<tD>::NodeIterator NodeCheckFunction)
{
	for (uint8 liNode = 0; liNode < miNodes; ++liNode)
	{
		mpNodes[liNode].IterateAllNodes(NodeCheckFunction);
	}
}


template<uint8 tLevels, class tD> template<uint8 tTargetLevel, typename FuncType> void cVoxelOctTree<tLevels, tD>::IterateAllOneLevel(FuncType lOperate)
{
	if (tTargetLevel > tLevels) return;

	for (uint32 lNode = 0; lNode < miNodes; ++lNode)
	{
		mpNodes[lNode].IterateAllOneLevel<tTargetLevel>(lOperate);
	}
}
template<uint8 tLevels, class tD> template<uint8 tTargetLevel, typename FuncType> void cVoxelOctTree<tLevels, tD>::IterateAllOneLevelCentre(FuncType lOperate,const c3DVf &lcCentre)
{
	if (tTargetLevel > tLevels) return;

	for (uint32 lNode = 0; lNode < miNodes; ++lNode)
	{
		mpNodes[lNode].IterateAllOneLevelCentre<tTargetLevel>(lOperate, cVoxelOctTreeLevel<tLevels, tD>::NewCentre(c3DVf(), lNode));
	}
}

template class cVoxelOctTree<8, uint8 >;
template class cVoxelOctTree<7, uint8 >;
template class cVoxelOctTree<6, uint8 >;
template class cVoxelOctTree<5, uint8 >;
template class cVoxelOctTree<4, uint8 >;

