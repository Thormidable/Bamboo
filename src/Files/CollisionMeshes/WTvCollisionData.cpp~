#include "../../WTDivWin.h"

double cMeshCollision::GetAngle(float *lpPos,uint32 liPolygon)
{
 return mlFaces[liPolygon].GetAngleSum(lpPos);
};

void cBeamCollision::Update(cMatrix4 &New)
{
/*
	 mfRaySize[0]=New[8]*mfLength;
	 mfRaySize[1]=New[9]*mfLength;
	 mfRaySize[2]=New[10]*mfLength;
*/
mfRaySize[0]=New[8];
mfRaySize[1]=New[9];
mfRaySize[2]=New[10];

/*
	mfRaySize[0]=0.0f;
	mfRaySize[1]=0.0f;
	mfRaySize[2]=mfLength;*/
};

void cRayCollision::Update(cMatrix4 &New)
 {
	 //Damn the slowness of this. DAMN.
	 uint32 DAMN_THE_SLOWNESS_OF_THIS_NEED_TO_FIX_EITHER_HOW_BEAMS_WORK_OR_HOW_TO_CALCULATE_THIS;
		 mfRaySize[0]=New[12]-GLastPos[0];
		 mfRaySize[1]=New[13]-GLastPos[1];
		 mfRaySize[2]=New[14]-GLastPos[2];

		 mfLength=sqrt(mfRaySize[0]*mfRaySize[0]+mfRaySize[1]*mfRaySize[1]+mfRaySize[2]*mfRaySize[2]);

		 float lfTemp=1.0f/mfLength;
		 mfRaySize[0]*=lfTemp;
		 mfRaySize[1]*=lfTemp;
		 mfRaySize[2]*=lfTemp;

	memcpy(GLastPos,New.Position(),sizeof(float)*3);
};

void cMeshFileCollision::LoadIMF(ifstream &FileStream)
{
	uint32 liBuff;

	FileStream.ignore(sizeof(uint32));

	FileStream.read((int8 *) &liBuff,sizeof(uint32));
	//mpFileName=new char[liBuff+1];
	FileStream.read((int8 *) mpFileName,sizeof(int8)*liBuff);
	mpFileName[liBuff]=0;

	FileStream.read((int8*) &mfSize,sizeof(float));

	mlVerteces.LoadIMFVerteces(FileStream);
	mlPlanes.LoadIMFPlanes(FileStream);
	mlFaces.LoadIMFPolygons(FileStream);


};

void cMeshCollision::BuildObject(float *lpRanges)
{
	float lfTempSize;


	mlPlanes.Init(6);
	mlPlanes.SetItems(6);

	mlPlanes[0].SetPlane(-1.0f,0.0f,0.0f,lpRanges[0]);
	mlPlanes[1].SetPlane(1.0f,0.0f,0.0f,lpRanges[1]);

	mlPlanes[2].SetPlane(0.0f,-1.0f,0.0f,lpRanges[2]);
	mlPlanes[3].SetPlane(0.0f,1.0f,0.0f,lpRanges[3]);

	mlPlanes[4].SetPlane(0.0f,0.0f,-1.0f,lpRanges[4]);
	mlPlanes[5].SetPlane(0.0f,0.0f,1.0f,lpRanges[5]);

	mlVerteces.Init(8);
	mlVerteces.SetItems(8);

	uint32 liCount;
	lfTempSize=0.0f;
	for(liCount=0;liCount<6;++liCount)
	{
		if(lpRanges[liCount]*lpRanges[liCount]>lfTempSize) lfTempSize=lpRanges[liCount]*lpRanges[liCount];
	}
	SetSize(lfTempSize);

	mlVerteces[0].SetVertex(-lpRanges[0],-lpRanges[2],-lpRanges[4]);
	mlVerteces[1].SetVertex(lpRanges[1],lpRanges[3],lpRanges[5]);
	mlVerteces[2].SetVertex(-lpRanges[0],lpRanges[3],-lpRanges[4]);
	mlVerteces[3].SetVertex(lpRanges[1],-lpRanges[2],lpRanges[5]);
	mlVerteces[4].SetVertex(lpRanges[1],lpRanges[3],-lpRanges[4]);
	mlVerteces[5].SetVertex(-lpRanges[0],lpRanges[3],lpRanges[5]);
	mlVerteces[6].SetVertex(-lpRanges[0],-lpRanges[2],lpRanges[5]);
	mlVerteces[7].SetVertex(lpRanges[1],-lpRanges[2],-lpRanges[4]);


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


}


cBeamCollision::cBeamCollision(){mfLength=1.0f;mfRaySize[0]=0.0f;mfRaySize[1]=0.0f;mfRaySize[2]=1.0f;};
cBeamCollision::~cBeamCollision(){};
void cBeamCollision::BuildObject(float lfLength,float lfRadius){mfLength=lfLength; SetSize(lfRadius);};
cBeamCollision *cBeamCollision::Beam(){return this;};
cRayCollision *cBeamCollision::Ray(){return 0;};
float cBeamCollision::RayVector(uint8 liPos){return mfRaySize[liPos];};
float *cBeamCollision::RayVector(){return mfRaySize;};
float cBeamCollision::Length(){return mfLength;};


cSphereCollision::cSphereCollision(){mfSize=0.0f;};
cSphereCollision::~cSphereCollision(){};
void cSphereCollision::SetSize(float lfSize){mfSize=lfSize*lfSize;};
float cSphereCollision::CollisionSize(){return mfSize;};
cSphereCollision *cSphereCollision::Sphere(){return this;};
cBeamCollision *cSphereCollision::Beam(){return 0;};
cMeshCollision *cSphereCollision::Mesh(){return 0;};
cRayCollision *cSphereCollision::Ray(){return 0;};
void cSphereCollision::Update(cMatrix4 &New){(void) New;};

cRayCollision::cRayCollision(){lbCreated=true;}
cRayCollision::~cRayCollision(){};
cRayCollision *cRayCollision::Ray(){return this;};
bool cRayCollision::CreatedThisFrame(){return lbCreated;}

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


	cMeshFileCollision::cMeshFileCollision(){};
	cMeshFileCollision::~cMeshFileCollision(){};
