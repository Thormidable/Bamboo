#ifndef __WTCTEXTURESTACK_H__
#define __WTCTEXTURESTACK_H__

class cVariableStore;
class cUniformFont;
class cUniformTexture;
class cShaderVariables;
class cShaderProgram;

class cTextureSlot
{
public:
	cTextureSlot(cTexture *lpTex,uint32 liUniform);
	cTextureSlot();
	cTexture *mpTexture;
	uint32 miUniform;
	void FirstTextureState(uint8 liTexSlot);
	void TextureState(cTextureSlot *lpPrevious,uint8 liTexSlot);
};

class cTextureStack
{
	cTextureSlot *mpTextures;
	static cTextureSlot *mpNoTexture;
protected:
	uint8 miTextures;
public:
	///Set bool to 1 if this is an object not requiring textures
	cTextureStack(bool lbNoTextures);
	cTextureStack();
	~cTextureStack();
	cTextureSlot *TextureList();
	cTextureSlot &TextureItem(uint8 liPos);
	void AddTexture(uint32 liUniform,cTexture *lpTexture);
	int8 ReturnFreeSlot();
	///This will return the number of Textures linked to this object.
   uint8 Textures();
   void CreateStatic();
   void RemoveTextureByUniform(uint32 liTexSlot);
   void RemoveTextureBySlot(uint8 liTexSlot);

   void ClearTextureStack();
};



#endif
