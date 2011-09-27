#include "../../WTDivWin.h"

using namespace std;

cWav::cWav(char *lpPath)
{
 printf("Start\n");
 char liCur;
 unsigned char liWave=0;
 unsigned char liData=0;
 const char lsFmt[]="fmt ";
 const char lsData[]="data";
 
 ifstream FileIn;
 ios::pos_type lcPosition;
 FileIn.open(lpPath,ios::in | ios::binary);
 mpData=0;
 miBlockSize=0;
 while(FileIn)
 {
	 
  FileIn.get(liCur);

  if(liCur==lsFmt[liWave]) ++liWave;
  else liWave=0;
  
  if(liCur==lsData[liData])++liData;
  else liData=0;
  

  if(liWave==4)
  {
   FileIn.read((int8*)&miBlockSize,4);
   FileIn.read((int8*)&miCompression,2);
   FileIn.read((int8*)&miChannels,2);
   FileIn.read((int8*)&miSampleRate,4);
   FileIn.read((int8*)&miByteRate,4);
   FileIn.read((int8*)&miBlockAlign,2);
   FileIn.read((int8*)&miBitsPerSample,2);
   mpExtra=new uint8[miBlockSize-16];
   FileIn.read((int8*)mpExtra,miBlockSize-16);
  }
  if(liData==4)
  {
   FileIn.read((int8*)&miDataSize,4);
   mpData=new int8[miDataSize];
   FileIn.read(mpData,miDataSize);
  }
  
  if(mpData && miBlockSize)
  {
	  printf("Start\n");
   if(miChannels==1) miFormat=0x1100;
    if(miChannels==2) miFormat=0x1102;
    if(miBitsPerSample==16) ++miFormat;
    alGenBuffers(1,&miBuffer);
    alBufferData(miBuffer,miFormat,mpData,miDataSize,miSampleRate);
    delete []mpData;
    mpData=0;
    FileIn.close();
    return;
  }
  
 }
FileIn.close();
exit(WT_AUDIO_FILE_LOAD_ERROR);
}

cWav::~cWav()
{
 
 alDeleteBuffers(1,&miBuffer);
 if(mpData) delete []mpData;
 if(mpExtra) delete []mpExtra;
}
