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

cModel::cModel(cCamera *lpCamera) : cRenderObject(lpCamera)
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
/*
    glBindBuffer(GL_ARRAY_BUFFER, mpMesh->mBuffer1);
    glVertexAttribPointer(mpShader->VertexPositionID(), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(mpShader->VertexPositionID());

    glVertexAttribPointer(mpShader->VertexNormalID(), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const GLvoid*>(mpMesh->Vertex()*3*sizeof(float)));
    glEnableVertexAttribArray(mpShader->VertexNormalID());

    glVertexAttribPointer(mpShader->VertexUVID(), 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const GLvoid*>(mpMesh->Vertex()*6*sizeof(float)));
    glEnableVertexAttribArray(mpShader->VertexUVID());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mpMesh->mBuffer2);
    glDrawElements(GL_TRIANGLES,mpMesh->Faces()*3,GL_UNSIGNED_SHORT,0);
*/
  mpMesh->RenderMesh();
 }
}


