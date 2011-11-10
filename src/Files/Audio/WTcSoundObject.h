#ifndef __WTCSOUNDOBJECT_H__
#define __WTCSOUNDOBJECT_H__

class cSoundObject : public cAudioBuffer, public cFile
{
    cAudioData *mpSoundData;
public:
    cSoundObject();
    ~cSoundObject();

    void LoadIMF(ifstream &FileStream);

};

#endif // WTCSOUNDOBJECT_H
