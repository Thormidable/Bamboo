#include "../../WTDivWin.h"
#include <cmath>

bool cImage::mbFirst=1;
float cImage::mpVertex[12];
uint16 cImage::mpFaces[6];
float cImage::mpTextCoords[8];
float cImage::mpNormals[12];


cImage::~cImage(){}

cImage::cImage(cTexture *lpTexture)
{
 mpPixmap=lpTexture;
 SetUp();
}


cImage::cImage()
{
 mpPixmap=0;
 SetUp();
}

void cImage::SetUp()
{
 Set2D();
 InitialiseArrays();
 Transparency(true);
}


void cImage::RenderToPainter()
{
if(mpPixmap)
{

 UpdateMatrix();

 mpPainterData->SetObject(this);
 mpPainterData->SetTexture(TextureNumber());
 SetOtherRenderVariables();

mpPainterData->RenderAgain();

}
}

void cImage::Position(float lfX,float lfY)
{
    mpData[12]=(lfX*gpWindow->InvWidth()*_CAMERA->Width()*4);
    mpData[13]=(lfY*gpWindow->InvHeight()*_CAMERA->Height()*4);

}

void cImage::Width(float lfWidth)
{
    mfWidth=lfWidth*gpWindow->InvWidth()*_CAMERA->Width()*2;
}
void cImage::Height(float lfHeight)
{
    mfHeight=lfHeight*gpWindow->InvHeight()*_CAMERA->Height()*2;
}

void cImage::RenderPainter(uint8 liLevel)
{
(void) liLevel;

 if(mpPixmap)
 {
     ResizeArrays();
     SetShaderVariables();

   glBegin(GL_QUADS);

    glNormal3f(0.0f,0.0f,1.0f);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-mfWidth,-mfHeight,2.1f);


    glTexCoord2f(1.0f,0.0f);
    glVertex3f(mfWidth,-mfHeight,2.1f);

    glTexCoord2f(1.0f,1.0f);
    glVertex3f(mfWidth,mfHeight,2.1f);

    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-mfWidth,mfHeight,2.1f);

   glEnd();

 }

}

void cImage::Texture(cTexture *lpGraph)
{
 mpPixmap=lpGraph;
}


void cImage::InitialiseArrays()
{

 mfWidth=0.01f;
 mfHeight=0.01f;

 if(mbFirst)
 {
  //order is BR TR TL BL
  mbFirst=0;
  mpVertex[7]=mpVertex[4]=mpVertex[3]=mpVertex[0]=mfWidth;
  mpVertex[1]=mpVertex[5]=mpVertex[8]=mpVertex[9]=mpVertex[11]=0.0f;
  mpFaces[3]=mpFaces[0]=0;
  mpFaces[1]=1;
  mpFaces[4]=mpFaces[2]=2;
  mpFaces[5]=3;

  mpNormals[9]=mpNormals[10]=mpNormals[6]=mpNormals[7]=mpNormals[3]=mpNormals[4]=mpNormals[0]=mpNormals[1]=0.0f;
  mpNormals[11]=mpNormals[8]=mpNormals[5]=mpNormals[2]=1.0f;

  mpTextCoords[5]=mpTextCoords[3]=mpTextCoords[2]=mpTextCoords[0]=1.0f;
  mpTextCoords[6]=mpTextCoords[1]=mpTextCoords[4]=mpTextCoords[7]=0.0f;
 }
}

void cImage::ResizeArrays()
{
 mpVertex[7]=mpVertex[4]=mpVertex[3]=mpVertex[0]=mfWidth;

}

unsigned int cImage::TextureNumber()
{
  if(mpPixmap) return mpPixmap->TextureNumber(); return 0;
}

void cImage::Size(float lfSize)
{
  mfWidth=lfSize*gpWindow->InvWidth()*_CAMERA->Width()*2;
  mfHeight=mfWidth*gpWindow->Ratio();
}

void cImage3D::SetUp()
{
 Set3D();
 InitialiseArrays();
 Transparency(true);
}

void cImage3D::Size(float lfSize)
{
    mfHeight=mfWidth=lfSize;
}

void cImage3D::Width(float lfWidth)
{
    mfWidth=lfWidth;
}

void cImage3D::Height(float lfHeight)
{
    mfHeight=lfHeight;
}

void cImage3D::Position(float lfX,float lfY)
{
    cMatrix4::Position(lfX,lfY);
}
