#include "stdafx.h"
#include "../WTBamboo.h"


cRenderPointer::cRenderPointer()
{
 mpObject=0;
 miDist=0;
 mpTexture=0;
 miAlpha=0;
 mpShader=0;
 ShaderPoint=0;
}

cRenderPointer cRenderPointer::operator=(cRenderPointer lcOther)
{
mpObject=lcOther.mpObject;
mpTexture=lcOther.mpTexture;
miAlpha=lcOther.miAlpha;
mpShader=lcOther.mpShader;
miDist=lcOther.miDist;
return *this;
}

void cRenderPointer::SetObject(cRenderObject *lpObject)
{
	mpObject=lpObject;
	UpdateTexture(0);
}

void cRenderPointer::SetShader(cShaderProgram *lpShader){mpShader=reinterpret_cast<psize>(lpShader);ShaderPoint=lpShader;}
void cRenderPointer::SetAlpha(uint8 lbAlpha){miAlpha=lbAlpha;}

inline void cRenderPointer::SetAll(cRenderObject *lpObject,cShaderProgram *lpShader,uint8 lbAlpha)
{
mpObject=lpObject;
UpdateTexture(0);
mpShader=reinterpret_cast<psize>(lpShader);
ShaderPoint=lpShader;
miAlpha=lbAlpha;
}


void cRenderPointer::UpdateTexture(uint8 liTexSlot)
{
 cTextureSlot *Slot;
 Slot=&(mpObject->TextureItem(liTexSlot));
 if(mpObject->Textures()) mpTexture=reinterpret_cast<psize>(Slot->mpTexture);
 else mpTexture=0;
}
