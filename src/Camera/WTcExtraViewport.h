#ifndef __WTCEXTRAVIEWPORT_H__
#define __WTCEXTRAVIEWPORT_H__

class cViewportHandler;

class cExtraViewport: public cPerspectiveControl, public cSignal
{
	cViewportHandler *mpHandler;
public:
	cExtraViewport();
	cExtraViewport(cCamera *lpCamera);
	~cExtraViewport();
	void Render();
	void UpdateRenderSettings();
	void Stop();

	void PrepareForRender();
	void UpdateProjectionMatrix();

};

class cViewportHandler
{
	cCamera *mpCamera;
	cLimitedPointerList<cExtraViewport> mcList;
	cViewportHandler(cCamera *lpCamera,uint8 liViewports);
 	void Render();
public:

	void Add(cExtraViewport *lpNew);
	void Remove(cExtraViewport *lpOld);
	void UpdateWindowSize();
	friend class cCamera;

};


#endif
