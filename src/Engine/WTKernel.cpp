
#include "stdafx.h"
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
	//trace(liProcessCount << " Processes Processed this Cycle")

	++liPTF;
	if(liPTF<_PPF) cCameraHandler::Instance()->UpdateNotRenderCameras(); //cCamera::Instance()->UpdateNotRender();
	}
	liPTF=0;

if(cFrameUpdateHandler::Pointer()) cFrameUpdateHandler::Pointer()->FrameUpdate();

cCameraHandler::Instance()->RenderCameras();

if(_FPS) gpTimer->EnforceFrameRate();
else gpTimer->Tick();

}

}

cKernel::~cKernel()
{
    _MOUSE->Unlock();
	TRACE("Deleting all cProcess Objects");
	DeleteAll();
    TRACE("Deleting cCamera");
	delete cCamera::Instance();

	TRACE("Deleting cFileHandler");
	delete cFileHandler::Instance();
	TRACE("Deleting cEventHandler");
	delete cEventHandler::Instance();

    TRACE("Deleting cCollisionHandler");
	delete cCollisionHandler::Instance();

#if WT_FULL_VERSION_BAMBOO
	TRACE("Deleting cLightHandler");
	delete cLightHandler::Instance();
#endif

	TRACE("Deleting cSync");
	delete gpTimer;
	TRACE("Deleting cWindow");
	delete gpWindow;
	TRACE("Delete all Bamboo Objects");


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
#if WT_FULL_VERSION_BAMBOO
	gpElementArray=new cElementArray;
#endif
}


void cKernel::ResetFindProcess()  { mpSearch=mpProcess->Start(); }

void cKernel::KillProgram()
{
 mbKillProgram=true;
};

cProcess *cKernel::CurrentProcess()
{
    return mpCursor->Data();
};


  cFrameUpdateHandler *cFrameUpdateHandler::mpInstance=0;
  cFrameUpdateHandler::cFrameUpdateHandler()
  {
    Init(5);
  };


  cFrameUpdateHandler *cFrameUpdateHandler::Instance()
  {
      if(!mpInstance){ mpInstance=new cFrameUpdateHandler; }
      return mpInstance;
  };
  cFrameUpdateHandler *cFrameUpdateHandler::Pointer()
  {
      return mpInstance;
  };

  void cFrameUpdateHandler::FrameUpdate()
  {
      for(uint32 liCount=0;liCount<miItems;++liCount)
      {
          mpList[liCount]->FrameUpdate();
      }
  };


cFrameUpdateType::cFrameUpdateType()
{
    cFrameUpdateHandler::Instance()->Add(this);
}
cFrameUpdateType::~cFrameUpdateType()
{
    cFrameUpdateHandler::Instance()->StripItem(this);
}
