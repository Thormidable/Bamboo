#include "../../WTDivWin.h"

void cText::RenderPainter(uint8 liLevel)
{

 (void) liLevel;
 if(mpFont)
 {
  SetShaderVariables();
  //mpFont->BindTexture();

 short liCount;
  for(liCount=0;liCount<mpString.length();++liCount)
  {
   float liRange;
     if(mpString[liCount]!=32)
     {

        liRange=IMF_FONT_SCALE*(mpFont->Character(mpString[liCount])); //(or /64)
          glBegin(GL_QUADS);
          glNormal3f(0.0f,0.0f,1.0f);
          glTexCoord2f(1,liRange+IMF_FONT_SCALE);   glVertex3f(-mfWidth*(2*liCount+1),mfHeight,3.1f);
          glTexCoord2f(1,liRange);            glVertex3f(-mfWidth*(2*liCount+1),-mfHeight,3.1f);
          glTexCoord2f(0,liRange);            glVertex3f(-mfWidth*(2*liCount-1),-mfHeight,3.1f);
          glTexCoord2f(0,liRange+IMF_FONT_SCALE);   glVertex3f(-mfWidth*(2*liCount-1),mfHeight,3.1f);

          glEnd();

    }



  }
 }
}

std::string &cText::Text()
{
 return mpString;
}

void cText::RenderToPainter()
{

 if(mpFont)
 {
  UpdateMatrix();
     mpPainterData->SetObject(this);
     mpPainterData->SetTexture(mpFont->TextureNumber());
     SetOtherRenderVariables();
     mpPainterData->RenderAgain();
 }
}






void cText::Text(char *lsText)
{
 mpString=lsText;
}

cText::cText(const char *lsText)
{

 mpFont=0;
 mpString=lsText;
}

cText::cText()
{


}

void cText::Font(cFont *lpFont)
{
  mpFont=lpFont;

}

