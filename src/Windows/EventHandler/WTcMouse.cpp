#include "stdafx.h"
#include "../../WTBamboo.h"

int cMouse::LockedX(){return miLockedX;};
int cMouse::LockedY(){return miLockedY;};

cMouse::cMouse()
{
 left=0;
 right=0;
 middle=0;
 locked=false;
 miShown=true;
cz=z=zs=x=y=xs=ys=cx=cy=0;
#if WT_OS_TYPE==OS_LINUX
	mcCursor = XCreateFontCursor(gpWindow->lpDisplay, XC_left_ptr);
#endif
}

void cMouse::Update()
{

if(locked)
{
#if WT_OS_TYPE==OS_WIN32
	/*xs=cx-x;
	ys=cy-y;
	cx=x;
	cy=y;
	*/
    xs=x-cx;
	ys=gpWindow->RenderAreaHeight()-y-cy;
	miLockedX=x=cx;
	miLockedY=y=gpWindow->RenderAreaHeight()-cy;
    if(cx<gpWindow->RenderAreaWidth()*0.4 || cx>gpWindow->RenderAreaWidth()*0.6 || cy<gpWindow->RenderAreaWidth()*0.4 || cy>gpWindow->RenderAreaHeight()*0.6)
	{
        x=gpWindow->RenderAreaWidth()*0.5;
        y=gpWindow->RenderAreaHeight()*0.5;
        SetCursorPos(x+gpWindow->WindowX(),y+gpWindow->WindowY());
	}
#endif
#if WT_OS_TYPE==OS_LINUX
    xs=x-cx;
	ys=gpWindow->RenderAreaHeight()-y-cy;
	miLockedX=x=cx;
	miLockedY=y=gpWindow->RenderAreaHeight()-cy;
    if(cx<0.4*gpWindow->RenderAreaWidth() || cx>gpWindow->RenderAreaWidth()*0.6 || cy<0.4*gpWindow->RenderAreaHeight() || cy>gpWindow->RenderAreaHeight()*0.6)
	{
	    x=gpWindow->RenderAreaWidth()*0.5;
        y=gpWindow->RenderAreaHeight()*0.5;
        gpWindow->MovePointer(x,y);
	}
#endif
}
else
{
	xs=x-cx;
	ys=gpWindow->RenderAreaHeight()-y-cy;
	miLockedX=x=cx;
	miLockedY=y=gpWindow->RenderAreaHeight()-cy;
}
zs=cz;
z+=cz;
cz=0;
}

bool cMouse::Locked(){return locked;};

void cMouse::Lock()
{

 if(_MOUSE->locked) return;

 miLockedX=cx;
 miLockedY=cy;

 locked=true;
 cx=x=gpWindow->RenderAreaWidth()*0.5;
 cy=y=gpWindow->RenderAreaHeight()*0.5;
#if WT_OS_TYPE==OS_WIN32
	SetCursorPos(x+gpWindow->WindowX(),y+gpWindow->WindowY());
#endif
#if WT_OS_TYPE==OS_LINUX

	gpWindow->MovePointer(x,y);
#endif

}

void cMouse::Unlock()
{

if(!_MOUSE->locked) return;
 locked=false;
 cx=x;
 cy=y;

 //XUngrabPointer(gpWindow->lpDisplay,CurrentTime);

}
 #if WT_OS_TYPE==OS_WIN32
void cMouse::Hide()
{
     miShown=false;
    ShowCursor(miShown);
}
#endif
#if WT_OS_TYPE==OS_LINUX
void cMouse::Hide()
 {
     miShown=false;
    XUndefineCursor(gpWindow->lpDisplay,gpWindow->lWindow);
 }
#endif


 #if WT_OS_TYPE==OS_WIN32
void cMouse::Show()
{
    miShown=true;
    ShowCursor(miShown);
}
#endif

#if WT_OS_TYPE==OS_LINUX
void cMouse::Show()
{
    miShown=true;
    XDefineCursor(gpWindow->lpDisplay,gpWindow->lWindow,mcCursor);
}
#endif



bool cMouse::Showing()
{return miShown;}

int cMouse::X(){return x;};
int cMouse::Y(){return y;};
int cMouse::Z(){return z;};
int cMouse::XSpeed(){return xs;};
int cMouse::YSpeed(){return ys;};
int cMouse::ZSpeed(){return zs;};
bool cMouse::Left(){return left;};
bool cMouse::Right(){return right;};
bool cMouse::Middle(){return middle;};

#if WT_FULL_VERSION_BAMBOO
cCollisionList *cMouse::Selection(cMouseCollisionObject *lpMouse,uint32 liFilter,cCollisionList *lpList)
{
 return _COLLISION_HANDLER->GenerateCollisionList(lpMouse,liFilter,lpList);
};

cCollisionList *cMouse::SelectionDetailed(cMouseCollisionObject *lpMouse,uint32 liFilter,cCollisionList *lpList)
{
    return _COLLISION_HANDLER->GenerateDetailedCollisionList(lpMouse,liFilter,lpList);
};
#endif
void cMouse::UnlockPosition()
{
    if(!_MOUSE->locked) return;
#if WT_OS_TYPE==OS_WIN32
    locked=false;
    cx=miLockedX+gpWindow->WindowX();
    cy=miLockedY+gpWindow->WindowY();

    SetCursorPos(cx,cy);
#endif
#if WT_OS_TYPE==OS_LINUX
    locked=false;
    cx=miLockedX;
    cy=miLockedY;
    gpWindow->MovePointer(cx,cy);
#endif
}

#if WT_OS_TYPE==OS_WIN32

void cMouse::SetPos(int lX,int lY)
{
    cx=lX;
    cy=lY;
};


void cMouse::SetWheelPos(int liSize)
{
    cz+=liSize;
};
void cMouse::SetLeft(bool lbLeft){left=lbLeft;};
void cMouse::SetRight(bool lbRight){right=lbRight;};
void cMouse::SetMiddle(bool lbMiddle){middle=lbMiddle;};

#endif
