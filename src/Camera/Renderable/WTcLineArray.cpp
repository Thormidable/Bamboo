#include "stdafx.h"
#include "../../WTBamboo.h"
//#include <cmath>

cLineArray::cLineArray() : cRenderObject(1)
{
 mpData=0;
 mfWidth=1.0f;
}

cLineArray::cLineArray(cCamera *lpCamera) : cRenderObject(lpCamera,1)
{
mpData=0;
mfWidth=1.0f;
}

cLineArray::cLineArray(vRenderNode *lpRenderer) : cRenderObject(lpRenderer,1)
{
 mpData=0;
 mfWidth=1.0f;
}


void cLineArray::RenderPainter()
{
 if(mpData)
 {
    SetShaderVariables();
	glLineWidth(mfWidth);
    mpData->RenderLines();
 }
}

void cLineArray::Data(cLineArrayData *lpData)
{
    mpData=lpData;
}

void cLineArray::Width(float lfWidth)
{
 mfWidth=lfWidth;
};
float cLineArray::Width()
{
 return mfWidth;
};