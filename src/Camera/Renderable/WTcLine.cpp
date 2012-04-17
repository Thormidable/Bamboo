#include "../../WTBamboo.h"
//#include <cmath>

cLine::cLine() : cRenderObject(1)
{
 Identity();

 mfPosition[0]=0.0f;
 mfPosition[1]=0.0f;
 mfPosition[2]=0.0f;

mfVector[0]=0.0f;
mfVector[1]=1.0f;
mfVector[2]=0.0f;

mfEnd[0]=0.0f;
mfEnd[1]=1.0f;
mfEnd[2]=0.0f;

mfColor[0]=0.0f;
mfColor[1]=0.0f;
mfColor[2]=0.0f;
mfColor[3]=0.0f;

}

cLine::cLine(cCamera *lpCamera) : cRenderObject(lpCamera,1)
{
Identity();
}

cLine::cLine(vRenderNode *lpRenderer) : cRenderObject(lpRenderer,1)
{
 Identity();
}


void cLine::RenderPainter()
{

  SetShaderVariables();
  glBegin(GL_LINES);
    glColor4fv(mfColor.Color());
    glVertex3fv(mfPosition);
    glVertex3fv(mfEnd);
  glEnd();
}



void cLine::Color(float lfR,float lfG,float lfB,float lfA)
{
 mfColor[0]=lfR;
 mfColor[1]=lfG;
 mfColor[2]=lfB;
 mfColor[3]=lfA;
}

void cLine::Color(float *lpColor)
{
    mfColor=lpColor;
}

cRGBA *cLine::Color()
{
 return &mfColor;
}
 /* UpdateMatrix();

   AdditionalRenderFunctions();

  glBegin(GL_POINTS);
    glColor4fv(mfColor);
    glVertex3fv(Matrix(12));
  glEnd();

}
*/

float *cLine::Position()
{
  return mfPosition;
}

void cLine::Position(float* lfPos){memcpy(mfPosition,lfPos,sizeof(float)*3);};

void cLine::Position(float lfX,float lfY,float lfZ)
{
  mfPosition[0]=lfX;
  mfPosition[1]=lfY;
  mfPosition[2]=lfZ;
}

float *cLine::Vector()
{
  return mfVector;
}

void cLine::Vector(float* lfPos)
{
  memcpy(mfVector,lfPos,sizeof(float)*3);
  mfEnd[0]=mfVector[0]+mfPosition[0];
  mfEnd[1]=mfVector[1]+mfPosition[1];
  mfEnd[2]=mfVector[2]+mfPosition[2];
};

void cLine::Vector(float lfX,float lfY,float lfZ)
{
  mfVector[0]=lfX;
  mfVector[1]=lfY;
  mfVector[2]=lfZ;
  mfEnd[0]=mfVector[0]+mfPosition[0];
  mfEnd[1]=mfVector[1]+mfPosition[1];
  mfEnd[2]=mfVector[2]+mfPosition[2];
}


void cLine::Color(cRGBA &lpColor){mfColor=lpColor;}
void cLine::Color(cRGBA *lpColor){mfColor=lpColor;}
void cLine::Color(cRGB &lpColor){mfColor=lpColor;}
void cLine::Color(cRGB *lpColor){mfColor=lpColor;}

float cLine::GetSize()
{
    return sqrt(mfVector[0]*mfVector[0]+mfVector[1]*mfVector[1]+mfVector[2]*mfVector[2]);
}

double cLine::GetSizeSq()
{
  return mfVector[0]*mfVector[0]+mfVector[1]*mfVector[1]+mfVector[2]*mfVector[2];
}
