#include "stdafx.h"
#include "../../WTBamboo.h"

vCollisionData *cCompoundCollisionFileNode::GetPointer()
{
 if(!mpPointer) GeneratePointer();
 return mpPointer;
};

void cCompoundCollisionFileNode::GeneratePointer()
{
    #if WT_FULL_VERSION_BAMBOO
    if(Type()==IMF_CCN_REFERENCE)
	{
		mpPointer=_GET_COLLISION_MESH_FILE(mcReference.c_str());
	}
    if(Type()==IMF_CCN_RADIUS)
    {
            delete mpPointer;
            mpPointer=new cSphereCollision();
            mpPointer->SetSize(*mpData);
    }
    if(Type()==IMF_CCN_BOX)
    {
        delete mpPointer;
        cMeshCollision *lpPointer=new cMeshCollision();
        lpPointer->BuildObject(mpData);
        mpPointer=lpPointer;
    }
    if(Type()==IMF_CCN_UNDEFINED)
    {
        mpPointer=0;
    }
    #else
        mpPointer=0;
    #endif

}

bool cCompoundCollisionFileNode::Compare(cCompoundCollisionFileNode *lpOther)
{
    if(Type()==lpOther->Type())
    {
        if(Type()==IMF_CCN_REFERENCE) return !mcReference.compare(lpOther->mcReference);
        if(Type()==IMF_CCN_RADIUS) return *mpData==*(lpOther->mpData);
        if(Type()==IMF_CCN_BOX)
        {
            return( mpData[0]==lpOther->mpData[0] &&
                    mpData[1]==lpOther->mpData[1] &&
                    mpData[2]==lpOther->mpData[2] &&
                    mpData[3]==lpOther->mpData[3] &&
                    mpData[4]==lpOther->mpData[4] &&
                    mpData[5]==lpOther->mpData[5]);
        }
        if(Type()==IMF_CCN_UNDEFINED) return 1;
    }
    return 0;
};

cCompoundCollisionFileNode::cCompoundCollisionFileNode()
{
    mpData=0;
    mpPointer=0;
    miType=IMF_CCN_UNDEFINED;
};
cCompoundCollisionFileNode::cCompoundCollisionFileNode(string lcName)
{
    mcReference=lcName;
    mpData=0;
    mpPointer=0;
    miType=IMF_CCN_REFERENCE;
};
cCompoundCollisionFileNode::cCompoundCollisionFileNode(float lfData)
{
    mpData=new float;
    *mpData=lfData;
    miType=IMF_CCN_RADIUS;
    mpPointer=0;
};
cCompoundCollisionFileNode::cCompoundCollisionFileNode(float *lfData)
{
    mpData=new float[6];
    memcpy(mpData,lfData,sizeof(float)*6);
    miType=IMF_CCN_BOX;
    mpPointer=0;
};

uint8 cCompoundCollisionFileNode::GetFileSize()
{
            if(Type()==IMF_CCN_REFERENCE) return sizeof(uint8)+sizeof(uint32)+mcReference.length()*sizeof(char);
            if(Type()==IMF_CCN_RADIUS) return sizeof(uint8)+sizeof(float);
            if(Type()==IMF_CCN_BOX) return sizeof(uint8)+sizeof(float)*6;
            if(Type()==IMF_CCN_UNDEFINED) return sizeof(uint8);
            return 0;
}

void cCompoundCollisionFileNode::ClearData()
{
        if(Type()==IMF_CCN_BOX) {delete []mpData; delete mpPointer;}
        if(Type()==IMF_CCN_RADIUS) {delete mpData; delete mpPointer; }
        mpData=0;
        mpPointer=0;
}

cCompoundCollisionFileNode::~cCompoundCollisionFileNode()
{
    ClearData();
}


string cCompoundCollisionFileNode::Reference()
{
    return mcReference;
};

float cCompoundCollisionFileNode::Radius()
{
    if(Type()==IMF_CCN_RADIUS) return *mpData;
    return 0.0f;
};
float *cCompoundCollisionFileNode::BoxBounds()
{
    if(Type()==IMF_CCN_BOX) return mpData;
    return 0;
}

uint8 cCompoundCollisionFileNode::Type()
{
    return miType;
};

void cCompoundCollisionFileNode::OutputIMF(ofstream &FileStream)
{
    FileStream.write((char*)&miType,sizeof(uint8));
    if(Type()==IMF_CCN_REFERENCE)
    {
        uint32 liSize;
        liSize=mcReference.length();
        FileStream.write((char*)&liSize,sizeof(uint32));
        FileStream.write(mcReference.c_str(),sizeof(char)*liSize);
    }
    if(Type()==IMF_CCN_RADIUS)
    {
        FileStream.write((char*)mpData,sizeof(float));
    }
    if(Type()==IMF_CCN_BOX)
    {
        FileStream.write((char*)mpData,sizeof(float)*6);
    }
}

void cCompoundCollisionFileNode::LoadIMF(ifstream &FileStream)
{
    ClearData();
    FileStream.read((char*)&miType,sizeof(uint8));
    if(Type()==IMF_CCN_REFERENCE)
    {
        uint32 liSize;
        FileStream.read((char*)&liSize,sizeof(uint32));
        char *lpFileName=new char[liSize+1];
        FileStream.read(lpFileName,sizeof(char)*liSize);
        lpFileName[liSize]=0;
        mcReference=lpFileName;
		delete []lpFileName;
    }
    if(Type()==IMF_CCN_RADIUS)
    {
        mpData=new float;
        FileStream.read((char*)mpData,sizeof(float));
    }
    if(Type()==IMF_CCN_BOX)
    {
        mpData=new float[6];
        FileStream.read((char*)mpData,sizeof(float)*6);
    }
    GeneratePointer();
}


cCompoundCollisionFile::cCompoundCollisionFile()
{

}
cCompoundCollisionFile::~cCompoundCollisionFile()
{

}


void cCompoundCollisionFile::OutputIMF(ofstream &FileStream)
{
 uint32 liBuff;
 liBuff=IMF_TYPE_COMPOUND_COLLISION_OBJECT;
 FileStream.write((int8 *) &liBuff,sizeof(uint32));

 liBuff=sizeof(uint32)+sizeof(int8)*StrLength(mpFileName);
 uint32 liCount;
 for(liCount=0;liCount<mpList.Items();++liCount)
 {
     liBuff+=mpList[liCount]->GetFileSize();
 }
 FileStream.write((int8 *)&liBuff,sizeof(uint32));

 liBuff=StrLength(mpFileName);
 FileStream.write((int8 *)&liBuff,sizeof(uint32));
 FileStream.write(mpFileName,sizeof(int8)*liBuff);


 liBuff=mpList.Items();
 FileStream.write((char*)&liBuff,sizeof(uint32));
 for(liCount=0;liCount<liBuff;++liCount)
 {
    mpList[liCount]->OutputIMF(FileStream);
 }

}

void cCompoundCollisionFile::LoadIMF(ifstream &FileStream)
{

 uint32 liBuff;
 FileStream.ignore(sizeof(uint32));

 FileStream.read((int8 *)&liBuff,sizeof(uint32));

 FileStream.read(mpFileName,sizeof(int8)*liBuff);
 mpFileName[liBuff]=0;


 FileStream.read((char*)&liBuff,sizeof(uint32));
 mpList.Init(liBuff);


 uint32 liCount;
 for(liCount=0;liCount<liBuff;++liCount)
 {
     mpList.Add(new cCompoundCollisionFileNode);
     mpList[liCount]->LoadIMF(FileStream);
 }
}

cCompoundCollisionFileNode *cCompoundCollisionFile::operator[](uint32 liPos)
{
    return mpList[liPos];
};

/*

void cCompoundCollisionFile::Remove(uint32 liPos)
{
    mpList.Remove(liPos);
}
*/
vCollisionData *cCompoundCollisionFile::GetPointer(uint32 liPos)
{
    return mpList[liPos]->GetPointer();
}

uint32 cCompoundCollisionFile::Items()
{
	return mpList.Items();
};
