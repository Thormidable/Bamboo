#include "../WTBamboo.h"

void cRenderPointer::RenderAgain()
{
  mbReRender=true;

};

cRenderPointer::cRenderPointer()
{
 mpObject=0;
 miDist=0;
 mpTexture=0;
 mbAlpha=false;
 mpShader=0;
 miLevel=0;
 mbReRender=false;
}

cRenderPointer cRenderPointer::operator=(cRenderPointer lcOther)
{
mpObject=lcOther.mpObject;
mpTexture=lcOther.mpTexture;
mbAlpha=lcOther.mbAlpha;
mpShader=lcOther.mpShader;
miLevel=lcOther.miLevel;
miDist=lcOther.miDist;
return *this;
}

void cRenderPointer::SetObject(cRenderObject *lpObject){mpObject=lpObject;}
void cRenderPointer::SetTexture(uint32 liTexture){mpTexture=liTexture;}
void cRenderPointer::SetShader(cShaderProgram *lpShader){mpShader=lpShader;}
void cRenderPointer::SetLevel(uint32 liLevel){miLevel=liLevel;}
void cRenderPointer::SetAlpha(bool lbAlpha){mbAlpha=lbAlpha;}

inline void cRenderPointer::SetAll(cRenderObject *lpObject,uint32 liTexture,cShaderProgram *lpShader,bool lbAlpha,uint32 liLevel)
{
mpObject=lpObject;
mpTexture=liTexture;
mpShader=lpShader;
mbAlpha=lbAlpha;
miLevel=liLevel;
}


