
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
		gpWindow->HandleMessages();
		gpWindow->HandleChanges();

		_MOUSE->Update();
        _KEYBOARD->UpdateKeyboard();

		if(gpWindow->mbQuit || mbKillProgram) return;

		mpCursor=mpProcess->Start();
		liProcessCount=0;
		while(mpCursor)
  		{
		  ++liProcessCount;
			if(mpCursor->Data() && mpCursor->Data()->Awake())
			{
				mpCursor->Data()->Run();
				mpCursor=mpCursor->Next();
			}
			else
			{
				if(!(mpCursor->Data()->Alive()))
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
	if(liPTF<_PPF) cCameraHandler::Instance()->UpdateNotRenderCameras(); //cCamera::Instance()->UpdateNotRender();
	}
	liPTF=0;
cCameraHandler::Instance()->RenderCameras();






if(_FPS)
{
	gpTimer->Tick();
	if(gpTimer->GetTimeMod()< _TIME_PER_FRAME)
	{
		printf("Time to Process Frame : %f s\n",gpTimer->GetTimeMod());
		printf("Free Time this frame : %f ms\n",(_TIME_PER_FRAME-gpTimer->GetTimeMod())*OS_TIME_SCALING);
		gpTimer->SleepWrap((_TIME_PER_FRAME-gpTimer->GetTimeMod())*OS_TIME_SCALING);
		printf("FPS : %f\n",1.0f/(gpTimer->GetTimeMod()+(_TIME_PER_FRAME-gpTimer->GetTimeMod())*OS_TIME_SCALING/1000));
	}
	else
	{
	    	printf("FPS : %f\n",1.0f/(gpTimer->GetTimeMod()));
	}

}
else
{
	gpTimer->Tick();
	printf("FPS : %f\n",gpTimer->GetCPS());
}

}

}

cKernel::~cKernel()
{
    _MOUSE->Unlock();
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

	trace("Deleting cSync");
	delete gpTimer;
	trace("Deleting cWindow");
	delete gpWindow;
	trace("Delete all Bamboo Objects");


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
	gpElementArray=new cElementArray;
}


void cKernel::ResetFindProcess()  { mpSearch=mpProcess->Start(); }

void cKernel::KillProgram()
{
 mbKillProgram=true;
};
