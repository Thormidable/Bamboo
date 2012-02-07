#ifndef __WTCCOMPOUNDCOLLISIONFILEOBJECT_H_
#define __WTCCOMPOUNDCOLLISIONFILEOBJECT_H_



class cCompoundCollisionFileNode
{
    string mcReference;
    float *mpData;
    uint8 miType;
    vCollisionData *mpPointer;
public:
    cCompoundCollisionFileNode();
    ~cCompoundCollisionFileNode();
    cCompoundCollisionFileNode(string lcName);
    cCompoundCollisionFileNode(float lfData);
    cCompoundCollisionFileNode(float *lfData);


    string Reference();
    float Radius();
    float *BoxBounds();
    uint8 Type();

    void ClearData();

    uint8 GetFileSize();

    void OutputIMF(ofstream &FileStream);
    void LoadIMF(ifstream &FileStream);

    bool Compare(cCompoundCollisionFileNode *lpOther);

 vCollisionData *GetPointer();
 void GeneratePointer();


};

class cCompoundCollisionFile: public cFile
{
    cLimitedPointerList<cCompoundCollisionFileNode> mpList;

public:
        //cCompoundCollisionFile(cIMFFile *lpFile);
        cCompoundCollisionFile();
        ~cCompoundCollisionFile();

    cCompoundCollisionFileNode *operator[](uint32 liPos);

	void LoadIMF(ifstream &FileStream);
	void OutputIMF(ofstream &FileStream);

	vCollisionData *GetPointer(uint32 liPos);

	uint32 Items();

};


#endif
