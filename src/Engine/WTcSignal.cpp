#include "../WTBamboo.h"

cSignal::cSignal()
{
 mbAwake=true;
 mbAlive=true;
}

void cSignal::Signal(SIGNAL liFlags)
{

	if(liFlags&WT_SIGNAL_VALUE_WAKE && !mbAwake) {mbAwake=true; OnWake();}
	if(liFlags&WT_SIGNAL_VALUE_SLEEP && mbAwake) {mbAwake=false; OnSleep();}
	if(liFlags&WT_SIGNAL_VALUE_KILL && mbAlive) {mbAlive=false; mbAwake=false; Stop();}
}


bool cSignal::Awake(){return mbAwake;};
bool cSignal::Asleep(){return !mbAwake;};
bool cSignal::Alive(){return mbAlive;};
bool cSignal::Dead(){return !mbAlive;};

