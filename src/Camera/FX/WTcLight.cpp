#include "../../WTDivWin.h"

cLight::~cLight()
{
 mpNode=0;

}

cLightHandler *cLight::mpLightHandler=0;


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
 mpLightHandler->MoreAwake();
}

void cLight::Position(float lfX,float lfY,float lfZ)
{
 mpPosition[0]=lfX;
 mpPosition[1]=lfY;
 mpPosition[2]=lfZ;
 //For being used in multiplication with 4x4 Matrices.
 mpPosition[3]=1;
}

void cLight::Ambient(float lfR,float lfG,float lfB,float lfA){ mpAmbient.Set(lfR,lfG,lfB,lfA);}
void cLight::Ambient(cRGBA &lcColor){mpAmbient=lcColor;};
void cLight::Ambient(cRGBA *lcColor){mpAmbient=lcColor;};
void cLight::Ambient(cRGB &lcColor){mpAmbient=lcColor;};
void cLight::Ambient(cRGB *lcColor){mpAmbient=lcColor;};

void cLight::Diffuse(float lfR,float lfG,float lfB,float lfA){ mpDiffuse.Set(lfR,lfG,lfB,lfA);}
void cLight::Diffuse(cRGBA &lcColor){mpDiffuse=lcColor;};
void cLight::Diffuse(cRGBA *lcColor){mpDiffuse=lcColor;};
void cLight::Diffuse(cRGB &lcColor){mpDiffuse=lcColor;};
void cLight::Diffuse(cRGB *lcColor){mpDiffuse=lcColor;};

void cLight::Specular(float lfR,float lfG,float lfB,float lfA){ mpSpecular.Set(lfR,lfG,lfB,lfA);}
void cLight::Specular(cRGBA &lcColor){mpSpecular=lcColor;};
void cLight::Specular(cRGBA *lcColor){mpSpecular=lcColor;};
void cLight::Specular(cRGB &lcColor){mpSpecular=lcColor;};
void cLight::Specular(cRGB *lcColor){mpSpecular=lcColor;};


void cLight::PrepareLight(uint32 liLight)
{
 glLightfv(GL_LIGHT0+liLight, GL_POSITION, mpPosition);
 glLightfv(GL_LIGHT0+liLight, GL_AMBIENT, mpAmbient.Color());
 glLightfv(GL_LIGHT0+liLight, GL_DIFFUSE, mpDiffuse.Color());
 glLightfv(GL_LIGHT0+liLight, GL_SPECULAR, mpSpecular.Color());
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


void cLight::Signal(SIGNAL lsSignal)
{
	if(lsSignal&WT_SIGNAL_VALUE_WAKE && !mbAwake)
	{
	    mpLightHandler->MoreAwake();
	    mbAwake=true;
	    AdditionalWakeFunctionality();
    }
	if(lsSignal&WT_SIGNAL_VALUE_SLEEP && mbAwake)
	{
	    mpLightHandler->MoreAsleep();
	    mbAwake=false;
	    AdditionalSleepFunctionality();
	}
	if(lsSignal&WT_SIGNAL_VALUE_KILL && mbAlive)
	{
	    if(mbAwake) mpLightHandler->MoreAsleep();
	    mbAlive=false;
	    mbAwake=false;
	    AdditionalKillFunctionality();
	    mpLightHandler->Remove(mpNode);
    }
}

