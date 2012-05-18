#include "../../WTBamboo.h"
//#include <cmath>

cLineArray::cLineArray() : cRenderObject(1)
{
 mpData=0;
}

cLineArray::cLineArray(cCamera *lpCamera) : cRenderObject(lpCamera,1)
{
mpData=0;
}

cLineArray::cLineArray(vRenderNode *lpRenderer) : cRenderObject(lpRenderer,1)
{
 mpData=0;
}


void cLineArray::RenderPainter()
{
 if(mpData)
 {
    SetShaderVariables();
    mpData->RenderLines();
 }
}

void cLineArray::Data(cLineArrayData *lpData)
{
    mpData=lpData;
}

