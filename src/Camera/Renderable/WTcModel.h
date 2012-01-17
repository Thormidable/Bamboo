#ifndef __WTCMODEL_H__
#define __WTCMODEL_H__


/**
* \brief A standard Textured Model renderable object.
*/
class cModel :public cRenderObject,virtual public cMaterial
{

 cMesh* mpMesh;


public:
 /// cModel constructor
 cModel();
 /// cModel constructor. Will be owned by lpRenderer.
 cModel(vRenderNode *lpRenderer);

	/// Will set the mesh the model will use.
        void Mesh(cMesh *lpObject);

	/// Will return the currently set Mesh.
		cMesh *Mesh();

	// Will render this object to the cPainter render list.
	void RenderPainter();


};

#endif
