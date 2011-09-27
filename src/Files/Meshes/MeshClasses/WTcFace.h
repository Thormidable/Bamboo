#ifndef __WTCFACE_H__
#define __WTCFACE_H__

/** \brief This class will store data about faces for a 3D Mesh.
 * This can be used for Models, Collision Meshes or any other object using 3D Faces. Includes code for loading and saving the object types to and from IMF Files. Uses cVertex and cPlane to store the data.
 */
class cFace
{
	
public:
	cVertex Verteces[3];
	cPlane Plane;
	// = Operator.
	cFace &operator=(cFace &lpOther);
	//Returns the Size in bytes that this object will use if written to an IMF file.
	uint32 FileSize();
	// Will Output this face to the ofstream FileStream using the IMF format.
	void OutputIMFFace(ofstream &FileStream);
	// Will read a face from the ifstream FileStream using the IMF format.
	void LoadIMFFace(ifstream &FileStream);
};

#endif