
#include "../../../WTBamboo.h"
//#include "../HList.h"


uint32 cFullFaceData::FileSize()
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


void cFullFaceData::OutputIMFFullFace(ofstream &FileStream)
{
	Verteces[0].OutputIMFVertex(FileStream);
	Verteces[1].OutputIMFVertex(FileStream);
	Verteces[2].OutputIMFVertex(FileStream);

	Plane.OutputIMFPlane(FileStream);
};

void cFullFaceData::LoadIMFFullFace(ifstream &FileStream)
{
	Verteces[0].LoadIMFVertex(FileStream);
	Verteces[1].LoadIMFVertex(FileStream);
	Verteces[2].LoadIMFVertex(FileStream);

	Plane.LoadIMFPlane(FileStream);
};

void cFullFaceData::Display()
{
	Plane.Display();
	Verteces[0].Display();
	Verteces[1].Display();
	Verteces[2].Display();

}

void cFullFaceData::Fill(float *lpVertex,uint16 *mpFace)
{
	Verteces[0]=&lpVertex[mpFace[0]];
	Verteces[1]=&lpVertex[mpFace[1]];
	Verteces[2]=&lpVertex[mpFace[2]];

	Plane.GeneratePlane(Verteces);

};

uint8 cFullFaceData::SharesVertex(cVertex *lpOther)
{
	uint8 liResults=0;
	if(Verteces[0]==lpOther[0] || Verteces[0]==lpOther[1] || Verteces[0]==lpOther[2]) ++liResults;
	if(Verteces[1]==lpOther[0] || Verteces[1]==lpOther[1] || Verteces[1]==lpOther[2]) ++liResults;
	if(Verteces[2]==lpOther[0] || Verteces[2]==lpOther[1] || Verteces[2]==lpOther[2]) ++liResults;
	return liResults;

};

bool cFullFaceData::SamePlane(cPlane &lpOther)
{
	return Plane==lpOther;
};

cFullFaceData &cFullFaceData::operator=(cFullFaceData &lpOther)
{
	Plane=lpOther.Plane;
	Verteces[0]=lpOther.Verteces[0];
	Verteces[1]=lpOther.Verteces[1];
	Verteces[2]=lpOther.Verteces[2];
	return this[0];
};

bool cFullFaceData::IsConcave(cFullFaceList &lpOther)
{
  	//For every Vertex.
	uint32 liCount;
	for(liCount=0;liCount<lpOther.Items();++liCount)
	{
	  	//If it shares two verteces with this cFullFace in the List (ie shares an edge)
		if(SharesVertex(lpOther[liCount].Verteces)==2)
		{
		  	//If this is concave with that plane.
			if(Plane.AbovePlane(Verteces[NotSharedVertex(lpOther[liCount])])) return true;
		}

	}
	return false;
};


uint8 cFullFaceData::NotSharedVertex(cFace &lpOther)
{
	bool li0,li1,li2;
	li0=li1=li2=false;
	if(Verteces[0]==lpOther.Verteces[0] || Verteces[1]==lpOther.Verteces[0] || Verteces[2]==lpOther.Verteces[0]) li0=true;
	if(Verteces[0]==lpOther.Verteces[1] || Verteces[1]==lpOther.Verteces[1] || Verteces[2]==lpOther.Verteces[1]) li1=true;
	if(Verteces[0]==lpOther.Verteces[2] || Verteces[1]==lpOther.Verteces[2] || Verteces[2]==lpOther.Verteces[2]) li2=true;
	if(li0==false) return 0;
	if(li1==false) return 1;
	if(li2==false) return 2;
	return 3;
};


bool cFullFaceData::IsConcave(cFace lpOther)
{
	if(SharesVertex(lpOther.Verteces)==2)
	{
		if(Plane.AbovePlane(Verteces[NotSharedVertex(lpOther)])) return true;
	}
	return false;
};

void cFullFaceList::OutputIMFFullFaces(ofstream &FileStream)
{
	FileStream.write((char *) &miItems,sizeof(uint32));
	uint32 liCount;
	for(liCount=0;liCount<miItems;++liCount)
	{
		mpList[liCount].OutputIMFFullFace(FileStream);
	}
};

void cFullFaceList::LoadIMFFullFaces(ifstream &FileStream)
{
	uint32 liCount;
	FileStream.read((char *) &liCount,sizeof(uint32));
	Init(liCount);
	for(liCount=0;liCount<miSpaces;++liCount)
	{

		mpList[liCount].LoadIMFFullFace(FileStream);
	}
	SetItems(miSpaces);
};

uint32 cFullFaceList::FileSize()
{
	uint32 liSize=0;
	uint32 liCount;
	for(liCount=0;liCount<miItems;++liCount)
	{
		liSize+=mpList[liCount].FileSize();
	}
	liSize+=sizeof(uint32);
	return liSize;
};

void cFullFaceList::Display()
{
	uint32 liCount;
	for(liCount=0;liCount<miItems;++liCount)
	{
		mpList[liCount].Display();
	}

};

void cFullFaceList::Normalise()
{
	uint32 liCount;
	for(liCount=0;liCount<miItems;++liCount)
	{
		mpList[liCount].Plane.Normalise();
	}
}

cFullFaceList::cFullFaceList(){};
cFullFaceList::~cFullFaceList(){};

cFullFaceData::cFullFaceData(){};
