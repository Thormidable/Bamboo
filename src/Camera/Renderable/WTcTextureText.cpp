#include "../../WTDivWin.h"

void cText::RenderPainter(uint8 liLevel)
{

 (void) liLevel;
 if(mpFont)
 {
  SetShaderVariables();
  //mpFont->BindTexture();

 short liCount;
  for(liCount=0;liCount<miLength;++liCount)
  {
   float liRange;
    liRange=0.015625*(mpFont->Character(mpString[liCount])); //(or /64)
    printf("liRange : %f\n",liRange);
    if (liRange)
    {
      glBegin(GL_QUADS);
      glNormal3f(0.0f,0.0f,1.0f);
      glTexCoord2f(1,liRange);           glVertex3f(-mfWidth*(2*liCount+1),mfHeight,3.1f);
      glTexCoord2f(1,liRange+0.015625);  glVertex3f(-mfWidth*(2*liCount+1),-mfHeight,3.1f);
      glTexCoord2f(0,liRange+0.015625);  glVertex3f(-mfWidth*(2*liCount-1),-mfHeight,3.1f);
      glTexCoord2f(0,liRange);           glVertex3f(-mfWidth*(2*liCount-1),mfHeight,3.1f);

      glEnd();

    }



  }
 }
}

void cText::RenderToPainter()
{

 if(mpFont)
 {
  UpdateMatrix();
     mpPainterData->SetObject(this);

     mpPainterData->SetTexture(mpFont->TextureNumber());
     mpPainterData->SetShader(mpShader);
     mpPainterData->RenderAgain();
 }
}


void cText::Render()
{
 glEnable(GL_TEXTURE_2D);
 if (mpFont)
 {
  UpdateMatrix();
  mpFont->BindTexture();

  if(mpShader) mpShader->Use();
  else _USE_FIXED_FUNCTION();
    SetShaderVariables();

  short liCount;
  for(liCount=0;liCount<miLength;++liCount)
  {
   float liRange;

   glTranslatef(mfWidth,0,0);
   liRange=0.015625*(mpFont->Character(mpString[liCount])); //(or /64)
   if (liRange)
   {
    glBegin(GL_QUADS);
      glTexCoord2f(1,liRange);          glVertex2f(mfWidth,-mfHeight);
      glTexCoord2f(1,liRange+0.015625); glVertex2f(mfWidth,mfHeight);
      glTexCoord2f(0,liRange+0.015625); glVertex2f(-mfWidth,mfHeight);
      glTexCoord2f(0,liRange);          glVertex2f(-mfWidth,-mfHeight);
    glEnd();
   }
  }
 }

}




void cText::Text(char *lsText)
{
 strcpy(mpString,lsText);
 miLength=strlen(mpString);
}

cText::cText(const char *lsText)
{

 mpFont=0;
 strcpy(mpString,lsText);
 miLength=strlen(mpString);
 SetUp();
}

cText::cText()
{
  SetUp();

}

void cText::Font(vFont *lpFont)
{
  mpFont=lpFont;

}
