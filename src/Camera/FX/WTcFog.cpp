#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO
cFog::cFog()
{
 lbOn=1;

 mtMode=GL_EXP;
 mpColor[0]=1.0;
 mpColor[1]=1.0;
 mpColor[2]=1.0;
 mpColor[3]=0.5;

 mfDensity=0.25;
 mfStart=cCamera::Instance()->Near();
 mfEnd=cCamera::Instance()->Far();
}

cFog::cFog(float lfStart,float lfEnd)
{
 lbOn=1;

 mtMode=GL_EXP;
 mpColor[0]=1.0;
 mpColor[1]=1.0;
 mpColor[2]=1.0;
 mpColor[3]=0.5;

 mfDensity=0.25;

 mfStart=lfStart;
 mfEnd=lfEnd;
}

void cFog::SetOn()
{
 glEnable(GL_FOG);
 glFogi(GL_FOG_MODE,mtMode);
 glFogfv(GL_FOG_COLOR, mpColor);
 glFogf(GL_FOG_DENSITY, mfDensity);
 glFogf(GL_FOG_START, mfStart);
 glFogf(GL_FOG_END, mfEnd);
 glClearColor(mpColor[0],mpColor[1],mpColor[2],1.0f);
}

void cFog::SetOff()
{
 glDisable(GL_FOG);
}

void cFog::SetColor(float lfRed,float lfGreen,float lfBlue,float lfAlpha)
{
  mpColor[0]=lfRed;
  mpColor[1]=lfGreen;
  mpColor[2]=lfBlue;
  mpColor[3]=lfAlpha;
};

void cFog::SetMode(char ltMode)
{
  mtMode=ltMode;

}

void cFog::SetDensity(float lfDensity)
{
  mfDensity=lfDensity;

}


void cFog::SetRange(float lfStart,float lfEnd)
{
  mfStart=lfStart;
  mfEnd=lfEnd;
}

bool cFog::On()
{
  return lbOn;

}

#endif
