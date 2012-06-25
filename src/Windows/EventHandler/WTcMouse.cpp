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
x=y=xs=ys=cx=cy=0.0f;
#if WT_OS_TYPE==OS_LINUX
	mcCursor = XCreateFontCursor(gpWindow->lpDisplay, XC_left_ptr);
#endif
}

void cMouse::Update()
{
if(locked)
{
#if WT_OS_TYPE==OS_WIN32
	xs=x-cx;
	ys=y-cy;
	x=cx;
	y=cy;
	//printf("Render Area : %f %f\n",gpWindow->RenderAreaX(),gpWindow->RenderAreaY());
	SetCursorPos(cx+gpWindow->WindowX(),cy+gpWindow->WindowY());
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
	miLockedX=x=cx;
	miLockedY=y=cy;
}
}

bool cMouse::Locked(){return locked;};

void cMouse::Lock()
{
 if(_MOUSE->locked) return;

 miLockedX=cx;
 miLockedY=cy;

 //miLockedX=cx;
 //miLockedY=cy;

 locked=true;
 cx=gpWindow->RenderAreaWidth()*0.5;
 cy=gpWindow->RenderAreaHeight()*0.5;
#if WT_OS_TYPE==OS_WIN32
	SetCursorPos(cx+gpWindow->WindowX(),cy+gpWindow->WindowY());
#endif
#if WT_OS_TYPE==OS_LINUX
	x=cx;
	y=cy;
	gpWindow->MovePointer(cx,cy);
#endif
}

void cMouse::Unlock()
{
if(!_MOUSE->locked) return;
 locked=false;
 cx=x;
 cy=y;
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
if (!Locked())
         {
            cx=lX;
            cy=lY;
         }
         else
         {
            x=lX;
            y=lY;
         }
};
void cMouse::SetPos(int lX,int lY,int lZ)
{
if (!Locked())
         {
            cx=lX;
            cy=lY;
            //cz=lZ;
         }
         else
         {
            x=lX;
            y=lY;
            z=lZ;
         }
};
void cMouse::SetLeft(bool lbLeft){left=lbLeft;};
void cMouse::SetRight(bool lbRight){right=lbRight;};
void cMouse::SetMiddle(bool lbMiddle){middle=lbMiddle;};

#endif
