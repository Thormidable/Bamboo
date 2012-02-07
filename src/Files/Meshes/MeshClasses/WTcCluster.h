#ifndef __WTCCLUSTER_H__
#define __WTCCLUSTER_H__

using namespace std;
/** \brief This class is an array of cFace.
 * This is often used
 */
class cCluster
{
	//cPlane *Planes;
	cFace *Faces;
	uint32 miSpaces;
	uint32 miItems;
public:
	~cCluster();
	cCluster();
	void Init(uint32 liSize);
	void Optimise();

	uint32 FileSize();
	
	void Order();
	void Strip();
	void Switch(uint32 li1,uint32 li2);
	void Add(cFullFaceData &lpData);
	void Remove(uint32 li1);
	uint32 Items();
	cFace Face(uint32 li1);
	void Resize();
	void OutputIMFClusters(ofstream &FileStream);
	
	void LoadIMFClusters(ifstream &FileStream);
	
};

class cClusterList : public cLimitedList<cCluster>
{
	
public:
	cClusterList(){};
	~cClusterList(){};
	void Optimise();
	void GenerateClusters(cFullFaceList &ClusterData);
	void GenerateConvex(cFullFaceList &ClusterData);
	void GenerateConcaves(cFullFaceList &ClusterData);

	void OutputIMFClusters(ofstream &FileStream)
	{
		FileStream.write((char *) &miItems,sizeof(uint32));
		uint32 liCount;
		for(liCount=0;liCount<miItems;++liCount)
		{
		 mpList[liCount].OutputIMFClusters(FileStream);
		}
	};
	
	void LoadIMFClusters(ifstream &FileStream)
	{
		uint32 liCount;
		FileStream.read((char *) &liCount,sizeof(uint32));
		Init(liCount);
		for(liCount=0;liCount<miItems;++liCount)
		{
			mpList[liCount].LoadIMFClusters(FileStream);
		}
	};

	uint32 FileSize()
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
};




#endif
