#include "stdafx.h"
#include "../../WTBamboo.h"
//#include <cmath>

cLine::cLine(bool lbNoTex) : cRenderObject(lbNoTex)
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

mfWidth=1.0f;

}

cLine::cLine(cCamera *lpCamera,bool lbNoTex) : cRenderObject(lpCamera,lbNoTex)
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

mfWidth=1.0f;
}

cLine::cLine(vRenderNode *lpRenderer,bool lbNoTex) : cRenderObject(lpRenderer,lbNoTex)
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

mfWidth=1.0f;
}


void cLine::RenderPainter()
{

	glLineWidth(mfWidth);
  SetShaderVariables();
  glBegin(GL_LINES);
    //glColor4fv(mfColor.Color());
    glVertex3fv(mfPosition.v);
    glVertex3fv(mfEnd.v);
  glEnd();
}

void cLine::Width(float lfWidth){mfWidth=lfWidth;};
float cLine::Width(){return mfWidth;};


float *cLine::Position()
{
  return mfPosition.v;
}

void cLine::Position(float* lfPos){mfPosition=lfPos;};

void cLine::Position(float lfX,float lfY,float lfZ)
{
  mfPosition[0]=lfX;
  mfPosition[1]=lfY;
  mfPosition[2]=lfZ;
}

float *cLine::Vector()
{
  return mfVector.v;
}

void cLine::Vector(float* lfPos)
{
  mfVector=lfPos;
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


float cLine::GetSize()
{
    return sqrt(mfVector[0]*mfVector[0]+mfVector[1]*mfVector[1]+mfVector[2]*mfVector[2]);
}

double cLine::GetSizeSq()
{
  return mfVector[0]*mfVector[0]+mfVector[1]*mfVector[1]+mfVector[2]*mfVector[2];
}

float *cLine::EndPoint(){return mfEnd.v;};
void cLine::EndPoint(float* lfPos)
{
    mfEnd=lfPos;

    mfVector[0]=mfEnd[0]-mfPosition[0];
    mfVector[1]=mfEnd[1]-mfPosition[1];
    mfVector[2]=mfEnd[2]-mfPosition[2];
};

void cLine::EndPoint(float lfX,float lfY,float lfZ)
{
    mfEnd[0]=lfX;
    mfEnd[1]=lfY;
    mfEnd[2]=lfZ;

    mfVector[0]=mfEnd[0]-mfPosition[0];
    mfVector[1]=mfEnd[1]-mfPosition[1];
    mfVector[2]=mfEnd[2]-mfPosition[2];

};

cLineRectangle::cLineRectangle() : cRenderObject(1)
{
    Set2D();

    mvEdges[0]=-1.0f;
    mvEdges[1]=0.0f;
    mvEdges[2]=0.0f;
    mvEdges[3]=-1.0f;
    mfWidth=1.0f;
};

cLineRectangle::cLineRectangle(vRenderNode *lpRenderer) : cRenderObject(lpRenderer,1)
{
        Set2D();
    mvEdges[0]=-1.0f;
    mvEdges[1]=0.0f;
    mvEdges[2]=0.0f;
    mvEdges[3]=-1.0f;
    mfWidth=1.0f;
};
cLineRectangle::cLineRectangle(cCamera *lpCamera) : cRenderObject(lpCamera,1)
{
        Set2D();
    mvEdges[0]=-1.0f;
    mvEdges[1]=0.0f;
    mvEdges[2]=0.0f;
    mvEdges[3]=-1.0f;
    mfWidth=1.0f;
};

float cLineRectangle::Width(){return mfWidth;};
void cLineRectangle::Width(float lfWidth){mfWidth=lfWidth;};

void cLineRectangle::RenderPainter()
{

  glLineWidth(mfWidth);
  SetShaderVariables();
  float lfDist=mpCamera->Near()+0.5f;
  //float lfDist=1.0f;
    glBegin(GL_LINE_LOOP);
    glVertex3f(-mvEdges[3],-mvEdges[0],lfDist);
    glVertex3f(-mvEdges[3],-mvEdges[1],lfDist);
    glVertex3f(-mvEdges[2],-mvEdges[1],lfDist);
    glVertex3f(-mvEdges[2],-mvEdges[0],lfDist);
  glEnd();
}

  void cLineRectangle::Top(float lfTop){mvEdges[0]=lfTop;};
  void cLineRectangle::Bottom(float lfBottom){mvEdges[1]=lfBottom;};
  void cLineRectangle::Right(float lfRight){mvEdges[3]=lfRight;};
  void cLineRectangle::Left(float lfLeft){mvEdges[2]=lfLeft;};

  void cLineRectangle::Edges(c4DVf lvTBLR){mvEdges=lvTBLR;};
  void cLineRectangle::Edges(c2DVf lvTL,c2DVf lvBR)
  {
      mvEdges[0]=lvTL[0];
      mvEdges[1]=lvBR[0];
      mvEdges[2]=lvTL[1];
      mvEdges[3]=lvBR[1];
  };

 c4DVf cLineRectangle::Edges()
 {
     return mvEdges;
 };

  float cLineRectangle::Top(){return mvEdges[0];};
  float cLineRectangle::Bottom(){return mvEdges[1];};
  float cLineRectangle::Right(){return mvEdges[3];};
  float cLineRectangle::Left(){return mvEdges[2];};

