#ifndef __WTVSIGNAL_H__
#define __WTVSIGNAL_H__


/** \brief Class for handling Signals sent between objects (cProcess, cRenderObject, cCollisionObject).
 * Allows the user to wake, sleep and kill objects. For cProcess (while cParentStack is enabled) also
 * allows signals to be sent to a process that will recursively affect all the children of that process.
 * Possible signals to be passed in are _S_SLEEP,_S_WAKE,_S_KILL,_S_SLEEP_TREE, _S_WAKE_TREE,_S_KILL_TREE
 * User Specified Signals are controlled by the class cUserSignal.
**/
class cSignal
{
protected:
	bool mbAwake;
	bool mbAlive;
public:
	cSignal();
	///This is the function that will handle a system signal. Possible signals to be passed in are _S_SLEEP,_S_WAKE,_S_KILL,_S_SLEEP_TREE, _S_WAKE_TREE,_S_KILL_TREE.
	virtual void Signal(SIGNAL lsSignal);
	///This will return true if the object is Awake.
	bool Awake();
	///This will return true if the object is Asleep.
	bool Asleep();
	///This will return true if the object is Alive.
	bool Alive();
	///This will return true if the object is Dead.
	bool Dead();
	///Virtual Functions to allow additional commands to be processed when a kill signal is received by an object. This can be user modified for classes inheriting cProcess.
	virtual void Stop(){};
	///Virtual Functions to allow additional commands to be processed when a sleep signal is received by an object. This can be user modified for classes inheriting cProcess.
	virtual void OnSleep(){};
	///Virtual Functions to allow additional commands to be processed when a wake signal is received by an object. This can be user modified for classes inheriting cProcess.
	virtual void OnWake(){};
};

/** \brief Class for handling user specified signals sent between classes inheriting cProcess.
 * The function UserSignal should be defined for each object. The signals each class has defined can be independant.
 * The code for processing the signal should be defined in UserSignal as there is no signal buffer.
 * This should be used for dealing with Process interactions, to make a single point of detection of interaction and allowing both processes to handle the interaction.
 * System signals (sleep, wake and kill) should be handled through cSignal.
**/
class cUserSignal
{

public:
	///Function to handle user specified signals. SIGNAL is an unsigned integer and lpData allows additional data to be passed to the function.
	virtual void UserSignal(SIGNAL liSignal,void *lpData){(void) liSignal;(void)lpData;};


};


#endif
