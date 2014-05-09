#ifndef __WTCBUTTON_H__
#define __WTCBUTTON_H__

#if WT_FULL_VERSION_BAMBOO

class cFocusHandler
{
    cFocusHandler(){};
public:
  static void *spData;

  static bool Focus(void *lpObj=0);
  static void ReleaseFocus();
  static bool GetFocus(void *lpObj);
};

/**
 * \brief Base Class for Buttons. Contains code for detecting Mouse Hover, Button is Pressed and Clicked.
 * Contains basic code for Button functionality. See cButton and cTextButton for specific instances.
 *
 **/

class cButtonBase : virtual public cSignal
{
protected:
  c2DVf mvCenter;
  c2DVf mvRange;

  bool MouseOver;
  bool MousePressed;

  void *mpFocusPointer;

public:
    cButtonBase();
	///Will return true if the mouse cursor is over this button, irrespective of whether Mouse buttons are depressed.
	bool Hover();
	///Will return true if the mouse cursor is over this button and the left mouse button is depressed. Will be updated to include all mosue buttons
	bool Pressed();
	///Will return true if the user has clicked on the button and released the mouse while still over the button. Rigorous button clicking detection. Will only return true for a single frame.
    bool Clicked();
    ///Will return true if the user has clicked on the button. It will continue to return true until the user has released the mouse button or moved the mouse off of the button.
    bool PressedOn();
    ///Will return true if the user has clicked on the button. It will continue to return true until the user has released the mouse button.
    bool Dragged();

	///Will return true if the mouse cursor is over this button and the Activation state is true.
	bool Pressed(bool lbActivate);
	///Will return true if the user has activated the button (lbActivate) and released the activation while still over the button. Rigorous button activation detection. Will only return true for a single frame.
    bool Clicked(bool lbActivate);
    ///Will return true if the user has activated(lbActivate) while on the button. It will continue to return true until the user has released the activation or moved the cursor off of the button.
    bool PressedOn(bool lbActivate);
    ///Will return true if the user has activated the button. It will continue to return true until the user has released the activation.
    bool Dragged(bool lbActivate);

    void FocusPointer(void *lpData);
};

/**
 * \brief Renderable Button object for displaying an object as a rendered image.
 * Takes an image and will render it as a 2D image. Will check for mouse collisions and mouse button clicks to determine how user has interacted with the button.
 * see cButtonBase for Mouse Interaction Functions.
 **/
class cButton : public cImage, public cButtonBase
{

    public:

	using cImage::Width;
	using cImage::Height;

    cButton();
	cButton(cCamera *lpCamera);
    ~cButton();
	/// Sets the Position of the Image in 2D Pixels.
	void Position(float lfX,float lfY=0.0f,float lfZ=0.0f);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(float *lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c2DVf lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c3DVf lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c2DVf *lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c3DVf *lfX);
	/// Sets the Width of the Image in Pixels to lfWidth.
	void Width(float lfWidth);
	/// Sets the Height of the Image in Pixels to lfHeight.
    void Height(float lfHeight);
	/// Sets the Width of the Image in Pixels to lfSize. Will make the height the appropriate height to make the box square on screen.
	void Size(float lfSize);
};

/**
 * \brief Renderable Button object for displaying a button as a string of text.
 * Takes a font and will render as cText. Will check for mouse collisions and mouse button clicks to determine how user has interacted with the button.
 * Sizing for this object will size the individual characters. The Buttons size will be the size of the entire string with a blank character on either end of the string.
 * The object must be resized (even to the same size) after the text is changed to account for the new string length. This is to avoid slowing the base cText class.
 * see cButtonBase for Mouse Interaction Functions.
 **/
class cTextButton : public cText, public cButtonBase
{

public:

	cTextButton();
	cTextButton(cCamera *lpCamera);
	~cTextButton();
	/// Sets the Width of a single character in Pixels to lfWidth.
    void Width(float lfWidth);
	/// Sets the Height of a single character in Pixels to lfHeight.
    void Height(float lfHeight);
	/// Sets the Width of a single character in Pixels to lfSize. Will make the height the appropriate height to make the characters square onscreen.
	void Size(float lfSize);
	/// Sets the current position of the Text button.
	void Position(float lfX,float lfY=0.0f,float lfZ=0.0f);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(float *lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c2DVf lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c3DVf lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c2DVf *lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c3DVf *lfX);

/*
	// This should be called after the text is updated to ensure the box collision parameters are correct.
	void UpdateButtonSize();
*/
};

class cPointButton : public cPoint, public cButtonBase
{

public:
	cPointButton();
	cPointButton(cCamera *lpCamera);
	~cPointButton();
	/// Sets the Position of the Image in 2D Pixels.
	void Position(float lfX,float lfY=0.0f,float lfZ=0.0f);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(float *lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c2DVf lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c3DVf lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c2DVf *lfX);
	/// Sets the Position of the Image in 2D Pixels.
	void Position(c3DVf *lfX);

};

#endif // __WTCBUTTON_H__

#endif
