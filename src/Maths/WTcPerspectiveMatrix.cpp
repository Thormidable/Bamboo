#include "../WTDivWin.h"

void cPerspectiveMatrix::Viewport()
{
	glViewport(0,0,gpWindow->Width,gpWindow->Height);
}

cPerspectiveMatrix::cPerspectiveMatrix()
{
 mfZoom=0.5f;
 mfRatio=800.0f/600.0f;
 mfNear=1.0f;
 mfFar=100.0f;

}

void cPerspectiveMatrix::Setup(float lfZoom,float lfRatio,float lfNear,float lfFar)
{
 mfZoom=lfZoom;
 mfRatio=lfRatio;
 mfNear=lfNear;
 mfFar=lfFar;
}

void cPerspectiveMatrix::Frustum()
{
 Viewport();
 Zero();
 mpData[0]=(mfNear)/(mfZoom);
 mpData[5]=(mfNear)/(mfZoom*mfRatio);
 mpData[10]=-(mfNear+mfFar)/(mfFar-mfNear);
 mpData[11]=-1.0f;
 mpData[14]=(-2.0f*mfFar*mfNear)/(mfFar-mfNear);
}

void cPerspectiveMatrix::Orthographic()
{
	Viewport();
Zero();
mpData[0]=1.0f/mfZoom;
mpData[5]=1.0f/(mfZoom*mfRatio);
mpData[10]=-2.0f/(mfFar-mfNear);
mpData[14]=-(mfFar+mfNear)/(mfFar-mfNear);
mpData[15]=1.0f;
}

void cPerspectiveMatrix::Frustum(float Width, float Height, float Near, float Far)
{
	Viewport();
 Zero();
 mpData[0]=(Near)/(Width);
 mpData[5]=(Near)/(Height);
 mpData[10]=-(Near+Far)/(Far-Near);
 mpData[11]=-1.0f;
 mpData[14]=(-2.0f*Far*Near)/(Far-Near);
}

void cPerspectiveMatrix::Orthographic(float Width, float Height, float Near, float Far)
{
	Viewport();
Zero();
mpData[0]=1.0f/Width;
mpData[5]=1.0f/Height;
mpData[10]=-2.0f/(Far-Near);
mpData[14]=-(Far+Near)/(Far-Near);
mpData[15]=1.0f;
}

	void cPerspectiveMatrix::Frustum(float Right, float Left, float Top, float Bottom, float Near, float Far)
	{
		Viewport();
		Zero();
		mpData[0]=(2.0f*Near)/(Right-Left);
		mpData[5]=(2.0f*Near)/(Top-Bottom);
		mpData[8]=(Right+Left)/(Right-Left);
		mpData[9]=(Top+Bottom)/(Top-Bottom);
		mpData[10]=-(Far+Near)/(Far-Near);
		mpData[11]=-1.0f;
		mpData[14]=-(2.0f*Far*Near)/(Far-Near);

	}
	void cPerspectiveMatrix::Orthographic(float Right, float Left, float Top, float Bottom, float Near, float Far)
	{
		Viewport();
		Zero();
		mpData[0]=2.0f/(Right-Left);
		mpData[5]=2.0f/(Top-Bottom);
		mpData[10]=-2.0f/(Far-Near);
		mpData[12]=-(Right+Left)/(Right-Left);
		mpData[13]=-(Top+Bottom)/(Top-Bottom);
		mpData[14]=-(Far+Near)/(Far-Near);
		mpData[15]=1.0f;

	}
	void cPerspectiveMatrix::Frustum(float *lpValues)
	{
		Viewport();
 Zero();
 mpData[0]=(lpValues[2])/(lpValues[0]);
 mpData[5]=(lpValues[2])/(lpValues[1]);
 mpData[10]=-(lpValues[2]+lpValues[3])/(lpValues[3]-lpValues[2]);
 mpData[11]=-1.0f;
 mpData[14]=(-2.0f*lpValues[3]*lpValues[2])/(lpValues[3]-lpValues[2]);
	}
	void cPerspectiveMatrix::Orthographic(float *lpValues)
	{
		Viewport();
Zero();
mpData[0]=1.0f/lpValues[0];
mpData[5]=1.0f/lpValues[1];
mpData[10]=-2.0f/(lpValues[3]-lpValues[2]);
mpData[14]=-(lpValues[3]+lpValues[2])/(lpValues[3]-lpValues[2]);
mpData[15]=1.0f;

	}
	void cPerspectiveMatrix::Frustum2(float *lpValues)
	{
		Viewport();
		Zero();
		mpData[0]=(2.0f*lpValues[4])/(lpValues[0]-lpValues[1]);
		mpData[5]=(2.0f*lpValues[4])/(lpValues[2]-lpValues[3]);
		mpData[8]=(lpValues[0]+lpValues[1])/(lpValues[0]-lpValues[1]);
		mpData[9]=(lpValues[2]+lpValues[3])/(lpValues[2]-lpValues[3]);
		mpData[10]=-(lpValues[5]+lpValues[4])/(lpValues[5]-lpValues[4]);
		mpData[11]=-1.0f;
		mpData[14]=-(2.0f*lpValues[5]*lpValues[4])/(lpValues[5]-lpValues[4]);
	}
	void cPerspectiveMatrix::Orthographic2(float *lpValues)
	{
		Viewport();
		Zero();
		mpData[0]=2.0f/(lpValues[0]-lpValues[1]);
		mpData[5]=2.0f/(lpValues[2]-lpValues[3]);
		mpData[10]=-2.0f/(lpValues[5]-lpValues[4]);
		mpData[12]=-(lpValues[0]+lpValues[1])/(lpValues[0]-lpValues[1]);
		mpData[13]=-(lpValues[2]+lpValues[3])/(lpValues[2]-lpValues[3]);
		mpData[14]=-(lpValues[5]+lpValues[4])/(lpValues[5]-lpValues[4]);
		mpData[15]=1.0f;
	}
	