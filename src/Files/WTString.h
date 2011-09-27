#ifndef __WTSTRING_H__
#define __WTSTRING_H__
/// This will find the string pointed to by lcFind within the string pointed to by lcPath and return a pointer to the character after the last character of lcFind.
char *Find(char* lcPath,char *lcFind);
/// This will find the character lcFind within the string pointed to by lcPath and return a pointer to the character after lcFind.
char *Find(char* lcPath,char lcFind);

/// This will return 1 if the two strings pointed to by lcPath and lcFind are identical.
bool Match(char* lcPath,char *lcFind);
/// This will copy the current Line (up to a EOL character - 0x0A or 0x00) from the pointer lcFrom to the pointer lcTo.
void LineCopy(char*lcTo,char *lcFrom);
/// This will return the number of characters from the start of the string pointed to by lcPath until the character lcFind.
uint32 CharCount(char *lcPath,char lcFind);

/// This will find the string pointed to by lcFind within the string pointed to by lcPath and return a pointer to the last character in lcFind.
char *FindOn(char* lcPath,char *lcFind);
/// This will find the character lcFind within the string pointed to by lcPath and return a pointer to the character lcFind.
char *FindOn(char *lcPath,char lcFind);
/// This will return the length of the string lpString.
uint16 StrLength(char *lpString);
#endif
