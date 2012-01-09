#include "../../WTBamboo.h"


cKeyStore::cKeyStore()
{

 memset(key,0,512);
}


 bool cKeyStore::operator[](uint16 liKey){return key[1][liKey];};
void cKeyStore::UpdateKeyboard()
{
    memcpy(&(key[1][0]),key,256);
}

bool cKeyStore::GetKey(uint16 liKey){return key[1][liKey];};
 bool *cKeyStore::SetArray(uint16 liKey){return &key[0][liKey];};

 void cKeyStore::SetKeyState(bool lbState,uint16 liKey)
{
     key[0][liKey]=lbState;
};

