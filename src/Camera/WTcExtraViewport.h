#ifndef __WTCEXTRAVIEWPORT_H__
#define __WTCEXTRAVIEWPORT_H__

class cViewportHandler;

/**
* \brief cViewport allows a cCameras Render List to be rendered again from another position and rotation.
* cViewport are owned by cCamera and will render the cCamera s Render List again every frame.
* The cViewport s position and rotation can be set in exactly the same way as a camera.
* The area on the screen the cViewport renders to can be set by cViewportControl.
* The Position and perspective matrices used for rendering are set by cPerspectiveControl.
* When created, the cViewport will default to the first cCamera.
* It can be set to use a different cCamera s Renderlist on creation by passing it a pointer to the cCamera it should be a member of.
*/
class cViewport: public cPerspectiveControl, public cSignal
{
	cViewportHandler *mpHandler;
public:
    ///Constructor. This will default to the camera _CAMERA
	cViewport();
	///Constructor. This will become a member of the cCamera pointed to by lpCamera. It will render lpCameras Render List.
	cViewport(cCamera *lpCamera);
	~cViewport();

	void Render();
	void UpdateRenderSettings();
	void Stop();

	void PrepareForRender();
	void UpdateProjectionMatrix();

};
/*
* \brief cViewportHandler is a class for controlling a list of cViewportHandler.
* cViewportHandler is owned by a cCamera object and controlls the list of cViewport Objects
*
*/
class cViewportHandler
{
	cCamera *mpCamera;
	cLimitedPointerList<cViewport> mcList;
	cViewportHandler(cCamera *lpCamera,uint8 liViewports);
 	void Render();
public:

	void Add(cViewport *lpNew);
	void Remove(cViewport *lpOld);
	void UpdateWindowSize();
	friend class cCamera;

};


#endif
