#include "stdafx.h"
#include "../../WTBamboo.h"

void cReferenceList::LoadIMF(ifstream &FileStream)
{

 uint32 liBuff;
 uint32 liCount;

 FileStream.read((int8*) &liBuff,sizeof(uint32));
 miLength=liBuff;
 mpReferenceList=new char*[miLength];

 for(liCount=0;liCount<miLength;++liCount)
 {
    FileStream.read((int8 *) &liBuff,sizeof(uint32));
    mpReferenceList[liCount]=new char[liBuff+1];
    memset(mpReferenceList[liCount],0,sizeof(char)*liBuff);

    FileStream.read(mpReferenceList[liCount],sizeof(int8)*liBuff);
    //Believes that this is an invalid write
    mpReferenceList[liCount][liBuff]=0;
    trace("Loaded Reference " << mpReferenceList[liCount]);
 }
}

cReferenceList::~cReferenceList()
{
 uint32 liCount;
 for(liCount=0;liCount<miLength;++liCount)
 {
  if(mpReferenceList[liCount]) {delete[] mpReferenceList[liCount]; mpReferenceList[liCount]=0;}
 }
 if(mpReferenceList){delete[] mpReferenceList; mpReferenceList=0;}
}

int8 *cReferenceList::Reference(uint32 liID)
{
 return mpReferenceList[liID];
}

uint32 cReferenceList::Size()
{
 return miLength;
}
