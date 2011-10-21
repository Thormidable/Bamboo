#include "../../WTDivWin.h"


cPoint::cPoint()
{
 Identity();  
mfColor[0]=0.0f;
mfColor[1]=0.0f;
mfColor[2]=0.0f;
mfColor[3]=0.0f;
}

cPoint::cPoint(cRenderNode *lpRenderer) : cRenderObject(lpRenderer)
{
 Identity();
}


void cPoint::RenderPainter(uint8 liLevel)
{
(void) liLevel;
    SetShaderVariables();
  glPointSize(mfPointSize);
  glBegin(GL_POINTS);
    glColor4fv(mfColor);
    glVertex3f(0.0f,0.0f,0.0f);
  glEnd();
  

}

void cPoint::RenderToPainter()
{
 float Temp[16];
 UpdateMatrix();

 glGetFloatv(GL_MODELVIEW_MATRIX,Temp);

 //mpPainterData->SetMatrix(Temp);
 mpPainterData->SetObject(this);
 mpPainterData->SetShader(mpShader);
 mpPainterData->RenderAgain();
 cPainter::Instance()->Add(mpPainterData);
}

void cPoint::Render()
{

  UpdateMatrix();
  glPointSize(mfPointSize);

    if(mpShader) mpShader->Use();
  else _USE_FIXED_FUNCTION();

  AdditionalRenderFunctions();

  
  glBegin(GL_POINTS);
    glColor4fv(mfColor);
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
  memcpy(mfColor,lpColor,sizeof(float)*4);
}

float *cPoint::Color()
{
 return mfColor;
}

void cPoint::PointSize(float lfPointSize)
{
  mfPointSize=lfPointSize;
  
};
