#ifndef __WTCAUDIOOBJECT_H__
#define __WTCAUDIOOBJECT_H__
/*
*/
class cAudioObject;
class cAudioListener
 {
     static cAudioListener *mpInstance;
     friend class cAudioObject;
     cAudioListener(){};
    float spPosition[3];
    float spSpeed[3];
    float spOrientation[6];

   public:
    static cAudioListener *Instance();
    void Position(float lfX,float lfY,float lfZ);
    void Speed(float lfX,float lfY,float lfZ);
    void Orientation(float lfZX,float lfZY,float lfZZ,float lfYX,float lfYY,float lfYZ);
    void Position(float *lpList);
    void Speed(float *lpList);
    void Orientation(float *lpList);
    float *Position();
    float *Speed();
    float *Orientation();

 };
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

 float mpPosition[3];
 float mpSpeed[3];
 bool StoringSpeed;
 bool mbLooping;
 float mfGain;
 float mfPitch;

~cAudioObject();
public:
 /// This will create an OpenAL source for this object, without linking any cAudioBuffers to it.
 cAudioObject();
 /// This will create an OpenAL source and link this object to a buffer.
 cAudioObject(cAudioBuffer *lpBuffer);

 /// This will link the OpenAL buffer pointed to by lpBuffer to this Audio Object ready to be played.
 void SetBuffer(cAudioBuffer *lpBuffer);
 /// This will play a sound through the OpenAL source from the buffer.
 void Play();
 /// This will stop the currently playing sound and reset the play position to the start.
 void Stop();
 /// This will pause the currently playing sound but retain the current play position.
 void Pause();
 /// This will return the ID of the OpenAL ID.
 ALuint Source();
 /// This will allow you to send signals to this object.
 void Signal(SIGNAL lsSignal);

  void Position(float lfX,float lfY,float lfZ);
  void Speed(float lfX,float lfY,float lfZ);
  void Loop(bool lbLoop);
  float *Position();
  float *Speed();
  bool Loop();
  void Gain(float lfGain);
  void Pitch(float lfPitch);
  float Gain();
  float Pitch();

};



#endif
