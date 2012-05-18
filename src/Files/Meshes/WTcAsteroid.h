#ifndef __WTCASTEROID_H__
#define __WTCASTEROID_H__

/**
* \brief This class stores the data for a 3D ASteroid.
* This holds the data for a 3D model in a format suitable for rendering. The data is stored in 2 large arrays with the face data stored in the array mpFaces while all the remaining data stored is stored consecutively in mpVertex. mpVertex points to the start of the array while mpNormals and mpUV point to the start of their respective data blocks.
* ASteroids are generated from another mesh. Icosphere meshes give good rugged asteroids, but any mesh can be used to give some control over the final shape of the asteroid.
*/
class cAsteroid : public cMesh
{

public:

	/**
	* \brief This will generate an Asteroid from the cMesh lpBase.
	* \param lfRandomRange gives the range that verteces can be randomised on the initial model.
	* \param liSubdivisions is the number of times the mesh can be subdivided.
	* \param lpBase is a pointer to a Base Mesh.
	**/
	cAsteroid(float lfRandomRange, uint8 liSubdivisions,cMesh *lpBase);
		/**
	* \brief This will generate an Asteroid from the cMesh lpBase.
	* \param lfRandomRange gives the range that verteces can be randomised on the initial model.
	* \param liSubdivisions is the number of times the mesh can be subdivided.
	* \param lfAsteroidSize is the size in spatial units of the starting Asteroid.
	**/
	cAsteroid(float lfRandomRange, uint8 liSubdivisions,float lfAsteroidSize);
	~cAsteroid();

    void Generate(float lfRandomRange,uint8 liSubdivisions);
	void RandomiseVerteces(float lfRange);
	//void SubdivideFaces();
	void SubdivideEdges();
	void GenerateIcosphere(float lfSize=1.0f);


};
#endif
