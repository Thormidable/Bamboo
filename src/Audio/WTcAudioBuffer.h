#ifndef __WTCBUFFER_H__
#define __WTCBUFFER_H__
/**
 * \brief This class will create a buffer space to store sound data.
 * This class will create and initialise an OpenAL buffer. The Buffer stores the sound data and is linked to a cAudioObject to allow it to be played.
 */
class cAudioBuffer
{
protected :
 // Integer ID of the buffer that this object will own.
 ALuint miBuffer;
 public:
	///Constructor to Initialise a Buffer.

        cAudioBuffer();
	// This destructor will destroy the current buffer.
        ~cAudioBuffer();
	/// This will return the ID of the buffer owned by this class.
        ALuint Buffer();
};

#endif
