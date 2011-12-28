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
        float lfTextLeft,lfTextTop;
        lfTextLeft=mfWidth*mpString.length()*0.5;
        lfTextTop=(mfHeight)*0.5;
         short liCount;
        for(liCount=0;liCount<mpString.length();++liCount)
        {
        float liRange;
         if(mpString[liCount]!=32)
         {

            liRange=IMF_FONT_SCALE*(mpFont->Character(mpString[liCount])); //(or /64)
              glNormal3f(0.0f,0.0f,1.0f);
              glBegin(GL_QUADS);
              glTexCoord2f(1,liRange+IMF_FONT_SCALE);   glVertex3f(lfTextLeft-mfWidth*(2*liCount+1),lfTextTop+mfHeight,3.1f);
              glTexCoord2f(1,liRange);            glVertex3f(lfTextLeft-mfWidth*(2*liCount+1),lfTextTop-mfHeight,3.1f);
              glTexCoord2f(0,liRange);            glVertex3f(lfTextLeft-mfWidth*(2*liCount-1),lfTextTop-mfHeight,3.1f);
              glTexCoord2f(0,liRange+IMF_FONT_SCALE);   glVertex3f(lfTextLeft-mfWidth*(2*liCount-1),lfTextTop+mfHeight,3.1f);

              glEnd();

        }
       }
    }

}

/*
void cButton::RenderToPainter()
{

UpdateMatrix();
 mpPainterData->SetObject(this);
if(mpFont) mpPainterData->SetTexture(mpFont->TextureNumber());
else mpPainterData->SetTexture(0);
 SetOtherRenderVariables();
 mpPainterData->RenderAgain();
}

void cButton::Render()
{

}


void cButton::BorderColor(cRGB lcBorder)
{
 mcBorderColor=lcBorder;
}

void cButton::FrontColor(cRGB lcFront)
{
    mcFrontColor=lcFront;
}
*/

void cButton::Position(float lfX,float lfY)
{
    XCenter=gpWindow->Width()*0.5f+lfX;
    YCenter=gpWindow->Height()*0.5f-lfY;
    mpData[12]=(lfX*gpWindow->InvWidth()*_CAMERA->Width()*4);
    mpData[13]=(lfY*gpWindow->InvHeight()*_CAMERA->Height()*4);

}



void cButton::Width(float lfWidth)
{
    XRange=lfWidth;
    mfWidth=lfWidth*gpWindow->InvWidth()*_CAMERA->Width()*4;
}
void cButton::Height(float lfHeight)
{
    YRange=lfHeight;
    mfHeight=lfHeight*gpWindow->InvHeight()*_CAMERA->Height()*4;
}

void cButton::Size(float lfSize)
{
  XRange=lfSize;
  YRange=XRange*gpWindow->Ratio();
  mfWidth=lfSize*gpWindow->InvWidth()*_CAMERA->Width()*4;
  mfHeight=mfWidth*gpWindow->Ratio();
}

void cTextButton::Position(float lfX,float lfY)
{
    XCenter=(gpWindow->Width()*0.5f+lfX*0.6f);
    YCenter=(gpWindow->Height()*0.5f-lfY*0.6f);
    mpData[12]=(lfX*gpWindow->InvWidth()*_CAMERA->Width()*4);
    mpData[13]=(lfY*gpWindow->InvHeight()*_CAMERA->Height()*4);

}
void cTextButton::Width(float lfWidth)
{
	miPixelWidth=lfWidth;
	XRange=lfWidth*Text().length();
    mfWidth=lfWidth*gpWindow->InvWidth()*_CAMERA->Width()*4;
}

void cTextButton::Height(float lfHeight)
{
	miPixelHeight=lfHeight;
	YRange=lfHeight;
    mfHeight=lfHeight*gpWindow->InvHeight()*_CAMERA->Height()*4;
}

void cTextButton::Size(float lfSize)
{
  miPixelWidth=lfSize;
  XRange=lfSize*Text().length();
  miPixelHeight=lfSize*gpWindow->Ratio();
  YRange=miPixelHeight;
  mfWidth=lfSize*gpWindow->InvWidth()*_CAMERA->Width()*4;
  mfHeight=mfWidth*gpWindow->Ratio();
}


bool cButtonBase::Hover()
{
  return _MOUSE->x>XCenter-XRange && _MOUSE->x<XCenter+XRange && _MOUSE->y>YCenter-YRange && _MOUSE->y<YCenter+YRange;
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
	Width(miPixelWidth);
 	 Height(miPixelHeight);
	 printf("X RANGE : %f\nY RANGE : %f\n",XRange,YRange);
	return cButtonBase::Hover();
}

