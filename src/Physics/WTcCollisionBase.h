#ifndef __WTCCOLLISIONBASE_H__
#define __WTCCOLLISIONBASE_H__

/*
 * This is the generic class for controlling collisions.
 * The specific data for the collisions is stored in vCollisionData and it's inheriting classes (mpObject).
 *
 */

class cBeamMesh;
class cRenderObject;
class vRenderObject;
class cCollisionList;
class vCollisionData;
class cSphereCollision;
class cMeshCollision;
class cRayCollision;
class cBeamCollision;
class cCompoundCollision;

class cCollisionBase : public cSignal
{
protected:
	vCollisionData *mpObject;
	uint8 miType;

	//Is the current object procedurally generated. (IE is it controlled by the FileHandler or not). If it is procedurally generated, cCollisionObject will delete it when a new object is introduced or cCollisionObject is destroyed.
	bool ProceduralObj;

	//Internal Function to initialise object for using a file loaded object.
    void OnFile(vCollisionData *lpPoint);

	//Internal Function to initialise object for using a proicedurally generated object.
	void OnProcedural();
public:
    cCollisionBase();
    ~cCollisionBase();
	///This will return true if this object has been procedurally generated.
	bool Procedural();
	///This will return true if this object has been procedurally generated.
	bool Loaded();

	//This will clear a Procedurally generated object. Used when cCollisionObject is deleted.
	void ClearProcedural();

	/**This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
	This applies to all the functions Sphere(),Box(),Mesh(),Ray(),Compound() and Beam().**/
	cSphereCollision *Sphere();
	#if WT_FULL_VERSION_BAMBOO
        /**This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
        This applies to all the functions Sphere(),Box(),Mesh(),Ray(),Compound() and Beam().**/
        cMeshCollision *Mesh();
        /**This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
        This applies to all the functions Sphere(),Box(),Mesh(),Ray(),Compound() and Beam().
        cRayCollision Objects will also return true to Beam().**/
        cRayCollision *Ray();
        /**This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
        This applies to all the functions Sphere(),Box(),Mesh(),Ray(),Compound() and Beam().**/
        cBeamCollision *Beam();
        /**This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
        This applies to all the functions Sphere(),Box(),Mesh(),Ray(),Compound() and Beam().**/
        cCompoundCollision *Compound();
	#endif
	///This will take a SphereCollision Object loaded from a file, and set this Collision Object to use it.
	void SetType(cSphereCollision *lpSphere);

	#if WT_FULL_VERSION_BAMBOO
        ///This will take a MeshCollision Object loaded from a file, and set this Collision Object to use it.
        void SetType(cMeshCollision *lpMesh);
        ///This will take a BeamCollision Object loaded from a file, and set this Collision Object to use it.
        void SetType(cBeamCollision *lpBeam);
        ///This will take a cCompoundCollision Object loaded from a file and set this Collision Object to use it.
        void SetType(cCompoundCollision *lpCompound);
    #endif

	///This will procedurally generate a Sphere or radius 1.0f;
	virtual cSphereCollision *SetType(float lfSize);

	#if WT_FULL_VERSION_BAMBOO

        ///This will procedurally generate a Beam of Radius lfRadius and Length lfLength.
        cBeamCollision *SetType(float lfLength,float lfRadius);
        ///This will procedureally generate a Box collision object from the array of 6 floats lpBounds. see cGeneratedBoxCollision::BuildObject(float *lpBounds) for more information.
        cMeshCollision *SetType(float *lpBounds);
        ///This will procedurally generate a Box Collision object. This is the same as handing it a float pointer.
        cMeshCollision *SetType(float lfXP,float lfXN,float lfYP,float lfYN,float lfZP,float lfZN);
        ///This will make a Beam object to match a rendered Beam. (Nice and easy eh?)
        cBeamCollision *SetType(cBeamMesh *lpBeam);
        ///This will make a Compound Collision Object.
        cCompoundCollision *SetType();

    #endif


	///This will return a generic pointer to the cCollisionData for this object
	cSphereCollision *GetCollisionData();

	///This will return a pointer to the Collision Data that this object will use to determine if there have been collisions.
	vCollisionData *CollisionData();

	///This is the accurate way of determining the type of these objects.
	uint8 Type();

    ///This is the Signal Function inherited from cSignal.
	void Signal(SIGNAL liFlags);

    ///Will return the squared radius of the Collision Object linked to this (generally this is the Sphere collision size of the object)
    float GetCollisionSize();

	///Internal function for checking for Sphere / Sphere collision between this object and the object lpOther;
	static bool SphereSphere(cSphereCollision* lpFirst, cMatrix4 &lmFirstMatrix,cSphereCollision* lpSecond, cMatrix4 &lmSecondMatrix);

	#if WT_FULL_VERSION_BAMBOO

        ///Internal function for checking for Model / Model collision between this object and the object lpOther;
        static bool ModelModel(cMeshCollision* lpFirst, cMatrix4 &lmFirstMatrix,cMeshCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Ray / Ray collision between this object and the object lpOther;
        static bool RayRay(cBeamCollision* lpFirst, cMatrix4 &lmFirstMatrix,cBeamCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Sphere / Model collision between this object and the object lpOther;
        static bool SphereModel(cSphereCollision* lpFirst, cMatrix4 &lmFirstMatrix,cMeshCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Sphere / Ray collision between this object and the object lpOther;
        static bool SphereRay(cSphereCollision* lpFirst, cMatrix4 &lmFirstMatrix,cBeamCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Ray / Model collision between this object and the object lpOther;
        static bool RayModel(cBeamCollision* lpFirst, cMatrix4 &lmFirstMatrix,cMeshCollision* lpSecond, cMatrix4 &lmSecondMatrix);
    #endif

};

#endif
