#ifndef __WTCKEYSTORE_H__
#define __WTCKEYSTORE_H__

class cKeyHash
{
public:
 static bool mbCreated;
 static char mpLowerCaseCharacters[256];
 static char mpUpperCaseCharacters[256];
 static char GetKeyCharacter(uint8 liKey);
 static void Init();
};

/**
 * \brief This class is for tracking actual key presses.
 * Whether Key presses are tracked is controlled by calling cKeyStore::KeyPressTracking() or __KEY->KeyPressTracking().
 * This will return the number of key presses this frame, they can then be pulled from the list of presses using PressedKey(uint8 ).
 * Note that this does not use KEY_CODES instead it is the number of the key press in the frame.
 */
class cKeyPressed
{
	static uint8 mpKeys[32];
	static uint8 miKeys;
public:
	cKeyPressed();
	~cKeyPressed();
	void Update(bool *lbOld,bool *lbNew);
	/// Will return the number of keys which have been pressed in the last frame.
	static uint8 PressedKeys();
	/// Will return the key pressed in position liCount this frame (Range is 0 and less than number of keys pressed).
	static uint8 PressedKey(uint8 liCount);
	/// Will return the character represented by the key press liCount.
	static char PressedCharacter(uint8 liCount);
};

/// This class stores all the input data for a single keyboard.
class cKeyStore
{
public:
 /// This is the array of keystates.
 bool key[2][256];
 cKeyPressed *mpKeyPressed;
 /// This will return a specific key state, using the relevant key code.

cKeyStore();
~cKeyStore();

 bool operator[](uint8 liKey);
void UpdateKeyboard();
bool GetKey(uint8 liKey);
 bool *SetArray(uint8 liKey);
void SetKeyState(bool lbState,uint8 liKey);
void KeyPressTracking(bool lbState);
};

#endif
