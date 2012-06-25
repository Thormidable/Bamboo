#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

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

void cTextButton::RenderPainter()
{

    if(Textures())
    {
	SetShaderVariables();
        float lfTextLeft;
        lfTextLeft=mfWidth*mpString.length()*0.5f;
         uint16 liCount;
         float lfHeight=mfHeight*0.5f;
        for(liCount=0;liCount<mpString.length();++liCount)
        {
        float liRange;
         if(mpString[liCount]!=32)
         {

            liRange=IMF_FONT_SCALE*(cFont::Character(mpString[liCount])); //(or /64)
              glNormal3f(0.0f,0.0f,1.0f);
              glBegin(GL_QUADS);

              glTexCoord2f(0,liRange+IMF_FONT_SCALE);   glVertex3f(lfTextLeft-mfWidth*(liCount-0.5f),lfHeight,1.0f);
              glTexCoord2f(0,liRange);                  glVertex3f(lfTextLeft-mfWidth*(liCount-0.5f),-lfHeight,1.0f);
              glTexCoord2f(1,liRange);                  glVertex3f(lfTextLeft-mfWidth*(liCount+0.5f),-lfHeight,1.0f);
              glTexCoord2f(1,liRange+IMF_FONT_SCALE);   glVertex3f(lfTextLeft-mfWidth*(liCount+0.5f),lfHeight,1.0f);
              glEnd();

        }
       }
    }

}



void cButton::Position(float lfX,float lfY)
{
    XCenter=lfX;
    YCenter=lfY;
    mpData[12]=lfX;
    mpData[13]=lfY;
}



void cButton::Width(float lfWidth)
{
    XRange=lfWidth*0.5f;
    mfWidth=lfWidth;
}
void cButton::Height(float lfHeight)
{
    YRange=lfHeight*0.5f;
    mfHeight=lfHeight;
}

void cButton::Size(float lfSize)
{
  XRange=lfSize*0.5f;
  YRange=XRange*gpWindow->WindowRatio();
  mfWidth=lfSize;
  mfHeight=mfWidth*gpWindow->WindowRatio();
}

void cTextButton::Width(float lfWidth)
{
	XRange=lfWidth*0.5f*Text().length();
    mfWidth=lfWidth;
}

void cTextButton::Height(float lfHeight)
{
	YRange=lfHeight*0.5f;
    mfHeight=lfHeight;
}

void cTextButton::Size(float lfSize)
{
  XRange=lfSize*0.5f*Text().length();
  mfWidth=lfSize;
  YRange=mfHeight=mfWidth*gpWindow->RenderRatio();
}


bool cButtonBase::Hover()
{

return _MOUSE->LockedX()>XCenter-XRange
      && _MOUSE->LockedX()<XCenter+XRange
      && _MOUSE->LockedY()>gpWindow->RenderAreaHeight()-YCenter-YRange
      && _MOUSE->LockedY()<gpWindow->RenderAreaHeight()-YCenter+YRange;
}

bool cButtonBase::Pressed()
{
return _MOUSE->Left() && Hover();
}

bool cButtonBase::Clicked()
{
   if(Hover())
    {
        if(!_MOUSE->Left())
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



bool cTextButton::Hover()
{
	return cButtonBase::Hover();
}

#endif
