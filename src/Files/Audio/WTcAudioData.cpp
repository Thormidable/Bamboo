
#include "../../WTBamboo.h"

cAudioData::cAudioData()
{
    miFormat=miBlockSize=miSampleRate=miByteRate=miBlockAlign=miDataSize=0;
    miCompression=miChannels=miBitsPerSample=0;
    mpExtra=0;
    mpData=0;
}

cAudioData::~cAudioData()
{
    delete []mpData; mpData=0;
    delete []mpExtra; mpExtra=0;
}

uint32 cAudioData::FileSize()
{
    uint32 liSize=sizeof(uint32)*6+sizeof(uint16)*3+miDataSize*sizeof(int8);
    if(mpExtra) liSize+=(miBlockSize-16)*sizeof(uint8);
    return liSize;

}


void cAudioData::LoadIMFSoundData(ifstream &FileStream)
{
    FileStream.read((int8 *)&miFormat,sizeof(uint32));
    FileStream.read((int8 *)&miBlockSize,sizeof(uint32));
    FileStream.read((int8 *)&miSampleRate,sizeof(uint32));
    FileStream.read((int8 *)&miByteRate,sizeof(uint32));
    FileStream.read((int8 *)&miBlockAlign,sizeof(uint32));
    FileStream.read((int8 *)&miDataSize,sizeof(uint32));

    FileStream.read((int8 *)&miCompression,sizeof(uint16));
    FileStream.read((int8 *)&miChannels,sizeof(uint16));
    FileStream.read((int8 *)&miBitsPerSample,sizeof(uint16));

    mpData=new int8[miDataSize];
    FileStream.read((int8 *)mpData,sizeof(int8)*miDataSize);

    if(miBlockSize>16)
    {
        mpExtra=new uint8[miBlockSize-16];
        FileStream.read((int8 *)mpExtra,sizeof(uint8)*(miBlockSize-16));
    }
    else mpExtra=0;

}



