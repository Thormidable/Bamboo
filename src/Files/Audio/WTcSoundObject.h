#ifndef __WTCSOUNDOBJECT_H__
#define __WTCSOUNDOBJECT_H__

/**
 \brief Inherits from cAudioBuffer. Stores cAudioBuffer object loaded from a file.
 This is an accessor for accessing Buffered audio data from a file.
 Pass a pointer to this class to a cAudioObject to have the cAudioObject Play it. see _GET_AUDIO_FILE(Reference).
*/

class cSoundObject : public cAudioBuffer, public cFile
{
    cAudioData *mpSoundData;
public:
    cSoundObject();
    ~cSoundObject();

    void LoadIMF(ifstream &FileStream);

};

#endif // WTCSOUNDOBJECT_H
