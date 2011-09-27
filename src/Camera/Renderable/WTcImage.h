#ifndef __WTCIMAGE_H__
#define __WTCIMAGE_H__
/**
* \brief A 2D renderable object.
* \param lpTexture pointer to the texture to bind to this 2D object
* This is actually a 3D polygon, which has a texture bound to it.
* it can be used as an OpenGL accelerated sprite.
*/
class cImage : public cRenderObject
{
 // This is the texture image which will form the sprite.
 vTexture *mpPixmap;
 // This is the size of the sprite on the screen.
 float mfSize;
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
public:
	/** Constructor for cImage.
	* \brief Will construct a new cImage class, and set the vTexture it will use.
	* \param lpTexture the vTexture that this object will use.
	*/
       cImage(vTexture *lpTexture);
 	/// Constructor for cImage. Will Create an Empty cImage Object.
       cImage();
	// This function will set this object to being a 2D object and initialise the arrays.
       void SetUp();
	//Destructor for cImage.
       ~cImage();

	/// Will set the current vTexture this object will use.
        void Texture(vTexture *lpObject);

	/// This returns the Texture ID of the texture this object will use.
        unsigned int TextureNumber();

	// Function to render this object from the cPainter render list.
       void RenderPainter(uint8 liLevel);
	// Function to render this object to the cPainter render list.
       void RenderToPainter();

	// Function to render this object to the screen.
        void Render();

	/// Sets the size of the image on screen.
       void Size(float lfSize);
	

};


#endif
