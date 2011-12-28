#ifndef __WTCBUTTON_H__
#define __WTCBUTTON_H__

/**
 * \brief Base Class for Buttons. Contains code for detecting Mouse Hover, Button is Pressed and Clicked.
 * Contains basic code for Button functionality. See cButton and cTextButton for specific instances.
 *
 **/

class cButtonBase
{
protected:
  float XCenter,XRange;
  float YCenter,YRange;

  bool MouseOver;

public:
	///Will return true if the mouse cursor is over this button, irrespective of whether Mouse buttons are depressed.
	bool Hover();
	///Will return true if the mouse cursor is over this button and the left mouse button is depressed. Will be updated to include all mosue buttons
	bool Pressed();
	///Will return true if the user has clicked on the button and released the mouse while still over the button. Rigorous button clicking detection. Will only return true for a single frame.
    bool Clicked();
};

/**
 * \brief Renderable Button object for displaying an object as a rendered image.
 * Takes an image and will render it as a 2D image. Will check for mouse collisions and mouse button clicks to determine how user has interacted with the button.
 * see cButtonBase for Mouse Interaction Functions.
 **/
class cButton : public cImage, public cButtonBase
{

    public:

    cButton();
    ~cButton();
	/// Sets the Position of the Image in 2D Pixels. Measured from the center of the screen.
	void Position(float lfX,float lfY);
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
 * see cButtonBase for Mouse Interaction Functions.
 **/
class cTextButton : public cText, public cButtonBase
{

 uint32 miPixelWidth;
 uint32 miPixelHeight;
public:

	cTextButton();
	~cTextButton();
	/// Sets the Position of the Image in 2D Pixels. Measured from the center of the screen.
	void Position(float lfX,float lfY);
	/// Sets the Width of a single character in Pixels to lfWidth.
    void Width(float lfWidth);
	/// Sets the Height of a single character in Pixels to lfHeight.
    void Height(float lfHeight);
	/// Sets the Width of a single character in Pixels to lfSize. Will make the height the appropriate height to make the characters square onscreen.
	void Size(float lfSize);


	void RenderPainter(uint8 liLevel);
	bool Hover();
/*
	// This should be called after the text is updated to ensure the box collision parameters are correct.
	void UpdateButtonSize();
*/
};

#endif // __WTCBUTTON_H__
