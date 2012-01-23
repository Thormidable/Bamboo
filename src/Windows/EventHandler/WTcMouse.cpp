#include "../../WTBamboo.h"


cMouse::cMouse()
{
 left=0;
 right=0;
 middle=0;
 locked=false;
 miShown=true;
x=y=xs=ys=cx=cy=0.0f;
}

void cMouse::Update()
{
if(locked)
{

#if WT_OS_TYPE==OS_WIN32
	xs=x;
	ys=y;
	x=y=0;
	SetCursorPos(cx,cy);
#endif
#if WT_OS_TYPE==OS_LINUX
	xs=cx-x;
	ys=cy-y;
	gpWindow->MovePointer(cx,cy);
#endif
}
else
{

	xs=cx-x;
	ys=cy-y;
	x=cx;
	y=cy;
}
}

void cMouse::Lock()
{

 locked=true;
 cx=gpWindow->Width()>>1;
 cy=gpWindow->Height()>>1;
 #if WT_OS_TYPE==OS_WIN32
	SetCursorPos(cx,cy);
#endif
#if WT_OS_TYPE==OS_LINUX
	gpWindow->MovePointer(cx,cy);
#endif
}

void cMouse::Unlock()
{
 locked=false;
 cx=x;
 cy=y;
}

void cMouse::Hide()
 {miShown=false;}

void cMouse::Show()
{miShown=true;}

bool cMouse::Showing()
{return miShown;}

int cMouse::X(){return x;};
 ///Will return the current Y Position of the mouse cursor in pixels from the bottom edge of the screen.
int cMouse::Y(){return y;};
 ///Will return the current Z Position of the mouse cursor.
int cMouse::Z(){return z;};
 ///Will return the number of horizontal pixels the cursor moved last frame. Moving Right is positive.
int cMouse::XSpeed(){return xs;};
 ///Will return the number of vertical pixels the cursor moved last frame. Moving Up is positive.
int cMouse::YSpeed(){return ys;};
 ///Will return the pressed state of the mouses left button.
bool cMouse::Left(){return left;};
 ///Will return the pressed state of the mouses right button.
bool cMouse::Right(){return right;};
///Will return the pressed state of the mouses middle button.
bool cMouse::Middle(){return middle;};
