#include "../WTDivWin.h"

cAudioBuffer::cAudioBuffer()
{
 cAudioDevice::Instance();
 alGetError();
 alGenBuffers(1,&miBuffer);
 
 if(alGetError()!= AL_NO_ERROR) trace("Audio Error\n"); //exit(WT_AUDIO_BUFFER_ERROR);
 
}

cAudioBuffer::~cAudioBuffer()
{

 alDeleteBuffers(1,&miBuffer);
}

ALuint cAudioBuffer::Buffer()
{
  return miBuffer;  
};