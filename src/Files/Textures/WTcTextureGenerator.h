#ifndef __WTCTEXTUREGENERATOR_H__
#define __WTCTEXTUREGENERATOR_H__

class cTextureGenerator
{
        cTexture **mpTextures;
        uint32 miTextures;
        cMesh *mpMesh;
        cSeamList *mpSeams;
        c2DVi miSize;
        uint8 miDepth;
        uint8 miPixelSize;
        bool mbDiffuse,mbNormalMap,mbEmmisions;
public:

    cTextureGenerator(cMesh *lpMesh,c2DVi liSize,uint8 liDepth=32);

    void DiffuseMap(bool lbState);
    void NormalMap(bool lbState);
    void Emmisions(bool lbState);

    bool DiffuseMap();
    bool NormalMap();
    bool Emmisions();

    uint8 CalculateTextures();

    void Size(c2DVi liSize);
    void Depth(uint8 liDepth);
    void Mesh(cMesh *lpMesh);


    void Prepare();

    void NewTextures();

    cTexture **GenerateAsteroidTextures();
};

#endif
