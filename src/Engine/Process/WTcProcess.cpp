#include "../../WTDivWin.h"

cProcess *gpParent;



cProcess::cProcess()
{

 if(WT_USE_PARENT_STACK) mpParent=new cParentStack(this);
 else mpParent=0;
	
  mpKernel=cKernel::Instance();
  mpNode=mpKernel->Add(this);
  mbAlive=true;
  mbAwake=true;
 
}

cProcess::~cProcess() 
{
	if(WT_USE_PARENT_STACK) delete []mpParent;
};


void cProcess::KillAll(){cKernel::Instance()->KillProgram();};

void cProcess::Signal(SIGNAL liFlags)
{
	if(mpParent && liFlags&WT_SIGNAL_VALUE_TREE)
	{
		mpParent->Signal(liFlags);
	}
	
	cSignal::Signal(liFlags);
}


void cProcess::UserSignal(SIGNAL lsSignal,void *lpData)
{
  (void)lsSignal;
  (void) lpData;
  
};

cParentStack *cProcess::ParentStack(){return mpParent;};
