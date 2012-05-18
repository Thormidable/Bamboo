#include "../../WTBamboo.h"
//#include <cmath>

cModel::cModel()
{
 mpMesh=0;
 }

cModel::cModel(vRenderNode *lpRenderer) : cRenderObject(lpRenderer)
{
 mpMesh=0;
}

cModel::cModel(cCamera *lpCamera) : cRenderObject(lpCamera)
{
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

float cModel::GetSize()
{
    if(mpMesh) return mpMesh->GetSize();
    return 0.0f;
}

double cModel::GetSizeSq()
{
    if(mpMesh) return mpMesh->GetSizeSq();
    return 0.0f;
}


c2DVf cModel::GetUVCoords(c3DVf GlobalPos)
{
 if(mpMesh && mpVariables && mpShader)
 {

     GlobalPos-=mmCache.Position();

 float *lpTangent=0;
 uint32 liTemp=mpShader->ShaderVariableSet()->GetAttributePosition("Bb_Tangent");

 if(liTemp)lpTangent=reinterpret_cast<float*>(mpVariables->GetVariable(liTemp-1)->Data());

 float *lpBinormal=0;
 liTemp=mpShader->ShaderVariableSet()->GetAttributePosition("Bb_Binormal");
 if(liTemp)lpBinormal=reinterpret_cast<float*>(mpVariables->GetVariable(liTemp-1)->Data());


 float *lpNormal=0;
 liTemp=mpShader->ShaderVariableSet()->GetAttributePosition("Bb_Normal");
 if(liTemp)lpNormal=reinterpret_cast<float*>(mpVariables->GetVariable(liTemp-1)->Data());

 return mpMesh->FindUVCoordinates(FindRelativeCoord(GlobalPos),
											lpTangent,
											lpBinormal,
											lpNormal);
/*
     return mpMesh->FindUVCoordinates(c3DVf(GlobalPos[0]*mmCache.Xx()+GlobalPos[1]*mmCache.Yx()+GlobalPos[2]*mmCache.Zx(),
                                            GlobalPos[0]*mmCache.Xy()+GlobalPos[1]*mmCache.Yy()+GlobalPos[2]*mmCache.Zy(),
                                            GlobalPos[0]*mmCache.Xz()+GlobalPos[1]*mmCache.Yz()+GlobalPos[2]*mmCache.Zz()),
											lpTangent,
											lpBinormal,
											lpNormal);*/
 }
 return c2DVf(0.0f,0.0f);
};

