#ifndef __WTCCAMERA_H__
#define __WTCCAMERA_H__

class cRenderNode;
class cParticleHandler;
class cPainter;

/**
*\brief This class will control the rendering of the render tree. It will handle all the render objects and how to render to the screen.
* cCamera is the renderer for the entire program. It will contain a scene graph, and inherits cCameraMatrix4 as its view
* matrix. It can be considered as a camera in the program space, and will render every thing in its scene graph to the screen.
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
	/// This is cCameras destructor and will delete the entire scene graph stored in mpRenderList.
	~cCamera();

	/// This function will return a pointer to the first cCamera object. This can be accessed by calling tjhe macro _CAMERA.
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

	void UpdateWindowSize();

	void Stop();

	cParticleHandler *ParticleHandler();
	cPainter *Painter();
	friend class cViewportHandler;
	friend class cExtraViewport;

};

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
