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

/**
 * \brief This class stores the data for rendering a 2D texture.
 * This stores and processes the data for a 2D texture. This can be applied to objects to add maps to their surface.
 * This can include Normal, specular, lighting or any other type of map. The data in the class can be modified and does update, but for textures which will receive a lot of updates, cDynamicTexture are faster.
 * These inherit cFile and are loaded from IMFs.
 *
 */
class cTexture : public cFile
{
public:

	   ///Constructor for generating a cTexture with no Data.
       cTexture();
	   ///Constructor for copying the cTexture object lpOther. Will be given the File Reference NewFileName
       cTexture(cTexture *lpOther,string NewFileName="GeneratedTexture");
	   ///Constructor for creating a cTexture object from the cTextureArray Loading class.
       cTexture(cTextureArray *lpArray);
        ~cTexture();
		///Returns the cTexture Width.
       uint32 Width();
	   ///Returns the cTexture Height.
       uint32 Height();
	   ///Returns the cTexture Color Depth.
       uint8 Depth();
	   ///Returns the Size in bytes of a Pixel.
       uint8 PixelSize();
	   ///Returns a pointer to the Data for the cTexture Object.
       uint8 *Data();
       uint32 TextureNumber();

        void BufferTexture();
        virtual void StreamImage(){};
        inline void BindTexture(){glBindTexture(GL_TEXTURE_2D,miTexture);}


		///Will return a pointer to a Duplicate of this texture. With the FileName Reference "GeneratedTexture"
       cTexture *Duplicate();
	   ///Will return a pointer to a Duplicate of this texture. With the FileName Reference NewFileName.
       cTexture *Duplicate(string NewFileName);


	   ///Will return a pointer to the data for the Pixel at lvXY.
       uint8 *GetPixel(c2DVi lvXY);
	   ///Will return a pointer to the data for the Pixel at lvXY.
       uint8 *GetPixel(c2DVf lvXY);

	   	///This will write the cRGBA Color to the pixel at lvUV. See cModel for Finding UV co-ordinates from global Co-ordinates.
       void Write(cRGBA Color,c2DVf lvUV);
	   ///This will write the cRGBA Color to the pixel at lvXY. See cModel for Finding UV co-ordinates from global Co-ordinates.
       virtual void Write(cRGBA Color,c2DVi lvXY);
	   ///This will write the cRGB Color to the pixel at lvUV. See cModel for Finding UV co-ordinates from global Co-ordinates.
       void Write(cRGB Color,c2DVf lvUV);
	   ///This will write the cRGB Color to the pixel at lvXY. See cModel for Finding UV co-ordinates from global Co-ordinates.
       virtual void Write(cRGB Color,c2DVi lvXY);
	   ///This will write the cTexture lpTexture to this texture at the point lvUV. See cModel for Finding UV co-ordinates from global Co-ordinates.
       void Write(cTexture *lpTexture,c2DVf lvUV);
	   ///This will write the cTexture lpTexture to this texture at the point lvXY. See cModel for Finding UV co-ordinates from global Co-ordinates.
       virtual void Write(cTexture *lpTexture,c2DVi lvXY);

	   	///This will blend the cRGBA Color over the pixel at lvUV. See cModel for Finding UV co-ordinates from global Co-ordinates.
       void Blend(cRGBA Color,c2DVf lvUV);
	   ///This will blend the cRGBA Color over the pixel at lvXY. See cModel for Finding UV co-ordinates from global Co-ordinates.
       virtual void Blend(cRGBA Color,c2DVi lvXY);
	   ///This will Blend the cTexture lpTexture over this texture at the point lvUV. See cModel for Finding UV co-ordinates from global Co-ordinates.
       void Blend(cTexture *lpTexture,c2DVf lvUV);
	   ///This will Blend the cTexture lpTexture over this texture at the point lvXY. See cModel for Finding UV co-ordinates from global Co-ordinates.
       virtual void Blend(cTexture *lpTexture,c2DVi lvXY);

       void UpdateSubImage(c2DVi Offset,c2DVi Size);

       void BlendPixels(uint8 *lpBase,uint8 *lpOverlay);

	   ///This will set the entire cTexture to the cRGBA lcColor.
       virtual void ColorTexture(cRGBA lcColor);
	   ///This will set the entire cTexture to the cRGB lcColor.
       virtual void ColorTexture(cRGB lcColor);


protected:
 uint32 miWidth,miHeight;
 uint8 miDepth,miPixelSize;
 GLuint miTexture;
 uint8 *mpData;

};

/**
 * \brief Class derived from cTexture. For creating an blank Texture with Data space for generating Textures at run time.
 *
 */
class cEmptyTexture : public cTexture
{

public:
	///Constructor for Creating an empty texture of specified Size and Color Depth. File Reference can be specified in lsFileName.
    cEmptyTexture(c2DVi liSize,uint8 liDepth=32,string lsFileName="GeneratedEmptyTexture");
};


/**
 * \brief Specialised class derived from cTexture for quick broad run time updates.
 * Class for quickly updating large portions of the image. Otherwise acts exactly like cTexture, This requires more graphics card memory, so should be saved for textures which require regular updating.
 * cDynamicTexture objects can be created by specifying Dynamic Textures in the IMF Handler.
 * See cTexture for details of the user available functions.
 */
class cDynamicTexture : public cTexture, public cFrameUpdateType
{
    bool mbFrame;
    bool mbChanged;
    bool mbNeedsUpdate;
    GLuint mpPBOIds[2];
public:
      cDynamicTexture();
       cDynamicTexture(cTexture *lpOther,string NewFileName="GeneratedDynamicTexture");
       cDynamicTexture(cTextureArray *lpArray);
      ~cDynamicTexture();

       void Write(cTexture *lpTexture,c2DVi lvXY);
       void Write(cRGBA Color,c2DVi lvUV);
       void Write(cRGB Color,c2DVi lvUV);

       void Blend(cRGBA Color,c2DVi lvXY);
       void Blend(cTexture *lpTexture,c2DVi lvXY);

       void FrameUpdate();

       void ColorTexture(cRGBA lcColor);
       void ColorTexture(cRGB lcColor);

       bool UpdateTexture();
       bool UpdatePBO();
       void StepFrame();



};




#endif
