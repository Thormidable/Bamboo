#ifndef __WTCVERTEX_H__
#define __WTCVERTEX_H__

class cFace;
class cPolygon;
class cCluster;
class cFullFaceData;
class cFullFaceList;

class cVertex
{

public:
	float mpData[3];
	cVertex(){mpData[0]=mpData[1]=mpData[2]=0.0f;};
	cVertex(float *lp1){memcpy(mpData,lp1,sizeof(float)*3);};
	//~cVertex(){};
	void SetVertex(float x,float y,float z){mpData[0]=x; mpData[1]=y; mpData[2]=z;};
	void SetVertex(float *lpData){memcpy(mpData,lpData,sizeof(float)*3);};
	float *Verteces(){return mpData;};
	float X(){return mpData[0];};
	float Y(){return mpData[1];};
	float Z(){return mpData[2];};

	void X(float lfX){mpData[0]=lfX;};
	void Y(float lfY){mpData[1]=lfY;};
	void Z(float lfZ){mpData[2]=lfZ;};

	float &operator[](uint8 liPos){return mpData[liPos];};
	bool operator==(cVertex &lpOther){return (mpData[0]==lpOther.mpData[0] && mpData[1]==lpOther.mpData[1] && mpData[2]==lpOther.mpData[2]);};
	bool operator==(float *lpOther){return (!memcmp(mpData,lpOther,sizeof(float)*3));};
	cVertex &operator=(cVertex &lpOther){memcpy(mpData,lpOther.mpData,sizeof(float)*3);return this[0];};
	float *operator=(float *lpOther){memcpy(mpData,lpOther,sizeof(float)*3);return mpData;};
	float *Data(){return mpData;};

	bool Similar(cVertex lpOther);


	void Display()
	{
		printf("Vertex : %f %f %f\n",mpData[0],mpData[1],mpData[2]);
	}

	uint32 FileSize()
	{
		return sizeof(float)*3;
	};

	double SqrDistance(){return mpData[0]*mpData[0]+mpData[1]*mpData[1]+mpData[2]*mpData[2];};
	double Distance(){return sqrt(mpData[0]*mpData[0]+mpData[1]*mpData[1]+mpData[2]*mpData[2]);};

	void OutputIMFVertex(ofstream &FileStream)
	{
		FileStream.write((char *) mpData,FileSize());
	};

	void LoadIMFVertex(ifstream &FileStream)
	{
		FileStream.read((char *) mpData,FileSize());
	};

	double AbsoluteDistance(cVertex &lpOther);

};

class cVertexList : public cLimitedList<cVertex>
{
public:
	cVertexList(){};

	~cVertexList(){};
	void GenerateVerteces(float *lpVerteces,uint32 liVerteces);
	void GenerateVerteces(cVertex *lpVerteces,uint32 liVerteces);

	void Display()
	{
		uint32 liCount;
		for(liCount=0;liCount<Items();++liCount)
		{
			mpList[liCount].Display();
		}
	}

	void Optimise()
	{
		Strip();
		OrderDistance();
	};

	void OrderDistance();

	void Strip();

	void LoadIMFVerteces(ifstream &FileStream);

	void OutputIMFVerteces(ofstream &FileStream);

	uint32 FileSize();
};


#endif