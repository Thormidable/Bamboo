#include "stdafx.h"
#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

void *cFocusHandler::spData=0;

bool cFocusHandler::Focus(void *lpObj)
{
    return ((!spData)||(spData==lpObj));
};
void cFocusHandler::ReleaseFocus()
{
    spData=0;
};
bool cFocusHandler::GetFocus(void *lpObj)
{
    if(!spData && spData!=lpObj) {spData=lpObj; return 1;} return 0;
};

cButton::cButton()
{
MouseOver=false;
Set2D();

Position(0.0f,0.0f);
Size(100);
}

cButton::cButton(cCamera *lpCamera) : cImage(lpCamera)
{
MouseOver=false;
Set2D();

Position(0.0f,0.0f);
Size(100);

}

cTextButton::cTextButton(cCamera *lpCamera) : cText(lpCamera)
{
MouseOver=false;
Set2D();

Position(0.0f,0.0f);
Size(20);
JustifyTextCentre();

}

cTextButton::cTextButton()
{
MouseOver=false;
Set2D();

Position(0.0f,0.0f);
Size(20);
JustifyTextCentre();
}
cButton::~cButton()
{
    //dtor
}

cTextButton::~cTextButton()
{
    //dtor
}


void cButton::Position(float lfX,float lfY,float lfZ)
{
  (void) lfZ;
    mvCenter[0]=lfX;
    mvCenter[1]=lfY;
    mpData[12]=lfX;
    mpData[13]=lfY;
}

	void cButton::Position(float *lfX)
	{
		memcpy(mvCenter.v,lfX,sizeof(float)*2);
		memcpy(mpData,lfX,sizeof(float)*2);
	};
	void cButton::Position(c2DVf lfX)
	{
		memcpy(mvCenter.v,lfX.v,sizeof(float)*2);
		memcpy(mpData,lfX.v,sizeof(float)*2);
	};
	void cButton::Position(c3DVf lfX)
	{
		memcpy(mvCenter.v,lfX.v,sizeof(float)*2);
		memcpy(mpData,lfX.v,sizeof(float)*2);
	};
	void cButton::Position(c2DVf *lfX)
	{
		memcpy(mvCenter.v,lfX->v,sizeof(float)*2);
		memcpy(mpData,mvCenter.v,sizeof(float)*2);
	};
	void cButton::Position(c3DVf *lfX)
	{
		memcpy(mvCenter.v,lfX->v,sizeof(float)*2);
		memcpy(mpData,mvCenter.v,sizeof(float)*2);
	};



void cButton::Width(float lfWidth)
{
    mvRange[0]=lfWidth*0.5f;
    mfWidth=lfWidth;
}
void cButton::Height(float lfHeight)
{
    mvRange[1]=lfHeight*0.5f;
    mfHeight=lfHeight;
}

void cButton::Size(float lfSize)
{
  mvRange[0]=lfSize*0.5f;
  mvRange[1]=mvRange[0]*gpWindow->WindowRatio();
  mfWidth=lfSize;
  mfHeight=mfWidth*gpWindow->WindowRatio();
}

void cTextButton::Width(float lfWidth)
{
	mvRange[0]=lfWidth*0.5f*Text().length();
    mfWidth=lfWidth;
}

void cTextButton::Height(float lfHeight)
{
	mvRange[1]=lfHeight*0.5f;
    mfHeight=lfHeight;
}

void cTextButton::Size(float lfSize)
{
  mvRange[0]=lfSize*0.5f*Text().length();
  mfWidth=lfSize;
  mvRange[1]=mfHeight=mfWidth*gpWindow->RenderRatio();
}

cButtonBase::cButtonBase()
{
MouseOver=false;
MousePressed=false;
mpFocusPointer=this;
};

void cButtonBase::FocusPointer(void *lpData)
{
    mpFocusPointer=lpData;
};

bool cButtonBase::Hover()
{

return Awake() && _MOUSE->LockedX()>mvCenter[0]-mvRange[0]
      && _MOUSE->LockedX()<mvCenter[0]+mvRange[0]
      && _MOUSE->LockedY()>mvCenter[1]-mvRange[1]
      && _MOUSE->LockedY()<mvCenter[1]+mvRange[1];
}


bool cButtonBase::Pressed(){return Pressed(_MOUSE->Left());};
bool cButtonBase::Clicked(){return Clicked(_MOUSE->Left());};
bool cButtonBase::PressedOn(){return PressedOn(_MOUSE->Left());};
bool cButtonBase::Dragged(){return Dragged(_MOUSE->Left());};

bool cButtonBase::PressedOn(bool lbActivate)
{

    if(lbActivate && cFocusHandler::Focus(mpFocusPointer))
    {
        if(Hover())
        {
            if(!MousePressed) MouseOver=true;
        }
        else
        {
            MouseOver=false;
        }

        MousePressed=true;
    }
    else
    {
        MousePressed=false;
        MouseOver=false;
    }

    return MouseOver;
};

bool cButtonBase::Dragged(bool lbActivate)
{
    if(lbActivate && cFocusHandler::Focus(mpFocusPointer))
    {
        if(!MousePressed && Hover())
        {
            MouseOver=true;
        }
        MousePressed=true;
    }
    else {MousePressed=false; MouseOver=false;}

    return MouseOver;
};



bool cButtonBase::Pressed(bool lbActivate)
{
return lbActivate && Hover() && cFocusHandler::Focus(mpFocusPointer);
}

bool cButtonBase::Clicked(bool lbActivate)
{
   if(Hover() && cFocusHandler::Focus(mpFocusPointer))
    {
        if(!lbActivate)
        {
            MouseOver=true;
            if(MousePressed)
            {
                MousePressed=false;
                return true;
            }
            return false;
        }
        else
        {
            if(MouseOver)
            {
                MousePressed=true;
            }
            return false;
        }

    }
    else
    {
        	MouseOver=false;
        	MousePressed=false;

    }
    return false;
}


void cTextButton::Position(float lfX,float lfY,float lfZ)
{
  (void) lfZ;
    mvCenter[0]=lfX;
    mvCenter[1]=lfY;
    mpData[12]=lfX;
    mpData[13]=lfY;
};

void cTextButton::Position(float *lfX)
	{
		memcpy(mvCenter.v,lfX,sizeof(float)*2);
		memcpy(mpData,lfX,sizeof(float)*2);
	};
	void cTextButton::Position(c2DVf lfX)
	{
		memcpy(mvCenter.v,lfX.v,sizeof(float)*2);
		memcpy(mpData,lfX.v,sizeof(float)*2);
	};
	void cTextButton::Position(c3DVf lfX)
	{
		memcpy(mvCenter.v,lfX.v,sizeof(float)*2);
		memcpy(mpData,lfX.v,sizeof(float)*2);
	};
	void cTextButton::Position(c2DVf *lfX)
	{
		memcpy(mvCenter.v,lfX->v,sizeof(float)*2);
		memcpy(mpData,mvCenter.v,sizeof(float)*2);
	};
	void cTextButton::Position(c3DVf *lfX)
	{
		memcpy(mvCenter.v,lfX->v,sizeof(float)*2);
		memcpy(mpData,mvCenter.v,sizeof(float)*2);
	};





cPointButton::cPointButton()
{
  MouseOver=false;
  Set2D();
  Position(0.0f,0.0f);
};

cPointButton::cPointButton(cCamera *lpCamera) : cPoint(lpCamera)
{
  MouseOver=false;
  Set2D();
  Position(0.0f,0.0f);
};
cPointButton::~cPointButton()
{

};


void cPointButton::Position(float lfX,float lfY,float lfZ)
{
  (void) lfZ;
    mvCenter[0]=lfX;
    mvCenter[1]=lfY;
    mpData[12]=lfX;
    mpData[13]=lfY;
}

void cPointButton::Position(float *lfX)
{
	memcpy(mvCenter.v,lfX,sizeof(float)*2);
	memcpy(mpData,lfX,sizeof(float)*2);
};
void cPointButton::Position(c2DVf lfX)
{
	memcpy(mvCenter.v,lfX.v,sizeof(float)*2);
	memcpy(mpData,lfX.v,sizeof(float)*2);
};
void cPointButton::Position(c3DVf lfX)
{
	memcpy(mvCenter.v,lfX.v,sizeof(float)*2);
	memcpy(mpData,lfX.v,sizeof(float)*2);
};
void cPointButton::Position(c2DVf *lfX)
{
	memcpy(mvCenter.v,lfX->v,sizeof(float)*2);
	memcpy(mpData,mvCenter.v,sizeof(float)*2);
};
void cPointButton::Position(c3DVf *lfX)
{
	memcpy(mvCenter.v,lfX->v,sizeof(float)*2);
	memcpy(mpData,mvCenter.v,sizeof(float)*2);
};



#endif


