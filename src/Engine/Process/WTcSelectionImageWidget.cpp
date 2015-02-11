
#include "../../WTBamboo.h"


void cSelectionImageWidget::Run()
{
    if(!mbLocked)
    {
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            if(mpOptions[liCount]->Clicked() && liCount!=miSelection)
            {
               Selected(liCount);
            }
        }
    }
};

cSelectionImageWidget::cSelectionImageWidget(uint8 liOptions,c2DVf lfSize,c3DVf lcPosition,cTexture *mpTexture,cFont *mpFont,cCamera *lpCamera,cShaderProgram *lpImageShader,cShaderProgram *lpTextShader,cRGBA SelectedColor)
{
    mpCancel=0;
    Init(liOptions,lfSize,lcPosition,mpTexture,mpFont,lpCamera,lpImageShader,lpTextShader,SelectedColor);
};

void cSelectionImageWidget::Init(uint8 liOptions,c2DVf lfSize,c3DVf lcPosition,cTexture *mpTexture,cFont *lpFont,cCamera *lpCamera,cShaderProgram *lpImageShader,cShaderProgram *lpTextShader,cRGBA SelectedColor)
{
mpCancel=0;

 mbLocked=false;
 mcSelected=SelectedColor;
mfTextSize=lfSize;
miViewable=liOptions;
mpOptions=new cButton*[miViewable];

if(lpCamera) mpSelected=_CREATE(cImage(lpCamera));
else mpSelected=_CREATE(cImage);
mpSelected->Shader("Image2DUniformColorProgram");
mpSelected->SetUniform("UniformColor",SelectedColor.Color());
mpSelected->Width(mfTextSize[0]*1.3);
mpSelected->Height(mfTextSize[1]*1.3);
mpSelected->Transparency(2);

 for(uint8 liCount=0;liCount<miViewable;++liCount)
 {
    if(lpCamera) mpOptions[liCount]=_CREATE(cButton(lpCamera));
    else mpOptions[liCount]=_CREATE(cButton);

    if(lpTextShader) mpOptions[liCount]->Shader(lpTextShader);
    else mpOptions[liCount]->Shader("Image2DProgram");
    mpOptions[liCount]->Width(mfTextSize[0]);
    mpOptions[liCount]->Height(mfTextSize[1]);
    mpOptions[liCount]->Transparency(2);
 }


 if(lpCamera) mpBackground=_CREATE(cImage(lpCamera));
 else _CREATE(cImage);

 if(lpImageShader) mpBackground->Shader(lpImageShader);
 else mpBackground->Shader("Image2DProgram");

 mpBackground->Width(200);
 mpBackground->Height(((float)liOptions*1.5f+6)*mfTextSize[1]);
 if(mpTexture) mpBackground->AddTexture(mpTexture);
 mpBackground->Transparency(1);


if(lpCamera) mpTitle=_CREATE(cTextButton(lpCamera));
else mpTitle=_CREATE(cTextButton);

if(lpTextShader) mpTitle->Shader(lpTextShader);
else mpTitle->Shader("TextProgram");

if(lpFont) mpTitle->AddFont(lpFont);
mpTitle->AddFont("Pirulen");

mpTitle->Size(mfTextSize[1]);
mpTitle->SetUniformPointer("TextColor",mcSelected.Color());
mpTitle->Transparency(2);

SetPosition(lcPosition);

 miSelection=0;
 UpdateSelected();

}

void cSelectionImageWidget::NoCancelButton()
{
        if(mpCancel) {_KILL(mpCancel); mpCancel=0;Resize();}
        return;
}
void cSelectionImageWidget::CancelButton(cTexture *lpTexture,cShaderProgram *lpProg,cCamera *lpCamera)
{
      if(!mpCancel)
      {
          if(lpCamera) mpCancel=_CREATE(cButton(lpCamera));
          else mpCancel=_CREATE(cButton);
          mpCancel->Transparency(mpBackground->Transparency()+1);
          Resize();
      }

      mpCancel->Shader(lpProg);
      if(lpTexture) mpCancel->AddTexture("Texture0",lpTexture);

}


void cSelectionImageWidget::SetBackGroundTexture(cTexture *lpTexture)
{
    mpBackground->ClearTextureStack();
    if(lpTexture) mpBackground->AddTexture(lpTexture);
};

void cSelectionImageWidget::FocusPointer(void *lpData)
{
 for(uint32 liCount=0;liCount<miViewable;++liCount) mpOptions[liCount]->FocusPointer(lpData);
 if(mpCancel) mpCancel->FocusPointer(lpData);
};

void cSelectionImageWidget::Resize()
{

    if(mpCancel)
    {
        mpCancel->Width(mfTextSize[1]);
        mpCancel->Height(mfTextSize[1]);
        mpBackground->Height((float)(miViewable*1.5f+5)*mfTextSize[1]);
    }
    else
    {
        mpBackground->Height((float)(miViewable*1.5f+4)*mfTextSize[1]);
    }

    mpTitle->Size(mfTextSize[1]);
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            mpOptions[liCount]->Width(mfTextSize[0]);
            mpOptions[liCount]->Height(mfTextSize[1]);
        }

        mpSelected->Width(mfTextSize[0]*1.3f);
        mpSelected->Height(mfTextSize[1]*1.3f);

    SetPosition(c3DVf(mpBackground->Position()));
};
void cSelectionImageWidget::Resize(c2DVf lfSize)
{
    mfTextSize=lfSize;

    if(mpCancel)
    {
        mpCancel->Width(mfTextSize[1]);
        mpCancel->Height(mfTextSize[1]);
        mpBackground->Height((float)(miViewable*1.4f+5)*mfTextSize[1]);
    }
    else
    {
        mpBackground->Height((float)(miViewable*1.4f+4)*mfTextSize[1]);
    }

    mpTitle->Size(mfTextSize[1]);
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            mpOptions[liCount]->Width(mfTextSize[0]);
            mpOptions[liCount]->Height(mfTextSize[1]);
        }

        mpSelected->Width(mfTextSize[0]*1.3f);
        mpSelected->Height(mfTextSize[1]*1.3f);
    SetPosition(c3DVf(mpBackground->Position()));
};

void cSelectionImageWidget::SetWidth(float lfWidth)
{
    mpBackground->Width(lfWidth);
};

void cSelectionImageWidget::SetWidth()
{
    mpBackground->Width(mfTextSize[0]*1.5f);
};


string cSelectionImageWidget::Title(){return mpTitle->Text();};
void cSelectionImageWidget::Title(string lsTitle){mpTitle->Text(lsTitle);};


void cSelectionImageWidget::SetOptionTexture(uint32 liOption,cTexture *lpText)
{
    mpOptions[liOption]->AddTexture("Texture0",lpText);
};

void cSelectionImageWidget::Stop()
{
 for(uint8 liCount=0;liCount<miViewable;++liCount)
 {
     _KILL(mpOptions[liCount]);
 }
 delete []mpOptions;
 _KILL(mpBackground);
 _KILL(mpTitle);
if(mpCancel) _KILL(mpCancel);
if(mpSelected) _KILL(mpSelected);
};

void cSelectionImageWidget::SetPosition(c3DVf lfPosition)
{
    c3DVf lfPos=lfPosition;
    mpBackground->Position(lfPos.v);

    lfPos[1]+=mpBackground->Height()*0.5-mfTextSize[1];
    mpTitle->Position(lfPos.v);
    lfPos[1]-=2.0f*mfTextSize[1];

    for(uint8 liCount=0;liCount<miViewable;++liCount)
    {
        mpOptions[liCount]->Position(lfPos[0],lfPos[1]);
        lfPos[1]-=mfTextSize[1]*1.4;
    }

    if(mpCancel)
    {
        mpCancel->Position(lfPos[0]+mpBackground->Width()*0.5-mfTextSize[1]*1.2f,lfPos[1]);
    }

    UpdateSelected();

}


uint32 cSelectionImageWidget::Selected()
{
    return miSelection;
};
void cSelectionImageWidget::Selected(uint32 liNew)
{
    if(liNew!=miSelection)
    {
        miSelection=liNew;
        UpdateSelected();
    }
};

void cSelectionImageWidget::UpdateSelected()
{
    c2DVf lfT=mpTitle->Position();
    mpSelected->Position(lfT[0],lfT[1]-(miSelection+2)*mfTextSize[1]*1.4f);
}

void cSelectionImageWidget::Lock()
{
    mbLocked=true;
};
void cSelectionImageWidget::Unlock()
{
    mbLocked=false;
};

void cSelectionImageWidget::Transparency(uint8 liTrans)
{
  mpBackground->Transparency(liTrans);
  mpSelected->Transparency(liTrans+1);
  for(uint8 liCount=0;liCount<miViewable;++liCount)
  {
   mpOptions[liCount]->Transparency(liTrans+2);
  }
  mpTitle->Transparency(liTrans+2);
  if(mpCancel) mpCancel->Transparency(liTrans+2);
};

void cSelectionImageWidget::OnSleep()
{
    for(uint8 liCount=0;liCount<miViewable;++liCount)
    {
        _SLEEP(mpOptions[liCount]);
    }
  _SLEEP(mpBackground);
  _SLEEP(mpTitle);
  _SLEEP(mpSelected);
  if(mpCancel) _SLEEP(mpCancel);
};
void cSelectionImageWidget::OnWake()
{
    for(uint8 liCount=0;liCount<miViewable;++liCount)
    {
        _WAKE(mpOptions[liCount]);
    }
  _WAKE(mpBackground);
  _WAKE(mpTitle);
  _WAKE(mpSelected);
  if(mpCancel) _WAKE(mpCancel);
};

void cSelectionImageSliderWidget::Run()
{
    if(!mbLocked)
    {
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            if(mpOptions[liCount]->Clicked() && liCount!=miSelection)
            {
                Selected(liCount);
            }
        }

        if(mpSlider->Dragged())
	{
	  float lfY=_MOUSE->Y();
	  if(lfY>mfTopLimit) lfY=mfTopLimit;
	  else if(lfY<mfBottomLimit) lfY=mfBottomLimit;

	  mpSlider->Position(mpSlider->X(),lfY);
	  UpdateShown((lfY-mfTopLimit)/(mfTopLimit-mfBottomLimit)*(miSpaces-miViewable));
       }
    }
};

void cSelectionImageSliderWidget::FocusPointer(void *lpData)
{
 for(uint32 liCount=0;liCount<miViewable;++liCount) mpOptions[liCount]->FocusPointer(lpData);
 if(mpCancel) mpCancel->FocusPointer(lpData);
 mpSlider->FocusPointer(lpData);
};

void cSelectionImageSliderWidget::Stop()
{
 cSelectionImageWidget::Stop();
 _KILL(mpSlider);
};

void cSelectionImageSliderWidget::CalculateSliderLimits()
{
  if(miViewable>miSpaces)
  {
      mfTopLimit=mfBottomLimit=mpBackground->Y();
  }
  else
  {
    mfBottomLimit=mpBackground->Y()-mpBackground->Height()*0.5+mfTextSize[1]*2;
    mfTopLimit=mpBackground->Y()+mpBackground->Height()*0.5-mfTextSize[1]*3;
  }


};

cButton *cSelectionImageSliderWidget::Slider()
{
      return mpSlider;
}

void cSelectionImageSliderWidget::PositionSlider(uint32 liStart)
{
  if(liStart>miSpaces-miViewable) miStart=miSpaces-miViewable;
  else miStart=liStart;

  if(miSpaces>miViewable)
  {
      mpSlider->Position(mpBackground->X()+mpBackground->Width()*0.5-mfTextSize[1]*1.2f,mfTopLimit-(float)(miStart/(miSpaces-miViewable))*(mfTopLimit-mfBottomLimit));
  }
  else
  {
      mpSlider->Position(mpBackground->X()+mpBackground->Width()*0.5-mfTextSize[1]*1.2f,(mfTopLimit+mfBottomLimit)*0.5);
  }

};

void cSelectionImageSliderWidget::UpdateShown(uint32 liStart)
{
    if(liStart+miViewable>miSpaces)
    {
        if(miViewable<=miSpaces) miStart=miSpaces-miViewable;
        else miStart=0;
    }
    else miStart=liStart;
  uint32 liCount;
  for(liCount=0;liCount<miViewable && liCount+liStart<miSpaces;++liCount)
  {
    mpOptions[liCount]->AddTexture("Texture0",mpList[liCount+liStart]);
  }
  while(liCount<miViewable)
  {
      mpOptions[liCount]->AddTexture("Texture0",0);
      ++liCount;
  }
  UpdateSelected();
};

void cSelectionImageSliderWidget::UpdateSliderPos()
{
  mpSlider->Position(mpSlider->X(),(float)(miStart/(miSpaces)));
};

void cSelectionImageSliderWidget::SetOptionTexture(uint32 liOption,cTexture *lpText)
{
     if(liOption>=miSpaces)
     {
       ResizeSpaces(liOption);
     }
    mpList[liOption]=lpText;

    if(liOption>=miStart && liOption<miStart+miViewable) cSelectionImageWidget::SetOptionTexture(liOption-miStart,lpText);

};

void cSelectionImageSliderWidget::ResizeSpaces(uint32 liOption)
{
     if(liOption<miSpaces) miSpaces=liOption;

       cTexture **lpList=new cTexture*[liOption];
       for(uint32 liCount=0;liCount<miSpaces;++liCount)
       {
        lpList[liCount]=mpList[liCount];
       }
       delete []mpList;
       mpList=lpList;

    miSpaces=liOption;

    CalculateSliderLimits();
};

void cSelectionImageSliderWidget::SetPosition(c3DVf lcPos)
{
  cSelectionImageWidget::SetPosition(lcPos);
  CalculateSliderLimits();
  PositionSlider(miStart);
};

void cSelectionImageSliderWidget::Resize(c2DVf lfSize)
{
  cSelectionImageWidget::Resize(lfSize);
  mpSlider->Height(lfSize[1]);
  CalculateSliderLimits();
  PositionSlider(miStart);
};
void cSelectionImageSliderWidget::Resize()
{
  cSelectionImageWidget::Resize();
  PositionSlider(miStart);
};

cSelectionImageSliderWidget::cSelectionImageSliderWidget(uint8 liOptions,c2DVf lfSize,c3DVf lcPosition,cTexture *lpTexture,cFont *lpFont,cCamera *lpCamera,cShaderProgram *lpImageShader,cShaderProgram *lpTextShader,cTexture *lpSliderText,cRGBA SelectedColor) : cSelectionImageWidget(liOptions,lfSize,lcPosition,lpTexture,lpFont,lpCamera,lpImageShader,lpTextShader,SelectedColor)
{
  miStart=0;
  miSpaces=liOptions;
  mpList=new cTexture*[liOptions];

  if(lpCamera) mpSlider=_CREATE(cButton(lpCamera));
  else mpSlider=_CREATE(cButton);

  if(lpImageShader) mpSlider->Shader(lpImageShader);
  else mpSlider->Shader("Image2DProgram");
  mpSlider->AddTexture("Texture0",lpSliderText);
  mpSlider->Width(lfSize[0]);
  mpSlider->Height(lfSize[1]);

  CalculateSliderLimits();
  PositionSlider(0);

};

void cSelectionImageSliderWidget::Transparency(uint8 liTrans)
{
 cSelectionImageWidget::Transparency(liTrans);
 mpSlider->Transparency(liTrans+2);
};

void cSelectionImageSliderWidget::OnSleep()
{
  cSelectionImageWidget::OnSleep();
  _SLEEP(mpSlider);
};

void cSelectionImageSliderWidget::OnWake()
{
  cSelectionImageWidget::OnWake();
  _WAKE(mpSlider);
};

void cSelectionImageSliderWidget::UpdateSelected()
{
    c2DVf lfT=mpTitle->Position();
    if(miSelection>miStart && miSelection<miStart+miViewable)
    mpSelected->Position(lfT[0],lfT[1]-(miSelection-miStart+2)*mfTextSize[1]*1.4f);
}
