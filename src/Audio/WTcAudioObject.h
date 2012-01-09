#ifndef __WTCAUDIOOBJECT_H__
#define __WTCAUDIOOBJECT_H__

class cAudioObject;
/**
 * \brief This controls the state of the Listener.
 * This is the assumed position, facing and velocity of the user for the purposes of Sound.
**/
class cAudioListener
 {
     static cAudioListener *mpInstance;
     friend class cAudioObject;
     cAudioListener(){};
    float spPosition[3];
    float spSpeed[3];
    float spOrientation[6];

   public:
	   ///Gets a pointer to the cAudioListener singleton
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
 **/
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
 void Buffer(cAudioBuffer *lpBuffer);
 /// This will play a sound through the OpenAL source from the buffer.
 void Play();
 ///Returns true if the sound is playing. Returns false if it isn't.
 bool Playing();
 /// This will stop the currently playing sound and reset the play position to the start.
 void Stop();
 /// This will pause the currently playing sound but retain the current play position.
 void Pause();
 /// This will return the ID of the OpenAL ID.
 ALuint Source();
 /// This will allow you to send signals to this object.
 void Signal(SIGNAL lsSignal);

/// Will Set the AudioObjects Position in Global Co-ordinates
  void Position(float lfX,float lfY,float lfZ);
  /// Will Set the AudioObjects Speed in Global Co-ordinates
  void Speed(float lfX,float lfY,float lfZ);
  /// Will Set whether the AudioObject should loop playing the sound it has buffered
  void Loop(bool lbLoop);
  /// Will return the AudioObjects Position in Global Co-ordinates
  float *Position();
  /// Will return the AudioObjects Speed in Global Co-ordinates
  float *Speed();
  /// Will return whether the AudioObject is set to loop
  bool Loop();
  /// Will set the AudioObjects gain
  void Gain(float lfGain);
  /// Will set the AudioObjects pitch
  void Pitch(float lfPitch);
  /// Will return the AudioObjects gain
  float Gain();
  /// Will return the AudioObjects pitch
  float Pitch();

};



#endif
