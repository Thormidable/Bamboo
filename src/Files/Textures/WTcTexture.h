#ifndef __WTCTEXTURE_H__
#define __WTCTEXTURE_H__

class cTextureArray
{
 public:
     cTextureArray();
     uint32 miWidth,miHeight;
     uint8 miDepth;
     uint8 *mpData;
     int8 *mpRef;
     ~cTextureArray();
};

class cTexture : public cFile
{
public:
       uint8 *Data();
       cTexture();
       cTexture(cTexture *lpOther);
       cTexture(cTexture *lpOther,string NewFileName);
       cTexture(cTextureArray *lpArray);
        ~cTexture();
       uint32 Width();
       uint32 Height();
       uint8 Depth();
       uint32 TextureNumber();

        void UpdateTexture();
        void BindTexture();


       cTexture *Duplicate();
       cTexture *Duplicate(string NewFileName);
       void Write(cRGBA Color,c2DVf lvUV);
       void Write(cRGBA Color,c2DVi lvXY);
       void Write(cRGB Color,c2DVf lvUV);
       void Write(cRGB Color,c2DVi lvXY);
       void Write(cTexture *lpTexture,c2DVf lvUV);
       void Write(cTexture *lpTexture,c2DVi lvXY);

       void WriteSubImage(c2DVi Offset,c2DVi Size);

       inline uint8 *GetPixel(c2DVi lvXY);
       inline uint8 *GetPixel(c2DVf lvXY);



//       virtual void Load()=0;

protected:
 uint32 miWidth,miHeight;
 uint8 miDepth,miPixelSize;
 GLuint miTexture;
 uint8 *mpData;

};

#endif
