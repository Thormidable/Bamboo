#include "../../WTDivWin.h"


cLandscape::cLandscape()
{
	mpLandscape=0;
	mpTexture=0;
	mb3D=true;
}

cLandscape::cLandscape(cmLandscape *lpModel,cTexture *lpTexture)
{
 //This function needs serious cutting down
 mpLandscape=lpModel;
 mpTexture=lpTexture;
	mb3D=true;
}


void cLandscape::RenderPainter(uint8 liLevel)
{
 (void) liLevel;
 if (mpLandscape)
 {

  PrepareMaterial();
 SetShaderVariables();
  mpLandscape->RenderMesh();
 }
}

void cLandscape::RenderToPainter()
{
 float Temp[16];
 UpdateMatrix();
 glGetFloatv(GL_MODELVIEW_MATRIX,Temp);


 mpPainterData->SetObject(this);
 //mpPainterData->SetMatrix(Temp);
 mpPainterData->SetTexture(mpTexture->TextureNumber());
SetOtherRenderVariables();
mpPainterData->RenderAgain();
 //cPainter::Instance()->Add(lcTemp);
}


	void cLandscape::Texture(cTexture *lpTexture){mpTexture=lpTexture;};
	/// Set the current height map for this landscape object.
	void cLandscape::Landscape(cmLandscape *lpLandscape){mpLandscape=lpLandscape;};
	/// Will return the height at Global co-ordinates lfX,lfZ.
	float cLandscape::GetHeight(float lfX,float lfZ){if(mpLandscape) return mpLandscape->GetHeightLocal(lfX-X(),lfZ-Z())-Y();  else return 0.0f;};
	/// Will return the height at the Local position lfX,lfZ (relative to landscapes corner)
	float cLandscape::GetHeightLocal(float lfX,float lfZ){if(mpLandscape) return mpLandscape->GetHeightLocal(lfX,lfZ); else return 0.0f;};
	/// Will return the height of the vertex at liX,liZ. (position is based on number of segments NOT distance)
	float cLandscape::GetVertexHeight(int liX,int liZ){if(mpLandscape) return mpLandscape->GetVertexHeight(liX,liZ); else return 0.0f;};



