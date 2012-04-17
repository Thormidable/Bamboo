#include "../../../WTBamboo.h"
//#include "../HList.h"

bool cVertex::Similar(cVertex lpOther)
{
	return (mpData[0]>lpOther.mpData[0]-WT_VERTEX_RANGE_CHECK_SIMILAR && mpData[0]<lpOther.mpData[0]+WT_VERTEX_RANGE_CHECK_SIMILAR &&
	mpData[1]>lpOther.mpData[1]-WT_VERTEX_RANGE_CHECK_SIMILAR && mpData[1]<lpOther.mpData[1]+WT_VERTEX_RANGE_CHECK_SIMILAR &&
	mpData[2]>lpOther.mpData[2]-WT_VERTEX_RANGE_CHECK_SIMILAR && mpData[2]<lpOther.mpData[2]+WT_VERTEX_RANGE_CHECK_SIMILAR);
};

double cVertex::AbsoluteDistance(cVertex &lpOther)
{
	double lfTotal=0.0f;
	double lfPart;
	lfPart=(mpData[0]-lpOther.mpData[0]);
	lfTotal+=lfPart*lfPart;
	lfPart=(mpData[1]-lpOther.mpData[1]);
	lfTotal+=lfPart*lfPart;
	lfPart=(mpData[2]-lpOther.mpData[2]);
	lfTotal+=lfPart*lfPart;
	return sqrt(lfTotal);
};

void cVertexList::LoadIMFVerteces(ifstream &FileStream)
{
	uint32 liCount;

	//Read in Verteces
	FileStream.read((char *) &liCount,sizeof(uint32));
	Init(liCount);

	for(liCount=0;liCount<miSpaces;++liCount)
	{
		mpList[liCount].LoadIMFVertex(FileStream);
	}

	SetItems(miSpaces);

};

void cVertexList::OutputIMFVerteces(ofstream &FileStream)
{
	FileStream.write((char *) &miItems,sizeof(uint32));
	uint32 liCount;
	for(liCount=0;liCount<miItems;++liCount)
	{
		mpList[liCount].OutputIMFVertex(FileStream);
	}

};

uint32 cVertexList::FileSize()
{
	uint32 liSize=0;
	uint32 liCount;
	for(liCount=0;liCount<miItems;++liCount)
	{
		liSize+=mpList[liCount].FileSize();
	}
	return liSize;
};


void cVertexList::GenerateVerteces(cVertex *lpVerteces,uint32 liVerteces)
{
 Init(liVerteces);
 SetItems(liVerteces);

 uint32 liCount;
 for(liCount=0;liCount<liVerteces;++liCount)
 {
  mpList[liCount]=lpVerteces[liCount];
 }


}

void cVertexList::GenerateVerteces(float *lpVerteces,uint32 liVerteces)
{
	uint32 liLoop;
	uint32 liCount;

	Init(liVerteces);
	for(liCount=0;liCount<liVerteces;++liCount)
	{
		for(liLoop=0;liLoop<Items();++liLoop)
		{
			if(mpList[liLoop]==&lpVerteces[liCount*3]) break;
		}

		if(liLoop==Items())
		{
			cVertex lcTemp(&lpVerteces[liCount*3]);
			Add(&lcTemp);
		}
	}
};


void cVertexList::OrderDistance()
{
	uint32 liFurthest=0;
	float FurthestDistance=0.0f;

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
};

void cVertexList::Strip()
{
	/*
	 * S *tripping Code
	 *
	 */
	uint32 liCount;
	uint32 liLoop;
	for(liCount=0;liCount<Items()-1;++liCount)
	{
		for(liLoop=liCount+1;liLoop<Items();++liLoop)
		{
			if(mpList[liLoop].Similar(mpList[liCount]))
			{
				if(mpList[liLoop].Distance()>mpList[liCount].SqrDistance()) Delete(liCount);
				else Delete(liLoop);
				liLoop--;
			}
		}
	}
};

