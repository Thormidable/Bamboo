#include "../../WTDivWin.h"
#include <cmath>

bool cImage::mbFirst=1;
float cImage::mpVertex[12];
uint16 cImage::mpFaces[6];
float cImage::mpTextCoords[8];
float cImage::mpNormals[12];


cImage::~cImage(){}

cImage::cImage(vTexture *lpTexture)
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
}


void cImage::RenderToPainter()
{
if(mpPixmap)
{

 UpdateMatrix();

 mpPainterData->SetObject(this);
 mpPainterData->SetTexture(TextureNumber());
 mpPainterData->SetShader(mpShader);

mpPainterData->RenderAgain();

}
}

void cImage::Position(float lfX,float lfY)
{
    mpData[12]=(lfX*gpWindow->InvWidth*_CAMERA->Width()*4);
    mpData[13]=(lfY*gpWindow->InvHeight*_CAMERA->Height()*4);

}

void cImage::Width(float lfWidth)
{
    mfWidth=lfWidth*gpWindow->InvWidth*_CAMERA->Width()*2;
}
void cImage::Height(float lfHeight)
{
    mfHeight=lfHeight*gpWindow->InvHeight*_CAMERA->Height()*2;
}

void cImage::RenderPainter(uint8 liLevel)
{
(void) liLevel;

 if(mpPixmap)
 {
     glDisable(GL_DEPTH_TEST);
     glEnable(GL_DEPTH_CLAMP);
     ResizeArrays();
     SetShaderVariables();

   glBegin(GL_QUADS);

    glNormal3f(0.0f,0.0f,1.0f);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(-mfWidth,-mfHeight,2.1f);
    //glVertex2f(-mfWidth,-mfHeight
    //glNormal3f(0.0f,0.0f,1.0f);

    glTexCoord2f(1.0f,0.0f);
   // glVertex2f(mfWidth,-mfHeight);
    glVertex3f(mfWidth,-mfHeight,2.1f);

   // glNormal3f(0.0f,0.0f,1.0f);
    glTexCoord2f(1.0f,1.0f);
   // glVertex2f(mfWidth,mfHeight);
    glVertex3f(mfWidth,mfHeight,2.1f);

   // glNormal3f(0.0f,0.0f,1.0f);
    glTexCoord2f(0.0f,1.0f);
   // glVertex2f(-mfWidth,mfHeight);
    glVertex3f(-mfWidth,mfHeight,2.1f);

   glEnd();

   glDisable(GL_DEPTH_CLAMP);
   glEnable(GL_DEPTH_TEST);
 }

}


void cImage::Render()
{
 glEnable(GL_TEXTURE_2D);
 glDisable(GL_DEPTH);
 if (mpPixmap)
 {
  UpdateMatrix();

  mpPixmap->BindTexture();
  ResizeArrays();

  if(mpShader) mpShader->Use();
  else _USE_FIXED_FUNCTION();

  SetShaderVariables();

   glVertexPointer(3,GL_FLOAT,0,mpVertex);
   glTexCoordPointer(2,GL_FLOAT,0,mpTextCoords);
   glNormalPointer(GL_FLOAT,0,mpNormals);
   glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,mpFaces);
 glDisable(GL_TEXTURE_2D);
 }
 glEnable(GL_DEPTH);
}


void cImage::Texture(vTexture *lpGraph)
{
 mpPixmap=lpGraph;
}


void cImage::InitialiseArrays()
{

 mfWidth=100.0f;
 mfHeight=100.0f;

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
  mfWidth=lfSize*gpWindow->InvWidth*_CAMERA->Width()*2;
  mfHeight=mfWidth*gpWindow->mfRatio;

}
