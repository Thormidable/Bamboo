#ifndef __WTCTEXTURETEXT_H__
#define __WTCTEXTURETEXT_H__

#if WT_FULL_VERSION_BAMBOO

#define TEXT_LEFT_JUSTIFY 0x0
#define TEXT_CENTRE_JUSTIFY 0x1

using namespace std;
/**
 * \brief This class is for rendering Text strings using a cFont object.
 * Renders 2D strings of Text using the specified cFont. Color can be optionally set based on the shader used. Uses a std:string to store the text string.
 * cText is a templated type of this class with a single line.
 */
template<uint8 liLines=1> class cMultiLineText : public cImage
{
protected:
 // A character array storing the string this text will use.
 std::string *mpString;
 uint8 miLines;
 uint8 mbLeftJustify;
public:

	/// Creates an empty text object with no text string.
cMultiLineText(cCamera *lpCamera) : cImage(lpCamera)
{
    mbLeftJustify=TEXT_LEFT_JUSTIFY;
    miLines=liLines;
    mpString=new string[miLines];
}

cMultiLineText()
{
    mbLeftJustify=TEXT_LEFT_JUSTIFY;
    miLines=liLines;
    mpString=new string[miLines];
};

	   /// Will accept a generic data type to render to the screen (will convert to a string).
       template <class T> void Value(T t,uint8 liLine=0)
        {
            std::stringstream ss;
            ss << t;
            mpString[liLine]=ss.str();
        };
	   ///Will add a generic data type to render to the screen.
       template <class T> void Add(T t,uint8 liLine=0)
       {
         std::stringstream ss;
         ss << t;
        mpString[liLine] += ss.str();
        };

       	/// Will accept a generic data type to render to the screen (will convert to a string). Will use the specified amount of precision
       template <class T> void Value(T t,uint8 liPrecision,uint8 liLine)
       {
            std::stringstream ss;
            ss << setprecision(liPrecision) << fixed << t;
            mpString[liLine]=ss.str();
        };
	   ///Will add a generic data type to render to the screen. Will use the specified amount of precision
       template <class T> void Add(T t,uint8 liPrecision,uint8 liLine)
        {
             std::stringstream ss;
             ss.precision(liPrecision);
             ss << setprecision(liPrecision) << fixed << t;
             mpString[liLine] += ss.str();
        };

///Will Add the Font with reference lcFont to this object using the uniform variable labelled lsFontSlot.
void AddFont(string lsFontSlot,string lcFont)
{
 AddFont(lsFontSlot,_GET_FONT_FILE(lcFont.c_str()));
}
///Will Add the Font lcFont to this object using the uniform variable labelled lsFontSlot.
void AddFont(string lsFontSlot,cFont *lpFont)
{
 uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lsFontSlot);
 if(liPos)
 {
		AddTexture(liPos-1,lpFont);
 	//	miCharSize=lpFont->Height();
 }
}
///Will Add the Font lcFont to the first free default Font slot ("Font0" "Font1" "Font2"). This is slower than AddFont(string,cFont*). Also it allows for mistakes in the naming of samplers in the shader.
void AddFont(cFont *lpFont)
{

 int32 liSlot=ReturnFreeSlot();
 if(liSlot>=0)
 {
 		string lsTextureSlot="Font";
 		std::stringstream out;
 		out << liSlot;
		lsTextureSlot.append(out.str());
		uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lsTextureSlot);
	 	if(liPos)
		{
			AddTexture(liPos-1,lpFont);
			//miCharSize=lpFont->Height();
		}
 }
}
///Will Add the Font with Reference lcFont to the first free default Font slot ("Font0" "Font1" "Font2"). This is slower than AddFont(string,cFont*). Also it allows for mistakes in the naming of samplers in the shader.
void AddFont(string lcFont)
{
 AddFont(_GET_FONT_FILE(lcFont.c_str()));
}
///Will return the length of the string.
uint16 Length(uint8 liLine=0)
{
	return mpString[liLine].length();
}

///Will set the length of the string.
void SetLength(uint16 liLength,uint8 liLine=0)
{
	mpString[liLine].resize(liLength);
};

///Will set the text to be justified to the Centre, Centre
void JustifyTextCentre()
{
    mbLeftJustify=TEXT_CENTRE_JUSTIFY;
};
///Will set the text to be justified to the top left
void JustifyTextLeft()
{
    mbLeftJustify=TEXT_LEFT_JUSTIFY;
};

void RenderPainter()
{

cFont *lpFont=static_cast<cFont*>(mpTextures[0].mpTexture);
 if(Textures() && lpFont)
 {
  SetShaderVariables();

 float lfHeight=mfHeight*0.5f;
 uint32 liCount;
 float lfXRange,lfYRange;
 float lfStart;
 float lfYPos;
 switch(mbLeftJustify)
 {
     case TEXT_CENTRE_JUSTIFY:
     {
         lfYPos=-(miLines-1.0f)*0.55f*mfHeight;
     }break;
     default:
     {
         lfYPos=0.0f;
     }break;
 };

 lfXRange=lpFont->CharacterX();
 lfYRange=lpFont->CharacterY();

 glBegin(GL_QUADS);
 glNormal3f(0.0f,0.0f,1.0f);

for(uint8 liLine=0;liLine<miLines;++liLine)
{
 switch(mbLeftJustify)
 {
     case TEXT_CENTRE_JUSTIFY:
     {
         lfStart=mpString[liLine].length()*0.5f*mfHeight;
     }break;
     default :
     {
         lfStart=0.0f;
     }break;
 }

  for(liCount=0;liCount<mpString[liLine].length();++liCount)
  {
     if(mpString[liLine].operator[](liCount)!=32)
     {
        uint8 liCharacter=cFont::Character(mpString[liLine].operator[](liCount));
        float lfX=lpFont->CharacterX(liCharacter);
        float lfY=lpFont->CharacterY(liCharacter);
          glMultiTexCoord2f(GL_TEXTURE0,lfX,lfY+lfYRange);   		glVertex3f(lfStart,lfYPos+lfHeight,1.0f);
          glMultiTexCoord2f(GL_TEXTURE0,lfX,lfY);            		glVertex3f(lfStart,lfYPos-lfHeight,1.0f);
          glMultiTexCoord2f(GL_TEXTURE0,lfX+lfXRange,lfY);            	glVertex3f(lfStart-mfHeight,lfYPos-lfHeight,1.0f);
          glMultiTexCoord2f(GL_TEXTURE0,lfX+lfXRange,lfY+lfYRange);   	glVertex3f(lfStart-mfHeight,lfYPos+lfHeight,1.0f);
    }

    lfStart-=mfHeight;

  }
  lfYPos+=mfHeight*1.1f;
 }
 glEnd();
}
};


/// Will set the text string the cText object will render.
void Text(string lsString,uint8 liLine=0)
{
    mpString[liLine]=lsString;
}
///Will return the reference of the std::string object.
std::string &Text(uint8 liLine=0)
{
 return mpString[liLine];
}

void Stop()
{
 cImage::Stop();
 delete []mpString;
 mpString=0;
};

};


template<uint8 liMessageLines=1> class cTextMessage : public cMultiLineText<liMessageLines>
{
    uint32 miFrames;
    public:

    cTextMessage(){};
    cTextMessage(cCamera *lpCamera) : cMultiLineText<liMessageLines>(lpCamera){};

    void Time(float lfTime){miFrames=lfTime*_FPS;};

    void Frames(uint32 liFrames){miFrames=liFrames;};
    uint32 Frames(){return miFrames;};
    void RenderPainter()
    {
        cMultiLineText<liMessageLines>::RenderPainter();
        --miFrames;
        if(!miFrames) cRenderObject::Signal(_S_KILL);
    };


};

#endif

#endif
