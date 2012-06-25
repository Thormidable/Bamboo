#ifndef __WTCICOSPHERE_H__
#define __WTCICOSPHERE_H__

/**
* \brief This class stores the data for a 3D IcoSphere.
* This holds the data for a 3D model in a format suitable for rendering. The data is stored in 2 large arrays with the face data stored in the array mpFaces while all the remaining data stored is stored consecutively in mpVertex. mpVertex points to the start of the array while mpNormals and mpUV point to the start of their respective data blocks.
* IcoSpheres are generated from another mesh. Icosphere meshes give good rugged IcoSpheres, but any mesh can be used to give some control over the final shape of the IcoSphere.
*/
class cIcoSphere : public cMesh
{
    float mfSize;
public:

	/**
	* \brief This will generate an IcoSphere from the cMesh lpBase.
	* \param liSubdivisions is the number of times the mesh can be subdivided.
	* \param lfIcoSphereSize is the size in spatial units of the starting IcoSphere.
	* \param lbNormals is whether the mesh needs Normal vectors.
	* \param lbUV is whether the mesh needs UV Coordinates. UV is formed from two hemi spheres meeting at the waist.
	**/
	cIcoSphere(uint8 liSubdivisions,float lfIcoSphereSize,bool lbNormals=false,bool lbUV=false);
	cIcoSphere(cIcoSphere *lpOther);
	~cIcoSphere();

    void Generate(uint8 liSubdivisions);
	void SubdivideEdges();
	void GenerateIcosphere();
	void PushToSphere();

	void Radius(float  lfNewSize);


};
#endif
