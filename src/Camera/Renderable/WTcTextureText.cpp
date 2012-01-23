#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

void cText::AddFont(string lsFontSlot,string lcFont)
{
 AddFont(lsFontSlot,_GET_FONT_FILE(lcFont.c_str()));
}

void cText::AddFont(string lsFontSlot,cFont *lpFont)
{
 uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lsFontSlot);
 if(liPos)
 {
		AddTexture(liPos-1,lpFont);
 	//	miCharSize=lpFont->Height();
 }
}

void cText::AddFont(cFont *lpFont)
{

 int8 liSlot=ReturnFreeSlot();
 if(liSlot)
 {
 		string lsTextureSlot="Font";
 		std::stringstream out;
 		out << liSlot;
		lsTextureSlot.append(out.str());
		uint32 liPos=mpShader->ShaderVariableSet()->GetUniformPosition(lsTextureSlot);
	 	if(liPos)
		{
			AddTexture(liPos-1,lpFont);
			//miCharSize=lpFont->Height();
		}
 }
}

void cText::AddFont(string lcFont)
{
 AddFont(_GET_FONT_FILE(lcFont.c_str()));
}


void cText::RenderPainter()
{


 if(Textures())
 {
  SetShaderVariables();

 float lfHeight=mfHeight*0.5f;
 uint32 liCount;
  for(liCount=0;liCount<mpString.length();++liCount)
  {
	float liRange;
     if(mpString[liCount]!=32)
     {
		 liRange=IMF_FONT_SCALE*(cFont::Character(mpString[liCount])); //(or /64)
          glBegin(GL_QUADS);
          glNormal3f(0.0f,0.0f,1.0f);
          glTexCoord2f(1,liRange+IMF_FONT_SCALE);   glVertex3f(-mfWidth*(liCount+0.5f),lfHeight,3.1f);
          glTexCoord2f(1,liRange);            glVertex3f(-mfWidth*(liCount+0.5f),-lfHeight,3.1f);
          glTexCoord2f(0,liRange);            glVertex3f(-mfWidth*(liCount-0.5f),-lfHeight,3.1f);
          glTexCoord2f(0,liRange+IMF_FONT_SCALE);   glVertex3f(-mfWidth*(liCount-0.5f),lfHeight,3.1f);

          glEnd();

    }

  }
 }
}

std::string &cText::Text()
{
 return mpString;
}



void cText::Text(char *lsText)
{
 mpString=lsText;
}

cText::cText(const char *lsText)
{

 mpString=lsText;
}

cText::cText()
{


}



#endif
