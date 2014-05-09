
#include "../../WTBamboo.h"


void cSelectionWidget::Run()
{
    if(!mbLocked)
    {
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            if(mpOptions[liCount]->Clicked() && liCount!=miSelection)
            {
                mpOptions[miSelection]->SetUniformPointer("TextColor",mcUnselected.Color());
                mpOptions[liCount]->SetUniformPointer("TextColor",mcSelected.Color());
                miSelection=liCount;
            }
        }
    }
};

cSelectionWidget::cSelectionWidget(uint8 liOptions,float lfSize,c3DVf lcPosition,cTexture *mpTexture,cFont *lpFont,cCamera *lpCamera,cShaderProgram *lpImageShader,cShaderProgram *lpTextShader,cRGBA UnselectedColor,cRGBA SelectedColor)
{
    mpCancel=0;
    Init(liOptions,lfSize,lcPosition,mpTexture,lpFont,lpCamera,lpImageShader,lpTextShader,UnselectedColor,SelectedColor);
};

void cSelectionWidget::Init(uint8 liOptions,float lfSize,c3DVf lcPosition,cTexture *mpTexture,cFont *lpFont,cCamera *lpCamera,cShaderProgram *lpImageShader,cShaderProgram *lpTextShader,cRGBA UnselectedColor,cRGBA SelectedColor)
{
mpCancel=0;

 mbLocked=false;
 mcSelected=SelectedColor;
 mcUnselected=UnselectedColor;
mfTextSize=lfSize;
miViewable=liOptions;
mpOptions=new cTextButton*[miViewable];
 for(uint8 liCount=0;liCount<miViewable;++liCount)
 {
    if(lpCamera) mpOptions[liCount]=_CREATE(cTextButton(lpCamera));
    else mpOptions[liCount]=_CREATE(cTextButton);

    if(lpTextShader) mpOptions[liCount]->Shader(lpTextShader);
    else mpOptions[liCount]->Shader("TextProgram");
    if(lpFont) mpOptions[liCount]->AddFont(lpFont);
    mpOptions[liCount]->AddFont("Pirulen");
    mpOptions[liCount]->Size(mfTextSize);
    mpOptions[liCount]->SetUniformPointer("TextColor",mcUnselected.Color());
    mpOptions[liCount]->Transparency(2);
 }
 miSelection=0;
 mpOptions[0]->SetUniformPointer("TextColor",mcSelected.Color());



 if(lpCamera) mpBackground=_CREATE(cImage(lpCamera));
 else _CREATE(cImage);

 if(lpImageShader) mpBackground->Shader(lpImageShader);
 else mpBackground->Shader("Image2DProgram");

 mpBackground->Width(200);
 mpBackground->Height((liOptions+4)*mfTextSize);
 if(mpTexture) mpBackground->AddTexture(mpTexture);
 mpBackground->Transparency(1);


if(lpCamera) mpTitle=_CREATE(cTextButton(lpCamera));
else mpTitle=_CREATE(cTextButton);

if(lpTextShader) mpTitle->Shader(lpTextShader);
else mpTitle->Shader("TextProgram");

if(lpFont) mpTitle->AddFont(lpFont);
mpTitle->AddFont("Pirulen");

mpTitle->Size(mfTextSize);
mpTitle->SetUniformPointer("TextColor",mcSelected.Color());
mpTitle->Transparency(2);

SetPosition(lcPosition);



}

void cSelectionWidget::NoCancelButton()
{
        if(mpCancel) {_KILL(mpCancel); mpCancel=0;Resize();}
        return;
}
void cSelectionWidget::CancelButton(cTexture *lpTexture,cShaderProgram *lpProg,cCamera *lpCamera)
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


void cSelectionWidget::SetBackGroundTexture(cTexture *lpTexture)
{
    mpBackground->ClearTextureStack();
    if(lpTexture) mpBackground->AddTexture(lpTexture);
};
void cSelectionWidget::SetFont(cFont *lpTexture)
{
    if(lpTexture)
    {
        mpTitle->ClearTextureStack();
        mpTitle->AddTexture(lpTexture);
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            mpOptions[liCount]->ClearTextureStack();
            mpOptions[liCount]->AddFont(lpTexture);
        }
    }
    else
    {
        mpTitle->ClearTextureStack();
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            mpOptions[liCount]->ClearTextureStack();
        }
    }
};


void cSelectionWidget::Resize()
{

    if(mpCancel)
    {
        mpCancel->Width(mfTextSize);
        mpCancel->Height(mfTextSize);
        mpBackground->Height((miViewable+5)*mfTextSize);
    }
    else
    {
        mpBackground->Height((miViewable+4)*mfTextSize);
    }

    mpTitle->Size(mfTextSize);
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            mpOptions[liCount]->Size(mfTextSize);
        }

    SetPosition(c3DVf(mpBackground->Position()));
};
void cSelectionWidget::Resize(float lfSize)
{
    mfTextSize=lfSize;

    if(mpCancel)
    {
        mpCancel->Width(mfTextSize);
        mpCancel->Height(mfTextSize);
        mpBackground->Height((miViewable+5)*mfTextSize);
    }
    else
    {
        mpBackground->Height((miViewable+4)*mfTextSize);
    }

    mpTitle->Size(mfTextSize);
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            mpOptions[liCount]->Size(mfTextSize);
        }

    SetPosition(c3DVf(mpBackground->Position()));
};

void cSelectionWidget::SetWidth(float lfWidth)
{
    mpBackground->Width(lfWidth);
};

void cSelectionWidget::SetWidth()
{
    uint16 liLength=mpTitle->Text().length();
    for(uint8 liCount=0;liCount<miViewable;++liCount)
    {
        if(liLength<mpOptions[liCount]->Text().length()) liLength=mpOptions[liCount]->Text().length();
    }

    mpBackground->Width((liLength+2)*mfTextSize);

};


string cSelectionWidget::Title(){return mpTitle->Text();};
void cSelectionWidget::Title(string lsTitle){mpTitle->Text(lsTitle);};


void cSelectionWidget::SetOptionText(uint32 liOption,string lsText)
{
    mpOptions[liOption]->Text(lsText);
    mpOptions[liOption]->Size(mfTextSize);
    if(mpBackground->Width()<(lsText.length()+2)*mfTextSize)
    {
        mpBackground->Width((lsText.length()+2)*mfTextSize);
    }
};

void cSelectionWidget::Stop()
{
 for(uint8 liCount=0;liCount<miViewable;++liCount)
 {
     _KILL(mpOptions[liCount]);
 }
 delete []mpOptions;
 _KILL(mpBackground);
 _KILL(mpTitle);
if(mpCancel) _KILL(mpCancel);
};

void cSelectionWidget::SetPosition(c3DVf lfPosition)
{
    c3DVf lfPos=lfPosition;
    mpBackground->Position(lfPos.v);

    lfPos[1]+=mpBackground->Height()*0.5-mfTextSize;
    mpTitle->Position(lfPos.v);
    lfPos[1]-=2.0f*mfTextSize;

    for(uint8 liCount=0;liCount<miViewable;++liCount)
    {
        mpOptions[liCount]->Position(lfPos[0],lfPos[1]);
        lfPos[1]-=mfTextSize*1.1;
    }

    if(mpCancel)
    {
        mpCancel->Position(lfPos[0]+mpBackground->Width()*0.5-mfTextSize*1.2f,lfPos[1]);
    }


}


uint32 cSelectionWidget::Selected()
{
    return miSelection;
};
void cSelectionWidget::Selected(uint32 liNew)
{
    if(liNew!=miSelection)
    {
        mpOptions[miSelection]->SetUniformPointer("TextColor",mcUnselected.Color());
        mpOptions[liNew]->SetUniformPointer("TextColor",mcSelected.Color());
        miSelection=liNew;
    }
};

void cSelectionWidget::Lock()
{
    mbLocked=true;
};
void cSelectionWidget::Unlock()
{
    mbLocked=false;
};

void cSelectionWidget::Transparency(uint8 liTrans)
{
  mpBackground->Transparency(liTrans);
  for(uint8 liCount=0;liCount<miViewable;++liCount)
  {
   mpOptions[liCount]->Transparency(liTrans+1);
  }
  mpTitle->Transparency(liTrans+1);
  if(mpCancel) mpCancel->Transparency(liTrans+1);
};

string cSelectionWidget::GetText(uint32 liText)
{
    return mpOptions[liText]->Text();
};

cFileListWidget::cFileListWidget(string lsPath,uint8 liOptions,float lfSize,c3DVf lcPosition,cTexture *mpTexture,cFont *lpFont,cCamera *lpCamera,cShaderProgram *lpImageShader,cShaderProgram *lpTextShader,cRGBA UnselectedColor,cTexture *lpSliderText) : cSelectionSliderWidget(liOptions,lfSize,lcPosition,mpTexture,lpFont,lpCamera,lpImageShader,lpTextShader,UnselectedColor,UnselectedColor,lpSliderText)
{
    mpFiles=new cDirectoryFileList(lsPath);
    ResizeSpaces(mpFiles->Files());
    for(uint16 liCount=0;liCount<mpFiles->Files();++liCount)
    {
        SetOptionText(liCount,mpFiles->File(liCount));
    }
    mbSelection=false;

}

void cSelectionWidget::FocusPointer(void *lpData)
{
    for(uint32 liCount=0;liCount<miViewable;++liCount) mpOptions[liCount]->FocusPointer(lpData);
 if(mpCancel) mpCancel->FocusPointer(lpData);
};



void cSelectionWidget::OnSleep()
{
    for(uint8 liCount=0;liCount<miViewable;++liCount)
    {
        _SLEEP(mpOptions[liCount]);
    }
  _SLEEP(mpBackground);
  _SLEEP(mpTitle);
  if(mpCancel) _SLEEP(mpCancel);
};
void cSelectionWidget::OnWake()
{
    for(uint8 liCount=0;liCount<miViewable;++liCount)
    {
        _WAKE(mpOptions[liCount]);
    }
  _WAKE(mpBackground);
  _WAKE(mpTitle);
  if(mpCancel) _WAKE(mpCancel);
};

void cFileListWidget::Run()
{
    if(!mbLocked)
    {
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            if(mpOptions[liCount]->Clicked())
            {
                miSelection=liCount+miStart;
                mbSelection=true;
            }
        }

    }

       if(mpSlider->Dragged())
        {
          float lfY=_MOUSE->Y();
          if(lfY>mfTopLimit) lfY=mfTopLimit;
          else if(lfY<mfBottomLimit) lfY=mfBottomLimit;

          mpSlider->Position(mpSlider->X(),lfY);
          UpdateShown((mfTopLimit-lfY)/(mfTopLimit-mfBottomLimit)*(miSpaces-miViewable));
       }

    if(mpCancel && mpCancel->Clicked())
    {
        _SLEEP_THIS();
    }
};

void cFileListWidget::Stop()
{
    cSelectionSliderWidget::Stop();
    delete mpFiles;
};

bool cFileListWidget::Selection()
{
    return mbSelection;
};

string cFileListWidget::SelectedPath()
{
    return mpFiles->File(miSelection);
};


void cSelectionSliderWidget::Run()
{
    if(!mbLocked)
    {
        for(uint8 liCount=0;liCount<miViewable;++liCount)
        {
            if(mpOptions[liCount]->Clicked() && liCount!=miSelection)
            {
                mpOptions[miSelection]->SetUniformPointer("TextColor",mcUnselected.Color());
                mpOptions[liCount]->SetUniformPointer("TextColor",mcSelected.Color());
                miSelection=liCount;
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

void cSelectionSliderWidget::Stop()
{
 cSelectionWidget::Stop();
 _KILL(mpSlider);
};

void cSelectionSliderWidget::FocusPointer(void *lpData)
{
 cSelectionWidget::FocusPointer(lpData);
 mpSlider->FocusPointer(lpData);
};

void cSelectionSliderWidget::CalculateSliderLimits()
{
  if(miViewable>miSpaces)
  {
      mfTopLimit=mfBottomLimit=mpBackground->Y();
  }
  else
  {
    mfBottomLimit=mpBackground->Y()-mpBackground->Height()*0.5+mpSlider->Height()*2;
    mfTopLimit=mpBackground->Y()+mpBackground->Height()*0.5-mfTextSize*3;
  }


};

cButton *cSelectionSliderWidget::Slider()
{
      return mpSlider;
}

void cSelectionSliderWidget::PositionSlider(uint32 liStart)
{
  if(liStart>miSpaces-miViewable) miStart=miSpaces-miViewable;
  else miStart=liStart;

  if(miSpaces>miViewable)
  {
      mpSlider->Position(mpBackground->X()+mpBackground->Width()*0.5-mfTextSize*1.2f,mfTopLimit-(float)(miStart/(miSpaces-miViewable))*(mfTopLimit-mfBottomLimit));
  }
  else
  {
      mpSlider->Position(mpBackground->X()+mpBackground->Width()*0.5-mfTextSize*1.2f,(mfTopLimit+mfBottomLimit)*0.5);
  }

};

void cSelectionSliderWidget::UpdateShown(uint32 liStart)
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
    mpOptions[liCount]->Text(mpList[liCount+liStart]);
    if(liCount+liStart==miSelection) mpOptions[liCount]->SetUniformPointer("TextColor",mcSelected.Color());
    else mpOptions[liCount]->SetUniformPointer("TextColor",mcUnselected.Color());
  }
  while(liCount<miViewable)
  {
      mpOptions[liCount]->Text("");
      ++liCount;
  }
};

void cSelectionSliderWidget::UpdateSliderPos()
{
  mpSlider->Position(mpSlider->X(),(float)(miStart/(miSpaces)));
};

void cSelectionSliderWidget::SetOptionText(uint32 liOption,string lsText)
{
     if(liOption>=miSpaces)
     {
       ResizeSpaces(liOption);
     }
    mpList[liOption]=lsText;

    if(liOption>=miStart && liOption<miStart+miViewable) cSelectionWidget::SetOptionText(liOption-miStart,lsText);

};

void cSelectionSliderWidget::ResizeSpaces(uint32 liOption)
{
     if(liOption<miSpaces) miSpaces=liOption;

       string *lpList=new string[liOption];
       for(uint32 liCount=0;liCount<miSpaces;++liCount)
       {
	  lpList[liCount]=mpList[liCount];
       }
       delete []mpList;
       mpList=lpList;

    miSpaces=liOption;

    CalculateSliderLimits();
};

void cSelectionSliderWidget::SetPosition(c3DVf lcPos)
{
  cSelectionWidget::SetPosition(lcPos);
  CalculateSliderLimits();
  PositionSlider(miStart);
};

string cSelectionSliderWidget::GetText(uint32 liText)
{
  return mpList[liText];
};

void cSelectionSliderWidget::Resize(float lfSize)
{
  cSelectionWidget::Resize(lfSize);
  mpSlider->Height(lfSize);
  CalculateSliderLimits();
  PositionSlider(miStart);
};
void cSelectionSliderWidget::Resize()
{
  cSelectionWidget::Resize();
  PositionSlider(miStart);
};

cSelectionSliderWidget::cSelectionSliderWidget(uint8 liOptions,float lfSize,c3DVf lcPosition,cTexture *lpTexture,cFont *lpFont,cCamera *lpCamera,cShaderProgram *lpImageShader,cShaderProgram *lpTextShader,cRGBA UnselectedColor,cRGBA SelectedColor,cTexture *lpSliderText) : cSelectionWidget(liOptions,lfSize,lcPosition,lpTexture,lpFont,lpCamera,lpImageShader,lpTextShader,UnselectedColor,SelectedColor)
{
  miStart=0;
  miSpaces=liOptions;
  mpList=new string[liOptions];

  if(lpCamera) mpSlider=_CREATE(cButton(lpCamera));
  else mpSlider=_CREATE(cButton);

  if(lpImageShader) mpSlider->Shader(lpImageShader);
  else mpSlider->Shader("Image2DProgram");
  mpSlider->AddTexture("Texture0",lpSliderText);
  mpSlider->Width(lfSize);
  mpSlider->Height(lfSize);

  CalculateSliderLimits();
  PositionSlider(0);


};

void cSelectionSliderWidget::Transparency(uint8 liTrans)
{
 cSelectionWidget::Transparency(liTrans);
 mpSlider->Transparency(liTrans+1);
};

void cSelectionSliderWidget::OnSleep()
{
  cSelectionWidget::OnSleep();
  _SLEEP(mpSlider);
};

void cSelectionSliderWidget::OnWake()
{
  cSelectionWidget::OnWake();
  _WAKE(mpSlider);
};
