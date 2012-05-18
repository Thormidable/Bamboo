#ifndef __WTCCOMPOUNDCOLLISION_H__
#define __WTCCOMPOUNDCOLLISION_H__

#if WT_FULL_VERSION_BAMBOO

class cCollisionObject;
/**
* \brief This is the storage class for cCompouncCollision objects.
* You will not interact with it directly, but it should be mentioned to explain where
* the cMatrix4 comes from for objects within a cCompoundCollision Object.
**/
class cCompoundCollisionNode : public cCollisionBase
{
public:
    ///Constructor.
    cCompoundCollisionNode();
    ///Destructor.
    ~cCompoundCollisionNode();

    uint8 Type();
    friend class cCompoundCollision;

    cMatrix4 &CacheMatrix();
};

class cCompoundCollisionNodeMobile : public cCompoundCollisionNode
{
protected:
    cMatrix4 mmCollisionMatrix;
    cMatrix4 mmTotalMatrix;
public:
    cCompoundCollisionNodeMobile();
    void UpdateMatrices(cMatrix4 &lcBase);

    cMatrix4 &CacheMatrix();
};

/**
* \brief The cCompoundCollision object is a type of vCollisionData for combining multiple Collision Objects into a single object.
* This allows the user to construct a collision object out of several simpler objects.
* This makes it possible to produce 'concave' faces by using several objects with exclusively convex faces.
* It is a cLimitedPointerList so can have the size of the array adjusted to store as many objects as are required.
* If there is a collision with any object within this compound Object then the cCompoundCollision object has collided.
* Negative Collision Objects will be added at a future date.
* Each Object within the cCompoundCollision Object has a cMatrix4 to allow it to be positioned and rotated as required.
* This class should either be started with a list size - cCompoundCollision(uint32 liSize) - or call the function Init(uint32 liSize) before it is used.
**/
class cCompoundCollision : public cSphereCollision, public cLimitedPointerList<cCompoundCollisionNode>
{

public:
    ///Constructor creting a 0 length list.
    cCompoundCollision();
    ///Constructor creating a list of length liSize
    cCompoundCollision(uint32 liSize);
    ///Destructor
    virtual ~cCompoundCollision();
    //Allows to determine type and get a cheap cast.
    cCompoundCollision *Compound();
    //Will Update the Matrix and should also update size
    void Update(cMatrix4 &New);


    /// [] operator to access the vCollisionData Objects within this cCompoundCollision Object.
    vCollisionData *operator[](uint32 liPos);
    // this will return the Matrix used by the vCollisionData Object at position liPos.
    //cMatrix4 &GetMatrix(uint32 liPos);

    ///For adding a created vCollisionData object. cSphereCollision, cMeshCollision, cBeamCollision etc.
    void AddType(vCollisionData *lpOther);
	///This will procedurally generate a Sphere or radius 1.0f;
	cSphereCollision *AddType(float lfSize);
	///This will procedurally generate a Beam of Radius lfRadius and Length lfLength.
	cBeamCollision *AddType(float lfLength,float lfRadius);
	///This will procedureally generate a Box collision object from the array of 6 floats lpBounds. see cGeneratedBoxCollision::BuildObject(float *lpBounds) for more information.
	cMeshCollision *AddType(float *lpBounds);
	///This will procedurally generate a Box Collision object. This is the same as handing it a float pointer.
	cMeshCollision *AddType(float lfXP,float lfXN,float lfYP,float lfYN,float lfZP,float lfZN);
	///This will make a Beam object to match a rendered Beam. (Nice and easy eh?)
	cBeamCollision *AddType(cBeam *lpBeam);

	uint8 GetType(uint32 liPos);
	vCollisionData *GetObject(uint32 liPos);

	bool Owns(vCollisionData *lpData);

	///Will return the Objects Type
	uint8 Type();

};

#endif
#endif

