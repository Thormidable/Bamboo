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
/**
 * \brief cParticleSource will generate particles at a specified rate for a specified duration with specified properties.
 * The class will generate particles at the specified rate for the specified duration, with the specified properties.
 * This is designed to be a controller for temporary flame trails etc. The particles generated are not owned by this instance, but passed to a cParticleHandler for efficiency.
 * */

class cParticleSource : public cRenderObject
{
    cParticleHandler *mpHandler;
    cParticleSettings Data;
    float mfDuration;
    float mfRate;
    float mfProduction;
    c3DVf mfOffset;

public:
	/** \brief Constructor for cParticleSource.
	 * \param lfDuration is the duration which the source will generate particles in seconds.
	 * \param lfRate is the number of particles the source will generate per second.
	 * \param lpSettings is the settings for the generated particles.
	 * \param lpHandler specifies which cParticleHandler should own the generated particles. This has a default value.
	 * \param lpNode specifies a vRenderNode object for the cParticleSource to follow. This automatically updates the Sources position relative to the Source.
	 * \param lfOffSet is the spatial position of the source relative to the vRenderNode object (in co-ordinates local to the source).
	 *
	 */
    cParticleSource(float lfDuration,float lfRate,cParticleSettings& lpSettings,vRenderNode *lpNode,c3DVf lfOffSet=c3DVf(0.0f,0.0f,0.0f),cParticleHandler *lpHandler=_CAMERA->ParticleHandler());
	cParticleSettings &Settings();

	///Change the cParticleSettings the source will use.
	void Settings(cParticleSettings &lpOther);

	///Change the Offset the Source will use.
	void OffSet(float *lpOffSet);

	///Set the remaining duration of the Source.
	void Duration(float lfDuration);
	///Set the particle generation rate. (Particles per second)
	void Rate(float lfRate);

	void RenderToPainter();
	void RenderPainter(){};

	///Returns the remaining duration of the source.
	float Duration();
	///Returns the current particle Generation rate of the the source (Particles per second)
	float Rate();
    void UseGravity();
	void NotUseGravity();

};


#endif

#endif
