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

void cModel::Mesh(const char* lcReference)
{
 mpMesh=_GET_MESH_FILE(lcReference);
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


