#include "../../WTDivWin.h"
//#include <cmath>

cTexturedModel::cTexturedModel()
{
 Identity();
 mpMesh=0;
 mpTexture=0;
}

cTexturedModel::cTexturedModel(cRenderNode *lpRenderer) : cRenderObject(lpRenderer)
{
 Identity();
 mpMesh=0;
 mpTexture=0;
}

void cTexturedModel::Texture(vTexture *lpTexture)
{
 mpTexture=lpTexture;
}

void cTexturedModel::Mesh(vMesh *lpGraph)
{
 mpMesh=lpGraph;
}


void cTexturedModel::RenderPainter(uint8 liLevel)
{

(void) liLevel;
 if(mpMesh)
 {
  PrepareMaterial();
  SetShaderVariables();


  mpMesh->RenderMesh();
 }
}

void cTexturedModel::RenderToPainter()
{


 UpdateMatrix();

 mpPainterData->SetObject(this);
 //mpPainterData->SetMatrix(Temp);
 mpPainterData->SetTexture(TextureNumber());

 mpPainterData->SetShader(mpShader);
mpPainterData->RenderAgain();
 //cPainter::Instance()->Add(lcTemp);
}

void cTexturedModel::Render()
{

 glEnable(GL_TEXTURE_2D);

  UpdateMatrix();
  UpdateCache();

 PrepareMaterial();

  mpTexture->BindTexture();

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);


  if(mpShader) mpShader->Use();
  else _USE_FIXED_FUNCTION();


 SetShaderVariables();
  AdditionalRenderFunctions();

  mpMesh->RenderMesh();

}


unsigned int cTexturedModel::TextureNumber()
{
  return mpTexture->TextureNumber();

}

vTexture *cTexturedModel::Texture()
{
 return mpTexture;
}
