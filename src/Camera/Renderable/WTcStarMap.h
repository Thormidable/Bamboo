#ifndef __WTCSTARMAP_H__
#define __WTCSTARMAP_H__

class cStarMap;

class cStar
{
	float Position[3];
	float Color[4];
	float Size;
public:

	void SetSize(float lpSize);
	void SetPosition(float *lpPos);

	void SetColor(float *lpRGB);

	friend class cStarMap;
};

/*
 * This will allow Particles to have a local axis (this object and above objects).
 * This will generate the particles and control them. User calls this,
 */
class cStarMap : public cRenderObject
{

GLuint mBuffer1;
GLuint mBuffer2;

	cStar *mpParticles;
	uint32 miParticles;


public:

	cStarMap(uint32 liParticles);
	cStarMap(uint32 liParticles,vRenderNode *lpNode);
	cStarMap(uint32 liParticles,cCamera *lpCamera);
	~cStarMap();
	void Initialise(uint32 liParticles);

	void RenderPainter();

	void Buffer();

	void StarMapMatrices();
};


#endif
