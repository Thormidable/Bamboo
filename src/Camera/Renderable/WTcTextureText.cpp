#include "../../WTDivWin.h"


void cText::RenderPainter(uint8 liLevel)
{
 (void) liLevel;
 if(mpFont)
 {

	 SetShaderVariables();
  mpFont->BindTexture();

  v2DPolygon::SizeArrays(miSize);
    glVertexPointer(3,GL_FLOAT,0,v2DPolygon::mpVertex);
    glTexCoordPointer(2,GL_FLOAT,0,v2DPolygon::mpTextCoords);
    glNormalPointer(GL_FLOAT,0,v2DPolygon::mpNormals);

 short liCount;
  for(liCount=0;liCount<miLength;++liCount)
  {
   float liRange;

   glTranslatef(miSize,0,0);
   liRange=0.015625*(mpFont->Character(mpString[liCount])); //(or /64)

   if (liRange)
   {
    v2DPolygon::SetTextCoords(liRange);
     glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,v2DPolygon::mpFaces);
    v2DPolygon::ResetTextCoords();
   }
  }
 }
}

void cText::RenderToPainter()
{
 if(mpFont)
 {
  float Temp[16];
  UpdateMatrix();
  glGetFloatv(GL_MODELVIEW_MATRIX,Temp);


 mpPainterData->SetObject(this);
 //mpPainterData->SetMatrix(Temp);
 mpPainterData->SetTexture(TextureNumber());
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


  short liCount;
  for(liCount=0;liCount<miLength;++liCount)
  {
   float liRange;

   glTranslatef(miSize,0,0);
  if(mpShader) mpShader->Use();
  else _USE_FIXED_FUNCTION();

  SetShaderVariables();
   liRange=0.015625*(mpFont->Character(mpString[liCount])); //(or /64)
   if (liRange)
   {
    glBegin(GL_QUADS);
      glTexCoord2f(1,liRange);          glVertex2f(miSize,0);
      glTexCoord2f(1,liRange+0.015625); glVertex2f(miSize,miSize);
      glTexCoord2f(0,liRange+0.015625); glVertex2f(0,miSize);
      glTexCoord2f(0,liRange);          glVertex2f(0,0);
    glEnd();
   }
  }
 }

}




void cText::Text(char *lsText)
{
 strcpy(mpString,lsText);
 miLength=strlen(mpString);
 Setup();
}

void cText::Setup()
{
miSize=0.025;
Set2D();
}
cText::cText(const char *lsText)
{

 mpFont=0;
 strcpy(mpString,lsText);
 miLength=strlen(mpString);
 Setup();
}

cText::cText()
{
  Setup();
  
}

void cText::Font(vFont *lpFont)
{
  mpFont=lpFont;
  
}

void cText::Size(float liSize)
{
  miSize=liSize;
  
}
