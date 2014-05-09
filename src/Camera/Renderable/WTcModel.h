#ifndef __WTCMODEL_H__
#define __WTCMODEL_H__


/**
* \brief A standard Textured Model renderable object.
*/
class cModel :public cRenderObject
{

 cMesh* mpMesh;


public:
 /// cModel constructor
 cModel();
 /// cModel constructor. Will be owned by lpRenderer.
 cModel(vRenderNode *lpRenderer);
 /// cModel constructor. Will be owned by the cRenderNode of the cCamera lpCamera.
 cModel(cCamera *lpCamera);

	/// Will set the mesh the model will use.
        void Mesh(cMesh *lpObject);
    ///Will set the mesh the model will use. Works on a media reference.
        void Mesh(const char* lcReference);

	/// Will return the currently set Mesh.
		cMesh *Mesh();

	// Will render this object to the cPainter render list.
	void RenderPainter();

    float GetSize();
    double GetSizeSq();

	///Will return the closest UV co-ordinates based of a point in Global space.
    c2DVf GetUVCoords(c3DVf GlobalPos);

    void UpdateArrayStates();

};


/**
* \brief A Base for rendering to a Texture.
    Will Automatically Write to the smallest cTexture object that is at least as large as the screen.
*/

class cRenderableTexture : public cTexture
{
 bool mbClearTexture;
 cRGBA mcClearColor;
 GLuint miFrameBuffer;
 uint8 miColorAttachment;
public:
    //cRenderableTexture();
    cRenderableTexture(uint32 liWidth, uint8 liHeight, uint8 liDepth=32);
    cRenderableTexture(cTexture *lpTexture);
    ~cRenderableTexture();
        /**
            \brief Will Prepare OpenGL to render to a cTexture Object.
            This will Check that the cTexture exists. Then that the size of the cTexture that it is big enough to receive the entire screen.
            Then it will bind and prepare the cTexture to be written to. All rendering will be rendered to the cTexture Object.
        */
        void PrepTextureToWriteTo();
        /// This will release the cTexture object and set the system to render to the screen once again.
        void FinishWriteToTexture();

        void ResizeFrameBuffer(uint32 liWidth,uint32 liHeight, uint8 liDepth=32);

        /// This will move the cTexture data from the Graphics card into RAM. This is a slow operation and unneccessary for rendering using the cTexture object. Instead call FinishWriteToTexture() and then use the cTexture object.
        void ExtractTexture();

        void BufferTexture();

        void SetColorAttachment(uint8 liColor);

        void SetClearColor(cRGBA lcColor);
        void SetClearState(bool lbClear);

};

/**
* \brief cMesh class for cPostProcess to Use.
*/
class cScreenQuadMesh : public cMesh
{
public:
    cScreenQuadMesh();
};

/**
* \brief This is really just an optimised square of four verteces with Texture co-ordinates.
* To operate as a PostProcess it needs to be aligned to cover the screen. This can be achieved with a Vertex Shader which reads \n
* void main(void) \n
* { \n
   gl_Position = vec4(gl_Vertex.xy, 0.0, 1.0); \n
  } \n
* \n
   gl_Vertex can also be used for Texture Co-ordinates, this will have Texture Coordinates 0,0 in the Lower left corner and 1,1 in the Top right corner.
   This Objecty does not have Normals or Texture Co-ordinate data as they are either meaningless or already being transfered.
*/
class cPostProcess : public cRenderObject
{

 static cScreenQuadMesh *spMesh;

public:
    cPostProcess();
    cPostProcess(cCamera *lpCamera);
    cPostProcess(vRenderNode *lpNode);

    void RenderPainter();

};


#endif
