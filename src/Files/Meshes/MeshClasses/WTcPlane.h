#ifndef __WTCPLANE_H__
#define __WTCPLANE_H__

/** \brief A class for handling plane data fir 3D mesh objects.
 * Is composed of 4 floats, X,Y,Z,N. X,Y,Z components of the Normalised normal vector and distance above the origin along the line of the Normal.
 */
class cPlane
{
	float mpData[4];
public:
	///Returns the X component of the Planes Normal.
	float X();
	///Returns the Y component of the Planes Normal.
	float Y();
	///Returns the Z component of the Planes Normal.
	float Z();
	///Return the length of the Planes Normal.
	float Dist();

	///Sets the values for the plane. The Normal vector should be normalised.
	void SetPlane(float x,float y,float z,float dist);
	///Will return a pointer to the float array (Normalvector and length, X,Y,Z,L) which stores the data for this object.
	float *Planes();

	cPlane();
	///Will Display this object to the terminal.
	void Display();

	//Will generate this plane from an array of 3 Verteces.  Will use the plane that they all lie in.
	void GeneratePlane(cVertex *lpVerteces);

	//Will return teh size in Bytes that this object will occupy if written to an IMF file.
	uint32 FileSize();

	//Will do a comparison of this plane and another plane.
	bool operator==(cPlane &lpOther);

	///Will set this object equal to the cPlane lpOther.
	cPlane &operator=(cPlane &lpOther);

	///Will set this plane equal to the Plane of cFullFaceData.
	cFullFaceData &operator=(cFullFaceData &lpOther);

	///Will Normalise the Normal Vector of this object. This ignores the Length set.
	void Normalise();

	///Will return true if all values (X,Y,Z,L) of this cPlane and the cPlane lpOther are within +/- the range lfRange.
	bool Similar(cPlane &lpOther,float lfRange);

	///Will Dot prod<cPolygon>uct the vector cVertex with the Normal Vector of this plane.
	double DotProduct(cVertex &lpOther);

	///Will return true if the 3D Position lpOther is in front of the faceing of this cPlane.
	bool AbovePlane(cVertex &lpOther);

	///Will Return the Distance this Plane sits from the origin. (Can be +ve or -ve)
	float Distance();

	///Returns the distance between the points on the two planes that lie on their normal vectors from the origin.
	double AbsoluteDistance(cPlane &lpOther);

	///Will Output this Object to ofstream in the IMF format.
	void OutputIMFPlane(ofstream &FileStream);
	///Will Load a cPlane from ifstream FileStream in the IMF format.
	void LoadIMFPlane(ifstream &FileStream);

};

/** \brief A resizable array of cPlane Objects.
 * Stores and Handles a list of cPlane objects using cLimitedList.
 */
class cPlaneList : public cLimitedList<cPlane>
{
public:
	cPlaneList(){};
	~cPlaneList(){};
	///Display this object to the Terminal
	void Display();
	///Will Output the list of planes to ofstream FileStream in the IMF format.
	void OutputIMFPlanes(ofstream &FileStream);
	///Will Load the list of planes from ifstream FileStream in the IMF format.
	void LoadIMFPlanes(ifstream &FileStream);
	///Will return the size of this object in Bytes when written in IMF format.
	uint32 FileSize();

	void GeneratePlanes(float *lpVerteces,uint16 *lpFaces,uint32 liFaces);

	void Optimise();
	void Strip();
	void Order();
};



#endif
