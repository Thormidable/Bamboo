#ifndef WTCAUDIODATA_H
#define WTCAUDIODATA_H

class cAudioData
{
public:
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

    cAudioData();
    ~cAudioData();

    uint32 FileSize();

    void LoadIMFSoundData(ifstream &FileStream);

};

#endif // WTCAUDIODATA_H
