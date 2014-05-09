#include "stdafx.h"
/*=============================*\
            EXCALIBUR

			exSync.cpp

Author:
Alice Blunt

Date:
20-09-07

Version:
1.0.0

Description:
Engine synchronisation source.
This is horribly platform
dependent!

Note - I used to be using
CPU TSC but that gets unstable
on pretty much any modern CPU,
so now I'm having to use OS
specific code ;_;

Copyright (c) 2007 Alice Blunt

\*=============================*/

/*
// Windows includes
#include <windows.h>
// Linux includes
#include <unistd.h>
#include <sys/time.h>
*/


#include "../WTBamboo.h"

cSync *cSync::mpInstance=0;

void cSync::SleepWrap(uint32 liMS)
{
#if WT_OS_TYPE==OS_LINUX
	usleep(1000*liMS);
#endif
#if WT_OS_TYPE==OS_WIN32
	Sleep(liMS);
#endif
}


// Synchroniser class constructor
cSync::cSync():
#if WT_OS_TYPE==OS_LINUX
	mfLastf(0.0f),mfCurrf(0.0f),mpTimeVal(0x0),
#endif
	miLastTime(0),miCurrTime(0),mfTimeMod(0.0f),mfTimeAcc(0.0f),mfCPS(0.0f)
{
#if WT_OS_TYPE==OS_LINUX
	mpTimeVal=new timeval;
#endif
	Tick();
	Tick();
	mfTimeMod=0.0f;
	mfTimeAcc=0.0f;
	mfCPS=0.0f;
}

cSync *cSync::Instance()
{
    if(!mpInstance) mpInstance=new cSync;
    return mpInstance;
}

// Synchroniser class destructor
cSync::~cSync()
{
#if WT_OS_TYPE==OS_LINUX
	delete (timeval*)mpTimeVal;
#endif
}


// Tick the synchroniser
// (Try to do this only once per cycle)
void cSync::Tick()
{
#if WT_OS_TYPE==OS_LINUX
	static timeval* lpTimeVal=static_cast<timeval*>(mpTimeVal);
	gettimeofday(lpTimeVal,NULL);
	miCurrTime=lpTimeVal->tv_sec;
	mfCurrf=lpTimeVal->tv_usec*0.000001f;
	mfTimeMod=(mfCurrf-mfLastf)+((float)(miCurrTime-miLastTime));
	miLastTime=miCurrTime;
	mfLastf=mfCurrf;
#endif
#if WT_OS_TYPE==OS_WIN32
	miCurrTime=(int)(timeGetTime()&UINT_MAX);
	mfTimeMod=(miCurrTime-miLastTime)*0.001f;
	miLastTime=miCurrTime;
#endif
	// Increment time accumulator and get cycles per second
	mfTimeAcc+=mfTimeMod;
	mfCPS=1.0f/mfTimeMod;
}

void cSync::EnforceFrameRate()
{
    Tick();
    int32 liSleepTime=(_TIME_PER_FRAME-GetTimeMod())*OS_TIME_SCALING;
	if(liSleepTime>0)
	{
        //printf("Time to Process Frame : %f s\n",gpTimer->GetTimeMod());
        //	printf("Free Time this frame : %f ms\n",(_TIME_PER_FRAME-gpTimer->GetTimeMod())*OS_TIME_SCALING);
        SleepWrap(liSleepTime);
	}
}

uint32 cSync::GetCurrentTime()
{
#if WT_OS_TYPE==OS_LINUX
	static timeval* lpTimeVal=static_cast<timeval*>(mpTimeVal);
	gettimeofday(lpTimeVal,NULL);
	return lpTimeVal->tv_usec*0.001f;
#endif
#if WT_OS_TYPE==OS_WIN32
	return (int)(timeGetTime()&UINT_MAX)*0.001f;
#endif
}

uint32 cSync::GetCurrentUs()
{
#if WT_OS_TYPE==OS_LINUX
	static timeval* lpTimeVal=static_cast<timeval*>(mpTimeVal);
	gettimeofday(lpTimeVal,NULL);
	return lpTimeVal->tv_usec;
#endif
#if WT_OS_TYPE==OS_WIN32
	return (int)(timeGetTime()&UINT_MAX);
#endif
}
