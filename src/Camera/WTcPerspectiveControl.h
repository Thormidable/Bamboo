#ifndef __WTCPERSPECTIVECONTROL_H__
#define __WTCPERSPECTIVECONTROL_H__

class cViewportHandler;
class cExtraViewport;

/**
 \brief The cViewportControl allows the user to control the region of the screen a cCamera or cViewport object will render to.
 This class allows the user to set a region of the screen for a cCamera or cViewport to render to.
 It can be either Proportional to screens width and height or Fixed.
 If the region is proportional the co-ordinates and sizes of the region are in the range 0.0f to 1.0f representing 0 up to the entire screen size.
 If the region is fixed the co-ordinates and sizes of the region are measured in pixels.
 The X and Y Co-ordinates specify the Lower Left corner of the region. The width and height determine the size of the region.
 */
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
    //Constructor to create a new cViewportControl
	cViewportControl();
	cViewportControl(float lfX,float lfY,float lfWidth,float lfHeight);
	cViewportControl(float lfX,float lfY,float lfWidth,float lfHeight, bool lbProportional);

    /// This will set the fixed size of a cViewport Control. Takes X,Y, Width and Height.
	void Viewport(float lfX,float lfY,float lfWidth,float lfHeight);
	/// This will set the X Co-ordinate of the Viewport.
	void ViewportX(float lfX);
	/// This will set the Y Co-ordinate of the Viewport.
	void ViewportY(float lfY);
	/// This will set the Width of the Viewport.
	void ViewportWidth(float lfWidth);
	/// This will set the Height of the Viewport.
	void ViewportHeight(float lfHeight);

    /// This will set the proportional size of a cViewport Control. Takes X,Y, Width and Height.
	void ViewportProportional(float lfX,float lfY,float lfWidth,float lfHeight);
	/// This will set the proportional Width of the Viewport.
	void ViewportProportionalWidth(float lfWidth);
	/// This will set the proportional Height of the Viewport.
	void ViewportProportionalHeight(float lfHeight);
	/// This will set the proportional X Co-ordinate of the Viewport.
	void ViewportProportionalX(float lfX);
	/// This will set the proportional Y Co-ordinate of the Viewport.
	void ViewportProportionalY(float lfY);
///This will return the Proportional Width of the Viewport region.
float ViewportProportionalWidth();
///This will return the Proportional Height of the Viewport region.
float ViewportProportionalHeight();
///This will return the Proportional X Co-ordinate of the Viewport region.
float ViewportProportionalX();
///This will return the Proportional Y Co-ordinate of the Viewport region.
float ViewportProportionalY();

///This will return the Width of the Viewports region.
float ViewportWidth();
///This will return the Height of the Viewports region.
float ViewportHeight();
///This will return the X Co-ordinate of the Viewports region.
float ViewportX();
///This will return the Y Co-ordinate of the Viewports region.
float ViewportY();

    ///This will turn on or off the use of Proportional co-ordinate systems.
	void Proportional(bool lbSet);
	///This will return whether proportional co-ordinate systems are being used or not.
	bool Proportional();

	void ClearViewport();
		/**
	* \brief This function will set the color the Viewport will clear the region to every frame.
	* \param lfRed This is the red component of the color that a Viewport will clear the region to.
	* \param lfGreen This is the green component of the color that a Viewport will clear the region to.
	* \param lfBlue This is the blue component of the color that cCamera will clear the region to.
	* \param lfAlpha This is the alpha component of the color that cCamera will clear the region to.
	* This function sets the color that the camera will clear the screen to every frame. RGB defines the color.
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

/**
 \brief cPerspectiveControl affects how a cViewport or cCamera will render its view.
 This can be imagined as a lens. The user can set the field of view, both in width and height.
 You can set a near and far clipping plane. Adjustments to the parameters will only take effect after the function cPerspectiveControl::UpdateProjectionMatrix() is called.
*/
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

    /// This Updates the perspective matrices with the specified parameters.
	virtual void UpdateProjectionMatrix();

};


#endif
