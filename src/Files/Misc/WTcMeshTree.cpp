#include "../../WTDivWin.h"

cMeshTreeArray::cMeshTreeArray()
{
 mpRef=0;
 mpList=0;
 miTreeLength=0;
}

cMeshTreeArray::~cMeshTreeArray()
{
 if(mpRef) delete []mpRef;
}


cMeshTree::~cMeshTree()
{
 if(mpList) delete []mpList; 
}

cMeshTree::cMeshTree(cMeshTreeArray *lpArray)
{
 if(lpArray->mpRef)
 {
  strcpy(mpFileName,lpArray->mpRef);
 }
 else
 {  mpFileName[0]=0; }
 
 mpList=lpArray->mpList;
 miTreeLength=lpArray->miTreeLength;
 FindSize();
}

float cMeshTree::FindSize()
{
 float lfPos[miTreeLength][4];
 mfSize=0.0f;
 uint32 liListPos;
 uint32 miLevel=0;
for(liListPos=0;liListPos<miTreeLength;++liListPos)
 {
	  miLevel=mpList[liListPos].miLevel;
	  if(miLevel)
	  {
	  if(mpList[liListPos].mpPosition)
	  {
	    lfPos[miLevel][0]=lfPos[miLevel-1][0]+mpList[liListPos].mpPosition[0];
	    lfPos[miLevel][1]=lfPos[miLevel-1][1]+mpList[liListPos].mpPosition[1];
	    lfPos[miLevel][2]=lfPos[miLevel-1][2]+mpList[liListPos].mpPosition[2];
	    lfPos[miLevel][3]=lfPos[miLevel][0]*lfPos[miLevel][0]+lfPos[miLevel][1]*lfPos[miLevel][1]+lfPos[miLevel][2]*lfPos[miLevel][2];
	  } else lfPos[miLevel][3]=0.0f;
	  }
	  else
	  {
	    if(mpList[liListPos].mpPosition)
	    {
	      lfPos[miLevel][0]=mpList[liListPos].mpPosition[0];
	      lfPos[miLevel][1]=mpList[liListPos].mpPosition[1];
	      lfPos[miLevel][2]=mpList[liListPos].mpPosition[2];
	      lfPos[miLevel][3]=lfPos[miLevel][0]*lfPos[miLevel][0]+lfPos[miLevel][1]*lfPos[miLevel][1]+lfPos[miLevel][2]*lfPos[miLevel][2];
	    } else lfPos[miLevel][3]=0.0f;
	  }
	    if(mpList[liListPos].Mesh())
	    {
	      if(lfPos[miLevel][3]+mpList[liListPos].Mesh()->GetSize()>mfSize) mfSize=lfPos[miLevel][3]+mpList[liListPos].Mesh()->GetSize();
	    }
 }
 return mfSize;
}


