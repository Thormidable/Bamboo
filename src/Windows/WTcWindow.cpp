#include "../WTBamboo.h"



uint32 cWindow::RenderAreaWidth()
{
    return miRenderWidth;
}
uint32 cWindow::RenderAreaHeight()
{
    return miRenderHeight;
}


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
    GetClientRect(gpWindow->hWnd,&Result);

    miRenderWidth=Result.right;
    miRenderHeight=Result.bottom;

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
	MoveWindow(hWnd,liX,liY,miWidth,miHeight,0);
}

void cWindow::Resize(short liX,short liY)
{
	MoveWindow(hWnd,miX,miY,liX,liY,0);
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

    case WM_CREATE:
        return 0;

    case WM_CLOSE:
         gpWindow->mbQuit=true;
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_PAINT:
         gpWindow->Repaint=true;
         return 0;



    case WM_SIZE:
       if (wParam==SIZE_RESTORED)
         {
          gpWindow->miWidth=LOWORD(lParam);
          gpWindow->miHeight=HIWORD(lParam);
          gpWindow->miInvWidth=1.0f/gpWindow->miWidth;
          gpWindow->miInvHeight=1.0f/gpWindow->miHeight;
          gpWindow->mfRatio=((float)gpWindow->miHeight)/gpWindow->miWidth;
          cCameraHandler::Instance()->UpdateWindowSize();
          return 0;
         }
        return 0;

    case WM_SIZING:
         return 0;

    case WM_MOVE:
         gpWindow->miX=(int16)LOWORD(lParam);
         gpWindow->miY=(int16)HIWORD(lParam);
         //gpWindow->Moved=true;
         return 0;


    case WM_MOUSEMOVE:
         if (!_MOUSE->locked)
         {
            _MOUSE->cx=(int16)LOWORD(lParam);
            _MOUSE->cy=(int16)HIWORD(lParam);
         }
         else
         {
            _MOUSE->x=(int16)LOWORD(lParam);
            _MOUSE->y=(int16)HIWORD(lParam);
         }
         return 0;

    case WM_LBUTTONDOWN:
         _MOUSE->left=true;
  //       _MOUSE->x = (int16)LOWORD(lParam);
   //      _MOUSE->y = (int16)HIWORD(lParam);
         return 0;

    case WM_LBUTTONUP:
         _MOUSE->left=false;
 //        _MOUSE->x = (int16)LOWORD(lParam);
 //        _MOUSE->y = (int16)HIWORD(lParam);
         return 0;

    case WM_RBUTTONDOWN:
         _MOUSE->right=true;
 //        _MOUSE->x = (int16)LOWORD(lParam);
 //        _MOUSE->y = (int16)HIWORD(lParam);
         return 0;

    case WM_RBUTTONUP:
         _MOUSE->right=false;
 //        _MOUSE->x = (int16)LOWORD(lParam);
 //        _MOUSE->y = (int16)HIWORD(lParam);
         return 0;

    case WM_KEYDOWN:
        _KEYBOARD->SetKeyState(true,wParam);
       return 0;


    case WM_KEYUP:
         _KEYBOARD->SetKeyState(false,wParam);
         return 0;


    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}

#endif


#if WT_OS_TYPE==OS_LINUX

int cWindow::DisplayAttributes[]={ GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

cWindow::cWindow()
{
gpWindow=this;
mbQuit=0;
miX=0;
miY=0;
miWidth=800;
miHeight=600;
miInvWidth=1.0f/miWidth;
miInvHeight=1.0f/miHeight;
Resized=false;
//Moved=false;
Hidden=true;
Repaint=false;
mfRatio=((float)miHeight)/miWidth;;

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
 lWindow = XCreateWindow(lpDisplay, lRoot, 0, 0, miWidth,
                        miHeight, 0, VisualInfo->depth, InputOutput, VisualInfo->visual,
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
		  _KEYBOARD->SetKeyState(true,liKeySym&0xFF) ;
		  break;
		}
		if(Event.type == KeyRelease)
		{
		  uint32 liKeySym=XLookupKeysym(&Event.xkey,0);
		  _KEYBOARD->SetKeyState(false,liKeySym&0xFF);
		  break;
		}


		//Mouse Stuff
		if(Event.type == ButtonPress)
		{
			if(Event.xbutton.button==1) _MOUSE->left=true;
			if(Event.xbutton.button==3) _MOUSE->right=true;
			if(Event.xbutton.button==2) _MOUSE->middle=true;
			break;
		}
		if(Event.type == ButtonRelease)
		{
			if(Event.xbutton.button==1) _MOUSE->left=false;
			if(Event.xbutton.button==3) _MOUSE->right=false;
			if(Event.xbutton.button==2) _MOUSE->middle=false;
			break;
		}
		if(Event.type == MotionNotify)
		{
		 if (!_MOUSE->locked)
         {
			_MOUSE->cx=Event.xmotion.x;
			_MOUSE->cy=Event.xmotion.y;
         }
         else
         {
			_MOUSE->x=Event.xmotion.x;
			_MOUSE->y=Event.xmotion.y;
         }

			break;
		}
		if(Event.type == ConfigureNotify)
		{
			gpWindow->miX=Event.xconfigure.x;
			gpWindow->miY=Event.xconfigure.y;
			gpWindow->miWidth=Event.xconfigure.width;
			gpWindow->miHeight=Event.xconfigure.height;
			gpWindow->miInvWidth=1.0f/miWidth;
            gpWindow->miInvHeight=1.0f/miHeight;
			//gpWindow->Moved=true;
			gpWindow->Resized=true;
			gpWindow->mfRatio=((float)gpWindow->miHeight)/gpWindow->miWidth;
			cCameraHandler::Instance()->UpdateWindowSize();
			FindRenderArea();
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
 //if(Resized)
//{

//}
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
		_MOUSE->xs=liWX-_MOUSE->cx;
		_MOUSE->ys=liWY-_MOUSE->cy;
	}

}

void cWindow::FindRenderArea()
{
    miRenderWidth=Width();
    miRenderHeight=Height();

    miBorderThickness=0;
    miTitleBarHeight=0;
}

#endif

	uint16 cWindow::X(){return miX;};
	uint16 cWindow::Y(){return miY;};
	uint16 cWindow::Width(){return miWidth;};
	uint16 cWindow::Height(){return miHeight;};
	float32 cWindow::InvWidth(){return miInvWidth;};
	float32 cWindow::InvHeight(){return miInvHeight;};
	float32 cWindow::Ratio(){return mfRatio;};
