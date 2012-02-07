#ifndef __WTCTEXTURETEXT_H__
#define __WTCTEXTURETEXT_H__

#if WT_FULL_VERSION_BAMBOO

using namespace std;
/// This class is a text renderable object
class cText : public cImage
{
protected:
 // A character array storing the string this text will use.
 std::string mpString;
public:
	/// Creates a text object and gives it a text string to use.
       cText(const char *lsText);
	   cText(const char *lsText,cCamera *lpCamera);
	/// Creates an empty text object with no text string.
       cText();
	   cText(cCamera *lpCamera);

	/// Will set the text string the cText object will render.
       void Text(char *lsText);
	/// Will accept a generic data type to render to the screen (will convert to a string).
       template <class T> void Value(T &t);

       template <class T> void Add(T &t);
	// Will render the text string from the cPainter render list to the screen.
       void RenderPainter();

       std::string &Text();

		///Will Add the Font lcFont to this object using the uniform variable labelled lsFontSlot.
		void AddFont(string lsFontSlot,cFont *lcFont);
		///Will Add the Font with reference lcFont to this object using the uniform variable labelled lsFontSlot.
		void AddFont(string lsFontSlot,string lcFont);
		///Will Add the Font lcFont to the first free default Font slot ("Font0" "Font1" "Font2"). This is slower than AddFont(string,cFont*). Also it allows for mistakes in the naming of samplers in the shader.
		void AddFont(cFont *lcFont);
		///Will Add the Font with Reference lcFont to the first free default Font slot ("Font0" "Font1" "Font2"). This is slower than AddFont(string,cFont*). Also it allows for mistakes in the naming of samplers in the shader.
		void AddFont(string lcFont);
};

//#include <sstream>

template <class T>
inline void cText::Value ( T &t)
{
    std::stringstream ss;
    ss << t;
    mpString=ss.str();
}


template <class T>
inline void cText::Add(T &t)
{
     std::stringstream ss;
     ss << t;
    mpString += ss.str();
}
#endif

#endif
