#include "stdafx.h"
#include "../../WTBamboo.h"

cKeyToggle::cKeyToggle(bool lbToggleState)
{
 mbToggleState=lbToggleState;
 mbKeyState=true;
};

bool cKeyToggle::UpdateOnToggle(bool lbKeyState)
{
   if(lbKeyState)
 {
  if(!mbKeyState)
  {
   mbToggleState=!mbToggleState;
   mbKeyState=true;
   return 1;
  }
  mbKeyState=true;
 }
 else
 {
    mbKeyState=false;
 }
 return 0;
};
bool cKeyToggle::Update(bool lbKeyState)
{
 if(lbKeyState)
 {
  if(!mbKeyState)
  {
   mbToggleState=!mbToggleState;
  }
  mbKeyState=true;
 }
 else
 {
    mbKeyState=false;
 }
 return mbToggleState;
};

bool cKeyToggle::On()
{
 return mbToggleState;
};

bool cKeyToggle::Off()
{
    return !mbToggleState;
};

void cKeyToggle::SetState(bool lbState)
{
    mbToggleState=lbState;
};
