#ifndef __WTCPARTICLE_H__
#define __WTCPARTICLE_H__


class cParticle : public cParticleForGroup,  public cSignal
/**
	* This Class is fire and Forget Particles. Find Position based on Global matrix as they will not be parented
	* to a RenderNode. Once position is set they will not be affected by changes to the local matrices.
	* These will automatically be grouped and handled by cParticleHandler for efficiency reasons.
	* Their position can be automatically updated by cParticleGroup if the flag is set
**/
{

public:
	cParticle();
	~cParticle();
	
	///This will set a cParticles Speed. 
	void UpdateSpeed(float *lpTemp);
	///This is the function that will update a cParticles Position. if WT_PARTICLE_HANDLER_UPDATE_PARTICLE_POSITIONS is true then cParticleHandler will do this automatically.
	virtual void UpdatePos();

	void AdditionalKillFunctionality();
	void AdditionalSleepFunctionality();
	void AdditionalWakeFunctionality();
};

class cGravityParticle : public cParticleForGroup
/** \brief cParticles which are affected by Gravity.
 * These Particles have the code to be affected by the variables _GRAVITY_X,_GRAVITY_Y and _GRAVITY_Z. UpdatePos() will account use the current Gravity settings to calculate the speed and position.
 */
{

public:
	void UpdatePos();
	friend class cParticleHandler;
};


class cWindAndGravityParticle : public cParticleForGroup
/** \brief cGravityParticles which are also affected by Wind.
 * These Particles have the code to be affected by the variables _WIND_X,_WIND_Y and _WIND_Z. UpdatePos() will account use the current Wind and Gravity settings to calculate the speed and position of each particle.
*/
{
	
public:
	void UpdatePos();
	friend class cParticleHandler;
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
class cParticleHandler : public cRenderObject
{

	uint32 FINISH_THIS;
	uint32 miParticles;
	cParticle **mpParticles;
	uint32 miMaxParticles;
	static cParticleHandler *spthis;
	bool lbRefresh;
	cParticleHandler();
	~cParticleHandler();
public:
	///Returns a pointer to the current cParticleHandler.
	static cParticleHandler *Instance();
	//This will resize the number of particles the cParticleHandler can process. The system is resized as required.
	void Resize(uint32 liSize);
	//This will add the specified Particle to this HAndler.
	void Add(cParticle *lpPart);
	//Will remove the specified Particle from this Handler, but not delete.
	void Remove(cParticle *lpPart);
	//Will remove the specified Particle from this Handler, but not delete.
	void Remove(uint32 liParticle);
	//Will delete the specified Particle from this Handler.
	void Delete(cParticle *lpPart);
	//Will delete All Particles from this Handler.
	void DeleteAll();
	void Refresh();
	void ForceRefresh(){lbRefresh=true;};
	void RenderToPainter();
	void RenderPainter(uint8 liLevel);
	void RenderPainter();
	void Render();
};
	
#endif
	