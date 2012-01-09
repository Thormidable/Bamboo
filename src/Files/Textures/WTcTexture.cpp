#include "../../WTBamboo.h"

using namespace std;

cTextureArray::cTextureArray()
{
 miWidth=0;miHeight=0;miDepth=0;
 mpData=0;
 mpRef=0;
}

cTextureArray::~cTextureArray()
{
 if(mpRef) delete []mpRef;
}

cTexture::cTexture(cTextureArray *lpTexture)
{
 strcpy(mpFileName,lpTexture->mpRef);

 miWidth=lpTexture->miWidth;
 miHeight=lpTexture->miHeight;
 miDepth=lpTexture->miDepth;

 mpData=lpTexture->mpData;

 glGenTextures(1, &miTexture);
 UpdateTexture();
}

void cTexture::UpdateTexture()
{
BindTexture();


glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

if(WT_ALLOW_DYNAMIC_TEXTURES) glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
else {glEnable(GL_TEXTURE_2D); glGenerateMipmapEXT(GL_TEXTURE_2D);}



if(miDepth==24) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width(),Height(), 0, GL_BGR, GL_UNSIGNED_BYTE,mpData);
if(miDepth==32) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width(),Height(), 0, GL_BGRA, GL_UNSIGNED_BYTE,mpData);
}

void cTexture::BindTexture()
{
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
glBindTexture(GL_TEXTURE_2D,miTexture);
}


uint8 *cTexture::Data()
{return mpData;}
