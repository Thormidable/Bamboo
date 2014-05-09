#ifndef __WTCTEXTBOXWIDGET_H__
#define __WTCTEXTBOXWIDGET_H__

/**
* \brief Class for controlling a editable Textbox. Will allow the user to change the contents using the keyboard.
Requires a cTexture object to render the border and a cFont object for rendering the text.

*/
class cTextBoxWidget : public cProcess
{
 float mfSize;
 bool mbLocked;
 bool mbSelected;
 bool mbLastMouse;
 void Run();
public:
 cText *mpTextField;
 cButton *mpBackground;
public:

/**
    \brief Constructor for the class. Takes all relevant data.
    \param lcPosition Position of the cTextBox (Center).
    \param lcSize Size of the text box (x,y).
    \param lpTexture cTexture pointer for the cTexture object to use as the border of the Textbox.
    \param lpFont cFont pointer for the Font to use for the text.
    \param TextColor cRGBA object to set the color of the text.
    \param lpCamera cCamera object to be a parent of this object.
    \param lpImageShader cShaderProgram to use for rendering the border image. Should take a bitmap in Texture0.
    \param lpTextShader cShaderProgram to use for rendering the text. Should take a 4 float vect in TextColor and a bitmap in Font0.

*/
 cTextBoxWidget(c3DVf lcPosition,c2DVf lvSize,cTexture *lpTexture=0,cFont *lpFont=0,cRGBA TextColor=cRGBA(0.9f,0.9f,0.9f,1.0f),cCamera *lpCamera=0,cShaderProgram *lpImageShader=0,cShaderProgram *lpTextShader=0);
 ///Will Set the Position of the cTextbox object (centre).
 void SetPosition(c3DVf lcPos);
 void Stop();
 ///Will disable User editing of text.
 void Lock();
 ///Will enable User editing of text.
 void Unlock();
 ///Will set the text in the textbox.
 void Text(string lsString);
 ///Will set the color of the text in the text box.
 void TextColor(cRGBA lcCol);
 ///Will return a string reference to the text in the box.
 string &Text();

 void OnWake();
 void OnSleep();

 void FocusPointer(void *lpData);

};

#endif
