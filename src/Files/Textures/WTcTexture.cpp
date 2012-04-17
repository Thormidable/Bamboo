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
 UpdateTexture();
}

void cTexture::UpdateTexture()
{
BindTexture();

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

if(WT_ALLOW_DYNAMIC_TEXTURES) glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
else {glEnable(GL_TEXTURE_2D); glGenerateMipmapEXT(GL_TEXTURE_2D);}


if(miDepth==24) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width(),Height(), 0, GL_BGR, GL_UNSIGNED_BYTE,mpData);
if(miDepth==32) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width(),Height(), 0, GL_BGRA, GL_UNSIGNED_BYTE,mpData);
}

void cTexture::BindTexture()
{
 glBindTexture(GL_TEXTURE_2D,miTexture);

}

cTexture::cTexture(){};

uint8 *cTexture::Data()
{return mpData;}

 cTexture::~cTexture(){if(mpData){delete []mpData;mpData=0;}}
    uint32 cTexture::Width(){return miWidth;}
       uint32 cTexture::Height(){return miHeight;}
       uint8 cTexture::Depth(){return miDepth;}
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
 glGenTextures(1, &(lpNew->miTexture));
 lpNew->UpdateTexture();
 return lpNew;
 };

 cTexture::cTexture(cTexture *lpOther)
 {
    miWidth=lpOther->miWidth;
    miHeight=lpOther->miHeight;
    miDepth=lpOther->miDepth;
    miPixelSize=lpOther->miPixelSize;
    glGenTextures(1, &miTexture);
    strcpy(mpFileName,"GeneratedTexture");
    mpData=new uint8[miWidth*miHeight*miPixelSize];
    memcpy(mpData,lpOther->mpData,sizeof(uint8)*miWidth*miHeight*miPixelSize);
    UpdateTexture();
 }

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

    UpdateTexture();
 }

void cTexture::Write(cRGBA Color,c2DVf lvUV)
{
    Write(Color,c2DVi(lvUV[0]*miWidth,lvUV[1]*miHeight));
};
void cTexture::Write(cRGBA Color,c2DVi lvXY)
{
    uint8 *lpPixel=GetPixel(lvXY);
    lpPixel[0]=Color.B()*255;
    lpPixel[1]=Color.G()*255;
    lpPixel[2]=Color.R()*255;
    if(miDepth==32) lpPixel[3]=Color.A()*255;
    BindTexture();
    if(miDepth==32) glTexSubImage2D(miTexture, 0, lvXY[0], lvXY[1], 1, 1, GL_BGRA, GL_UNSIGNED_BYTE,lpPixel);
    if(miDepth==24) glTexSubImage2D(miTexture, 0, lvXY[0], lvXY[1], 1, 1, GL_BGR, GL_UNSIGNED_BYTE,lpPixel);
    glBindTexture(GL_TEXTURE_2D,0);
    BindTexture();
};

void cTexture::Write(cRGB Color,c2DVf lvUV)
{
    Write(Color,c2DVi(lvUV[0]*miWidth,lvUV[1]*miHeight));
};
void cTexture::Write(cRGB Color,c2DVi lvXY)
{
    uint8 *lpPixel=GetPixel(lvXY);
    lpPixel[0]=Color.B()*255;
    lpPixel[1]=Color.G()*255;
    lpPixel[2]=Color.R()*255;
    glEnable(GL_TEXTURE_2D);
    BindTexture();
    if(miDepth==24) glTexSubImage2D(GL_TEXTURE_2D, 0, lvXY[0], lvXY[1], 1, 1, GL_BGR, GL_UNSIGNED_BYTE,lpPixel);
    if(miDepth==32) glTexSubImage2D(GL_TEXTURE_2D, 0, lvXY[0], lvXY[1], 1, 1, GL_BGRA, GL_UNSIGNED_BYTE,lpPixel);
    glBindTexture(GL_TEXTURE_2D,0);
    BindTexture();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
};

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

void cTexture::Write(cTexture *lpTexture,c2DVf lvUV)
{
 Write(lpTexture,c2DVi(lvUV[0]*miWidth,lvUV[1]*miHeight));
};

void cTexture::Write(cTexture *lpTexture,c2DVi lvXY)
{

 c2DVi TLLC(lvXY[0]-lpTexture->Width()*0.5f,lvXY[1]-lpTexture->Height()*0.5f);
 c2DVi TURC(lvXY[0]+lpTexture->Width()*0.5f,lvXY[1]+lpTexture->Height()*0.5f);

 bool lbAdjusted=false;

 c2DVi OLLC;
 if(TLLC[0]<0) {OLLC[0]=-TLLC[0]; TLLC[0]=0; lbAdjusted=true;}
 if(TLLC[1]<0) {OLLC[1]=-TLLC[1]; TLLC[1]=0; lbAdjusted=true;}

 c2DVi OURC;
 if(TURC[0]>miWidth) {OURC[0]=-TURC[0]; TURC[0]=miWidth; lbAdjusted=true;}
 if(TURC[1]>miHeight) {OURC[1]=-TURC[1]; TURC[1]=miHeight; lbAdjusted=true;}

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
          if(lbAdjusted==true) WriteSubImage(TLLC,DimensionStore);
          else
          {
            BindTexture();
             if(miDepth==24) glTexSubImage2D(miTexture, 0, TLLC[0], TLLC[1], lpTexture->Width(), lpTexture->Height(), GL_BGR,  GL_UNSIGNED_BYTE, lpTexture->Data());
             if(miDepth==32) glTexSubImage2D(miTexture, 0, TLLC[0], TLLC[1], lpTexture->Width(), lpTexture->Height(), GL_BGRA, GL_UNSIGNED_BYTE, lpTexture->Data());
            glBindTexture(GL_TEXTURE_2D,0);
            BindTexture();
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
        WriteSubImage(TLLC,DimensionStore);
     }
 }


};

void cTexture::WriteSubImage(c2DVi Offset,c2DVi Size)
{
    float *lpSubImage=new float[Size[0]*Size[1]*miPixelSize];
    uint32 liOffsetBase=(Offset[1]*miWidth+Offset[0])*miPixelSize;
    uint32 liMyWidth=Size[0]*miPixelSize;
    uint32 miMyWidth=miWidth*miPixelSize;

        for(uint32 liCount=0;liCount<Size[1];++liCount)
        {
            memcpy(&lpSubImage[liCount*liMyWidth],&mpData[liCount*miMyWidth+liOffsetBase],sizeof(uint8)*liMyWidth);
        }

 BindTexture();
     if(miDepth==24) glTexSubImage2D(miTexture, 0, Offset[0], Offset[1], Size[0], Size[1], GL_BGR,  GL_UNSIGNED_BYTE, lpSubImage);
     if(miDepth==32) glTexSubImage2D(miTexture, 0, Offset[0], Offset[1], Size[0], Size[1], GL_BGRA, GL_UNSIGNED_BYTE, lpSubImage);
 glBindTexture(GL_TEXTURE_2D,0);
 BindTexture();

 delete []lpSubImage;
};

