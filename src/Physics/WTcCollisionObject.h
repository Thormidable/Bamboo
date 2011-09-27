#ifndef __WTCCOLLISIONOBJECT_H__
#define __WTCCOLLISIONOBJECT_H__

/*
 * This is the generic class for controlling collisions.
 * The specific data for the collisions is stored in vCollisionData and it's inheriting classes (mpObject).
 * 
 */

class cBeamMesh;
class cRenderObject;
class vRenderObject;

class cCollisionObject : public cSignal
{

	static float CollisionDistance;
	vCollisionData *mpObject;
	uint8 miType;
	
	
	
	///Is the current object procedurally generated. (IE is it controlled by the FileHandler or not). If it is procedurally generated, cCollisionObject will delete it when a new object is introduced or cCollisionObject is destroyed.
	bool ProceduralObj;

	/**
	 * This concise little variable determines whether the object has a previous frame to act from. (IE no old matrix, no real position).
	 * An Object can be enabled by calling 
	 *
	 **/ 
	bool mbCreatedThisFrame;
	///This is the user assigned type of collision for the purposes of filtering, undesired collisions.
	uint32 miID;
	///This is a pointer to the Renderable Object this Collision Object is following.
	vRenderObject *mpFollowing;
	///This is a pointer to the Process which is linked to this CollisionObject.
	vProcess *mpLinked;
	
	///This is a pointer to the list that owns this CollisionObject.
	cLinkedNode<cCollisionObject> *mpOwner;
public:
	cCollisionObject(vRenderObject *lpFollow,vProcess *lpLinked=0,uint32 liFilterType=0);
	cCollisionObject(cBeamMesh *lpFollow,vProcess *lpLinked=0,uint32 liFilterType=0);

	void Initialise(vRenderObject *lpFollow,vProcess *lpLinked,uint32 liFilterType);
	
	~cCollisionObject();

	bool CreatedThisFrame(){return mbCreatedThisFrame;};

	void NotCreatedThisFrame(){mbCreatedThisFrame=false;};
	
	vCollisionData *CollisionData(){return mpObject;};

	void Signal(SIGNAL liFlags);
	
	bool Procedural(){return ProceduralObj;};
	bool Loaded(){return (!ProceduralObj);};
	
	void ClearProcedural();
	
	///This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
	///This applies to all the functions Sphere(),Box(),Mesh(),Ray() and Beam().
	cSphereCollision *Sphere(){return mpObject->Sphere();};
	///This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
	///This applies to all the functions Sphere(),Box(),Mesh(),Ray() and Beam().
	cMeshCollision *Mesh(){return mpObject->Mesh();};
	///This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
	///This applies to all the functions Sphere(),Box(),Mesh(),Ray() and Beam().
	///cRayCollision Objects will also return true to Beam().
	cRayCollision *Ray(){return mpObject->Ray();};
	///This is a dynamic cast on the type of collision object this is. Note ALL cCollisionData objects return true to Sphere.
	///This applies to all the functions Sphere(),Box(),Mesh(),Ray() and Beam().
	cBeamCollision *Beam(){return mpObject->Beam();};
	
	///This will take a SphereCollision Object loaded from a file, and set this Collision Object to use it.
	void SetType(cSphereCollision *lpSphere);
	///This will take a MeshCollision Object loaded from a file, and set this Collision Object to use it.
	void SetType(cMeshCollision *lpMesh);
	///This will take a BeamCollision Object loaded from a file, and set this Collision Object to use it.
	void SetType(cBeamCollision *lpBeam);
	
	void OnFile(vCollisionData *lpPoint);
	void OnProcedural();
	///This will procedurally generate a Sphere or radius 1.0f;
	cSphereCollision *SetType(float lfSize);
	///This will procedurally generate a Beam of Radius lfRadius and Length lfLength.
	cBeamCollision *SetType(float lfLength,float lfRadius);
	///This will procedureally generate a Box collision object from the array of 6 floats lpBounds. see cGeneratedBoxCollision::BuildObject(float *lpBounds) for more information.
	cMeshCollision *SetType(float *lpBounds);
	///This will make a ray object. See cRayCollision::BuildObject(float *lpBounds) for more information. Makes Ray radius to be same as object and ray to follow it's movement.
	cRayCollision *SetType(cRenderObject *lpObj);
	///This will make a Beam object to match a rendered Beam. (Nice and easy eh?)
	cBeamCollision *SetType(cBeamMesh *lpBeam);

	
	cSphereCollision *GetCollisionData()
	{
		if(miType==WT_COLLISION_RADIUS) return Sphere();
		if(miType==WT_COLLISION_MODEL) return Mesh();
		if(miType==WT_COLLISION_RAY) return Ray();
		if(miType==WT_COLLISION_BEAM) return Beam();
		return 0;
	};
	
	///This is the accurate way of determining the type of these objects.
	uint8 Type(){return miType;};

	

	
	/**
	 * * \brief This will check for a collision between this object and the object lpOther.
	 * \param lpOther is a pointer to the other collision object to check against.
	 * It will check both objects have collisions on.
	 * Then it will do an initial quick check to see if a collision is a possibility.
	 * Finally if required it will do a much more detailed collision check.
	 **/
	bool CheckCollision(cCollisionObject *lpOther);
	
	/**
	 * It is used for quickly detecting if two objects MAY be colliding.
	 * This function is will assume all objects are either Spheres or Beams.
	 * This is a highly inaccurate way of colliding objects, but should filter the majority of collisions from the much slower more accurate collision detection performed elsewhere.
	 **/
	bool TouchCollision(cCollisionObject *lpOther);











	/// This is a temporary storage for transfering sizes between objects.
	static float mfStaticSize[3];
	
	///This will return the Objects Cached Matrix mmCache.
	cMatrix4& CacheMatrix(){return mpFollowing->mmCache;};
	
	
	///This will return a pointer the cRenderObject linked to this.
	vRenderObject *RenderObject(){return mpFollowing;};
	



	///This will return the current Collision Filter ID of this object.
	uint32 CollisionFilter(){return miID;};
	///This will set the Collision Filter ID of this object.
	void CollisionFilter(uint32 liID);
	
	/** This Function will control the collision detection between this object and lpOther.
	 * It will check the filter lpCol to cehck that the other object is of a suitable type.
	 * Then will call CheckCollision(cCollisionObject *lpOther)
	 * */
	bool Collision(cCollisionObject *lpOther,uint32 lpCol);
	bool Collision(cCollisionObject *lpOther);

	

	/// This will do a sphere collision between two points. lf1 and lf2 are x*x+y*y+z*z. lfR is (Sum of Radii)*(Sum of Radii).
	bool CompareRanges(float lf1,float lf2,float lfR);
	
	/**
	 * \brief This sets the process that this renderable object will return collision signals to.
	 * \param lpLink Points to the process that this renderable object will return collision signals to.
	 */
	void SetLink(vProcess *lpLink){mpLinked=lpLink;}
	///Returns the process currently linked to this renderable object.
	vProcess *GetLink(){return mpLinked;}
	/// This will generate a collision list of all objects colliding with this object filtered by type liType.
	void GenerateCollisionList(uint32 liType=0);
	
	/// This will return the position of the selected object.
	float *GetPos();
	
	
	/// This will remove the cCollisionObject from it's Spatial Slots before its position is updated.
	void PreUpdateCache();
	/// This will Add the cCollisionObject to the relevant Spatial Slots after it has found it's new position.
	void PostUpdateCache();
	

	bool SphereSphere(cCollisionObject *lpOther);
	bool ModelModel(cCollisionObject *lpOther);
	bool RayRay(cCollisionObject *lpOther);
	bool SphereModel(cCollisionObject *lpOther);
	bool SphereRay(cCollisionObject *lpOther);
	bool RayModel(cCollisionObject *lpOther);
	
	float GetCollisionSize();
};


#endif
