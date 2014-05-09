#ifndef __WTCTOGGLEBUTTON_H__
#define __WTCTOGGLEBUTTON_H__

/**
* \brief This is explicitly a cProcess object for handling a toggleable button
* It is not a renderable object. To access it's renderable component access the pointer from ButtonObject().
* It will take three images for the button, On, Off and Hover. These are selected based on the state of the button.
* Updates the state of the button. Should be checked for state not for being clicked.
*/
class cToggleButton: public cProcess
{
 cButton *mpButton;
 cTexture *mpOn;
 cTexture *mpOff;
 cTexture *mpHover;
 cTexture *mpLast;
 cKeyToggle mcState;
public:
    /// Constructor. Takes the textures for the different states of the button.
    cToggleButton(cTexture *lpOn,cTexture *lpOff=0,cTexture *lpHover=0);
    /// Constructor. Takes the cCamera object to use and the textures for the different states of the button.
    cToggleButton(cCamera *lpCamera,cTexture *lpOn,cTexture *lpOff=0,cTexture *lpHover=0);
    ///Update Function for this cProcess.
    void Run();
    /// Stop Function for this cProcess.
    void Stop();

    ///Will return true if the mouse cursor is over this button, irrespective of whether Mouse buttons are depressed.
	bool Hover();

    ///Will return true if the button is in the on state. Otherwise will return false.
    bool On();
    ///Will return false if the button is in the off state. Otherwise will return false.
    bool Off();

    void State(bool lbState);

    ///Will return a pointer to allow the user to access the cRenderObject components of this object.
    cButton *ButtonObject();

    void OnSleep();
    void OnWake();

    void FocusPointer(void *lpData);
};

#endif
