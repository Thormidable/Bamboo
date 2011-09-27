#ifndef __WTCTEXTURETEXT_H__
#define __WTCTEXTURETEXT_H__

using namespace std;
/// This class is a text renderable object
class cText : public cRenderObject
{
 // The current font texture that this text will use.
 vFont *mpFont;
 // A character array storing the string this text will use.
 char mpString[128];
 // A string array holding the string this text will use. Will be Future Upgrade.
 string mString;
 // Length of the current string.
 int miLength;
 // Size of each character.
 float miSize;

public:
	/// Creates a text object and gives it a text string to use.
       cText(const char *lsText);
	/// Creates an empty text object with no text string.
       cText();

	// Will Initialise the cText object.
       void Setup();

	/// Will set the font texture the text will use.
       void Font(vFont *lpFont);

	/// Will set the size of the characters.
       void Size(float liSize);
	/// Will set the text string the cText object will render.
       void Text(char *lsText);
	/// Will accept a generic data type to render to the screen (will convert to a string).
       template <class T> void Value(const T &t);
       // Will return the ID of the font currently bound to this text.
       unsigned int TextureNumber(){return mpFont->TextureNumber();}
	// Will render the text string from the cPainter render list to the screen.
       void RenderPainter(uint8 liLevel);
	// Will render the text string to the cPainter render list.
       void RenderToPainter();
	// Will render the text string to the screen.
       void Render();

};

//#include <sstream>

template <class T>
inline void cText::Value (const T &t)
{
std::stringstream ss;
ss << t;
mString=ss.str();
strcpy(mpString,mString.c_str());
miLength=strlen(mpString);
//return ss.str();
}

#endif
