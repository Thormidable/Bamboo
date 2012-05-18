#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

void cParticleGroup::Refresh()
{

	if(mbRespawn)
	{
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




cParticleGroup::cParticleGroup(uint32 liParticles)
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



#endif
