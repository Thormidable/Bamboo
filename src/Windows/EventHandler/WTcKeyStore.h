#ifndef __WTCKEYSTORE_H__
#define __WTCKEYSTORE_H__

#if WT_OS_TYPE==OS_LINUX
/// This class stores all the input data for a single keyboard.
class cKeyStore
{
public:
 /// This is the array of keystates.
 bool key[2][256];
 /// This will return a specific key state, using the relevant key code.
 bool operator[](uint16 liKey);
 /// This will create and initialise the keystore object.

 bool Array(uint16 liBit,uint16 liKey){return key[liBit][liKey];};
 bool *SetArray(uint16 liBit,uint16 liKey){return &key[liBit][liKey];};
 cKeyStore();

};
#endif

 #if WT_OS_TYPE==OS_WIN32
/// This class stores all the input data for a single keyboard.
class cKeyStore
{
public:
 /// This is the array of keystates.
 bool key[256];
 /// This will return a specific key state, using the relevant key code.
 bool operator[](uint16 liKey){return key[liKey];};
 /// This will create and initialise the keystore object.

 void SetKeyState(bool lbState,uint16 liKey){key[liKey]=lbState;};
 cKeyStore();

  bool WinKey(uint16 liKey){return this->operator[](liKey);};
};


 #endif


#endif
