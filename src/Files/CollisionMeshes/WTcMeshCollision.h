#ifndef __WTCMESHCOLLISION_H__
#define __WTCMESHCOLLISION_H__

#if WT_FULL_VERSION_BAMBOO

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
#endif

#endif
