#include "../../WTBamboo.h"


cPoint::cPoint() : cRenderObject(true)
{
 Identity();
mfColor[0]=0.0f;
mfColor[1]=0.0f;
mfColor[2]=0.0f;
mfColor[3]=0.0f;
}

cPoint::cPoint(vRenderNode *lpRenderer) : cRenderObject(lpRenderer,true)
{
 Identity();
}

cPoint::cPoint(cCamera *lpCamera) : cRenderObject(lpCamera,true)
{
 Identity();
}

void cPoint::RenderPainter()
{
    SetShaderVariables();
  //glPointSize(mfPointSize);
  glBegin(GL_POINTS);
    glColor4fv(mfColor.Color());
    glVertex3f(0.0f,0.0f,0.0f);
  glEnd();


}


void cPoint::Color(float lfR,float lfG,float lfB,float lfA)
{
 mfColor[0]=lfR;
 mfColor[1]=lfG;
 mfColor[2]=lfB;
 mfColor[3]=lfA;
}

void cPoint::Color(float *lpColor)
{
  memcpy(mfColor.Color(),lpColor,sizeof(float)*4);
}

float *cPoint::Color()
{
 return mfColor.Color();
}
/*
void cPoint::PointSize(float lfPointSize)
{
  mfPointSize=lfPointSize;

};
*/
void cPoint::Color(cRGB *lpOther){mfColor=lpOther;}
void cPoint::Color(cRGBA *lpOther){mfColor=lpOther;}
void cPoint::Color(cRGB &lpOther){mfColor=lpOther;}
void cPoint::Color(cRGBA &lpOther){mfColor=lpOther;}
