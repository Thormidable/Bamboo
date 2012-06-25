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

 mpList=new cRenderPointer*[WT_PAINTER_STARTING_SIZE];
 mpBucket=new cRenderPointer*[WT_PAINTER_STARTING_SIZE];
 memset(mpList,0,sizeof(cRenderPointer*)*WT_PAINTER_STARTING_SIZE);
 memset(mpBucket,0,sizeof(cRenderPointer*)*WT_PAINTER_STARTING_SIZE);
 miSize=WT_PAINTER_STARTING_SIZE;

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
  memset(&lpTemp[miSize],0,sizeof(cRenderPointer*)*(liSize-miSize));
  delete []mpList;
  mpList=lpTemp;

  lpTemp=new cRenderPointer*[liSize];
  memcpy(lpTemp,mpBucket,sizeof(cRenderPointer*)*miSize);
  memset(&lpTemp[miSize],0,sizeof(cRenderPointer*)*(liSize-miSize));
  delete []mpBucket;
  mpBucket=lpTemp;

  miSize=liSize;

}

void cPainter::Add(cRenderPointer *lfData)
{

if(miPos>=miSize) {Resize(miSize*2);}
 mpList[miPos]=lfData;
 ++miPos;
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
	  //Apparently uninitialised value here!
	  //On first pass, mmTotalCache is based un uninitialised values.
	  //Not necessary to fix.
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
    //Believes something is not initialised.
    //On first pass, mmTotalCache is based un uninitialised values.
	  //Not necessary to fix.
	mpBucket[(lpStarts[(mpList[liFindPos]->miDist>>liPass)&0xff])++]=mpList[liFindPos];
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
    /*
unsigned int liStart,liEnd,liPos;
cRenderPointer **lpSwitch;
liEnd=miPos-1;
liPos=liStart=0;
for(liPos=0;liPos<miPos;++liPos)
{if(mpList[liPos]->miAlpha){mpBucket[liEnd--]=mpList[liPos];}
 else{mpBucket[liStart++]=mpList[liPos];}
}
lpSwitch=mpBucket;
mpBucket=mpList;
mpList=lpSwitch;*/


  unsigned int liFindPos;
 unsigned int liSum,liOld;
 cRenderPointer **lpSwitch;
 uint32 lpStarts[0x100];

  //Reset the bucket sizes
  memset(lpStarts,0,1024);
 //Find the size of each bucket;
  for(liFindPos=0;liFindPos<miPos;++liFindPos)
  {
	  ++lpStarts[(mpList[liFindPos]->miAlpha)&0xff];
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
	  mpBucket[(lpStarts[(mpList[liFindPos]->miAlpha)&0xff])++]=mpList[liFindPos];
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


void cPainter::DepthState(uint8 mpCurrent,uint8 mpLast)
{
  if(mpCurrent && !mpLast)
  {
   glDepthMask(GL_FALSE);
   return;
  }

  if(!mpCurrent && mpLast) glDepthMask(GL_TRUE);
}

void cPainter::Render()
{
if(miPos)
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

       ShaderState(mpList[0]->ShaderPoint,0);
          uint8 liTexSlot;
        for(liTexSlot=0;liTexSlot<WT_TEXTURE_NUMBER_ALLOWED;++liTexSlot)
        {
          mpList[0]->mpObject->TextureItem(liTexSlot).FirstTextureState(liTexSlot);
        }

      if(mpList[0]->miAlpha) glDepthMask(GL_FALSE);
      else glDepthMask(GL_TRUE);

      #if WT_FULL_VERSION_BAMBOO
        if(_LIGHT->AnyLights() && mpList[0]->mpObject->Lighting()) _LIGHT->PrepareLight(&(mpList[0]->mpObject->mmCache));
      #endif

        if(mpList[0]->mpShader) mpList[0]->mpObject->RenderPainter();

     for(liCount=1;liCount<miPos;liCount++)
     {
          ShaderState(mpList[liCount]->ShaderPoint,mpList[liCount-1]->ShaderPoint);
       uint8 liTexSlot;

    if(mpList[liCount]->ShaderPoint!=mpList[liCount-1]->ShaderPoint)
    {
        for(liTexSlot=0;liTexSlot<WT_TEXTURE_NUMBER_ALLOWED;++liTexSlot)
        {
                mpList[liCount]->mpObject->TextureItem(liTexSlot).FirstTextureState(liTexSlot);
        }
    }
    else
    {
        for(liTexSlot=0;liTexSlot<WT_TEXTURE_NUMBER_ALLOWED;++liTexSlot)
        {
                mpList[liCount]->mpObject->TextureItem(liTexSlot).TextureState(&(mpList[liCount-1]->mpObject->TextureItem(liTexSlot)),liTexSlot);
        }
    }

	DepthState(mpList[liCount]->miAlpha,mpList[liCount-1]->miAlpha);


      #if WT_FULL_VERSION_BAMBOO
        if(_LIGHT->AnyLights() && mpList[liCount]->mpObject->Lighting()) _LIGHT->PrepareLight(&(mpList[liCount]->mpObject->mmCache));
      #endif

        if(mpList[liCount]->mpShader) mpList[liCount]->mpObject->RenderPainter();

     }
}
	glDepthMask(GL_TRUE);
}

void cPainter::Remove(cRenderPointer *lfSlot)
  {
uint32 liCount;
  for(liCount=0;liCount<miPos;++liCount)
  {
	if(mpList[liCount]==lfSlot)
	{
		  if(miPos-1>liCount) memmove(&mpList[liCount],&mpList[liCount+1],sizeof(cRenderPointer*)*(miPos-liCount-1));
		  else mpList[liCount]=0;
		  --miPos;
		  return;

	}
  }

 }

void cPainter::Reset()
{
  glDisableClientState(GL_TEXTURE_COORD_ARRAY); glDisable(GL_TEXTURE_2D);

};
