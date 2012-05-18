#include "../../WTBamboo.h"


cBillBoard::cBillBoard() : cRenderObject()
{
 Identity();
}

cBillBoard::cBillBoard(vRenderNode *lpRenderer) : cRenderObject(lpRenderer)
{
 Identity();
}

cBillBoard::cBillBoard(cCamera *lpCamera) : cRenderObject(lpCamera)
{
 Identity();
}

void cBillBoard::RenderPainter()
{
    SetShaderVariables();
  glBegin(GL_POINTS);
    glVertex3f(0.0f,0.0f,0.0f);
  glEnd();


}
