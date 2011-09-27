#ifndef __WTCPOLYGON_H__
#define __WTCPOLYGON_H__

/** \brief This class stores Polygon Data for 3D Meshes. A Polygon is a single convex boundaried Face in a single Plane with any number of verteces above 3.
 * cFaces which are sharing an edge and in the same plane can be combined into a single cPolygon. This allows models to be represented with less
 * Planes for the purposes of calculating Collisions. Uses cPlane and cVertex Objects.
 */
class cPolygon
{
	
public:
	cPlane Plane;
	cVertexList Verteces;
	cVertex mlCenter;
	
	cPolygon();

	///Constructor, creates a cPolygon with enough spaces for liSpaces cVertexes.
	cPolygon(uint32 liSpaces);
	
	~cPolygon();
	//Determines the Size this objet will occupy in IMF format.
	uint32 FileSize();

	///Will Return cVertex number liPos.
	cVertex &operator[](uint8 liPos);

	///Will make this equal to another cPolygon object lpOther.
	cPolygon &operator=(cPolygon &lpOther);

	///Will return the cPlane object storing the plane for this object.
	cPlane &PlaneData();

	//Will Initialise this object
	void Init(uint32 liSize);

	//Will Generate a Polygon from a cFullFaceData object lpFace.
	void GeneratePolygon(cFullFaceData &lpFace);

	void GeneratePolygon(cVertex *lpVertex,uint32 liVerteces);

	//Will add the cVertex lpOther to this object
	void AddVertex(cVertex *lpOther);
	//Will Remove Vertex number liPos.
	void RemoveVertex(uint32 liPos);

	///Returns the number of Verteces that are shared with the cFullFaceData object lpOther.
	uint8 SharesVertex(cFullFaceData &lpOther);
	///Returns the number of Verteces that are shared with the cPolygon object lpOther.
	uint32 SharesVertex(cPolygon &lpOther);
	///Returns the true if cVertex lpOther is the same as any vertex in this object.
	bool SharesVertex(cVertex &lpOther);
	///Returns the position (0,1,2) of the Vertex which is NOT shared with this object.
	uint8 NotSharedVertex(cFullFaceData &lpOther);

	//Will Shuffle the Verteces to ensure they are in CW order. is important for determining if a point is within the boundaries of the polygon as well as certain other checks.
	void OrderClockwise();

	///Will return the Area of this object.
	float Area();

	///Will Output this object to the ofstream FileStream in IMF format.
	void OutputIMFPolygon(ofstream &FileStream);

	//Will return the smallest angle from the center between any pair of cVertex objects next to each other in the list of cVertex objects beyond the point liStart.
	uint32 GetSmallestAngle(uint32 liStart);

	///Will return the sum of angles from the point lpPos (Array of 3 float 3D Position, X,Y,Z). if this is 2*pi or very close the point is on the plane and within the boundaries of the cPolygon.
	double GetAngleSum(float *lpPos);

	///Will Calculate the Center point from all the cVertex objects in the List.
	void CalculateCenter();
	///Will return the cVertex storing the Central point of the polygon. This will be on the plane.
	cVertex &Center();
	///Will Load this object in IMF format from the ifstream FileStream.
	void LoadIMFPolygon(ifstream &FileStream);
	///Will Display this object top the screen.
	void Display();
  
};



/** \brief An array of cPolygon Objects.
 * Creates an array of cPolygon objects using the class cLimitedList.
 */

class cPolygonList : public cLimitedList<cPolygon>
{
	
public:
	cPolygonList();
	~cPolygonList();
	
	//Will Generate a List of Polygons from the cFullFaceList lpFaces.
	void GeneratePolygonList(cFullFaceList &lpFaces);
	void GeneratePolygonList(float *lpVerteces,uint16 *lpFaces,uint32 liFaces);
	/// Will Optimise the order of the Polygons for collisions. First it will Combine() objects to reduce the number of planes. It will sort the Verteces into CW order and then Call OrderArea() to optimise for Beam / Ray collisions.
	void OptimiseRays();
	/// Will Optimise the order of the Polygons for collisions. First it will Combine() objects to reduce the number of planes. It will sort the Verteces into CW order and then Call OrderDistance() to optimise for Mesh Collsiions.
	void OptimiseMeshes();
	// Will Order the Polygons in the list into order from furthest from the Origin in.
	void OrderDistance();
	//Will Order the Polygons in the list into order from the Largest area to the smallest area.
	void OrderArea();
	//Will order all the verteces in the cPolygon objects into CW order.
	void OrderVerteces();
	//Will Combine all cPolygon Objects in the list which can be combined.
	void Combine();
	///Will output all the cPolygons in the list to the ofstream FileStream.
	void OutputIMFPolygons(ofstream &FileStream);
	///Will Load a cPolygon list from the ifstream FileStream.
	void LoadIMFPolygons(ifstream &FileStream);
	//Returns the size in Bytes of this object.
	uint32 FileSize();
	///Will Display the list of cPolygons to the terminal.
	void Display();

};


#endif