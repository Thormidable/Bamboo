#ifndef __WTCRAYCOLLISION_H__
#define __WTCRAYCOLLISION_H__

#if WT_FULL_VERSION_BAMBOO

/**
This class is for representing objects moving very fast.
The system will assume that the object is a sphere of radius equal to the value set in SetSize(float *lfSize).
It will move the object in a straight line from it's previous position to the position it is in at the start of this frame.
This is a fast and perfect (after the assumption that the object is a sphere) way of colliding fast moving objects.
Best used for projectiles. Note: Drastic camera manipulations can interfere with this class.
*/
class cRayCollision : public cBeamCollision
{
 float GLastPos[3];
 bool lbCreated;
public:
 //Constructor
 cRayCollision();
 virtual ~cRayCollision();
 cRayCollision *Ray();
 void Update(cMatrix4 &New);
 //A Ray object cannot collide on the frame it was created (as it has moved nowhere). This controls avoiding collisions until the 2nd frame.
 bool CreatedThisFrame();

};
#endif

#endif
