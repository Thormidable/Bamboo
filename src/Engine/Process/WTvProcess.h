#ifndef __WTVPROCESS_H__
#define __WTVPROCESS_H__


class cParentStack;

/// This is the virtual base class for a system process, see cProcess.
class vProcess : public cSignal, public cUserSignal
{
public:
 virtual ~vProcess(){};
 /// Virtual function linking code to update (or run) the process by single frame.
 virtual void Run()=0;

 // Virtual function for extra processes to be performed when proccess is killed.
 virtual void AdditionalKillFunctionality()=0;
 virtual void AdditionalSleepFunctionality()=0;
 virtual void AdditionalWakeFunctionality()=0;
 ///Virtual Function for 
 virtual cParentStack *ParentStack()=0;



};

#endif
