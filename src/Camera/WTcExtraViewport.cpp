#include "../WTBamboo.h"


cExtraViewport::cExtraViewport()
{
 mpHandler=_CAMERA->mpViewportHandler;
 if(mpHandler) mpHandler->Add(this);
};

cExtraViewport::cExtraViewport(cCamera *lpCamera)
{
 mpHandler=lpCamera->mpViewportHandler;
 if(mpHandler) mpHandler->Add(this);
};

cExtraViewport::~cExtraViewport()
{
 //mpHandler->Remove(this);
};

void cExtraViewport::UpdateRenderSettings()
{
	UpdateViewport();
	ResetGLMatrix();
}

void cExtraViewport::Stop()
{
 if(mpHandler)
 {
	 mpHandler->Remove(this);
 	mpHandler=0;
 }
 else
 {
	delete this;
 }
}

void cExtraViewport::PrepareForRender()
{
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

void cViewportHandler::Add(cExtraViewport *lpNew)
{
 mcList.Add(lpNew);
}
void cViewportHandler::Remove(cExtraViewport *lpOld)
{
	mcList.Remove(lpOld);
}

void cExtraViewport::UpdateProjectionMatrix()
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

