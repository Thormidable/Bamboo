#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

void cSpotLight::Direction(float lfX,float lfY,float lfZ,float lfA)
{
 mpDirection[0]=lfX;
 mpDirection[1]=lfY;
 mpDirection[2]=lfZ;
 mpDirection[3]=lfA;
}

cSpotLight::cSpotLight()
{
 Direction(0.0f,0.0f,1.0f,10.0f);

}
void cSpotLight::PrepareLight(uint32 liLight)
{
 glLightfv(GL_LIGHT0+liLight, GL_POSITION, mpPosition);
 glLightfv(GL_LIGHT0+liLight, GL_AMBIENT, mpAmbient.Color());
 glLightfv(GL_LIGHT0+liLight, GL_DIFFUSE, mpDiffuse.Color());
 glLightfv(GL_LIGHT0+liLight, GL_SPECULAR, mpSpecular.Color());
 glLightf(GL_LIGHT0+liLight, GL_CONSTANT_ATTENUATION+miAttenuationType, miAttenuation);
 glLightf(GL_LIGHT0+liLight, GL_SPOT_CUTOFF, mpDirection[3]);
 glLightfv(GL_LIGHT0+liLight, GL_SPOT_DIRECTION, mpDirection);
}

#endif
