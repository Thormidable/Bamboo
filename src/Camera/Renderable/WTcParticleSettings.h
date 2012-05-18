#ifndef __WTCPARTICLESETTINGS_H__
#define __WTCPARTICLESETTINGS_H__

#if WT_FULL_VERSION_BAMBOO

class cParticleSettings
{
public:
	float RGB[8];
	float Speed[5];
	float Life[2];
	float Position[6];
	float Size[2];

	cParticleSettings &operator=(cParticleSettings &lpOther);

	void SetColours(float *lpRGB);
	void SetSizes(float *lpSize);
	void SetLife(float *lpLife);
	void SetSpeeds(float *lpSpeed);
	void SetPositions(float *lpPos);

	static float sfStore[6];

};

#endif

#endif
