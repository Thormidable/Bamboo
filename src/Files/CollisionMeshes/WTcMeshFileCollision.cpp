#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

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

cMeshFileCollision::cMeshFileCollision(){};
cMeshFileCollision::~cMeshFileCollision(){};

#endif
