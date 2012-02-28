#ifndef __WTCFONT_H__
#define __WTCFONT_H__

/** \brief This class will store the data for a Font ready to be used for rendering cText.
 * This should come from an IMF file and be composed of an image of 93 character images stacked vertically.
 * This is a file class and should be handled entirely by the engine.
 */
class cFont : public cTexture
{
 public:

    ~cFont();
    //
    cFont(cTextureArray *lpData);
    uint8 Character(uint8 lcChar);
    uint32 Height(){return miWidth;}
    void UpdateTexture();
    void BindTexture();

};


#endif
