
#include "../../WTBamboo.h"

void cMeshArray::LoadIMF(ifstream &FileStream)
{
 uint32 liTemp;
 uint32 liFormat;
	FileStream.ignore(sizeof(uint32));

	FileStream.read((int8*) &liTemp,sizeof(uint32));
	mpRef=new char[liTemp+1];
	FileStream.read((int8*) mpRef,liTemp*sizeof(int8));
	mpRef[liTemp]=0;

	FileStream.read((int8 *) &(liFormat),sizeof(uint32));
	FileStream.read((char *) &(miVertex),sizeof(uint32));

	mpVertex=new float[8*miVertex];
	mpNormals=&mpVertex[3*miVertex];
	mpUV=&mpVertex[6*miVertex];
	if(liFormat&IMF_MODEL_VERTEX)
	{
//	  mpVertex=new float[3*miVertex];
	  FileStream.read((char *) mpVertex,3*sizeof(float)*miVertex);
	} else mpVertex=0;

	if(liFormat&IMF_MODEL_NORMALS)
	{
	//mpNormals=new float[3*miVertex];
	FileStream.read((char *) mpNormals,3*sizeof(float)*miVertex);
	} else mpNormals=0;

	if(liFormat&IMF_MODEL_UVS)
	{
	//mpUV=new float[2*miVertex];
	FileStream.read((char *) mpUV,2*sizeof(float)*miVertex);
	} else mpUV=0;

	FileStream.read((char *) &(miFaces),sizeof(uint32));

	if(liFormat&IMF_MODEL_FACES)
	{
	  mpFaces=new uint16[miFaces*3];
	  FileStream.read((char *) mpFaces,3*sizeof(uint16)*miFaces);
	}else mpFaces=0;
}

cMeshArray::cMeshArray()
{
	mpVertex=0;mpNormals=0;mpUV=0;mpFaces=0;miVertex=0;miFaces=0;mpRef=0;
}

cMeshArray::~cMeshArray()
{
	if(mpRef) delete []mpRef;
}

cMesh::cMesh(cMeshArray *lpMesh)
{

    glGenBuffers(1,&mBuffer1);
	glGenBuffers(1,&mBuffer2);

	miModelCentre[0]=miModelCentre[1]=miModelCentre[2]=0.0f;
	strcpy(mpFileName,lpMesh->mpRef);

	mpVertex=lpMesh->mpVertex;
	mpUV=lpMesh->mpUV;
	mpNormals=lpMesh->mpNormals;
	mpFaces=lpMesh->mpFaces;

	miFaces=lpMesh->miFaces;
	miVertex=lpMesh->miVertex;

	BufferMesh();
	FindSize();




}

cMesh::~cMesh()
{
	if(mpVertex) {delete []mpVertex; mpVertex=0;}
	//if(mpNormals) {delete []mpNormals; mpNormals=0;}
	//if(mpUV) {delete []mpUV; mpUV=0;}
	if(mpFaces) {delete []mpFaces; mpFaces=0;}
	if(mBuffer1) {glDeleteBuffers(1, &mBuffer1);mBuffer1=0;}
	if(mBuffer2) {glDeleteBuffers(1, &mBuffer2);mBuffer2=0;}
}

void cMesh::Position(float lfX,float lfY,float lfZ)
{
	uint32 liCount;

	miModelCentre[0]+=lfX;
	miModelCentre[1]+=lfY;
	miModelCentre[2]+=lfZ;
	for(liCount=0;liCount<miVertex*3;liCount+=3)
	{
		mpVertex[liCount]-=lfX;
		mpVertex[liCount+1]-=lfY;
		mpVertex[liCount+2]-=lfZ;
	}
FindSize();
}

void cMesh::PositionX(float lfX)
{
	uint32 liCount;
	miModelCentre[0]+=lfX;
	for(liCount=0;liCount<miVertex;++liCount)
	{
		mpVertex[liCount*3]-=lfX;
	}
FindSize();
}

void cMesh::PositionY(float lfY)
{
	uint32 liCount;
	miModelCentre[0]+=lfY;
	for(liCount=0;liCount<miVertex;++liCount)
	{
		mpVertex[liCount*3+1]-=lfY;
	}
FindSize();
}

void cMesh::PositionZ(float lfZ)
{
	uint32 liCount;
	miModelCentre[2]+=lfZ;
	for(liCount=0;liCount<miVertex;++liCount)
	{
		mpVertex[liCount*3+2]-=lfZ;
	}
FindSize();
}

void cMesh::ResetPosition()
{
	uint32 liCount;
	for(liCount=0;liCount<miVertex*3;liCount+=3)
	{
		mpVertex[liCount]+=miModelCentre[0];
		mpVertex[liCount+1]+=miModelCentre[1];
		mpVertex[liCount+2]+=miModelCentre[2];
	}
FindSize();
}



//This operates Exclusively on a triangulated array
void cMesh::CreateNormalArray()
{

CreateNormalArrayFlat();

//Smooth Normals;

for(uint32 liCount=0;liCount<miVertex;++liCount)
{
    //printf("\n liCount : %u\n",liCount);
    c3DVf lvNormal(0.0f,0.0f,0.0f);
    c3DVf lvVertex(&mpVertex[liCount*3]);
    for(uint32 liLoop=0;liLoop<miVertex;++liLoop)
    {
        if(lvVertex==&mpVertex[liLoop*3])
        {
      //      printf("Found Vertex to Smooth : %u %u\n",liCount,liLoop);
            lvNormal+=&mpNormals[liLoop*3];
        }
    }
    //printf("lvNormal : %f %f %f\n",lvNormal[0],lvNormal[1],lvNormal[2]);
    lvNormal.Normalise();
    //printf("lvNormal : %f %f %f\n",lvNormal[0],lvNormal[1],lvNormal[2]);
    for(uint32 liLoop=0;liLoop<miVertex;++liLoop)
    {
        if(lvVertex==&mpVertex[liLoop*3])
        {
            memcpy(&mpNormals[liLoop*3],lvNormal.v,sizeof(float)*3);
            //printf("Found Vertex to Smooth : %u %u\n",liCount,liLoop);
        }
    }

}

RemoveDuplicateVerteces(0.0001f);



}


//This operates Exclusively on a triangulated array
void cMesh::CreateNormalArrayFlat()
{
    float *lpVertex=new float[miFaces*24];
    float *lpNormals=&lpVertex[miFaces*9];

    float *lpUV=0; if(mpUV) lpUV=&lpVertex[miFaces*18];

    uint16 *lpFaces=new uint16[miFaces*3];
    uint32 liVertex=miFaces*3;
    uint32 liFaces=miFaces;

	uint32 liCount;

	for(liCount=0;liCount<liVertex;++liCount)
	{
	    uint32 liPos=mpFaces[liCount];
	    memcpy(&lpVertex[liCount*3],&mpVertex[liPos*3],sizeof(float)*3);
	    lpNormals[liCount*3]=lpNormals[liCount*3+1]=lpNormals[liCount*3+2]=0.0f;
	    if(mpUV) memcpy(&lpUV[liCount*2],&mpUV[liPos*2],sizeof(float)*2);

	    lpFaces[liCount]=liCount;
	}


    delete []mpVertex;
    delete []mpFaces;
    mpVertex=lpVertex;
    mpNormals=lpNormals;
    mpUV=lpUV;

    mpFaces=lpFaces;
    miVertex=liVertex;
    miFaces=liFaces;

	c3DVf v1,v2;

    uint32 liFurthest=0;
    uint32 liFace=0;
    double lfFurthest=0.0;

	for(liCount=0;liCount<miFaces*3;liCount+=3)
	{
	    v2=&mpVertex[mpFaces[liCount]*3];
	    if(v2.MagnitudeSq()>lfFurthest)
        {
            liFace=liCount/3;
            liFurthest=mpFaces[liCount];
            lfFurthest=v2.MagnitudeSq();
        }
        v2=&mpVertex[mpFaces[liCount+1]*3];
	    if(v2.MagnitudeSq()>lfFurthest)
        {
            liFace=liCount/3;
            liFurthest=mpFaces[liCount+1];
            lfFurthest=v2.MagnitudeSq();
        }
        v2=&mpVertex[mpFaces[liCount+2]*3];
	    if(v2.MagnitudeSq()>lfFurthest)
        {
            liFace=liCount/3;
            liFurthest=mpFaces[liCount+2];
            lfFurthest=v2.MagnitudeSq();
        }

		v1.v[0]=mpVertex[mpFaces[liCount]*3]-mpVertex[mpFaces[liCount+1]*3];
		v1.v[1]=mpVertex[mpFaces[liCount]*3+1]-mpVertex[mpFaces[liCount+1]*3+1];
		v1.v[2]=mpVertex[mpFaces[liCount]*3+2]-mpVertex[mpFaces[liCount+1]*3+2];

		v2.v[0]=mpVertex[mpFaces[liCount]*3]-mpVertex[mpFaces[liCount+2]*3];
		v2.v[1]=mpVertex[mpFaces[liCount]*3+1]-mpVertex[mpFaces[liCount+2]*3+1];
		v2.v[2]=mpVertex[mpFaces[liCount]*3+2]-mpVertex[mpFaces[liCount+2]*3+2];

		v1=v1*v2;

		v1.Normalise();

        mpNormals[mpFaces[liCount]*3]=  v1.v[0];
        mpNormals[mpFaces[liCount]*3+1]=v1.v[1];
        mpNormals[mpFaces[liCount]*3+2]=v1.v[2];

		mpNormals[mpFaces[liCount+2]*3]=  v1.v[0];
		mpNormals[mpFaces[liCount+2]*3+1]=v1.v[1];
		mpNormals[mpFaces[liCount+2]*3+2]=v1.v[2];

		mpNormals[mpFaces[liCount+1]*3]=  v1.v[0];
		mpNormals[mpFaces[liCount+1]*3+1]=v1.v[1];
		mpNormals[mpFaces[liCount+1]*3+2]=v1.v[2];
	}

    ForceNormalDirectionStart(liFurthest,liFace);

	for(liCount=0;liCount<miVertex;liCount++)
	{
	    c3DVf Vert(&mpVertex[liCount*3]);
	  //   printf("DotProd : %u %f\n",liCount,Vert.Dot(&mpNormals[liCount*3]));
        //printf("Vertex/Norm %u: %f %f %f,%f %f %f\n",liCount,mpVertex[liCount*3],mpVertex[liCount*3+1],mpVertex[liCount*3+2],mpNormals[liCount*3],mpNormals[liCount*3+1],mpNormals[liCount*3+2]);
	}

}

void cMesh::ForceNormalDirectionStart(uint32 liFurthest,uint32 liFace)
{
    c3DVf v1;
    bool *lbDone = new bool[miFaces];
    for(uint32 liCount=0;liCount<miFaces;++liCount)
	{
        lbDone[liCount]=false;
	}

    v1=&mpVertex[liFurthest*3];

    if(v1.Dot(&mpNormals[liFurthest*3])<0.0f)
    {
        mpNormals[liFurthest*3]=-mpNormals[liFurthest*3];
        mpNormals[liFurthest*3+1]=-mpNormals[liFurthest*3+1];
        mpNormals[liFurthest*3+2]=-mpNormals[liFurthest*3+2];
    }

    if(v1.Dot(&mpNormals[mpFaces[liFace*3]*3])<0.0f)
    {
        mpNormals[mpFaces[liFace*3]*3]=-mpNormals[mpFaces[liFace*3]*3]; mpNormals[mpFaces[liFace*3]*3+1]=-mpNormals[mpFaces[liFace*3]*3+1]; mpNormals[mpFaces[liFace*3]*3+2]=-mpNormals[mpFaces[liFace*3]*3+2];
    }
    if(v1.Dot(&mpNormals[mpFaces[liFace*3+1]*3])<0.0f)
    {
        mpNormals[mpFaces[liFace*3+1]*3]=-mpNormals[mpFaces[liFace*3+1]*3]; mpNormals[mpFaces[liFace*3+1]*3+1]=-mpNormals[mpFaces[liFace*3+1]*3+1]; mpNormals[mpFaces[liFace*3+1]*3+2]=-mpNormals[mpFaces[liFace*3+1]*3+2];
    }
    if(v1.Dot(&mpNormals[mpFaces[liFace*3+2]*3])<0.0f)
    {
        mpNormals[mpFaces[liFace*3+2]*3]=-mpNormals[mpFaces[liFace*3+2]*3]; mpNormals[mpFaces[liFace*3+2]*3+1]=-mpNormals[mpFaces[liFace*3+2]*3+1]; mpNormals[mpFaces[liFace*3+2]*3+2]=-mpNormals[mpFaces[liFace*3+2]*3+2];
    }
    lbDone[liFace]=true;

    ForceNormalDirection(liFurthest,liFace,lbDone);

    for(uint32 liCount=0;liCount<miFaces;++liCount)
	{
     if(!lbDone[liCount])  printf("Face Not Done : %lu\n",liCount);
	}
}

void cMesh::ZeroCentre()
{
    c3DVd Centre(0.0f,0.0f,0.0f);
    for(uint32 liCount=0;liCount<miVertex;++liCount)
    {
        c3DVd Temp(mpVertex[liCount*3],mpVertex[liCount*3+1],mpVertex[liCount*3+2]);
        Centre+=Temp;
    }

    double lfMag=1.0/(miVertex);
    Centre*=lfMag;

    for(uint32 liCount=0;liCount<miVertex;++liCount)
    {
        mpVertex[liCount*3]-=Centre[0];
        mpVertex[liCount*3+1]-=Centre[1];
        mpVertex[liCount*3+2]-=Centre[2];
    }
}

void cMesh::ForceNormalDirection(uint32 liFurthest,uint32 liFace,bool *lbDone)
{
    c3DVf v1=&mpNormals[liFurthest*3];

	for(uint32 liCount=0;liCount<miFaces;++liCount)
	{
            if(lbDone[liCount]==false && ContainsVertex(c3DVf(&mpVertex[liFurthest*3]),liCount))
            {
                int8 Share=FacesShareEdge(&mpFaces[liFace*3],&mpFaces[liCount*3]);
                if(Share>-1)
                {
                                     c3DVf Vect;
                    bool lbConcave;
                    bool lbPerpendicular;
                    bool lbAcute;

                     {

                     float *lpFurthest=&mpVertex[liFurthest*3];
                     float *lpFurthestNormal=&mpNormals[liFurthest*3];
                     uint16 *lpFaceCorrect=&mpFaces[liFace*3];
                     uint16 *lpFaceUnknown=&mpFaces[liCount*3];

                            int8 liOtherShare=FacesShareEdge(lpFaceCorrect,lpFaceUnknown);
    int8 liFurthestShare=FacesShareEdge(lpFaceUnknown,lpFaceCorrect);

       double lfEq;


c3DVf lpRV;

                    if(liFurthestShare==0)
                    {
                        if(lpFurthest==&mpVertex[lpFaceCorrect[1]*3]) lpRV=&mpVertex[lpFaceCorrect[2]*3];
                        else lpRV=&mpVertex[lpFaceCorrect[1]*3];
                    }
                    else
                    {
                        if(liFurthestShare==1)
                        {
                            if(lpFurthest==&mpVertex[lpFaceCorrect[0]*3]) lpRV=&mpVertex[lpFaceCorrect[2]*3];
                            else lpRV=&mpVertex[lpFaceCorrect[0]*3];
                        }
                        else
                        {
                                if(lpFurthest==&mpVertex[lpFaceCorrect[1]*3]) lpRV=&mpVertex[lpFaceCorrect[0]*3];
                                else lpRV=&mpVertex[lpFaceCorrect[1]*3];
                        }
                    }

                    lpRV-=lpFurthest;

lpRV.Normalise();

c3DVf lpStart(&mpVertex[lpFaceUnknown[liOtherShare]*3]);
lpStart-=lpFurthest;

//Find the number of Ray vectors to reach the perpendicular.
lfEq=(lpStart[0]*lpRV[0]+
		lpStart[1]*lpRV[1]+
		lpStart[2]*lpRV[2]);
c3DVf lpOtherCentre(lpFurthest);
lpOtherCentre+=(lpRV*lfEq);


lpStart=&mpVertex[lpFaceCorrect[liFurthestShare]*3];
lpStart-=lpFurthest;

//Find the number of Ray vectors to reach the sphere.
lfEq=(lpStart[0]*lpRV[0]+
		lpStart[1]*lpRV[1]+
		lpStart[2]*lpRV[2]);

c3DVf lpFurthestCentre(lpFurthest);
lpFurthestCentre+=(lpRV*lfEq);


    c3DVf lpOtherFaceVect(&mpVertex[lpFaceUnknown[liOtherShare]*3]);
    lpOtherFaceVect-=lpOtherCentre;

    c3DVf lpFurthestFaceVect(&mpVertex[lpFaceCorrect[liFurthestShare]*3]);
    lpFurthestFaceVect-=lpFurthestCentre;

    Vect=lpFurthestFaceVect;


    if(lpOtherFaceVect.Dot(lpFurthestNormal)>0.0f) lbConcave=true;
    else lbConcave=false;

    c3DVf lvOtherNormal=&mpNormals[lpFaceUnknown[0]*3];

    float lfNormalDot=lvOtherNormal.Dot(lpFurthestNormal);
    if(lfNormalDot>-0.0001f && lfNormalDot<0.0001f) lbPerpendicular=true;
    else lbPerpendicular=false;

    //printf("\n");
    //printf("Angle : %f\n",lpOtherFaceVect.Angle(lpFurthestFaceVect));
    if(lpOtherFaceVect.Angle(lpFurthestFaceVect)<(3.141569*0.5f)) lbAcute=true;
    else lbAcute=false;

    }

                    uint32 liCurFace=mpFaces[liCount*3]*3;
                     if(!lbAcute)
                     {

                            if(v1.Dot(&mpNormals[liCurFace])<0.0f){ mpNormals[liCurFace]=-mpNormals[liCurFace]; mpNormals[liCurFace+1]=-mpNormals[liCurFace+1]; mpNormals[liCurFace+2]=-mpNormals[liCurFace+2]; }
                            else
                            {
                                if(lbPerpendicular)
                                {
                                     if((lbConcave && Vect.Dot(&mpNormals[liCurFace])<0.0f)||(!lbConcave && Vect.Dot(&mpNormals[liCurFace])>0.0f))
                                    {
                                        mpNormals[liCurFace]=-mpNormals[liCurFace]; mpNormals[liCurFace+1]=-mpNormals[liCurFace+1]; mpNormals[liCurFace+2]=-mpNormals[liCurFace+2];
                                    }
                                 }                            }
                     }
                     else
                     {
                            if(v1.Dot(&mpNormals[liCurFace])>0.0f){ mpNormals[liCurFace]=-mpNormals[liCurFace]; mpNormals[liCurFace+1]=-mpNormals[liCurFace+1]; mpNormals[liCurFace+2]=-mpNormals[liCurFace+2]; }
                            else
                            {

                                if(lbPerpendicular)
                                {
                                     if((lbConcave && Vect.Dot(&mpNormals[liCurFace])<0.0f)||(!lbConcave && Vect.Dot(&mpNormals[liCurFace])>0.0f))
                                    {
                                        mpNormals[liCurFace]=-mpNormals[liCurFace]; mpNormals[liCurFace+1]=-mpNormals[liCurFace+1]; mpNormals[liCurFace+2]=-mpNormals[liCurFace+2];
                                    }
                                 }


                            }
                     }

                     memcpy(&mpNormals[mpFaces[liCount*3+1]*3],&mpNormals[liCurFace],sizeof(float)*3);
                     memcpy(&mpNormals[mpFaces[liCount*3+2]*3],&mpNormals[liCurFace],sizeof(float)*3);

                      lbDone[liCount]=true;

                    if(mpFaces[liCount*3]!=liFurthest) ForceNormalDirection(mpFaces[liCount*3],liCount,lbDone);
                    if(mpFaces[liCount*3+1]!=liFurthest) ForceNormalDirection(mpFaces[liCount*3+1],liCount,lbDone);
                    if(mpFaces[liCount*3+2]!=liFurthest) ForceNormalDirection(mpFaces[liCount*3+2],liCount,lbDone);
                }
                }


            }
}

uint8 cMesh::FaceCompare(float *lpFurthest,float *lpFurthestNormal,uint16 *lpFaceCorrect,uint16 *lpFaceUnknown)
{
    int8 liOtherShare=FacesShareEdge(lpFaceCorrect,lpFaceUnknown);
    int8 liFurthestShare=FacesShareEdge(lpFaceUnknown,lpFaceCorrect);

       double lfEq;

c3DVf lpStart(&mpVertex[lpFaceUnknown[liOtherShare]*3]);
lpStart-=lpFurthest;

c3DVf lpRV;

                    if(liFurthestShare==0)
                    {
                        if(lpFurthest==&mpVertex[lpFaceCorrect[1]*3]) lpRV=&mpVertex[lpFaceCorrect[2]*3];
                        else lpRV=&mpVertex[lpFaceCorrect[1]*3];
                    }
                    else
                    {
                        if(liFurthestShare==1)
                        {
                            if(lpFurthest==&mpVertex[lpFaceCorrect[0]*3]) lpRV=&mpVertex[lpFaceCorrect[2]*3];
                            else lpRV=&mpVertex[lpFaceCorrect[0]*3];
                        }
                        else
                        {
                                if(lpFurthest==&mpVertex[lpFaceCorrect[1]*3]) lpRV=&mpVertex[lpFaceCorrect[0]*3];
                                else lpRV=&mpVertex[lpFaceCorrect[1]*3];
                        }
                    }

                    lpRV-=lpFurthest;

//Find the number of Ray vectors to reach the perpendicular.
lfEq=(lpStart[0]*lpRV[0]+
		lpStart[1]*lpRV[1]+
		lpStart[2]*lpRV[2]);

c3DVf lpOtherCentre=lpStart+lpRV*lfEq;


lpStart=&mpVertex[lpFaceCorrect[liFurthestShare]*3];
lpStart-=lpFurthest;


//Find the number of Ray vectors to reach the sphere.
lfEq=(lpStart[0]*lpRV[0]+
		lpStart[1]*lpRV[1]+
		lpStart[2]*lpRV[2]);

c3DVf lpFurthestCentre=lpStart+lpRV*lfEq;

    c3DVf lpOtherFaceVect(&mpVertex[lpFaceUnknown[liOtherShare]*3]);
    lpOtherFaceVect-=lpOtherCentre;

    c3DVf lpFurthestFaceVect(&mpVertex[lpFaceCorrect[liFurthestShare]*3]);
    lpFurthestFaceVect-=lpFurthestCentre;

    bool lbConcave;
    if(lpOtherFaceVect.Dot(lpFurthestNormal)>0.0f) lbConcave=true;
    else lbConcave=false;

    c3DVf lvOtherNormal=&mpNormals[lpFaceUnknown[0]*3];
    bool lbPerpendicular;
    if(lvOtherNormal.Dot(lpFurthestNormal)==0.0f) lbPerpendicular=true;
    else lbPerpendicular=false;

    bool lbAcute;
    if(lpOtherFaceVect.Angle(lpFurthestFaceVect)<90) lbAcute=true;
    else lbAcute=false;

    uint8 liData=0;
    if(lbConcave) liData=liData|0x1;
    if(lbPerpendicular) liData=liData|0x2;
    if(lbAcute) liData=liData|0x4;

    return liData;



}

int8 cMesh::FacesShareEdge(FACE_TYPE *lpFace1,FACE_TYPE *lpFace2)
{
    int8 liCount=0;
    bool lbVerts[3];
    c3DVf Vertex1[3];
    c3DVf Vertex2[3];
    Vertex1[0]=&mpVertex[lpFace1[0]*3];
    Vertex1[1]=&mpVertex[lpFace1[1]*3];
    Vertex1[2]=&mpVertex[lpFace1[2]*3];

    Vertex2[0]=&mpVertex[lpFace2[0]*3];
    Vertex2[1]=&mpVertex[lpFace2[1]*3];
    Vertex2[2]=&mpVertex[lpFace2[2]*3];

    if(Vertex2[0]==Vertex1[0] || Vertex2[0]==Vertex1[1] || Vertex2[0]==Vertex1[2]) {lbVerts[0]=true; ++liCount;} else lbVerts[0]=false;
    if(Vertex2[1]==Vertex1[0] || Vertex2[1]==Vertex1[1] || Vertex2[1]==Vertex1[2]) {lbVerts[1]=true; ++liCount;} else lbVerts[1]=false;
    if(Vertex2[2]==Vertex1[0] || Vertex2[2]==Vertex1[1] || Vertex2[2]==Vertex1[2]) {lbVerts[2]=true; ++liCount;} else lbVerts[2]=false;

    if(liCount>1)
    {
        if(!lbVerts[0]) return 0;
        if(!lbVerts[1]) return 1;
        if(!lbVerts[2]) return 2;
        //return 3;
    }
    return -1;
}

bool cMesh::ContainsVertex(c3DVf lcVert,uint32 liFace)
{
 if(lcVert==&mpVertex[mpFaces[liFace*3]*3]) return 1;
 if(lcVert==&mpVertex[mpFaces[liFace*3+1]*3]) return 1;
 if(lcVert==&mpVertex[mpFaces[liFace*3+2]*3]) return 1;
 return 0;
}


//This operates Exclusively on a triangulated array
void cMesh::CreateUVSphereMap()
{
 float *lpVert=new float[16*miVertex];
 uint32 liSize=6;
 float *lpNorm=0; if(mpNormals) {lpNorm=&lpVert[liSize*miVertex]; liSize+=6;}
 float *lpUV=&lpVert[liSize*miVertex];

 uint32 liVertex=miVertex;
 memcpy(lpVert,mpVertex,sizeof(float)*miVertex*3);
 if(mpNormals) memcpy(lpNorm,mpNormals,sizeof(float)*miVertex*3);
 memcpy(lpUV,mpUV,sizeof(float)*miVertex*2);

 //uint32 liSeamStart=miVertex;



//FindSeam
for(uint32 liCount=0;liCount<miFaces;++liCount)
{
    float *lpVertex[3];
    lpVertex[0]=&mpVertex[mpFaces[liCount*3]*3];
    lpVertex[1]=&mpVertex[mpFaces[liCount*3+1]*3];
    lpVertex[2]=&mpVertex[mpFaces[liCount*3+2]*3];
//if one point above and one point beneath the line, duplicate the Vertex beneath.

    bool lbAbove=false;
    bool lbBelow=false;

    for(uint8 liLoop=0;liLoop<3;++liLoop)
    {
        if(lpVertex[liLoop][1]>=0.0f) lbAbove=true;
        if(lpVertex[liLoop][1]<0.0f) lbBelow=true;
         mpUV[mpFaces[liCount*3+liLoop]*2]=1.0f;
        mpUV[mpFaces[liCount*3+liLoop]*2+1]=1.0f;
    }

    //If this is a seam
    if(lbAbove && lbBelow)
    {
     for(uint8 liLoop=0;liLoop<3;++liLoop)
     {
        if(lpVertex[liLoop][1]<0.0f)
        {
            memcpy(&lpVert[liVertex*3],lpVertex[liLoop],sizeof(float)*3);
            if(mpNormals) memcpy(&lpNorm[liVertex*3],&mpNormals[mpFaces[liCount*3+liLoop]*3],sizeof(float)*3);
            lpUV[liVertex*2]=-2.0f;
            lpUV[liVertex*2+1]=-2.0f;
            mpFaces[liCount*3+liLoop]=liVertex;

            ++liVertex;
        }
     }
    }

}

delete[] mpVertex;

mpVertex=new float[liVertex*8];
liSize=3;
if(mpNormals) {mpNormals=&mpVertex[liVertex*3]; liSize+=3;}
mpUV=&mpVertex[liVertex*liSize];

memcpy(mpVertex,lpVert,sizeof(float)*3*liVertex);
if(mpNormals) memcpy(mpNormals,lpNorm,sizeof(float)*3*liVertex);
memcpy(mpUV,lpUV,sizeof(float)*2*liVertex);

miVertex=liVertex;

lpVert=mpVertex;
lpUV=mpUV;
for(uint32 liCount=0;liCount<miVertex;liCount++)
{
	lpVert=&mpVertex[liCount*3];
	lpUV=&mpUV[liCount*2];
    float lfAlpha=atan2(sqrt(lpVert[0]*lpVert[0]+lpVert[2]*lpVert[2]),lpVert[1]);

	c2DVf lfVec(lpVert[0],lpVert[2]);
	float lfScale=lfVec.Magnitude();

	if(lpVert[1]>=0.0f || (lpUV[0]<0.0f && lpUV[1]<0.0f))
	{
		c2DVf lvPos(0.3f,0.3f);
		lfVec*=lfAlpha*0.5f/(3.141569f*lfScale);
		lvPos+=lfVec;
		lpUV[0]=lvPos[0];
		lpUV[1]=lvPos[1];
	}
	else
	{
	    c2DVf lvPos(0.75f,0.75f);
		lfVec*=((3.141569-fabs(lfAlpha))*0.5f/(3.141569f*lfScale));
		lvPos+=lfVec;
		lpUV[0]=lvPos[0];
		lpUV[1]=lvPos[1];
	}
}

}


void cMesh::BufferMesh()
{
	uint8 liSize=3;
	if(mpNormals) liSize+=3;
	if(mpUV) liSize+=2;

	glBindBuffer(GL_ARRAY_BUFFER, mBuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*miVertex*liSize, mpVertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16)*miFaces*3, mpFaces, GL_STATIC_DRAW);

}

void cMesh::RenderMesh()
{

	glBindBuffer(GL_ARRAY_BUFFER, mBuffer1);

	glVertexPointer(3,GL_FLOAT,0,0);
	if(mpNormals)
	{
		glNormalPointer(GL_FLOAT,0,reinterpret_cast<const GLvoid*>(miVertex*3*sizeof(float)));
	}

	if(mpUV)
	{
	    if(mpNormals) glTexCoordPointer(2,GL_FLOAT,0,reinterpret_cast<const GLvoid*>(miVertex*6*sizeof(float)));
	    else glTexCoordPointer(2,GL_FLOAT,0,reinterpret_cast<const GLvoid*>(miVertex*3*sizeof(float)));
	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer2);
	glDrawElements(GL_TRIANGLES,miFaces*3,GL_UNSIGNED_SHORT,0);

}

float cMesh::GetSize()
{
return mfSize;
}

double cMesh::GetSizeSq()
{
    return mfSize*mfSize;
}

void cMesh::FindSize()
{
 uint32 liCount;
 float mfTemp;
 mfSize=0.0f;
 for(liCount=0;liCount<miVertex*3;liCount+=3)
 {
  mfTemp=(mpVertex[liCount]*mpVertex[liCount]+mpVertex[liCount+1]*mpVertex[liCount+1]+mpVertex[liCount+2]*mpVertex[liCount+2]);
  if(mfTemp>mfSize) mfSize=mfTemp;
 }
 mfSize=sqrt(mfSize);
}


cMesh::cMesh()
{
    miModelCentre[0]=miModelCentre[1]=miModelCentre[2]=0.0f; mpVertex=0;mpNormals=0;mpUV=0;mpFaces=0;miFaces=0;miVertex=0;
    glGenBuffers(1,&mBuffer1);
	glGenBuffers(1,&mBuffer2);

};

	uint8 cMesh::VertexSize()
	{
	    uint8 liSize=0;
	    if(mpVertex) liSize+=3;
	    if(mpNormals) liSize+=3;
	    if(mpUV) liSize+=2;
	    return liSize;
	}

	cMesh *cMesh::Duplicate(string lsFileName)
	{

	    cMesh *lpNew=new cMesh();
	    lpNew->miVertex=miVertex;
	    lpNew->miFaces=miFaces;
	    uint8 liSize=VertexSize();
	    lpNew->mpVertex=new float[liSize*miVertex];
	    memcpy(lpNew->mpVertex,mpVertex,sizeof(float)*liSize*miVertex);
	    liSize=3;
	    if(mpNormals) {lpNew->mpNormals=&lpNew->mpVertex[sizeof(float)*liSize*miVertex]; liSize+=3;}
	    if(mpUV) {lpNew->mpUV=&lpNew->mpVertex[sizeof(float)*liSize*miVertex]; liSize+=2;}

	    lpNew->mpFaces=new uint16[miFaces*3];
	    memcpy(lpNew->mpFaces,mpFaces,sizeof(uint16)*miFaces*3);

	    if(lsFileName=="") strcpy(lpNew->mpFileName,"GeneratedMesh");
	    else strcpy(lpNew->mpFileName,lsFileName.c_str());

        BufferMesh();

	    return lpNew;
	}

	void cMesh::Equals(cMesh *lpMesh, string lsFileName)
	{
	   miVertex=lpMesh->miVertex;
       miFaces=lpMesh->miFaces;
	   uint8 liSize=lpMesh->VertexSize();

        delete []mpVertex;
        delete []mpFaces;

	    mpVertex=new float[liSize*miVertex];
	    memcpy(mpVertex,lpMesh->mpVertex,sizeof(float)*liSize*miVertex);
	    liSize=3;
	    if(lpMesh->mpNormals) {mpNormals=&mpVertex[sizeof(float)*liSize*miVertex]; liSize+=3;}
	    if(lpMesh->mpUV) {mpUV=&mpVertex[sizeof(float)*liSize*miVertex]; liSize+=2;}

	    mpFaces=new uint16[miFaces*3];
	    memcpy(mpFaces,lpMesh->mpFaces,sizeof(uint16)*miFaces*3);

	    if(lsFileName=="") strcpy(mpFileName,"GeneratedMesh");
	    else strcpy(mpFileName,lsFileName.c_str());

        BufferMesh();
	}



 /// This will return the number of verteces in the vertex position array mpVertex.
 uint32 cMesh::Verteces(){return miVertex;}
/// This will return the number of faces in the face array mpFaces.
 uint32 cMesh::Faces(){return miFaces;}
 /// This will return a pointer to the vertex position array.
 float *cMesh::VertexData(){return mpVertex;}
/// This will return a pointer to the face array..
FACE_TYPE*cMesh::FaceData(){return mpFaces;}
 /// This will return a pointer to the array of vertex normals.
 float *cMesh::NormalData(){return mpNormals;}
 /// This will return a pointer to the array of texture co-ordinates.
 float *cMesh::UVData(){return mpUV;}


float *cMesh::Vertex(uint32 liVertex){return &mpVertex[liVertex*3];};
FACE_TYPE *cMesh::Face(uint32 liFace){return &mpFaces[liFace*3];};
FACE_TYPE cMesh::Face(uint32 liFace,uint8 liVertex){return mpFaces[liFace*3+liVertex];};
float *cMesh::Normal(uint32 liVertex){return &mpNormals[liVertex*3];};
float *cMesh::UV(uint32 liVertex){return &mpUV[liVertex*2];};

float cMesh::GetAngleSum(uint32 liFace,float *lpPos)
{
	float lp1[4],lp2[4],lp3[4];
	c3DVf FaceData[3];
	FaceData[0]=&mpVertex[mpFaces[liFace*3]*3];
	FaceData[1]=&mpVertex[mpFaces[liFace*3+1]*3];
	FaceData[2]=&mpVertex[mpFaces[liFace*3+2]*3];

	lp1[0]=FaceData[0].X()-lpPos[0];
	lp1[1]=FaceData[0].Y()-lpPos[1];
	lp1[2]=FaceData[0].Z()-lpPos[2];
	lp1[3]=sqrt(lp1[0]*lp1[0]+lp1[1]*lp1[1]+lp1[2]*lp1[2]);

	lp2[0]=FaceData[1].X()-lpPos[0];
	lp2[1]=FaceData[1].Y()-lpPos[1];
	lp2[2]=FaceData[1].Z()-lpPos[2];
	lp2[3]=sqrt(lp2[0]*lp2[0]+lp2[1]*lp2[1]+lp2[2]*lp2[2]);


	lp3[0]=FaceData[2].X()-lpPos[0];
	lp3[1]=FaceData[2].Y()-lpPos[1];
	lp3[2]=FaceData[2].Z()-lpPos[2];
	lp3[3]=sqrt(lp3[0]*lp3[0]+lp3[1]*lp3[1]+lp3[2]*lp3[2]);

	double lfAngle=acos((lp1[0]*lp2[0]+lp1[1]*lp2[1]+lp1[2]*lp2[2])/(lp1[3]*lp2[3]));
	lfAngle+=acos((lp3[0]*lp2[0]+lp3[1]*lp2[1]+lp3[2]*lp2[2])/(lp3[3]*lp2[3]));
	lfAngle+=acos((lp3[0]*lp1[0]+lp3[1]*lp1[1]+lp3[2]*lp1[2])/(lp3[3]*lp1[3]));

	//printf("lfAngle : %f\n",lfAngle);
	return lfAngle;
}

//This Takes Coordinates in Model Pos.
//Convert them to Model Pos before shunting here
c2DVf cMesh::FindUVCoordinates(c3DVf ModelPos,float *lpTangent,float *lpBinormal,float *NormalData)
{

    if(lpTangent && lpBinormal && NormalData)
	{
	   // printf("Vertex Centre : %f %f %f\n",ModelPos[0],ModelPos[1],ModelPos[2]);
		//printf("FindUV Centre : %f %f %f\n",ModelPos[0],ModelPos[1],ModelPos[2]);
    //Find Face.
    float lfDist=10000.0f;
    uint32 liPos=miFaces+1;
	c3DVf lvFacePoint;
    float *lpVertex;
    float *lpNormal;
        for(uint32 liCount=0;liCount<miFaces;++liCount)
        {

            lpVertex=&mpVertex[mpFaces[liCount*3]*3];
            lpNormal=&NormalData[mpFaces[liCount*3]*3];

            float PlaneValue=lpNormal[0]*lpVertex[0]+lpNormal[1]*lpVertex[1]+lpNormal[2]*lpVertex[2];
            float GlobalValue=ModelPos.Dot(lpNormal);
            if(PlaneValue==GlobalValue)
            {
				GlobalValue=0.0f;
                PlaneValue=GetAngleSum(liCount,ModelPos.v);
                if(PlaneValue>WT_RAY_ANGLE_LOWER && PlaneValue<WT_RAY_ANGLE_UPPER) {lfDist=0.0f; liPos=liCount; lvFacePoint=ModelPos; break;}
            }
            else
			{
				GlobalValue=PlaneValue-GlobalValue;
				//GlobalValue=GlobalValue-PlaneValue;
				if(fabs(GlobalValue)<lfDist)
				{
					c3DVf TempModelPos=ModelPos+c3DVf(lpNormal)*GlobalValue;
               		PlaneValue=GetAngleSum(liCount,TempModelPos.v);
                	if(PlaneValue>WT_RAY_ANGLE_LOWER && PlaneValue<WT_RAY_ANGLE_UPPER)
					{
						lfDist=fabs(GlobalValue);
						liPos=liCount;
						lvFacePoint=TempModelPos;
					}
				}
			}
        }

    //If Face has been found.
    if(liPos<miFaces)
    {

         lpVertex=&mpVertex[mpFaces[liPos*3]*3];
         lpNormal=&NormalData[mpFaces[liPos*3]*3];

        c2DVf FinalUV;
        c2DVf lpUV(&mpUV[mpFaces[liPos*3]*2]);

       /* printf("Face Has been found\n");
        printf("lpVertex: %f %f %f\n",lpVertex[0],lpVertex[1],lpVertex[2]);
        printf("lpNormal: %f %f %f\n",lpNormal[0],lpNormal[1],lpNormal[2]);
        printf("lpUV: %f %f\n",lpUV[0],lpUV[1]);*/



        c3DVf TVect(&lpTangent[mpFaces[liPos*3]*3]);
        c3DVf BVect(&lpBinormal[mpFaces[liPos*3]*3]);

        c3DVf lvVectXYZC0(lvFacePoint-lpVertex);

        c3DVf lvVectXYZ10(&mpVertex[mpFaces[liPos*3+1]*3]);
        lvVectXYZ10-=lpVertex;
        c3DVf lvVectXYZ20(&mpVertex[mpFaces[liPos*3+2]*3]);
        lvVectXYZ20-=lpVertex;

        c2DVf lvVectUV10(&mpUV[mpFaces[liPos*3+1]*2]);
        lvVectUV10-=lpUV;
        c2DVf lvVectUV20(&mpUV[mpFaces[liPos*3+2]*2]);
        lvVectUV20-=lpUV;
/*
        printf("Tangent (U) : %f %f %f\n",TVect[0],TVect[1],TVect[2]);
        printf("Binormal (V) : %f %f %f\n",BVect[0],BVect[1],BVect[2]);*/

        float *lpDisp=&mpVertex[mpFaces[liPos*3]*3];
        //printf("Vertex 0: %f %f %f\n",lpDisp[0],lpDisp[1],lpDisp[2]);
        lpDisp=&mpVertex[mpFaces[liPos*3+1]*3];
        //printf("Vertex 1: %f %f %f\n",lpDisp[0],lpDisp[1],lpDisp[2]);
        lpDisp=&mpVertex[mpFaces[liPos*3+2]*3];
        //printf("Vertex 2: %f %f %f\n",lpDisp[0],lpDisp[1],lpDisp[2]);

        lpDisp=&mpUV[mpFaces[liPos*3]*2];
        //printf("UV : 0 %f %f\n",lpDisp[0],lpDisp[1]);
        lpDisp=&mpUV[mpFaces[liPos*3+1]*2];
        //printf("UV : 1 %f %f\n",lpDisp[0],lpDisp[1]);
        lpDisp=&mpUV[mpFaces[liPos*3+2]*2];
        //printf("UV : 2 %f %f\n",lpDisp[0],lpDisp[1]);


        float TDot=TVect.Dot(lvVectXYZ10);
        float TDot2=TVect.Dot(lvVectXYZ20);
      //  printf("TDot : %f %f\n",TDot,TDot2);
        //if(fabs(TDot)>fabs(TDot2))
        if(fabs(lvVectUV10[0])>fabs(lvVectUV20[0]))
        {
            FinalUV[0]=lpUV[0]+((lvVectUV10[0]*TVect.Dot(lvVectXYZC0))/(TDot));
        //    printf("Tangent Ratio: %f\n",TVect.Dot(lvVectXYZC0)/TDot);
        //    printf("U Vect : %f\n",lvVectUV10[0]);
        }
        else
        {

                FinalUV[0]=lpUV[0]+((lvVectUV20[0]*TVect.Dot(lvVectXYZC0))/TDot2);
       //         printf("Tangent Ratio: %f\n",TVect.Dot(lvVectXYZC0)/TDot2);
       //         printf("U Vect : %f\n",lvVectUV20[0]);
        }
       // printf("U Base: %f\n",lpUV[1]);

        TDot=BVect.Dot(lvVectXYZ10);
        TDot2=BVect.Dot(lvVectXYZ20);
      //  printf("BDot : %f %f\n",TDot,TDot2);
        //if(fabs(TDot)>fabs(TDot2))
        if(fabs(lvVectUV10[1])>fabs(lvVectUV20[1]))
        {
            FinalUV[1]=lpUV[1]+((lvVectUV10[1]*BVect.Dot(lvVectXYZC0))/(TDot));
       //     printf("Binormal Ratio: %f\n",BVect.Dot(lvVectXYZC0)/TDot);
       //     printf("V Vect : %f\n",lvVectUV10[1]);
        }
        else
        {
                FinalUV[1]=lpUV[1]+((lvVectUV20[1]*BVect.Dot(lvVectXYZC0))/TDot2);
        //        printf("Binormal Ratio: %f\n",BVect.Dot(lvVectXYZC0)/TDot2);
        //        printf("V Vect : %f\n",lvVectUV20[1]);
        }
      //  printf("V Base: %f\n",lpUV[1]);



        return FinalUV;

    }
	}
//Error_Detected:
    c2DVf Result(0.0f,0.0f);
    return Result;
}

void cMesh::RemoveDuplicateVerteces(float lfMergeRange)
{
    uint32 liSpace=0;

if(!mpNormals && !mpUV)
{
    for(uint32 liCount=0;liCount<miVertex;++liCount)
    {
        bool lbFound=false;
        for(uint32 liLoop=0;liLoop<liSpace;++liLoop)
        {
            if(VertexMatch(liLoop,liCount,lfMergeRange))
            {
                UpdateFaces(liLoop,liCount);
                lbFound=true;
                break;
            }
        }
        if(!lbFound)
        {
			if(liSpace!=liCount)
			{
            	UpdateFaces(liSpace,liCount);
            	memmove(&mpVertex[liSpace*3],&mpVertex[liCount*3],sizeof(float)*3);
			}
            liSpace++;
        }
    }

    miVertex=liSpace;
}

else
{
    if(mpNormals)
    {
        if(mpUV)
        {
            for(uint32 liCount=0;liCount<miVertex;++liCount)
            {
                bool lbFound=false;
                for(uint32 liLoop=0;liLoop<liSpace;++liLoop)
                {
                    if(VertexMatch(liLoop,liCount,lfMergeRange) && NormalMatch(liLoop,liCount,lfMergeRange) && UVMatch(liLoop,liCount,lfMergeRange))
                    {
                        UpdateFaces(liLoop,liCount);
                        lbFound=true;
                        break;
                    }
                }
                if(!lbFound)
                {
					if(liSpace!=liCount)
					{
                    	UpdateFaces(liSpace,liCount);
                    	memcpy(&mpVertex[liSpace*3],&mpVertex[liCount*3],sizeof(float)*3);
                    	memcpy(&mpNormals[liSpace*3],&mpNormals[liCount*3],sizeof(float)*3);
                    	memcpy(&mpUV[liSpace*2],&mpUV[liCount*2],sizeof(float)*2);
					}
                    liSpace++;
                }
            }
        }
        else
        {
            for(uint32 liCount=0;liCount<miVertex;++liCount)
            {
                bool lbFound=false;
                for(uint32 liLoop=0;liLoop<liSpace;++liLoop)
                {
                    if(VertexMatch(liLoop,liCount,lfMergeRange) && NormalMatch(liLoop,liCount,lfMergeRange))
                    {
                        UpdateFaces(liLoop,liCount);
                        lbFound=true;
                        break;
                    }
                }
                if(!lbFound)
                {
					if(liSpace!=liCount)
					{
                    	UpdateFaces(liSpace,liCount);
                    	memcpy(&mpVertex[liSpace*3],&mpVertex[liCount*3],sizeof(float)*3);
                    	memcpy(&mpNormals[liSpace*3],&mpNormals[liCount*3],sizeof(float)*3);
					}
                    liSpace++;
                }
            }
        }

    }
    else
    {
        for(uint32 liCount=0;liCount<miVertex;++liCount)
        {
            bool lbFound=false;
            for(uint32 liLoop=0;liLoop<liSpace;++liLoop)
            {
                if(VertexMatch(liLoop,liCount,lfMergeRange) && UVMatch(liLoop,liCount,lfMergeRange))
                {
                    UpdateFaces(liLoop,liCount);
                    lbFound=true;
                    break;
                }
            }
            if(!lbFound)
            {
				if(liSpace!=liCount)
				{
                	UpdateFaces(liSpace,liCount);
                	memcpy(&mpVertex[liSpace*3],&mpVertex[liCount*3],sizeof(float)*3);
                	memcpy(&mpUV[liSpace*2],&mpUV[liCount*2],sizeof(float)*2);
				}
                liSpace++;
            }
        }
    }
}
};

bool cMesh::VertexMatch(uint32 liOne, uint32 liTwo,float lfMergeRange)
{
     if(mpVertex[liOne*3]<mpVertex[liTwo*3]+lfMergeRange && mpVertex[liOne*3]>mpVertex[liTwo*3]-lfMergeRange)
            {
                 if(mpVertex[liOne*3+1]<mpVertex[liTwo*3+1]+lfMergeRange && mpVertex[liOne*3+1]>mpVertex[liTwo*3+1]-lfMergeRange)
                {
                     if(mpVertex[liOne*3+2]<mpVertex[liTwo*3+2]+lfMergeRange && mpVertex[liOne*3+2]>mpVertex[liTwo*3+2]-lfMergeRange)
                    {
                        return 1;
                    }
                }
            }
            return 0;
}


bool cMesh::NormalMatch(uint32 liOne, uint32 liTwo,float lfMergeRange)
{
     if(mpNormals[liOne*3]<mpNormals[liTwo*3]+lfMergeRange && mpNormals[liOne*3]>mpNormals[liTwo*3]-lfMergeRange)
            {
                 if(mpNormals[liOne*3+1]<mpNormals[liTwo*3+1]+lfMergeRange && mpNormals[liOne*3+1]>mpNormals[liTwo*3+1]-lfMergeRange)
                {
                     if(mpNormals[liOne*3+2]<mpNormals[liTwo*3+2]+lfMergeRange && mpNormals[liOne*3+2]>mpNormals[liTwo*3+2]-lfMergeRange)
                    {
                        return 1;
                    }
                }
            }
            return 0;
}


bool cMesh::UVMatch(uint32 liOne, uint32 liTwo,float lfMergeRange)
{

     if(mpUV[liOne*2]<mpUV[liTwo*2]+lfMergeRange && mpUV[liOne*2]>mpUV[liTwo*2]-lfMergeRange)
            {
                 if(mpUV[liOne*2+1]<mpUV[liTwo*2+1]+lfMergeRange && mpUV[liOne*2+1]>mpUV[liTwo*2+1]-lfMergeRange)
                {

                        return 1;
                }
            }

    return 0;
}

void cMesh::UpdateFaces(uint32 liBase,uint32 liCopy)
{
    for(uint32 liOther=0;liOther<miFaces*3;++liOther)
    {
        if(mpFaces[liOther]==liCopy) mpFaces[liOther]=liBase;
    }
};


c3DVf cMesh::GetTexture3DLocation(c2DVf lfPos)
{
    c2DVf One,Two,Three;
    for(uint32 liFace=0;liFace<miFaces;++liFace)
    {
        One=mpUV[mpFaces[liFace*3]*2];
        Two=mpUV[mpFaces[liFace*3+1]*2];
        Three=mpUV[mpFaces[liFace*3+2]*2];

        c2DVf Centre=(One+Two+Three)/3;

        One-=lfPos;
        Two-=lfPos;
        Three-=lfPos;
        float lfAngle=One.Angle(Two)+One.Angle(Three)+Two.Angle(Three);
        if(lfAngle>2*WT_PI-0.001f && lfAngle<2*WT_PI+0.001f)
        {
            c3DVf Onep=mpVertex[mpFaces[liFace*3]*3];
            c3DVf Twop=mpVertex[mpFaces[liFace*3+1]*3];
            c3DVf Threep=mpVertex[mpFaces[liFace*3+2]*3];

            c3DVf Average=(Onep+Twop+Threep)/3;

            Onep-=Average;
            Twop-=Average;
            Threep-=Average;

            One=mpUV[mpFaces[liFace*3]*2];
            Two=mpUV[mpFaces[liFace*3+1]*2];
            Three=mpUV[mpFaces[liFace*3+2]*2];

            One-=Centre;
            Two-=Centre;
            Three-=Centre;

            lfPos-=Centre;
            float a,b;
            b=a=0.0f;
            if(One.Dot(lfPos)<Three.Dot(lfPos))
            {
                if(Two.Dot(lfPos)<Three.Dot(lfPos))
                {
                    //a*One+b*Two=lfPos;
                   float Denom=One[1]*Two[0]-One[0]*Two[1];
                   if(Denom)
                   {
                       if(One[0])
                       {

                           b=(lfPos[0]*One[1]-lfPos[1]*One[0])/Denom;
                           a=(lfPos[0]-b*Two[0]/One[0]);
                       }
                       else
                       {

                            a=-(lfPos[0]*Two[2]-lfPos[2]*Two[0])/Denom;
                            b=(lfPos[0]-a*One[0]/Two[0]);
                       }
                       Average+=Onep*a+Twop*b;
                       return Average;
                   }
                }
            }
                if(One.Dot(lfPos)<Two.Dot(lfPos))
                {
                    //a*One+c*Three=lfPos;
                 float Denom=One[1]*Three[0]-One[0]*Three[1];
                   if(Denom)
                   {
                       if(One[0])
                       {
                           b=(lfPos[0]*One[1]-lfPos[1]*One[0])/Denom;
                           a=(lfPos[0]-b*Three[0]/One[0]);
                       }
                       else
                       {
                            a=-(lfPos[0]*Three[2]-lfPos[2]*Three[0])/Denom;
                            b=(lfPos[0]-a*One[0]/Three[0]);
                       }
                       Average+=Onep*a+Threep*b;
                       return Average;
                   }

                }

                    //a*Two+b*Three=lfPos;

                    float Denom=Two[1]*Three[0]-Two[0]*Three[1];
                   if(Denom)
                   {
                       if(Two[0])
                       {
                           b=(lfPos[0]*Two[1]-lfPos[1]*Two[0])/Denom;
                           a=(lfPos[0]-b*Three[0]/Two[0]);
                       }
                       else
                       {
                            a=-(lfPos[0]*Three[2]-lfPos[2]*Three[0])/Denom;
                            b=(lfPos[0]-a*Two[0]/Three[0]);
                       }
                       Average+=Twop*a+Threep*b;
                       return Average;
                   }

            }

    }

    return c3DVf(0.0f,0.0f,0.0f);
}


cSeamPair cMesh::UVSeam(FACE_TYPE *Face1,FACE_TYPE *Face2)
{
    cSeamPair lsPair;
    bool lbFound=false;


    c3DVf Vertex1[3];
    c3DVf Vertex2[3];

    c2DVf UV1[3];
    c2DVf UV2[3];

    Vertex1[0]=&mpVertex[Face1[0]*3];
    Vertex1[1]=&mpVertex[Face1[1]*3];
    Vertex1[2]=&mpVertex[Face1[2]*3];

    Vertex2[0]=&mpVertex[Face2[0]*3];
    Vertex2[1]=&mpVertex[Face2[1]*3];
    Vertex2[2]=&mpVertex[Face2[2]*3];

    UV1[0]=&mpUV[Face1[0]*2];
    UV1[1]=&mpUV[Face1[1]*2];
    UV1[2]=&mpUV[Face1[2]*2];

    UV2[0]=&mpUV[Face2[0]*2];
    UV2[1]=&mpUV[Face2[1]*2];
    UV2[2]=&mpUV[Face2[2]*2];

    for(uint8 li1=0;li1<3;++li1)
    {
        for(uint8 li2=0;li2<3;++li2)
        {
            if(Vertex2[li2]==Vertex1[li1])
            {
                if(!(UV2[li2]==UV1[li1]))
                {
                    if(lbFound==false)
                    {
                        lbFound=true;
                        lsPair.Data[0].mvStart=UV1[li1];
                        lsPair.Data[1].mvStart=UV2[li2];
                    }
                    else
                    {
                        lsPair.Data[0].mvEnd=UV1[li1];
                        lsPair.Data[1].mvEnd=UV2[li2];
                        lsPair.Data[0].miTemplate=SEAM_VOID_VALUE;
                        lsPair.Data[1].miTemplate=SEAM_VOID_VALUE;
                        return lsPair;
                    }
                }
            }
        }
    }

    lsPair.Data[0].miTemplate=0;
    lsPair.Data[1].miTemplate=0;

    return lsPair;
};

void cMesh::GenerateSpace(uint16 liVerteces,bool lbNormal,bool lbUV,uint32 liFaces)
{
    if(mpVertex) delete []mpVertex;
    if(mpFaces) delete []mpFaces;
    miVertex=liVerteces;
    uint8 liSize=3;
    if(lbNormal) liSize+=3;
    if(lbUV) liSize+=2;

    mpVertex=new float[liVerteces*liSize];
    liSize=3;
    if(lbNormal)
    {
      mpNormals=&mpVertex[liVerteces*liSize];
      liSize+=3;
    }
    if(lbUV)
    {
        mpUV=&mpVertex[liVerteces*liSize];
        liSize+=2;
    }

    mpFaces=new uint16[liFaces*3];
    miFaces=liFaces;

};

void cMesh::RemoveErrorFaces(float lfRange)
{
    RemoveDuplicateVerteces(lfRange);
    for(uint32 liCount=0;liCount<miFaces*3;liCount+=3)
    {
        if(mpFaces[liCount]==mpFaces[liCount+1] || mpFaces[liCount]==mpFaces[liCount+2] || mpFaces[liCount+1]==mpFaces[liCount+2])
        {
            --miFaces;
            memmove(&mpFaces[liCount],&mpFaces[liCount+3],sizeof(uint16)*(miFaces*3-liCount));
        }
    }
};

cMesh *cMesh::operator=(cMesh *lpOther)
{
    delete []mpFaces;
    delete []mpVertex;
    miFaces=lpOther->miFaces;
    mpFaces=new FACE_TYPE[miFaces*3];

    uint8 miSize=3;
    if(lpOther->mpNormals) miSize+=3;
    if(lpOther->mpUV) miSize+=2;


    miVertex=lpOther->miVertex;
    mpVertex=new float[miSize*miVertex];
    miSize=3;
    if(lpOther->mpNormals) {mpNormals=&mpVertex[miSize*miVertex]; miSize+=3;}
    if(lpOther->mpUV) {mpUV=&mpVertex[miSize*miVertex]; miSize+=2;}

    memcpy(mpFaces,lpOther->mpFaces,sizeof(FACE_TYPE)*miFaces*3);
    memcpy(mpVertex,lpOther->mpVertex,sizeof(float)*miVertex*miSize);

    BufferMesh();

 return this;
};

cMesh::cMesh(cMesh *lpOther)
{
    glGenBuffers(1,&mBuffer1);
	glGenBuffers(1,&mBuffer2);

	miModelCentre[0]=miModelCentre[1]=miModelCentre[2]=0.0f;
	strcpy(mpFileName,lpOther->mpFileName);

    miFaces=lpOther->miFaces;
    mpFaces=new FACE_TYPE[miFaces*3];

    uint8 miSize=3;
    if(lpOther->mpNormals) miSize+=3;
    if(lpOther->mpUV) miSize+=2;

    miVertex=lpOther->miVertex;
    mpVertex=new float[miSize*miVertex];
    miSize=3;
    if(lpOther->mpNormals) {mpNormals=&mpVertex[miSize*miVertex]; miSize+=3;} else {mpNormals=0;}
    if(lpOther->mpUV) {mpUV=&mpVertex[miSize*miVertex]; miSize+=2;} else {mpUV=0;}

    memcpy(mpFaces,lpOther->mpFaces,sizeof(FACE_TYPE)*miFaces*3);
    memcpy(mpVertex,lpOther->mpVertex,sizeof(float)*miVertex*miSize);

    //SetFormat();
    BufferMesh();
    FindSize();

};

void cMesh::AddData(bool lbNormals,bool lbUV)
{
if(lbNormals || lbUV)
{
   uint8 miSize=3;
if(lbNormals) miSize+=3;
 if(lbUV) miSize+=2;

  float *lpTempV=new float[miVertex*miSize];
  memcpy(lpTempV,mpVertex,sizeof(float)*miVertex*3);
  delete []mpVertex;
  mpVertex=lpTempV;
  miSize=3;
  if(lbNormals) {mpNormals=&mpVertex[miVertex*miSize]; miSize+=3; memset(mpNormals,0,sizeof(float)*3*miVertex);} else {mpNormals=0;}
  if(lbUV) {mpUV=&mpVertex[miVertex*miSize]; miSize+=2; memset(mpUV,0,sizeof(float)*2*miVertex);} else {mpUV=0;}


    if(lbNormals) CreateNormalArray();
    if(lbUV) CreateUVSphereMap();
}
else
{
    mpNormals=0;
    mpUV=0;
}

}
