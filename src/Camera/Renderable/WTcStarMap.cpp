#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO


void cStarMap::RenderPainter()
{

	SetShaderVariables();
	 uint32 liCount;

	 glBegin(GL_POINTS);
	 for(liCount=0;liCount<miParticles;++liCount)
	 {
			glColor4fv(mpParticles[liCount]->Color.Color());
			glVertex3f(mpParticles[liCount]->Position[0]-_CAMERA->X(),mpParticles[liCount]->Position[1]-_CAMERA->Y(),mpParticles[liCount]->Position[2]-_CAMERA->Z());
			//glVertex3f(mpParticles[liCount]->Position[0],mpParticles[liCount]->Position[1],mpParticles[liCount]->Position[2]);
	 }
	 glEnd();

}

cStarMap::cStarMap(uint32 liParticles) : cParticleGroup(liParticles)
{
	RespawnAll();
};

cStarMap::cStarMap(uint32 liParticles,cCamera *lpCamera) : cParticleGroup(liParticles,lpCamera)
{
	RespawnAll();
}

cStarMap::cStarMap(uint32 liParticles,vRenderNode* lpNode) : cParticleGroup(liParticles,lpNode)
{
	RespawnAll();
};

void cStarMap::RespawnAll()
{
	uint32 liCount;
	for(liCount=0;liCount<miSpaces;++liCount)
	{
		float lfValue[4];
		if(!mpParticles[liCount]) mpParticles[liCount]=new cParticleForGroup;

		float lfAngle[4];
		lfAngle[0]=RANDOM_NUMBER*2*3.1416;
		lfAngle[1]=RANDOM_NUMBER*2*3.1416;
		lfAngle[2]=sin(lfAngle[0]);
		lfAngle[3]=cos(lfAngle[1]);

		lfValue[0]=sin(lfAngle[0])*100.0f+sin(lfAngle[1])*100.0f;
		lfValue[1]=ZEROED_RANDOM_NUMBER*2*cos(lfAngle[1])*100.0f;
		lfValue[2]=cos(lfAngle[0])*100.0f+sin(lfAngle[1])*100.0f;

		mpParticles[liCount]->SetPosition(lfValue);
		mpParticles[liCount]->SetFade(0.0f);
		memset(lfValue,0,sizeof(float)*4);
		mpParticles[liCount]->SetSpeed(lfValue);
		mpParticles[liCount]->SetSize(RANDOM_NUMBER*20.0f);
		lfValue[0]=0.85+RANDOM_NUMBER*0.15;
		lfValue[1]=0.85+RANDOM_NUMBER*0.15;
		lfValue[2]=0.85+RANDOM_NUMBER*0.15;
		lfValue[3]=0.3+RANDOM_NUMBER*0.5;
		mpParticles[liCount]->SetColor(lfValue);
	}
	miParticles=miSpaces;
};


void cStarMap::Refresh()
{

};





#endif
