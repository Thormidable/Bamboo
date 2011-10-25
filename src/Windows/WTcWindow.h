#ifndef __CWINDOW_H__
#define __CWINDOW_H__


/**
* \brief This class will create control and destroy desktop windows.
* This is ugly and disgusting. It will create new windows, link the window with OpenGL
* and do basic event handling. This is the users access to interact with the OS.
* Note it is all very OS specific.
*/
class cWindow
{
public:
#if WT_OS_TYPE==OS_WIN32
	WNDCLASSEX wcex;
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	/// This will create a new cWindow class. Create a desktop window and InitialiseOpenGL(). This is Windows OS only.
	cWindow(HINSTANCE lphInstance);
#endif

#if WT_OS_TYPE==OS_LINUX
	Display *lpDisplay;
	static int DisplayAttributes[5];
	XVisualInfo* VisualInfo;
	GLXContext glContext;
	XSetWindowAttributes WindowAttributes;
	XWindowAttributes gwa;
	Window lWindow,lRoot;
	XEvent Event;
 	/// This will create a new cWindow class. Create a desktop window and InitialiseOpenGL(). This is Linux OS only.
	cWindow();

	/// This will move the mouse cursor to the position liX,liY in the current window. see _MOUSE
	void MovePointer(uint32 liX,uint32 liY);
	/// This will update the current mouse speeds. see _MOUSE
	void GetMouseSpeed();
#endif
	/// This is a flag telling the system if it is quitting or should quit.
          bool mbQuit;
	/// This is the window current X position on the desktop in pixels.
	int X;
	/// This is the windows current Y position on the desktop in pixels.
	int Y;
	/// This is the windows current width in pixels.
	int Width;
	/// This is the windows current height in pixels.
	int Height;
	/// This is a flag telling the system if the window has been resized and so if the context needs updating.
          bool Resized;
	/// This is a flag telling the system if the window has been moved.
          bool Moved;
	/// This is a flag telling the system if the window is hidden or not.
          bool Hidden;
	/// This is a flag telling the system that the window requires repainting (updating)
          bool Repaint;
	/// This is a float storing the ratio of the window to avoid distorting the view.
          float mfRatio;

	~cWindow();

	/// This will return mfRatio.
	float Ratio();
	/// This will create the window object and initialise it.
	void StartWindow();
	/// This will create the OpenGL context and enable OpenGL.
	void EnableOpenGL();

	/// This will prepare the Rendering matrix and other OpenGL initialisations.
	void InitialiseOpenGL();

	/// This will do NOTHING.
	void EnableInput();
	/// This will do NOTHING.
	void DisableInput();

	/// This will Move the window to position liX,liY (in pixels) on the desktop.
	void Move(short liX,short liY);
	/// This will resize the window to size liX,liY (in pixels).
	void Resize(short liX,short liY);

	/// This will make this context the current one (to recieve rendering data).
	void MakeCurrent();

	/// This is an interupt function that will handle messages from the OS.
	void HandleMessages();
	/// This will handle changes to the window (from the OS).
	void HandleChanges();


};

#if WT_OS_TYPE==OS_WIN32

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam);
#endif


#endif
