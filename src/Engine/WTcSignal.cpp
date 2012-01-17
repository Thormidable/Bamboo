#include "../WTBamboo.h"

cSignal::cSignal()
{
 mbAwake=true;
 mbAlive=true;
}

void cSignal::Signal(SIGNAL liFlags)
{
	/*	miFlags=(miFlags|liFlags);
	 *	miFlags=(miFlags&(~(liFlags>>16)));*/

	if(liFlags&WT_SIGNAL_VALUE_WAKE && !mbAwake) {mbAwake=true; AdditionalWakeFunctionality();}
	if(liFlags&WT_SIGNAL_VALUE_SLEEP && mbAwake) {mbAwake=false; AdditionalSleepFunctionality();}
	if(liFlags&WT_SIGNAL_VALUE_KILL && mbAlive) {mbAlive=false; mbAwake=false; AdditionalKillFunctionality();}
}


bool cSignal::Awake(){return mbAwake;};
bool cSignal::Asleep(){return !mbAwake;};
bool cSignal::Alive(){return mbAlive;};
bool cSignal::Dead(){return !mbAlive;};
/*
 * bool cObjectStates::Awake(){return miFlags&WT_SIGNAL_AWAKE;};
 * bool cObjectStates::Asleep(){return !Awake();};
 * bool cObjectStates::Alive(){return miFlags&WT_SIGNAL_ALIVE;};
 * bool cObjectStates::Dead(){return !Alive();};
 */
