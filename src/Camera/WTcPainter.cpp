#include "../WTBamboo.h"

void *cPainter::lpValue=0;

/*
cPainter *cPainter::Instance()
{

 if(!mpInstance) { mpInstance=new cPainter(); mpInstance->Resize(WT_PAINTER_STARTING_SIZE);}
 return mpInstance;
}
*/
cPainter::cPainter()//uint32 liSize)
{

 mpList=0;
 mpBucket=0;
 miSize=0;
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


  lfX=mpList[liPass]->mpObject->mmTotalCache.Matrix()[12];
  lfY=mpList[liPass]->mpObject->mmTotalCache.Matrix()[13];
  lfZ=mpList[liPass]->mpObject->mmTotalCache.Matrix()[14];

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
  for(liFindPos=0;liFindPos<miPos;++liFindPos)
  {
	  ++lpStarts[(mpList[liFindPos]->mpShader>>liPass)&0xff];

}

  //Convert bucket sizes to bucket starts.
  liSum=liOld=0;
  for(liFindPos=0;liFindPos<0x100;++liFindPos)
  {
   liSum+=lpStarts[liFindPos];
   lpStarts[liFindPos]=liOld;
   liOld=liSum;
  }

  //Fill the Buckets.
  for(liFindPos=0;liFindPos<miPos;++liFindPos)
  {
	  mpBucket[(lpStarts[(mpList[liFindPos]->mpShader>>liPass)&0xff])++]=mpList[liFindPos];

}

  lpSwitch=mpBucket;
  mpBucket=mpList;
  mpList=lpSwitch;
}
}

void cPainter::SortByTexture(uint8 liTexSlot)
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
  for(liFindPos=0;liFindPos<miPos;++liFindPos)
  {
	   mpList[liFindPos]->UpdateTexture(liTexSlot);
	  ++lpStarts[(mpList[liFindPos]->mpTexture>>liPass)&0xff];

  }

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

void cPainter::ShaderState(cShaderProgram *mpCurrent,cShaderProgram *mpLast)
{

   if(mpCurrent!=mpLast)
   {
    mpCurrent->Use();
	mpCurrent->SetShaderVariables();
   }
//  else if(mpLast) {_USE_FIXED_FUNCTION();}
}


void cPainter::DepthState(bool mpCurrent,bool mpLast)
{
  if(mpCurrent != mpLast)
  {
   if(mpCurrent) glDisable(GL_DEPTH_TEST);
   else glEnable(GL_DEPTH_TEST);
  }
}

void cPainter::Render()
{


 uint32 liCount;

 SortByDistance();
for(liCount=0;liCount<WT_TEXTURE_NUMBER_ALLOWED;++liCount)
{
 SortByTexture(liCount);
}

 SortByShader();


 SortByAlpha();

glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_NORMAL_ARRAY);
glEnable(GL_DEPTH_TEST);
 for(liCount=0;liCount<miPos;liCount++)
 {

  if(liCount)
  {
   uint8 liTexSlot;
    for(liTexSlot=0;liTexSlot<WT_TEXTURE_NUMBER_ALLOWED;++liTexSlot)
    {
            mpList[liCount]->mpObject->TextureItem(liTexSlot).TextureState(&(mpList[liCount-1]->mpObject->TextureItem(liTexSlot)),liTexSlot);
    }
    ShaderState(mpList[liCount]->ShaderPoint,mpList[liCount-1]->ShaderPoint);
    DepthState(mpList[liCount]->mbAlpha,mpList[liCount-1]->mbAlpha);
  }
  else
  {

      uint8 liTexSlot;
    for(liTexSlot=0;liTexSlot<WT_TEXTURE_NUMBER_ALLOWED;++liTexSlot)
    {
	  mpList[liCount]->mpObject->TextureItem(liTexSlot).FirstTextureState(liTexSlot);
    }
    ShaderState(mpList[liCount]->ShaderPoint,0);
  if(mpList[liCount]->mbAlpha) glDisable(GL_DEPTH_TEST);
  else glEnable(GL_DEPTH_TEST);
  }

  #if WT_FULL_VERSION_BAMBOO
    if(_LIGHT->AnyLights() && mpList[liCount]->mpObject->Lighting()) _LIGHT->PrepareLight(&(mpList[liCount]->mpObject->mmCache));
  #endif


	mpList[liCount]->mpObject->RenderPainter();

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
