#ifndef __WTCIMAGE_H__
#define __WTCIMAGE_H__

#if WT_FULL_VERSION_BAMBOO

class cImage3D;


/**
* \brief A 2D renderable object.
* \param lpTexture pointer to the texture to bind to this 2D object
* This is actually a 3D polygon, which has a texture bound to it.
* it can be used as an OpenGL accelerated sprite.
*/
class cImage : public cRenderObject
{
	friend class cImage3D;

protected:
 // This is the size of the sprite on the screen.
 float mfWidth;

 float mfHeight;
 // This is the vertex array for a single polygon.
 static float mpVertex[12];
 // This is the Face array for a single polygon.
 static uint16 mpFaces[6];
 // This is the UV array for a single polygon.
 static float mpTextCoords[8];
 // This is the Normals array for a single polygon
 static float mpNormals[12];
 // This boolean determines whether the arrays need to be generated.
 static bool mbFirst;

 	// Will fill the arrays for forming the polygon.
       void InitialiseArrays();
       	// Updates arrays to make the image of size mfSize.
       void ResizeArrays();

	   cImage(vRenderNode *lpRenderNode);
public:
 	/// Constructor for cImage. Will Create an Empty cImage Object.
       cImage();
	   cImage(cCamera *lpCamera);
	// This function will set this object to being a 2D object and initialise the arrays.
       virtual void SetUp();
	//Destructor for cImage.
       ~cImage();


	// Function to render this object from the cPainter render list.
       void RenderPainter();


	/// Sets the size of the image on screen. Makes the width be lfSize pixels and makes the height to make it appear square.
       virtual void Size(float lfSize);
    /// Sets the size of the image on screen. Makes the width be lfSize pixels and makes the height to make it appear square.
       virtual void Width(float lfWidth);
       /// Sets the size of the image on screen. Makes the width be lfSize pixels and makes the height to make it appear square.
       virtual void Height(float lfHeight);

        ///Will return the Width of this image in pixels.
        float Width();
        ///Will return the Height of this image in pixels.
        float Height();



};

/**
* \brief This is a Texture rendered onto a plane, which can be moved as a 3D object.
* This literally produces a 2D image on a plane in 3D. This can be mvoed like any other object
* This is good for producing billboards or in game HUDS or screens.
* Other than specified functions operates in the same way as the class cImage.
* Check the facing of the plane to be sure it displays.
*/
class cImage3D : public cImage
{

public:
	cImage3D();
	cImage3D(vRenderNode *lpCamera);
	cImage3D(cCamera *lpCamera);
    void SetUp();
};

#endif

#endif
