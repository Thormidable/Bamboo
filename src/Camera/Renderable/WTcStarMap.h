#ifndef __WTCSTARMAP_H__
#define __WTCSTARMAP_H__

#if WT_FULL_VERSION_BAMBOO


/*
 * This will allow Particles to have a local axis (this object and above objects).
 * This will generate the particles and control them. User calls this,
 */
class cStarMap : public cParticleGroup
{

public:

	cStarMap(uint32 liParticles);
	cStarMap(uint32 liParticles,vRenderNode *lpNode);
	cStarMap(uint32 liParticles,cCamera *lpCamera);

	void RenderPainter();

	void RespawnAll();
	void Refresh();
};


#endif

#endif
