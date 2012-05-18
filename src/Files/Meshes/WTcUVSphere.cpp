#include "../../WTBamboo.h"

cUVSphere::cUVSphere(uint8 liSubdivisions,float lfUVSphereSize,bool lbNormals,bool UVCoords)
{
    Generate(liSubdivisions,lfUVSphereSize,lbNormals,UVCoords);

    BufferMesh();
}


cUVSphere::~cUVSphere()
{

}
/*
void cUVSphere::Generate(uint8 liSubdivisions,float lfUVSphereSize,bool lbNormals,bool UVCoords)
{

    if(liSubdivisions%2) liSubdivisions--;
    uint8 VertSubdivisions=(liSubdivisions/2-1);

    GenerateSpace(liSubdivisions*(liSubdivisions-2)+2,0,0,2*(liSubdivisions)*(VertSubdivisions));

    float lfAngleSize=2*WT_PI/liSubdivisions;

    mpVertex[0]=0.0f;
    mpVertex[1]=lfUVSphereSize;
    mpVertex[2]=0.0f;

    uint32 liCount=3;



    for(uint8 liU=0;liU<liSubdivisions;++liU)
    {
        for(uint8 liV=1;liV<=VertSubdivisions;++liV)
        {
            float SinV=sin(liV*lfAngleSize);
            mpVertex[liCount]=sin(liU*lfAngleSize)*SinV*lfUVSphereSize;
            mpVertex[liCount+1]=cos(liV*lfAngleSize)*lfUVSphereSize;
            mpVertex[liCount+2]=cos(liU*lfAngleSize)*SinV*lfUVSphereSize;
            liCount+=3;
        }
    }

    mpVertex[liCount]=0.0f;
    mpVertex[liCount+1]=-lfUVSphereSize;
    mpVertex[liCount+2]=0.0f;

    liCount+=3;

    miVertex=liCount/3;

    liCount=0;
    for(uint8 liU=0;liU<liSubdivisions-1;++liU)
    {
        mpFaces[liCount]=0;
        mpFaces[liCount+1]=VertSubdivisions*liU+1;
        mpFaces[liCount+2]=VertSubdivisions*(liU+1)+1;
        liCount+=3;

        mpFaces[liCount]=miVertex-1;
        mpFaces[liCount+1]=VertSubdivisions*(liU+2);
        mpFaces[liCount+2]=VertSubdivisions*(liU+1);
        liCount+=3;
    }

    mpFaces[liCount]=0;
    mpFaces[liCount+1]=VertSubdivisions*(liSubdivisions-1)+1;
    mpFaces[liCount+2]=1;
    liCount+=3;

    mpFaces[liCount]=miVertex-1;
    mpFaces[liCount+1]=VertSubdivisions;
    mpFaces[liCount+2]=VertSubdivisions*(liSubdivisions);
    liCount+=3;


   for(uint8 liU=0;liU<liSubdivisions-1;++liU)
    {
        for(uint8 liV=1;liV<=VertSubdivisions-1;++liV)
        {
            mpFaces[liCount]=liU*VertSubdivisions+liV;
            mpFaces[liCount+1]=liU*VertSubdivisions+liV+1;
            mpFaces[liCount+2]=(liU+1)*VertSubdivisions+liV;

            liCount+=3;

            mpFaces[liCount]=liU*VertSubdivisions+liV+1;
            mpFaces[liCount+1]=(liU+1)*VertSubdivisions+liV+1;
            mpFaces[liCount+2]=(liU+1)*VertSubdivisions+liV;

            liCount+=3;
        }
    }

    uint8 liU=liSubdivisions-1;
    for(uint8 liV=1;liV<=VertSubdivisions-1;++liV)
    {
        mpFaces[liCount]=liU*VertSubdivisions+liV;
        mpFaces[liCount+1]=liU*VertSubdivisions+liV+1;
        mpFaces[liCount+2]=liV;

        liCount+=3;

        mpFaces[liCount]=liU*VertSubdivisions+liV+1;
        mpFaces[liCount+1]=liV+1;
        mpFaces[liCount+2]=liV;

        liCount+=3;
    }

    miFaces=liCount/3;

  if(lbNormals) CreateNormalArray();
  if(UVCoords) CreateUVSphereMap();

};
*/

void cUVSphere::Generate(uint8 liSubdivisions,float lfUVSphereSize,bool lbNormals,bool UVCoords)
{

    if(liSubdivisions%2) liSubdivisions--;
    uint8 VertSubdivisions=(liSubdivisions/2-1);

    GenerateSpace(liSubdivisions*(liSubdivisions-2)+2,0,0,2*(liSubdivisions)*(VertSubdivisions));

    float lfAngleSize=2*WT_PI/liSubdivisions;

    mpVertex[0]=0.0f;
    mpVertex[1]=lfUVSphereSize;
    mpVertex[2]=0.0f;

    uint32 liCount=3;



    for(uint8 liU=0;liU<liSubdivisions;++liU)
    {
        for(uint8 liV=1;liV<=VertSubdivisions;++liV)
        {
            float SinV=sin(liV*lfAngleSize);
            mpVertex[liCount]=sin(liU*lfAngleSize)*SinV*lfUVSphereSize;
            mpVertex[liCount+1]=cos(liV*lfAngleSize)*lfUVSphereSize;
            mpVertex[liCount+2]=cos(liU*lfAngleSize)*SinV*lfUVSphereSize;
            liCount+=3;
        }
    }

    mpVertex[liCount]=0.0f;
    mpVertex[liCount+1]=-lfUVSphereSize;
    mpVertex[liCount+2]=0.0f;

    liCount+=3;

    miVertex=liCount/3;

    liCount=0;
    for(uint8 liU=0;liU<liSubdivisions-1;++liU)
    {
        mpFaces[liCount]=VertSubdivisions*(liU+1)+1;
        mpFaces[liCount+1]=VertSubdivisions*liU+1;
        mpFaces[liCount+2]=0;
        liCount+=3;

        mpFaces[liCount]=VertSubdivisions*(liU+1);
        mpFaces[liCount+1]=VertSubdivisions*(liU+2);
        mpFaces[liCount+2]=miVertex-1;
        liCount+=3;
    }

    mpFaces[liCount]=1;
    mpFaces[liCount+1]=VertSubdivisions*(liSubdivisions-1)+1;
    mpFaces[liCount+2]=0;
    liCount+=3;

    mpFaces[liCount]=VertSubdivisions*(liSubdivisions);
    mpFaces[liCount+1]=VertSubdivisions;
    mpFaces[liCount+2]=miVertex-1;
    liCount+=3;


   for(uint8 liU=0;liU<liSubdivisions-1;++liU)
    {
        for(uint8 liV=1;liV<=VertSubdivisions-1;++liV)
        {
            mpFaces[liCount]=(liU+1)*VertSubdivisions+liV;
            mpFaces[liCount+1]=liU*VertSubdivisions+liV+1;
            mpFaces[liCount+2]=liU*VertSubdivisions+liV;

            liCount+=3;

            mpFaces[liCount]=(liU+1)*VertSubdivisions+liV;
            mpFaces[liCount+1]=(liU+1)*VertSubdivisions+liV+1;
            mpFaces[liCount+2]=liU*VertSubdivisions+liV+1;

            liCount+=3;
        }
    }

    uint8 liU=liSubdivisions-1;
    for(uint8 liV=1;liV<=VertSubdivisions-1;++liV)
    {
        mpFaces[liCount]=liV;
        mpFaces[liCount+1]=liU*VertSubdivisions+liV+1;
        mpFaces[liCount+2]=liU*VertSubdivisions+liV;

        liCount+=3;

        mpFaces[liCount]=liV;
        mpFaces[liCount+1]=liV+1;
        mpFaces[liCount+2]=liU*VertSubdivisions+liV+1;

        liCount+=3;
    }

    miFaces=liCount/3;

  if(lbNormals) CreateNormalArray();
  if(UVCoords) CreateUVSphereMap();

};
