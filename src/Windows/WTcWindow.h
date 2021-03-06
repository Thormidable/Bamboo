#ifndef __CWINDOW_H__
#define __CWINDOW_H__


/**
* \brief This class will create control and destroy desktop windows.
* This will create new windows, link the window with OpenGL
* and do basic event handling. This is the users access to interact with the OS.
* Note it is all very OS specific.
*/
class cWindow
{
    uint8 miBorderThickness;
    uint8 miTitleBarHeight;
    uint32 miRenderWidth;
    uint32 miRenderHeight;
    uint32 miRenderX;
    uint32 miRenderY;
	// This is the window current X position on the desktop in pixels.
	uint16 miWindowX;
	// This is the windows current Y position on the desktop in pixels.
	uint16 miWindowY;
	// This is the windows current width in pixels.
	uint16 miWindowWidth;
	// This is the windows current height in pixels.
	uint16 miWindowHeight;
	//Inverse value for window width.
	float32 miInvWindowWidth;
	//Inverse value for window width.
	float32 miInvWindowHeight;
		// This is a flag telling the system if the window has been resized and so if the context needs updating.
          bool Resized;
	// This is a flag telling the system if the window has been moved.
          //bool Moved;
	// This is a flag telling the system if the window is hidden or not.
          bool Hidden;

	// This is a float storing the ratio of the window to avoid distorting the view.
          float32 mfRenderRatio;

          float32 mfWindowRatio;

public:
// This is a flag telling the system that the window requires repainting (updating)
          bool Repaint;
#if WT_OS_TYPE==OS_WIN32
	WNDCLASSEX wcex;
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	/// This will create a new cWindow class. Create a desktop window and InitialiseOpenGL(). This is Windows OS only.
	cWindow(HINSTANCE lphInstance);

	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam);
    void GrabMouse();
#endif

		///This will return the height of the Title bar in pixels. This is Windows only.
    uint32 TitleBarHeight();
    ///This will return the size of the window border in pixels. This is Windows only.
    uint32 BorderThickness();

#if WT_OS_TYPE==OS_LINUX
	Display *lpDisplay;
	static int DisplayAttributes[];
	XVisualInfo* VisualInfo;
	GLXContext glContext;
	XSetWindowAttributes WindowAttributes;
	XWindowAttributes gwa;
	Window lWindow,lRoot;
	XEvent Event;
 	/// This will create a new cWindow class. Create a desktop window and InitialiseOpenGL(). This is Linux OS only.
	cWindow();

	/// This will move the mouse cursor to the position liX,liY in the current window. see cMouse. This is Linux OS only.
	void MovePointer(uint32 liX,uint32 liY);
	// This will update the current mouse speeds. see _MOUSE
	void GetMouseSpeed();

	void GrabMouse();
#endif
	// This is a flag telling the system if it is quitting or should quit.
          bool mbQuit;

	/// This is the window current X position on the desktop in pixels.
	uint16 WindowX();
	/// This is the windows current Y position on the desktop in pixels.
	uint16 WindowY();
	/// This is the windows current width in pixels.
	uint16 WindowWidth();
	/// This is the windows current height in pixels.
	uint16 WindowHeight();
	///Inverse value for window width.
	float32 InvWindowWidth();
	///Inverse value for window width.
	float32 InvWindowHeight();

	/// This will return the Windows Width Height Ratio.
	float WindowRatio();

    ///This will return the render Areas Width Height Ratio.
	float RenderRatio();


	~cWindow();

	// This will create the window object and initialise it.
	void StartWindow();
	// This will create the OpenGL context and enable OpenGL.
	void EnableOpenGL();

	// This will prepare the Rendering matrix and other OpenGL initialisations.
	void InitialiseOpenGL();

	// This will do NOTHING.
	void EnableInput();
	// This will do NOTHING.
	void DisableInput();

	/// This will Move the window to position liX,liY (in pixels) on the desktop.
	void Move(short liX,short liY);
	/// This will resize the window to size liX,liY (in pixels).
	void Resize(short liX,short liY);

	// This will make this context the current one (to recieve rendering data).
	void MakeCurrent();

	// This is an interupt function that will handle messages from the OS.
	void HandleMessages();
	// This will handle changes to the window (from the OS).
	void HandleChanges();

    void FindRenderArea();
	///This will return the render Areas width supplied by the OS (May be different to Window Width)
    uint32 RenderAreaWidth();
	///This will return the render Areas height supplied by the OS (May be different to Window Height)
    uint32 RenderAreaHeight();
    ///This will return the render Areas X Position supplied by the OS (May be different to Window X)
    uint32 RenderAreaX();
	///This will return the render Areas Y Position supplied by the OS (May be different to Window Y)
    uint32 RenderAreaY();

    friend class cCamera;
    friend class cCameraPainter;


};

#if WT_OS_TYPE==OS_WIN32

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam);
#endif

void CreateConsole();

#endif
