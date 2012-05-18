#ifndef __WTCBEAMCOLLISION_H__
#define __WTCBEAMCOLLISION_H__

#if WT_FULL_VERSION_BAMBOO

class cMouse;

/**
This class is for representing beams. Think energy beams.
The system will assume that the object is a sphere of radius equal to the value set in SetSize(float *lfSize).
The system will project the beam from the centrepoint of the beams current position in the direction of the Z-axis for a distance of mfLength.
This is a fast and perfect (if the beam is a cylinder capped with hemi-spheres) way of colliding straight energy beams.
See vCollisionData for more information.
**/
class cBeamCollision : public cSphereCollision
{
    friend class cMouse;
 //float GVector[3];
protected:
 c3DVf mfRaySize;
 float mfLength;
public:
	cBeamCollision();
	virtual ~cBeamCollision();
	///This will generate a cBeamCollision data set of length lfength and Radius lfRadius.
	void BuildObject(float lfLength,float lfRadius);
	virtual cBeamCollision *Beam();
	virtual cRayCollision *Ray();
	virtual void Update(cMatrix4 &New);
	virtual void PrepForCollision();
	float RayVector(uint8 liPos);
	///Will return a float array with the beams global vector representing the direction it is pointing in. This should be normalised.
	float *RayVector();
	///Will return the length of the beam.

	float Length();
	///Will return the Objects Type
	uint8 Type();

	float Radius();
	void Radius(float lfRadius);
};
#endif

#endif

