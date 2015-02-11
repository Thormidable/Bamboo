
#include "../../WTBamboo.h"

void cStarMap::UpdateCache()
{
	//printf("This : %p, mpCollisionObject : %p\n",this,mpCollisionObject);
	if(mpCollisionObject)
	{
		mmCache=_MATRIX_STACK->Current();
		StarMapMatrices();
		mmTotalCache=_COMBINED_MATRIX;
        mmTotalCache.Multiply(mmCache);

		mpCollisionObject->PostUpdateCache();
	}
	else
	{
		mmCache=_MATRIX_STACK->Current();
		StarMapMatrices();
		mmTotalCache=_COMBINED_MATRIX;
        mmTotalCache.Multiply(mmCache);


	}

};

void cStarMap::RenderPainter()
{

	SetShaderVariables();

    if(mpLastShader!=mpShader && mpShader)
    {
        mpLastShader=mpShader;
        mpAttributeLinker->ShaderAndAttributeArray(mpShader,mpAttributes);

        mpAttributes->Elements(miParticles);
        mpAttributes->PointData((char*)mpParticles);

        mpAttributes->Buffer();
    }

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    mpAttributeLinker->Write();
    glDrawArrays(GL_POINTS,0,miParticles);

}


void cStarMap::Buffer()
{
//	glGenBuffers(1,&mBuffer1);
//	glGenBuffers(1,&mBuffer2);

};

cStarMap::cStarMap(uint32 liParticles)
{
	mpParticles=0;
	Initialise(liParticles);
};

cStarMap::cStarMap(uint32 liParticles,cCamera *lpCamera) : cRenderObject(lpCamera)
{
	mpParticles=0;
	Initialise(liParticles);
}

cStarMap::cStarMap(uint32 liParticles,vRenderNode* lpNode) : cRenderObject(lpNode)
{
	mpParticles=0;
	Initialise(liParticles);
};

cStarMap::~cStarMap()
{
 delete []mpParticles;
 mpParticles=0;
 miParticles=0;
}

void cStarMap::StarMapMatrices()
{
 mmTotalCache[12]=0.0f;
 mmTotalCache[13]=0.0f;
 mmTotalCache[14]=0.0f;
 //mmTotalCache[15]=1.0f;

 mmCache[12]=_CAMERA->X();
 mmCache[13]=_CAMERA->Y();
 mmCache[14]=_CAMERA->Z();
 //mmCache[15]=1.0f;

}

void cStarMap::Initialise(uint32 liParticles,float lfDist)
{
    mpLastShader=0;
    if(!lfDist) lfDist=mpRenderer->Camera()->Far()*0.9;
	miParticles=liParticles;
	delete []mpParticles;
	mpParticles=new cStar[miParticles];
	uint32 liCount;
	for(liCount=0;liCount<miParticles;++liCount)
	{
		float lfAngle[4];
		lfAngle[0]=RANDOM_NUMBER*2*3.1416;
		lfAngle[1]=RANDOM_NUMBER*2*3.1416;
		lfAngle[2]=sin(lfAngle[0]);
		lfAngle[3]=cos(lfAngle[1]);

		float lfValue[4];
		lfValue[0]=sin(lfAngle[0])*sin(lfAngle[1])*lfDist;
		lfValue[1]=cos(lfAngle[1])*lfDist;
		lfValue[2]=cos(lfAngle[0])*sin(lfAngle[1])*lfDist;

		mpParticles[liCount].SetPosition(lfValue);
		if(RANDOM_NUMBER>0.99)
		{
            mpParticles[liCount].SetSize(RANDOM_NUMBER*150.0f+5.0f);
		}
		else
		{
		    mpParticles[liCount].SetSize(RANDOM_NUMBER*3.0f+3.0f);
		}

		lfValue[0]=0.7+RANDOM_NUMBER*0.3;
		lfValue[1]=0.7+RANDOM_NUMBER*0.3;
		lfValue[2]=0.7+RANDOM_NUMBER*0.3;
		lfValue[3]=1.0;
		mpParticles[liCount].SetColor(lfValue);

	}


	mpAttributes=new cManualInterleavedAttributeArray(3);

//Don't forget that If adding Normal_Array or Texture_Coord_Array to set mbNormalArray and mbUVArray.
	mpAttributes->AddComponent(new cInterleavedVertexArray(3));
	mpAttributes->AddComponent(new cInterleavedFloatArray(4,"Bb_Color"));
	mpAttributes->AddComponent(new cInterleavedFloatArray(1,"Bb_Size"));

	mpAttributes->Elements(0);
	mpAttributes->PointData((char*)mpParticles);

	mpAttributeLinker=new cAttributeLinker(mpAttributes);

	Transparency(1);
}

	void cStar::SetSize(float lpSize)
	{
		Size=lpSize;
	};

	void cStar::SetPosition(float *lpPos)
	{
		memcpy(Position,lpPos,sizeof(float)*3);
	};
	void cStar::SetColor(float *lpRGB)
	{
		memcpy(Color,lpRGB,sizeof(float)*4);
	};



