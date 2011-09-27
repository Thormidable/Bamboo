#include "../../WTDivWin.h"

void cSpotLight::Direction(float lfX,float lfY,float lfZ,float lfA)
{
 mpDirection[0]=lfX;
 mpDirection[1]=lfY;
 mpDirection[2]=lfZ;
 mpDirection[3]=lfA;
}


void cSpotLight::PrepareLight()
{
 glLightfv(GL_LIGHT0+miLightID, GL_POSITION, mpPosition);
 glLightfv(GL_LIGHT0+miLightID, GL_AMBIENT, mpAmbient);
 glLightfv(GL_LIGHT0+miLightID, GL_DIFFUSE, mpDiffuse);
 glLightfv(GL_LIGHT0+miLightID, GL_SPECULAR, mpSpecular);
 glLightf(GL_LIGHT0+miLightID, GL_CONSTANT_ATTENUATION+miAttenuationType, miAttenuation);
 glLightf(GL_LIGHT0+miLightID, GL_SPOT_CUTOFF, mpDirection[3]);
 glLightfv(GL_LIGHT0+miLightID, GL_SPOT_DIRECTION, mpDirection);
}

void cSpotLight::PrepareLight(uint32 liLight)
{
 glEnable(GL_LIGHT0+liLight);
 glLightfv(GL_LIGHT0+liLight, GL_POSITION, mpPosition);
 glLightfv(GL_LIGHT0+liLight, GL_AMBIENT, mpAmbient);
 glLightfv(GL_LIGHT0+liLight, GL_DIFFUSE, mpDiffuse);
 glLightfv(GL_LIGHT0+liLight, GL_SPECULAR, mpSpecular);
 glLightf(GL_LIGHT0+liLight, GL_CONSTANT_ATTENUATION+miAttenuationType, miAttenuation);
 glLightf(GL_LIGHT0+liLight, GL_SPOT_CUTOFF, mpDirection[3]);
 glLightfv(GL_LIGHT0+liLight, GL_SPOT_DIRECTION, mpDirection);
}
