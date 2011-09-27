#ifndef __WTCTEXTUREDMODEL_H__
#define __WTCTEXTUREDMODEL_H__
/**
* \brief A standard Textured Model renderable object.
*/
class cTexturedModel :public cRenderObject,virtual public cMaterial
{
 // The current mesh that deterimines the shape of the model.
 vMesh* mpMesh;
 // The current texture that is bound to this object.
 vTexture* mpTexture;
 
public:
 /// cTexturedModel constructor
 cTexturedModel();
 /// cTexturedModel constructor. Will be owned by lpRenderer.
 cTexturedModel(cRenderNode *lpRenderer);

	/// Will set the mesh the model will use.
        void Mesh(vMesh *lpObject);
	// Will return the number of the vTexture that is currently bound to this model.
        unsigned int TextureNumber();
	/// Will set the texture bound to this model.
	void Texture(vTexture *lpTexture);
	/// Will return the pointer to the vTexture that is currently bound to this model.
	vTexture *Texture();
	
	// Will render this object to the cPainter render list.
	void RenderPainter(uint8 liLevel);
	// Will render this object from the cPainter render list to the screen.
	void RenderToPainter();
	// Will render this object to the screen.
	void Render();
	

};

#endif
