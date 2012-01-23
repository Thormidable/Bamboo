#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

cmLandscapeArray::cmLandscapeArray()
{
 mpRef=0;
 mpVertex=0;
 mpUV=0;

}

cmLandscapeArray::~cmLandscapeArray()
{
 if (mpRef) delete []mpRef;
}


cLandscapeMeshFile::cLandscapeMeshFile(cmLandscapeArray *lpArray) : cmLandscape(lpArray)
{
      strcpy(mpFileName,lpArray->mpRef);
}

cmLandscape::cmLandscape(cmLandscapeArray *lpArray)
{

  mpBufferIDs=0;


	miXSteps=lpArray->miXSteps;
	miZSteps=lpArray->miZSteps;

	mfXSize=lpArray->mfXSize;
	mfZSize=lpArray->mfZSize;

	mfHeightRange=lpArray->mfHeightRange;

	mpVertex=lpArray->mpVertex;
	//delete []lpArray->mpUV;

	PrepareLandscape();
	BufferMesh();

};


void cmLandscape::PrepareLandscape()
{

 mfXSizeI=1/mfXSize;
 mfZSizeI=1/mfZSize;

 mpQuads=0;mpNormals=0;mpUV=0;

float *mpTemp;
mpTemp=new float[VertexDataSize()];

if(mpVertex) {memcpy(mpTemp,mpVertex,sizeof(float)*3*miXSteps*miZSteps); delete []mpVertex; mpVertex=mpTemp;} else {mpVertex=mpTemp; GenerateVerteces();}
mpNormals=mpVertex+3*miXSteps*miZSteps;
mpUV=mpVertex+6*miXSteps*miZSteps;

GenerateNormals();
GenerateUVs();
GenerateFaces();

}


void cmLandscape::BufferMesh()
{

	if (!mpBufferIDs) mpBufferIDs = new GLuint[2];
	glGenBuffersARB(2,mpBufferIDs);

	glBindBufferARB(GL_ARRAY_BUFFER, mpBufferIDs[0]);
	glBufferDataARB(GL_ARRAY_BUFFER, sizeof(float)*VertexDataSize(), mpVertex, GL_STATIC_DRAW);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, mpBufferIDs[1]);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16)*miQuads, mpQuads, GL_STATIC_DRAW);


	glBindBufferARB(GL_ARRAY_BUFFER,0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,0);

}


uint32 cmLandscape::GetNode(uint32 liX,uint32 liZ)
{
 return (liX+liZ*miXSteps);
}

uint32 cmLandscape::miCustomLandscapes=0;


cmLandscape::cmLandscape(uint32 liXSteps,uint32 liZSteps,float lfXSize,float lfZSize)
{
mpBufferIDs=0;

uint32 MAKE_THIS_CONCATENATE_MICUSTOMLANDSCAPES_ONTO_THE_END_OF_STRING;
//strcpy(mpFileName,"CustomLandscapeModel");
++miCustomLandscapes;
mpVertex=0;
mpNormals=0;
mpUV=0;
mpQuads=0;

 miXSteps=liXSteps;
 miZSteps=liZSteps;

 mfXSize=lfXSize;
 mfZSize=lfZSize;

 mfHeightRange=1.0f;

  PrepareLandscape();
 BufferMesh();


}


cmLandscape::cmLandscape(cmLandscape *lpArray)
{
  printf("Here it is Asshole\n");
mpBufferIDs=0;

mpVertex=0;
mpNormals=0;
mpUV=0;

mpQuads=0;

if(lpArray)
{
 miXSteps=lpArray->miXSteps;
 miZSteps=lpArray->miZSteps;

 mfXSize=lpArray->mfXSize;
 mfZSize=lpArray->mfZSize;

 mfHeightRange=lpArray->mfHeightRange;

 mpVertex=new float[miXSteps*miZSteps*3];
 memcpy(mpVertex,lpArray->mpVertex,sizeof(float)*miXSteps*miZSteps*3);

 //mpUV=lpArray->mpUV;
printf("Here\n");
PrepareLandscape();
printf("Here\n");
BufferMesh();
printf("Here\n");
}
else
  trace("ERROR : Null Pointer Handed to Function\n");
}

cmLandscape::~cmLandscape()
{
delete []mpVertex; mpVertex=0;
delete []mpQuads; mpQuads=0;

if (mpBufferIDs)
{
  glDeleteBuffers(2,mpBufferIDs);
  delete []mpBufferIDs;
  mpBufferIDs=0;
}

}

float cmLandscape::GetHeightLocal(float lfX,float lfZ)
{
 float lfHeight;
 int32 liX,liZ;

 liX=static_cast<int32>(lfX*mfXSizeI);
 liZ=static_cast<int32>(lfZ*mfZSizeI);

 if(liX>=0 && liX<(int32)miXSteps && liZ>=0 && liZ<(int32)miZSteps)
 {
	lfX=(lfX-liX*mfXSize)*mfXSizeI;
	lfZ=(lfZ-liZ*mfZSize)*mfZSizeI;

	// Find the Starting Node
	liX =(3*(liX+liZ*miXSteps));

	lfHeight = mpVertex[liX+1]*(1-lfX)*(1-lfZ);
	lfHeight+= mpVertex[liX+4]*lfX*(1-lfZ);
	lfHeight+= mpVertex[liX+3*miXSteps+4]*lfX*lfZ;
	lfHeight+= mpVertex[liX+3*miXSteps+1]*(1-lfX)*lfZ;
	return lfHeight;
 }
 return 0.0f;
}

float cmLandscape::GetVertexHeight(uint32 liX,uint32 liZ)
{
	return mpVertex[GetNode(liX,liZ)*3+1];
}

void cmLandscape::SetHeight(uint32 liX,uint32 liZ,float lfHeight)
{

 mpVertex[GetNode(liX,liZ)*3+1]=lfHeight;

}


void cmLandscape::Randomize(float liHeight,uint8 liSize)
{

 double liSum;
 uint32 liX1;
 uint32 liX,liZ;

 for(liX=0;liX<miXSteps;++liX)
 {
   for(liZ=0;liZ<miZSteps;++liZ)
   {
	   SetHeight(liX,liZ,(double)liHeight*(rand()/((double)RAND_MAX + 1)));
   }
 }


 float BlendYs[miXSteps*miZSteps];
 for(liX1=0;liX1<miXSteps*miZSteps;++liX1)
 {
  liSum=0.0f;
  for(liX=-liSize;liX<=liSize;++liX)
  {
   for(liZ=-liSize;liZ<=liSize;++liZ)
   {
    if(static_cast<int32>(liX+liX1+liZ*miXSteps)>=0) liSum+=mpVertex[3*(liX+liX1+liZ*miXSteps)+1];
   }
  }
  BlendYs[liX1]=liSum;
 }

 liX1=0;
 for(liX=0;liX<miXSteps;++liX)
 {
	 for(liZ=0;liZ<miZSteps;++liZ)
	 {
		 SetHeight(liX,liZ,BlendYs[liX1++]);
	 }
 }
 BufferMesh();
}

void cmLandscape::Randomize(uint32 liLines,float lfHeightRange=0.001)
{
	uint32 liBorder,liTemp;
	uint32 liCount;
	uint32 liSX,liSZ,liEX,liEZ;

	//Flatten Landscape
	for(liSX=1;liSX<Verteces()*3;liSX+=3)
	{
		mpVertex[liSX]=0.0f;
	}

	float liGradient;
	liBorder=2*(miXSteps+miZSteps);

	while(liLines)
	{
		liTemp=RANDOM_NUMBER*liBorder;
			if(liTemp<2*miXSteps)
			{
				if(liTemp<miXSteps)
				{
					liSZ=0;
					liSX=miXSteps;
				}
				else
				{
					liSZ=miZSteps-1;
					liSX=miXSteps-liTemp;
				}
			}
			else
			{
				liTemp-=2*miXSteps;
				if(liTemp<miZSteps)
				{
					liSX=0;
					liSZ=liTemp;
				}
				else
				{
					liSX=miXSteps-1;
					liSZ=miZSteps-liTemp;
				}
			}

		liTemp=RANDOM_NUMBER*liBorder;
			if(liTemp<2*miXSteps)
			{
				if(liTemp<miXSteps)
				{
					liEZ=0;
					liEX=miXSteps;
				}
				else
				{
					liEZ=miZSteps-1;
					liEX=miXSteps-liTemp;
				}
			}
			else
			{
				liTemp-=2*miXSteps;
				if(liTemp<miZSteps)
				{
					liEX=0;
					liEZ=liTemp;
				}
				else
				{
					liEX=miXSteps-1;
					liEZ=miZSteps-liTemp;
				}
			}


			if (liSX-liEX) liGradient=(liSZ-liEZ)/(liSX-liEX);
			else liGradient=0.0f;

			if(static_cast<int32>(liSX-liEX)<0)
			{
				liSX=liEX;
				liSZ=liEZ;
			}

		if(RANDOM_NUMBER>0.5f)
		{
			for(liTemp=0;liTemp<miZSteps;++liTemp)
			{
				for(liCount=0;liCount<miXSteps && liSX<liCount+liTemp*liGradient;++liCount)
				{
					SetHeight(liTemp,liCount,GetVertexHeight(liTemp,liCount)+lfHeightRange);
					//mpVertex[(liCount+liTemp*miXSteps)*3+1]+=lfHeightRange;
				}
			}
		}
		else
		{
			for(liTemp=miZSteps;liTemp>0;--liTemp)
			{
				for(liCount=miXSteps;liCount>0 && liSX>liCount+liTemp*liGradient;--liCount)
				{
					SetHeight(liTemp,liCount,GetVertexHeight(liTemp,liCount)+lfHeightRange);
					//mpVertex[(liCount+liTemp*miXSteps)*3+1]+=lfHeightRange;
				}
			}
		}

		--liLines;
	}
BufferMesh();
}

void cmLandscape::Randomize(float liHeight)
{

 uint32 liX,liZ;
 for(liX=0;liX<miXSteps;++liX)
 {
	 for(liZ=0;liZ<miZSteps;++liZ)
	 {
		 SetHeight(liX,liZ,(double)liHeight*(rand()/((double)RAND_MAX + 1)));
	 }
 }
 BufferMesh();
//for(liSize=1;liSize<3*miXSteps*miZSteps;liSize+=3) {mpVertex[liSize]=(double)liHeight*(rand()/((double)RAND_MAX + 1)); }
}

//This operates Exclusively on a triangulated array
void cmLandscape::CreateNormalArray()
//(uint16 *lpFaces, uint32 liFaces,float *lpVertex,uint32 liVertex)
{
/*
 float *lpNormals;
 lpNormals=new float[liVertex*3];

 uint32 liCount;

 c3DVf v1,v2;

 for(liCount=0;liCount<liFaces*3;liCount+=3)
 {
  v1.x=lpVertex[lpFaces[liCount]*3]-lpVertex[lpFaces[liCount+1]*3];
  v2.x=lpVertex[lpFaces[liCount]*3]-lpVertex[lpFaces[liCount+2]*3];

  v1.y=lpVertex[lpFaces[liCount]*3+1]-lpVertex[lpFaces[liCount+1]*3+1];
  v2.y=lpVertex[lpFaces[liCount]*3+1]-lpVertex[lpFaces[liCount+2]*3+1];

  v1.z=lpVertex[lpFaces[liCount]*3+2]-lpVertex[lpFaces[liCount+1]*3+2];
  v2.z=lpVertex[lpFaces[liCount]*3+2]-lpVertex[lpFaces[liCount+2]*3+2];

  v1=v1*v2;

  lpNormals[lpFaces[liCount+2]*3]=lpNormals[lpFaces[liCount+1]*3]=lpNormals[lpFaces[liCount]*3]=v1.x;
  lpNormals[lpFaces[liCount+2]*3+1]=lpNormals[lpFaces[liCount+1]*3+1]=lpNormals[lpFaces[liCount]*3+1]=v1.y;
  lpNormals[lpFaces[liCount+2]*3+2]=lpNormals[lpFaces[liCount+1]*3+2]=lpNormals[lpFaces[liCount]*3+2]=v1.z;
 }
 return lpNormals;
 */
}


void cmLandscape::RenderMesh()
{

	glBindBufferARB(GL_ARRAY_BUFFER, mpBufferIDs[0]);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, mpBufferIDs[1]);

	glVertexPointer(3,GL_FLOAT,0,0);
	glNormalPointer(GL_FLOAT,0,reinterpret_cast<const GLvoid*>(miXSteps*miZSteps*3*sizeof(float)));
	glTexCoordPointer(2,GL_FLOAT,0,reinterpret_cast<const GLvoid*>(miXSteps*miZSteps*6*sizeof(float)));

	glDrawElements(GL_TRIANGLE_STRIP,miQuads,GL_UNSIGNED_SHORT,0);

}

void cmLandscape::SetHeightRange(float lfRange)
{
  printf("mfHeightRange : %f\n",mfHeightRange);
	float lfPropor=lfRange/mfHeightRange;

	uint32 liLoop,liArrayPos=1;
		for(liLoop=0;liLoop<Verteces();++liLoop)
		{
			mpVertex[liArrayPos]=mpVertex[liArrayPos]*lfPropor;
			liArrayPos+=3;
		}

		mfHeightRange=lfRange;
		BufferMesh();
}

void cmLandscape::SetXStep(float lfStep)
{
	mfXSize=lfStep/mfXSize;

	uint32 liLoop1,liArrayPos=0;
	for(liLoop1=0;liLoop1<Verteces();++liLoop1)
	{
		mpVertex[liArrayPos]=mpVertex[liArrayPos]*mfXSize;
		liArrayPos+=3;
	}

mfXSize=lfStep;
mfXSizeI=1.0f/mfXSize;

 BufferMesh();
}


void cmLandscape::SetZStep(float lfStep)
{
	mfZSize=lfStep/mfZSize;

	uint32 liLoop1,liArrayPos=2;
	for(liLoop1=0;liLoop1<Verteces();++liLoop1)
	{
		mpVertex[liArrayPos]=mpVertex[liArrayPos]*mfZSize;
		liArrayPos+=3;
	}

	mfZSize=lfStep;
	mfZSizeI=1.0f/mfZSize;

	BufferMesh();
}

void cmLandscape::SetXZStep(float lfXStep,float lfZStep)
{
	mfXSize=lfXStep/mfXSize;
	mfZSize=lfZStep/mfZSize;

	uint32 liLoop1,liArrayPos=0;
	for(liLoop1=0;liLoop1<Verteces();++liLoop1)
	{
		mpVertex[liArrayPos]=mpVertex[liArrayPos]*mfXSize;
		mpVertex[liArrayPos+2]=mpVertex[liArrayPos+2]*mfZSize;
		liArrayPos+=3;
	}

	mfXSize=lfXStep;
	mfXSizeI=1.0f/mfXSize;

	mfZSize=lfZStep;
	mfZSizeI=1.0f/mfZSize;

	BufferMesh();

}
/*
void cLandscapeMeshRandom::GenerateUVs()
{
	uint32 liArrayPos=0;
	uint32 liTile=0;
	float lfXRand,lfZRand;
	float lfXRange,lfZRange;
	uint8 liLowX,liHighX,liLowZ,liHighZ;
	liLowX=liHighX=liLowZ=liHighZ=0;
	uint32 liCount;
	uint32 liPos;

	uint32 liLoop1,liLoop2;
	for(liLoop1=0;liLoop1<miZSteps-1;++liLoop1)
	{
		for(liLoop2=0;liLoop2<miXSteps-1;++liLoop2)
		{
			lfXRand=RANDOM_NUMBER*WT_LANDSCAPE_TEXTURE_PERCENTAGE_SHIFT;
			lfZRand=RANDOM_NUMBER*WT_LANDSCAPE_TEXTURE_PERCENTAGE_SHIFT;
			for(liCount=1;liCount<4;liCount++)
			{
				liPos=liTile+liCount*3;
				if(mpVertex[liPos]<mpVertex[liTile+liLowX*3]) liLowX=liCount;
				if(mpVertex[liPos]>mpVertex[liTile+liHighX*3]) liHighX=liCount;
				if(mpVertex[liPos+2]<mpVertex[liTile+liLowZ*3+2]) liLowX=liCount;
				if(mpVertex[liPos+2]>mpVertex[liTile+liHighZ*3+2]) liLowX=liCount;
			}

			lfXRange=1.0f/(mpVertex[liTile+liHighX*3]-mpVertex[liTile+liLowX*3]);
			lfZRange=1.0f/(mpVertex[liTile+liHighZ*3+2]-mpVertex[liTile+liLowZ*3+2]);

				for(liCount=0;liCount<4;++liCount)
				{
					liPos=liTile+liCount*3;

					mpUV[liArrayPos++]=(float) lfXRand+WT_LANDSCAPE_TEXTURE_ACTUAL_SCALE*lfXRange*(mpVertex[liPos]-mpVertex[liTile+liLowX*3]);
					mpUV[liArrayPos++]=(float) lfZRand+WT_LANDSCAPE_TEXTURE_ACTUAL_SCALE*lfZRange*(mpVertex[liPos+2]-mpVertex[liTile+liLowZ*3+2]);
				}

			liTile+=12;
		}
	}
}*/

void cmLandscape::GenerateRandomUVs()
{
	uint32 liArrayPos=0;
	uint32 liTile=0;
	uint32 liLoop1,liLoop2;
	float lfXRange,lfZRange;
	uint8 liLowX,liHighX,liLowZ,liHighZ;
	liLowX=liHighX=liLowZ=liHighZ=0;
	uint32 liCount;
	uint32 liPos;
	for(liLoop1=0;liLoop1<miZSteps;++liLoop1)
	{
		for(liLoop2=0;liLoop2<miXSteps;++liLoop2)
		{

			for(liCount=1;liCount<4;liCount++)
			{
				liPos=liTile+liCount*3;
				if(mpVertex[liPos]<mpVertex[liTile+liLowX*3]) liLowX=liCount;
				if(mpVertex[liPos]>mpVertex[liTile+liHighX*3]) liHighX=liCount;
				if(mpVertex[liPos+2]<mpVertex[liTile+liLowZ*3+2]) liLowX=liCount;
				if(mpVertex[liPos+2]>mpVertex[liTile+liHighZ*3+2]) liLowX=liCount;
			}

			lfXRange=1.0f/(mpVertex[liTile+liHighX*3]-mpVertex[liTile+liLowX*3]);
			lfZRange=1.0f/(mpVertex[liTile+liHighZ*3+2]-mpVertex[liTile+liLowZ*3+2]);

			for(liCount=0;liCount<4;++liCount)
			{

				liPos=liTile+liCount*3;
				mpUV[liArrayPos++]=(float) lfXRange*(mpVertex[liPos]-mpVertex[liTile+liLowX*3]);
				mpUV[liArrayPos++]=(float) lfZRange*(mpVertex[liPos+2]-mpVertex[liTile+liLowZ*3+2]);
			}

			liTile+=12;
		}
	}
}
/*
uint32 cLandscapeMeshIndividual::GetNode(uint32 liX,uint32 liZ)
{
 if(liX) liX=(liX-1)*4+1;
 if(liZ) liZ=(liZ-1)*(miXSteps-1)*4+1;

 return liX+liZ;
}

/// This will set the height of the landscapes vertex numbered liX,liZ in the array.
void cLandscapeMeshIndividual::SetHeight(uint32 liX,uint32 liZ,float lfHeight)
{
 uint32 liNode=GetNode(liX,liZ)*3;

 mpVertex[liNode+1]=lfHeight;

 if(liX && liX<miXSteps-1) mpVertex[liNode+5]=lfHeight;
 if(liX && liZ<miZSteps-1) mpVertex[liNode+4*(miXSteps-1)-1]=lfHeight;
 if(liX && liZ && liZ<miZSteps-1 && liX<miXSteps-1) mpVertex[liNode+4*(miXSteps-1)+2]=lfHeight;
}


float cLandscapeMeshIndividual::GetHeightLocal(float lfX,float lfZ)
{
	float lfHeight;
	int32 liX,liZ;

	liX=static_cast<int32>(lfX*mfXSizeI);
	liZ=static_cast<int32>(lfZ*mfZSizeI);

	if(liX>=0 && liX<(int32)miXSteps && liZ>=0 && liZ<(int32)miZSteps)
	{
		lfX=(lfX-liX*mfXSize)*mfXSizeI;
		lfZ=(lfZ-liZ*mfZSize)*mfZSizeI;


		lfHeight = mpVertex[GetNode(liX,liZ)*3+1]*(1-lfX)*(1-lfZ);
		lfHeight+= mpVertex[GetNode(liX+1,liZ)*3+1]*lfX*(1-lfZ);
		lfHeight+= mpVertex[GetNode(liX+1,liZ+1)*3+1]*lfX*lfZ;
		lfHeight+= mpVertex[GetNode(liX,liZ+1)*3+1]*(1-lfX)*lfZ;
		return lfHeight;
	}
	return 0.0f;
}

void cLandscapeMeshIndividual::ConvertVertexData(float *lpHeight)
{

	uint32 liArrayPos,liLoop1,liLoop2;
	liArrayPos=0;
	uint32 liTile=0;
	for(liLoop1=0;liLoop1<miZSteps-1;++liLoop1) //Z
		{
			for(liLoop2=0;liLoop2<miXSteps-1;++liLoop2) //X
			{
				mpVertex[liArrayPos++]=lpHeight[liTile];
				mpVertex[liArrayPos++]=lpHeight[liTile+1];
				mpVertex[liArrayPos++]=lpHeight[liTile+2];

				mpVertex[liArrayPos++]=lpHeight[liTile+3];
				mpVertex[liArrayPos++]=lpHeight[liTile+4];
				mpVertex[liArrayPos++]=lpHeight[liTile+5];

				mpVertex[liArrayPos++]=lpHeight[liTile+miXSteps*3+3];
				mpVertex[liArrayPos++]=lpHeight[liTile+miXSteps*3+4];
				mpVertex[liArrayPos++]=lpHeight[liTile+miXSteps*3+5];

				mpVertex[liArrayPos++]=lpHeight[liTile+miXSteps*3];
				mpVertex[liArrayPos++]=lpHeight[liTile+miXSteps*3+1];
				mpVertex[liArrayPos++]=lpHeight[liTile+miXSteps*3+2];

				liTile+=3;
			}
		}
}


void cLandscapeMeshIndividual::GenerateVerteces()
{



	uint32 liArrayPos,liLoop1,liLoop2;
	liArrayPos=0;
	uint32 liTile=0;
	for(liLoop1=0;liLoop1<miZSteps-1;++liLoop1) //Z
		{
			for(liLoop2=0;liLoop2<miXSteps-1;++liLoop2) //X
			{
				mpVertex[liArrayPos++]=mfXSize*liLoop2;
				mpVertex[liArrayPos++]=0.0f;
				mpVertex[liArrayPos++]=mfZSize*liLoop1;

				mpVertex[liArrayPos++]=mfXSize*(liLoop2+1);
				mpVertex[liArrayPos++]=0.0f;
				mpVertex[liArrayPos++]=mfZSize*liLoop1;

				mpVertex[liArrayPos++]=mfXSize*(liLoop2+1);
				mpVertex[liArrayPos++]=0.0f;
				mpVertex[liArrayPos++]=mfZSize*(liLoop1+1);

				mpVertex[liArrayPos++]=mfXSize*liLoop2;
				mpVertex[liArrayPos++]=0.0f;
				mpVertex[liArrayPos++]=mfZSize*(liLoop1+1);

				liTile+=3;
			}
		}
}

void cLandscapeMeshIndividual::GenerateNormals()
{
	uint32 liArrayPos=0;
	uint32 liLoop1,liLoop2;
		for(liLoop1=0;liLoop1<miZSteps;++liLoop1) //Z
		{
			for(liLoop2=0;liLoop2<miXSteps;++liLoop2) //X
			{
				mpNormals[liArrayPos++]=0.0f;
				mpNormals[liArrayPos++]=1.0f;
				mpNormals[liArrayPos++]=0.0f;

				mpNormals[liArrayPos++]=0.0f;
				mpNormals[liArrayPos++]=1.0f;
				mpNormals[liArrayPos++]=0.0f;

				mpNormals[liArrayPos++]=0.0f;
				mpNormals[liArrayPos++]=1.0f;
				mpNormals[liArrayPos++]=0.0f;

				mpNormals[liArrayPos++]=0.0f;
				mpNormals[liArrayPos++]=1.0f;
				mpNormals[liArrayPos++]=0.0f;

			}
		}
}

void cLandscapeMeshIndividual::GenerateFaces()
{
	uint32 liLoop1;

	miQuads=4*(miZSteps-1)*(miXSteps-1);

	delete []mpQuads;
	printf("Failure\n");
	mpQuads=new uint16[miQuads];

	for(liLoop1=0;liLoop1<miQuads;liLoop1++)
	{
		mpQuads[liLoop1]=liLoop1;
	}

}
*/


void cmLandscape::GenerateVerteces()
{

	//Find the Verteces Positions
	uint32 liLoop1,liLoop2,liArrayPos;
	liArrayPos=0;

for(liLoop1=0;liLoop1<miZSteps;++liLoop1) //Z
 {
	 for(liLoop2=0;liLoop2<miXSteps;++liLoop2) //X
  {
	  mpVertex[liArrayPos++]=mfXSize*liLoop2;
	  mpVertex[liArrayPos++]=0.0f;
	  mpVertex[liArrayPos++]=mfZSize*liLoop1;

  }
 }

}

void cmLandscape::GenerateNormals()
{
	uint32 liLoop1,liLoop2,liArrayPos;
	liArrayPos=0;

for(liLoop1=0;liLoop1<miZSteps;++liLoop1) //Z
{
	for(liLoop2=0;liLoop2<miXSteps;++liLoop2) //X
	{
		mpNormals[liArrayPos++]=0.0f;
		mpNormals[liArrayPos++]=1.0f;
		mpNormals[liArrayPos++]=0.0f;
	}
}

}

void cmLandscape::GenerateUVs()
{
	uint32 liLoop1,liLoop2,liArrayPos;
	liArrayPos=0;


	float lfXRange,lfZRange;

	lfXRange=1.0f/(miXSteps*mfXSize);
	lfZRange=1.0f/(miZSteps*mfZSize);

for(liLoop1=0;liLoop1<miZSteps;++liLoop1) //Z
{
	for(liLoop2=0;liLoop2<miXSteps;++liLoop2) //X
	{
		mpUV[liArrayPos*2]=mpVertex[liArrayPos*3]*lfXRange;
		mpUV[liArrayPos*2+1]=mpVertex[liArrayPos*3+2]*lfZRange;
		++liArrayPos;
	}
}

}
/*
void cLandscapeMeshIndividual::RenderMesh()
{

	glBindBufferARB(GL_ARRAY_BUFFER, mpBufferIDs[0]);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, mpBufferIDs[1]);

	glVertexPointer(3,GL_FLOAT,0,0);
	glNormalPointer(GL_FLOAT,0,reinterpret_cast<const GLvoid*>(miXSteps*miZSteps*3*sizeof(float)));
	glTexCoordPointer(2,GL_FLOAT,0,reinterpret_cast<const GLvoid*>(miXSteps*miZSteps*6*sizeof(float)));

	//glNormalPointer(GL_FLOAT,0,reinterpret_cast<const GLvoid*>(Verteces()*3*sizeof(float)));
	//glTexCoordPointer(2,GL_FLOAT,0,reinterpret_cast<const GLvoid*>(Verteces()*6*sizeof(float)));

	glDrawElements(GL_QUADS,miQuads,GL_UNSIGNED_SHORT,0);

}
*/

void cmLandscape::GenerateFaces()
{
	miQuads=2*(miZSteps-1)*(miXSteps)+miZSteps-2;

	delete []mpQuads;

	mpQuads=new uint16[miQuads];

	int32 liCount;
	int32 liSeq,liBase,liXVert;
	uint32 liLoop;

	liXVert=miXSteps;
	liSeq=0;
	liBase=0;

	for(liLoop=0;liLoop<miZSteps-1;++liLoop)
	{
		if(liLoop%2)
		{
			for(liCount=0;liCount<liXVert;++liCount)
			{
				mpQuads[liSeq++]=liBase+liCount;
				mpQuads[liSeq++]=liBase+liXVert+liCount;
			}

		}
		else
		{
			for(liCount=liXVert-1;liCount>=0;--liCount)
			{
				mpQuads[liSeq++]=liBase+liCount;
				mpQuads[liSeq++]=liBase+liXVert+liCount;
			}
		}
		if(liLoop<(miZSteps-2))
		{

			mpQuads[liSeq]=mpQuads[liSeq-1];
			++liSeq;
			liBase+=liXVert;
		}


	}

}

cmLandscape *cmLandscape::Duplicate()
{
 return new cmLandscape(this);
}

cmLandscape::cmLandscape(){};

#endif
