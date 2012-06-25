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
	* \param liSubdivisions is the number of times the mesh can be subdivided.
	* \param lfUVSphereSize is the radius of the sphere generated.
	* \param lbNormals is whether the user desires normals generated for the sphere.
	* \param UVCoords is whether the user desires UV co-ordinates generated for the sphere.
	**/
	cUVSphere(uint8 liSubdivisions=16,float lfUVSphereSize=1.0f,bool lbNormals=false,bool UVCoords=false);
    cUVSphere(cUVSphere *lpOther);
	~cUVSphere();
    void Generate(uint8 liSubdivisions,float lfUVSphereSize);

    void Radius(float lfSize);

};
#endif
