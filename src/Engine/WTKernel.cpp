
#include "../WTBamboo.h"

cWindow *gpWindow;
//cAudioDevice *gpAudioDevice;
cSync *gpTimer;


cKernel *cKernel::mpInstance=0;
cLinkedNode<cProcess> *cKernel::mpSearch;

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
		_MOUSE->Update();
        _KEYBOARD->UpdateKeyboard();

		if(gpWindow->mbQuit || mbKillProgram) return;

	  trace("New Process Cycle")
		//cLinkedNode<cProcess> *lpCursor;
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
	trace(liProcessCount << " Processes Processed this Cycle")

	++liPTF;
	if(liPTF<_PPF) cCamera::Instance()->UpdateNotRender();
	}
	liPTF=0;
trace("New Render Cycle")
	cCamera::Instance()->Render();


if(_FPS)
{
	gpTimer->Tick();
	if(gpTimer->GetTimeMod()< _TIME_PER_FRAME)
	{
		gpTimer->SleepWrap((_TIME_PER_FRAME-gpTimer->GetTimeMod())*1000);
	}
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

#if WT_FULL_VERSION_BAMBOO
	trace("Deleting cLightHandler");
	delete cLightHandler::Instance();
#endif

	trace("Deleting cPainter");
	delete cPainter::Instance();

	trace("Deleting cSync");
	delete gpTimer;
	trace("Deleting cWindow");
	delete gpWindow;
	trace("Delete all Bamboo Objects");

	trace("Finished Bamboo V 1.1");

}

cLinkedNode<cProcess> *cKernel::Add(cProcess *lpNew)
{

	if (!mpProcess)
	{
		mpProcess=new cLinkedList<cProcess>(lpNew);
		return mpProcess->Start();
	}
	return mpProcess->Insert(lpNew);
}

void cKernel::Remove(cLinkedNode<cProcess> *lpOld)
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
	trace("Creating cKernel");
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
