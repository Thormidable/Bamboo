#ifndef __WTCLANDSCAPE_H__
#define __WTCLANDSCAPE_H__

/**
 * \brief A height map based, matrix structured Landscape.
 * Landscape is composed of a matrix of square polygons. The heights
 * of each vertex is produced using the packaging software, and is generated
 * from a bitmap.
*/

class cLandscape : public cRenderObject, public cMaterial
{
 //This is an array of Vertexs, with a single vertex per point (so smoothing Normals are required)
// Pointer to the vmLandscape file which holds the data for this landscape object.
 vmLandscape *mpLandscape;
// Pointer to the texture which is bound to this landscape object.
 vTexture *mpTexture;

public:

 // Function to render this object to the cPainter render list.
 void RenderToPainter();
 // Function to render this object from the cPainter render list.
 void RenderPainter(uint8 liLevel);
 // Function to render this object to screen.
 void Render();

	
	cLandscape();
	/// Create a landscape object and set its height map and texture.
	cLandscape(vmLandscape *lpModel, vTexture *lpTexture);
	/// Set the texture bound to this landscape object.
	void Texture(vTexture *lpTexture);
	/// Set the current height map for this landscape object.
	void Landscape(vmLandscape *lpLandscape);
	/// Will return the height at Global co-ordinates lfX,lfZ.
	float GetHeight(float lfX,float lfZ); 
	/// Will return the height at the Local position lfX,lfZ (relative to landscapes corner)
	float GetHeightLocal(float lfX,float lfZ);
	/// Will return the height of the vertex at liX,liZ. (position is based on number of segments NOT distance)
	float GetVertexHeight(int liX,int liZ);

};

#endif
