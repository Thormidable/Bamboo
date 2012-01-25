#ifndef __WTCPERSPECTIVECONTROL_H__
#define __WTCPERSPECTIVECONTROL_H__

class cViewportHandler;
class cExtraViewport;

class cViewportControl
{
protected:
 float mfViewportX,mfViewportY;
 float mfViewportWidth,mfViewportHeight;

 float mfProportionalX,mfProportionalY;
 float mfProportionalWidth,mfProportionalHeight;
 cRGBA mcClearColor;
 bool mbProportional;

 void SetClearColor();

public:

	cViewportControl();
	cViewportControl(float lfX,float lfY,float lfWidth,float lfHeight);
	cViewportControl(float lfX,float lfY,float lfWidth,float lfHeight, bool lbProportional);

	void Viewport(float lfX,float lfY,float lfWidth,float lfHeight);
	void ViewportX(float lfX);
	void ViewportY(float lfY);
	void ViewportWidth(float lfWidth);
	void ViewportHeight(float lfHeight);

	void ViewportProportional(float lfX,float lfY,float lfWidth,float lfHeight);
	void ViewportProportionalWidth(float lfWidth);
	void ViewportProportionalHeight(float lfHeight);
	void ViewportProportionalX(float lfX);
	void ViewportProportionalY(float lfY);

float ViewportProportionalWidth();
float ViewportProportionalHeight();
float ViewportProportionalX();
float ViewportProportionalY();

	void Proportional(bool lbSet);
	bool Proportional();
	void ClearViewport();
		/**
	* \brief This function will set the color the camera will clear the screen to every frame.
	* \param lfRed This is the red component of the color that cCamera will clear the screen to.
	* \param lfGreen This is the green component of the color that cCamera will clear the screen to.
	* \param lfBlue This is the blue component of the color that cCamera will clear the screen to.
	* \param lfAlpha This is the alpha component of the color that cCamera will clear the screen to.
	* This function sets the color that the camera will clear the screen to every frame. RGB defines the color
	* while lfAlpha sets the translucency of the screen clear - this can be used to leave screen echos.
	*/
	void ClearColor(float lfRed=0.0f,float lfGreen=0.0f,float lfBlue=0.0f,float lfAlpha=1.0f);
	/// See cCamera::ClearColor(float,float,float,float);
	void ClearColor(float *lpColor);
	/// See cCamera::ClearColor(float,float,float,float);
	void ClearColor(cRGBA &lpColor);
	/// See cCamera::ClearColor(float,float,float,float);
	void ClearColor(cRGB &lpColor);
	/// See cCamera::ClearColor(float,float,float,float);
	void ClearColor(cRGBA *lpColor);
	/// See cCamera::ClearColor(float,float,float,float);
	void ClearColor(cRGB *lpColor);
	/// See cCamera::ClearColor(float,float,float,float);
	cRGBA ClearColor();

	void UpdateViewport();
	virtual void UpdateWindowSize()=0;
};

class cPerspectiveControl : public cCameraMatrix4, public cViewportControl
{
protected:
	/// This object builds and controls the Perspective Matrix for the system.
cPerspectiveMatrix mmPerspective;
///This controls the projection matrix for 2D objects. Best not to play with.
cPerspectiveMatrix mmPerspective2D;

static cMatrix4 mmCombined;
static cMatrix4 mmCamera;
static cMatrix4 mmProjection;
static cMatrix4 mm2DProjection;


public:

	cPerspectiveControl();

	/// This will return the closest distance cCamera will render polygons.
	virtual float Near();
	/// This will return the Furthest distance cCamera will render polygons.
	virtual float Far();

	/// This will set the closest distance cCamera will render polygons.
	virtual void Near(float lfN);
	/// This will set the Furthest distance cCamera will render polygons.
	virtual void Far(float lfF);

	///This will set the width of the closest viewing space.
	virtual void Width(float lfZoom);
	///This will return the width of the closest viewing space.
	virtual float Width();

	///This will set the height of the closest viewing space.
	virtual void Height(float lfHeight);
	///This will return the height of the closest viewing space.
	virtual float Height();

	///This will set the ratio of the closest viewing space (Height will equal Width * Ratio).
	virtual void Ratio(float lfRatio);
	///This will return the ratio of the closest viewing space.
	virtual float Ratio();

	// This will set the Current GL Matrix to be equivalent to the Camera matrix (essentially produces a Global Positioning Matrix).
	void ResetGLMatrix();

	static float *CameraMatrix();
	static float *CombinedMatrix();
	static float *ProjectionMatrix();
	static float *Projection2DMatrix();


	void UpdateWindowSize();

		/// This creates the camera model view matrix using an Orthographic algorithm.
	virtual void UpdateProjectionMatrix();

};


#endif
