#include "stdafx.h"
#include "../../WTBamboo.h"

using namespace std;

void cTextureGenerator::Depth(uint8 liDepth)
{
    miDepth=liDepth;
    miPixelSize=miDepth>>3;
};

    cTextureGenerator::cTextureGenerator(cMesh *lpMesh,c2DVi liSize,uint8 liDepth)
    {
        mpMesh=lpMesh;
        miSize=liSize;
        mbDiffuse=true;
        mbNormalMap=false;
        mbEmmisions=false;
        mpSeams=0;
        mpTextures=0;
        miTextures=0;
        Depth(liDepth);
    };

    void cTextureGenerator::DiffuseMap(bool lbState){mbDiffuse=lbState;};
    void cTextureGenerator::NormalMap(bool lbState){mbNormalMap=lbState;};
    void cTextureGenerator::Emmisions(bool lbState){mbEmmisions=lbState;};
    bool cTextureGenerator::DiffuseMap(){return mbDiffuse;};
    bool cTextureGenerator::NormalMap(){return mbNormalMap;};
    bool cTextureGenerator::Emmisions(){return mbEmmisions;};
    void cTextureGenerator::Size(c2DVi liSize){ miSize=liSize; };
    void cTextureGenerator::Mesh(cMesh *lpMesh){mpMesh=lpMesh; };

    uint8 cTextureGenerator::CalculateTextures()
    {
        uint8 liReturn=0;
        if(mbDiffuse) liReturn++;
        if(mbNormalMap) liReturn++;
        if(mbEmmisions) liReturn++;
        return liReturn;
    };

    void cTextureGenerator::Prepare()
    {
       if(!mpTextures || mpTextures[0]->Depth()!=miDepth || mpTextures[0]->Width()!=miSize[0] || mpTextures[0]->Height()!=miSize[1])
       {
            NewTextures();
       }

        delete mpSeams;
        mpSeams=new cSeamList(miTextures,mpTextures);

        mpSeams->GenerateSeamList(mpMesh);
        mpSeams->GenerateAreaMap();
      }

      void cTextureGenerator::NewTextures()
      {
        miTextures=CalculateTextures();
        delete []mpTextures;
        mpTextures=new cTexture*[miTextures];

        for(uint8 liTexture=0;liTexture<miTextures;++liTexture)
        {
            mpTextures[liTexture]=new cEmptyTexture(miSize,miDepth);
        }
      }

    cTexture **cTextureGenerator::GenerateAsteroidTextures()
    {
        c2DVf lfInvSize(1.0f/miSize[0],1.0f/miSize[1]);
        Prepare();
/*
        for(uint32 liX=0;liX<miSize[0];++liX)
        {
            for(uint32 liY=0;liY<miSize[1];++liY)
            {
                c3DVf lfValue=mpMesh->GetTexture3DLocation(c2DVf(liX*lfInvSize[0],liY*lfInvSize[1]));
                //mpTextures[0]->Data()[((miSize[0]*miSize[1])+miSize[0])*miDepth>>3]=cSimplexNoise::Noise(lfValue[0],lfValue[1],lfValue[2]);
                *(mpTextures[0]->GetPixel(c2DVi(liX,liY)))=cSimplexNoise::Noise(lfValue[0],lfValue[1],lfValue[2]);
            }
        }
        */
        for(uint32 liCount=0;liCount<miTextures;++liCount)
        {
            mpTextures[liCount]->ColorTexture(cRGBA(1.0f,0.0f,0.0f,1.0f));
            mpTextures[liCount]->BufferTexture();
        }


        return mpTextures;

    };
