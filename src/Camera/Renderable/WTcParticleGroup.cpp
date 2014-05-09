#include "stdafx.h"
#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

void cParticleGroup::Settings(cParticleSettings &lpOther){Data=lpOther;}
	void cParticleGroup::RespawnOn(){mbRespawn=true;};
	void cParticleGroup::Fade(float lfFadeTime){mbRespawn=false; mfFadeTime=lfFadeTime;};

	void cParticleGroup::UseGravity(){mbUseGravity=true;};
	void cParticleGroup::NotUseGravity(){mbUseGravity=false;};


void cParticleGroup::Refresh()
{

	if(mbRespawn || mfFadeTime>0.0f)
	{
	    if(mfFadeTime>0.0f) mfFadeTime-=0.04f;
		uint32 liCount;
		for(liCount=0;liCount<Items();++liCount)
		{
		    mpList[liCount].Life-=WT_FRAME_TIME;
			if(mpList[liCount].Life<=0.0f) mpList[liCount].Spawn(Data);
			else mpList[liCount].UpdatePos();
		}
	}
	else
	{
	 	uint32 liFound=0;
		uint32 liCount;
		for(liCount=0;liCount<Items();++liCount)
		{
            mpList[liCount].Life-=WT_FRAME_TIME;
			if(mpList[liCount].Life>0.0f)
			{
				mpList[liCount].UpdatePos();
				if(liFound!=liCount) mpList[liFound]=mpList[liCount];
				++liFound;
			}
		}

	 	if(liFound<Items())
	 	{
		  	miItems=liFound;
			if(!Items()) _KILL_THIS();
		}

	}

};




cParticleGroup::cParticleGroup(uint32 liParticles) : cParticleHandler(liParticles)
{
	mbRespawn=0;
	mbUseGravity=0;
};

cParticleGroup::cParticleGroup(uint32 liParticles,cCamera *lpCamera) : cParticleHandler(liParticles,lpCamera)
{
	mbRespawn=0;
	mbUseGravity=0;
}

cParticleGroup::cParticleGroup(uint32 liParticles,vRenderNode* lpNode) : cParticleHandler(liParticles,lpNode)
{
	mbRespawn=0;
	mbUseGravity=0;
};



void cParticleGroup::RespawnAll()
{
	uint32 liCount;
	for(liCount=0;liCount<miSpaces;++liCount)
	{
	    mpList[liCount].Spawn(Data);
	}
    miItems=miSpaces;
};







cParticleGroup::~cParticleGroup()
{

}




cParticleSource::cParticleSource(float lfDuration,float lfRate,cParticleSettings& lpSettings,vRenderNode *lpNode,c3DVf lfOffSet,cParticleHandler *lpHandler) : cRenderObject(lpNode,0)
{
    mfDuration=lfDuration;
    mfRate=1.0f/lfRate;
    mpHandler=lpHandler;
    Data=lpSettings;
    mfOffset=lfOffSet;
	mfProduction=0.0f;
};

cParticleSettings &cParticleSource::Settings(){return Data;};


void cParticleSource::Settings(cParticleSettings &lpOther){Data=lpOther;};
void cParticleSource::Duration(float lfDuration){mfDuration=lfDuration;};
void cParticleSource::Rate(float lfRate){mfRate=1.0f/lfRate;};
void cParticleSource::RenderToPainter()
{
 mfProduction+=0.004f;
 while(mfProduction>mfRate)
 {
     mfProduction-=mfRate;
     cParticle *lpPart=mpHandler->NewParticle();
         memcpy(Data.Position,mpRenderer->mmCache.Position(),sizeof(float)*3);
         Data.Position[0]+=mfOffset[0];
         Data.Position[1]+=mfOffset[1];
         Data.Position[2]+=mfOffset[2];

     lpPart->Spawn(Data);
 }
 mfDuration-=0.004f;
 if(mfDuration<0.0f) _KILL_THIS();
};

float cParticleSource::Duration(){return mfDuration;};
float cParticleSource::Rate(){return 1.0f/mfRate;};

void cParticleSource::OffSet(float *lpOffSet)
{
    mfOffset=lpOffSet;
};

#endif


