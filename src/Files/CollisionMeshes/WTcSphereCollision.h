#ifndef __WTCSPHERECOLLISION_H__
#define __WTCSPHERECOLLISION_H__

/**
This is the class for storing the data for Sphere collisions.
All vCollisionData inherits cSphereCollision. This is because everyobject will attempt a sphere collision before refining the collisions to the appropriate type (for speed).
See vCollisionData for more information.
**/
class cSphereCollision : public vCollisionData
{
protected:
 float mfSize;
public:
    /// Initialisation of the cSphereCollision Object. Will initialise the size of the collision to 0.
    cSphereCollision();
    virtual ~cSphereCollision();
    ///Will Set the Size of the Collision (For the Sphere aspect of collisions.) This should be the radius of the collison Sphere.
    void SetSize(float lfSize);
    /// Will return the Collision Size Value, which is the radius of the Collision Sphere squared.
    float CollisionSize();
    cSphereCollision *Sphere();
    #if WT_FULL_VERSION_BAMBOO
        virtual cBeamCollision *Beam();
        virtual cMeshCollision *Mesh();
        virtual cRayCollision *Ray();
        virtual cCompoundCollision *Compound();
    #endif
    virtual void Update(cMatrix4 &New);

    uint8 Type();

    ///Will return the Objects Type
};

#endif
