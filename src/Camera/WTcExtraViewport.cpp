
#include "../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO
cViewport::cViewport()
{
 mpHandler=_CAMERA->mpViewportHandler;
 if(mpHandler) mpHandler->Add(this);
};

cViewport::cViewport(cCamera *lpCamera)
{
 mpHandler=lpCamera->mpViewportHandler;
 if(mpHandler) mpHandler->Add(this);
};

cViewport::~cViewport()
{
 mpHandler=0;
};

void cViewport::UpdateRenderSettings()
{

	UpdateViewport();
	ResetGLMatrix();
}

void cViewport::Stop()
{
 if(mpHandler)
 {
	 mpHandler->Remove(this);
 }
 else
 {
	delete this;
 }
}

void cViewport::PrepareForRender()
{
    _CAMERA_ZOOM=Near()/(Width()+Height());
		UpdateProjectionMatrix();
		UpdateViewport();
		ResetGLMatrix();
		ClearViewport();
}

void cViewportHandler::Render()
{
 uint8 liPos;
 for(liPos=0;liPos<mcList.Items();++liPos)
 {

	if(mcList[liPos]->Awake())
	{
		mcList[liPos]->PrepareForRender();
		mpCamera->RecalculateTotalMatrices();
		mpCamera->RenderObjects();


	}
 }
};

cViewportHandler::cViewportHandler(cCamera *lpCamera,uint8 liViewports)
{
 mpCamera=lpCamera;
 mcList.Init(liViewports);
 glEnable(GL_SCISSOR_TEST);
}

void cViewportHandler::Add(cViewport *lpNew)
{
 mcList.Add(lpNew);
}
void cViewportHandler::Remove(cViewport *lpOld)
{
	mcList.Delete(lpOld);
}

void cViewport::UpdateProjectionMatrix()
{

  mmPerspective.Frustum();
  mmPerspective2D.Orthographic(mfViewportWidth,0.0f,mfViewportHeight,0.0f,1.0f,10.0f);

}

void cViewportHandler::UpdateWindowSize()
{
 uint8 liPos;
 for(liPos=0;liPos<mcList.Items();++liPos)
 {
		mcList[liPos]->UpdateWindowSize();

 }

};

#endif
