#ifndef __WTCPARTICLESETTINGS_H__
#define __WTCPARTICLESETTINGS_H__

#if WT_FULL_VERSION_BAMBOO

/**
* \brief This class stores settings values for cParticle, cParticleGroup and cParticleSource Objects.
* Stores settings for constructing Particles of various types. Created, empty, each setting field must be filled.
* The base values are the minimum value the particle can have. the variance is randomised and added to the base.
*/


class cParticleSettings
{
public:
    /// Stores Colors. First 4 are base RGBA values. Second 4 are The variance in the RGBA values.
	float RGB[8];
	/**
	* \brief Stores Colors.
        First 3 are a Base vector for the particles values.
        4th is a variance on the speed of the particles.
        if the 5th is true then the particles will use a cone system bound by the angle stored in the 5th value.
        if the 5th is not true then the particles will use a ball system, bound by no angle.
	*/
	float Speed[5];
	/// The first value is the base life duration of the particles in seconds. The second value is the variance in the particles life.
	float Life[2];
    /// The first three form the base vector for the offset of the particles. The last three for the variance in the vector for the particels offset.
	float Position[6];
	///The first value is the base size of the particle. The second value is the variance in the size of the particle.
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
