
#include "../WTBamboo.h"


float cPerspectiveControl::Near2D(){return mmPerspective2D.Near();};
float cPerspectiveControl::Far2D(){return mmPerspective2D.Far();};
void cPerspectiveControl::Near2D(float lfN){mmPerspective2D.Near(lfN);};
void cPerspectiveControl::Far2D(float lfF){mmPerspective2D.Far(lfF);};

cMatrix4 cPerspectiveControl::mmCombined;
cMatrix4 cPerspectiveControl::mmCamera;
cMatrix4 cPerspectiveControl::mmProjection;
cMatrix4 cPerspectiveControl::mm2DProjection;

cPerspectiveControl::cPerspectiveControl()
{
	mmPerspective.Setup(1.0f,gpWindow->RenderRatio(),1.0f,100.0f);
	mmPerspective2D.Near(1.0f);
	mmPerspective2D.Far(10.0f);
	Identity();
	UpdateProjectionMatrix();
}

float *cPerspectiveControl::CameraMatrix(){return mmCamera.Matrix();};
float *cPerspectiveControl::CombinedMatrix(){return mmCombined.Matrix();};
float *cPerspectiveControl::ProjectionMatrix(){return mmProjection.Matrix();};
float *cPerspectiveControl::Projection2DMatrix(){return mm2DProjection.Matrix();};


void cPerspectiveControl::UpdateProjectionMatrix()
{
  mmPerspective.Frustum();
  mmPerspective2D.Orthographic(mfViewportWidth,0.0f,mfViewportHeight,0.0f,mmPerspective2D.Near(),mmPerspective2D.Far());
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

}


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
 if(mbClear)
 {
 	SetClearColor();
 	glScissor(mfViewportX,mfViewportY,mfViewportWidth,mfViewportHeight);
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 }
 else
 {
    glScissor(mfViewportX,mfViewportY,mfViewportWidth,mfViewportHeight);
	glClear(GL_DEPTH_BUFFER_BIT);
 }
}

void cViewportControl::Proportional(bool lbSet)
{
 mbProportional=lbSet;
}

bool cViewportControl::Proportional()
{
 return mbProportional;
}


void cPerspectiveControl::UpdateWindowSize()
{
 if(Proportional())
 {
  mfViewportX=mfProportionalX*gpWindow->RenderAreaWidth();
  mfViewportY=mfProportionalY*gpWindow->RenderAreaHeight();
  mfViewportWidth=mfProportionalWidth*gpWindow->RenderAreaWidth();
  mfViewportHeight=mfProportionalHeight*gpWindow->RenderAreaHeight();
 }
 UpdateProjectionMatrix();
}

void cViewportControl::ViewportProportionalWidth(float lfWidth){mfProportionalWidth=lfWidth;};
void cViewportControl::ViewportProportionalHeight(float lfHeight){mfProportionalHeight=lfHeight;};
void cViewportControl::ViewportProportionalX(float lfX){mfProportionalX=lfX;};
void cViewportControl::ViewportProportionalY(float lfY){mfProportionalY=lfY;};

float cViewportControl::ViewportProportionalWidth(){return mfProportionalWidth;};
float cViewportControl::ViewportProportionalHeight(){return mfProportionalHeight;};
float cViewportControl::ViewportProportionalX(){return mfProportionalX;};
float cViewportControl::ViewportProportionalY(){return mfProportionalY;};

float cViewportControl::ViewportWidth(){return mfViewportWidth;};
float cViewportControl::ViewportHeight(){return mfViewportHeight;};
float cViewportControl::ViewportX(){return mfViewportX;};
float cViewportControl::ViewportY(){return mfViewportY;};

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

	void cViewportControl::Clear(bool lbClear)
	{
		mbClear=lbClear;
	};

	bool cViewportControl::Clear()
	{
		return mbClear;
	};


	void cViewportControl::Viewport(float lfX,float lfY,float lfWidth,float lfHeight)
	{
		mfViewportHeight=lfHeight;
		mfViewportWidth=lfWidth;
		mfViewportX=lfX;
		mfViewportY=lfY;
	};

	void cViewportControl::ViewportProportional(float lfX,float lfY,float lfWidth,float lfHeight)
	{
		mfProportionalX=lfX;
		mfProportionalY=lfY;
		mfProportionalWidth=lfWidth;
		mfProportionalHeight=lfHeight;

		mfViewportHeight=lfHeight*gpWindow->RenderAreaHeight();
		mfViewportWidth=lfWidth*gpWindow->RenderAreaWidth();
		mfViewportX=lfX*gpWindow->RenderAreaWidth();
		mfViewportY=lfY*gpWindow->RenderAreaHeight();
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
		mbClear=true;
		Proportional(false);
		ViewportProportional(200.0f,200.0f,200.0f,200.0f);
	};

	cViewportControl::cViewportControl(float lfX,float lfY,float lfWidth,float lfHeight)
	{
		mbClear=true;
		Viewport(lfX,lfY,lfWidth,lfHeight);
	};

	cViewportControl::cViewportControl(float lfX,float lfY,float lfWidth,float lfHeight, bool lbProportional)
	{
		mbClear=true;
		Proportional(lbProportional);
		if(Proportional()) Viewport(lfX,lfY,lfWidth,lfHeight);
		else ViewportProportional(lfX,lfY,lfWidth,lfHeight);
	};


c3DVf cPerspectiveControl::VisualRay(float lfX,float lfY)
{

float v3DXDist=((2.0f*(lfX-mfViewportX)-mfViewportWidth)/mfViewportWidth)*Width();
float v3DYDist=((2.0f*(lfY-mfViewportY)-mfViewportHeight)/mfViewportHeight)*Height();

return c3DVf(ZVect()*Near()-XVect()*v3DXDist-YVect()*v3DYDist);

};
