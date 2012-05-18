#ifndef __WTCUVSphere_H__
#define __WTCUVSphere_H__

/**
* \brief This class stores the data for a 3D UVSphere.
* This holds the data for a 3D model in a format suitable for rendering. The data is stored in 2 large arrays with the face data stored in the array mpFaces while all the remaining data stored is stored consecutively in mpVertex. mpVertex points to the start of the array while mpNormals and mpUV point to the start of their respective data blocks.
* UVSpheres are generated from another mesh. Icosphere meshes give good rugged UVSpheres, but any mesh can be used to give some control over the final shape of the UVSphere.
*/
class cUVSphere : public cMesh
{

public:

	/**
	* \brief This will generate an UVSphere from the cMesh lpBase.
	* \param lfRandomRange gives the range that verteces can be randomised on the initial model.
	* \param liSubdivisions is the number of times the mesh can be subdivided.
	* \param lpBase is a pointer to a Base Mesh.
	**/
	cUVSphere(uint8 liSubdivisions=16,float lfUVSphereSize=1.0f,bool lbNormals=false,bool UVCoords=false);

	~cUVSphere();

    void Generate(uint8 liSubdivisions,float lfUVSphereSize,bool lbNormals,bool UVCoords);

};
#endif
