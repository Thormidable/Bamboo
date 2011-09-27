#ifndef __WTCCAMERA_H__
#define __WTCCAMERA_H__

class cRenderNode;

/** 
*\brief This class will control the rendering of the render tree. It will handle all the render objects and how to render to the screen.
* cCamera is the renderer for the entire program. It will contain a scene graph, and inherits cCameraMatrix4 as its view 
* matrix. It can be considered as a camera in the program space, and will render every thing in its scene graph to the screen.
*/
class cCamera : public cCameraMatrix4
{
protected:
// This stores the current instance of cCamera. This means that only one cCamera object will exist at any one time. This is returned by cCamera::Instance(). Future expansions will allow multiple cCamera objects.
static cCamera *mpInstance;

	// This variable can be thought of as the lens effect. 0.5f - 1.0f can be considered normal. 0.1f -0.5f is a fisheye lens.
       float mfZoom;
 	// This variable stores the closest that cCamera will render polygons.
       	float mfNear;
	// This variable stores the furthest that cCamera will render polygons.
	float mfFar;

	/* 
	* This points to the top level cRenderNode. This is the start of the scene graph and any cMatrix4 translations made
	* to the cRenderNode in this pointer will affect the entire scene graph. 
	*/
       cRenderNode *mpRenderList;

// This should NEVER be called by the user. Use cCamera::Instance() instead.
	cCamera();
public:
	/// This is cCameras destructor and will delete the entire scene graph stored in mpRenderList.
	~cCamera();
	/** 
	* This function will return a pointer to the current cCamera object.
	*/
	static cCamera *Instance();
	/// This function will automatically remove all cRenderObjects from the scene graph pointed to by mpRenderList.
	void RemoveAll();

	/// This function will render the scene graph to the screen. This is used if WT_USE_PAINTER is set to false.
	virtual void Render();

	/**
	* \brief This function will set the color the camera will clear the screen to every frame.
	* \param lfRed This is the red component of the color that cCamera will clear the screen to.
	* \param lfGreen This is the green component of the color that cCamera will clear the screen to.
	* \param lfBlue This is the blue component of the color that cCamera will clear the screen to.
	* \param lfAlpha This is the alpha component of the color that cCamera will clear the screen to.
	* This function sets the color that the camera will clear the screen to every frame. RGB defines the color
	* while lfAlpha sets the translucency of the screen clear - this can be used to leave screen echos.
	*/
	void SetClearColor(float lfRed,float lfGreen,float lfBlue,float lfAlpha);
	
	/// This creates the camera model view matrix using an Orthographic algorithm.
	void Orthographic();
	/// This creates the camera model view matrix using a Frustum algorithm.
	void Frustum();
	
	/// This will return a pointer to the scene graph.
	cRenderNode *RenderList();
	
	/// This will return a virtual pointer to the the scene graph.
	vRenderObject *vRenderList();
	
	/// This will return the closest distance cCamera will render polygons.
	float Near();
	/// This will return the Furthest distance cCamera will render polygons.
	float Far();

	/// This will set the closest distance cCamera will render polygons.
	void Near(float lfN);
	/// This will set the Furthest distance cCamera will render polygons.
	void Far(float lfF);

	// This will set the Current GL Matrix to be equivalent to the Camera matrix (essentially produces a Global Positioning Matrix).
	void ResetGLMatrix();
};


class cCameraPainter : public cCamera
{
	cCameraPainter();
public:
	/// This function will render the scene graph to cPainter instead of the screen.  This is used if WT_USE_PAINTER is set to true.
	void Render();
	friend class cCamera;
};
#endif
