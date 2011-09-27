#include "../WTDivWin.h"

cAudioDevice *cAudioDevice::mpInstance=0;

cAudioDevice::cAudioDevice()
{
 mpDevice=alcOpenDevice("Generic Software");
 if(mpDevice)
 {
  mpContext=alcCreateContext(mpDevice,NULL);
  alcMakeContextCurrent(mpContext);
  return;
 }

 mpDevice=alcOpenDevice(NULL);
 if(mpDevice)
 {
  mpContext=alcCreateContext(mpDevice,NULL);
  alcMakeContextCurrent(mpContext);
  return;
 }
 exit(WT_AUDIO_DEVICE_OPENING_ERROR);
}

cAudioDevice::~cAudioDevice()
{
 alcMakeContextCurrent(NULL);
 alcDestroyContext(mpContext);
 alcCloseDevice(mpDevice);
}

cAudioDevice *cAudioDevice::Instance()
{
  if(!mpInstance) mpInstance=new cAudioDevice; 
  return mpInstance;
};