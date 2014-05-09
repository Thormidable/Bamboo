#include "stdafx.h"
#include "../../WTBamboo.h"


void cTextBoxWidget::FocusPointer(void *lpData)
{
 mpBackground->FocusPointer(lpData);
};

cTextBoxWidget::cTextBoxWidget(c3DVf lcPosition,c2DVf lvSize,cTexture *mpTexture,cFont *lpFont,cRGBA TextColor,cCamera *lpCamera,cShaderProgram *lpImageShader,cShaderProgram *lpTextShader)
{
	mfSize=lvSize[1];

	if(lpCamera) mpBackground=_CREATE(cButton(lpCamera));
	else mpBackground=_CREATE(cButton);

	if(lpImageShader) mpBackground->Shader(lpImageShader);
	else mpBackground->Shader("Image2DProgram");

	mpBackground->AddTexture(mpTexture);
	mpBackground->Height(mfSize+4);
	mpBackground->Width(lvSize[0]);
	mpBackground->Transparency(1);
	mbSelected=false;
	mbLastMouse=false;


if(lpCamera) mpTextField=_CREATE(cText(lpCamera));
	else mpTextField=_CREATE(cText);

	if(lpImageShader) mpTextField->Shader(lpTextShader);
	else mpTextField->Shader("TextProgram");

	if(lpFont) mpTextField->AddFont(lpFont);
	else mpTextField->AddFont("Pirulen");
	mpTextField->SetUniform("TextColor",TextColor.Color());
	mpTextField->Transparency(2);
	mpTextField->Text("Insert Text");

	mbLocked=false;

	SetPosition(lcPosition);
};

void cTextBoxWidget::Run()
{
	if(!mbLocked)
	{
		if(mpBackground->Clicked())
		{
			printf("TextBox Widget Selected\n");
			mbSelected=true; mbLastMouse=false; _KEYBOARD->KeyPressTracking(true);
		}
		else
		{
			if(_MOUSE->Left()) mbLastMouse=true;
			else
			{
				if(mbLastMouse)
				{
					printf("TextBox Widget Unselected\n");
					mbSelected=false; _KEYBOARD->KeyPressTracking(false);

				}
				mbLastMouse=false;
			}
		}

		if(mbSelected)
		{
			for(uint8 liCount=0;liCount<_PRESSED_KEYS();++liCount)
			{

				char liKey=_PRESSED_KEY_CHARACTER(liCount);
				printf("Key Pressed : %c\n",liKey);
				switch(liKey)
				{
					case 8:
					{
						if(mpTextField->Length()>1) mpTextField->Text(mpTextField->Text().erase(mpTextField->Length()-1));
						else mpTextField->Text("");
						break;
					}
					case 0: break;
					default: mpTextField->Add(liKey);
				};
			}
		}

	}

};

 void cTextBoxWidget::SetPosition(c3DVf lcPos)
 {
	if(mpBackground)
	{
		mpBackground->Position(lcPos[0],lcPos[1]);
		mpTextField->Position(lcPos[0]-mpBackground->Width()*0.5+mfSize,lcPos[1]);
	}
	else
	{
		mpTextField->Position(lcPos[0],lcPos[1]);
	}
	mpTextField->Size(mfSize);
 };
 void cTextBoxWidget::Stop()
 {
	_KILL(mpTextField);
	if(mpBackground) _KILL(mpBackground);
 }

 void cTextBoxWidget::TextColor(cRGBA lcCol)
 {
	mpTextField->SetUniform("TextColor",lcCol.Color());
 };

 void cTextBoxWidget::Lock(){mbLocked=true;};
 void cTextBoxWidget::Unlock(){mbLocked=false;};
 void cTextBoxWidget::Text(string lsString){if(!mbLocked) mpTextField->Text(lsString);};
 string &cTextBoxWidget::Text(){return mpTextField->Text();}



 void cTextBoxWidget::OnWake()
 {
     _WAKE(mpTextField);
    _WAKE(mpBackground);
 }

 void cTextBoxWidget::OnSleep()
 {
     _SLEEP(mpTextField);
     _SLEEP(mpBackground);
 }
