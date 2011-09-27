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
 float Temp[16];
 UpdateMatrix();
 glGetFloatv(GL_MODELVIEW_MATRIX,Temp);

 //cRenderPointer lcTemp;
 mpPainterData->SetObject(this);
 //mpPainterData->SetMatrix(Temp);
 mpPainterData->SetTexture(TextureNumber());

mpPainterData->RenderAgain();
// cPainter::Instance()->Add(lcTemp);
}
}

void cImage::RenderPainter(uint8 liLevel)
{
(void) liLevel;
 if(mpPixmap)
 {
   ResizeArrays();
   glVertexPointer(3,GL_FLOAT,0,mpVertex);
   glTexCoordPointer(2,GL_FLOAT,0,mpTextCoords);
   glNormalPointer(GL_FLOAT,0,mpNormals);

   glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,mpFaces);
 }
}


void cImage::Render()
{
 glEnable(GL_TEXTURE_2D);
 if (mpPixmap)
 {
  UpdateMatrix();
  mpPixmap->BindTexture();
  ResizeArrays();

  if(mpShader) mpShader->Use();
  else _USE_FIXED_FUNCTION();
  
   glVertexPointer(3,GL_FLOAT,0,mpVertex);
   glTexCoordPointer(2,GL_FLOAT,0,mpTextCoords);
   glNormalPointer(GL_FLOAT,0,mpNormals);
   glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,mpFaces);
 glDisable(GL_TEXTURE_2D);
 }
}


void cImage::Texture(vTexture *lpGraph)
{
 mpPixmap=lpGraph;
}


void cImage::InitialiseArrays()
{

 mfSize=1.0f;

 if(mbFirst)
 {
  //order is BR TR TL BL
  mbFirst=0;
  mpVertex[7]=mpVertex[4]=mpVertex[3]=mpVertex[0]=1.0f;
  mpVertex[1]=mpVertex[2]=mpVertex[5]=mpVertex[6]=mpVertex[8]=mpVertex[9]=mpVertex[10]=mpVertex[11]=0.0f;

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
 mpVertex[7]=mpVertex[4]=mpVertex[3]=mpVertex[0]=mfSize;
}

unsigned int cImage::TextureNumber()
{
  if(mpPixmap) return mpPixmap->TextureNumber(); return 0;
  
}

void cImage::Size(float lfSize)
{
  mfSize=lfSize;
  
}