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
	xs=x-cx;
	ys=y-cy;
	x=cx;
	y=cy;
	SetCursorPos(cx+gpWindow->X(),cy+gpWindow->Y());
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
	SetCursorPos(cx+gpWindow->X(),cy+gpWindow->Y());
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
int cMouse::Y(){return y;};
int cMouse::Z(){return z;};
int cMouse::XSpeed(){return xs;};
int cMouse::YSpeed(){return ys;};
bool cMouse::Left(){return left;};
bool cMouse::Right(){return right;};
bool cMouse::Middle(){return middle;};

cCollisionList *cMouse::Selection(cMouseCollisionObject *lpMouse,uint32 liFilter,cCollisionList *lpList)
{
 return _COLLISION_HANDLER->GenerateCollisionList(lpMouse,liFilter,lpList);
};

cCollisionList *cMouse::SelectionDetailed(cMouseCollisionObject *lpMouse,uint32 liFilter,cCollisionList *lpList)
{
    return _COLLISION_HANDLER->GenerateDetailedCollisionList(lpMouse,liFilter,lpList);
};

/*
cCollisionList *cMouse::Selection(cViewport *lpViewport,float lfRadius)
{
    lpViewport->ViewportWidth();
    lpViewport->ViewportHeight();
    lpViewport->ViewportX();
    lpViewport->ViewportY();

       c3DVf MouseVector(X());

    if((X()>lpViewport->ViewportX() && X()<lpViewport->ViewportX()+lpViewport->ViewportWidth())&&(Y()>lpViewport->ViewportY() && Y()<lpViewport->ViewportY()+lpViewport->ViewportHeight()))
    {
        float lfWidthMod=(((X()-lpViewport->ViewportX())/lpViewport->ViewportWidth())-0.5f)*Width();
        float lfHeightMod=(((Y()-lpViewport->ViewportY())/lpViewport->ViewportHeight())-0.5f)*Height();
        float lfDepthMod=(lpViewport->Near());
        float* lpMatrix=lpViewport->Matrix();

        c3DVf MouseVector(lpMatrix[0]*lfWidthMod+lpMatrix[4]*lfHeightMod+lpMatrix[8]*lfDepthMod,
                          lpMatrix[1]*lfWidthMod+lpMatrix[5]*lfHeightMod+lpMatrix[9]*lfDepthMod,
                          lpMatrix[2]*lfWidthMod+lpMatrix[6]*lfHeightMod+lpMatrix[10]*lfDepthMod);

        c3DVf &MouseStart(lpViewport->Position());
        MouseStart.Invert();

        return cCollisionHandler::GenerateMouseSelection(MouseVector,MouseStart,lfRadius);
    }


};*/
