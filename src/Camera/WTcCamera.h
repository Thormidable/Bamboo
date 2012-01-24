#ifndef __WTCCAMERA_H__
#define __WTCCAMERA_H__

class cRenderNode;
class cViewportHandler;
class cExtraViewport;

class cViewportControl
{
protected:
 float mfViewportX,mfViewportY;
 float mfViewportWidth,mfViewportHeight;
 cRGBA mcClearColor;

 void SetClearColor();

public:

	cViewportControl();
	cViewportControl(float lfX,float lfY,float lfWidth,float lfHeight);
	void Viewport(float lfX,float lfY,float lfWidth,float lfHeight);
	void ViewportX(float lfX);
	void ViewportY(float lfY);
	void ViewportWidth(float lfWidth);
	void ViewportHeight(float lfHeight);

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

		/// This creates the camera model view matrix using an Orthographic algorithm.
	virtual void UpdateProjectionMatrix();

};

/**
*\brief This class will control the rendering of the render tree. It will handle all the render objects and how to render to the screen.
* cCamera is the renderer for the entire program. It will contain a scene graph, and inherits cCameraMatrix4 as its view
* matrix. It can be considered as a camera in the program space, and will render every thing in its scene graph to the screen.
*/
class cCamera : public cPerspectiveControl
{
protected:


// This stores the current instance of cCamera. This means that only one cCamera object will exist at any one time. This is returned by cCamera::Instance(). Future expansions will allow multiple cCamera objects.
static cCamera *mpInstance;

	/*
	* This points to the top level cRenderNode. This is the start of the scene graph and any cMatrix4 translations made
	* to the cRenderNode in this pointer will affect the entire scene graph.
	*/
    cRenderNode *mpRenderList;
	cViewportHandler *mpViewportHandler;

	void UpdateRenderSettings();
	void UpdateRenderState();
	void RecalculateTotalMatrices();
	void RenderObjects();
	void UpdateScreen();
	void RecalculateAllMatrices();

private:
// This should NEVER be called by the user. Use cCamera::Instance() instead.
	cCamera();
public:
	/// This is cCameras destructor and will delete the entire scene graph stored in mpRenderList.
	~cCamera();

	/// This function will return a pointer to the current cCamera object. This can be accessed by calling tjhe macro _CAMERA.
	static cCamera *Instance();
	/// This function will automatically remove all cRenderObjects from the scene graph pointed to by mpRenderList.
	void RemoveAll();

	/// This function will render the scene graph to the screen. It will build a list of objects to be rendered. It will then sort, process and render them for optimal performance.
	virtual void Render();
	///This function will update cache matrices and other important background information but will not render.
	virtual void UpdateNotRender();





	/// This will return a pointer to the scene graph.
	cRenderNode *RenderList();

	/// This will return a virtual pointer to the the scene graph.
	vRenderObject *vRenderList();

	void UpdateProjectionMatrix();



	friend class cViewportHandler;
	friend class cExtraViewport;

};



#endif
