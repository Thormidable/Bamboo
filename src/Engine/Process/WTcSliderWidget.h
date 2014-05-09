#ifndef __WTCSLIDERWIDGET_H__
#define __WTCSLIDERWIDGET_H__

/*
template <class tA> class A
{

  public:
    cButton *mpBackground;
    A(uint8 li1)
    {

    };
};

template<class tB> class B : public A<tB>
{
    public:
    B(uint8 li2) : A<tB>(li2)
    {

    };
};*/

template<class T> class cSliderWidget : public cProcess
{
  float mfMin,mfRange;
  float mfHeight;
  T mfValue;
  float mfTopLimit,mfBottomLimit;

  bool mbLocked;
public:
  cImage *mpBackground;
  cButton *mpSlider;
  cText *mpValue;
  cText *mpTitle;

cSliderWidget(cTexture *lpBackground,cTexture *lpButton, float lfMin,float lfMax,float lfHeight,cFont *lpFont,cRGBA lcTextColor, cShaderProgram *lpShader,cShaderProgram *lpTextShader,cCamera *lpCamera)
{

 if(lpCamera) mpBackground=_CREATE(cImage(lpCamera));
 else mpBackground=_CREATE(cImage);

 if(lpShader) mpBackground->Shader(lpShader);
 else mpBackground->Shader("Image2DProgram");

 mpBackground->AddTexture(lpBackground);
 mpBackground->Width(60);
 mpBackground->Height(mfHeight);

 mpBackground->Transparency(1);

 if(lpCamera) mpSlider=_CREATE(cButton(lpCamera));
 else mpSlider=_CREATE(cButton);

 if(lpShader) mpSlider->Shader(lpShader);
 else mpSlider->Shader("Image2DProgram");

 mpSlider->AddTexture(lpButton);
 mpSlider->Width(40);
 mpSlider->Height(20);

 mpSlider->Transparency(2);

 mfHeight=lfHeight;
 mfMin=lfMin;
 mfRange=lfMax-lfMin;

 if(lpFont)
 {
     if(lpCamera)
     {
        mpTitle=_CREATE(cText(lpCamera));
        mpValue=_CREATE(cText(lpCamera));
     }
     else
     {
        mpTitle=_CREATE(cText);
        mpValue=_CREATE(cText);
     }

     if(lpTextShader)
     {
         mpValue->Shader(lpTextShader);
         mpTitle->Shader(lpTextShader);
     }
     else
     {
        mpTitle->Shader("TextProgram");
        mpValue->Shader("TextProgram");
     }

     mpValue->AddFont(lpFont);
     mpValue->SetUniform("TextColor",lcTextColor.Color());
     mpValue->Size(20);
     mpValue->Transparency(3);
     mpValue->JustifyTextCentre();

     mpTitle->AddFont(lpFont);
     mpTitle->SetUniform("TextColor",lcTextColor.Color());
     mpTitle->Size(20);
     mpTitle->Transparency(3);
     mpTitle->JustifyTextCentre();


 }
 else
 {
     mpValue=0;
 }



 Position(gpWindow->RenderAreaWidth()*0.5,gpWindow->RenderAreaHeight()*0.5);

 mbLocked=false;

};



void Title(string lsTitle)
{
    mpTitle->Text(lsTitle);
};

void TextSize(float lfSize)
{
    if(mpValue)
    {
        mpValue->Size(lfSize);
        mpTitle->Size(lfSize);
    }
};

virtual void Position(float lfX,float lfY)
{
    mfTopLimit=lfY+mfHeight*0.4-mpTitle->Height()*2;
    mfBottomLimit=lfY-mfHeight*0.4;
    mpSlider->Position(lfX,((mfTopLimit-mfBottomLimit)*(mfValue-mfMin)/mfRange)+mfBottomLimit);
    mpBackground->Position(lfX,lfY);
    if(mpValue) mpValue->Position(lfX,((mfTopLimit-mfBottomLimit)*(mfValue-mfMin)/mfRange)+mfBottomLimit);
    mpTitle->Position(lfX,mfTopLimit+mpTitle->Height()*3.6f);
};

void Run()
{
    if(!mbLocked && mpSlider->Dragged())
    {
        float lfY=_MOUSE->Y();
        if(lfY>mfTopLimit) lfY=mfTopLimit;
        else if(lfY<mfBottomLimit) lfY=mfBottomLimit;

        mpSlider->Position(mpSlider->X(),lfY);
        mfValue=mfRange*(lfY-mfBottomLimit)/(mfTopLimit-mfBottomLimit)+mfMin;
       if(mpValue)
       {
           mpValue->Value(mfValue);
           mpValue->Position(mpSlider->X(),lfY);
       }
    }
};

virtual void Range(float lfMin, float lfMax)
{
     mfMin=lfMin;
     mfRange=lfMax-lfMin;
     mfValue=mfRange*(mpSlider->Y()-mfBottomLimit)/(mfTopLimit-mfBottomLimit);
     if(mpValue) mpValue->Value(mfValue);
};


void SliderSize(float lfWidth,float lfHeight)
{
    mpSlider->Width(lfWidth);
    mpSlider->Height(lfHeight);
};

virtual void Size(float lfWidth, float lfHeight)
{
    mfHeight=lfHeight;
    mpBackground->Width(lfWidth);
    mpBackground->Height(mfHeight);
    mfTopLimit=mpBackground->Y()+mfHeight*0.4;
    mfBottomLimit=mpBackground->Y()-mfHeight*0.4;
};


void Stop()
{
    _KILL(mpBackground);
    _KILL(mpSlider);
    if(mpValue) _KILL(mpValue);
    _KILL(mpTitle);
};

void FocusPointer(void *lpData)
{
 mpSlider->FocusPointer(lpData);
};

T Value()
{
    return mfValue;
};

virtual void Value(T lfValue)
{
    mfValue=lfValue;
    mpSlider->Position(mpSlider->X(),((mfTopLimit-mfBottomLimit)*(lfValue-mfMin)/mfRange)+mfBottomLimit);
    if(mpValue)
    {
        mpValue->Position(mpSlider->X(),mpSlider->Y());
        mpValue->Value(mfValue);
    }
};

void Lock(){mbLocked=true;};
void Unlock(){mbLocked=false;};

void OnSleep()
{
    _SLEEP(mpBackground);
    _SLEEP(mpSlider);
    _SLEEP(mpValue);
    _SLEEP(mpTitle);
};

void OnWake()
{
    _WAKE(mpBackground);
    _WAKE(mpSlider);
    _WAKE(mpValue);
    _WAKE(mpTitle);
};

void Transparency(uint8 liX)
{
    mpBackground->Transparency(liX);
    mpSlider->Transparency(liX+1);
    mpValue->Transparency(liX+1);
    mpTitle->Transparency(liX+1);
};

};





template<class T> class cSliderHorizontalWidget : public cProcess
{
  float mfMin,mfRange;
  float mfWidth;
  T mfValue;
  float mfTopLimit,mfBottomLimit;

  bool mbLocked;
public:
  cImage *mpBackground;
  cButton *mpSlider;
  cText *mpValue;
  cText *mpTitle;

cSliderHorizontalWidget(cTexture *lpBackground,cTexture *lpButton, float lfMin,float lfMax,float lfWidth,cFont *lpFont,cRGBA lcTextColor, cShaderProgram *lpShader,cShaderProgram *lpTextShader,cCamera *lpCamera)
{

 if(lpCamera) mpBackground=_CREATE(cImage(lpCamera));
 else mpBackground=_CREATE(cImage);

 if(lpShader) mpBackground->Shader(lpShader);
 else mpBackground->Shader("Image2DProgram");

 mpBackground->AddTexture(lpBackground);
 mpBackground->Height(90);
 mpBackground->Width(lfWidth);

 mpBackground->Transparency(1);

 if(lpCamera) mpSlider=_CREATE(cButton(lpCamera));
 else mpSlider=_CREATE(cButton);

 if(lpShader) mpSlider->Shader(lpShader);
 else mpSlider->Shader("Image2DProgram");

 mpSlider->AddTexture(lpButton);
 mpSlider->Width(20);
 mpSlider->Height(40);

 mpSlider->Transparency(2);

 mfWidth=lfWidth;
 mfMin=lfMin;
 mfRange=lfMax-lfMin;

 if(lpFont)
 {
     if(lpCamera)
     {
        mpTitle=_CREATE(cText(lpCamera));
        mpValue=_CREATE(cText(lpCamera));
     }
     else
     {
        mpTitle=_CREATE(cText);
        mpValue=_CREATE(cText);
     }

     if(lpTextShader)
     {
         mpValue->Shader(lpTextShader);
         mpTitle->Shader(lpTextShader);
     }
     else
     {
        mpTitle->Shader("TextProgram");
        mpValue->Shader("TextProgram");
     }

     mpValue->AddFont(lpFont);
     mpValue->SetUniform("TextColor",lcTextColor.Color());
     mpValue->Size(20);
     mpValue->Transparency(3);
     mpValue->JustifyTextCentre();

     mpTitle->AddFont(lpFont);
     mpTitle->SetUniform("TextColor",lcTextColor.Color());
     mpTitle->Size(20);
     mpTitle->Transparency(3);
     mpTitle->JustifyTextCentre();


 }
 else
 {
     mpValue=0;
 }



 Position(gpWindow->RenderAreaWidth()*0.5,gpWindow->RenderAreaHeight()*0.5);

 mbLocked=false;

};



void Title(string lsTitle)
{
    mpTitle->Text(lsTitle);
};

void TextSize(float lfSize)
{
    if(mpValue)
    {
        mpValue->Size(lfSize);
        mpTitle->Size(lfSize);
    }
};

virtual void Position(float lfX,float lfY)
{
    mfTopLimit=lfX+mfWidth*0.4;
    mfBottomLimit=lfX-mfWidth*0.4;
    mpSlider->Position(((mfTopLimit-mfBottomLimit)*(mfValue-mfMin)/mfRange)+mfBottomLimit,lfY+mpBackground->Height()*0.5-mpTitle->Height()*3.6);
    mpBackground->Position(lfX,lfY);
    if(mpValue) mpValue->Position(((mfTopLimit-mfBottomLimit)*(mfValue-mfMin)/mfRange)+mfBottomLimit,mpSlider->Y());
    mpTitle->Position(lfX,lfY+mpBackground->Height()*0.5f-mpTitle->Height()*1.6f);
};

void Run()
{
    if(!mbLocked && mpSlider->Dragged())
    {
        float lfX=_MOUSE->X();
        if(lfX>mfTopLimit) lfX=mfTopLimit;
        else if(lfX<mfBottomLimit) lfX=mfBottomLimit;

        mpSlider->Position(lfX,mpSlider->Y());
        mfValue=mfRange*(lfX-mfBottomLimit)/(mfTopLimit-mfBottomLimit)+mfMin;
       if(mpValue)
       {
           mpValue->Value(mfValue);
           mpValue->Position(lfX,mpSlider->Y());
       }
    }
};

virtual void Range(float lfMin, float lfMax)
{
     mfMin=lfMin;
     mfRange=lfMax-lfMin;
     mfValue=mfRange*(mpSlider->X()-mfBottomLimit)/(mfTopLimit-mfBottomLimit);
     if(mpValue) mpValue->Value(mfValue);
};


void SliderSize(float lfWidth,float lfHeight)
{
    mpSlider->Width(lfWidth);
    mpSlider->Height(lfHeight);
};

virtual void Size(float lfWidth, float lfHeight)
{
    mfWidth=lfWidth;
    mpBackground->Width(mfWidth);
    mpBackground->Height(lfHeight);
    mfTopLimit=mpBackground->X()+mfWidth*0.4;
    mfBottomLimit=mpBackground->X()-mfWidth*0.4;
};


void Stop()
{
    _KILL(mpBackground);
    _KILL(mpSlider);
    if(mpValue) _KILL(mpValue);
    _KILL(mpTitle);
};

void FocusPointer(void *lpData)
{
 mpSlider->FocusPointer(lpData);
};

T Value()
{
    return mfValue;
};

virtual void Value(T lfValue)
{
    mfValue=lfValue;
    mpSlider->Position(((mfTopLimit-mfBottomLimit)*(lfValue-mfMin)/mfRange)+mfBottomLimit,mpSlider->Y());
    if(mpValue)
    {
        mpValue->Position(mpSlider->X(),mpSlider->Y());
        mpValue->Value(mfValue);
    }
};

void Lock(){mbLocked=true;};
void Unlock(){mbLocked=false;};

void OnSleep()
{
    _SLEEP(mpBackground);
    _SLEEP(mpSlider);
    _SLEEP(mpValue);
    _SLEEP(mpTitle);
};

void OnWake()
{
    _WAKE(mpBackground);
    _WAKE(mpSlider);
    _WAKE(mpValue);
    _WAKE(mpTitle);
};

void Transparency(uint8 liX)
{
    mpBackground->Transparency(liX);
    mpSlider->Transparency(liX+1);
    mpValue->Transparency(liX+1);
    mpTitle->Transparency(liX+1);
};

};


#endif
