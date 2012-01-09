#include "../../../WTBamboo.h"
//#include "../HList.h"

void cClusterList::Optimise()
{
	uint32 liCount;
	for(liCount=0;liCount<miItems;++liCount)
	{
		mpList[liCount].Optimise();
	}
};

void cCluster::Add(cFullFaceData &lpData)
{
 Faces[miItems].Plane=lpData.Plane;
 memcpy(Faces[miItems++].Verteces,lpData.Verteces,sizeof(cVertex)*3);
};

void cClusterList::GenerateConvex(cFullFaceList &ClusterData)
{

	int32 liCount;

	while(ClusterData.Items())
	{

		for(liCount=0;liCount<(int32)ClusterData.Items()-1;++liCount)
		{
			if(!ClusterData[liCount].IsConcave(ClusterData))
			{
				mpList[0].Add(ClusterData[liCount]);
				ClusterData.Remove(liCount);
				--liCount;
			}

		}
	}
	miItems=1;

};


void cClusterList::GenerateConcaves(cFullFaceList &ClusterData)
{
	uint32 liCount;
	int32 liLoop;
	miItems=0;
	while(ClusterData.Items())
	{
		mpList[++miItems].Add(ClusterData[0]);
		ClusterData.Remove(0);
		bool lbFinished=false;
		while(!lbFinished)
		{
			lbFinished=true;
			for(liCount=0;liCount<mpList[miItems].Items();++liCount)
			{
				for(liLoop=0;liLoop<(int32)ClusterData.Items();++liLoop)
				{
					if(ClusterData[liLoop].IsConcave(mpList[miItems].Face(liCount)))
					{
						mpList[miItems].Add(ClusterData[liLoop]);
						ClusterData.Remove(liLoop);
						lbFinished=false;
						--liLoop;
					}
				}
			}
		}
	}

	miItems++;
};

void cClusterList::GenerateClusters(cFullFaceList &ClusterData)
{

GenerateConvex(ClusterData);
GenerateConcaves(ClusterData);

};




void cCluster::Order()
{
	/*
	 * Find Starting point for planes (IE Furthest from Centre)
	 *
	 */
	float lfFurthestDist=0;
	uint32 liFurthestPlane=0;
	uint32 liCount;
	for(liCount=0;liCount<miItems;++liCount)
	{
		if(Faces[liCount].Plane.Distance()>lfFurthestDist)
		{
			lfFurthestDist=Faces[liCount].Plane.Distance();
			liFurthestPlane=liCount;
		}
	}
	Switch(0,liCount);

	/*
	 * This will order the rest of the planes by selecting the plane which is
	 * overall furthest from all the sorted planes.
	 */
	//liCount is the number of positions (at the start) which are ordered.
	uint32 liLoop;
	for(liCount=1;liCount<miItems-1;++liCount)
	{
		lfFurthestDist=0;
		liFurthestPlane=0;
		//liLoop will go through every un sorted face to test them.
		for(liLoop=liCount;liLoop<miItems;++liLoop)
		{
			uint32 liGetDist;
			double lfAbsoluteDist=0.0f;
			//liGetDist will calculate plane[liLoops] distance to every plane[liGetDist] face.
			for(liGetDist=0;liGetDist<liCount;++liGetDist)
			{
				lfAbsoluteDist+=Faces[liLoop].Plane.AbsoluteDistance(Faces[liGetDist].Plane);
			}
			if(lfAbsoluteDist>lfFurthestDist)
			{
				lfFurthestDist=lfAbsoluteDist;
				liFurthestPlane=liLoop;
			}
		}
		Switch(liLoop,liCount);
	}
};

void cCluster::Remove(uint32 li1)
{
	if(li1<miItems)
	{
	memcpy(&Faces[li1],&Faces[li1+1],sizeof(cFace)*(miItems-li1-1));
	--miItems;
	}
}

void cCluster::Strip()
{
	uint32 liCount;
	uint32 liLoop;
	for(liCount=0;liCount<miItems-1;++liCount)
	{
		for(liLoop=liCount+1;liLoop<miItems;++liLoop)
		{
			if(Faces[liCount].Plane==Faces[liLoop].Plane) {Remove(liLoop); liLoop=liCount;}
		}
	}
};

void cCluster::Switch(uint32 li1,uint32 li2)
{
	cFace lcTemp;
	lcTemp=Faces[li1];
	Faces[li1]=Faces[li2];
	Faces[li2]=lcTemp;
};


	cCluster::~cCluster(){if(Faces) delete []Faces; Faces=0;miSpaces=miItems=0;};
	cCluster::cCluster(){Faces=0;miSpaces=miItems=0;};
	void cCluster::Init(uint32 liSize){if(Faces) delete []Faces; miSpaces=liSize; Faces=new cFace[miSpaces]; miItems=0;};
	void cCluster::Optimise(){Strip();Order();Resize();};

	uint32 cCluster::FileSize()
	{
		uint32 liSize=0;
		uint32 liCount;
		for(liCount=0;liCount<miItems;++liCount)
		{
			liSize+=Faces[liCount].FileSize();
		}
		liSize+=sizeof(uint32);
		return liSize;
	};

uint32 cCluster::Items(){return miItems;};
cFace cCluster::Face(uint32 li1){return Faces[li1];};
void cCluster::Resize()
{
	 cFace *lpTemp;
	 lpTemp=new cFace[miItems];
	 uint32 liCount;
	 for(liCount=0;liCount<miItems;++liCount)
	 {
	  lpTemp[liCount]=Faces[liCount];
	 }
	 delete []Faces;
	 Faces=lpTemp;
	 miSpaces=miItems;
};

	void cCluster::OutputIMFClusters(ofstream &FileStream)
	{
		FileStream.write((int8 *) &miItems,sizeof(uint32));
		uint32 liCount;
		for(liCount=0;liCount<miItems;++liCount)
		{
			Faces[liCount].OutputIMFFace(FileStream);
		}
	};

	void cCluster::LoadIMFClusters(ifstream &FileStream)
	{
		uint32 liCount;
		FileStream.read((int8 *) &liCount,sizeof(uint32));
		Init(liCount);
		for(liCount=0;liCount<miItems;++liCount)
		{
			Faces[liCount].LoadIMFFace(FileStream);
		}

	};
