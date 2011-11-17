#include "../WTDivWin.h"

void *cPainter::lpValue=0;

cPainter *cPainter::mpInstance=0;


cPainter *cPainter::Instance()
{

 if(!mpInstance) { mpInstance=new cPainter(); mpInstance->Resize(WT_PAINTER_STARTING_SIZE);}
 return mpInstance;
}

cPainter::cPainter()//uint32 liSize)
{

 mpList=0;
 mpBucket=0;
 miSize=0;
// miAllocated=0;
 miPos=0;

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
}

cPainter::~cPainter()
{
if(mpList) {delete []mpList;mpList=0;}
if(mpBucket) {delete []mpBucket; mpBucket=0;}
}

void cPainter::Resize(uint32 liSize)
{
cRenderPointer **lpTemp;

  lpTemp=new cRenderPointer*[liSize];
  memcpy(lpTemp,mpList,sizeof(cRenderPointer*)*miSize);
  delete []mpList;
  mpList=lpTemp;

  lpTemp=new cRenderPointer*[liSize];
  memcpy(lpTemp,mpBucket,sizeof(cRenderPointer*)*miSize);
  delete []mpBucket;
  mpBucket=lpTemp;

  miSize=liSize;

}

void cPainter::Add(cRenderPointer *lfData)
{

if(miPos>=miSize) {Resize(miSize*2);}
 mpList[miPos]=lfData;
 ++miPos;
//return &mpList[miPos-1];
}


void cPainter::SortByDistance()
{

 unsigned short liPass=0;
 unsigned int liFindPos=0;
 unsigned int liSum=0,liOld=0;
 cRenderPointer **lpSwitch=0;
 uint32 lpStarts[0x100];

 memset(lpStarts,0,sizeof(uint32)*0x100);

 for(liPass=0;liPass<miPos;++liPass)
 {

  float lfX,lfY,lfZ;


  lfX=mpList[liPass]->mpObject->mmCache.Matrix()[12];
  lfY=mpList[liPass]->mpObject->mmCache.Matrix()[13];
  lfZ=mpList[liPass]->mpObject->mmCache.Matrix()[14];

  mpList[liPass]->miDist=static_cast<uint32>(lfX*lfX+lfY*lfY+lfZ*lfZ);
 }

for(liPass=0;liPass<25;liPass+=8)
{
  //Reset the bucket sizes
  memset(lpStarts,0,0x100*sizeof(uint32));


 //Find the size of each bucket;
  for(liFindPos=0;liFindPos<miPos;++liFindPos)
  {
	  //Apparently uninitialised value here! Believes that miDist is uninitialised, as comes from mmCache.Matrix()...
	++lpStarts[(mpList[liFindPos]->miDist>>liPass)&0xFF];

  }

  //Convert bucket sizes to bucket starts.
  liSum=0;
  liOld=0;
  for(liFindPos=0;liFindPos<0x100;++liFindPos)
  {
   liSum+=lpStarts[liFindPos];
   lpStarts[liFindPos]=liOld;
   liOld=liSum;
  }

  //Fill the Buckets.
  for(liFindPos=0;liFindPos<miPos;++liFindPos)
  {
    //Believes something is not initialised. lpStarts?
	mpBucket[lpStarts[(mpList[liFindPos]->miDist>>liPass)&0xff]++]=mpList[liFindPos];
  }

  lpSwitch=mpBucket;
  mpBucket=mpList;
  mpList=lpSwitch;
}

}

void cPainter::SortByShader()
{

 unsigned short liPass;
 unsigned int liFindPos;
 unsigned int liSum,liOld;
 cRenderPointer **lpSwitch;
// psize lpStarts[0x100];
  uint32 lpStarts[0x100];

for(liPass=0;liPass<pbits;liPass+=8)
{
  //Reset the bucket sizes
  memset(lpStarts,0,1024);
 //Find the size of each bucket;
  for(liFindPos=0;liFindPos<miPos;++liFindPos) {++lpStarts[(reinterpret_cast<psize>(mpList[liFindPos]->mpShader)>>liPass)&0xff];}

  //Convert bucket sizes to bucket starts.
  liSum=liOld=0;
  for(liFindPos=0;liFindPos<0x100;++liFindPos)
  {
   liSum+=lpStarts[liFindPos];
   lpStarts[liFindPos]=liOld;
   liOld=liSum;
  }

  //Fill the Buckets.
  for(liFindPos=0;liFindPos<miPos;++liFindPos){mpBucket[lpStarts[(reinterpret_cast<psize>(mpList[liFindPos]->mpShader)>>liPass)&0xff]++]=mpList[liFindPos];}

  lpSwitch=mpBucket;
  mpBucket=mpList;
  mpList=lpSwitch;
}
}

void cPainter::SortByTexture()
{
 unsigned short liPass;
 unsigned int liFindPos;
 unsigned int liSum,liOld;
 cRenderPointer **lpSwitch;
 unsigned int lpStarts[0x100];

for(liPass=0;liPass<25;liPass+=8)
{
  //Reset the bucket sizes
  memset(lpStarts,0,1024);
 //Find the size of each bucket;
  for(liFindPos=0;liFindPos<miPos;++liFindPos) {++lpStarts[(mpList[liFindPos]->mpTexture>>liPass)&0xff];}

  //Convert bucket sizes to bucket starts.
  liSum=liOld=0;
  for(liFindPos=0;liFindPos<0x100;++liFindPos)
  {
   liSum+=lpStarts[liFindPos];
   lpStarts[liFindPos]=liOld;
   liOld=liSum;
  }

  //Fill the Buckets.
  for(liFindPos=0;liFindPos<miPos;++liFindPos){mpBucket[lpStarts[(mpList[liFindPos]->mpTexture>>liPass)&0xff]++]=mpList[liFindPos];}

  lpSwitch=mpBucket;
  mpBucket=mpList;
  mpList=lpSwitch;
}
}


void cPainter::SortByAlpha()
{
unsigned int liStart,liEnd,liPos;
cRenderPointer **lpSwitch;
liEnd=miPos-1;
liPos=liStart=0;
for(liPos=0;liPos<miPos;++liPos)
{if(mpList[liPos]->mbAlpha){mpBucket[liEnd--]=mpList[liPos];}
 else{mpBucket[liStart++]=mpList[liPos];}
}
lpSwitch=mpBucket;
mpBucket=mpList;
mpList=lpSwitch;
}

void cPainter::ShaderState(vShaderProgram *mpCurrent,vShaderProgram *mpLast)
{
  if(mpCurrent)
  {
   if(mpCurrent!=mpLast)
   {
    mpCurrent->Use();
   }
  }
  else if(mpLast) {_USE_FIXED_FUNCTION();}
}


void cPainter::TextureState(uint32 mpCurrent,uint32 mpLast)
{

  if(mpCurrent)
  {
   if(!mpLast) {glEnable(GL_TEXTURE_2D); glEnableClientState(GL_TEXTURE_COORD_ARRAY);}
   if(mpCurrent!=mpLast)
   {
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D,mpCurrent);
   }
  }
  else if(mpLast) {glDisableClientState(GL_TEXTURE_COORD_ARRAY); glDisable(GL_TEXTURE_2D);}
}

void cPainter::Render()
{
 uint32 liCount;

 SortByDistance();

 SortByShader();

 SortByTexture();

 SortByAlpha();



glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_NORMAL_ARRAY);
glEnable(GL_DEPTH_TEST);
 for(liCount=0;liCount<miPos;liCount++)
 {

  if(mpList[liCount]->mbReRender)
  {

  if(liCount)
  {
    TextureState(mpList[liCount]->mpTexture,mpList[liCount-1]->mpTexture);
    ShaderState(mpList[liCount]->mpShader,mpList[liCount-1]->mpShader);
  }
  else
  {
    TextureState(mpList[liCount]->mpTexture,0);
    ShaderState(mpList[liCount]->mpShader,0);
  }

#warning comment THIS NEEDS TO BE FIXED FOR MATRIX STACK
  if(mpList[liCount]->mbAlpha) glDisable(GL_DEPTH_TEST);

  mpList[liCount]->mpObject->RenderPainter(mpList[liCount]->miLevel);
  mpList[liCount]->mbReRender=false;
  }
 }
}

void cPainter::Remove(cRenderPointer *lfSlot)
  {
uint32 liCount;
  for(liCount=0;liCount<miPos;++liCount)
  {
	if(mpList[liCount]==lfSlot)
	{
		  if(miPos-liCount) memmove(&mpList[liCount],&mpList[liCount+1],sizeof(cRenderPointer**)*(miPos-liCount)-1);
		  --miPos;
		  return;
	}
  }

 }

void cPainter::Reset()
{
  glDisableClientState(GL_TEXTURE_COORD_ARRAY); glDisable(GL_TEXTURE_2D);

};
