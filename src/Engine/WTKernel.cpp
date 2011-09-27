
#include "../WTDivWin.h"

cWindow *gpWindow;
//cAudioDevice *gpAudioDevice;
cSync *gpTimer;


cKernel *cKernel::mpInstance=0;
cLinkedNode<vProcess> *cKernel::mpSearch;

void cKernel::DeleteAll()
{
	delete mpProcess;
	mpProcess=0;
}

void cKernel::Update()
{
uint32 liProcessCount;
uint16 liPTF=0;

trace("Entering cKernel::Update")
while(mpProcess)
{
	while(liPTF<_PPF)
	{
		trace("Handle Messages")
		gpWindow->HandleMessages();
		gpWindow->HandleChanges();
		
		trace("Update Mouse / Window")
		_MOUSE.Update();
		
		if(gpWindow->mbQuit || mbKillProgram) return;
		
	  trace("New Process Cycle")
		//cLinkedNode<vProcess> *lpCursor;
		mpCursor=mpProcess->Start();
		liProcessCount=0;
		while(mpCursor)
  		{
		  ++liProcessCount;
		//XXXXXXXXXXXXXXXXX LOOK AT THIS
			if(mpCursor->mpData && mpCursor->mpData->Awake())
			{
			  //printf("cPainter::lpValue %p\n",cPainter::lpValue);
				mpCursor->mpData->Run();
				mpCursor=mpCursor->Next(); 
			}
			else
			{
				if(!(mpCursor->mpData->Alive()))
				{
					if(mpCursor->Next()) 
					{
						mpCursor=mpCursor->Next(); 
						mpProcess->Delete(mpCursor->Previous());
						
					}
					else 
					{
						mpProcess->Delete(mpCursor); 
						
						mpCursor=0;
					}
				}
				else
				{
				  mpCursor=mpCursor->Next();
				}
			}
		}
	trace(liProcessCount << " Processes Processed this Frame")
	++liPTF;
	}
	liPTF=0;
trace("New Render Cycle")
	cCamera::Instance()->Render();


if(_FPS)
{
gpTimer->Tick();
if(gpTimer->GetTimeMod()< _TIME_PER_FRAME) gpTimer->SleepWrap(_TIME_PER_FRAME-gpTimer->GetTimeMod());
}
	trace("Update Timer")
	gpTimer->Tick();
	printf("FPS:%f\n",gpTimer->GetCPS());
	
}

}

cKernel::~cKernel()
{
	trace("Deleting all cProcess Objects");
	DeleteAll();
trace("Deleting cCamera");
	delete cCamera::Instance();

	trace("Deleting cFileHandler");
	delete cFileHandler::Instance();
	trace("Deleting cEventHandler");
	delete cEventHandler::Instance();
	
trace("Deleting cCollisionHandler");
	delete cCollisionHandler::Instance();
	
	trace("Deleting cLightHandler");
	delete cLightHandler::Instance();
#if WT_USE_PAINTER_ALGORITHM
	trace("Deleting cPainter");
	delete cPainter::Instance();
#endif
	trace("Deleting cSync");
	delete gpTimer;
	trace("Deleting cWindow");
	delete gpWindow;
	trace("Delete all DivWin Objects");
	
}

cLinkedNode<vProcess> *cKernel::Add(vProcess *lpNew)
{
	trace("cKernel::Add")
	if (!mpProcess)
	{
		mpProcess=new cLinkedList<vProcess>(lpNew);
		return mpProcess->Start();
	}
	return mpProcess->Insert(lpNew);
}

void cKernel::Remove(cLinkedNode<vProcess> *lpOld)
{
	mpProcess->Delete(lpOld);
}

cKernel *cKernel::Instance()
{
	if (!mpInstance) {mpInstance=new cKernel;}
	return mpInstance;
}

cKernel::cKernel()
{
	trace("Entering cKernel::cKernel");
	mpProcess=0;

	mpCursor=0;
	mpInstance=0;
	mpSearch=0;
	mfTickFreq=1.0f;

	mbKillProgram=false;
	cCamera::Instance();
}


void cKernel::ResetFindProcess()  { mpSearch=mpProcess->Start(); }

void cKernel::KillProgram()
{
 mbKillProgram=true;
};