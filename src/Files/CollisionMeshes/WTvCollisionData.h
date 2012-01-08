#ifndef __WTVCOLLISIONDATA_H__
#define __WTVCOLLISIONDATA_H__

class cSphereCollision;
class cBeamCollision;
class cBoxCollision;
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
	///Will return a pointer if this object contains a Beam collision data object. Otherwise returns 0;
	virtual cBeamCollision *Beam()=0;
	///Will return a pointer if this object contains a Mesh collision data object. Otherwise returns 0;
	virtual cMeshCollision *Mesh()=0;
	///Will return a pointer if this object contains a Ray collision data object. Otherwise returns 0;
	virtual cRayCollision *Ray()=0;
	///Will return a pointer if this object contains a Compound collision data objecty. Otherwise returns 0;
	virtual cCompoundCollision *Compound()=0;
	//Will Update the collision Data Object based off the new global position matrix. This is important for rays.
	virtual void Update(cMatrix4 &New)=0;

};
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
    virtual cBeamCollision *Beam();
    virtual cMeshCollision *Mesh();
    virtual cRayCollision *Ray();
    virtual cCompoundCollision *Compound();
    virtual void Update(cMatrix4 &New);
};

/**
This class is for representing beams. Think energy beams.
The system will assume that the object is a sphere of radius equal to the value set in SetSize(float *lfSize).
The system will project the beam from the centrepoint of the beams current position in the direction of the Z-axis for a distance of mfLength.
This is a fast and perfect (if the beam is a cylinder capped with hemi-spheres) way of colliding straight energy beams.
See vCollisionData for more information.
**/

class cBeamCollision : public cSphereCollision
{
 //float GVector[3];
protected:
 float mfRaySize[3];
 float mfLength;
public:
	cBeamCollision();
	virtual ~cBeamCollision();
	///This will generate a cBeamCollision data set of length lfength and Radius lfRadius.
	void BuildObject(float lfLength,float lfRadius);
	virtual cBeamCollision *Beam();
	virtual cRayCollision *Ray();
	virtual void Update(cMatrix4 &New);
	float RayVector(uint8 liPos);
	///Will return a float array with the beams global vector representing the direction it is pointing in. This should be normalised.
	float *RayVector();
	///Will return the length of the beam.
	float Length();
};

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

/**
This is the cCollisionData class for Boxes. Boxes can either be loaded from a file or procedurally generated.
These boxes actually work as simple Collision Meshes with 6 planes and 8 verteces.
Will Rotate as object moves.
**/
class cMeshCollision : public cSphereCollision
{
public:
	cPlaneList mlPlanes;
	cVertexList mlVerteces;
	cPolygonList mlFaces;


public:

	cMeshCollision(){};
	/**This will build a Box collision. Expects an array of 6 float values representing the length of the normal vector for each plane. (-X, +X, -Y, +Y, -Z, +Z).
	* Floats passed to this function which are +ve will produce a plane facing away from 0,0,0 (origin is behind the plane).
	* Floats passed to this function which are -ve will produce a plane facing towards 0,0,0 (origin is in front of the plane). This way boxes can be constructed which do not contain the origin.
	*/
	void BuildObject(float *lpRanges);

	cMeshCollision *Mesh();

	virtual ~cMeshCollision();
	//Returns the number of Verteces in this Mesh Object.
	uint32 Verteces();
	//Returns a pointer to the Vertex data (array of floats in sets of 3 for x,y,z) for this collision mesh object.
	float *Vertex(uint32 liPos);

	//Returns the number of Planes in this Mesh Object.
	uint32 Planes();
	//Returns a pointer to the plane data (array of floats in sets of 4 for  normal vector x,y,z and length of normal vector) for this collision mesh object.
	float *Plane(uint32 liPos);

	//Returns the number of Faces in this Mesh Object.
	uint32 Faces();
	//Returns the cVertexList for plane number liPos of this collision mesh object.
	cVertexList FaceVerteces(uint32 liPos);
	//Returns the cPolygon number liPos of this collision mesh object.
	cPolygon Polygon(uint32 liPos);
	//Plane Data. Float Array for polygon liPos.
	float *FacePlane(uint32 liPos);
	//Will return the sum of angles between the point lpPos and every vertex of cPolygon number liPolygon. If this is 2*pi() (or very close) the point lpPos lies on the plane of the polygon inside the outer boundary.
	double GetAngle(float *lpPos,uint32 liPolygon);

};


/** \brief  Mesh Collision Object with functionality to load a Collision Mesh from a file.
 * This inherits cMeshCollision, so uses that code for defining the Mesh Collision Object.
 *
 */
class cMeshFileCollision : public cMeshCollision, public cFile, public cIMFLoader
{

public:
	cMeshFileCollision();
	///Will Load a Collision Mesh Object from an IMF File.
	void LoadIMF(ifstream &FileStream);
	virtual ~cMeshFileCollision();
};

/**
* \brief This is the storage class for cCompouncCollision objects.
* You will not interact with it directly, but it should be mentioned to explain where
* the cMatrix4 comes from for objects within a cCompoundCollision Object.
**/
class cCompoundCollisionNode : public cCollisionBase
{
protected:
    vCollisionData *mpCollisionData;
    cMatrix4 mmCollisionMatrix;

public:
    ///Constructor.
    cCompoundCollisionNode();
    ///Destructor.
    ~cCompoundCollisionNode();

    friend class cCompoundCollision;
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
    /// this will return the Matrix used by the vCollisionData Object at position liPos.
    cMatrix4 &GetMatrix(uint32 liPos);

    ///For adding a created vCollisionData object. cSphereCollision, cMeshCollision, cBeamCollision etc.
    void AddType(vCollisionData *lpOther);
    /*
	///This will take a SphereCollision Object loaded from a file, and set this Collision Object to use it.
	void AddType(cSphereCollision *lpSphere);
	///This will take a MeshCollision Object loaded from a file, and set this Collision Object to use it.
	void AddType(cMeshCollision *lpMesh);
	///This will take a BeamCollision Object loaded from a file, and set this Collision Object to use it.
	void AddType(cBeamCollision *lpBeam);
    */
	///This will procedurally generate a Sphere or radius 1.0f;
	cSphereCollision *AddType(float lfSize);
	///This will procedurally generate a Beam of Radius lfRadius and Length lfLength.
	cBeamCollision *AddType(float lfLength,float lfRadius);
	///This will procedureally generate a Box collision object from the array of 6 floats lpBounds. see cGeneratedBoxCollision::BuildObject(float *lpBounds) for more information.
	cMeshCollision *AddType(float *lpBounds);
	///This will procedurally generate a Box Collision object. This is the same as handing it a float pointer.
	cMeshCollision *AddType(float lfXP,float lfXN,float lfYP,float lfYN,float lfZP,float lfZN);
	///This will make a Beam object to match a rendered Beam. (Nice and easy eh?)
	cBeamCollision *AddType(cBeamMesh *lpBeam);

};

#endif
