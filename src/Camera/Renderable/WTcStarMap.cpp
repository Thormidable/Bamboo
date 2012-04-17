#include "../../WTBamboo.h"

void cStarMap::RenderPainter()
{
	StarMapMatrices();
	SetShaderVariables();
	 uint32 liCount;

	 glPointSize(1.0f);
	 glBegin(GL_POINTS);
	 for(liCount=0;liCount<miParticles;++liCount)
	 {
			glColor4fv(mpParticles[liCount].Color);
			glVertex3fv(mpParticles[liCount].Position);
	 }
	 glEnd();

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

 mmCache[12]=-_CAMERA->X();
 mmCache[13]=-_CAMERA->Y();
 mmCache[14]=-_CAMERA->Z();

}

void cStarMap::Initialise(uint32 liParticles,float lfDist)
{
    //if(!lfDist) lfDist=mpRenderer->Camera()->Far()-mpRenderer->Camera()->Near()*3;
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
		lfValue[0]=sin(lfAngle[0])*lfDist+sin(lfAngle[1])*lfDist;
		lfValue[1]=ZEROED_RANDOM_NUMBER*2*cos(lfAngle[1])*lfDist;
		lfValue[2]=cos(lfAngle[0])*lfDist+sin(lfAngle[1])*lfDist;

		mpParticles[liCount].SetPosition(lfValue);
		mpParticles[liCount].SetSize(RANDOM_NUMBER*10.0f);
		lfValue[0]=0.85+RANDOM_NUMBER*0.15;
		lfValue[1]=0.85+RANDOM_NUMBER*0.15;
		lfValue[2]=0.85+RANDOM_NUMBER*0.15;
		lfValue[3]=0.3+RANDOM_NUMBER*0.5;
		mpParticles[liCount].SetColor(lfValue);
	}
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



