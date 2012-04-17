#ifndef __WTCPARTICLE_H__
#define __WTCPARTICLE_H__

#if WT_FULL_VERSION_BAMBOO



class cParticle
/**
	* This Class is fire and Forget Particles. Find Position based on Global matrix as they will not be parented
	* to a RenderNode. Once position is set they will not be affected by changes to the local matrices.
	* These will automatically be grouped and handled by cParticleHandler for efficiency reasons.
	* Their position can be automatically updated by cParticleGroup if the flag is set
**/
{
protected:
	c3DVf Position;
	cRGBA Color;
	float Size;
	c3DVf Speed;
	float Life;
public:
    cParticle();

	///This will set a cParticles Speed.
	void UpdateSpeed(float *lpTemp);
	///This is the function that will update a cParticles Position. if WT_PARTICLE_HANDLER_UPDATE_PARTICLE_POSITIONS is true then cParticleHandler will do this automatically.
	void UpdatePos();

	void UpdateGravity();
	void UpdateGravityAndWind();
	void UpdateWind();

	friend class cParticleHandler;
	friend class cParticleGroup;
	friend class cStarMap;

	void Spawn(cParticleSettings &lpData);

	void SetSize(float lpSize);
	void SetLife(float lpLife);
	void SetSpeed(float *lpSpeed);
	void SetPosition(float *lpPos);

	void SetColor(float *lpRGB);
	void SetColor(cRGB *lpRGB);
	void SetColor(cRGBA *lpRGB);
	void SetColor(cRGB &lpRGB);
	void SetColor(cRGBA &lpRGB);

	cParticle operator=(cParticle *lpOther);
	cParticle operator=(cParticle lpOther);
};

/**
* This call will take all cParticleFree inheriting Particles (Inc cGravityParticle and cWindAndGravityParticle) and will deal with them as a block for efficiency and so the user does not need to track them.
* All coordinates must be converted to global co-ordinates when they are created.
* This will keep the overheads for particles low as they can be handled as a group.
* Particles can still be controlled by the Toplevel class.
* Particles will automatically be updated every frame if WT_PARTICLE_HANDLER_UPDATE_PARTICLE_POSITIONS is true.
* May be issues with time dependancy.
* Essentially this class will work in teh background and handle objects of types cParticle,cGravityParticle,cWindAndGravityParticle.
**/
class cParticleHandler : public cLimitedList<cParticle>, public cRenderObject
{
	friend class cCamera;

protected:
	bool lbRefresh;

	cManualInterleavedAttributeArray *mpAttributes;
	cAttributeLinker *mpAttributeLinker;

	~cParticleHandler();


public:
	cParticleHandler();
	cParticleHandler(uint32 liParticles);
    cParticleHandler(uint32 liParticles,vRenderNode *lpNode);
	cParticleHandler(uint32 liParticles,cCamera *lpCamera);
	cParticleHandler(vRenderNode *lpNode);
	cParticleHandler(cCamera *lpCamera);


	//This will add the specified Particle to this HAndler.
	cParticle *NewParticle();

	//Will remove the specified Particle from this Handler, but not delete.
	void Remove(uint32 liParticle);
	//Will delete the specified Particle from this Handler.
	void Delete(uint32 liParticle);
	//Will delete All Particles from this Handler.
	void DeleteAll();
	virtual void Refresh();
	void ForceRefresh(){lbRefresh=true;};
	void RenderPainter();

	uint32 LivingParticles();

	void InitialiseParticleHandler(uint32 liParticles);

};

#endif

c3DVf ParticleArcSpeeds(c3DVf Vector,float lfSpeedRange, float lfAngleRange);
c3DVf ParticleBallSpeeds(float lfSpeed,float lfSpeedRange);

c3DVf ParticleArcSpeeds(float *lpSpeedData);
c3DVf ParticleBallSpeeds(float *lpSpeedData);

c3DVf ParticleSideVelocity(float *lpSpeedInfo);
c3DVf ParticleSideVelocity(c3DVf lpSpeedInfo,float lfSpeedRange, float lfSideSpeed);

c3DVf GenerateUniformRandomVector();

#endif
