
#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO


cLandscape::cLandscape(cmLandscape *lpModel,cCamera *lpCamera) : cRenderObject(lpCamera)
{
 mpLandscape=lpModel;
	mb3D=true;

	mbNormalArray=true;
	mbUVArray=true;
}


cLandscape::cLandscape(cmLandscape *lpModel)
{
 mpLandscape=lpModel;
	mb3D=true;
	mbNormalArray=true;
	mbUVArray=true;
}

void cLandscape::Landscape(string lsLandscape)
{
 mpLandscape=_GET_LANDSCAPE_FILE(lsLandscape.c_str());
 mbNormalArray=true;
	mbUVArray=true;
}




void cLandscape::RenderPainter()
{

 if (mpLandscape)
 {

  PrepareMaterial();
 SetShaderVariables();
  mpLandscape->RenderMesh();
 }
}



	void cLandscape::Landscape(cmLandscape *lpLandscape){mpLandscape=lpLandscape;};

	float cLandscape::GetHeight(float lfX,float lfZ){if(mpLandscape) return mpLandscape->GetHeightLocal(lfX-X(),lfZ-Z())-Y();  else return 0.0f;};

	float cLandscape::GetHeightLocal(float lfX,float lfZ){if(mpLandscape) return mpLandscape->GetHeightLocal(lfX,lfZ); else return 0.0f;};

	float cLandscape::GetVertexHeight(int liX,int liZ){if(mpLandscape) return mpLandscape->GetVertexHeight(liX,liZ); else return 0.0f;};

float cLandscape::GetSize()
{
    if(mpLandscape) return mpLandscape->GetSize();
    return 0.0f;
}

double cLandscape::GetSizeSq()
{
    if(mpLandscape) return mpLandscape->GetSizeSq();
    return 0.0f;
}

#endif

