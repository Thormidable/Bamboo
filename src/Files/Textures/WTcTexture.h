#ifndef __WTCTEXTURE_H__
#define __WTCTEXTURE_H__

class cTextureArray
{
 public:
     cTextureArray();
     uint32 miWidth,miHeight,miDepth;
     uint8 *mpData;
     int8 *mpRef;
     ~cTextureArray();
};

class cTexture : public cFile
{
public:
       uint8 *Data();
       cTexture(){};
       cTexture(cTextureArray *lpArray);
        ~cTexture(){if(mpData){delete []mpData;mpData=0;}}
       uint32 Width(){return miWidth;}
       uint32 Height(){return miHeight;}
       uint32 Depth(){return miDepth;}

        void UpdateTexture();
        void BindTexture();

       uint32 TextureNumber(){return miTexture;}

//       virtual void Load()=0;

protected:
 int miWidth,miHeight,miDepth;
 unsigned int miTexture;
 uint8 *mpData;

};

#endif
