#include "../WTDivWin.h"

cAudioObject::cAudioObject()
{
 cAudioDevice::Instance();
 alGenSources(1, &miSource);
}

cAudioObject::cAudioObject(cAudioBuffer *lpBuffer)
{
 cAudioDevice::Instance();
 alGenSources(1, &miSource);
 mpBuffer=lpBuffer;
 alSourcei(miSource,AL_BUFFER,lpBuffer->Buffer());
}

cAudioObject::~cAudioObject()
{
 alDeleteSources(1,&miSource);
}

void cAudioObject::Play()
{
 alSourcePlay(miSource);
}

void cAudioObject::SetBuffer(cAudioBuffer *lpBuffer)
{
 mpBuffer=lpBuffer;
 
 alSourcei(miSource,AL_BUFFER,lpBuffer->Buffer());
 
}

ALuint cAudioObject::Source()
{
  return miSource;
  
};
