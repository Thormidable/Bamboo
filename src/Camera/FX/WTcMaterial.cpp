#include "stdafx.h"
#include "../../WTBamboo.h"

cMaterial::cMaterial()
{
mpSpecular[0]=1.0;
mpSpecular[1]=1.0;
mpSpecular[2]=1.0;
mpSpecular[3]=0.0;
mpShine[0]=50.0;
}

void cMaterial::SetSpecular(float lfRed,float lfGreen,float lfBlue,float lfAlpha)
{
 mpSpecular[0]=lfRed;
 mpSpecular[1]=lfGreen;
 mpSpecular[2]=lfBlue;
 mpSpecular[3]=lfAlpha;
}

void cMaterial::SetShine(float lfShine)
{
 mpShine[0]=lfShine;
}

void cMaterial::PrepareMaterial()
{
 //glMaterialfv(GL_FRONT, GL_SPECULAR, mpSpecular);
 //glMaterialfv(GL_FRONT, GL_SHININESS, mpShine);
}


