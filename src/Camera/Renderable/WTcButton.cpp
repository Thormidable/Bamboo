#include "../../WTDivWin.h"

cButton::cButton()
{
MouseOver=false;
Set2D();

Position(0.0f,0.0f);
Size(100);
}

cTextButton::cTextButton()
{
MouseOver=false;
Set2D();

Position(0.0f,0.0f);
Size(20);
}
cButton::~cButton()
{
    //dtor
}

cTextButton::~cTextButton()
{
    //dtor
}

void cTextButton::RenderPainter(uint8 liLevel)
{
    (void) liLevel;
    if(mpFont)
    {
SetShaderVariables();
        float lfTextLeft;
        lfTextLeft=mfWidth*mpString.length()*0.5;
         short liCount;
         float lfHeight=mfHeight*0.5f;
        for(liCount=0;liCount<mpString.length();++liCount)
        {
        float liRange;
         if(mpString[liCount]!=32)
         {

            liRange=IMF_FONT_SCALE*(mpFont->Character(mpString[liCount])); //(or /64)
              glNormal3f(0.0f,0.0f,1.0f);
              glBegin(GL_QUADS);
              glTexCoord2f(1,liRange+IMF_FONT_SCALE);   glVertex3f(lfTextLeft-mfWidth*(liCount+0.5f),lfHeight,3.1f);
              glTexCoord2f(1,liRange);                  glVertex3f(lfTextLeft-mfWidth*(liCount+0.5f),-lfHeight,3.1f);
              glTexCoord2f(0,liRange);                  glVertex3f(lfTextLeft-mfWidth*(liCount-0.5f),-lfHeight,3.1f);
              glTexCoord2f(0,liRange+IMF_FONT_SCALE);   glVertex3f(lfTextLeft-mfWidth*(liCount-0.5f),lfHeight,3.1f);

              glEnd();

        }
       }
    }

}

void cButton::Position(float lfX,float lfY)
{
    XCenter=lfX;
    YCenter=gpWindow->RenderAreaHeight()-lfY;
    mpData[12]=lfX;
    mpData[13]=lfY;
}



void cButton::Width(float lfWidth)
{
    XRange=lfWidth*0.5;
    mfWidth=lfWidth;
}
void cButton::Height(float lfHeight)
{
    YRange=lfHeight*0.5;
    mfHeight=lfHeight;
}

void cButton::Size(float lfSize)
{
  XRange=lfSize*0.5;
  YRange=XRange*gpWindow->Ratio();
  mfWidth=lfSize;
  mfHeight=mfWidth*gpWindow->Ratio();
}

void cTextButton::Width(float lfWidth)
{
	XRange=lfWidth*0.5*Text().length();
    mfWidth=lfWidth;
}

void cTextButton::Height(float lfHeight)
{
	YRange=lfHeight*0.5;
    mfHeight=lfHeight;
}

void cTextButton::Size(float lfSize)
{
  XRange=lfSize*0.5*Text().length();
  mfWidth=lfSize;
  YRange=mfHeight=mfWidth*gpWindow->Ratio();
}


bool cButtonBase::Hover()
{
        printf("Render Area Width Hegiht : %i %i\n",gpWindow->RenderAreaWidth(),gpWindow->RenderAreaHeight());
        printf("Centre X Y : %f %f\n",XCenter,YCenter);
        printf("Range X Y : %f %f\n",XRange,YRange);
        printf("Mouse X Y : %i %i\n",_MOUSE->x,_MOUSE->y);

return _MOUSE->x>XCenter-XRange
      && _MOUSE->x<XCenter+XRange
      && _MOUSE->y>YCenter-YRange
      && _MOUSE->y<YCenter+YRange;
}

bool cButtonBase::Pressed()
{
return _MOUSE->left && Hover();
}

bool cButtonBase::Clicked()
{
   if(Hover())
    {
        if(!_MOUSE->left)
        {
            MouseOver=true;
            return false;
        }
        else
        {
            if(MouseOver) return true;
            return false;
        }

    }
    else
    {
        MouseOver=false;
    }
    return false;
}



bool cTextButton::Hover()
{
	//Width(cImage::Width());
 	// Height(cImage::Height());
	return cButtonBase::Hover();
}


