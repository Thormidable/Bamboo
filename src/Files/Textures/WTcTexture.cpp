
#include "../../WTBamboo.h"

using namespace std;

cTextureArray::cTextureArray()
{
 miWidth=0;miHeight=0;miDepth=0;
 mpData=0;
 mpRef=0;
}

cTextureArray::~cTextureArray()
{
 if(mpRef) delete []mpRef;
}

cTexture::cTexture(cTextureArray *lpTexture)
{
 strcpy(mpFileName,lpTexture->mpRef);

 miWidth=lpTexture->miWidth;
 miHeight=lpTexture->miHeight;
 miDepth=lpTexture->miDepth;
 miPixelSize=miDepth>>3;
 mpData=lpTexture->mpData;

 glGenTextures(1, &miTexture);
 BufferTexture();
}

void cTexture::BufferTexture()
{
BindTexture();

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

glEnable(GL_TEXTURE_2D);

if(WT_ALLOW_DYNAMIC_TEXTURES) glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
else glGenerateMipmap(GL_TEXTURE_2D);



if(miDepth==24) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width(),Height(), 0, GL_BGR, GL_UNSIGNED_BYTE,mpData);
if(miDepth==32) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width(),Height(), 0, GL_BGRA, GL_UNSIGNED_BYTE,mpData);
}


cTexture::cTexture()
{
    glGenTextures(1, &miTexture);
};

uint8 *cTexture::Data(){return mpData;}

 cTexture::~cTexture(){if(mpData){delete []mpData;mpData=0;} glDeleteTextures(1,&miTexture);}
    uint32 cTexture::Width(){return miWidth;}
       uint32 cTexture::Height(){return miHeight;}
       uint8 cTexture::Depth(){return miDepth;}
       uint8 cTexture::PixelSize(){return miPixelSize;}
       uint32 cTexture::TextureNumber(){return miTexture;}

cTexture *cTexture::Duplicate()
{
    return Duplicate("GeneratedTexture");
};
cTexture *cTexture::Duplicate(string NewFileName)
{
 cTexture *lpNew=new cTexture;
 lpNew->mpData=new uint8[miWidth*miHeight*miPixelSize];
 memcpy(lpNew->mpData,mpData,sizeof(uint8)*miWidth*miHeight*miPixelSize);
 strcpy(lpNew->mpFileName,NewFileName.c_str());
 lpNew->miWidth=miWidth;
 lpNew->miHeight=miHeight;
 lpNew->miDepth=miDepth;
 lpNew->miPixelSize=miPixelSize;
 lpNew->BufferTexture();
 return lpNew;
 };

 cTexture::cTexture(cTexture *lpOther,string NewFileName)
 {
    miWidth=lpOther->miWidth;
    miHeight=lpOther->miHeight;
    miDepth=lpOther->miDepth;
    miPixelSize=lpOther->miPixelSize;
    glGenTextures(1, &miTexture);
    strcpy(mpFileName,NewFileName.c_str());
    mpData=new uint8[miWidth*miHeight*miPixelSize];
    memcpy(mpData,lpOther->mpData,sizeof(uint8)*miWidth*miHeight*miPixelSize);

    BufferTexture();
 }


uint8 *cTexture::GetPixel(c2DVf lvUV)
{
 //if(lvUV.X()>0.0f && lvUV.X()<1.0f && lvUV.Y()>0.0f && lvUV.Y<1.0f)
 {
     int32 liX=lvUV.X()*miWidth;
     int32 liY=lvUV.Y()*miHeight;
     return &mpData[(liY*miWidth+liX)*miPixelSize];
 }
}

uint8 *cTexture::GetPixel(c2DVi lvXY)
{
 return &mpData[(lvXY.Y()*miWidth+lvXY.X())*miPixelSize];
}


void cTexture::Write(cRGBA Color,c2DVf lvUV)
{
    this->Write(Color,c2DVi(lvUV[0]*miWidth,lvUV[1]*miHeight));
};
void cTexture::Write(cRGBA Color,c2DVi lvXY)
{
    uint8 *lpPixel=GetPixel(lvXY);
    lpPixel[0]=Color.B()*255;
    lpPixel[1]=Color.G()*255;
    lpPixel[2]=Color.R()*255;
    if(miDepth==32) lpPixel[3]=Color.A()*255;
    BindTexture();
    if(miDepth==32) glTexSubImage2D(GL_TEXTURE_2D, 0, lvXY[0], lvXY[1], 1, 1, GL_BGRA, GL_UNSIGNED_BYTE,lpPixel);
    if(miDepth==24) glTexSubImage2D(GL_TEXTURE_2D, 0, lvXY[0], lvXY[1], 1, 1, GL_BGR, GL_UNSIGNED_BYTE,lpPixel);



};

void cTexture::Write(cRGB Color,c2DVf lvUV)
{
    this->Write(Color,c2DVi(lvUV[0]*miWidth,lvUV[1]*miHeight));
};
void cTexture::Write(cRGB Color,c2DVi lvXY)
{
    uint8 *lpPixel=GetPixel(lvXY);
    lpPixel[0]=Color.B()*255;
    lpPixel[1]=Color.G()*255;
    lpPixel[2]=Color.R()*255;


    BindTexture();
    if(miDepth==24) glTexSubImage2D(GL_TEXTURE_2D, 0, lvXY[0], lvXY[1], 1, 1, GL_BGR, GL_UNSIGNED_BYTE,lpPixel);
    if(miDepth==32) glTexSubImage2D(GL_TEXTURE_2D, 0, lvXY[0], lvXY[1], 1, 1, GL_BGRA, GL_UNSIGNED_BYTE,lpPixel);




};

void cTexture::Write(cTexture *lpTexture,c2DVf lvUV)
{
 this->Write(lpTexture,c2DVi(lvUV[0]*miWidth,lvUV[1]*miHeight));
};

void cTexture::Write(cTexture *lpTexture,c2DVi lvXY)
{

 c2DVi TLLC(lvXY[0]-lpTexture->Width()*0.5f,lvXY[1]-lpTexture->Height()*0.5f);
 c2DVi TURC(lvXY[0]+lpTexture->Width()*0.5f,lvXY[1]+lpTexture->Height()*0.5f);

 bool lbAdjusted=false;

 c2DVi OLLC(0,0);
 if(TLLC[0]<0)
 {
     OLLC[0]=-TLLC[0]; TLLC[0]=0; lbAdjusted=true;
     }
 if(TLLC[1]<0)
 {
     OLLC[1]=-TLLC[1]; TLLC[1]=0; lbAdjusted=true;
     }

 c2DVi OURC(lpTexture->Width(),lpTexture->Height());
 if(TURC[0]>miWidth) {
     OURC[0]-=(TURC[0]-miWidth); TURC[0]=miWidth; lbAdjusted=true;
     }
 if(TURC[1]>miHeight) {
     OURC[1]-=(TURC[1]-miHeight); TURC[1]=miHeight; lbAdjusted=true;
     }

 c2DVi TLLCStore=TLLC;
 c2DVi DimensionStore=TURC-TLLC;


 int32 liCopyWidth=(TURC[0]-TLLC[0])*sizeof(uint8);

 if(liCopyWidth>0)
 {
     if(miDepth==lpTexture->miDepth)
     {
         liCopyWidth*=miPixelSize;
        for(;TLLC[1]<TURC[1];++TLLC[1])
        {
            memcpy(GetPixel(c2DVi(TLLC[0],TLLC[1])),lpTexture->GetPixel(c2DVi(OLLC[0],OLLC[1])),liCopyWidth);
            ++OLLC[1];
        }
          if(lbAdjusted==true) UpdateSubImage(TLLCStore,DimensionStore);
          else
          {
            BindTexture();
             if(miDepth==24) glTexSubImage2D(GL_TEXTURE_2D, 0, TLLC[0], TLLC[1], lpTexture->Width(), lpTexture->Height(), GL_BGR,  GL_UNSIGNED_BYTE, lpTexture->Data());
             if(miDepth==32) glTexSubImage2D(GL_TEXTURE_2D, 0, TLLC[0], TLLC[1], lpTexture->Width(), lpTexture->Height(), GL_BGRA, GL_UNSIGNED_BYTE, lpTexture->Data());
          }

     }
     else
     {
         uint32 liX;
         if(miPixelSize<lpTexture->miPixelSize) liX=miPixelSize;
         else liX=lpTexture->miPixelSize;
         for(;TLLC[1]<TURC[1];++TLLC[1])
         {
             for(uint32 liW=0;liW<liCopyWidth;++liW)
             {
               memcpy(GetPixel(c2DVi(TLLC[0]+liW,TLLC[1])),lpTexture->GetPixel(c2DVi(OLLC[0]+liW,OLLC[1])),liX);
             }
             ++OLLC[1];
         }
        UpdateSubImage(TLLCStore,DimensionStore);
     }
 }


};















void cTexture::Blend(cRGBA Color,c2DVf lvUV)
{
    this->Blend(Color,c2DVi(lvUV[0]*miWidth,lvUV[1]*miHeight));
};
void cTexture::Blend(cRGBA Color,c2DVi lvXY)
{
    uint8 lpOverlay[4];
    lpOverlay[0]=(Color.B()*255);
    lpOverlay[1]=(Color.G()*255);
    lpOverlay[2]=(Color.R()*255);
    lpOverlay[3]=(Color.A()*255);
    BlendPixels(GetPixel(lvXY),lpOverlay);

    BindTexture();
    if(miDepth==32) glTexSubImage2D(GL_TEXTURE_2D, 0, lvXY[0], lvXY[1], 1, 1, GL_BGRA, GL_UNSIGNED_BYTE,lpOverlay);
    if(miDepth==24) glTexSubImage2D(GL_TEXTURE_2D, 0, lvXY[0], lvXY[1], 1, 1, GL_BGR, GL_UNSIGNED_BYTE,lpOverlay);
};

void cTexture::Blend(cTexture *lpTexture,c2DVf lvUV)
{
 this->Blend(lpTexture,c2DVi(lvUV[0]*miWidth,lvUV[1]*miHeight));
};

void cTexture::Blend(cTexture *lpTexture,c2DVi lvXY)
{
 if(lpTexture->Depth()==24) {Write(lpTexture,lvXY); return;}

 c2DVi TLLC(lvXY[0]-lpTexture->Width()*0.5f,lvXY[1]-lpTexture->Height()*0.5f);
 c2DVi TURC(lvXY[0]+lpTexture->Width()*0.5f,lvXY[1]+lpTexture->Height()*0.5f);

 bool lbAdjusted=false;

 c2DVi OLLC(0,0);
 if(TLLC[0]<0)
 {
     OLLC[0]=-TLLC[0]; TLLC[0]=0; lbAdjusted=true;
     }
 if(TLLC[1]<0)
 {
     OLLC[1]=-TLLC[1]; TLLC[1]=0; lbAdjusted=true;
     }

 c2DVi OURC(lpTexture->Width(),lpTexture->Height());
 if(TURC[0]>miWidth) {
     OURC[0]-=(TURC[0]-miWidth); TURC[0]=miWidth; lbAdjusted=true;
     }
 if(TURC[1]>miHeight) {
     OURC[1]-=(TURC[1]-miHeight); TURC[1]=miHeight; lbAdjusted=true;
     }

 c2DVi TLLCStore=TLLC;
 c2DVi DimensionStore=TURC-TLLC;


 c2DVi liCopySize=(TURC-TLLC)*sizeof(uint8);

 if(liCopySize[0]>0)
 {
    if(miDepth==32)
    {
         for(;TLLC[1]<TURC[1];++TLLC[1])
         {
             for(uint32 liW=0;liW<liCopySize[0];++liW)
             {
                 uint8 *lpOverlay=lpTexture->GetPixel(c2DVi(OLLC[0]+liW,OLLC[1]));
                if(lpOverlay[3])
                 {
                     uint8 *lpBase=GetPixel(c2DVi(TLLC[0]+liW,TLLC[1]));
                    float lfAlpha=lpOverlay[3]/255;
                    float lfInvAlpha=1.0f-lfAlpha;

                    lpBase[0]=lpOverlay[0]*lfAlpha+lfInvAlpha*lpBase[0];
                    lpBase[1]=lpOverlay[1]*lfAlpha+lfInvAlpha*lpBase[1];
                    lpBase[2]=lpOverlay[2]*lfAlpha+lfInvAlpha*lpBase[2];
                    lpBase[3]=lpBase[3]*lfInvAlpha+lpOverlay[3];
                    }
                 }

 //              BlendPixels(GetPixel(c2DVi(TLLC[0]+liW,TLLC[1])),lpTexture->GetPixel(c2DVi(OLLC[0]+liW,OLLC[1])));
            ++OLLC[1];
             }

                  if(lbAdjusted==true) UpdateSubImage(TLLCStore,DimensionStore);
                  else
                  {
                    BindTexture();
                     if(miDepth==24) glTexSubImage2D(GL_TEXTURE_2D, 0, TLLC[0], TLLC[1], lpTexture->Width(), lpTexture->Height(), GL_BGR,  GL_UNSIGNED_BYTE, lpTexture->Data());
                     if(miDepth==32) glTexSubImage2D(GL_TEXTURE_2D, 0, TLLC[0], TLLC[1], lpTexture->Width(), lpTexture->Height(), GL_BGRA, GL_UNSIGNED_BYTE, lpTexture->Data());
                  }
         }

         if(miDepth==24)
         {
          for(;TLLC[1]<TURC[1];++TLLC[1])
          {
             for(uint32 liW=0;liW<liCopySize[0];++liW)
             {
                 uint8 *lpOverlay=lpTexture->GetPixel(c2DVi(OLLC[0]+liW,OLLC[1]));
                if(lpOverlay[3])
                 {
                     uint8 *lpBase=GetPixel(c2DVi(TLLC[0]+liW,TLLC[1]));
                    float lfAlpha=lpOverlay[3]/255;
                    float lfInvAlpha=1.0f-lfAlpha;

                    lpBase[0]=lpOverlay[0]*lfAlpha+lfInvAlpha*lpBase[0];
                    lpBase[1]=lpOverlay[1]*lfAlpha+lfInvAlpha*lpBase[1];
                    lpBase[2]=lpOverlay[2]*lfAlpha+lfInvAlpha*lpBase[2];
                    }
                 }

 //              BlendPixels(GetPixel(c2DVi(TLLC[0]+liW,TLLC[1])),lpTexture->GetPixel(c2DVi(OLLC[0]+liW,OLLC[1])));
            ++OLLC[1];
             }
             UpdateSubImage(TLLCStore,DimensionStore);
             return;
         }
 }


};
/*
          if(lbAdjusted==true) UpdateSubImage(TLLCStore,DimensionStore);
          else
          {
            BindTexture();
             if(miDepth==24) glTexSubImage2D(GL_TEXTURE_2D, 0, TLLC[0], TLLC[1], lpTexture->Width(), lpTexture->Height(), GL_BGR,  GL_UNSIGNED_BYTE, lpTexture->Data());
             if(miDepth==32) glTexSubImage2D(GL_TEXTURE_2D, 0, TLLC[0], TLLC[1], lpTexture->Width(), lpTexture->Height(), GL_BGRA, GL_UNSIGNED_BYTE, lpTexture->Data());
          }*/














void cTexture::UpdateSubImage(c2DVi Offset,c2DVi Size)
{

    uint8 *lpSubImage=new uint8[Size[0]*Size[1]*miPixelSize];
    uint32 liOffsetBase=(Offset[1]*miWidth+Offset[0])*miPixelSize;
    uint32 liMyWidth=Size[0]*miPixelSize;
    uint32 miMyWidth=miWidth*miPixelSize;

        for(uint32 liCount=0;liCount<Size[1];++liCount)
        {
            memcpy(&lpSubImage[liCount*liMyWidth],&mpData[liCount*miMyWidth+liOffsetBase],sizeof(uint8)*liMyWidth);
        }

 BindTexture();
     if(miDepth==24) glTexSubImage2D(GL_TEXTURE_2D, 0, Offset[0], Offset[1], Size[0], Size[1], GL_BGR,  GL_UNSIGNED_BYTE, lpSubImage);
     if(miDepth==32) glTexSubImage2D(GL_TEXTURE_2D, 0, Offset[0], Offset[1], Size[0], Size[1], GL_BGRA, GL_UNSIGNED_BYTE, lpSubImage);

 delete []lpSubImage;
/*
  BindTexture();
  if(miDepth==24) glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, miWidth, miHeight, GL_BGR,  GL_UNSIGNED_BYTE, mpData);
  if(miDepth==32) glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, miWidth, miHeight, GL_BGRA, GL_UNSIGNED_BYTE, mpData);
*/

};

cEmptyTexture::cEmptyTexture(c2DVi liSize,uint8 liDepth,string lsFileName)
{
    miWidth=liSize[0];
    miHeight=liSize[1];
    miDepth=liDepth;
    miPixelSize=miDepth>>3;
    mpData=new uint8[miWidth*miHeight*miPixelSize];

};

void cTexture::ColorTexture(cRGBA lcColor)
{

    if(miDepth==32)
    {
        uint8 liColor[4];
        liColor[0]=lcColor[2]*255;
        liColor[1]=lcColor[1]*255;
        liColor[2]=lcColor[0]*255;
        liColor[3]=lcColor[3]*255;
        for(uint32 liCount=0;liCount<miWidth*miHeight;++liCount) {memcpy(&mpData[liCount*miPixelSize],liColor,sizeof(uint8)*4);}
        return;
    }
    if(miDepth==24)
    {
        uint8 liColor[3];
        liColor[0]=lcColor[2]*255;
        liColor[1]=lcColor[1]*255;
        liColor[2]=lcColor[0]*255;
        for(uint32 liCount=0;liCount<miWidth*miHeight;++liCount) {memcpy(&mpData[liCount*miPixelSize],liColor,sizeof(uint8)*3);}
    }

};
void cTexture::ColorTexture(cRGB lcColor)
{
    if(miDepth==32)
    {
        uint8 liColor[4];
        liColor[0]=lcColor[2]*255;
        liColor[1]=lcColor[1]*255;
        liColor[2]=lcColor[0]*255;
        liColor[3]=255;
        for(uint32 liCount=0;liCount<miWidth*miHeight;++liCount) {memcpy(&mpData[liCount*miPixelSize],liColor,sizeof(uint8)*4);}
        return;
    }
    if(miDepth==24)
    {
        uint8 liColor[3];
        liColor[0]=lcColor[2]*255;
        liColor[1]=lcColor[1]*255;
        liColor[2]=lcColor[0]*255;
        for(uint32 liCount=0;liCount<miWidth*miHeight;++liCount) {memcpy(&mpData[liCount*miPixelSize],liColor,sizeof(uint8)*3);}
    }
};

void cTexture::BlendPixels(uint8 *lpBase,uint8 *lpOverlay)
{
 if(lpOverlay[3])
 {
    float lfAlpha=lpOverlay[3]/255;
    float lfInvAlpha=1.0f-lfAlpha;

    lpBase[0]=lpOverlay[0]*lfAlpha+lfInvAlpha*lpBase[0];
    lpBase[1]=lpOverlay[1]*lfAlpha+lfInvAlpha*lpBase[1];
    lpBase[2]=lpOverlay[2]*lfAlpha+lfInvAlpha*lpBase[2];

    if(miDepth==32)
    {
        lpBase[3]=lpBase[3]*lfInvAlpha+lpOverlay[3];
    }
 }

}


cDynamicTexture::cDynamicTexture()
{
    mbFrame=false;
    mbChanged=true;
    glGenBuffers(2,mpPBOIds);
}

cDynamicTexture::cDynamicTexture(cTexture *lpOther,string NewFileName) : cTexture(lpOther,NewFileName)
{
        mbFrame=false;
        mbChanged=true;
        glGenBuffers(2,mpPBOIds);
};
cDynamicTexture::cDynamicTexture(cTextureArray *lpArray) : cTexture(lpArray)
{
        mbFrame=false;
        mbChanged=true;
    glGenBuffers(2,mpPBOIds);
};

cDynamicTexture::~cDynamicTexture()
{
    glDeleteBuffers(2,mpPBOIds);
};

void cDynamicTexture::Write(cRGBA Color,c2DVi lvXY)
{
    uint8 *lpPixel=GetPixel(lvXY);
    lpPixel[0]=Color.B()*255;
    lpPixel[1]=Color.G()*255;
    lpPixel[2]=Color.R()*255;
    if(miDepth==32) lpPixel[3]=Color.A()*255;

    mbChanged=true;
};

void cDynamicTexture::Write(cRGB Color,c2DVi lvXY)
{
    uint8 *lpPixel=GetPixel(lvXY);
    lpPixel[0]=Color.B()*255;
    lpPixel[1]=Color.G()*255;
    lpPixel[2]=Color.R()*255;

    mbChanged=true;
};

void cDynamicTexture::Write(cTexture *lpTexture,c2DVi lvXY)
{

 c2DVi TLLC(lvXY[0]-lpTexture->Width()*0.5f,lvXY[1]-lpTexture->Height()*0.5f);
 c2DVi TURC(lvXY[0]+lpTexture->Width()*0.5f,lvXY[1]+lpTexture->Height()*0.5f);

 bool lbAdjusted=false;

 c2DVi OLLC(0,0);
 if(TLLC[0]<0)
 {
     OLLC[0]=-TLLC[0]; TLLC[0]=0; lbAdjusted=true;
     }
 if(TLLC[1]<0)
 {
     OLLC[1]=-TLLC[1]; TLLC[1]=0; lbAdjusted=true;
     }

 c2DVi OURC(lpTexture->Width(),lpTexture->Height());
 if(TURC[0]>miWidth) {
     OURC[0]-=(TURC[0]-miWidth); TURC[0]=miWidth; lbAdjusted=true;
     }
 if(TURC[1]>miHeight) {
     OURC[1]-=(TURC[1]-miHeight); TURC[1]=miHeight; lbAdjusted=true;
     }

 c2DVi TLLCStore=TLLC;
 c2DVi DimensionStore=TURC-TLLC;


 c2DVi liCopySize=(TURC-TLLC)*sizeof(uint8);

 if(liCopySize[0]>0 && liCopySize[1]>0)
 {
     if(miDepth==lpTexture->Depth())
     {
         liCopySize[0]*=miPixelSize;
        for(;TLLC[1]<TURC[1];++TLLC[1])
        {
            memcpy(GetPixel(c2DVi(TLLC[0],TLLC[1])),lpTexture->GetPixel(c2DVi(OLLC[0],OLLC[1])),liCopySize[0]);
            ++OLLC[1];
        }
     }
     else
     {
         uint32 liX;
         if(miPixelSize<lpTexture->PixelSize()) liX=miPixelSize;
         else liX=lpTexture->PixelSize();
         for(;TLLC[1]<TURC[1];++TLLC[1])
         {
             for(uint32 liW=0;liW<liCopySize[0];++liW)
             {
               memcpy(GetPixel(c2DVi(TLLC[0]+liW,TLLC[1])),lpTexture->GetPixel(c2DVi(OLLC[0]+liW,OLLC[1])),liX);
             }
             ++OLLC[1];
         }

     }
     mbChanged=true;
 }
};











void cDynamicTexture::Blend(cRGBA Color,c2DVi lvXY)
{
    uint8 lpOverlay[4];
    lpOverlay[0]=(Color.B()*255);
    lpOverlay[1]=(Color.G()*255);
    lpOverlay[2]=(Color.R()*255);
    lpOverlay[3]=(Color.A()*255);
    BlendPixels(GetPixel(lvXY),lpOverlay);
    BlendPixels(GetPixel(lvXY),lpOverlay);
    mbChanged=true;
};

void cDynamicTexture::Blend(cTexture *lpTexture,c2DVi lvXY)
{
 if(lpTexture->Depth()==24) {Write(lpTexture,lvXY); return;}

 c2DVi TLLC(lvXY[0]-lpTexture->Width()*0.5f,lvXY[1]-lpTexture->Height()*0.5f);
 c2DVi TURC(lvXY[0]+lpTexture->Width()*0.5f,lvXY[1]+lpTexture->Height()*0.5f);

 bool lbAdjusted=false;

 c2DVi OLLC(0,0);
 if(TLLC[0]<0)
 {
     OLLC[0]=-TLLC[0]; TLLC[0]=0; lbAdjusted=true;
     }
 if(TLLC[1]<0)
 {
     OLLC[1]=-TLLC[1]; TLLC[1]=0; lbAdjusted=true;
     }

 c2DVi OURC(lpTexture->Width(),lpTexture->Height());
 if(TURC[0]>miWidth) {
     OURC[0]-=(TURC[0]-miWidth); TURC[0]=miWidth; lbAdjusted=true;
     }
 if(TURC[1]>miHeight) {
     OURC[1]-=(TURC[1]-miHeight); TURC[1]=miHeight; lbAdjusted=true;
     }

 c2DVi TLLCStore=TLLC;
 c2DVi DimensionStore=TURC-TLLC;


 c2DVi liCopySize=(TURC-TLLC)*sizeof(uint8);

 if(liCopySize[0]>0 && liCopySize[1]>0)
 {
    if(miDepth==32)
    {
         for(;TLLC[1]<TURC[1];++TLLC[1])
         {
             for(uint32 liW=0;liW<liCopySize[0];++liW)
             {
                 uint8 *lpOverlay=lpTexture->GetPixel(c2DVi(OLLC[0]+liW,OLLC[1]));
                if(lpOverlay[3])
                 {
                     uint8 *lpBase=GetPixel(c2DVi(TLLC[0]+liW,TLLC[1]));
                    float lfAlpha=lpOverlay[3]/255;
                    float lfInvAlpha=1.0f-lfAlpha;

                    lpBase[0]=lpOverlay[0]*lfAlpha+lfInvAlpha*lpBase[0];
                    lpBase[1]=lpOverlay[1]*lfAlpha+lfInvAlpha*lpBase[1];
                    lpBase[2]=lpOverlay[2]*lfAlpha+lfInvAlpha*lpBase[2];
                    lpBase[3]=lpBase[3]*lfInvAlpha+lpOverlay[3];
                    }
                 }

 //              BlendPixels(GetPixel(c2DVi(TLLC[0]+liW,TLLC[1])),lpTexture->GetPixel(c2DVi(OLLC[0]+liW,OLLC[1])));
            ++OLLC[1];
             }
           mbChanged=true;
           return;
         }

         if(miDepth==24)
         {
          for(;TLLC[1]<TURC[1];++TLLC[1])
          {
             for(uint32 liW=0;liW<liCopySize[0];++liW)
             {
                 uint8 *lpOverlay=lpTexture->GetPixel(c2DVi(OLLC[0]+liW,OLLC[1]));
                if(lpOverlay[3])
                 {
                     uint8 *lpBase=GetPixel(c2DVi(TLLC[0]+liW,TLLC[1]));
                    float lfAlpha=lpOverlay[3]/255;
                    float lfInvAlpha=1.0f-lfAlpha;

                    lpBase[0]=lpOverlay[0]*lfAlpha+lfInvAlpha*lpBase[0];
                    lpBase[1]=lpOverlay[1]*lfAlpha+lfInvAlpha*lpBase[1];
                    lpBase[2]=lpOverlay[2]*lfAlpha+lfInvAlpha*lpBase[2];
                    }
                 }

 //              BlendPixels(GetPixel(c2DVi(TLLC[0]+liW,TLLC[1])),lpTexture->GetPixel(c2DVi(OLLC[0]+liW,OLLC[1])));
            ++OLLC[1];
             }
             mbChanged=true;
             return;
         }



     }

 };











bool cDynamicTexture::UpdateTexture()
{
    return mbNeedsUpdate;
}

bool cDynamicTexture::UpdatePBO()
{
    return mbChanged;
}

void cDynamicTexture::StepFrame()
{
    if(mbChanged) {mbNeedsUpdate=true; mbChanged=false; mbFrame=!mbFrame;}
    else
    {
        mbNeedsUpdate=false;
    }
}

void cDynamicTexture::FrameUpdate()
{
 if(UpdateTexture())
 {
    glBindTexture(GL_TEXTURE_2D, miTexture);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, mpPBOIds[!mbFrame]);


    // copy pixels from PBO to texture object
    // Use offset instead of ponter.
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, miWidth,miHeight,GL_BGRA, GL_UNSIGNED_BYTE, 0);
 }

 if(UpdatePBO())
 {
    // bind PBO to update texture source
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mpPBOIds[mbFrame]);

    // Note that glMapBufferARB() causes sync issue.
    // If GPU is working with this buffer, glMapBufferARB() will wait(stall)
    // until GPU to finish its job. To avoid waiting (idle), you can call
    // first glBufferDataARB() with NULL pointer before glMapBufferARB().
    // If you do that, the previous data in PBO will be discarded and
    // glMapBufferARB() returns a new allocated pointer immediately
    // even if GPU is still working with the previous data.
    glBufferData(GL_PIXEL_UNPACK_BUFFER, miWidth*miHeight*miPixelSize, 0, GL_STREAM_DRAW);

    // map the buffer object into client's memory
    GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER,GL_WRITE_ONLY);
    if(ptr)
    {
        memcpy(ptr,mpData,sizeof(uint8)*miPixelSize*miWidth*miHeight);
        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER); // release the mapped buffer
    }
 }

 StepFrame();

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}


void cDynamicTexture::ColorTexture(cRGBA lcColor)
{
   cTexture::ColorTexture(lcColor);
   mbChanged=true;
}
void cDynamicTexture::ColorTexture(cRGB lcColor)
{
   cTexture::ColorTexture(lcColor);
   mbChanged=true;
}

cGUIFrameTexture::cGUIFrameTexture(c2DVi lvSize,cTexture *lpCorner,cTexture *lpEdge,cTexture *lpCentre,cRGBA lpBaseColor,uint8 liDepth) : cGUIFrameBase(lpBaseColor)
{
    miWidth=lvSize[0];
    miHeight=lvSize[1];
    miDepth=liDepth;
    miPixelSize=miDepth>>3;

    mpData=new uint8[miWidth*miHeight*miPixelSize];
    memset(mpData,0,miWidth*miHeight*miPixelSize);

    WriteBaseColor(lpBaseColor);
    WriteEdge(lpEdge);
    WriteCorners(lpCorner);
    WriteCentres(lpCentre);
    SortBackColor(lpBaseColor);
BufferTexture();


};

cGUIFrameHorizontalTitleTexture::cGUIFrameHorizontalTitleTexture(c2DVi lvSize,cTexture *lpCorner,cTexture *lpEdge,cTexture *lpBreak,uint32 liBreakHeight,cTexture *lpBreakEdge,cTexture *lpCentre,cRGBA lpBaseColor,uint8 liDepth) : cGUIFrameBase(lpBaseColor)
{
    miBreakY=liBreakHeight;
    miWidth=lvSize[0];
    miHeight=lvSize[1];
    miDepth=liDepth;
    miPixelSize=miDepth>>3;
    mpData=new uint8[miWidth*miHeight*miPixelSize];
    memset(mpData,0,miWidth*miHeight*miPixelSize);

    WriteBaseColor(lpBaseColor);
    WriteEdge(lpEdge);
    WriteCorners(lpCorner);

if(lpBreakEdge)
{
    uint16 liY=miHeight-lpBreakEdge->Height()*0.5f-liBreakHeight;
    for(uint16 liCount=0;liCount<miWidth;liCount+=lpBreakEdge->Width())
    {
        CopyImage(c2DVi(liCount,liY),lpBreakEdge);
    }
}

if(lpBreak)
{
    lpBreak->Rotate90CW();
    CopyImage(c2DVi(0,miHeight-lpBreak->Height()*0.5f-liBreakHeight),lpBreak);
    lpBreak->FlipHorizontally();
    CopyImage(c2DVi(miWidth-lpBreak->Width(),miHeight-lpBreak->Height()*0.5f-liBreakHeight),lpBreak);
    lpBreak->FlipHorizontally();
    lpBreak->Rotate90CCW();
}

if(lpCentre)
{
    CopyImage(c2DVi(miWidth/2,0),lpCentre);
    lpCentre->Rotate90CW();
    CopyImage(c2DVi(0,miHeight-liBreakHeight*0.5f),lpCentre);
    CopyImage(c2DVi(0,(miHeight-liBreakHeight)*0.5f),lpCentre);
    lpCentre->Rotate90CW();
    CopyImage(c2DVi(miWidth/2,miHeight-lpCentre->Height()),lpCentre);
    lpCentre->Rotate90CW();
    CopyImage(c2DVi(miWidth-lpCentre->Width(),miHeight-liBreakHeight*0.5f),lpCentre);
    CopyImage(c2DVi(miWidth-lpCentre->Width(),(miHeight-liBreakHeight)*0.5f),lpCentre);
    lpCentre->Rotate90CW();
}

SortBackColor(lpBaseColor);

BufferTexture();

};

uint32 cGUIFrameHorizontalTitleTexture::Break(){return miBreakY;}

void cGUIFrameHandler::BaseColor(cRGBA lcCol)
{
    mpBaseColor=lcCol;
};

void cGUIFrameHandler::ClearBaseColor()
{
    mpBaseColor=cRGBA(0.0f,0.0f,0.0f,0.0f);
};


void cGUIFrameBase::WriteBaseColor(cRGBA lpBaseColor)
{
if(lpBaseColor.A()>0.0f)
{
    uint8 lcColor[4];
    lcColor[0]=lpBaseColor.R()*255;
    lcColor[1]=lpBaseColor.G()*255;
    lcColor[2]=lpBaseColor.B()*255;
    lcColor[3]=lpBaseColor.A()*255;

    uint8 *lpBase=mpData;
    for(uint32 liPos=0;liPos<miWidth*miHeight;++liPos)
    {
        memcpy(lpBase,lcColor,miPixelSize);
        lpBase+=miPixelSize;
    }
}
else memset(mpData,0,miWidth*miHeight*miPixelSize);
}

void cGUIFrameBase::WriteEdge(cTexture *lpEdge)
{
if(lpEdge)
{
        for(uint16 liX=0;liX<miWidth;liX+=lpEdge->Width()){CopyImage(c2DVi(liX,0),lpEdge);}
        lpEdge->Rotate90CW();
        for(uint16 liX=0;liX<miHeight;liX+=lpEdge->Height()){CopyImage(c2DVi(0,liX),lpEdge);}
        lpEdge->Rotate90CW();
        for(uint16 liX=0;liX<miWidth;liX+=lpEdge->Width()){CopyImage(c2DVi(liX,miHeight-lpEdge->Height()),lpEdge);}
        lpEdge->Rotate90CW();
        for(uint16 liX=0;liX<miHeight;liX+=lpEdge->Height()){CopyImage(c2DVi(miWidth-lpEdge->Width(),liX),lpEdge);}
        lpEdge->Rotate90CW();
}
}
void cGUIFrameBase::WriteCorners(cTexture *lpCorner)
{
if(lpCorner)
{
    CopyImage(c2DVi(0,0),lpCorner);
    lpCorner->FlipVertically();
    CopyImage(c2DVi(0,miHeight-lpCorner->Height()),lpCorner);
    lpCorner->FlipHorizontally();
    CopyImage(c2DVi(miWidth-lpCorner->Width(),miHeight-lpCorner->Height()),lpCorner);
    lpCorner->FlipVertically();
    CopyImage(c2DVi(miWidth-lpCorner->Width(),0),lpCorner);
    lpCorner->FlipHorizontally();
}
}

void cGUIFrameBase::WriteCentres(cTexture *lpCentre)
{
if(lpCentre)
{
    CopyImage(c2DVi(miWidth/2,0),lpCentre);
    lpCentre->Rotate90CW();
    CopyImage(c2DVi(0,miHeight/2),lpCentre);
    lpCentre->Rotate90CW();
    CopyImage(c2DVi(miWidth/2,miHeight-lpCentre->Height()),lpCentre);
    lpCentre->Rotate90CW();
    CopyImage(c2DVi(miWidth-lpCentre->Width(),miHeight/2),lpCentre);
    lpCentre->Rotate90CW();
}
}

cGUIFrameVerticalTitleTexture::cGUIFrameVerticalTitleTexture(c2DVi lvSize,cTexture *lpCorner,cTexture *lpEdge,cTexture *lpBreak,uint32 liBreakHeight,cTexture *lpBreakEdge,cTexture *lpCentre,cRGBA lpBaseColor,uint8 liDepth)  : cGUIFrameBase(lpBaseColor)
{
    miBreakX=liBreakHeight;
    miWidth=lvSize[0];
    miHeight=lvSize[1];
    miDepth=liDepth;
    miPixelSize=miDepth>>3;
    mpData=new uint8[miWidth*miHeight*miPixelSize];

    WriteBaseColor(lpBaseColor);
    WriteEdge(lpEdge);
    WriteCorners(lpCorner);


if(lpBreakEdge)
{
    lpBreakEdge->Rotate90CW();
    for(uint16 liCount=0;liCount<miHeight;liCount+=lpBreakEdge->Height())
    {
        CopyImage(c2DVi(liBreakHeight,liCount),lpBreakEdge);
    }
    lpBreakEdge->Rotate90CCW();
}

if(lpBreak)
{
    CopyImage(c2DVi(liBreakHeight,0),lpBreak);
    lpBreak->FlipVertically();
    CopyImage(c2DVi(liBreakHeight,miHeight-lpBreak->Height()),lpBreak);
    lpBreak->FlipVertically();
}

if(lpCentre)
{

    CopyImage(c2DVi(liBreakHeight*0.5,0),lpCentre);
    CopyImage(c2DVi((miWidth-liBreakHeight)*0.5f+liBreakHeight,0),lpCentre);
    lpCentre->Rotate90CW();

    CopyImage(c2DVi(0,miHeight/2),lpCentre);
    lpCentre->Rotate90CW();

    CopyImage(c2DVi((miWidth-liBreakHeight)*0.5f+liBreakHeight,miHeight-lpCentre->Height()),lpCentre);
    CopyImage(c2DVi(liBreakHeight*0.5,miHeight-lpCentre->Height()),lpCentre);
    lpCentre->Rotate90CW();

    CopyImage(c2DVi(miWidth-lpCentre->Width(),miHeight/2),lpCentre);
    lpCentre->Rotate90CW();

}

SortBackColor(lpBaseColor);

BufferTexture();

};

uint32 cGUIFrameVerticalTitleTexture::Break(){return miBreakX;}

void cTexture::CopyImage(c2DVi lvPos,cTexture *lpTexture)
{
    uint8 liMoveSize;
    if(miDepth==lpTexture->miDepth) {CopyImageClean(lvPos,lpTexture); return;}
    if(miDepth>lpTexture->miDepth) {CopyImageUnbalanced(lvPos,lpTexture); return;}

    //Runs when this is RGB and lpTexture is RGBA
    liMoveSize=3;

    c2DVi liBasePos;
    c2DVi liTop;
    c2DVi liTex;
    if(miWidth<lvPos[0]+lpTexture->Width()) liTop[0]=miWidth;
    else liTop[0]=lvPos[0]+lpTexture->Width();
    if(miHeight<lvPos[1]+lpTexture->Height()) liTop[1]=miHeight;
    else liTop[1]=lvPos[1]+lpTexture->Height();


    for(liBasePos[0]=lvPos[0];liBasePos[0]<liTop[0];++liBasePos[0])
    {
        for(liBasePos[1]=lvPos[1];liBasePos[1]<liTop[1];++liBasePos[1])
        {
            float lfScale=(float)lpTexture->GetPixel(liTex)[3]/255.0f;
            mpData[(liBasePos[0]+liBasePos[1]*miWidth)*miPixelSize]=lpTexture->GetPixel(liTex)[0]*lfScale;
            mpData[(liBasePos[0]+liBasePos[1]*miWidth)*miPixelSize+1]=lpTexture->GetPixel(liTex)[1]*lfScale;
            mpData[(liBasePos[0]+liBasePos[1]*miWidth)*miPixelSize+2]=lpTexture->GetPixel(liTex)[2]*lfScale;
            ++liTex[1];
        }
        liTex[1]=0;
        ++liTex[0];
    }
}

void cTexture::CopyImageUnbalanced(c2DVi lvPos,cTexture *lpTexture)
{
    uint8 liMoveSize;
    liMoveSize=3;

    c2DVi liBasePos;
    c2DVi liTop;
    c2DVi liTex;
    if(miWidth<lvPos[0]+lpTexture->Width()) liTop[0]=miWidth;
    else liTop[0]=lvPos[0]+lpTexture->Width();
    if(miHeight<lvPos[1]+lpTexture->Height()) liTop[1]=miHeight;
    else liTop[1]=lvPos[1]+lpTexture->Height();


    for(liBasePos[0]=lvPos[0];liBasePos[0]<liTop[0];++liBasePos[0])
    {
        for(liBasePos[1]=lvPos[1];liBasePos[1]<liTop[1];++liBasePos[1])
        {
            memcpy(&mpData[(liBasePos[0]+liBasePos[1]*miWidth)*miPixelSize],lpTexture->GetPixel(liTex),liMoveSize);
            mpData[(liBasePos[0]+liBasePos[1]*miWidth)*miPixelSize+3]=255;
            ++liTex[1];
        }
        liTex[1]=0;
        ++liTex[0];
    }
}


void cTexture::CopyImageClean(c2DVi lvPos,cTexture *lpTexture)
{
    c2DVi liBasePos;
    c2DVi liTop;
    c2DVi liTex;
    if(miWidth<lvPos[0]+lpTexture->Width()) liTop[0]=miWidth;
    else liTop[0]=lvPos[0]+lpTexture->Width();
    if(miHeight<lvPos[1]+lpTexture->Height()) liTop[1]=miHeight;
    else liTop[1]=lvPos[1]+lpTexture->Height();


    for(liBasePos[0]=lvPos[0];liBasePos[0]<liTop[0];++liBasePos[0])
    {
        for(liBasePos[1]=lvPos[1];liBasePos[1]<liTop[1];++liBasePos[1])
        {
            memcpy(&mpData[(liBasePos[0]+liBasePos[1]*miWidth)*miPixelSize],lpTexture->GetPixel(liTex),miPixelSize);
            ++liTex[1];
        }
        liTex[1]=0;
        ++liTex[0];
    }
}



void cTexture::FlipHorizontally()
{
    uint8 *lpTemp = new uint8[miPixelSize];
    for(uint16 liX=0;liX<miWidth>>1;++liX)
    {
        for(uint16 liY=0;liY<miHeight;++liY)
        {
            memcpy(lpTemp,&mpData[(liY*miWidth+liX)*miPixelSize],miPixelSize);
            memcpy(&mpData[(liY*miWidth+liX)*miPixelSize],&mpData[(liY*miWidth+(miWidth-liX-1))*miPixelSize],miPixelSize);
            memcpy(&mpData[(liY*miWidth+(miWidth-liX-1))*miPixelSize],lpTemp,miPixelSize);
        }
    }
	delete []lpTemp;
};
void cTexture::FlipVertically()
{
    uint8 *lpTemp = new uint8[miPixelSize*miWidth];
    for(uint16 liY=0;liY<miHeight>>1;++liY)
    {
        memcpy(lpTemp,&mpData[(liY*miWidth)*miPixelSize],miPixelSize*miWidth);
        memcpy(&mpData[liY*miWidth*miPixelSize],&mpData[(miHeight-liY-1)*miWidth*miPixelSize],miPixelSize*miWidth);
        memcpy(&mpData[(miHeight-liY-1)*miWidth*miPixelSize],lpTemp,miPixelSize*miWidth);
    }
	delete []lpTemp;
};
void cTexture::Rotate90CCWClean()
{
    uint8 *lpTemp = new uint8[miPixelSize];

    for(uint16 liX=0;liX<(miWidth+1)>>1;++liX)
    {
        for(uint16 liY=0;liY<(miHeight+1)>>1;++liY)
        {
            memcpy(lpTemp,&mpData[(liX+liY*miWidth)*miPixelSize],miPixelSize);
            memcpy(&mpData[(liX+liY*miWidth)*miPixelSize],&mpData[((miWidth-liX-1)+liY*miWidth)*miPixelSize],miPixelSize);
            memcpy(&mpData[((miWidth-liX-1)+liY*miWidth)*miPixelSize],&mpData[((miWidth-liX-1)+(miHeight-liY-1)*miWidth)*miPixelSize],miPixelSize);
            memcpy(&mpData[((miWidth-liX-1)+(miHeight-liY-1)*miWidth)*miPixelSize],&mpData[(liX+(miHeight-liY-1)*miWidth)*miPixelSize],miPixelSize);
            memcpy(&mpData[(liX+(miHeight-liY-1)*miWidth)*miPixelSize],lpTemp,miPixelSize);
        }
    }

    uint16 liTemp=miWidth;
    miWidth=miHeight;
    miHeight=liTemp;
	delete []lpTemp;
};
void cTexture::Rotate90CWClean()
{
    uint8 *lpTemp = new uint8[miPixelSize];

    for(uint16 liX=0;liX<(miWidth+1)>>1;++liX)
    {
        for(uint16 liY=0;liY<(miHeight+1)>>1;++liY)
        {
            memcpy(lpTemp,&mpData[(liX+liY*miWidth)*miPixelSize],miPixelSize);
            memcpy(&mpData[(liX+liY*miWidth)*miPixelSize],&mpData[(liX+(miHeight-liY-1)*miWidth)*miPixelSize],miPixelSize);
            memcpy(&mpData[(liX+(miHeight-liY-1)*miWidth)*miPixelSize],&mpData[((miWidth-liX-1)+(miHeight-liY-1)*miWidth)*miPixelSize],miPixelSize);
            memcpy(&mpData[((miWidth-liX-1)+(miHeight-liY-1)*miWidth)*miPixelSize],&mpData[((miWidth-liX-1)+liY*miWidth)*miPixelSize],miPixelSize);
            memcpy(&mpData[((miWidth-liX-1)+liY*miWidth)*miPixelSize],lpTemp,miPixelSize);
        }
    }

    uint16 liTemp=miWidth;
    miWidth=miHeight;
    miHeight=liTemp;
	delete []lpTemp;
};


void cTexture::Rotate90CCW()
{
    if(miWidth==miHeight){Rotate90CCWClean(); return;}

    uint8 *lpTemp=new uint8[miWidth*miHeight*miPixelSize];

    for(uint16 liX=0;liX<miWidth;++liX)
    {
        for(uint16 liY=0;liY<miHeight;++liY)
        {
            memcpy(&lpTemp[(liX*miHeight+(miHeight-liY-1))*miPixelSize],&mpData[(liX+liY*miWidth)*miPixelSize],miPixelSize);
        }
    }

    delete []mpData;
    mpData=lpTemp;

    uint16 liTemp=miWidth;
    miWidth=miHeight;
    miHeight=liTemp;
};


void cTexture::Rotate90CW()
{
    if(miWidth==miHeight){ Rotate90CWClean(); return;}

    uint8 *lpTemp=new uint8[miWidth*miHeight*miPixelSize];

    for(uint16 liX=0;liX<miWidth;++liX)
    {
        for(uint16 liY=0;liY<miHeight;++liY)
        {
            memcpy(&lpTemp[((miWidth-liX-1)*miHeight+liY)*miPixelSize],&mpData[(liX+liY*miWidth)*miPixelSize],miPixelSize);
        }
    }

    delete []mpData;
    mpData=lpTemp;


    uint16 liTemp=miWidth;
    miWidth=miHeight;
    miHeight=liTemp;
};

    cGUIFrameHandler *cGUIFrameHandler::mpInstance=0;

cGUIFrameHandler::cGUIFrameHandler()
{
    mpCorner=0;
    mpEdge=0;
    mpCentre=0;
    mpBreak=0;
    mpBreakEdge=0;
    miDepth=32;
    mpBaseColor=cRGBA(0.0f,0.0f,0.0f,0.0f);
};

cGUIFrameBase::cGUIFrameBase(cRGBA lpCol)
{
    mcCol=lpCol;
};


bool cGUIFrameBase::BaseColor(cRGBA lpCol)
{
    return mcCol==lpCol;
};

cGUIFrameTexture *cGUIFrameHandler::GetTexture(c2DVi lvSize)
{
    for(uint32 liCount=0;liCount<mpFrames.Items();++liCount)
    {
        if(mpFrames[liCount]->Width()==lvSize[0] && mpFrames[liCount]->Height()==lvSize[1] && mpFrames[liCount]->BaseColor(mpBaseColor))
        {
            return mpFrames[liCount];
        }
    }

    mpFrames.Add(new cGUIFrameTexture(lvSize,mpCorner,mpEdge,mpCentre,mpBaseColor,miDepth));
    return mpFrames[mpFrames.Items()-1];
};
cGUIFrameHandler *cGUIFrameHandler::Instance()
{
    if(!mpInstance) mpInstance=new cGUIFrameHandler();
    return mpInstance;
};
void cGUIFrameHandler::Clear()
{
    mpFrames.Init(2);
    mpHorizontal.Init(2);
    mpVertical.Init(2);
};

void cGUIFrameHandler::SetTextures(cTexture *lpCorner,cTexture *lpEdge,cTexture *lpCentre,cTexture *lpBreak,cTexture *lpBreakEdge,cRGBA lpBase,uint8 liDepth)
{
    mpCorner=lpCorner;
    mpEdge=lpEdge;
    mpCentre=lpCentre;
    mpBreak=lpBreak;
    mpBreakEdge=lpBreakEdge;
    mpBaseColor=lpBase;
    miDepth=liDepth;
};

cGUIFrameHorizontalTitleTexture *cGUIFrameHandler::GetTextureHBreak(c2DVi lvSize,uint32 liPos)
{
    for(uint32 liCount=0;liCount<mpHorizontal.Items();++liCount)
    {
        if(mpHorizontal[liCount]->Width()==lvSize[0] && mpHorizontal[liCount]->Height()==lvSize[1] && mpHorizontal[liCount]->Break()==liPos && mpHorizontal[liCount]->BaseColor(mpBaseColor))
        {
            return mpHorizontal[liCount];
        }
    }

    mpHorizontal.Add(new cGUIFrameHorizontalTitleTexture(lvSize,mpCorner,mpEdge,mpBreak,liPos,mpBreakEdge,mpCentre,mpBaseColor,miDepth));
    return mpHorizontal[mpHorizontal.Items()-1];
};

cGUIFrameVerticalTitleTexture *cGUIFrameHandler::GetTextureVBreak(c2DVi lvSize,uint32 liPos)
{
    for(uint32 liCount=0;liCount<mpVertical.Items();++liCount)
    {
        if(mpVertical[liCount]->Width()==lvSize[0] && mpVertical[liCount]->Height()==lvSize[1] && mpVertical[liCount]->Break()==liPos && mpVertical[liCount]->BaseColor(mpBaseColor))
        {
            return mpVertical[liCount];
        }
    }

    mpVertical.Add(new cGUIFrameVerticalTitleTexture(lvSize,mpCorner,mpEdge,mpBreak,liPos,mpBreakEdge,mpCentre,mpBaseColor,miDepth));
    return mpVertical[mpVertical.Items()-1];
};

void cGUIFrameBase::SortBackColor(cRGBA lpCol)
{
    uint8 liCol[4]={lpCol[0]*255,lpCol[1]*255,lpCol[2]*255,lpCol[3]*255};
    for(uint32 liCount=0;liCount<miWidth*miHeight;++liCount)
    {
        if(mpData[liCount*miPixelSize]!=mpData[liCount*miPixelSize+2])
        {
            memcpy(&mpData[liCount*miPixelSize],liCol,miPixelSize);
        }
    }
};

cGUIFrameTexture *cGUIFrameHandler::GetTexture(uint32 liPos)
{
    return mpFrames[liPos];
};
cGUIFrameHorizontalTitleTexture *cGUIFrameHandler::GetTextureHBreak(uint32 liPos)
{
    return mpHorizontal[liPos];
};
cGUIFrameVerticalTitleTexture *cGUIFrameHandler::GetTextureVBreak(uint32 liPos)
{
    return mpVertical[liPos];
};
