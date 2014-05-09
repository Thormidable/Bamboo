#include "stdafx.h"
#include "../../../WTBamboo.h"
//#include "../HList.h"

void cPlaneList::GeneratePlanes(float *lpVerteces,uint16 *lpFaces,uint32 liFaces)
{
 uint32 liCount;
 Init(liFaces);
 SetItems(liFaces);
 cVertex lpVert[3];
 for(liCount=0;liCount<liFaces;++liCount)
 {
   lpVert[0].SetVertex(&lpVerteces[lpFaces[liCount*3]*3]);
   lpVert[1].SetVertex(&lpVerteces[lpFaces[liCount*3+1]*3]);
   lpVert[2].SetVertex(&lpVerteces[lpFaces[liCount*3+2]*3]);

  mpList[liCount].GeneratePlane(lpVert);
 }

}


void cPlane::GeneratePlane(cVertex *lpVerteces)
{

	//Done;
	c3DVf v1,v2;
	//Don't forget to Normalise.
	v1.v[0]=(lpVerteces[0].X()-lpVerteces[1].X());
	v1.v[1]=(lpVerteces[0].Y()-lpVerteces[1].Y());
	v1.v[2]=(lpVerteces[0].Z()-lpVerteces[1].Z());

	v2.v[0]=(lpVerteces[0].X()-lpVerteces[2].X());
	v2.v[1]=(lpVerteces[0].Y()-lpVerteces[2].Y());
	v2.v[2]=(lpVerteces[0].Z()-lpVerteces[2].Z());

	v1=v1*v2;

	v1.Normalise();
	//ASsign the Normal Vector to the plane and find the plane constant
	mpData[0]=v1.v[0];
	mpData[1]=v1.v[1];
	mpData[2]=v1.v[2];
	mpData[3]=-(v1.v[0]*lpVerteces[0].X()+v1.v[1]*lpVerteces[0].Y()+v1.v[2]*lpVerteces[0].Z());

};



void cPlane::Normalise()
{
	//printf("Normalise cPlane\n");
	float lfDiv;
	lfDiv=1.0f/sqrt(mpData[0]*mpData[0]+mpData[1]*mpData[1]+mpData[2]*mpData[2]);
	mpData[0]=mpData[0]*lfDiv;
	mpData[1]=mpData[1]*lfDiv;
	mpData[2]=mpData[2]*lfDiv;
};

bool cPlane::Similar(cPlane &lpOther,float lfRange)
{
	return(
		mpData[0]>=lpOther.mpData[0]-lfRange && mpData[0]<=lpOther.mpData[0]+lfRange &&
		mpData[1]>=lpOther.mpData[1]-lfRange && mpData[1]<=lpOther.mpData[1]+lfRange &&
		mpData[2]>=lpOther.mpData[2]-lfRange && mpData[2]<=lpOther.mpData[2]+lfRange &&
		mpData[3]>=lpOther.mpData[3]-lfRange && mpData[3]<=lpOther.mpData[3]+lfRange);
};

double cPlane::AbsoluteDistance(cPlane &lpOther)
{
	double lfTotal=0.0f;
	double lfPart;
	lfPart=(mpData[0]*mpData[3]-lpOther.mpData[0]*lpOther.mpData[3]);
	lfTotal+=lfPart*lfPart;
	lfPart=(mpData[1]*mpData[3]-lpOther.mpData[1]*lpOther.mpData[3]);
	lfTotal+=lfPart*lfPart;
	lfPart=(mpData[2]*mpData[3]-lpOther.mpData[2]*lpOther.mpData[3]);
	lfTotal+=lfPart*lfPart;
	return sqrt(lfTotal);
};


void cPlaneList::Display()
{
	uint32 liCount;
	for(liCount=0;liCount<Items();++liCount)
	{
		mpList[liCount].Display();
	}
}

void cPlaneList::OutputIMFPlanes(ofstream &FileStream)
{
	FileStream.write((char *) &miItems,sizeof(uint32));
	uint32 liCount;

	for(liCount=0;liCount<miItems;++liCount)
	{
		mpList[liCount].OutputIMFPlane(FileStream);
	}
};

void cPlaneList::LoadIMFPlanes(ifstream &FileStream)
{
	uint32 liCount;
	FileStream.read((char *) &liCount,sizeof(uint32));
	Init(liCount);
	for(liCount=0;liCount<miSpaces;++liCount)
	{
		mpList[liCount].LoadIMFPlane(FileStream);
	}
	SetItems(miSpaces);
};

uint32 cPlaneList::FileSize()
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

cFullFaceData &cPlane::operator=(cFullFaceData &lpOther)
{
	memcpy(mpData,lpOther.Plane.mpData,sizeof(float)*4);
	return lpOther;
};








	float cPlane::X(){return mpData[0];};
	float cPlane::Y(){return mpData[1];};
	float cPlane::Z(){return mpData[2];};
	float cPlane::Dist(){return mpData[3];};

	void cPlane::SetPlane(float x,float y,float z,float dist){mpData[0]=x; mpData[1]=y; mpData[2]=z; mpData[3]=dist;};

	float *cPlane::Planes(){return mpData;};

	cPlane::cPlane(){mpData[0]=mpData[1]=mpData[2]=mpData[3]=3.0f;};

	void cPlane::Display()
	{
		printf("Plane : %f %f %f     %f\n",mpData[0],mpData[1],mpData[2],mpData[3]);
	}

	uint32 cPlane::FileSize()
	{
		return sizeof(float)*4;
	};

	bool cPlane::operator==(cPlane &lpOther)
	{
	    return (mpData[0]==lpOther.mpData[0] &&
        mpData[1]==lpOther.mpData[1] &&
        mpData[2]==lpOther.mpData[2] &&
        mpData[3]==lpOther.mpData[3]
        );
		//return (!memcmp(mpData,lpOther.mpData,sizeof(float)*4));
	};

	cPlane &cPlane::operator=(cPlane &lpOther)
	{

		memmove(mpData,lpOther.mpData,sizeof(float)*4);
		return this[0];
	};

	/*
	cFullFaceData &cPlane::operator=(cFullFaceData &lpOther)
	{
	 operator=(lpOther.Plane);
	 return lpOther;
	};*/


	double cPlane::DotProduct(cVertex &lpOther)
	{
		return lpOther[0]*mpData[0]+lpOther[1]*mpData[1]+lpOther[2]*mpData[2];
	};

	bool cPlane::AbovePlane(cVertex &lpOther)
	{
		//Check this. No really.
		return -DotProduct(lpOther)>Distance();
	};

	float cPlane::Distance(){return mpData[3];};

	//Distance from One to Tother

	void cPlane::OutputIMFPlane(ofstream &FileStream)
	{
		FileStream.write((char*)mpData,FileSize());
	};

	void cPlane::LoadIMFPlane(ifstream &FileStream)
	{
		FileStream.read((char*)mpData,FileSize());
	};


void cPlaneList::Optimise()
{
 Strip();
 Order();


}

void cPlaneList::Strip()
{
    uint32 liCount;
	uint32 liLoop;
	for(liCount=0;liCount<Items()-1;++liCount)
	{
		for(liLoop=liCount+1;liLoop<Items();++liLoop)
		{
			if(mpList[liLoop].Similar(mpList[liCount],0.1f))
			{
				Delete(liLoop);
				liLoop--;
			}
		}
	}
}

void cPlaneList::Order()
{
	uint32 liFurthest=0;
	double FurthestDistance=0.0f;

	uint32 liCount;
	for(liCount=0;liCount<Items();++liCount)
	{
		if(mpList[liCount].Distance()>FurthestDistance) {FurthestDistance=mpList[liCount].Distance();liFurthest=liCount;};
	}
	SwitchItems(0,liFurthest);



	for(liCount=1;liCount<Items()-1;++liCount)
	{
		liFurthest=0;
		FurthestDistance=0.0f;
		uint32 liLoop;
		for(liLoop=liCount;liLoop<Items();++liLoop)
		{
			double lfTotal=0.0f;
			uint32 liLoopa;
			for(liLoopa=0;liLoopa<liCount;++liLoopa)
			{
				lfTotal+=mpList[liLoop].AbsoluteDistance(mpList[liLoopa]);
			}
			if(lfTotal>FurthestDistance){FurthestDistance=lfTotal; liFurthest=liLoop;};

		}
		SwitchItems(liCount,liFurthest);
	}

}

