#ifndef __WTCEVENTHANDLER_H__
#define __WTCEVENTHANDLER_H__

/**
* \brief This will handle events from the OS.
* Actually this will just store the Input data for the keyboard and mouse.
* It is easiest to access the input data using _KEY and _MOUSE.
* There can only be one cEventHandler, created using Instance().
*/
class cEventHandler
{
 /// This is a pointer to the current cEventHandler instance.
 static cEventHandler *mpInstance;
 /// Lucky Constructor. Does nothing.
 cEventHandler(){};
 public:
 /// This will return a pointer to the current cEventhandler instance. If there is no instance it will create one.
 static cEventHandler *Instance();
 /// This will store all the keyboard input data. see _KEY
 cKeyStore Key;
 /// This will store the mouse input data. see _MOUSE
 cMouse Mouse;
};

#if WT_OS_TYPE==OS_WIN32
/// This is a Windows only function and is an interupt used by Windows.
LRESULT CALLBACK RecieveEvent(HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam);
#endif

#endif

