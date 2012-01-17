#include "../../WTBamboo.h"
//#include <cmath>

cModel::cModel()
{
 Identity();
 mpMesh=0;
 }

cModel::cModel(vRenderNode *lpRenderer) : cRenderObject(lpRenderer)
{
 Identity();
 mpMesh=0;
}

void cModel::Mesh(cMesh *lpGraph)
{
 mpMesh=lpGraph;
}

cMesh *cModel::Mesh(){return mpMesh;}

void cModel::RenderPainter()
{
 if(mpMesh)
 {
  PrepareMaterial();
  SetShaderVariables();


  mpMesh->RenderMesh();
 }
}


