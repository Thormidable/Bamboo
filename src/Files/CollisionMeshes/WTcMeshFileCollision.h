#ifndef __WTCMESHFILECOLLISION_H__
#define __WTCMESHFILECOLLISION_H__

#if WT_FULL_VERSION_BAMBOO

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

#endif

#endif
