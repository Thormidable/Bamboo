#ifndef __WTCMOUSECOLLISIONOBJECT_H__
#define __WTCMOUSECOLLISIONOBJECT_H__

#if WT_FULL_VERSION_BAMBOO

/**
 * \brief This Object is the base object for detecting Mouse Selections.
 * This is a singleton created when first used and
 **/
class cMouseCollisionObject : public cCollisionBase
{
    friend class cCompoundCollision;
protected:
    cCamera *mpCamera;
public:

	cMouseCollisionObject(cCamera *lpCamera=_CAMERA);

	void Initialise(cCamera *lpCamera);

	void CalculateVector();
	void CalculateStart();

	~cMouseCollisionObject();

	///The Signal Function to allow cMouseCollisionObject to receive Signals.
	void Signal(SIGNAL liFlags);

	/**
	 * * \brief This will check for a collision between this object and the object lpOther.
	 * \param lpOther is a pointer to the other collision object to check against.
	 * It will check both objects have collisions on.
	 * Then it will do an initial quick check to see if a collision is a possibility.
	 * Finally if required it will do a much more detailed collision check.
	 **/
	bool CheckCollision(cCollisionObject *lpOther);

	/**
	 * * \brief This will check for a collision between this object and the object lpOther.
	 * \param lpOther is a pointer to the other collision object to check against.
	 * \param lpList is a pointer to an existing cCollisionList object. If specified this will add all Collisions to the existing list.
	 * It will check both objects have collisions on.
	 * Then it will do an initial quick check to see if a collision is a possibility.
	 * Finally if required it will do a much more detailed collision check.
	 **/
	cCollisionList *CheckCollisionDetail(cCollisionObject *lpOther,cCollisionList *lpList=0);

	/**
	 * It is used for quickly detecting if two objects MAY be colliding.
	 * This function is will assume all objects are either Spheres or Beams.
	 * This is a highly inaccurate way of colliding objects, but should filter the majority of collisions from the much slower more accurate collision detection performed elsewhere.
	 **/
	bool TouchCollision(cCollisionObject *lpOther);

	bool CheckCollision();
	void CheckCollisionDetail();
	bool TouchCollision();


	/// This will generate a collision list of all objects colliding with this object filtered by type liType.
	cCollisionList *GenerateCollisionList(uint32 liType=0);

	/// This will return the position of the selected object.
	float *GetPos();

    void Stop();

	cMatrix4 &CacheMatrix();

};

#endif

#endif
