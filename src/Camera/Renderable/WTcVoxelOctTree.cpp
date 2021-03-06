
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
	lFace.SetItems(lcMesh.Faces());
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

	cVoxelOctTreeBase<tD> *lpNewObject = GetVoxelOctTree(lMaxSize.X()*2, lMaxSize.Y()*2, lMaxSize.Z()*2);

	lpNewObject->GenerateTree(lFace);

	return lpNewObject;
}

template<uint8 tLevels, class tD> void cVoxelOctTree<tLevels, tD>::GenerateTree(const cLimitedList<PolygonInfo> &lFace)
{
	IterateAllNodes([](tD &lcValue){lcValue = 1; },VoxelSkipFlags::NONE);

	uint64 ltCounts = 0;
	IterateAllOneLevel<0>(
		[&](cVoxelOctTreeLevel<0, uint8> &lcValue)
	{
		if (lcValue.GetNode(0, 0, 0) == 1) ++ltCounts;
	}, VoxelSkipFlags::EMPTY);

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

			float32 lCur = -mNodeHalfDims[2];
			if (lcCollisions.Items() > 0)
			{
				ShellSort(lcCollisions.mpList, lcCollisions.Items(),
					[](c3DVf *l1, c3DVf *l2)->bool
				{
					return l1->Z() > l2->Z();
				});


				for (uint32 lCol = 0; lCol < lcCollisions.Items(); lCol += 2)
				{
					for (; lCur < lcCollisions[lCol].Z() && lCur < mNodeHalfDims[2]; lCur += 1.0f)
					{
						GetNode(lX, lY, lCur) = 0; 
					}
					if (lCol + 1 < lcCollisions.Items())
					{
						while (lCur >= lcCollisions[lCol + 1].Z()) ++lCol;
						lCur = floor(lcCollisions[lCol + 1].Z() + 1.0f);
					}
				}
			}

			for (; lCur < mNodeHalfDims[2]; lCur += 1.0f)
			{
				GetNode(lX, lY, lCur) = 0;
			}
			

		}
	}


	uint64 lCounts = 0;
	IterateAllOneLevel<0>(
	[&](cVoxelOctTreeLevel<0, uint8> &lcValue)
	{
		if (lcValue.GetNode(0, 0, 0) > 0)
		{
			++lCounts;
		}
	}, VoxelSkipFlags::EMPTY);

	GenerateCounts();
}

 
template<uint8 tLevels, class tD> cMesh *cVoxelOctTree<tLevels, tD>::GenerateMeshFromTree() 
{
 // Level 1 put vertex at the centre of mass of all incomplete blocks of nodes.
//  Level 2 put a vertex between all fully solid and fully empty blocks. (three maybe four cases allows it to do hard edges too...)
	cMeshArray *lpMeshArray = new cMeshArray;

	cLimitedList<c3DVf> lVerteces(OctSize()*OctSize());
	cLimitedList<c3DVt<FACE_TYPE> > lFaces(OctSize()*OctSize());

	lVerteces.SetItems(0);

	c3DVf *lpList = VoxelBlockCentreOfMass::Instance()->mfCentre;
	uint8 *lpSurroundingList = VoxelBlockCentreOfMass::Instance()->mSurroundingConnections;

	auto Func = [&](cVoxelOctTreeLevel<1, tD> &lNode,const c3DVf &lCentre)
	{
		if (lNode.NodeLayout() != 0 && lNode.NodeLayout() != 0xFF)
		{
			lVerteces.Add(lCentre + lpList[lNode.NodeLayout()] * lNode.NodeSize());
			
			uint32 lCoreVertex = lVerteces.Items()-1;			
			float32 lStep = -1.0f;
			uint8 lBit = 1;
			uint8 lLocalVerteces = 0;
			for (uint8 lUp = 0; lUp < 2; ++lUp)
			{
				for (uint8 lDim = 0; lDim < 3; ++lDim)
				{
					if (lpSurroundingList[lNode.NodeLayout()]&lBit)
					{
						c3DVf lNewCentre = lCentre;
						lNewCentre.v[lDim] += lStep;
						uint8 lID = 0;
						if (GetNode(lNewCentre.v[0] - 0.5f, lNewCentre.v[1] - 0.5f, lNewCentre.v[2] - 0.5f)> 0) lID += 0x1;
						if (GetNode(lNewCentre.v[0] - 0.5f, lNewCentre.v[1] - 0.5f, lNewCentre.v[2] + 0.5f)> 0) lID += 0x2;
						if (GetNode(lNewCentre.v[0] - 0.5f, lNewCentre.v[1] + 0.5f, lNewCentre.v[2] - 0.5f)> 0) lID += 0x4;
						if (GetNode(lNewCentre.v[0] - 0.5f, lNewCentre.v[1] + 0.5f, lNewCentre.v[2] + 0.5f)> 0) lID += 0x8;
						if (GetNode(lNewCentre.v[0] + 0.5f, lNewCentre.v[1] - 0.5f, lNewCentre.v[2] - 0.5f) > 0) lID += 0x10;
						if (GetNode(lNewCentre.v[0] + 0.5f, lNewCentre.v[1] - 0.5f, lNewCentre.v[2] + 0.5f) > 0) lID += 0x20;
						if (GetNode(lNewCentre.v[0] + 0.5f, lNewCentre.v[1] + 0.5f, lNewCentre.v[2] - 0.5f) > 0) lID += 0x40;
						if (GetNode(lNewCentre.v[0] + 0.5f, lNewCentre.v[1] + 0.5f, lNewCentre.v[2] + 0.5f) > 0) lID += 0x80;

						lVerteces.Add(lNewCentre + lpList[lID] * lNode.NodeSize());

						if (!(++lLocalVerteces % 2))
						{
							lFaces.Add(c3DVt<FACE_TYPE>(lCoreVertex, lVerteces.Items() - 1, lVerteces.Items() - 2));
						}
					}

					lFaces.Add(c3DVt<FACE_TYPE>(lCoreVertex, lVerteces.Items() - 1, lCoreVertex + 1));

					lBit = lBit << 1;
				}
				lStep = 1.0f;
			}
		}
	};

	IterateAllOneLevelCentre<1>(Func, c3DVf(0,0,0), (VoxelSkipFlags::EMPTY|VoxelSkipFlags::DENSE));


	lpMeshArray->miVertex = lVerteces.Items();
	lpMeshArray->miFaces = lFaces.Items();

	lpMeshArray->mpVertex = new float[lVerteces.Items() * 3];
	memcpy(lpMeshArray->mpVertex, lVerteces.mpList, sizeof(float32) * 3 * lVerteces.Items());

	lpMeshArray->mpFaces = new FACE_TYPE[lFaces.Items() * 3];
	memcpy(lpMeshArray->mpFaces, lFaces.mpList, sizeof(FACE_TYPE) * 3 * lFaces.Items());

	string lTemp("InternalGenerateVoxelMesh");
	lpMeshArray->mpRef = new char[lTemp.length()+1];
	memcpy(lpMeshArray->mpRef, lTemp.data(), lTemp.length()+1);

	cMesh *lpReturn = new cMesh(lpMeshArray);
	
	lpReturn->BufferMesh();

	return lpReturn; 
}


template<uint8 tLevels, class tD> cVoxelOctTree<tLevels,tD>::~cVoxelOctTree()
{
	delete[] mpNodes;
	delete[] mpCentres;
}

template<uint8 tLevels, class tD>  void cVoxelOctTree<tLevels, tD>::IterateAllLevels(LevelIterator LevelCheck, VoxelSkip lSkip)
{
	for (uint8 liNode = 0; liNode < miNodes; ++liNode)
	{
		if(!mpNodes[liNode].ShouldSkip(lSkip)) mpNodes[liNode].IterateAllLevels(LevelCheck, lSkip);
	}
}

template<uint8 tLevels, class tD>  void cVoxelOctTree<tLevels, tD>::IterateAllNodes(NodeIterator NodeCheckFunction, VoxelSkip lSkip)
{
	for (uint8 liNode = 0; liNode < miNodes; ++liNode)
	{
		if (!mpNodes[liNode].ShouldSkip(lSkip)) mpNodes[liNode].IterateAllNodes(NodeCheckFunction, lSkip);
	}
}


template<uint8 tLevels, class tD> template<uint8 tTargetLevel, typename FuncType> void cVoxelOctTree<tLevels, tD>::IterateAllOneLevel(FuncType lOperate, VoxelSkip lSkip)
{
	if (tTargetLevel > tLevels) return;

	for (uint32 lNode = 0; lNode < miNodes; ++lNode)
	{
		if (!mpNodes[lNode].ShouldSkip(lSkip)) mpNodes[lNode].IterateAllOneLevel<tTargetLevel>(lOperate, lSkip);
	}
}
template<uint8 tLevels, class tD> template<uint8 tTargetLevel, typename FuncType> void cVoxelOctTree<tLevels, tD>::IterateAllOneLevelCentre(FuncType lOperate, const c3DVf &lcCentre, VoxelSkip lSkip)
{
	if (tTargetLevel > tLevels) return;

	for (uint32 lNode = 0; lNode < miNodes; ++lNode)
	{
		if (!mpNodes[lNode].ShouldSkip(lSkip)) mpNodes[lNode].IterateAllOneLevelCentre<tTargetLevel>(lOperate, cVoxelOctTreeLevel<tLevels, tD>::NewCentre(c3DVf(), lNode), lSkip);
	}
}

template class cVoxelOctTree<8, uint8 >;
template class cVoxelOctTree<7, uint8 >;
template class cVoxelOctTree<6, uint8 >;
template class cVoxelOctTree<5, uint8 >;
template class cVoxelOctTree<4, uint8 >;
