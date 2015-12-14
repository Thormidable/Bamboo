
#include "../../WTBamboo.h"

uint8 cVoxelOctTreeBase::GetNodeIndex(float &liX,float &liY,float &liZ,float siNodeSize)
{
	uint8 liNode = 0;
	if(liX > 0)
	{
		liX -=siNodeSize;
		liNode+=4;
	}
	else
	{
		liX +=siNodeSize;
	}

	if(liY > 0)
	{
		liNode +=2;
		liY -=siNodeSize;
	}
	else
	{
		liY +=siNodeSize;
	}

	if(liZ > 0)
	{
		liNode +=1;
		liZ -=siNodeSize;
	}
	else
	{
		liZ +=siNodeSize;
	}
	return liNode;
}

uint8 cVoxelOctTreeBase::GetNodeIndex(float &liX,float &liY,float &liZ)
{
	uint8 liNode = 0;
	if(liX > 0)
	{
		liNode+=4;
	}

	if(liY > 0)
	{
		liNode +=2;
	}

	if(liZ > 0)
	{
		liNode +=1;
	}
	return liNode;
}


cVoxelOctTreeBase::cVoxelOctTreeBase()
{

}

cVoxelOctTreeBase::~cVoxelOctTreeBase()
{

}

cVoxelOctTree::cVoxelOctTree(float XSize,float YSize,float ZSize)
{
	float lfMin = min(min(XSize,YSize),ZSize);
	uint32 liLevels = 0;
	while(pow(2,++liLevels) < lfMin);

	uint32 liStepSize = pow(2,liLevels);
	miNodes = static_cast<uint32>(XSize) / liStepSize;
	miNodes *= static_cast<uint32>(YSize) / liStepSize;
	miNodes *= static_cast<uint32>(ZSize) / liStepSize;

	if(liLevels < 7) liLevels = 7;
	switch(liLevels)
	{
	case 7:
		mpNodes = new cVoxelOctTreeLevel<128>[miNodes];
		break;
	case 8:
		mpNodes = new cVoxelOctTreeLevel<256>[miNodes];
		break;
	case 9:
		mpNodes = new cVoxelOctTreeLevel<512>[miNodes];
		break;
	case 10 : 
		mpNodes = new cVoxelOctTreeLevel<1024>[miNodes];
		break;
	default:
		mpNodes = new cVoxelOctTreeLevel<1024>[miNodes];
	}

}

uint8 &GetNode(float &liX,float &liY,float &liZ)
{
	//TODO : This needs to identify which Node to Use.
}

void cVoxelOctTree::SetSurfaceVoxelsFromMesh(cMesh &lcMesh)
{
	float *lpVertexData = lcMesh.VertexData();
	for(uint32 liPolygon = 0;liPolygon < lcMesh.Faces(); ++liPolygon)
	{
		uint16 *lpFace = lcMesh.Face(liPolygon);

		c3DVf lcVerteces[3];

		c3DVi liLowerCorner(lpVertexData[lpFace[0]*3],lpVertexData[lpFace[0]*3+1],lpVertexData[lpFace[0]*3+2]);
		c3DVi liUpperCorner(lpVertexData[lpFace[0]*3],lpVertexData[lpFace[0]*3+1],lpVertexData[lpFace[0]*3+2]);

		for(uint8 liVertex = 0; liVertex < 3;++liVertex)
		{
			lcVerteces[liVertex].X(lpVertexData[lpFace[liVertex]*3]);
			lcVerteces[liVertex].Y(lpVertexData[lpFace[liVertex]*3+1]);
			lcVerteces[liVertex].Z(lpVertexData[lpFace[liVertex]*3+2]);

			// Set The Corners to Be Surface Voxels.
			GetNode(lcVerteces[liVertex].X(),lcVerteces[liVertex].Y(),lcVerteces[liVertex].Z()) = 2;

			//Check Boundaries on The Polygon...
			if(liLowerCorner.X() < lcVerteces[liVertex].X())	liLowerCorner.X(lcVerteces[liVertex].X());
			if(liLowerCorner.Y() < lcVerteces[liVertex].Y())	liLowerCorner.Y(lcVerteces[liVertex].Y());
			if(liLowerCorner.Z() < lcVerteces[liVertex].Z())	liLowerCorner.Z(lcVerteces[liVertex].Z());
			if(liUpperCorner.X() < lcVerteces[liVertex].X())	liUpperCorner.X(lcVerteces[liVertex].X());
			if(liUpperCorner.Y() < lcVerteces[liVertex].Y())	liUpperCorner.Y(lcVerteces[liVertex].Y());
			if(liUpperCorner.Z() < lcVerteces[liVertex].Z())	liUpperCorner.Z(lcVerteces[liVertex].Z());
		}

		liUpperCorner +=1;

		c3DVf lcVectors[3];

		// Plot all the voxels which lie on the edge.
		for(uint32 liEdge=0;liEdge < 3;++liEdge)
		{
			uint8 liEnd = liEdge+1;
			if(liEnd == 3) liEnd = 0;

			c3DVf lcCursor;
			c3DVf lcStart(lcVerteces[liEdge]);
			c3DVf lcEnd(lcVerteces[liEnd]);
			c3DVf lcVector;
			c3DVi lcCursorInt, lcEndInt;

			lcVector = lcEnd-lcStart;
			lcVectors[liEdge] = lcVector;

			lcCursorInt = lcCursor = lcStart;
			lcCursorInt+=1;
			lcEndInt = lcEnd;
			lcEndInt+=1;
			while(!(lcCursorInt == lcEndInt))
			{
				c3DVf lcSmall;
				lcSmall.X((ceil(lcCursorInt.X())-lcCursor.X()) / lcVector.X());
				lcSmall.Y((ceil(lcCursorInt.Y())-lcCursor.Y()) / lcVector.Y());
				lcSmall.Z((ceil(lcCursorInt.Z())-lcCursor.Z()) / lcVector.Z());

				if(lcSmall.X() <= lcSmall.Y()+std::numeric_limits<float>::epsilon() && lcSmall.X() <= lcSmall.Z()+std::numeric_limits<float>::epsilon())
				{
					if(lcSmall.X() > lcSmall.Y()-std::numeric_limits<float>::epsilon()) ++lcCursorInt.v[1];
					if(lcSmall.X() > lcSmall.Z()-std::numeric_limits<float>::epsilon()) ++lcCursorInt.v[2];
					++lcCursorInt.v[0];
					lcCursor+=lcVector*lcSmall.X();
				}
				else
				{
					if(lcSmall.Y() <= lcSmall.Z()+std::numeric_limits<float>::epsilon())
					{
						if(lcSmall.X() > lcSmall.Z()-std::numeric_limits<float>::epsilon()) ++lcCursorInt.v[2];
						++lcCursorInt.v[1];
						lcCursor+=lcVector*lcSmall.Y();
					}
					else 
					{
						++lcCursorInt.v[2];
						lcCursor+=lcVector*lcSmall.Z();
					}
				}

				GetNode(lcCursorInt.X()-1,lcCursorInt.Y()-1,lcCursorInt.Z()-1) = 2;

			}
		}

		//Finally Process Every Voxel in the boundaries of the face. And set them to surface.

		c3DVf lcNormal = lcVectors[0]*lcVectors[1];
		lcNormal.Normalise();
		float lcPlaneValue = lcNormal.Dot(lcVectors[0]);

		for(uint32 liX = liLowerCorner.X(); liX < liUpperCorner.X(); ++liX)
		{
			for(uint32 liY = liLowerCorner.Y(); liY < liUpperCorner.Y(); ++liY)
			{
				for(uint32 liZ = liLowerCorner.Z(); liZ < liUpperCorner.Z(); ++liZ)
				{
					c3DVf lcBoxPos(static_cast<float>(liX)+0.5,static_cast<float>(liY)+0.5,static_cast<float>(liZ)+0.5);
					//Determine if Box is less than one half box away from the surface
					if( abs(lcNormal.Dot(lcBoxPos)-lcPlaneValue) < 0.5f )
					{
						float lfTotalAngle = 0.0f;
						//Sum angles to determine if it is within the face.
						for(uint8 liVertex=0;liVertex < 3;++liVertex)
						{
							uint8 liEnd = liVertex+1;
							if(liEnd == 3) liEnd = 0;
							c3DVf lcAngle1 = lcVerteces[liVertex] - lcBoxPos;
							c3DVf lcAngle2 = lcVerteces[liEnd] - lcBoxPos;

							lfTotalAngle +=lcAngle1.Angle(lcAngle2);
						}
						//If Box is within the face. Set it to be surface.
						if(lfTotalAngle<= 2*WT_PI)
						{
							GetNode(lcBoxPos.X(),lcBoxPos.Y(),lcBoxPos.Z()) = 2;
						}
					}
				}

			}
		}

	}
}

void cVoxelOctTree::GenerateTree(cMesh &lcMesh)
{
	IterateWholeTree([](uint8 &lcValue){lcValue = 1;});

	SetSurfaceVoxelsFromMesh(lcMesh);
	
	FloodFillFromEdge();
}

void cVoxelOctTree::FloodFillFromEdge()
{
	for(uint32 liX=0; liX < )
}

cVoxelOctTree::~cVoxelOctTree()
{
	delete [] mpNodes;
}