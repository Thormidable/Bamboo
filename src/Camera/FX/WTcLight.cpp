#include "../../WTDivWin.h"

cLight::~cLight()
{
 mpNode=0;
}

cLightHandler *cLight::mpLightHandler=0;

void cLight::SetID(uint8 liLightID)
{
 miLightID=liLightID;
}

cLight::cLight()
{
 
 mpLightHandler=cLightHandler::Instance();
 mpNode=mpLightHandler->Add(this);

 Position(0.0f,0.0f,0.0f);
 Ambient(0.5f,0.5f,0.5f,0.0f);
 Diffuse(1.0f,1.0f,1.0f,0.0f);
 Specular(1.0f,1.0f,1.0f,0.0f);
 Attenuation(2.0f);
 AttenuationType(0);
}

void cLight::Position(float lfX,float lfY,float lfZ)
{
 mpPosition[0]=lfX;
 mpPosition[1]=lfY;
 mpPosition[2]=lfZ;
 uint32 CHECK_WTF_THIS_IS_FOR;
 mpPosition[3]=1;
}

void cLight::Ambient(float lfR,float lfG,float lfB,float lfA)
{
 mpAmbient[0]=lfR;
 mpAmbient[1]=lfG;
 mpAmbient[2]=lfB;
 mpAmbient[3]=lfA;
}

void cLight::Diffuse(float lfR,float lfG,float lfB,float lfA)
{
 mpDiffuse[0]=lfR;
 mpDiffuse[1]=lfG;
 mpDiffuse[2]=lfB;
 mpDiffuse[3]=lfA;
}

void cLight::Specular(float lfR,float lfG,float lfB,float lfA)
{
 mpSpecular[0]=lfR;
 mpSpecular[1]=lfG;
 mpSpecular[2]=lfB;
 mpSpecular[3]=lfA;
}


void cLight::PrepareLight()
{
 glLightfv(GL_LIGHT0+miLightID, GL_POSITION, mpPosition);
 glLightfv(GL_LIGHT0+miLightID, GL_AMBIENT, mpAmbient);
 glLightfv(GL_LIGHT0+miLightID, GL_DIFFUSE, mpDiffuse);
 glLightfv(GL_LIGHT0+miLightID, GL_SPECULAR, mpSpecular);
 glLightf(GL_LIGHT0+miLightID, GL_CONSTANT_ATTENUATION+miAttenuationType, miAttenuation);
}

void cLight::PrepareLight(uint32 liLight)
{
 glEnable(GL_LIGHT0+liLight);
 glLightfv(GL_LIGHT0+liLight, GL_POSITION, mpPosition);
 glLightfv(GL_LIGHT0+liLight, GL_AMBIENT, mpAmbient);
 glLightfv(GL_LIGHT0+liLight, GL_DIFFUSE, mpDiffuse);
 glLightfv(GL_LIGHT0+liLight, GL_SPECULAR, mpSpecular);
 glLightf(GL_LIGHT0+liLight, GL_CONSTANT_ATTENUATION+miAttenuationType, miAttenuation);
}

void cLight::AttenuationType(uint8 liOrder)
{
miAttenuationType=liOrder;
}

void cLight::Attenuation(float liAttenuation)
{
  miAttenuation=liAttenuation;
  
};

