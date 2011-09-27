/*=============================*\
            EXCALIBUR

			exSync.hh

Author:
Alice Blunt

Date:
04-10-07

Version:
1.0.1

Description:
Engine synchronisation header

Note - In windows, timing is accurate
is to 1ms (0.001s) (though in
reality, it never manages to hit that
target, you'll probably find your
timing will be accurate to ~2-3ms).
So don't trust profiling of very fast
sections of code, profile several at a
time and calculate the average.
Oh and don't make me use QPC in
windows, it has the same flaws as
TSC on mordern processors, plus a
whole load more. Fun.

In linux, timing is accuate to 1us
(0.000001s). Much more useful.

exSleep is balanced to ~1ms accuracy
on all platforms.

Copyright (c) 2007 Alice Blunt

\*=============================*/


#ifndef __WTCSYNC_H__
#define __WTCSYNC_H__

/// This is the timer class. It allows the user to time events and pause the system.
class cSync
{
private:
	/// This is a pointer to the current cSync instance.
	static cSync *mpInstance;
#if WT_OS_TYPE==OS_LINUX
	/// This is a Linux specific variable. It stores the last ticks time value.

	float mfLastf;
	/// This is a Linux specific variable. It stores the current ticks time value.
	float mfCurrf;

	/// This is Linux specific variable. It stores a pointer to the time value.
	timeval* mpTimeVal;
#endif
	// General timing vars
	/// This is the integer representation of the last ticks time.
	int miLastTime;
	/// This is the integer representation of the current ticks time.
	int miCurrTime;
	// Accessible data (modifier,accumulator,cycles per second)
	/// This is the time in seconds between the last two ticks.
	float mfTimeMod;
	/// This is the total time in seconds accumalated since the timer was started.
	float mfTimeAcc;
	/// This is the current cycles per second
	float mfCPS;
public:
	cSync();
	~cSync();
	
	///This will tick the system and recalculate the current system speed.
	void Tick();

	/// This will will sleep wrap the system by liMS miliseconds
	void SleepWrap(uint32 lMS);
	// Accessors
	/// This will return mfTimeMod.
	inline float GetTimeMod(){ return mfTimeMod;}
	/// This will reutrn mfTimeAcc.
	inline float GetTimeAcc(){ return mfTimeAcc;}
	/// This will return mfCPS.
	inline float GetCPS(){ return mfCPS;}
};


#endif
