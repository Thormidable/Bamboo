#ifndef __WTCAUDIOOBJECT_H__
#define __WTCAUDIOOBJECT_H__
/**
 * \brief This class will allow a sound to be played.
 * This class will link an audio source and a buffer, This allows the sound data stored in the buffer to be played through the source. Each source is an audio channel and can only play one sound at a time.
 */
class cAudioObject : public cSignal
{
 // This is the ID of the OpenAL source owned by this object.
 ALuint miSource;
 // This is a pointer to the OpenAL buffer linked to this object.
 cAudioBuffer *mpBuffer;
public:
 /// This will create an OpenAL source for this object, without linking any cAudioBuffers to it.
 cAudioObject();
 /// This will create an OpenAL source and link this object to a buffer.
 cAudioObject(cAudioBuffer *lpBuffer);
 ~cAudioObject();
 /// This will link the OpenAL buffer pointed to by lpBuffer to this Audio Object ready to be played.
 void SetBuffer(cAudioBuffer *lpBuffer);
 /// This will play a sound through the OpenAL source from the buffer.
 void Play();
 /// This will return the ID of the OpenAL ID.
 ALuint Source();
 /// This will allow you to send signals to this object.
 void Signal(SIGNAL lsSignal);
};

#endif
