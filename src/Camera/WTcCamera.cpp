#include "stdafx.h"
#include "../WTBamboo.h"

float cCameraHandler::sfCamera_Zoom=0.0f;
cCamera *cCamera::mpCurrentCamera=0;

cCamera::cCamera()
{
 trace("Creating cCamera::cCamera()");
 if(!mpInstance)
 {
	 mpInstance=this;
	 Proportional(true);
	 ViewportProportional(0.0f,0.0f,1.0f,1.0f);
	 Width(1.0f);
	 Height(0.75f);
 }

 cCameraHandler::Instance()->Add(this);
 mpRenderList=new cRenderNode(false,this);
#if WT_FULL_VERSION_BAMBOO
 if(WT_STARTING_VIEWPORT_SLOTS) mpViewportHandler=new cViewportHandler(this,WT_STARTING_VIEWPORT_SLOTS);
 else mpViewportHandler=0;
 mpParticleHandler=0;
#endif
  mpPainter=new cPainter();
  mpPainter->Resize(WT_PAINTER_STARTING_SIZE);



}

cPainter *cCamera::Painter()
{
 return mpPainter;
}

cCamera::~cCamera()
{
 trace("Destroying cCamera");
 mpRenderList->StartKillAll();
 delete mpRenderList; mpRenderList=0;
 #if WT_FULL_VERSION_BAMBOO
    delete mpViewportHandler; mpViewportHandler=0;
 #endif
 delete mpPainter; mpPainter=0;
}

void cCamera::Stop()
{
 cCameraHandler::Instance()->Remove(this);
}

void cCamera::UpdateNotRender()
{
    ResetGLMatrix();
    mpRenderList->CalculateMatrices();
}

void cCamera::UpdateRenderSettings()
{
	UpdateViewport();
	ResetGLMatrix();
}

void cCamera::UpdateRenderState()
{
    _CAMERA_ZOOM=Near()/(Width()+Height());
	#if WT_FULL_VERSION_BAMBOO
        _LIGHT->SetLightStates();
    #endif
	mpPainter->Reset();

	mpRenderList->RenderToPainter();
}

void cCamera::RecalculateTotalMatrices()
{
 mpRenderList->RecalculateTotalMatrix();
}

void cCamera::RecalculateAllMatrices()
{
mpRenderList->CalculateMatrices();
}

void cCamera::RenderObjects()
{
	mpPainter->Render();
}


void cCamera::Render()
{
    mpCurrentCamera=this;
	UpdateRenderSettings();
	UpdateRenderState();
	ClearViewport();
	RenderObjects();
#if WT_FULL_VERSION_BAMBOO
	if(mpViewportHandler) mpViewportHandler->Render();
#endif
}


void cCamera::RemoveAll()
{
 delete mpRenderList;
 mpRenderList=0;
}

cCamera *cCamera::mpInstance=0;

cCamera *cCamera::Instance()
{
	if (!mpInstance) mpInstance=new cCamera;

	return mpInstance;
}


cRenderNode *cCamera::RenderList()
{
  return mpRenderList;

};


vRenderObject *cCamera::vRenderList()
{
  return (vRenderObject*)mpRenderList;

};



cCameraHandler::cCameraHandler()
{
 mcList.Init(WT_STARTING_CAMERA_SLOTS);
};

cCameraHandler *cCameraHandler::mpInstance=0;

cCameraHandler *cCameraHandler::Instance()
{
	if(!mpInstance) mpInstance=new cCameraHandler;
	return mpInstance;
};

void cCameraHandler::Add(cCamera *lpCamera)
{
	mcList.Add(lpCamera);
};

void cCameraHandler::Remove(cCamera *lpCamera)
{
	mcList.Delete(lpCamera);
};
#if WT_FULL_VERSION_BAMBOO
cParticleHandler *cCamera::ParticleHandler()
{
	if(!mpParticleHandler) mpParticleHandler=new cParticleHandler;
	return mpParticleHandler;
}

#endif
void cCameraHandler::RenderCameras()
{
 uint8 liPos;
 for(liPos=0;liPos<mcList.Items();++liPos)
 {
  if(mcList[liPos]->Awake()) mcList[liPos]->Render();
 }
 UpdateScreen();
}
void cCameraHandler::UpdateNotRenderCameras()
{
 uint8 liPos;
 for(liPos=0;liPos<mcList.Items();++liPos)
 {
  if(mcList[liPos]->Awake()) mcList[liPos]->UpdateNotRender();
 }
}

void cCamera::UpdateWindowSize()
{
#if WT_FULL_VERSION_BAMBOO
 if(mpViewportHandler) mpViewportHandler->UpdateWindowSize();
#endif
 if(Proportional())
 {
  mfViewportX=mfProportionalX*gpWindow->RenderAreaX();
  mfViewportY=mfProportionalY*gpWindow->RenderAreaY();
  mfViewportWidth=mfProportionalWidth*gpWindow->RenderAreaWidth();
  mfViewportHeight=mfProportionalHeight*gpWindow->RenderAreaHeight();
 }
 UpdateProjectionMatrix();


}

void cCameraHandler::UpdateWindowSize()
{

 uint8 liPos;
 for(liPos=0;liPos<mcList.Items();++liPos)
 {
  if(mcList[liPos]->Awake()) mcList[liPos]->UpdateWindowSize();
 }
 gpSettings->UserWindowSizeUpdate();
}

void cCameraHandler::UpdateScreen()
{
	#if WT_OS_TYPE==OS_WIN32
		SwapBuffers(gpWindow->hDC);
	#endif
	#if WT_OS_TYPE==OS_LINUX
		glXSwapBuffers(gpWindow->lpDisplay,gpWindow->lWindow);
	#endif
	gpWindow->Repaint=false;

};


