#ifndef __WTCKEYSTORE_H__
#define __WTCKEYSTORE_H__


/// This class stores all the input data for a single keyboard.
class cKeyStore
{
public:
 /// This is the array of keystates.
 bool key[2][256];
 /// This will return a specific key state, using the relevant key code.

cKeyStore();

 bool operator[](uint16 liKey);
void UpdateKeyboard();
bool GetKey(uint16 liKey);
 bool *SetArray(uint16 liKey);
void SetKeyState(bool lbState,uint16 liKey);

};

#endif
