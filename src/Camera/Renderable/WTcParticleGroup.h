#ifndef __WTCPARTICLEGROUP_H__
#define __WTCPARTICLEGROUP_H__

#if WT_FULL_VERSION_BAMBOO
/*
 * This will allow Particles to have a local axis (this object and above objects).
 * This will generate the particles and control them. User calls this,
 */
class cParticleGroup : public cParticleHandler
{
protected:
	cParticleSettings Data;

	bool mbRespawn;
	bool mbUseGravity;

public:

	cParticleGroup(uint32 liParticles);
	cParticleGroup(uint32 liParticles,vRenderNode *lpNode);
	cParticleGroup(uint32 liParticles,cCamera *lpCamera);
	cParticleSettings &Settings(){return Data;};
	~cParticleGroup();

	void Settings(cParticleSettings &lpOther){Data=lpOther;}
	virtual void RespawnAll();
	void RespawnOn(){mbRespawn=true;};
	void Fade(){mbRespawn=false;};

	void Refresh();
	void UseGravity(){mbUseGravity=true;};
	void NotUseGravity(){mbUseGravity=false;};

};


#endif

#endif
