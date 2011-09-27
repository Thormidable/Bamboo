#include "../../WTDivWin.h"

#if WT_OS_TYPE==OS_LINUX
cKeyStore::cKeyStore()
{
 uint32 liCount;
 uint32 liBit;
for(liBit=0;liBit<2;++liBit)
{
 for(liCount=0;liCount<0xFF;++liCount)
 {
  key[liBit][liCount]=false;
 }
}
}
#endif

#if WT_OS_TYPE==OS_WIN32
cKeyStore::cKeyStore()
{
 uint32 liCount;
 for(liCount=0;liCount<0xFF;++liCount)
 {
  key[liCount]=false;
 }
}
#endif

