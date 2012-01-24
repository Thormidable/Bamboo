#include "../WTBamboo.h"


cRenderPointer::cRenderPointer()
{
 mpObject=0;
 miDist=0;
 mpTexture=0;
 mbAlpha=false;
 mpShader=0;
 ShaderPoint=0;
}

cRenderPointer cRenderPointer::operator=(cRenderPointer lcOther)
{
mpObject=lcOther.mpObject;
mpTexture=lcOther.mpTexture;
mbAlpha=lcOther.mbAlpha;
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
void cRenderPointer::SetAlpha(bool lbAlpha){mbAlpha=lbAlpha;}

inline void cRenderPointer::SetAll(cRenderObject *lpObject,cShaderProgram *lpShader,bool lbAlpha)
{
mpObject=lpObject;
UpdateTexture(0);
mpShader=reinterpret_cast<psize>(lpShader);
ShaderPoint=lpShader;
mbAlpha=lbAlpha;
}

void cRenderPointer::UpdateTexture(uint8 liTexSlot)
{
 cTextureSlot *Slot;
 Slot=&(mpObject->TextureItem(liTexSlot));
 if(mpObject->Textures()) mpTexture=reinterpret_cast<psize>(Slot->mpTexture);
 else mpTexture=0;
}
