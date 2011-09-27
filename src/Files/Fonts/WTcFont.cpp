#include "../../WTDivWin.h"

using namespace std;


cFont::cFont(cTextureArray *lpTexture)
{
 strcpy(mpFileName,lpTexture->mpRef);

 miWidth=lpTexture->miWidth;
 miDepth=lpTexture->miDepth;

 mpData=lpTexture->mpData;

 glGenTextures(1, &miTexture);
 UpdateTexture();

}

cFont::~cFont()
{
 if(mpData) {delete []mpData; mpData=0;}
}

void cFont::UpdateTexture()
{
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
glBindTexture(GL_TEXTURE_2D,miTexture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

if(miDepth==24) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, miWidth,miWidth*64, 0, GL_BGR, GL_UNSIGNED_BYTE,mpData);
if(miDepth==32) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, miWidth,miWidth*64, 0, GL_RGBA, GL_UNSIGNED_BYTE,mpData);
}


void cFont::BindTexture()
{
//  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
glBindTexture(GL_TEXTURE_2D,miTexture);
}

uint8 cFont::Character(uint8 lcChar)
{
if(lcChar>96) return lcChar-71; //a-z
if(lcChar>64) return lcChar-65; //A-Z
if(lcChar>47) return lcChar+4; //0-9
if(lcChar==32)return 0;
return 0xFF;
}

