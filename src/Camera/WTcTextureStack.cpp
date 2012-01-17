#include "../WTBamboo.h"

cTextureSlot *cTextureStack::mpNoTexture=0;

void cTextureStack::CreateStatic()
{
 if(!mpNoTexture)
 {
	 mpNoTexture=new cTextureSlot[WT_TEXTURE_NUMBER_ALLOWED];
	 memset(mpNoTexture,0,sizeof(cTextureSlot)*WT_TEXTURE_NUMBER_ALLOWED);
 }
}

cTextureSlot::cTextureSlot(cTexture *lpTex,uint32 liUniform)
{
 mpTexture=lpTex;
 miUniform=liUniform;
}

cTextureStack::cTextureStack(bool lbNoTextures)
{
 (void) (lbNoTextures);
 CreateStatic();
 mpTextures=0;
 miTextures=0;
}

cTextureSlot::cTextureSlot()
{
 mpTexture=0;
 miUniform=0;
};

cTextureStack::cTextureStack()
{
	mpTextures=new cTextureSlot[WT_TEXTURE_NUMBER_ALLOWED];
	miTextures=0;
	CreateStatic();
}
cTextureStack::~cTextureStack()
{
 	delete []mpTextures;
	mpTextures=0;
}

cTextureSlot *cTextureStack::TextureList()
{
 if(mpTextures) return mpTextures;
 else return mpNoTexture;
};
uint8 cTextureStack::Textures()
{
 return miTextures;
}

void cTextureStack::AddTexture(uint32 liUniform,cTexture *lpTexture)
{
 if(mpTextures)
 {
  if(miTextures)
  {
  	uint8 liCount;
  	for(liCount=0;liCount<miTextures;++liCount)
	{
		if(mpTextures[liCount].miUniform==liUniform)
		{
			mpTextures[liCount].mpTexture=lpTexture;
			return;
		}
	}
 	if(miTextures<WT_TEXTURE_NUMBER_ALLOWED)
 	{
		mpTextures[miTextures].miUniform=liUniform;
		mpTextures[miTextures++].mpTexture=lpTexture;
 	}
 	return;
  }
		mpTextures[miTextures].miUniform=liUniform;
		mpTextures[miTextures++].mpTexture=lpTexture;
 }
};

cTextureSlot &cTextureStack::TextureItem(uint8 liPos)
{
	return TextureList()[liPos];
}

void cTextureSlot::FirstTextureState(uint8 liTexSlot)
{
    if(mpTexture)
    {
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0+liTexSlot);
		glClientActiveTexture(GL_TEXTURE0+liTexSlot);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		mpTexture->BindTexture();
		glUniform1i(miUniform,liTexSlot);
    }
}

void cTextureSlot::TextureState(cTextureSlot *lpPrevious,uint8 liTexSlot)
{
 if(mpTexture != lpPrevious->mpTexture)
 {
  if(mpTexture)
  {
	  if(!lpPrevious->mpTexture)
	  {
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0+liTexSlot);
		glClientActiveTexture(GL_TEXTURE0+liTexSlot);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		mpTexture->BindTexture();
		glUniform1i(miUniform,liTexSlot);
	  }
	  else
	  {
		glActiveTexture(GL_TEXTURE0+liTexSlot);
		mpTexture->BindTexture();
		glUniform1i(miUniform,liTexSlot);
	  }
  }
  else
  {
		  glClientActiveTexture(GL_TEXTURE0);
		  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		  glDisable(GL_TEXTURE_2D);
  }
 }
}

int8 cTextureStack::ReturnFreeSlot()
{

 if(mpTextures)
 {
  uint8 liCount;
 for(liCount=0;liCount<WT_TEXTURE_NUMBER_ALLOWED;++liCount)
 {
	if(!mpTextures[liCount].mpTexture) return liCount;
  }
 }

 return -1;
}

void cTextureStack::RemoveTextureBySlot(uint8 liTexSlot)
{
 if(miTextures)
 {
  	mpTextures[liTexSlot].miUniform=0;
  	mpTextures[liTexSlot].mpTexture=0;
 	if(liTexSlot+1<miTextures)
 	{
  		int8 liCount;
  		for(liCount=miTextures;liCount;--liCount)
  		{
  			if(mpTextures[liTexSlot].mpTexture) miTextures=liCount-1;
  		}
 	}
 	else --miTextures;
 }
}

void cTextureStack::RemoveTextureByUniform(uint32 liUniform)
{
 uint8 liPos;
 for(liPos=0;liPos<miTextures;++liPos)
 {
	if(mpTextures[liPos].mpTexture)
	{
		if(mpTextures[liPos].miUniform==liUniform)
		{
			mpTextures[liPos].miUniform=0;
			mpTextures[liPos].mpTexture=0;
			break;
		}
	}
 }

	if(liPos+1<miTextures)
 	{
  		int8 liCount;
  		for(liCount=miTextures;liCount;--liCount)
  		{
  			if(mpTextures[liPos].mpTexture) miTextures=liCount-1;
  		}
 	}
 	else --miTextures;

}


void cTextureStack::ClearTextureStack()
{
 if(miTextures)
 {
 	uint8 liCount;
 	for(liCount=0;liCount<WT_TEXTURE_NUMBER_ALLOWED;++liCount)
 	{
 		mpTextures[liCount].mpTexture=0;
		mpTextures[liCount].miUniform=0;
 	}
 	miTextures=0;
 }
}
