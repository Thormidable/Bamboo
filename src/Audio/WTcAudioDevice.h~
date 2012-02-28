#ifndef __WTCAUDIODEVICE_H__
#define __WTCAUDIODEVICE_H__
/**
 * \brief This class will initialise the sound card.
 * This class will initialise an audio device so sounds can be played on the system.
 */
class cAudioDevice
{
 // A pointer to the current OpenAL device.
 ALCdevice *mpDevice;
 // A pointer to the current OpenAL Context.
 ALCcontext *mpContext;
 
 static cAudioDevice *mpInstance;
public:
	/// Constructor will start and initialise an OpenAL system.
	cAudioDevice();
	///This Function will return a pointer to the current OpenAL Audio Device.
 static cAudioDevice *Instance();
 // Destructor will stop and close the current OpenAL device.
 ~cAudioDevice();
};


#endif
