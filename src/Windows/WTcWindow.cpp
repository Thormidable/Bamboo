#include "../WTDivWin.h"

void cWindow::InitialiseOpenGL()
{
	StartWindow();
	EnableOpenGL();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
}

#if WT_OS_TYPE==OS_WIN32

void cWindow::HandleChanges()
{
	if (Resized)
	{
		wglDeleteContext( hRC );
		hRC = wglCreateContext( hDC );
		wglMakeCurrent( hDC, hRC );
		cCamera::Instance()->UpdateProjectionMatrix();
	}
	Resized=false;
}

void cWindow::EnableInput()
{
	EnableWindow(hWnd,1);
}

void cWindow::DisableInput()
{
	EnableWindow(hWnd,0);
}

void cWindow::Move(short liX,short liY)
{
	MoveWindow(hWnd,liX,liY,Width,Height,0);
}

void cWindow::Resize(short liX,short liY)
{
	MoveWindow(hWnd,X,Y,liX,liY,0);
}

cWindow::~cWindow()
{
	trace("Remove Current Context");
	wglMakeCurrent (NULL, NULL);
	trace("Delete Windows Context");
	wglDeleteContext (hRC);
	trace("Release the DC");
	ReleaseDC (hWnd, hDC);
	trace("Destroy the current OS's window");
	DestroyWindow (hWnd);
}

cWindow::cWindow(HINSTANCE lphInstance)
{
    mbQuit=false;
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

    wc.lpfnWndProc = RecieveEvent;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance =lphInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";

    RegisterClass (&wc);
    Hidden=true;
    Resized=false;
    Moved=false;

}


void cWindow::StartWindow()
{
	hWnd=CreateWindow(
		wc.lpszClassName, "DivWin",
		WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE | WS_SIZEBOX,
		//WS_OVERLAPPEDWINDOW
		0, 0, 800, 600,
		NULL, NULL, wc.hInstance, NULL);
		X=Y=0;
		Width=800;
		Height=600;
		Hidden=false;
		//Changed=false;
		Resized=false;
		Moved=false;

	InitialiseOpenGL();
}

void cWindow::EnableOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	/* get the device context (DC) */
	hDC = GetDC (hWnd);

	/* set the pixel format for the DC */
	ZeroMemory (&pfd, sizeof (pfd));
	pfd.nSize = sizeof (pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
	PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	iFormat = ChoosePixelFormat (hDC, &pfd);
	SetPixelFormat (hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	hRC = wglCreateContext( hDC );
	wglMakeCurrent( hDC, hRC );
}

void cWindow::MakeCurrent()
{
	wglMakeCurrent( hDC,hRC);
}

void cWindow::HandleMessages()
{
	if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
	{

		TranslateMessage (&msg);
		DispatchMessage (&msg);

	}
}

LRESULT CALLBACK RecieveEvent(	HWND hWnd, UINT message,
								WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
    case WM_CREATE:
        return 0;

    case WM_CLOSE:
         gpWindow->mbQuit=true;
//        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_PAINT:
         gpWindow->Repaint=true;
         return 0;


    case WM_SIZE:
         if (wParam==SIZE_RESTORED)
         {
          gpWindow->Width=LOWORD(lParam);
          gpWindow->Height=HIWORD(lParam);
          gpWindow->Resized=true;
          gpWindow->mfRatio=((float)gpWindow->Height)/gpWindow->Width;
          return 0;
         }
        return 0;

    case WM_SIZING:
         return 0;

    case WM_MOVE:
         gpWindow->X=LOWORD(lParam);
         gpWindow->Y=HIWORD(lParam);
         gpWindow->Moved=true;
         return 0;

    case WM_MOUSEMOVE:
         if (!_MOUSE.locked)
         {/*
          _MOUSE.cx=(int)LOWORD(lParam);
          _MOUSE.cy=(int)HIWORD(lParam);
	  */
	 _MOUSE.x+=(int)LOWORD(lParam);
         _MOUSE.y+=(int)HIWORD(lParam);
         }
         return 0;

    case WM_LBUTTONDOWN:
         _MOUSE.left=true;
         return 0;

    case WM_LBUTTONUP:
         _MOUSE.left=false;
         return 0;

    case WM_RBUTTONDOWN:
         _MOUSE.right=true;
         return 0;

    case WM_RBUTTONUP:
         _MOUSE.right=false;
         return 0;

    case WM_KEYDOWN:
        cEventHandler::Instance()->Key.SetKeyState(true,wParam);
       return 0;

    case WM_KEYUP:
         cEventHandler::Instance()->Key.SetKeyState(false,wParam);
         return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}
#endif

float cWindow::Ratio() {return mfRatio;}

#if WT_OS_TYPE==OS_LINUX

int cWindow::DisplayAttributes[]={ GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

cWindow::cWindow()
{

mbQuit=0;
X=0;
Y=0;
Width=800;
Height=600;
Resized=false;
Moved=false;
Hidden=true;
Repaint=false;
mfRatio=((float)Height)/Width;;

lpDisplay=XOpenDisplay(0);
lRoot=DefaultRootWindow(lpDisplay);

//XVisualInfo* glXChooseVisual(Display *dpy, int screen, int *attribList)
VisualInfo=glXChooseVisual(lpDisplay,0,DisplayAttributes);

WindowAttributes.colormap = XCreateColormap(lpDisplay, lRoot,VisualInfo->visual, AllocNone);
WindowAttributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask | PointerMotionMask;

InitialiseOpenGL();
}

cWindow::~cWindow()
{
	trace("Stop this windows context from being current");
	printf("Display : %p\n",lpDisplay);
	glXMakeCurrent(lpDisplay, None, NULL);
	trace("Destroy this windows context");
	glXDestroyContext(lpDisplay, glContext);
	trace("Destroy this windows Window");
	XDestroyWindow(lpDisplay, lWindow);
	trace("Close the Display");
	XCloseDisplay(lpDisplay);

}

void cWindow::StartWindow()
{
 lWindow = XCreateWindow(lpDisplay, lRoot, 0, 0, Width,
                        Height, 0, VisualInfo->depth, InputOutput, VisualInfo->visual,
                        CWBorderPixel|CWColormap|CWEventMask, &WindowAttributes);

 XMapWindow(lpDisplay, lWindow);
 XStoreName(lpDisplay, lWindow, "GLDivWin");
}

void cWindow::EnableOpenGL()
{

 glContext = glXCreateContext(lpDisplay, VisualInfo, NULL, GL_TRUE);
 glXMakeCurrent(lpDisplay, lWindow, glContext);
}

void cWindow::EnableInput(){}
void cWindow::DisableInput(){}

void cWindow::Move(short liX,short liY){(void)liX;(void)liY;}
void cWindow::Resize(short liX,short liY){(void)liX;(void)liY;}

void cWindow::MakeCurrent()
{
glXMakeCurrent(lpDisplay, lWindow, glContext);
}

void cWindow::HandleMessages()
{
 	while(XPending(lpDisplay))
	{
		XNextEvent(lpDisplay, &Event);
        	if(Event.type == Expose)
		{
			XGetWindowAttributes(lpDisplay, lWindow, &gwa);
			glViewport(0, 0, gwa.width, gwa.height);
			glXSwapBuffers(lpDisplay, lWindow);
		break;
		}
		//Key stuff

		if(Event.type == KeyPress)
		{
		  uint32 liKeySym=XLookupKeysym(&Event.xkey,0);
		  (cEventHandler::Instance()->Key.SetArray((liKeySym & 0xFF00) == 0xFF00,liKeySym & 0xFF))[0]=true; break;
		}
		if(Event.type == KeyRelease)
		{
		  uint32 liKeySym=XLookupKeysym(&Event.xkey,0);
		  (cEventHandler::Instance()->Key.SetArray((liKeySym & 0xFF00) == 0xFF00,liKeySym & 0xFF))[0]=false; break;
		}


		//Mouse Stuff
		if(Event.type == ButtonPress)
		{
			if(Event.xbutton.button==1) _MOUSE.left=true;
			if(Event.xbutton.button==3) _MOUSE.right=true;
			if(Event.xbutton.button==2) _MOUSE.middle=true;
			break;
		}
		if(Event.type == ButtonRelease)
		{
			if(Event.xbutton.button==1) _MOUSE.left=false;
			if(Event.xbutton.button==3) _MOUSE.right=false;
			if(Event.xbutton.button==2) _MOUSE.middle=false;
			break;
		}
		if(Event.type == MotionNotify)
		{
				_MOUSE.cx=Event.xmotion.x;
				_MOUSE.cy=Event.xmotion.y;
			break;
		}
		if(Event.type == ConfigureNotify)
		{
			gpWindow->X=Event.xconfigure.x;
			gpWindow->Y=Event.xconfigure.y;
			gpWindow->Width=Event.xconfigure.width;
			gpWindow->Height=Event.xconfigure.height;
			gpWindow->Moved=true;
			gpWindow->Resized=true;
			gpWindow->mfRatio=((float)gpWindow->Height)/gpWindow->Width;
			break;
		}
		if(Event.type == DestroyNotify)
		{
			gpWindow->mbQuit=true;
			break;
		}
}
}

void cWindow::HandleChanges()
{
 if(Resized)
{
	cCamera::Instance()->UpdateProjectionMatrix();
}
}

void cWindow::MovePointer(uint32 liX,uint32 liY)
{
XWarpPointer(lpDisplay,None,lWindow,0,0,0,0,liX,liY);
}

void cWindow::GetMouseSpeed()
{
 Window lpRootWin,lpChildWin;
 int liRX,liRY,liWX,liWY;
 unsigned int liMask;
	if (XQueryPointer(lpDisplay,lWindow,&lpRootWin,&lpChildWin,&liRX,&liRY,&liWX,&liWY,&liMask))
	{
		_MOUSE.xs=liWX-_MOUSE.cx;
		_MOUSE.ys=liWY-_MOUSE.cy;
	}

}

#endif
