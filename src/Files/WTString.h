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
void LineCopy(char*lcTo,char *lcFrom,char lcEnd);
void LineCopy(char*lcTo,char *lcFrom,const char *lcEnd);
/// This will return the number of characters from the start of the string pointed to by lcPath until the character lcFind.
uint32 CharCount(char *lcPath,char lcFind);

/// This will find the string pointed to by lcFind within the null terminated string pointed to by lcPath and return a pointer to the last character in lcFind.
char *FindOn(char* lcPath,char *lcFind);
/// This will find the character lcFind within the null terminated string pointed to by lcPath and return a pointer to the character lcFind.
char *FindOn(char *lcPath,char lcFind);
/// This will find the string pointed to by lcFind within the (null or \r or \n terminated) string pointed to by lcPath and return a pointer to the last character in lcFind.
char *FindOnString(char* lcPath,char *lcFind);
/// This will find the character lcFind within the (null or \r or \n terminated) string pointed to by lcPath and return a pointer to the character lcFind.
char *FindOnString(char *lcPath,char lcFind);
/// This will return the length of the string lpString.
uint16 StrLength(char *lpString);
///One of these MUST be zero terminated. The other should be either zero terminated or terminated with a character in lcEnds. lcEnds should be zero terminated.
bool CompareVariables(char *lcFirst,const char *lcSecond,const char *lcEnds);
///Will return the length of the String until 0 or one of the lcEnds String is found.
uint32 StringLength(char *lcString,char *lcEnds);
#endif
