#include "../../WTBamboo.h"
#include <cmath>

#if WT_FULL_VERSION_BAMBOO

bool cImage::mbFirst=1;
float cImage::mpVertex[12];
uint16 cImage::mpFaces[6];
float cImage::mpTextCoords[8];
float cImage::mpNormals[12];





cImage::~cImage(){}

cImage::cImage()
{
 SetUp();
}

cImage::cImage(vRenderNode *lpRenderNode) : cRenderObject(lpRenderNode)
{
 SetUp();
}

cImage::cImage(cCamera *lpCamera) : cRenderObject(lpCamera)
{
 SetUp();
}

void cImage::SetUp()
{
 Set2D();
 InitialiseArrays();
 Transparency(true);
 mfPriority=6.0f;
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


void cImage::RenderPainter()
{
 if(Textures())
 {
     ResizeArrays();
     SetShaderVariables();
    float lfWidth=mfWidth*0.5f;
    float lfHeight=mfHeight*0.5f;
   glBegin(GL_QUADS);

    glNormal3f(0.0f,0.0f,1.0f);

    glMultiTexCoord2f(GL_TEXTURE0,1.0f,0.0f);
    glVertex3f(-lfWidth,lfHeight,mfPriority);

    glMultiTexCoord2f(GL_TEXTURE0,0.0f,0.0f);
    glVertex3f(lfWidth,lfHeight,mfPriority);

    glMultiTexCoord2f(GL_TEXTURE0,0.0f,1.0f);
    glVertex3f(lfWidth,-lfHeight,mfPriority);

    glMultiTexCoord2f(GL_TEXTURE0,1.0f,1.0f);
    glVertex3f(-lfWidth,-lfHeight,mfPriority);


   glEnd();

 }

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

float cImage::Priority()
{
    return mfPriority-1.0f;
}

void cImage::Priority(float lfPriority)
{
    mfPriority=lfPriority+1.0f;
}

cImage3D::cImage3D()
{

}

cImage3D::cImage3D(vRenderNode *lpNode): cImage(lpNode)
{

}

cImage3D::cImage3D(cCamera *lpCamera): cImage(lpCamera)
{

}


void cImage3D::RenderPainter()
{

 if(Textures())
 {
     ResizeArrays();
     SetShaderVariables();
    float lfWidth=mfWidth*0.5f;
    float lfHeight=mfHeight*0.5f;
   glBegin(GL_QUADS);

    glNormal3f(0.0f,0.0f,1.0f);

    glMultiTexCoord2f(GL_TEXTURE0,0.0f,1.0f);
    glVertex3f(-lfWidth,lfHeight,0.0f);

    glMultiTexCoord2f(GL_TEXTURE0,1.0f,1.0f);
    glVertex3f(lfWidth,lfHeight,0.0f);

    glMultiTexCoord2f(GL_TEXTURE0,1.0f,0.0f);
    glVertex3f(lfWidth,-lfHeight,0.0f);

    glMultiTexCoord2f(GL_TEXTURE0,0.0f,0.0f);
    glVertex3f(-lfWidth,-lfHeight,0.0f);

   glEnd();

 }

}

#endif
