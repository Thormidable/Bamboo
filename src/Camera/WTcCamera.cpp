#include "../WTDivWin.h"

cCamera::cCamera()
{
 trace("Creating cCamera::cCamera()");
 mpRenderList=new cRenderNode(0);
 Identity();
// gpWindow->InitialiseOpenGL();
 mmPerspective.Setup(0.5f,gpWindow->Ratio(),1.0f,20.0f);
 UpdateProjectionMatrix();
 cPainter::Instance();
}

cCamera::~cCamera()
{
 trace("Destroying cCamera");
 delete mpRenderList; mpRenderList=0;
}

void cCamera::UpdateNotRender()
{
    ResetGLMatrix();
    mpRenderList->RenderToPainter();
}

void cCamera::Render()
{

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

void cCamera::UpdateProjectionMatrix()
{
	#warning comment This runs every frame. Only neccessary on frames when window is resized or values are changed.
  mmPerspective.Frustum();

}

float cCamera::Near()
{
 return mmPerspective.Near();
}

float cCamera::Far()
{
 return mmPerspective.Far();
}

void cCamera::ResetGLMatrix()
{
	_MATRIX_STACK->Identity();
	mmPerspectiveCameraMatrix=mmPerspective;
	//mmPerspectiveCameraMatrix.Multiply(Test());
	mmPerspectiveCameraMatrix.Multiply(Matrix());
	mmPerspectiveCameraMatrix.Translate(mpPosition);

}

cCamera *cCamera::mpInstance=0;

cCamera *cCamera::Instance()
{
	if (!mpInstance) mpInstance=new cCamera;

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
  mmPerspective.Near(lfN);

};

void cCamera::Far(float lfF)
{
  mmPerspective.Far(lfF);

};

float *cCamera::Perspective()
{
 return mmPerspective.Matrix();
}

void cCamera::Width(float lfZoom)
{
	mmPerspective.Width(lfZoom);
}
float cCamera::Width()
{
	return mmPerspective.Width();
}

void cCamera::Height(float lfHeight)
{
	mmPerspective.Height(lfHeight);
}

float cCamera::Height()
{
	return mmPerspective.Height();
}

float cCamera::Ratio()
{
  return mmPerspective.Ratio();
}

void cCamera::Ratio(float lfRatio)
{
 mmPerspective.Ratio(lfRatio);
}


	void cCamera::SetClearColor(float *lpColor)	{ 	glClearColor(lpColor[0],lpColor[1],lpColor[2],lpColor[3]); }
	void cCamera::SetClearColor(cRGBA &lpColor){ 	glClearColor(lpColor[0],lpColor[1],lpColor[2],lpColor[3]); }
	void cCamera::SetClearColor(cRGB &lpColor){ 	glClearColor(lpColor[0],lpColor[1],lpColor[2],1.0f); }
	void cCamera::SetClearColor(cRGBA *lpColor){ 	glClearColor(lpColor->R(),lpColor->G(),lpColor->B(),lpColor->A()); }
	void cCamera::SetClearColor(cRGB *lpColor){ 	glClearColor(lpColor->R(),lpColor->G(),lpColor->B(),1.0f); }

float *cCamera::TotalPositionMatrix()
{
#warning comment Potential Minor Optimisation here. Can combine both matrices together.
    return mmPerspectiveCameraMatrix.Matrix();
};

