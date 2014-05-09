#include "stdafx.h"
#include "../../WTBamboo.h"

 cToggleButton::cToggleButton(cTexture *lpOn,cTexture *lpOff,cTexture *lpHover)
 {
     mpOn=lpOn;
     mpOff=lpOff;
     mpHover=lpHover;
     mpButton=new cButton(_CAMERA);
 };

 cToggleButton::cToggleButton(cCamera *lpCamera,cTexture *lpOn,cTexture *lpOff,cTexture *lpHover)
 {
     mpOn=lpOn;
     mpOff=lpOff;
     mpHover=lpHover;
     mpButton=new cButton(lpCamera);
 };

 void cToggleButton::Run()
 {
     mcState.UpdateOnToggle(mpButton->Clicked());

     if(mpButton->Hover())
     {
         if(mpHover && mpLast!=mpHover)
         {
            mpButton->AddTexture("Texture0",mpHover); mpLast=mpHover;
         }
    }
     else
     {
        if(mcState.On())
        {
          if(mpLast!=mpOn)
          {
              mpButton->AddTexture("Texture0",mpOn);
              mpLast=mpOn;
          }
        }
        else
        {
          if(mpLast!=mpOff)
          {
            mpButton->AddTexture("Texture0",mpOff);
            mpLast=mpOff;
          }
        }
     }
 };

 void cToggleButton::Stop()
 {
    _KILL(mpButton);
    mpButton=0;
 };

	bool cToggleButton::Hover(){return mpButton->Hover();};
    cButton *cToggleButton::ButtonObject(){return mpButton;};

    bool cToggleButton::On(){return mcState.On();};
    bool cToggleButton::Off(){return mcState.Off();};

    void cToggleButton::State(bool lbState)
    {
        mcState.SetState(lbState);
    };

void cToggleButton::OnSleep()
{
    _SLEEP(mpButton);
};

void cToggleButton::OnWake()
{
    _WAKE(mpButton);
};

void cToggleButton::FocusPointer(void *lpData)
{
 mpButton->FocusPointer(lpData);
};
