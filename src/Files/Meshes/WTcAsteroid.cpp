#include "../../WTBamboo.h"

cAsteroid::cAsteroid(float lfRandomRange, uint8 liSubdivisions,float lfAsteroidSize)
{
    GenerateIcosphere(lfAsteroidSize);
    Generate(lfRandomRange,liSubdivisions);

    BufferMesh();
}

cAsteroid::cAsteroid(float lfRandomRange, uint8 liSubdivisions,cMesh *lpBase)
{
  if(lpBase) Equals(lpBase,"AsteroidMesh");
  else GenerateIcosphere();

  if(mpNormals || mpUV)
  {
      float *lpTemp=new float[3*miVertex];
      memcpy(lpTemp,mpVertex,sizeof(float)*miVertex*3);
      delete []mpVertex;
      mpVertex=lpTemp;
      mpUV=0;
      mpNormals=0;
  }

  Generate(lfRandomRange,liSubdivisions);

    BufferMesh();


}

cAsteroid::~cAsteroid()
{

}
void cAsteroid::Generate(float lfRandomRange, uint8 liSubdivisions)
{
 RandomiseVerteces(lfRandomRange);
 for(;liSubdivisions;--liSubdivisions)
 {
     SubdivideEdges();
     lfRandomRange*=0.5f;
     RemoveDuplicateVerteces(0.001f);
     RandomiseVerteces(lfRandomRange);
 }



 float *lpTempV=new float[miVertex*8];
  memcpy(lpTempV,mpVertex,sizeof(float)*miVertex*3);
  delete []mpVertex;
  mpVertex=lpTempV;
  mpNormals=&mpVertex[miVertex*3];
  mpUV=&mpVertex[miVertex*6];

  CreateNormalArray();
  //CreateNormalArrayFlat();
  CreateUVSphereMap();



};

    void cAsteroid::RandomiseVerteces(float lfRange)
    {
        for(uint32 liCount=0;liCount<miVertex*3;++liCount)
        {
            mpVertex[liCount]+=ZEROED_RANDOM_NUMBER*lfRange;
        }
    };

	void cAsteroid::SubdivideEdges()
	{
	    uint32 liVerteces=miFaces*2+2;
	    //This is the correct way to determine number of Verteces;
	    float *lpTempV=new float[liVerteces*9];

        uint32 liFaces=miFaces*4;
	    //This the correct way to determine the number of Faces.
        FACE_TYPE *lpTempF=new FACE_TYPE[liFaces*3];

        uint32 liVMade=0;
        uint32 liFMade=0;

        for(uint32 liCount=0;liCount<miFaces;++liCount)
        {
            c3DVf Vx[3];
            Vx[0]=&mpVertex[mpFaces[liCount*3]*3];
            Vx[1]=&mpVertex[mpFaces[liCount*3+1]*3];
            Vx[2]=&mpVertex[mpFaces[liCount*3+2]*3];

            c3DVf Vc[3];
            Vc[0]=(Vx[0]+Vx[1])*0.5f;
            Vc[1]=(Vx[0]+Vx[2])*0.5f;
            Vc[2]=(Vx[2]+Vx[1])*0.5f;

            memcpy(&lpTempV[liVMade*3],Vx[0].v,sizeof(float)*3);
            memcpy(&lpTempV[liVMade*3+3],Vx[1].v,sizeof(float)*3);
            memcpy(&lpTempV[liVMade*3+6],Vx[2].v,sizeof(float)*3);

            memcpy(&lpTempV[liVMade*3+9],Vc[0].v,sizeof(float)*3);
            memcpy(&lpTempV[liVMade*3+12],Vc[1].v,sizeof(float)*3);
            memcpy(&lpTempV[liVMade*3+15],Vc[2].v,sizeof(float)*3);

            lpTempF[liFMade++]=liVMade;
            lpTempF[liFMade++]=liVMade+3;
            lpTempF[liFMade++]=liVMade+4;

            lpTempF[liFMade++]=liVMade+3;
            lpTempF[liFMade++]=liVMade+1;
            lpTempF[liFMade++]=liVMade+5;

            lpTempF[liFMade++]=liVMade+5;
            lpTempF[liFMade++]=liVMade+2;
            lpTempF[liFMade++]=liVMade+4;

            lpTempF[liFMade++]=liVMade+3;
            lpTempF[liFMade++]=liVMade+5;
            lpTempF[liFMade++]=liVMade+4;

            liVMade+=6;

        }
    delete []mpFaces;
    delete []mpVertex;

    miVertex=liVerteces*3;
    miFaces=liFaces;
    mpVertex=lpTempV;
    mpFaces=lpTempF;

	};

	void cAsteroid::GenerateIcosphere(float lfAsteroidSize)
	{
        delete []mpVertex;
        delete []mpFaces;

        mpVertex=new float[36];
        mpFaces=new FACE_TYPE[60];

        float t = lfAsteroidSize*((1.0 + sqrt(5.0)) / 2.0f);

        mpVertex[0]=-lfAsteroidSize; mpVertex[1]=t; mpVertex[2]=0.0f;
        mpVertex[3]=lfAsteroidSize; mpVertex[4]=t; mpVertex[5]=0.0f;
        mpVertex[6]=-lfAsteroidSize; mpVertex[7]=-t; mpVertex[8]=0.0f;
        mpVertex[9]=lfAsteroidSize; mpVertex[10]=-t; mpVertex[11]=0.0f;

        mpVertex[12]=0.0f; mpVertex[13]=-lfAsteroidSize; mpVertex[14]=t;
        mpVertex[15]=0.0f; mpVertex[16]=lfAsteroidSize; mpVertex[17]=t;
        mpVertex[18]=0.0f; mpVertex[19]=-lfAsteroidSize; mpVertex[20]=-t;
        mpVertex[21]=0.0f; mpVertex[22]=lfAsteroidSize; mpVertex[23]=-t;

        mpVertex[24]=t; mpVertex[25]=0.0f; mpVertex[26]=-lfAsteroidSize;
        mpVertex[27]=t; mpVertex[28]=0.0f; mpVertex[29]=lfAsteroidSize;
        mpVertex[30]=-t; mpVertex[31]=0.0f; mpVertex[32]=-lfAsteroidSize;
        mpVertex[33]=-t; mpVertex[34]=0.0f; mpVertex[35]=lfAsteroidSize;

        mpFaces[0]=5; mpFaces[1]=11; mpFaces[2]=0;
        mpFaces[3]=1; mpFaces[4]=5; mpFaces[5]=0;
        mpFaces[6]=7; mpFaces[7]=1; mpFaces[8]=0;
        mpFaces[9]=10; mpFaces[10]=7; mpFaces[11]=0;
        mpFaces[12]=11; mpFaces[13]=10; mpFaces[14]=0;

        mpFaces[15]=9; mpFaces[16]=5; mpFaces[17]=1;
        mpFaces[18]=4; mpFaces[19]=11; mpFaces[20]=5;
        mpFaces[21]=2; mpFaces[22]=10; mpFaces[23]=11;
        mpFaces[24]=6; mpFaces[25]=7; mpFaces[26]=10;
        mpFaces[27]=8; mpFaces[28]=1; mpFaces[29]=7;

        mpFaces[30]=4; mpFaces[31]=9; mpFaces[32]=3;
        mpFaces[33]=2; mpFaces[34]=4; mpFaces[35]=3;
        mpFaces[36]=6; mpFaces[37]=2; mpFaces[38]=3;
        mpFaces[39]=8; mpFaces[40]=6; mpFaces[41]=3;
        mpFaces[42]=9; mpFaces[43]=8; mpFaces[44]=3;

        mpFaces[45]=5; mpFaces[46]=9; mpFaces[47]=4;
        mpFaces[48]=11; mpFaces[49]=4; mpFaces[50]=2;
        mpFaces[51]=10; mpFaces[52]=2; mpFaces[53]=6;
        mpFaces[54]=7; mpFaces[55]=6; mpFaces[56]=8;
        mpFaces[57]=1; mpFaces[58]=8; mpFaces[59]=9;

        mpUV=0;
        mpNormals=0;

        miFaces=20;
        miVertex=12;

	};
