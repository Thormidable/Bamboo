#include "../WTDivWin.h"

cCamera::cCamera()
{
 trace("Creating cCamera::cCamera()");
 mpRenderList=new cRenderNode(0);
 Identity();
// gpWindow->InitialiseOpenGL();
 mfZoom=0.5; //0.5 - 1.0 is correction. 0.1 - 0.5 is fisheye ???
 mfNear=1.0f;
 mfFar=20.0f;
 Frustum();
}

cCamera::~cCamera()
{
 trace("Creating cCameraPainter::cCameraPainter()");
 delete mpRenderList; mpRenderList=0;
}

cCameraPainter::cCameraPainter()
{
 cPainter::Instance();
}




void cCamera::Render()
{
	printf("Camera Not Painter Render\n");

	//This will render the objects in their current render tree order
 glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 ResetGLMatrix();
 mpRenderList->Render();
#if WT_OS_TYPE==OS_WIN32
	SwapBuffers(gpWindow->hDC);
#endif
#if WT_OS_TYPE==OS_LINUX
	glXSwapBuffers(gpWindow->lpDisplay,gpWindow->lWindow);
#endif

 gpWindow->Repaint=false;
}

void cCameraPainter::Render()
{
	printf("Camera Painter Algorithm Render\n");
	
	ResetGLMatrix();
	cPainter::Instance()->Reset();
	
	mpRenderList->RenderToPainter();
	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cPainter::Instance()->Render();
	#if WT_OS_TYPE==OS_WIN32
	SwapBuffers(gpWindow->hDC);
	#endif
	#if WT_OS_TYPE==OS_LINUX
	glXSwapBuffers(gpWindow->lpDisplay,gpWindow->lWindow);
	#endif
	gpWindow->Repaint=false;
}

void cCamera::SetClearColor(float lfRed,float lfGreen,float lfBlue,float lfAlpha)
{
 glClearColor(lfRed,lfGreen,lfBlue,lfAlpha);
}

void cCamera::RemoveAll()
{
 delete mpRenderList;
 mpRenderList=0;
}

void cCamera::Orthographic()
{
 glViewport(0,0,gpWindow->Width,gpWindow->Height);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-1.0,1.0,-1.0,1.0,1.0,10.0);
 glMatrixMode(GL_MODELVIEW);
}

void cCamera::Frustum()
{
 glViewport(0,0,gpWindow->Width,gpWindow->Height);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glFrustum(-mfZoom, mfZoom, -gpWindow->mfRatio*mfZoom, gpWindow->mfRatio*mfZoom, mfNear, mfFar);
 glMatrixMode(GL_MODELVIEW);
}

float cCamera::Near()
{
 return mfNear;
}

float cCamera::Far()
{
 return mfFar;
}

void cCamera::ResetGLMatrix()
{
	glLoadIdentity();
	glMultMatrixf(Matrix());
	glTranslatef(mpPosition[0],mpPosition[1],mpPosition[2]);
}

cCamera *cCamera::mpInstance=0;

cCamera *cCamera::Instance()
{
	if (!mpInstance)
	{
		
		if(WT_USE_PAINTER_ALGORITHM) mpInstance=new cCameraPainter;
		else mpInstance=new cCamera;
	}
	
	return mpInstance;
}

/// This will return a pointer to the scene graph.
cRenderNode *cCamera::RenderList()
{
  return mpRenderList;
  
};

/// This will return a virtual pointer to the the scene graph.
vRenderObject *cCamera::vRenderList()
{
  return (vRenderObject*)mpRenderList;
  
};

void cCamera::Near(float lfN)
{
  mfNear=lfN;
  
};

void cCamera::Far(float lfF)
{
  mfFar=lfF;
  
};
