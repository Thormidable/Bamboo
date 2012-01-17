#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

cLandscape::cLandscape(cmLandscape *lpModel)
{
 //This function needs serious cutting down
 mpLandscape=lpModel;
	mb3D=true;
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


#endif

