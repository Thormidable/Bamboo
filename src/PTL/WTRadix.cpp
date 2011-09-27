#include "../WTDivWin.h"


void RadixSort(unsigned int *lpList,unsigned int *lpBucket,unsigned int liSize)
{
 unsigned short liPass;
 unsigned int liPos;
 unsigned int liSum,liOld;
 unsigned int *lpSwitch;
 unsigned int lpStarts[0x100];

for(liPass=0;liPass<25;liPass+=8)
{
  //Reset the bucket sizes
  memset(lpStarts,0,1024);
 //Find the size of each bucket;
  for(liPos=0;liPos<liSize;++liPos) {++lpStarts[(lpList[liPos]>>liPass)&0xff];}

  //Convert bucket sizes to bucket starts.
  liSum=liOld=0;
  for(liPos=0;liPos<0x100;++liPos)
  {
   liSum+=lpStarts[liPos];
   lpStarts[liPos]=liOld;
   liOld=liSum;
  }

  //Fill the Buckets.
  for(liPos=0;liPos<liSize;++liPos){lpBucket[lpStarts[(lpList[liPos]>>liPass)&0xff]++]=lpList[liPos];}

  lpSwitch=lpBucket;
  lpBucket=lpList;
  lpList=lpSwitch;
}
}


void RadixSort(int *lpList,int *lpBucket,unsigned int liSize)
{
 unsigned short liPass;
 unsigned int liPos;
 unsigned int liSum,liOld;
 int *lpSwitch;
 unsigned int lpStarts[0x100];

for(liPass=0;liPass<17;liPass+=8)
{
  //Reset the bucket sizes
  memset(lpStarts,0,1024);
 //Find the size of each bucket;
  for(liPos=0;liPos<liSize;++liPos) {++lpStarts[(lpList[liPos]>>liPass)&0xff];}

  //Convert bucket sizes to bucket starts.
  liSum=liOld=0;
  for(liPos=0;liPos<0x100;++liPos)
  {
   liSum+=lpStarts[liPos];
   lpStarts[liPos]=liOld;
   liOld=liSum;
  }

  //Fill the Buckets.
  for(liPos=0;liPos<liSize;++liPos){lpBucket[lpStarts[(lpList[liPos]>>liPass)&0xff]++]=lpList[liPos];}

  lpSwitch=lpBucket;
  lpBucket=lpList;
  lpList=lpSwitch;
}

  memset(lpStarts,0,1024);
 //Find the size of each bucket;
  for(liPos=0;liPos<liSize;++liPos) {++lpStarts[((lpList[liPos]>>liPass)&0xff)^0x80];}

  //Convert bucket sizes to bucket starts.
  liSum=liOld=0;
  for(liPos=0;liPos<0x100;++liPos)
  {
   liSum+=lpStarts[liPos];
   lpStarts[liPos]=liOld;
   liOld=liSum;
  }

  for(liPos=0;liPos<liSize;++liPos){lpBucket[lpStarts[((lpList[liPos]>>liPass)&0xff)^0x80]++]=lpList[liPos];}
}

void RadixSort(float *lpfList,float *lpfBucket,unsigned int liSize)
{

 int *lpList,*lpBucket;
 lpList=(int*)lpfList;
 lpBucket=(int*)lpfBucket;

 unsigned short liPass;
 unsigned int liPos;
 unsigned int liSum,liOld;
 int *lpSwitch;
 unsigned int lpStarts[0x100];

for(liPass=0;liPass<25;liPass+=8)
{
  //Reset the bucket sizes
  memset(lpStarts,0,1024);
 //Find the size of each bucket;
  for(liPos=0;liPos<liSize;++liPos) {++lpStarts[(lpList[liPos]>>liPass)&0xff];}

  //Convert bucket sizes to bucket starts.
  liSum=liOld=0;
  for(liPos=0;liPos<0x100;++liPos)
  {
   liSum+=lpStarts[liPos];
   lpStarts[liPos]=liOld;
   liOld=liSum;
  }

  //Fill the Buckets.
  for(liPos=0;liPos<liSize;++liPos){lpBucket[lpStarts[(lpList[liPos]>>liPass)&0xff]++]=lpList[liPos];}

  //Switch the Bucket and List arrays
  lpSwitch=lpBucket;
  lpBucket=lpList;
  lpList=lpSwitch;
}

if(lpList[liSize-1]<0)
{
 //liPass is recording the position to copy to.
 liPass=0;
 liPos=liSize-1;
 //LiPos will start with the MOST negative value
 while(liPos>0)
 {
  //When reach the +ve Values switch mode
  if(lpList[liPos]>=0) break;
  //Copy values from one list to the next
  lpBucket[liPass]=lpList[liPos];

  //Update pointers
  ++liPass;
  --liPos;
 }

 //New mode, look for smallest positive values
 liPos=0;
 while(liPass<liSize)
 {
  //copy values
  lpBucket[liPass]=lpList[liPos];
  //update Values
  ++liPos;
  ++liPass;
 }
memcpy(lpList,lpBucket,liSize*4);
}

}














//This may not work please check
template<class cValue> void RadixSort(cValue *lpvList,cValue *lpvBucket,unsigned int liSize)
{
 int *lpList,*lpBucket;
 lpList=(int*)lpvList;
 lpBucket=(int*)lpvBucket;

 char lcSizeof=sizeof(cValue)*8;
 char lcGroup=lcSizeof/32;

 unsigned short liPass;
 unsigned int liPos;
 unsigned int liSum,liOld;
 int *lpSwitch;
 unsigned int lpStarts[0x100];

 char lcSign;

for(liPass=0;liPass<lcSizeof;liPass+=8)
{
  //Reset the bucket sizes
  memset(lpStarts,0,32*lcSizeof);
 //Find the size of each bucket;
  for(liPos=0;liPos<liSize;liPos+=lcGroup){++lpStarts[(lpList[liPos]>>liPass)&0xff];}

  //Convert bucket sizes to bucket starts.
  liSum=liOld=0;
  for(liPos=0;liPos<0x100;++liPos)
  {
   liSum+=lpStarts[liPos]*lcGroup;
   lpStarts[liPos]=liOld;
   liOld=liSum;
  }

  //Fill the Buckets.
  for(liPos=0;liPos<liSize;++liPos)
  {
   lpBucket[lpStarts[(lpList[liPos]>>liPass)&0xff]]=lpList[liPos];
   lpStarts[(lpList[liPos]>>liPass)&0xff]+=lcGroup;
  }

  //Switch the Bucket and List arrays
  lpSwitch=lpBucket;
  lpBucket=lpList;
  lpList=lpSwitch;
}

}
