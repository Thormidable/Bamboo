#ifndef __WTCCOLLISIONBASE_H__
#define __WTCCOLLISIONBASE_H__

/**
 * \brief Base class for Collision Objects. Inherited by cCollisionObject and cCompoundCollisionNode.
 * This holds functionality and Data for base Collision Objects.
 *
 */

class cBeam;
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
       virtual cMeshCollision *Mesh();
        /**This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
        This applies to all the functions Sphere(),Box(),Mesh(),Ray(),Compound() and Beam().
        cRayCollision Objects will also return true to Beam().**/
       virtual  cRayCollision *Ray();
        /**This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
        This applies to all the functions Sphere(),Box(),Mesh(),Ray(),Compound() and Beam().**/
        virtual cBeamCollision *Beam();
        /**This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
        This applies to all the functions Sphere(),Box(),Mesh(),Ray(),Compound() and Beam().**/
        virtual cCompoundCollision *Compound();
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
	///This will procedurally generate a cSphereCollision for this cCollisionObject.
    cSphereCollision *SetTypeSphere(float lfRadius);

	#if WT_FULL_VERSION_BAMBOO

        ///This will procedurally generate a Beam of Radius lfRadius and Length lfLength.
        cBeamCollision *SetType(float lfLength,float lfRadius);
        ///This will procedurally generate a Beam of Radius lfRadius and Length lfLength.
        cBeamCollision *SetTypeBeam(float lfLength,float lfRadius);
        ///This will procedureally generate a Box collision object from the array of 6 floats lpBounds. see cGeneratedBoxCollision::BuildObject(float *lpBounds) for more information.
        cMeshCollision *SetType(float *lpBounds);
        ///This will procedurally generate a Box Collision object. This is the same as handing it a float pointer.
        cMeshCollision *SetType(float lfXP,float lfXN,float lfYP,float lfYN,float lfZP,float lfZN);
        ///This will make a Beam object to match a rendered Beam. (Nice and easy eh?)
        cBeamCollision *SetType(cBeam *lpBeam);
        ///This will make a Beam object to match a rendered Beam. (Nice and easy eh?)
        cBeamCollision *SetTypeBeam(cBeam *lpBeam);
        ///This will make a Compound Collision Object.
        cCompoundCollision *SetType();


		///This will procedurally generate a cMeshCollision - Box Collision - for this cCollisionObject.
		cMeshCollision *SetTypeBox(float *lfRadius);
		///This will procedurally generate a cMeshCollision - Box Collision - for this cCollisionObject.
		cMeshCollision *SetTypeBox(float lfmX,float lfpX,float lfmY, float lfpY,float lfmZ,float lfpZ);
		///This will use a cMeshFileCollision with the reference lcReference
		void SetTypeMesh(string lcReference);
		///This will use the cMeshFileCollision pointed to by lpMesh
		void SetTypeMesh(cMeshCollision *lpMesh);
		///This will procedurally generate a new cCompoundCollision Object ready to be defined by the user.
		cCompoundCollision *SetTypeCompound();
		///This will use the cCompoundCollision Object pointed to by lpData.
		void SetTypeCompound(cCompoundCollision *lpData);

    #endif

	bool Owns(vCollisionData *lpData);

	///This will return a generic pointer to the cCollisionData for this object
	cSphereCollision *GetCollisionData();

	///This will return a pointer to the Collision Data that this object will use to determine if there have been collisions.
	vCollisionData *CollisionData();

	///This is the accurate way of determining the type of these objects.
	virtual uint8 Type();

    ///This is the Signal Function inherited from cSignal.
	void Signal(SIGNAL liFlags);

    ///Will return the squared radius of the Collision Object linked to this (generally this is the Sphere collision size of the object)
    float GetCollisionSize();

	///Internal function for checking for Sphere / Sphere collision between this object and the object lpOther;
	static bool SphereSphere(cSphereCollision* lpFirst, cMatrix4 &lmFirstMatrix,cSphereCollision* lpSecond, cMatrix4 &lmSecondMatrix);
	///Internal function for checking for Sphere / Sphere collision between this object and the object lpOther;
	static void SphereSphereDetail(cSphereCollision* lpFirst, cMatrix4 &lmFirstMatrix,cSphereCollision* lpSecond, cMatrix4 &lmSecondMatrix);


	#if WT_FULL_VERSION_BAMBOO

        ///Internal function for checking for Model / Model collision between this object and the object lpOther;
        static bool ModelModel(cMeshCollision* lpFirst, cMatrix4 &lmFirstMatrix,cMeshCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        static bool ModelModelProcess(cMeshCollision* lpVerteces, cMatrix4 &lmVertexMatrix,cMeshCollision* lpPlanes, cMatrix4 &lmPlaneMatrix);
        ///Internal function for checking for Ray / Ray collision between this object and the object lpOther;
        static bool RayRay(cBeamCollision* lpFirst, cMatrix4 &lmFirstMatrix,cBeamCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Sphere / Model collision between this object and the object lpOther;
        static bool SphereModel(cSphereCollision* lpFirst, cMatrix4 &lmFirstMatrix,cMeshCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Sphere / Ray collision between this object and the object lpOther;
        static bool SphereRay(cSphereCollision* lpFirst, cMatrix4 &lmFirstMatrix,cBeamCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Ray / Model collision between this object and the object lpOther;
        static bool RayModel(cBeamCollision* lpFirst, cMatrix4 &lmFirstMatrix,cMeshCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Model / Model collision between this object and the object lpOther;
        static void ModelModelDetail(cMeshCollision* lpFirst, cMatrix4 &lmFirstMatrix,cMeshCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        static bool ModelModelDetailProcess(cMeshCollision* lpVerteces, cMatrix4 &lmVertexMatrix,cMeshCollision* lpPlanes, cMatrix4 &lmPlaneMatrix);
        ///Internal function for checking for Ray / Ray collision between this object and the object lpOther;
        static void RayRayDetail(cBeamCollision* lpFirst, cMatrix4 &lmFirstMatrix,cBeamCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Sphere / Model collision between this object and the object lpOther;
        static void SphereModelDetail(cSphereCollision* lpFirst, cMatrix4 &lmFirstMatrix,cMeshCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Sphere / Ray collision between this object and the object lpOther;
        static void SphereRayDetail(cSphereCollision* lpFirst, cMatrix4 &lmFirstMatrix,cBeamCollision* lpSecond, cMatrix4 &lmSecondMatrix);
        ///Internal function for checking for Ray / Model collision between this object and the object lpOther;
        static void RayModelDetail(cBeamCollision* lpFirst, cMatrix4 &lmFirstMatrix,cMeshCollision* lpSecond, cMatrix4 &lmSecondMatrix);

        static bool CompoundCollision(cCompoundCollision* lpCompound,cMatrix4 &lcCompoundCollision, vCollisionData *lpOther,cMatrix4 &lpOtherMatrix);
        static void CompoundCollisionDetail(cCompoundCollision* lpCompound,cMatrix4 &lcCompoundCollision, vCollisionData *lpOther,cMatrix4 &lpOtherMatrix);


		#endif





		virtual cProcess *GetLink(){return 0;};
		virtual vRenderObject *RenderObject(){return 0;};
		virtual cMatrix4 &CacheMatrix()=0;
		virtual uint32 CollisionFilter(){return 0;};
		virtual bool IsDelayed(){return 0;}

		virtual void CheckCollisionDetail(){};
		virtual bool CheckCollision(){return 0;};

};

#endif
