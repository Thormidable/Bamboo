
#include "../../WTBamboo.h"

bool cKeyHash::mbCreated=false;

char cKeyHash::mpUpperCaseCharacters[256];
char cKeyHash::mpLowerCaseCharacters[256];

uint8 cKeyPressed::mpKeys[32];
uint8 cKeyPressed::miKeys=0;
char cKeyHash::GetKeyCharacter(uint8 liKey)
{
	printf("liKey : %u\n",liKey);
	#if WT_OS_TYPE==OS_LINUX
        if(KEY_SHIFT || _KEY(KEY_CODE_RIGHT_SHIFT)) return mpUpperCaseCharacters[liKey];
        return mpLowerCaseCharacters[liKey];
	#endif
	#if WT_OS_TYPE==OS_WIN32
        if(KEY_SHIFT) return mpUpperCaseCharacters[liKey];
        return mpLowerCaseCharacters[liKey];
	#endif
}

void cKeyHash::Init()
{
	printf("Init cKeyHash\n");
memset(mpUpperCaseCharacters,0,256);
memset(mpLowerCaseCharacters,0,256);

 mbCreated=true;

 mpUpperCaseCharacters[KEY_CODE_a]='a';
 mpUpperCaseCharacters[KEY_CODE_b]='b';
 mpUpperCaseCharacters[KEY_CODE_c]='c';
 mpUpperCaseCharacters[KEY_CODE_d]='d';
 mpUpperCaseCharacters[KEY_CODE_e]='e';
 mpUpperCaseCharacters[KEY_CODE_f]='f';
 mpUpperCaseCharacters[KEY_CODE_g]='g';
 mpUpperCaseCharacters[KEY_CODE_h]='h';
 mpUpperCaseCharacters[KEY_CODE_i]='i';
 mpUpperCaseCharacters[KEY_CODE_j]='j';
 mpUpperCaseCharacters[KEY_CODE_k]='k';
 mpUpperCaseCharacters[KEY_CODE_l]='l';
 mpUpperCaseCharacters[KEY_CODE_m]='m';
 mpUpperCaseCharacters[KEY_CODE_n]='n';
 mpUpperCaseCharacters[KEY_CODE_o]='o';
 mpUpperCaseCharacters[KEY_CODE_p]='p';
 mpUpperCaseCharacters[KEY_CODE_q]='q';
 mpUpperCaseCharacters[KEY_CODE_r]='r';
 mpUpperCaseCharacters[KEY_CODE_s]='s';
 mpUpperCaseCharacters[KEY_CODE_t]='t';
 mpUpperCaseCharacters[KEY_CODE_u]='u';
 mpUpperCaseCharacters[KEY_CODE_v]='v';
 mpUpperCaseCharacters[KEY_CODE_w]='w';
 mpUpperCaseCharacters[KEY_CODE_x]='x';
 mpUpperCaseCharacters[KEY_CODE_y]='y';
 mpUpperCaseCharacters[KEY_CODE_z]='z';

 mpUpperCaseCharacters[KEY_CODE_A]='A';
 mpUpperCaseCharacters[KEY_CODE_B]='B';
 mpUpperCaseCharacters[KEY_CODE_C]='C';
 mpUpperCaseCharacters[KEY_CODE_D]='D';
 mpUpperCaseCharacters[KEY_CODE_E]='E';
 mpUpperCaseCharacters[KEY_CODE_F]='F';
 mpUpperCaseCharacters[KEY_CODE_G]='G';
 mpUpperCaseCharacters[KEY_CODE_H]='H';
 mpUpperCaseCharacters[KEY_CODE_I]='I';
 mpUpperCaseCharacters[KEY_CODE_J]='J';
 mpUpperCaseCharacters[KEY_CODE_K]='K';
 mpUpperCaseCharacters[KEY_CODE_L]='L';
 mpUpperCaseCharacters[KEY_CODE_M]='M';
 mpUpperCaseCharacters[KEY_CODE_N]='N';
 mpUpperCaseCharacters[KEY_CODE_O]='O';
 mpUpperCaseCharacters[KEY_CODE_P]='P';
 mpUpperCaseCharacters[KEY_CODE_Q]='Q';
 mpUpperCaseCharacters[KEY_CODE_R]='R';
 mpUpperCaseCharacters[KEY_CODE_S]='S';
 mpUpperCaseCharacters[KEY_CODE_T]='T';
 mpUpperCaseCharacters[KEY_CODE_U]='U';
 mpUpperCaseCharacters[KEY_CODE_V]='V';
 mpUpperCaseCharacters[KEY_CODE_W]='W';
 mpUpperCaseCharacters[KEY_CODE_X]='X';
 mpUpperCaseCharacters[KEY_CODE_Y]='Y';
 mpUpperCaseCharacters[KEY_CODE_Z]='Z';

 mpUpperCaseCharacters[KEY_CODE_0]=')';
 mpUpperCaseCharacters[KEY_CODE_1]='!';
 mpUpperCaseCharacters[KEY_CODE_2]='"';
 //mpUpperCaseCharacters[KEY_CODE_3]='£';
 mpUpperCaseCharacters[KEY_CODE_4]='$';
 mpUpperCaseCharacters[KEY_CODE_5]='%';
 mpUpperCaseCharacters[KEY_CODE_6]='^';
 mpUpperCaseCharacters[KEY_CODE_7]='&';
 mpUpperCaseCharacters[KEY_CODE_8]='*';
 mpUpperCaseCharacters[KEY_CODE_9]='(';
 mpUpperCaseCharacters[KEY_CODE_NP0]='0';
 mpUpperCaseCharacters[KEY_CODE_NP1]='1';
 mpUpperCaseCharacters[KEY_CODE_NP2]='2';
 mpUpperCaseCharacters[KEY_CODE_NP3]='3';
 mpUpperCaseCharacters[KEY_CODE_NP4]='4';
 mpUpperCaseCharacters[KEY_CODE_NP5]='5';
 mpUpperCaseCharacters[KEY_CODE_NP6]='6';
 mpUpperCaseCharacters[KEY_CODE_NP7]='7';
 mpUpperCaseCharacters[KEY_CODE_NP8]='8';
 mpUpperCaseCharacters[KEY_CODE_NP9]='9';
// mpUpperCaseCharacters[KEY_CODE_PERIOD]='>';
// mpUpperCaseCharacters[KEY_CODE_DECIMAL]='>';
// mpUpperCaseCharacters[KEY_CODE_EQUALS]='+';
 mpUpperCaseCharacters[KEY_CODE_QUOTE]='@';
 mpUpperCaseCharacters[KEY_CODE_SLASH]='?';
// mpUpperCaseCharacters[KEY_CODE_DASH]='_';
 mpUpperCaseCharacters[KEY_CODE_SBC]='}';
 mpUpperCaseCharacters[KEY_CODE_SBO]='{';
// mpUpperCaseCharacters[KEY_CODE_COMMA]='<';
 mpUpperCaseCharacters[KEY_CODE_SEMICOLON]=':';
 //mpUpperCaseCharacters[KEY_CODE_TILDE]='~';
 mpUpperCaseCharacters[KEY_CODE_NP_DECIMAL]='.';
 mpUpperCaseCharacters[KEY_CODE_NP_DIVIDE]='/';
 mpUpperCaseCharacters[KEY_CODE_NP_MULTIPLY]='*';
 mpUpperCaseCharacters[KEY_CODE_NP_PERIOD]='.';
 mpUpperCaseCharacters[KEY_CODE_NP_PLUS]='+';
 //mpUpperCaseCharacters[KEY_CODE_NP_SEPARATOR]='-';
 mpUpperCaseCharacters[KEY_CODE_NP_DECIMAL]='.';
 mpUpperCaseCharacters[KEY_CODE_NP_DIVIDE]='/';
 mpUpperCaseCharacters[KEY_CODE_NP_MULTIPLY]='*';
 mpUpperCaseCharacters[KEY_CODE_NP_PERIOD]='.';
 mpUpperCaseCharacters[KEY_CODE_NP_PLUS]='+';
 mpUpperCaseCharacters[KEY_CODE_SPACE]=' ';

 mpLowerCaseCharacters[KEY_CODE_A]='A';
 mpLowerCaseCharacters[KEY_CODE_B]='B';
 mpLowerCaseCharacters[KEY_CODE_C]='C';
 mpLowerCaseCharacters[KEY_CODE_D]='D';
 mpLowerCaseCharacters[KEY_CODE_E]='E';
 mpLowerCaseCharacters[KEY_CODE_F]='F';
 mpLowerCaseCharacters[KEY_CODE_G]='G';
 mpLowerCaseCharacters[KEY_CODE_H]='H';
 mpLowerCaseCharacters[KEY_CODE_I]='I';
 mpLowerCaseCharacters[KEY_CODE_J]='J';
 mpLowerCaseCharacters[KEY_CODE_K]='K';
 mpLowerCaseCharacters[KEY_CODE_L]='L';
 mpLowerCaseCharacters[KEY_CODE_M]='M';
 mpLowerCaseCharacters[KEY_CODE_N]='N';
 mpLowerCaseCharacters[KEY_CODE_O]='O';
 mpLowerCaseCharacters[KEY_CODE_P]='P';
 mpLowerCaseCharacters[KEY_CODE_Q]='Q';
 mpLowerCaseCharacters[KEY_CODE_R]='R';
 mpLowerCaseCharacters[KEY_CODE_S]='S';
 mpLowerCaseCharacters[KEY_CODE_T]='T';
 mpLowerCaseCharacters[KEY_CODE_U]='U';
 mpLowerCaseCharacters[KEY_CODE_V]='V';
 mpLowerCaseCharacters[KEY_CODE_W]='W';
 mpLowerCaseCharacters[KEY_CODE_X]='X';
 mpLowerCaseCharacters[KEY_CODE_Y]='Y';
 mpLowerCaseCharacters[KEY_CODE_Z]='Z';

 mpLowerCaseCharacters[KEY_CODE_a]='a';
 mpLowerCaseCharacters[KEY_CODE_b]='b';
 mpLowerCaseCharacters[KEY_CODE_c]='c';
 mpLowerCaseCharacters[KEY_CODE_d]='d';
 mpLowerCaseCharacters[KEY_CODE_e]='e';
 mpLowerCaseCharacters[KEY_CODE_f]='f';
 mpLowerCaseCharacters[KEY_CODE_g]='g';
 mpLowerCaseCharacters[KEY_CODE_h]='h';
 mpLowerCaseCharacters[KEY_CODE_i]='i';
 mpLowerCaseCharacters[KEY_CODE_j]='j';
 mpLowerCaseCharacters[KEY_CODE_k]='k';
 mpLowerCaseCharacters[KEY_CODE_l]='l';
 mpLowerCaseCharacters[KEY_CODE_m]='m';
 mpLowerCaseCharacters[KEY_CODE_n]='n';
 mpLowerCaseCharacters[KEY_CODE_o]='o';
 mpLowerCaseCharacters[KEY_CODE_p]='p';
 mpLowerCaseCharacters[KEY_CODE_q]='q';
 mpLowerCaseCharacters[KEY_CODE_r]='r';
 mpLowerCaseCharacters[KEY_CODE_s]='s';
 mpLowerCaseCharacters[KEY_CODE_t]='t';
 mpLowerCaseCharacters[KEY_CODE_u]='u';
 mpLowerCaseCharacters[KEY_CODE_v]='v';
 mpLowerCaseCharacters[KEY_CODE_w]='w';
 mpLowerCaseCharacters[KEY_CODE_x]='x';
 mpLowerCaseCharacters[KEY_CODE_y]='y';
 mpLowerCaseCharacters[KEY_CODE_z]='z';

 mpLowerCaseCharacters[KEY_CODE_0]='0';
 mpLowerCaseCharacters[KEY_CODE_1]='1';
 mpLowerCaseCharacters[KEY_CODE_2]='2';
 mpLowerCaseCharacters[KEY_CODE_3]='3';
 mpLowerCaseCharacters[KEY_CODE_4]='4';
 mpLowerCaseCharacters[KEY_CODE_5]='5';
 mpLowerCaseCharacters[KEY_CODE_6]='6';
 mpLowerCaseCharacters[KEY_CODE_7]='7';
 mpLowerCaseCharacters[KEY_CODE_8]='8';
 mpLowerCaseCharacters[KEY_CODE_9]='9';
 mpLowerCaseCharacters[KEY_CODE_NP0]='0';
 mpLowerCaseCharacters[KEY_CODE_NP1]='1';
 mpLowerCaseCharacters[KEY_CODE_NP2]='2';
 mpLowerCaseCharacters[KEY_CODE_NP3]='3';
 mpLowerCaseCharacters[KEY_CODE_NP4]='4';
 mpLowerCaseCharacters[KEY_CODE_NP5]='5';
 mpLowerCaseCharacters[KEY_CODE_NP6]='6';
 mpLowerCaseCharacters[KEY_CODE_NP7]='7';
 mpLowerCaseCharacters[KEY_CODE_NP8]='8';
 mpLowerCaseCharacters[KEY_CODE_NP9]='9';
// mpLowerCaseCharacters[KEY_CODE_PERIOD]='.';
// mpLowerCaseCharacters[KEY_CODE_DECIMAL]='.';
// mpLowerCaseCharacters[KEY_CODE_EQUALS]='=';
 mpLowerCaseCharacters[KEY_CODE_QUOTE]='"';
 mpLowerCaseCharacters[KEY_CODE_SLASH]='/';
// mpLowerCaseCharacters[KEY_CODE_DASH]='_';
 mpLowerCaseCharacters[KEY_CODE_SBC]=']';
 mpLowerCaseCharacters[KEY_CODE_SBO]='[';
// mpLowerCaseCharacters[KEY_CODE_COMMA]=',';
 mpLowerCaseCharacters[KEY_CODE_SEMICOLON]=';';
 //mpLowerCaseCharacters[KEY_CODE_TILDE]='#';
 mpLowerCaseCharacters[KEY_CODE_NP_DECIMAL]='.';
 mpLowerCaseCharacters[KEY_CODE_NP_DIVIDE]='/';
 mpLowerCaseCharacters[KEY_CODE_NP_MULTIPLY]='*';
 mpLowerCaseCharacters[KEY_CODE_NP_PERIOD]='.';
 mpLowerCaseCharacters[KEY_CODE_NP_PLUS]='+';
 //mpLowerCaseCharacters[KEY_CODE_NP_SEPARATOR]='-';
 mpLowerCaseCharacters[KEY_CODE_NP_DECIMAL]='.';
 mpLowerCaseCharacters[KEY_CODE_NP_DIVIDE]='/';
 mpLowerCaseCharacters[KEY_CODE_NP_MULTIPLY]='*';
 mpLowerCaseCharacters[KEY_CODE_NP_PERIOD]='.';
 mpLowerCaseCharacters[KEY_CODE_NP_PLUS]='+';
 mpLowerCaseCharacters[KEY_CODE_SPACE]=' ';
 mpLowerCaseCharacters[KEY_CODE_BACKSPACE]=8;

};

cKeyPressed::cKeyPressed()
{
 	miKeys=0;
	if(!cKeyHash::mbCreated) cKeyHash::Init();
};

char cKeyPressed::PressedCharacter(uint8 liCount)
{
 return cKeyHash::GetKeyCharacter(mpKeys[liCount]);
};

void cKeyPressed::Update(bool *lbOld,bool *lbNew)
{
 miKeys=0;
 for(uint8 liCount=0;liCount<255;++liCount)
 {
	if(!lbOld[liCount] && lbNew[liCount]) mpKeys[miKeys++]=liCount;
 }
 if(!lbOld[255] && lbNew[255]) mpKeys[miKeys++]=255;
};

	cKeyPressed::~cKeyPressed()
	{
		miKeys=0;
	};

	uint8 cKeyPressed::PressedKeys(){return miKeys;};
	uint8 cKeyPressed::PressedKey(uint8 liCount){return mpKeys[liCount];};


cKeyStore::cKeyStore()
{
 mpKeyPressed=0;
 memset(key,0,512);
}


 bool cKeyStore::operator[](uint8 liKey){return key[1][liKey];};
void cKeyStore::UpdateKeyboard()
{
	if(mpKeyPressed) mpKeyPressed->Update(key[1],key[0]);
    memcpy(&(key[1][0]),key,256);
}

bool cKeyStore::GetKey(uint8 liKey){return key[1][liKey];};
 bool *cKeyStore::SetArray(uint8 liKey){return &key[0][liKey];};

 void cKeyStore::SetKeyState(bool lbState,uint8 liKey)
{
     key[0][liKey]=lbState;
};

void cKeyStore::KeyPressTracking(bool lbState)
{
 if(lbState)
 {
	if(!mpKeyPressed) mpKeyPressed=new cKeyPressed;
 }
 else
 {
	delete mpKeyPressed;
	mpKeyPressed=0;
 }
};


cKeyStore::~cKeyStore()
{
 delete mpKeyPressed;
};




