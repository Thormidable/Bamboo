#include "../../WTDivWin.h"

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
	/*GetCursorPos(&Pos);
	xs=Pos.x-cx;
	ys=Pos.y-cy;*/
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
 cx=gpWindow->Width>>1;
 cy=gpWindow->Height>>1;
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
