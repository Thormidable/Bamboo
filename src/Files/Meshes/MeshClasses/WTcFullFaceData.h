#ifndef __WTCFULLFACEDATA_H__
#define __WTCFULLFACEDATA_H__

/* \brief This class is a cFace with expanded Functionality.
 * Allows the user to check information about the face. See list of functions for information.
 */
class cFullFaceData : public cFace
{

public:


	cFullFaceData();
	//Will return thje size in bytes this face will occupy if written to a file in IMF format.
	uint32 FileSize();

	//Will Fill the data for this Object from a array of floats representing vertex coordinates (3 floats to a vertex) and an array of 3 uint16s indicating which verteces to use.
	void Fill(float *lpVertex,uint16 *mpFace);

	//Will return 1 if the cPlane lpOther is in the same plane as this object.
	bool SamePlane(cPlane &lpOther);
	// = operator
	cFullFaceData &operator=(cFullFaceData &lpOther);

	//Will return one if this Face is concave with the first connected cFullFace it is touching.
	bool IsConcave(cFullFaceList &lpOther);
	//Will return 1 if this Face is concave (and shares an edge) with the cFace lpOther.
	bool IsConcave(cFace lpOther);

	//Will return the number of the Vertex owned by lpOther which is not shared by this face (0,1,2). If all faces are shared, will return 3. If no faces are shared will return 2.
	uint8 NotSharedVertex(cFace &lpOther);
	//Will return the number of verteces that this object shares with the array of 3 cVertex object pointed to by lpOther (0,1,2,3).
	uint8 SharesVertex(cVertex *lpOther);
	//Will output this object to the ofstream FileStream in the IMF format.
	void OutputIMFFullFace(ofstream &FileStream);
	//Will load the cFullFaceData object from the ifstream FileStream in the IMF format.
	void LoadIMFFullFace(ifstream &FileStream);
	//Will output this object to the terminal.
	void Display();

};

/* \brief A dynamic linked list of cFullFaceData.
 * As described. Can load object to and from IMFs.
 */
class cFullFaceList : public cLimitedList<cFullFaceData>
{
public:
	cFullFaceList();
	~cFullFaceList();
	void OutputIMFFullFaces(ofstream &FileStream);

	void LoadIMFFullFaces(ifstream &FileStream);

	uint32 FileSize();

	void Display();
	//Will Normalise all Normals of the cFullFaceData objects in the list.
	void Normalise();
};


#endif