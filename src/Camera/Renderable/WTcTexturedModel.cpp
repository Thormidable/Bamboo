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

void cTexturedModel::Texture(cTexture *lpTexture)
{
 mpTexture=lpTexture;
}

void cTexturedModel::Mesh(cMesh *lpGraph)
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
 mpPainterData->SetTexture(TextureNumber());
 SetOtherRenderVariables();
 mpPainterData->RenderAgain();

}


unsigned int cTexturedModel::TextureNumber()
{
  return mpTexture->TextureNumber();

}

cTexture *cTexturedModel::Texture()
{
 return mpTexture;
}

