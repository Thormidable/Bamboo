
#include "../../../WTBamboo.h"
//#include "../HList.h"


cFace &cFace::operator=(cFace &lpOther)
{
	Plane=lpOther.Plane;
	Verteces[0]=lpOther.Verteces[0];
	Verteces[1]=lpOther.Verteces[1];
	Verteces[2]=lpOther.Verteces[2];
	return this[0];
};

uint32 cFace::FileSize()
{
	uint32 liSize=0;
	uint32 liCount;
	for(liCount=0;liCount<3;++liCount)
	{
		liSize+=Verteces[liCount].FileSize();
	}
	liSize+=Plane.FileSize();
	return liSize;
};

void cFace::OutputIMFFace(ofstream &FileStream)
{
	Verteces[0].OutputIMFVertex(FileStream);
	Verteces[1].OutputIMFVertex(FileStream);
	Verteces[2].OutputIMFVertex(FileStream);

	Plane.OutputIMFPlane(FileStream);
};

void cFace::LoadIMFFace(ifstream &FileStream)
{
	Verteces[0].LoadIMFVertex(FileStream);
	Verteces[1].LoadIMFVertex(FileStream);
	Verteces[2].LoadIMFVertex(FileStream);

	Plane.LoadIMFPlane(FileStream);
};
