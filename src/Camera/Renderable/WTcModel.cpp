
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
    mbNormalArray=mpMesh->NormalData();
    mbUVArray=mpMesh->UVData();
  //PrepareMaterial();
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
 }
 return c2DVf(0.0f,0.0f);
};

void cModel::UpdateArrayStates()
{
 if(mpMesh)
 {
     mbNormalArray=mpMesh->NormalData();
     mbUVArray=mpMesh->UVData();
 }
};





/*
cRenderableTexture::cRenderableTexture()
{
    mbClearTexture=true;
    mcClearColor=cRGBA(0.0f,0.0f,0.0f,1.0f);
    glGenFramebuffers(1, &miFrameBuffer);
    mpData=0;
    strcpy(mpFileName,"RenderableTexture");
};*/

cRenderableTexture::cRenderableTexture(uint32 liWidth, uint8 liHeight, uint8 liDepth)
{
    miColorAttachment=0;
    mbClearTexture=true;
    mcClearColor=cRGBA(0.0f,0.0f,0.0f,1.0f);
    glGenFramebuffers(1, &miFrameBuffer);
    mpData=0;
    strcpy(mpFileName,"RenderableTexture");
    ResizeFrameBuffer(liWidth,liHeight,liDepth);
};
cRenderableTexture::cRenderableTexture(cTexture *lpTexture)
{
    miColorAttachment=0;
    mbClearTexture=true;
    mcClearColor=cRGBA(0.0f,0.0f,0.0f,1.0f);
    glGenFramebuffers(1, &miFrameBuffer);
    mpData=0;
    strcpy(mpFileName,"RenderableTexture");
    ResizeFrameBuffer(lpTexture->Width(),lpTexture->Height(),lpTexture->Depth());
};

cRenderableTexture::~cRenderableTexture()
{
    glDeleteFramebuffers(1,&miFrameBuffer);
};

void cRenderableTexture::ResizeFrameBuffer(uint32 liWidth,uint32 liHeight, uint8 liDepth)
{
    miDepth=liWidth;
    miHeight=liHeight;
    miDepth=liDepth;
    miPixelSize=miDepth>>3;

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, miFrameBuffer);
    BindTexture();

    if(miDepth==24) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width(),Height(), 0, GL_BGR, GL_UNSIGNED_BYTE, NULL);
    if(miDepth==32) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width(),Height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+miColorAttachment, GL_TEXTURE_2D, miTexture, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status!=GL_FRAMEBUFFER_COMPLETE) printf("FrameBuffer ERROR\n");
}

void cRenderableTexture::PrepTextureToWriteTo()
{
       glBindFramebuffer(GL_DRAW_FRAMEBUFFER, miFrameBuffer);
       if(mbClearTexture)
       {

           glClearColor(mcClearColor.R(),mcClearColor.G(),mcClearColor.B(),mcClearColor.A());
            //glScissor(mfViewportX,mfViewportY,mfViewportWidth,mfViewportHeight);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       }
};

void cRenderableTexture::FinishWriteToTexture()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
};


void cRenderableTexture::ExtractTexture()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER,miFrameBuffer);
    glReadBuffer(GL_COLOR_ATTACHMENT0+miColorAttachment);

    if(mpData) delete []mpData;
    mpData=new uint8[miPixelSize*miWidth*miHeight];

    if(miDepth==24) glReadPixels(0,0,miWidth,miHeight,GL_BGR,GL_UNSIGNED_BYTE,mpData);
    if(miDepth==32) glReadPixels(0,0,miWidth,miHeight,GL_BGRA,GL_UNSIGNED_BYTE,mpData);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
};

void cRenderableTexture::BufferTexture()
{
//This function intentionally left blank

}

void cRenderableTexture::SetColorAttachment(uint8 liColor)
{
 miColorAttachment=liColor;
};


cScreenQuadMesh *cPostProcess::spMesh = 0;

cPostProcess::cPostProcess()
{
    if(!spMesh) spMesh=new cScreenQuadMesh();
}

cPostProcess::cPostProcess(cCamera *lpCamera) : cRenderObject(lpCamera)
{
    if(!spMesh) spMesh=new cScreenQuadMesh();
}

cPostProcess::cPostProcess(vRenderNode *lpCamera) : cRenderObject(lpCamera)
{
    if(!spMesh) spMesh=new cScreenQuadMesh();
}

void cPostProcess::RenderPainter()
{
    SetShaderVariables();
    spMesh->RenderMesh();
}

cScreenQuadMesh::cScreenQuadMesh()
{
 mpVertex=new float[12];

 mpVertex[10]=mpVertex[5]=mpVertex[3]=mpVertex[11]=mpVertex[8]=mpVertex[2]=mpVertex[1]=mpVertex[0]=0.0f;
 mpVertex[9]=mpVertex[7]=mpVertex[6]=mpVertex[4]=1.0f;

 mpFaces=new FACE_TYPE[4];
 mpFaces[0]=0;
 mpFaces[1]=1;
 mpFaces[2]=2;
 mpFaces[3]=3;

 BufferMesh();

}


void cRenderableTexture::SetClearColor(cRGBA lcColor)
{
    mcClearColor=lcColor;
};
void cRenderableTexture::SetClearState(bool lbClear)
{
    mbClearTexture=lbClear;
};



















