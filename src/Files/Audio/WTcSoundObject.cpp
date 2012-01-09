#include "../../WTBamboo.h"


cSoundObject::~cSoundObject()
{
    delete mpSoundData;
    mpSoundData=0;
}

cSoundObject::cSoundObject()
{
    mpSoundData=new cAudioData;
}

void cSoundObject::LoadIMF(ifstream &FileStream)
{
    uint32 liBuff;
 FileStream.read((int8 *) &liBuff,sizeof(uint32));

 FileStream.read((int8 *) &liBuff,sizeof(uint32));
 FileStream.read((int8 *) mpFileName,sizeof(int8)*liBuff);


 mpSoundData->LoadIMFSoundData(FileStream);

  alBufferData(miBuffer,mpSoundData->miFormat,mpSoundData->mpData,mpSoundData->miDataSize,mpSoundData->miSampleRate);
}

