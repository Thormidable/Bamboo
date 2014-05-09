#include "stdafx.h"
#include "../WTBamboo.h"

char *Find(char* lcPath,char *lcFind)
{
 short liLetter=0;
 while (lcPath[0])
 {
  if (lcPath[0]==lcFind[liLetter])
  {++liLetter;
   if(!lcFind[liLetter]) return &lcPath[1];
  }
  else {liLetter=0;}
  ++lcPath;
 }
 return 0;
}

char *Find(char *lcPath,char lcFind)
{
 while(lcPath[0])
 {
  if (lcPath[0]==lcFind) return &lcPath[1];
  ++lcPath;
 }
 return 0;
}

uint32 CharCount(char *lcPath,char lcFind)
{
 uint32 liCount=0;
 while(lcPath && lcPath[0]!=0x0A)
 {
  if(lcPath[0]==lcFind) ++liCount;
  ++lcPath;
 }
 return liCount;
}

bool Match(char *lcPath,char *lcFind)
{
 uint32 liPlace=0;

 while(lcFind[liPlace] && lcPath[liPlace]==lcFind[liPlace])
 {
  ++liPlace;
 }
 if(lcFind[liPlace]) return 0;
 else return 1;
}

void LineCopy(char*lcTo,char *lcFrom,char lcEnd)
{
 while(lcFrom[0] && lcFrom[0]!=lcEnd)
 {
  lcTo[0]=lcFrom[0];
  ++lcTo; ++lcFrom;
 }
 lcTo[0]=0;
}

void LineCopy(char*lcTo,char *lcFrom,const char *lcEnd)
{
 bool lbContinue=true;
 uint8 liStep=0;
 while(lcEnd[liStep]){if(lcFrom[0]==lcEnd[liStep] || !lcFrom) lbContinue=false; ++liStep;}
 while(lbContinue)
 {
  lcTo[0]=lcFrom[0];
  ++lcTo; ++lcFrom;
  uint8 liStep=0;
 while(lcEnd[liStep]){if(lcFrom[0]==lcEnd[liStep] || !lcFrom) lbContinue=false; ++liStep;}
 }
 lcTo[0]=0;
}

bool CompareVariables(char *lcFirst,const char *lcSecond,const char *lcEnds)
{
 while(*lcFirst==*lcSecond && *lcFirst && *lcSecond)
 {
     ++lcFirst;
     ++lcSecond;
 }
 bool lbFirst,lbSecond;
 lbFirst=*lcFirst;
 lbSecond=*lcSecond;
 while((lbFirst || lbSecond) && *lcEnds)
 {
     if(*lcFirst==*lcEnds) lbFirst=false;
     if(*lcSecond==*lcEnds) lbSecond=false;
	 ++lcEnds;
 }
 if(lbFirst || lbSecond) return 0;
 else return true;
}

void LineCopy(char*lcTo,char *lcFrom)
{
 while(lcFrom[0]!=0x0A && lcFrom[0])
 {
  lcTo[0]=lcFrom[0];
  ++lcTo; ++lcFrom;
 }
 lcTo[0]=0;
}

char *FindOn(char* lcPath,char *lcFind)
{short liLetter=0;
 while (lcPath[0])
 {if (lcPath[0]==lcFind[liLetter])
  {++liLetter;
   if(!lcFind[liLetter]) return &lcPath[0];}
  else {liLetter=0;}
  ++lcPath;}
 return 0;
}

char *FindOn(char *lcPath,char lcFind)
{while(lcPath[0])
 {if (lcPath[0]==lcFind) return &lcPath[0];
  ++lcPath;
 }
 return 0;
}

uint16 StrLength(char *lpString)
{
 uint16 liCount=0;
 while(lpString[liCount]){++liCount;}
 return liCount;
}

uint32 StringLength(char *lcString,char *lcEnds)
{
 char* lcTemp=lcString;
 while(*lcTemp)
 {
	char *lcTempEnd=lcEnds;
 	while(*lcTempEnd)
 	{
  		if(*lcTemp==*lcTempEnd) return (uint16)(lcTemp-lcString);

		++lcTempEnd;
 	}
	++lcTemp;
 }
 return (uint16)(lcTemp-lcString);
}


char *FindOnString(char* lcPath,char *lcFind)
{short liLetter=0;
 while (lcPath[0] && lcPath[0]!=0x0A && lcPath[0]!=0x0D)
 {if (lcPath[0]==lcFind[liLetter])
  {++liLetter;
   if(!lcFind[liLetter]) return &lcPath[0];}
  else {liLetter=0;}
  ++lcPath;}
 return 0;
}

char *FindOnString(char *lcPath,char lcFind)
{while(lcPath[0] && lcPath[0]!=0x0A && lcPath[0]!=0x0D)
 {if (lcPath[0]==lcFind) return &lcPath[0];
  ++lcPath;
 }
 return 0;
}
