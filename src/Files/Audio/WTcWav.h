#ifndef __WTCWAV_H__
#define __WTCWAV_H__
/** This will load and store a wav file into memory. It is itself an OpenAL buffer, so does not need to be added.
 * It can be played by linking to an cAudioObject and calling Play()
 */
class cWav : public cAudioBuffer, public cFile
{
 // This will store the size of a data block in the wav file.
 uint32 miBlockSize;
 // This will store the frequency of the audio samples.
 uint32 miSampleRate;
 // This will store the byte rate
 uint32 miByteRate;
 // This will store the block alignment of the wav file.
 uint32 miBlockAlign;
 // This will store the size of the data stored in the wav file.
 uint32 miDataSize;
 // This will store the compression of the data.
 uint16 miCompression;
 // This will store the channels used to record the data.
 uint16 miChannels;
 // This will store the size of each audio sample.
 uint16 miBitsPerSample;
 // This will store the format of the audio data.
 uint32 miFormat;
 // This is a pointer to extra data in the wav file.
 uint8 *mpExtra;
 // This is a pointer to the sound data in the wav file.
 int8 *mpData;
public:
 /**
 * \brief This constructor will load the wav file from the file lpPath.
 * \param lpPath This is the file path of the wav file.
 * The file lpPath will be loaded into an OpenAL buffer.
 */
 cWav(char *lpPath);
 /// This will free the wav file from memory and destroy the OpenAL buffer.
 ~cWav();
};

#endif
