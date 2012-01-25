#ifndef __WTCCAMERA_H__
#define __WTCCAMERA_H__

class cRenderNode;
class cParticleHandler;
class cPainter;

/**
*\brief This class will control the rendering of the render tree. It will handle all the render objects and how to render to the screen.
* cCamera is the renderer for a single Render List. It will contain a scene graph, and inherits cPerspectiveControl and cSignal. It also inherits cViewportControl and cCameraMatrix4 through cPerspectiveControl
* It can be considered as a set of renderable objects with a camera, and will render every thing in its scene graph to the screen.
* It will not render any objects in another cCamera's scene graph.
* cRenderObjects and those inheriting it can be passed a cCamera as a parameter on creation to make them exist in the camera.
* cViewports can be created which will render the same scene graph as their owning cCamera object but from another perspective.
* The cCamera object renders first, followed by the cViewport objects in the order they were created.
* cCamera objects can be positioned and rotated using the functions in cCameraMatrix4.
* The region of the screen it renders to (the viewport) is set using the functions in cViewportControl.
* The perspective (field of view etc) is set by the functions in cPerspectiveControl.
*/
class cCamera : public cPerspectiveControl, public cSignal
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
	cPainter *mpPainter;

	void UpdateRenderSettings();
	void UpdateRenderState();
	void RecalculateTotalMatrices();
	void RenderObjects();
	void RecalculateAllMatrices();
	cParticleHandler *mpParticleHandler;

private:

public:
	cCamera();
	// This is cCameras destructor and will delete the entire scene graph stored in mpRenderList.
	~cCamera();

	/// This function will return a pointer to the first cCamera object. This can be accessed by calling tjhe macro _CAMERA.
	static cCamera *Instance();
	// This function will automatically remove all cRenderObjects from the scene graph pointed to by mpRenderList.
	void RemoveAll();

	// This function will render the scene graph to the screen. It will build a list of objects to be rendered. It will then sort, process and render them for optimal performance.
	virtual void Render();
	//This function will update cache matrices and other important background information but will not render.
	virtual void UpdateNotRender();

	/// This will return a pointer to the scene graph.
	cRenderNode *RenderList();

	/// This will return a virtual pointer to the the scene graph.
	vRenderObject *vRenderList();

	void UpdateWindowSize();
    ///Function for performing cCamera specific actions after receiving a kill signal from via cSignal::Signal(SIGNAL).
	void Stop();

    ///Function for returning a pointer to the cParticleHandler for this cCamera.
	cParticleHandler *ParticleHandler();
	cPainter *Painter();
	friend class cViewportHandler;
	friend class cViewport;

};
/**
* \brief This class is designed to own and control multiple cCamera objects.
* All cCamera objects are owned by this class. The cCameras are rendered in the order they were created and will render ontop of any previous cCamera objects.

*/
class cCameraHandler
{
	static cCameraHandler *mpInstance;
	cLimitedPointerList<cCamera> mcList;
	cCameraHandler();
public:
	static cCameraHandler *Instance();
	void Add(cCamera *lpCamera);
	void Remove(cCamera *lpCamera);
	void RenderCameras();
	void UpdateNotRenderCameras();
	void UpdateWindowSize();
	void UpdateScreen();
};

#endif
