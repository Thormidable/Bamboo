

#include "../WTBamboo.h"


uint32 cWindow::RenderAreaX(){return miRenderX;}
uint32 cWindow::RenderAreaY(){return miRenderY;}

uint32 cWindow::RenderAreaWidth(){return miRenderWidth;}
uint32 cWindow::RenderAreaHeight(){return miRenderHeight;}


void cWindow::InitialiseOpenGL()
{
    StartWindow();
    EnableOpenGL();

    _CAMERA->UpdateProjectionMatrix();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_MODULATE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glFrontFace(GL_CW);

	glShadeModel(GL_SMOOTH);

	FindRenderArea();

}

#if WT_OS_TYPE==OS_WIN32

void cWindow::FindRenderArea()
{

    RECT Result;
    GetClientRect(hWnd,&Result);
    miRenderWidth=Result.right;
    miRenderHeight=Result.bottom;
/*
    GetWindowRect(hWnd,&Result);
    miWindowWidth=Result.right-Result.left;
    miWindowHeight=Result.bottom-Result.top;
*/
    POINT lcPoint;
    lcPoint.x=0;
    lcPoint.y=0;
    ClientToScreen(hWnd,&lcPoint);
    miRenderX=lcPoint.x;
    miRenderY=lcPoint.y;

    miBorderThickness=(miWindowWidth-miRenderWidth)*0.5f;
    miTitleBarHeight=(miWindowHeight-miRenderHeight)-miBorderThickness;

}


void cWindow::HandleChanges()
{
	if (Resized)
	{
		wglDeleteContext( hRC );
        hRC = wglCreateContext( hDC );
		wglMakeCurrent( hDC, hRC );
		_CAMERA->UpdateProjectionMatrix();
		FindRenderArea();
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
	MoveWindow(hWnd,liX,liY,miWindowWidth,miWindowHeight,0);
}

void cWindow::Resize(short liX,short liY)
{
    miWindowWidth=liX;
    miWindowHeight=liY;
    miInvWindowWidth=1.0f/miWindowWidth;
    miInvWindowHeight=1.0f/miWindowHeight;
    mfWindowRatio=((float)miWindowHeight)/miWindowWidth;
	MoveWindow(hWnd,miWindowX,miWindowY,liX,liY,0);
}

cWindow::~cWindow()
{
	    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}


cWindow::cWindow(HINSTANCE hInstance)
{
    gpWindow=this;
    mbQuit = false;

    miBorderThickness=0;
    miTitleBarHeight=0;

miWindowX=0;
miWindowY=0;
miWindowWidth=800;
miWindowHeight=600;
miInvWindowWidth=1.0f/miWindowWidth;
miInvWindowHeight=1.0f/miWindowHeight;

miRenderX=0;
miRenderY=0;
miRenderHeight=600;
miRenderWidth=800;

mfRenderRatio=600/800;
mfWindowRatio=600/800;
Hidden=false;
Resized=false;
Repaint=false;


    // register window class
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))        return;



InitialiseOpenGL();


}





void cWindow::StartWindow()

{
    miWindowWidth=800;
    miWindowHeight=600;
    miRenderWidth=800;
    miRenderHeight=600;
    miInvWindowWidth=1.0f/miWindowWidth;
    miInvWindowHeight=1.0f/miWindowHeight;
    mfWindowRatio=((float)miWindowHeight)/miWindowWidth;
    mfRenderRatio=((float)miRenderHeight)/miRenderWidth;
   hWnd=CreateWindowEx(0,
		wcex.lpszClassName, "Bamboo",
		WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE | WS_SIZEBOX,
		//WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		//WS_OVERLAPPEDWINDOW| WS_VISIBLE,
		10, 10, 800, 600,
		NULL, NULL, wcex.hInstance, NULL);

		Hidden=false;
		//Changed=false;
		Resized=false;
		//Moved=false;

		FindRenderArea();


}

void cWindow::EnableOpenGL()
{
  PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    // get the device context (DC)
    hDC = GetDC(hWnd);

    // set the pixel format for the DC
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(hDC, &pfd);

    SetPixelFormat(hDC, iFormat, &pfd);

    // create and enable the render context (RC)
    hRC = wglCreateContext(hDC);

    wglMakeCurrent(hDC, hRC);



}

uint32 cWindow::TitleBarHeight()
{
    return miTitleBarHeight;
};

uint32 cWindow::BorderThickness()
{
    return miBorderThickness;
};

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{

    case WM_PAINT:
         gpWindow->Repaint=true;
         return 0;

    case WM_MOUSEMOVE:
         _MOUSE->SetPos((int16)LOWORD(lParam),(int16)HIWORD(lParam));
         return 0;

    case WM_KEYDOWN:
        _KEYBOARD->SetKeyState(true,wParam);
       return 0;


    case WM_KEYUP:
         _KEYBOARD->SetKeyState(false,wParam);
         return 0;

    case WM_MOUSEWHEEL:
        _MOUSE->SetWheelPos(GET_WHEEL_DELTA_WPARAM(wParam));
        return 0;

    case WM_MBUTTONDOWN:
        _MOUSE->SetMiddle(true);
        return 0;

    case WM_MBUTTONUP:
        _MOUSE->SetMiddle(false);
        return 0;

    case WM_LBUTTONDOWN:
         _MOUSE->SetLeft(true);
         return 0;

    case WM_LBUTTONUP:
         _MOUSE->SetLeft(false);
         return 0;

    case WM_RBUTTONDOWN:
         _MOUSE->SetRight(true);
         return 0;

    case WM_RBUTTONUP:
         _MOUSE->SetRight(false);
         return 0;

    case WM_SIZE:
       if (wParam==SIZE_RESTORED)
         {
            gpWindow->miWindowWidth=LOWORD(lParam);
            gpWindow->miWindowHeight=HIWORD(lParam);
            gpWindow->miInvWindowWidth=1.0f/gpWindow->miWindowWidth;
            gpWindow->miInvWindowHeight=1.0f/gpWindow->miWindowHeight;

            gpWindow->mfWindowRatio=((float)gpWindow->miWindowHeight)/gpWindow->miWindowWidth;
            gpWindow->mfRenderRatio=((float)gpWindow->miRenderHeight)/gpWindow->miRenderWidth;
            gpWindow->FindRenderArea();
            cCameraHandler::Instance()->UpdateWindowSize();
          return 0;
         }
        return 0;

    case WM_SIZING:
         return 0;

    case WM_MOVE:
            gpWindow->miWindowX=(int16)LOWORD(lParam);
            gpWindow->miWindowY=(int16)HIWORD(lParam);
         return 0;

    case WM_CREATE:
        return 0;

    case WM_CLOSE:
         gpWindow->mbQuit=true;
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_ENTERSIZEMOVE:
        return 0;

    case WM_EXITSIZEMOVE:
    return 0;

    case WM_MOVING:
    return 0;


    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


void CreateConsole()
{
	AllocConsole();
	HANDLE StdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int32 CRT = _open_osfhandle(reinterpret_cast<intptr_t>(StdOutHandle), _O_TEXT);
	FILE* StdOut = _fdopen(CRT, "w");
	setvbuf(StdOut, nullptr, _IONBF, 1);
	*stdout = *StdOut;
}

#endif


#if WT_OS_TYPE==OS_LINUX

int cWindow::DisplayAttributes[]={ GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

cWindow::cWindow()
{
gpWindow=this;
mbQuit=0;
miWindowX=0;
miWindowY=0;
miWindowWidth=800;
miWindowHeight=600;
miInvWindowWidth=1.0f/miWindowWidth;
miInvWindowHeight=1.0f/miWindowHeight;

miRenderX=0;
miRenderY=0;
miRenderHeight=600;
miRenderWidth=800;

Resized=false;
//Moved=false;
Hidden=true;
Repaint=false;
mfWindowRatio=((float)miWindowHeight)/miWindowWidth;

lpDisplay=XOpenDisplay(0);
lRoot=DefaultRootWindow(lpDisplay);

//XVisualInfo* glXChooseVisual(Display *dpy, int screen, int *attribList)
VisualInfo=glXChooseVisual(lpDisplay,0,DisplayAttributes);

WindowAttributes.colormap = XCreateColormap(lpDisplay, lRoot,VisualInfo->visual, AllocNone);
WindowAttributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | StructureNotifyMask | PointerMotionMask | LeaveNotify;


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
 lWindow = XCreateWindow(lpDisplay, lRoot, 0, 0, miWindowWidth,
                        miWindowHeight, 0, VisualInfo->depth, InputOutput, VisualInfo->visual,
                        CWBorderPixel|CWColormap|CWEventMask, &WindowAttributes);

 XMapWindow(lpDisplay, lWindow);
 XStoreName(lpDisplay, lWindow, "GLBamboo");
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
		switch(Event.type)
		{
		    case MotionNotify:
		    {
                _MOUSE->cx=Event.xmotion.x;
                _MOUSE->cy=Event.xmotion.y;
                break;
		    };
		    case Expose:
		    {
		        XGetWindowAttributes(lpDisplay, lWindow, &gwa);
                glViewport(0, 0, gwa.width, gwa.height);
                glXSwapBuffers(lpDisplay, lWindow);
                break;
		    };
		    case KeyPress:
		    {
		      	uint32 liKeySym=XLookupKeysym(&Event.xkey,0);
                _KEYBOARD->SetKeyState(true,liKeySym&0xFF) ;
                break;
		    };
		    case KeyRelease:
		    {
                uint32 liKeySym=XLookupKeysym(&Event.xkey,0);
                _KEYBOARD->SetKeyState(false,liKeySym&0xFF);
                break;
		    };
		    case ButtonPress:
		    {
                if(Event.xbutton.button==1) _MOUSE->left=true;
                if(Event.xbutton.button==3) _MOUSE->right=true;
                if(Event.xbutton.button==2) _MOUSE->middle=true;
                if(Event.xbutton.button==4) ++(_MOUSE->cz);
                if(Event.xbutton.button==5) --(_MOUSE->cz);
                break;
		    };
		    case ButtonRelease:
		    {
                if(Event.xbutton.button==1) _MOUSE->left=false;
                if(Event.xbutton.button==3) _MOUSE->right=false;
                if(Event.xbutton.button==2) _MOUSE->middle=false;
                break;
		    };
		    case ConfigureNotify:
		    {
                gpWindow->miWindowX=Event.xconfigure.x;
                gpWindow->miWindowY=Event.xconfigure.y;
                gpWindow->miWindowWidth=Event.xconfigure.width;
                gpWindow->miWindowHeight=Event.xconfigure.height;
                gpWindow->miInvWindowWidth=1.0f/miWindowWidth;
                gpWindow->miInvWindowHeight=1.0f/miWindowHeight;
                //gpWindow->Moved=true;
                gpWindow->Resized=true;
                gpWindow->mfRenderRatio=gpWindow->mfWindowRatio=((float)gpWindow->miWindowHeight)/gpWindow->miWindowWidth;
                FindRenderArea();
                cCameraHandler::Instance()->UpdateWindowSize();
                break;
		    };
		    case DestroyNotify:
		    {
                gpWindow->mbQuit=true;
                break;
		    };
		    case LeaveNotify:
		    {
                if(_MOUSE->Locked())
                {
                    MovePointer(_MOUSE->X(),_MOUSE->Y());
                }
		        break;
		    };
		    case EnterNotify:
		    {

		    };
		};

		}
}


void cWindow::HandleChanges()
{
 //if(Resized)
//{

//}
}

#if WT_OS_TYPE==OS_WIN32

#endif

#if WT_OS_TYPE==OS_LINUX
void cWindow::GrabMouse()
{
    XGrabPointer(lpDisplay,lWindow,true,0,GrabModeAsync,GrabModeAsync,lWindow,None,CurrentTime);
}
#endif

void cWindow::MovePointer(uint32 liX,uint32 liY)
{
XWarpPointer(lpDisplay,None,lWindow,0,0,0,0,liX,liY);
XFlush( lpDisplay );
}

void cWindow::GetMouseSpeed()
{
 Window lpRootWin,lpChildWin;
 int liRX,liRY,liWX,liWY;
 unsigned int liMask;
	if (XQueryPointer(lpDisplay,lWindow,&lpRootWin,&lpChildWin,&liRX,&liRY,&liWX,&liWY,&liMask))
	{
		_MOUSE->xs=liWX-_MOUSE->cx;
		_MOUSE->ys=liWY-_MOUSE->cy;
	}

}

void cWindow::FindRenderArea()
{
    miRenderWidth=WindowWidth();
    miRenderHeight=WindowHeight();

    miRenderX=WindowX();
    miRenderY=WindowY();

    miBorderThickness=0;
    miTitleBarHeight=0;
}

#endif

	uint16 cWindow::WindowX(){return miWindowX;};
	uint16 cWindow::WindowY(){return miWindowY;};
	uint16 cWindow::WindowWidth(){return miWindowWidth;};
	uint16 cWindow::WindowHeight(){return miWindowHeight;};
	float32 cWindow::InvWindowWidth(){return miInvWindowWidth;};
	float32 cWindow::InvWindowHeight(){return miInvWindowHeight;};
	float32 cWindow::WindowRatio(){return mfWindowRatio;};
	float32 cWindow::RenderRatio(){return mfRenderRatio;};
