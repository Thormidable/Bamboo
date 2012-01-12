#ifndef __WTCTEXTURETEXT_H__
#define __WTCTEXTURETEXT_H__

#if WT_FULL_VERSION_BAMBOO

using namespace std;
/// This class is a text renderable object
class cText : public cImage
{
    protected:
 // The current font texture that this text will use.
 cFont *mpFont;
 // A character array storing the string this text will use.
 std::string mpString;

public:
	/// Creates a text object and gives it a text string to use.
       cText(const char *lsText);
	/// Creates an empty text object with no text string.
       cText();

	/// Will set the font texture the text will use.
       void Font(cFont *lpFont);
	/// Will set the text string the cText object will render.
       void Text(char *lsText);
	/// Will accept a generic data type to render to the screen (will convert to a string).
       template <class T> void Value(const T &t);

       template <class T> void Add(const T &t);
       // Will return the ID of the font currently bound to this text.
       unsigned int TextureNumber(){return mpFont->TextureNumber();}
	// Will render the text string from the cPainter render list to the screen.
       void RenderPainter(uint8 liLevel);
	// Will render the text string to the cPainter render list.
       void RenderToPainter();

       std::string &Text();
};

//#include <sstream>

template <class T>
inline void cText::Value (const T &t)
{
    std::stringstream ss;
    ss << t;
    mpString=ss.str();
}


template <class T>
inline void cText::Add(const T &t)
{
     std::stringstream ss;
     ss << t;
    mpString += ss.str();
}
#endif

#endif
