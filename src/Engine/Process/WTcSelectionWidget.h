#ifndef __WTCSELECTIONWIDGET_H__
#define __WTCSELECTIONWIDGET_H__

/**
 \brief A Derived cProcess class containing Renderable objects to forma widget for holding and processing a list of individually selectable objects.
 This class holds and displays a list of string objects one of which can be selected at a time using the mouse.
 It will automatically process user interactions and the currently selected item can be accessed using it's position in the list.
 This is a cProcess derived object and should not be deleted. It should instead be sent a _KILL() Signal to allow it to clean up correctly.
*/
class cSelectionWidget : public cProcess
{
protected:
void Run();
public:
 cTextButton **mpOptions;
 cButton *mpCancel;
 cText *mpTitle;
 uint32 miSelection;
 uint8 miViewable;
 cImage *mpBackground;
 cRGBA mcUnselected;
 cRGBA mcSelected;
 float mfTextSize;
 bool mbLocked;

 /**
    \brief cSelectionWidget
    \param liOptions Number of list items desired.
    \param lfSize Size of the text characters used.
    \param lcPosition Position of the Object (Screen Co-ordinates)
    \param lpTexture Pointer to the cTexture Object to use for the back end of the object.
    \param lpFont Pointer to the cFont Object to use for rendering the Text.
    \param lpCamera Pointer to the cCamera Object to be made owner of this object.
    \param lpImageShader Pointer to a cShaderProgram Object to be used for rendering the back end of the object. Will use lpTexture in Texture slot Texture0.
    \param lpTextShader Pointer to a cShaderProgram Object to be used for rendering the text. Must have a vec4 called TextColor for accepting a Font Color. Will use lpFont in Texture Slot Font0.
    \param UnselectedColor cRGBA Color to use for the unselected Items.
    \param SelectedColor cRGBA Color to use for the selected Item.
 */
 cSelectionWidget(uint8 liOptions,float lfSize,c3DVf lcPosition,cTexture *lpTexture=0,cFont *lpFont=0,cCamera *lpCamera=0,cShaderProgram *lpImageShader=0,cShaderProgram *lpTextShader=0,cRGBA UnselectedColor=cRGBA(0.3f,0.3f,0.3f,1.0f),cRGBA SelectedColor=cRGBA(0.9f,0.9f,0.9f,1.0f));
 ///Will Reinitialise the Object to start it fresh again. Parameters are same as the Constructor.
 void Init(uint8 liOptions,float lfSize,c3DVf lcPosition,cTexture *lpTexture,cFont *lpFont,cCamera *lpCamera,cShaderProgram *lpImageShader,cShaderProgram *lpTextShader,cRGBA UnselectedColor,cRGBA SelectedColor);
 ///Will Set the text for item liOption as lsText.
 virtual void SetOptionText(uint32 liOption,string lsText);
 virtual void SetPosition(c3DVf lcPos);
 void Stop();
 ///This will return the list index of selected item
 uint32 Selected();
 /// This will set the selected item to be the item in list index liNew.
 void Selected(uint32 liNew);
 ///This lock the list so the Selected Item cannot be changed by mouse inputs.
 void Lock();
 ///This will unlock the list so the Selected Item can be changed by mouse inputs.
 void Unlock();
 ///This will set the Transparency for the object.
 void Transparency(uint8 liTrans);
 ///This will return the text of item in position liText.
 virtual string GetText(uint32 liText);

 void SetBackGroundTexture(cTexture *lpTexture);
 void SetFont(cFont *lpTexture);
 void Resize(float lfSize);
 void Resize();
 void SetWidth(float lfWidth);
 void SetWidth();


 string Title();
 void Title(string lsTitle);
 void OnSleep();
 void OnWake();

 void NoCancelButton();
 void CancelButton(cTexture *lpTexture=0,cShaderProgram *lpShader=_GET_SHADER_FILE("Image2DProgram"),cCamera *lpCamera=_CAMERA);

 void FocusPointer(void *lpData);

};

class cSelectionSliderWidget : public cSelectionWidget
{
protected:
 float mfTopLimit,mfBottomLimit;
 cButton *mpSlider;
 string *mpList;
 uint32 miSpaces;
 uint32 miStart;
public:
  cSelectionSliderWidget(uint8 liOptions,float lfSize,c3DVf lcPosition,cTexture *lpTexture=0,cFont *lpFont=0,cCamera *lpCamera=0,cShaderProgram *lpImageShader=0,cShaderProgram *lpTextShader=0,cRGBA UnselectedColor=cRGBA(0.3f,0.3f,0.3f,1.0f),cRGBA SelectedColor=cRGBA(0.9f,0.9f,0.9f,1.0f),cTexture *lpSliderText=0);
   void Run();
   void Stop();
   cButton *Slider();
   void UpdateShown(uint32 liStart);
   void UpdateSliderPos();

   void SetPosition(c3DVf lcPos);

   void CalculateSliderLimits();
   void Resize(float lfSize);
   void Resize();

    void Transparency(uint8 liTrans);

     void OnSleep();
    void OnWake();

   void SetOptionText(uint32 liOption,string lsText);

   void PositionSlider(uint32 liSlider);
   void ResizeSpaces(uint32 liSpaces);

   string GetText(uint32 liText);

    void FocusPointer(void *lpData);
};

class cFileListWidget : public cSelectionSliderWidget
{
    cDirectoryFileList *mpFiles;
    bool mbSelection;
    public:
    cFileListWidget(string lsPath,uint8 liOptions,float lfSize,c3DVf lcPosition,cTexture *lpTexture=0,cFont *lpFont=0,cCamera *lpCamera=0,cShaderProgram *lpImageShader=0,cShaderProgram *lpTextShader=0,cRGBA UnselectedColor=cRGBA(0.3f,0.3f,0.3f,1.0f),cTexture *lpSliderText=0);
    void Run();
    void Stop();
    bool Selection();
    string SelectedPath();

};

#endif
