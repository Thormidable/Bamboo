#include "../../WTDivWin.h"

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
		printf("miVertex : %lu\n",miVertex);
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
	
	miModelCentre[0]=miModelCentre[1]=miModelCentre[2]=0.0f;
	strcpy(mpFileName,lpMesh->mpRef);

	mpVertex=lpMesh->mpVertex;
	mpUV=lpMesh->mpUV;
	mpNormals=lpMesh->mpNormals;
	mpFaces=lpMesh->mpFaces;

	miFaces=lpMesh->miFaces;
	miVertex=lpMesh->miVertex;
	SetFormat();

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

void cMesh::SetFormat()
{
	miFormat=0;
	if(mpVertex) miFormat=miFormat|WT_MESH_FORMAT_VERTECES;
	if(mpUV) miFormat=miFormat|WT_MESH_FORMAT_UVS;
	if(mpNormals) miFormat=miFormat|WT_MESH_FORMAT_NORMALS;

}

//This operates Exclusively on a triangulated array
void cMesh::CreateNormalArray()
{
//if(mpNormals) delete[]mpNormals;
//	mpNormals=new float[miVertex*3];

	uint32 liCount;

	c3DVf v1,v2;

	for(liCount=0;liCount<miFaces*3;liCount+=3)
	{
		v1.v[0]=mpVertex[mpFaces[liCount]*3]-mpVertex[mpFaces[liCount+1]*3];
		v2.v[0]=mpVertex[mpFaces[liCount]*3]-mpVertex[mpFaces[liCount+2]*3];

		v1.v[1]=mpVertex[mpFaces[liCount]*3+1]-mpVertex[mpFaces[liCount+1]*3+1];
		v2.v[1]=mpVertex[mpFaces[liCount]*3+1]-mpVertex[mpFaces[liCount+2]*3+1];
 
		v1.v[2]=mpVertex[mpFaces[liCount]*3+2]-mpVertex[mpFaces[liCount+1]*3+2];
		v2.v[2]=mpVertex[mpFaces[liCount]*3+2]-mpVertex[mpFaces[liCount+2]*3+2];

		v1=v1*v2;
  
		mpNormals[mpFaces[liCount+2]*3]=mpNormals[mpFaces[liCount+1]*3]=mpNormals[mpFaces[liCount]*3]=v1.v[0];
		mpNormals[mpFaces[liCount+2]*3+1]=mpNormals[mpFaces[liCount+1]*3+1]=mpNormals[mpFaces[liCount]*3+1]=v1.v[1];
		mpNormals[mpFaces[liCount+2]*3+2]=mpNormals[mpFaces[liCount+1]*3+2]=mpNormals[mpFaces[liCount]*3+2]=v1.v[2];
	}
}

void cMesh::BufferMesh()
{
	trace("cMesh::BufferMesh entering")
	//if (!mpBufferIDs) mpBufferIDs= new uint32[2];
	glGenBuffers(1,&mBuffer1);
	glGenBuffers(1,&mBuffer2);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*miVertex*8, mpVertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16)*miFaces*3, mpFaces, GL_STATIC_DRAW);

	trace("cMesh::BufferMesh leaving")
}

void cMesh::RenderMesh()
{
	printf("cMEsh::REnderMesh : Here\n");
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer2);


	glVertexPointer(3,GL_FLOAT,0,0);
	glNormalPointer(GL_FLOAT,0,reinterpret_cast<const GLvoid*>(miVertex*3*sizeof(float)));
	glTexCoordPointer(2,GL_FLOAT,0,reinterpret_cast<const GLvoid*>(miVertex*6*sizeof(float)));
	glDrawElements(GL_TRIANGLES,miFaces*3,GL_UNSIGNED_SHORT,0);

}

float cMesh::GetSize()
{
return mfSize;
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


cMesh::cMesh(){miModelCentre[0]=miModelCentre[1]=miModelCentre[2]=0.0f;mBuffer1=0;mBuffer2=0; mpVertex=0;mpNormals=0;mpUV=0;mpFaces=0;miFaces=0;miVertex=0;};



 /// This will return the number of verteces in the vertex position array mpVertex.
 uint32 cMesh::Vertex(){return miVertex;}
/// This will return the number of faces in the face array mpFaces.
 uint32 cMesh::Faces(){return miFaces;}
 /// This will return a pointer to the vertex position array.
 float *cMesh::VertexData(){return mpVertex;}
/// This will return a pointer to the face array..
uint16 *cMesh::FaceData(){return mpFaces;}
 /// This will return a pointer to the array of vertex normals.
 float *cMesh::NormalData(){return mpNormals;}
 /// This will return a pointer to the array of texture co-ordinates.
 float *cMesh::UVData(){return mpUV;}
 