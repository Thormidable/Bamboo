#ifndef __WTCKEYTOGGLE_H__
#define __WTCKEYTOGGLE_H__


/// This class controls a Toggle on a boolean Value, based of a Keycode.
class cKeyToggle
{
    bool mbToggleState;
    bool mbKeyState;
public:
    cKeyToggle(bool lbToggleState=false);
    void SetState(bool lbState);
    bool Update(bool lbKeyState);
    bool UpdateOnToggle(bool lbKeyState);
    bool On();
    bool Off();

};

#endif
