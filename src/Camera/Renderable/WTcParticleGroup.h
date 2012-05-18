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
	float mfFadeTime;

public:

	cParticleGroup(uint32 liParticles);
	cParticleGroup(uint32 liParticles,vRenderNode *lpNode);
	cParticleGroup(uint32 liParticles,cCamera *lpCamera);
	cParticleSettings &Settings();
	~cParticleGroup();

	void Settings(cParticleSettings &lpOther);
	virtual void RespawnAll();
	void RespawnOn();
	void Fade(float lfFadeTime);

	void Refresh();
	void UseGravity();
	void NotUseGravity();

};

class cParticleSource : public cFrameUpdateType
{
    cParticleHandler *mpHandler;
    cParticleSettings Data;
    float mfDuration;
    float mfRate;
    float mfProduction;
    vRenderNode *mpNode;
    c3DVf mfOffset;

public:
    cParticleSource(float lfDuration,float lfRate,cParticleSettings& lpSettings,cParticleHandler *lpHandler=_CAMERA->ParticleHandler(),vRenderNode *lpNode=0,c3DVf lfOffSet=c3DVf(0.0f,0.0f,0.0f));
	cParticleSettings &Settings();
	~cParticleSource();

	void Settings(cParticleSettings &lpOther);
	void RenderNode(vRenderNode *lpNode);

	void OffSet(float *lpOffSet);

	void Duration(float lfDuration);
	void Rate(float lfRate);

	void FrameUpdate();

	float Duration();
	float Rate();
    void UseGravity();
	void NotUseGravity();

};


#endif

#endif
