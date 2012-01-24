#include "../WTBamboo.h"

cMatrix4 cPerspectiveControl::mmCombined;
cMatrix4 cPerspectiveControl::mmCamera;
cMatrix4 cPerspectiveControl::mmProjection;
cMatrix4 cPerspectiveControl::mm2DProjection;

cPerspectiveControl::cPerspectiveControl()
{
	mmPerspective.Setup(1.0f,gpWindow->Ratio(),1.0f,100.0f);
	Identity();
}

float *cPerspectiveControl::CameraMatrix(){return mmCamera.Matrix();};
float *cPerspectiveControl::CombinedMatrix(){return mmCombined.Matrix();};
float *cPerspectiveControl::ProjectionMatrix(){return mmProjection.Matrix();};
float *cPerspectiveControl::Projection2DMatrix(){return mm2DProjection.Matrix();};

cCamera::cCamera()
{
 trace("Creating cCamera::cCamera()");
 mpRenderList=new cRenderNode(0);


 if(WT_VIEWPORTS_ALLOWED) mpViewportHandler=new cViewportHandler(this,WT_VIEWPORTS_ALLOWED);
 else mpViewportHandler=0;

  cPainter::Instance();
}

cCamera::~cCamera()
{
 trace("Destroying cCamera");
 mpRenderList->StartKillAll();
 delete mpRenderList; mpRenderList=0;
 delete mpViewportHandler; mpViewportHandler=0;
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
	#if WT_FULL_VERSION_BAMBOO
        _LIGHT->SetLightStates();
    #endif
	cPainter::Instance()->Reset();

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


	cPainter::Instance()->Render();

}

void cCamera::UpdateScreen()
{
	#if WT_OS_TYPE==OS_WIN32
		SwapBuffers(gpWindow->hDC);
	#endif
	#if WT_OS_TYPE==OS_LINUX
		glXSwapBuffers(gpWindow->lpDisplay,gpWindow->lWindow);
	#endif
	gpWindow->Repaint=false;

};

void cCamera::Render()
{
	UpdateRenderSettings();
	UpdateRenderState();
	ClearViewport();
	RenderObjects();

	if(mpViewportHandler) mpViewportHandler->Render();

	UpdateScreen();
}


void cCamera::RemoveAll()
{
 delete mpRenderList;
 mpRenderList=0;
}

void cPerspectiveControl::UpdateProjectionMatrix()
{
	#warning comment This runs every frame. Only neccessary on frames when window is resized or values are changed.
  mmPerspective.Frustum();
  mmPerspective2D.Orthographic(mfViewportWidth,0.0f,mfViewportHeight,0.0f,1.0f,10.0f);

}

void cCamera::UpdateProjectionMatrix()
{

  mmPerspective.Frustum();
  gpWindow->FindRenderArea();
  mfViewportWidth=gpWindow->Width();
  mfViewportHeight=gpWindow->Height();
  mmPerspective2D.Orthographic(mfViewportWidth,0.0f,mfViewportHeight,0.0f,1.0f,10.0f);

}

float cPerspectiveControl::Near()
{
 return mmPerspective.Near();
}

float cPerspectiveControl::Far()
{
 return mmPerspective.Far();
}

void cPerspectiveControl::ResetGLMatrix()
{
	_MATRIX_STACK->Identity();
	mmCamera=ConstructCameraMatrix();
    mmCombined=mmPerspective;
	mmCombined.Multiply(mmCamera.Matrix());
	mmProjection=mmPerspective;
	mm2DProjection=mmPerspective2D;

	printf("mmCamera");
	mmCamera.Display();
	printf("\nmmProjection");
	mmProjection.Display();
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

void cPerspectiveControl::Near(float lfN)
{
  mmPerspective.Near(lfN);

};

void cPerspectiveControl::Far(float lfF)
{
  mmPerspective.Far(lfF);

};


void cPerspectiveControl::Width(float lfZoom)
{
	mmPerspective.Width(lfZoom);
}
float cPerspectiveControl::Width()
{
	return mmPerspective.Width();
}

void cPerspectiveControl::Height(float lfHeight)
{
	mmPerspective.Height(lfHeight);
}

float cPerspectiveControl::Height()
{
	return mmPerspective.Height();
}

float cPerspectiveControl::Ratio()
{
  return mmPerspective.Ratio();
}

void cPerspectiveControl::Ratio(float lfRatio)
{
 mmPerspective.Ratio(lfRatio);
}

void cViewportControl::ClearViewport()
{
 SetClearColor();
 glScissor(mfViewportX,mfViewportY,mfViewportWidth,mfViewportHeight);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void cViewportControl::SetClearColor()
{
glClearColor(mcClearColor.R(),mcClearColor.G(),mcClearColor.B(),mcClearColor.A());
}

void cViewportControl::ClearColor(float lfRed,float lfGreen,float lfBlue,float lfAlpha)
{
 mcClearColor.Set(lfRed,lfGreen,lfBlue,lfAlpha);
}

	void cViewportControl::ClearColor(float *lpColor){mcClearColor=lpColor;};
	void cViewportControl::ClearColor(cRGBA &lpColor){mcClearColor=lpColor;}
	void cViewportControl::ClearColor(cRGB &lpColor){ mcClearColor=lpColor;}
	void cViewportControl::ClearColor(cRGBA *lpColor){mcClearColor=lpColor;}
	void cViewportControl::ClearColor(cRGB *lpColor){ mcClearColor=lpColor;}
	cRGBA cViewportControl::ClearColor(){ return mcClearColor;}





	void cViewportControl::Viewport(float lfX,float lfY,float lfWidth,float lfHeight)
	{
		mfViewportHeight=lfHeight;
		mfViewportWidth=lfWidth;
		mfViewportX=lfX;
		mfViewportY=lfY;
	};
	void cViewportControl::ViewportX(float lfX){mfViewportX=lfX;};
	void cViewportControl::ViewportY(float lfY){mfViewportY=lfY;};
	void cViewportControl::ViewportWidth(float lfWidth){mfViewportWidth=lfWidth;};
	void cViewportControl::ViewportHeight(float lfHeight){mfViewportHeight=lfHeight;};

	void cViewportControl::UpdateViewport()
	{
		glViewport(mfViewportX,mfViewportY,mfViewportWidth,mfViewportHeight);
	};

	cViewportControl::cViewportControl()
	{
		mfViewportHeight=gpWindow->Height();
		mfViewportWidth=gpWindow->Width();
		mfViewportX=mfViewportY=0.0f;


	};

	cViewportControl::cViewportControl(float lfX,float lfY,float lfWidth,float lfHeight)
	{
		Viewport(lfX,lfY,lfWidth,lfHeight);

	};

