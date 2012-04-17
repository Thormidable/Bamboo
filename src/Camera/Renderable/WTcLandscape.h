#ifndef __WTCLANDSCAPE_H__
#define __WTCLANDSCAPE_H__

#if WT_FULL_VERSION_BAMBOO

/**
 * \brief A height map based, matrix structured Landscape.
 * Landscape is composed of a matrix of square polygons. The heights
 * of each vertex is produced using the packaging software, and is generated
 * from a bitmap.
*/

class cLandscape : virtual public cRenderObject, public cMaterial
{
 //This is an array of Vertexs, with a single vertex per point (so smoothing Normals are required)
// Pointer to the cmLandscape file which holds the data for this landscape object.
 cmLandscape *mpLandscape;


public:

 // Function to render this object from the cPainter render list.
 void RenderPainter();

	/// Create a landscape object and set its height map and texture. Can also assign the Landscape to a Camera
 	cLandscape(cmLandscape *lpModel,cCamera *lpCamera);
	/// Create a landscape object and set its height map and texture.
	cLandscape(cmLandscape *lpModel=0);
	/// Set the current height map for this landscape object.
	void Landscape(cmLandscape *lpLandscape);
	/// Set the current height map for this landscape object to use.
	void Landscape(string lsLandscape);
	/// Will return the height at Global co-ordinates lfX,lfZ.
	float GetHeight(float lfX,float lfZ);
	/// Will return the height at the Local position lfX,lfZ (relative to landscapes corner)
	float GetHeightLocal(float lfX,float lfZ);
	/// Will return the height of the vertex at liX,liZ. (position is based on number of segments NOT distance)
	float GetVertexHeight(int liX,int liZ);

    float GetSize();
    double GetSizeSq();

};

#endif

#endif
