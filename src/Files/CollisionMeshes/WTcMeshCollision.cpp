#include "stdafx.h"
#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

double cMeshCollision::GetAngle(float *lpPos,uint32 liPolygon)
{
 return mlFaces[liPolygon].GetAngleSum(lpPos);
};

void cMeshCollision::BuildObject(float *lpRanges)
{

	mlPlanes.Init(6);
	mlPlanes.SetItems(6);

	mlPlanes[0].SetPlane(-1.0f,0.0f,0.0f,-lpRanges[0]);
	mlPlanes[1].SetPlane(1.0f,0.0f,0.0f,lpRanges[1]);

	mlPlanes[2].SetPlane(0.0f,-1.0f,0.0f,-lpRanges[2]);
	mlPlanes[3].SetPlane(0.0f,1.0f,0.0f,lpRanges[3]);

	mlPlanes[4].SetPlane(0.0f,0.0f,-1.0f,-lpRanges[4]);
	mlPlanes[5].SetPlane(0.0f,0.0f,1.0f,lpRanges[5]);

	mlVerteces.Init(8);
	mlVerteces.SetItems(8);

	uint32 liCount=0;

		float lfX,lfY,lfZ;
		if(abs(lpRanges[0])>abs(lpRanges[1])) lfX=lpRanges[0];
		else lfX=lpRanges[1];

		if(abs(lpRanges[2])>abs(lpRanges[3])) lfY=lpRanges[2];
		else lfY=lpRanges[3];

		if(abs(lpRanges[4])>abs(lpRanges[5])) lfZ=lpRanges[4];
		else lfZ=lpRanges[5];

	SetSize(sqrt(lfX*lfX+lfY*lfY+lfZ*lfZ));

	mlVerteces[0].SetVertex(lpRanges[0],lpRanges[2],lpRanges[4]);
	mlVerteces[1].SetVertex(lpRanges[1],lpRanges[3],lpRanges[5]);
	mlVerteces[2].SetVertex(lpRanges[0],lpRanges[3],lpRanges[4]);
	mlVerteces[3].SetVertex(lpRanges[1],lpRanges[2],lpRanges[5]);
	mlVerteces[4].SetVertex(lpRanges[1],lpRanges[3],lpRanges[4]);
	mlVerteces[5].SetVertex(lpRanges[0],lpRanges[3],lpRanges[5]);
	mlVerteces[6].SetVertex(lpRanges[0],lpRanges[2],lpRanges[5]);
	mlVerteces[7].SetVertex(lpRanges[1],lpRanges[2],lpRanges[4]);


	mlFaces.Init(6);
	mlFaces.SetItems(6);
	for(liCount=0;liCount<6;++liCount)
	{
		mlFaces[liCount].Verteces.Init(4);
		mlFaces[liCount].Verteces.SetItems(4);
	}

	mlFaces[0].Plane=mlPlanes[0];
	mlFaces[1].Plane=mlPlanes[1];
	mlFaces[2].Plane=mlPlanes[2];
	mlFaces[3].Plane=mlPlanes[3];
	mlFaces[4].Plane=mlPlanes[4];
	mlFaces[5].Plane=mlPlanes[5];

	//-x
	mlFaces[0].Verteces[0]=mlVerteces[0];
	mlFaces[0].Verteces[1]=mlVerteces[6];
	mlFaces[0].Verteces[2]=mlVerteces[5];
	mlFaces[0].Verteces[3]=mlVerteces[2];

	//+x
	mlFaces[1].Verteces[0]=mlVerteces[1];
	mlFaces[1].Verteces[1]=mlVerteces[3];
	mlFaces[1].Verteces[2]=mlVerteces[7];
	mlFaces[1].Verteces[3]=mlVerteces[4];

	//-y
	mlFaces[2].Verteces[0]=mlVerteces[0];
	mlFaces[2].Verteces[1]=mlVerteces[7];
	mlFaces[2].Verteces[2]=mlVerteces[3];
	mlFaces[2].Verteces[3]=mlVerteces[6];

	//+y
	mlFaces[3].Verteces[0]=mlVerteces[1];
	mlFaces[3].Verteces[1]=mlVerteces[4];
	mlFaces[3].Verteces[2]=mlVerteces[2];
	mlFaces[3].Verteces[3]=mlVerteces[5];

	//-z
	mlFaces[4].Verteces[0]=mlVerteces[0];
	mlFaces[4].Verteces[1]=mlVerteces[2];
	mlFaces[4].Verteces[2]=mlVerteces[4];
	mlFaces[4].Verteces[3]=mlVerteces[7];

	//+z
	mlFaces[5].Verteces[0]=mlVerteces[1];
	mlFaces[5].Verteces[1]=mlVerteces[3];
	mlFaces[5].Verteces[2]=mlVerteces[6];
	mlFaces[5].Verteces[3]=mlVerteces[5];

	mlFaces[0].CalculateCenter();
	mlFaces[1].CalculateCenter();
	mlFaces[2].CalculateCenter();
	mlFaces[3].CalculateCenter();
	mlFaces[4].CalculateCenter();
	mlFaces[5].CalculateCenter();
}

cMeshCollision *cMeshCollision::Mesh(){return this;};
cMeshCollision::~cMeshCollision(){};
uint32 cMeshCollision::Verteces(){return mlVerteces.Items();};
float *cMeshCollision::Vertex(uint32 liPos){return mlVerteces[liPos].Verteces();};
uint32 cMeshCollision::Planes(){return mlPlanes.Items();};
float *cMeshCollision::Plane(uint32 liPos){return mlPlanes[liPos].Planes();};
uint32 cMeshCollision::Faces(){return mlFaces.Items();};
cVertexList cMeshCollision::FaceVerteces(uint32 liPos){return mlFaces[liPos].Verteces;};
cPolygon cMeshCollision::Polygon(uint32 liPos){return mlFaces[liPos];};

float *cMeshCollision::FacePlane(uint32 liPos)
{
  return mlFaces[liPos].PlaneData().Planes();

};

uint8 cMeshCollision::Type(){return WT_COLLISION_MODEL;}


#endif
