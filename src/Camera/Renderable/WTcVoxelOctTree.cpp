
#include "../../WTBamboo.h"

template<class tD> cVoxelOctTree<tD>::cVoxelOctTree() : mpNodes(nullptr), mpCentres(nullptr), miOctTreeSize(0)
{


}

template<class tD> cVoxelOctTree<tD>::cVoxelOctTree(float32 XSize, float32 YSize, float32 ZSize) : mpNodes(nullptr), mpCentres(nullptr), miOctTreeSize(0)
{
	Resize(XSize, YSize, XSize);
}

template<class tD> void cVoxelOctTree<tD>::Resize(float32 XSize, float32 YSize, float32 ZSize)
{
	delete[] mpNodes;
	delete[] mpCentres;

	static const uint8 sMinimumLevels = 4;
	static const uint8 sMaxLevels = 8;

	//Calculate Levels required for minimum dimension (to allow efficient generation of non cubic objects.
	float32 lfMin = min(min(XSize, YSize), ZSize);
	uint32 liLevels = 0;
	while (pow(2, ++liLevels) < lfMin);
	liLevels = max(min(liLevels, sMaxLevels), sMinimumLevels);

	miOctTreeSize = pow(2, liLevels);

	mNodeDims.X(static_cast<uint32>(ceil(XSize / miOctTreeSize)));
	mNodeDims.Y(static_cast<uint32>(ceil(YSize / miOctTreeSize)));
	mNodeDims.Z(static_cast<uint32>(ceil(ZSize / miOctTreeSize)));

	miNodes = mNodeDims.X();
	miNodes *= mNodeDims.Y();
	miNodes *= mNodeDims.Z();


	switch (liLevels)
	{
	case 4:
		mpNodes = new cVoxelOctTreeLevel<4, tD>[miNodes];
		break;
	case 5:
		mpNodes = new cVoxelOctTreeLevel<5, tD>[miNodes];
		break;
	case 6:
		mpNodes = new cVoxelOctTreeLevel<6, tD>[miNodes];
		break;
	case 7:
		mpNodes = new cVoxelOctTreeLevel<7, tD>[miNodes];
		break;
	case 8:
		mpNodes = new cVoxelOctTreeLevel<8, tD>[miNodes];
		break;
	//case 9:
	//	mpNodes = new cVoxelOctTreeLevel<9, tD>[miNodes];
	//	break;
	default:
		throw;
	}


	// Generate Centre Points for Each 'node'
	c3DVf lStepStart;
	lStepStart.X(-(static_cast<float32>((mNodeDims.X() - 1)*miOctTreeSize) / 2.0f));
	lStepStart.Y(-(static_cast<float32>((mNodeDims.Y() - 1)*miOctTreeSize) / 2.0f));
	lStepStart.Z(-(static_cast<float32>((mNodeDims.Z() - 1)*miOctTreeSize) / 2.0f));

	mpCentres = new c3DVf[miNodes];
	uint32 lCentre = 0;
	for (uint32 lXC = 0; lXC < mNodeDims.X(); ++lXC)
	{
		for (uint32 lYC = 0; lYC < mNodeDims.Y(); ++lYC)
		{
			for (uint32 lZC = 0; lZC < mNodeDims.Z(); ++lZC)
			{
				mpCentres[lCentre].X(lStepStart.X() + static_cast<float32>(miOctTreeSize*lXC));
				mpCentres[lCentre].Y(lStepStart.Y() + static_cast<float32>(miOctTreeSize*lYC));
				mpCentres[lCentre].Z(lStepStart.Z() + static_cast<float32>(miOctTreeSize*lZC));
			}
		}

	}

	mNodeHalfDims.X(miOctTreeSize*mNodeDims[0] / 2);
	mNodeHalfDims.Y(miOctTreeSize*mNodeDims[1] / 2);
	mNodeHalfDims.Z(miOctTreeSize*mNodeDims[2] / 2);

	miInvOctTreeSize = 1.0f / miInvOctTreeSize;

}

template<class tD> void cVoxelOctTree<tD>::ZeroAllNodes()
{
	auto ZeroNode = [](tD &lNode){lNode = 0; };

	IterateWholeTree(ZeroNode);
}

template<class tD> cVoxelOctTreeBase<tD> &cVoxelOctTree<tD>::GetSuperNode(float32 liX, float32 liY, float32 liZ)
{
	uint32 lX = ceil(static_cast<float32>(liX + mNodeHalfDims[0]) * miInvOctTreeSize);
	uint32 lY = ceil(static_cast<float32>(liY + mNodeHalfDims[1]) * miInvOctTreeSize);
	uint32 lZ = ceil(static_cast<float32>(liZ + mNodeHalfDims[2]) * miInvOctTreeSize);

	return mpNodes[lX + lY*mNodeDims[0] + lZ*mNodeDims[0] * mNodeDims[1]];
}

template<class tD> tD &cVoxelOctTree<tD>::GetNode(float32 liX, float32 liY, float32 liZ)
{
	uint32 lX = static_cast<uint32>((liX + mNodeHalfDims[0])) % miOctTreeSize;
	uint32 lY = static_cast<uint32>((liY + mNodeHalfDims[0])) % miOctTreeSize;
	uint32 lZ = static_cast<uint32>((liZ + mNodeHalfDims[0])) % miOctTreeSize;

	return GetSuperNode(liX, liY, liZ).GetNode(lX, lY, lZ);
}

template<class tD> void cVoxelOctTree<tD>::GenerateCounts()
{
	for (uint32 lNode = 0; lNode < miNodes; ++lNode)
	{
		mpNodes[lNode].GenerateCounts();
	}
}

template<class tD> void cVoxelOctTree<tD>::GenerateTree(cMesh &lcMesh)
{
	
	c3DVu lcStart;

	struct PolygonInfo
	{
		c3DVf Normal;
		float32 Value;
		c3DVf Verteces[3];
	};

	//PreCalculations for RayCasting

	PolygonInfo *lFace = new PolygonInfo[lcMesh.Faces()];

	c3DVf lMaxSize(0,0,0);

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

	Resize(lMaxSize.X(), lMaxSize.Y(), lMaxSize.Z());
	IterateWholeTree([](tD &lcValue){lcValue = 1; });

	//Do RayCasts
	lcStart.Z(0);
	cLimitedList<c3DVf> lcCollisions(50);
	for (uint32 lX = 0; lX < miOctTreeSize*mNodeDims[0]; ++lX)
	{
		lcStart.X(lX);
		for (uint32 lY = 0; lY < miOctTreeSize*mNodeDims[1]; ++lY)
		{
			lcStart.Y(lY);
			lcCollisions.SetItems(0);
			
			for (uint32 lPolygon = 0; lPolygon < lcMesh.Faces(); ++lPolygon)
			{
				PolygonInfo &lPoly = lFace[lPolygon];
				float32 lZ = (lPoly.Value - lPoly.Normal.Dot(lcStart)) / lPoly.Normal[2];
				
				c3DVf lcCollision(lcStart.X()-mNodeHalfDims[0], lcStart.Y()-mNodeHalfDims[1], lZ);

				c3DVf lV[3];
				lV[0] = lPoly.Verteces[0] - lcCollision;
				lV[1] = lPoly.Verteces[1] - lcCollision;
				lV[2] = lPoly.Verteces[2] - lcCollision;

				float32 lfAngle = lV[0].Angle(lV[1]) + lV[1].Angle(lV[2]) + lV[0].Angle(lV[2]);

				if (lfAngle >= 2 * WT_PI*0.999)
				{
					lcCollision += mNodeHalfDims;
					lcCollisions.Add(lcCollision);
				}
			}

			if (lcCollisions.Items() % 2 > 0)
			{
				throw; 
			}

			uint32 lStart = 0;
			if (lcCollisions.Items() > 0)
			{
				ShellSort(lcCollisions.mpList, lcCollisions.Items(),
					[](c3DVf *l1, c3DVf *l2)->bool
				{
					return l1->Z() < l2->Z();
				});

				for (uint32 lCol = 0; lCol < lcCollisions.Items(); lCol += 2)
				{
					for (uint32 lCur = lStart; lCur < lcCollisions[lCol].Z(); ++lCur){ GetNode(lX, lY, lCur) = 0; }
					if (lCol + 1 < lcCollisions.Items()) lStart = lcCollisions[lCol + 1].Z() + 1;
				}
			}

			for (uint32 lCur = 0; lCur < miOctTreeSize*mNodeDims[2]; lCur++) GetNode(lX, lY, lCur) = 0;

		}
	}

	delete[] lFace;

	GenerateCounts();
}

 
template<class tD> cMesh *cVoxelOctTree<tD>::GenerateMesh()
{
 // Level 1 put vertex at the centre of mass of all incomplete blocks of nodes.
//  Level 2 put a vertex between all fully solid and fully empty blocks. (three maybe four cases allows it to do hard edges too...)


}


template<class tD> cVoxelOctTree<tD>::~cVoxelOctTree()
{
	delete[] mpNodes;
	delete[] mpCentres;
}

template<class tD>  void cVoxelOctTree<tD>::IterateWholeTree(typename cVoxelOctTreeBase<tD>::NodeIterator NodeCheckFunction)
{
	for (uint8 liNode = 0; liNode < miNodes; ++liNode)
	{
		mpNodes[liNode].IterateWholeTree(NodeCheckFunction);
	}
}

template class cVoxelOctTree< uint8 >;
