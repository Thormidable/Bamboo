#ifndef __WTVCOLLISIONDATA_H__
#define __WTVCOLLISIONDATA_H__

class cSphereCollision;
class cBeamCollision;
class cMeshCollision;
class cRayCollision;
class cCompoundCollision;

/// Virtual Class so cCollisionObject can access the Collision data object it needs.
class vCollisionData
{

public:
	vCollisionData(){};
	virtual ~vCollisionData(){};
	///Will Set the Size of the Collision (For the Sphere aspect of collisions.) This should be the radius of the collison Sphere.
	virtual void SetSize(float lfSize)=0;
	/// Will return the Collision Size Value, which is the radius of the Collision Sphere squared.
	virtual float CollisionSize()=0;
	///Will return a pointer if this object contains a sphere collision data object. Otherwise returns 0;
	virtual cSphereCollision *Sphere()=0;
	#if WT_FULL_VERSION_BAMBOO
        ///Will return a pointer if this object contains a Beam collision data object. Otherwise returns 0;
        virtual cBeamCollision *Beam()=0;
        ///Will return a pointer if this object contains a Mesh collision data object. Otherwise returns 0;
        virtual cMeshCollision *Mesh()=0;
        ///Will return a pointer if this object contains a Ray collision data object. Otherwise returns 0;
        virtual cRayCollision *Ray()=0;
        ///Will return a pointer if this object contains a Compound collision data objecty. Otherwise returns 0;
        virtual cCompoundCollision *Compound()=0;
	#endif
	//Will Update the collision Data Object based off the new global position matrix. This is important for rays.
	virtual void Update(cMatrix4 &New)=0;

};

#endif
