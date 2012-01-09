#include "../../WTBamboo.h"
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

void cImage::Width(float lfWidth)
{
    mfWidth=lfWidth;
}
void cImage::Height(float lfHeight)
{
    mfHeight=lfHeight;
}
void cImage::Size(float lfSize)
{
  mfWidth=lfSize;
  mfHeight=mfWidth*gpWindow->Ratio();
}


void cImage::RenderPainter(uint8 liLevel)
{
(void) liLevel;

 if(mpPixmap)
 {
     ResizeArrays();
     SetShaderVariables();
    float lfWidth=mfWidth*0.5f;
    float lfHeight=mfHeight*0.5f;
   glBegin(GL_QUADS);

    glNormal3f(0.0f,0.0f,1.0f);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-lfWidth,-lfHeight,2.1f);


    glTexCoord2f(1.0f,0.0f);
    glVertex3f(lfWidth,-lfHeight,2.1f);

    glTexCoord2f(1.0f,1.0f);
    glVertex3f(lfWidth,lfHeight,2.1f);

    glTexCoord2f(0.0f,1.0f);
    glVertex3f(-lfWidth,lfHeight,2.1f);

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


void cImage3D::SetUp()
{
 Set3D();
 InitialiseArrays();
 Transparency(true);
}



	float cImage::Width()
	{
	  return mfWidth;
	}


	float cImage::Height()
	{
	    return mfHeight;
	}
