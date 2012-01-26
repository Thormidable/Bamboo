#include "../../../WTBamboo.h"
//#include "../HList.h"

void cPolygon::GeneratePolygon(cVertex *lpVertex,uint32 liVerteces)
{
 Plane.GeneratePlane(lpVertex);
 Verteces.GenerateVerteces(lpVertex,liVerteces);
}

void cPolygonList::GeneratePolygonList(float *lpVerteces,uint16 *lpFaces,uint32 liFaces)
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

  mpList[liCount].GeneratePolygon(lpVert,3);
 }
OptimiseMeshes();
//OptimiseRays();
};

uint32 cPolygon::FileSize()
{
	uint32 liSize;
	liSize=Plane.FileSize();
	liSize+=Verteces.FileSize();
	return liSize;
};


cPolygon &cPolygon::operator=(cPolygon &lpOther)
{
	Plane=lpOther.Plane;
	mlCenter=lpOther.mlCenter;
	Verteces=lpOther.Verteces;
	return this[0];
}

float cPolygon::Area()
{
	float x,y,z;
	float lfArea;
	float lp1[3],lp2[3];
	uint32 liCount;
	uint32 liItemPos=Verteces.Items()-1;
	lp1[0]=Verteces[liItemPos].X()-mlCenter[0];
	lp1[1]=Verteces[liItemPos].Y()-mlCenter[1];
	lp1[2]=Verteces[liItemPos].Z()-mlCenter[2];


	lp2[0]=Verteces[0].X()-mlCenter[0];
	lp2[1]=Verteces[0].Y()-mlCenter[1];
	lp2[2]=Verteces[0].Z()-mlCenter[2];

	x=(lp1[1]*lp2[2]-lp1[2]*lp2[1]);
	y=(lp1[2]*lp2[0]-lp1[0]*lp2[2]);
	z=(lp1[0]*lp2[1]-lp1[1]*lp2[0]);

	lfArea=(x*x+y*y+z*z)*0.5;

	for(liCount=1;liCount<liItemPos;++liCount)
	{
		if(liCount & 0x1)
		{
			lp2[0]=Verteces[liCount].X()-mlCenter[0];
			lp2[1]=Verteces[liCount].Y()-mlCenter[1];
			lp2[2]=Verteces[liCount].Z()-mlCenter[2];
		}
		else
		{
			lp1[0]=Verteces[liCount].X()-mlCenter[0];
			lp1[1]=Verteces[liCount].Y()-mlCenter[1];
			lp1[2]=Verteces[liCount].Z()-mlCenter[2];
		}

		x=(lp1[1]*lp2[2]-lp1[2]*lp2[1]);
		y=(lp1[2]*lp2[0]-lp1[0]*lp2[2]);
		z=(lp1[0]*lp2[1]-lp1[1]*lp2[0]);

		lfArea+=(x*x+y*y+z*z)*0.5;
	}

	return lfArea;
};

void cPolygon::OutputIMFPolygon(ofstream &FileStream)
{
	Plane.OutputIMFPlane(FileStream);
	Verteces.OutputIMFVerteces(FileStream);
};

uint32 cPolygon::GetSmallestAngle(uint32 liStart)
{
	uint32 NEARLY_WORKING_NEED_TO_IDENTIFY_IF_ANGLE_INFRONT_OR_BEHIND_FIRST_VECTOR;
	float lp1[4],lp2[4];
	uint32 liCount;

	lp1[0]=Verteces[liStart].X()-mlCenter[0];
	lp1[1]=Verteces[liStart].Y()-mlCenter[1];
	lp1[2]=Verteces[liStart].Z()-mlCenter[2];
	lp1[3]=sqrt(lp1[0]*lp1[0]+lp1[1]*lp1[1]+lp1[2]*lp1[2]);

	lp2[0]=Verteces[liStart+1].X()-mlCenter[0];
	lp2[1]=Verteces[liStart+1].Y()-mlCenter[1];
	lp2[2]=Verteces[liStart+1].Z()-mlCenter[2];
	lp2[3]=sqrt(lp2[0]*lp2[0]+lp2[1]*lp2[1]+lp2[2]*lp2[2]);


	uint32 liSmallest=liStart+1;
	double lfAngle=acos((lp1[0]*lp2[0]+lp1[1]*lp2[1]+lp1[2]*lp2[2])/(lp1[3]*lp2[3]));

	for(liCount=liStart+2;liCount<Verteces.Items();++liCount)
	{

		lp2[0]=Verteces[liCount].X()-mlCenter[0];
		lp2[1]=Verteces[liCount].Y()-mlCenter[1];
		lp2[2]=Verteces[liCount].Z()-mlCenter[2];
		lp2[3]=sqrt(lp2[0]*lp2[0]+lp2[1]*lp2[1]+lp2[2]*lp2[2]);

		double TempAngle=acos((lp1[0]*lp2[0]+lp1[1]*lp2[1]+lp1[2]*lp2[2])/(lp1[3]*lp2[3]));
		if(TempAngle<lfAngle){lfAngle=TempAngle; liSmallest=liCount;}

	}

	return liSmallest;

}

double cPolygon::GetAngleSum(float *lpPos)
{

	float lp1[4],lp2[4];
	uint32 liCount;

	lp1[0]=Verteces[Verteces.Items()-1].X()-lpPos[0];
	lp1[1]=Verteces[Verteces.Items()-1].Y()-lpPos[1];
	lp1[2]=Verteces[Verteces.Items()-1].Z()-lpPos[2];
	lp1[3]=sqrt(lp1[0]*lp1[0]+lp1[1]*lp1[1]+lp1[2]*lp1[2]);

	lp2[0]=Verteces[0].X()-lpPos[0];
	lp2[1]=Verteces[0].Y()-lpPos[1];
	lp2[2]=Verteces[0].Z()-lpPos[2];
	lp2[3]=sqrt(lp2[0]*lp2[0]+lp2[1]*lp2[1]+lp2[2]*lp2[2]);


	double lfAngle=acos((lp1[0]*lp2[0]+lp1[1]*lp2[1]+lp1[2]*lp2[2])/(lp1[3]*lp2[3]));

	for(liCount=1;liCount<Verteces.Items()-1;++liCount)
	{
		if(liCount & 0x1)
		{
			lp2[0]=Verteces[liCount].X()-lpPos[0];
			lp2[1]=Verteces[liCount].Y()-lpPos[1];
			lp2[2]=Verteces[liCount].Z()-lpPos[2];
			lp2[3]=sqrt(lp2[0]*lp2[0]+lp2[1]*lp2[1]+lp2[2]*lp2[2]);
		}
		else
		{
			lp1[0]=Verteces[liCount].X()-lpPos[0];
			lp1[1]=Verteces[liCount].Y()-lpPos[1];
			lp1[2]=Verteces[liCount].Z()-lpPos[2];
			lp1[3]=sqrt(lp1[0]*lp1[0]+lp1[1]*lp1[1]+lp1[2]*lp1[2]);
		}
		lfAngle+=acos((lp1[0]*lp2[0]+lp1[1]*lp2[1]+lp1[2]*lp2[2])/(lp1[3]*lp2[3]));
	}

	return lfAngle;
};


bool cPolygon::SharesVertex(cVertex &lpOther)
{
	uint32 liCount;
	for(liCount=0;liCount<Verteces.Items();++liCount) if(Verteces[liCount]==lpOther) return 1;
	return 0;
};


void cPolygonList::GeneratePolygonList(cFullFaceList &lpFaces)
{
	Init(lpFaces.Items());

	//miItems=0;
	while(miItems<lpFaces.Items())
	{
		mpList[miItems].GeneratePolygon(lpFaces[miItems]);
		++miItems;
	}


	OptimiseMeshes();
};


void cPolygon::Init(uint32 liSize)
{
	Verteces.Init(liSize);
};


void cPolygon::GeneratePolygon(cFullFaceData &lpFace)
{
	Verteces.Init(3);
	Verteces[0]=lpFace.Verteces[0];
	Verteces[1]=lpFace.Verteces[1];
	Verteces[2]=lpFace.Verteces[2];
	Verteces.SetItems(3);

	Plane=lpFace.Plane;
};

uint8 cPolygon::SharesVertex(cFullFaceData &lpOther)
{

	uint32 liCount;
	uint8 liResult=0;
	for(liCount=0;liCount<Verteces.Items();++liCount)
	{
		if((Verteces[liCount]==lpOther.Verteces[0])||(Verteces[liCount]==lpOther.Verteces[1])||(Verteces[liCount]==lpOther.Verteces[2]))++liResult;
	}
	return liResult;

};

uint32 cPolygon::SharesVertex(cPolygon &lpOther)
{
	uint32 liCount,liLoop;
	uint32 liResult=0;
	for(liCount=0;liCount<Verteces.Items();++liCount)
	{
		for(liLoop=0;liLoop<lpOther.Verteces.Items();++liLoop)
		{
			if(Verteces[liCount]==lpOther.Verteces[liLoop])++liResult;
		}
	}
	return liResult;
};

uint8 cPolygon::NotSharedVertex(cFullFaceData &lpOther)
{
	uint32 liCount;
	bool li0,li1,li2;
	li0=li1=li2=false;
	for(liCount=0;liCount<Verteces.Items();++liCount)
	{
		if(Verteces[liCount]==lpOther.Verteces[0]) li0=true;
		if(Verteces[liCount]==lpOther.Verteces[1]) li1=true;
		if(Verteces[liCount]==lpOther.Verteces[2]) li2=true;
	}
	if(li0==false) return 0;
	if(li1==false) return 1;
	if(li2==false) return 2;
	return 3;
};



void cPolygon::CalculateCenter()
{

	uint32 liCount;
	mlCenter.X(0.0f);
	mlCenter.Y(0.0f);
	mlCenter.Z(0.0f);
	for(liCount=0;liCount<Verteces.Items();++liCount)
	{
		mlCenter.X(mlCenter.X()+Verteces[liCount].X());
		mlCenter.Y(mlCenter.Y()+Verteces[liCount].Y());
		mlCenter.Z(mlCenter.Z()+Verteces[liCount].Z());
	}
	double lfInv;
	if( Verteces.Items())	lfInv=1.0f/Verteces.Items();
	else lfInv=0.0f;

	mlCenter.X(mlCenter.X()*lfInv);
	mlCenter.Y(mlCenter.Y()*lfInv);
	mlCenter.Z(mlCenter.Z()*lfInv);

	mlCenter.Display();
};

void cPolygonList::Combine()
{
	uint32 li1;
	bool lbContinue=true;
	while(lbContinue)
	{
     lbContinue=false;
	for(li1=0;li1<miItems-1;++li1)
	{
		uint32 li2;
		for(li2=li1+1;li2<miItems;++li2)
		{
			if(mpList[li1].Plane==mpList[li2].Plane)
			{

                mpList[li1].Plane.Display();
                mpList[li2].Plane.Display();
				mpList[li1].Verteces.ChangeSize(mpList[li1].Verteces.Items()+mpList[li2].Verteces.Items());

				uint32 liVert2;
				for(liVert2=0;liVert2<mpList[li2].Verteces.Items();liVert2++)
				{
					if(!mpList[li1].SharesVertex(mpList[li2].Verteces[liVert2]))	 {mpList[li1].AddVertex(&(mpList[li2].Verteces[liVert2])); lbContinue=true;}
				}

				Remove(li2);
				--li2;
			}

		}
	}
	}
};

void cPolygonList::OrderDistance()
{
	uint32 liLoop;
	for(liLoop=0;liLoop<Items()-1;++liLoop)
	{
		uint32 liCount;
		uint32 liDistance=0;
		for(liCount=liLoop+1;liCount<Items();++liCount)
		{
			liDistance=liLoop;
			if(mpList[liCount].Plane.Distance()>mpList[liDistance].Plane.Distance()) liDistance=liCount;
		}
		if(liLoop!=liDistance) SwitchItems(liLoop,liDistance);
	}
};

void cPolygonList::OrderArea()
{
	uint32 liLoop;
	for(liLoop=0;liLoop<Items()-1;++liLoop)
	{
		uint32 liCount;
		uint32 liArea=liLoop;
		for(liCount=liLoop+1;liCount<Items();++liCount)
		{

			if(mpList[liCount].Area()>mpList[liArea].Area()) liArea=liCount;
		}
		if(liLoop!=liArea) SwitchItems(liLoop,liArea);
	}

};


void cPolygon::OrderClockwise()
{
	CalculateCenter();

	uint32 liCurrent=0;
	for(liCurrent=0;liCurrent<Verteces.Items()-1;++liCurrent)
	{
		uint32 liNext=GetSmallestAngle(liCurrent);
		if(liNext!=liCurrent+1) Verteces.SwitchItems(liNext,liCurrent+1);
	}
};


void cPolygonList::OptimiseRays()
{
	Combine();
	OrderArea();
	OrderVerteces();
};

void cPolygonList::OptimiseMeshes()
{
	Combine();
	OrderDistance();
	OrderVerteces();
};



void cPolygonList::OrderVerteces()
{
	uint32 liCount;
	for(liCount=0;liCount<miItems;++liCount)
	{
		mpList[liCount].OrderClockwise();
	}

};


void cPolygonList::OutputIMFPolygons(ofstream &FileStream)
{
	FileStream.write((char *) &miItems,sizeof(uint32));
	uint32 liCount;
	for(liCount=0;liCount<miItems;++liCount)
	{
		mpList[liCount].OutputIMFPolygon(FileStream);
	}
};

void cPolygonList::LoadIMFPolygons(ifstream &FileStream)
{
	uint32 liCount;
	FileStream.read((char *) &liCount,sizeof(uint32));
	Init(liCount);
	for(liCount=0;liCount<miSpaces;++liCount)
	{

		mpList[liCount].LoadIMFPolygon(FileStream);
	}
	SetItems(miSpaces);
};

uint32 cPolygonList::FileSize()
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

void cPolygonList::Display()
{
	uint32 liCount;
	for(liCount=0;liCount<Items();++liCount)
	{
		mpList[liCount].Display();
	}
}


cVertex &cPolygon::Center(){return mlCenter;};

void cPolygon::LoadIMFPolygon(ifstream &FileStream)
{
	Plane.LoadIMFPlane(FileStream);
	Verteces.LoadIMFVerteces(FileStream);
};

void cPolygon::Display()
{
	Plane.Display();
	Verteces.Display();
}

	void cPolygon::AddVertex(cVertex *lpOther){Verteces.Add(lpOther);};
void cPolygon::RemoveVertex(uint32 liPos){Verteces.Remove(liPos);};
cPlane &cPolygon::PlaneData(){return Plane;};
	cVertex &cPolygon::operator[](uint8 liPos){return Verteces[liPos];};
		cPolygon::cPolygon(){};

cPolygon::cPolygon(uint32 liSpaces)
{
	Verteces.Init(liSpaces);
};

cPolygon::~cPolygon()
{


};

cPolygonList::cPolygonList(){};
cPolygonList::~cPolygonList(){};
