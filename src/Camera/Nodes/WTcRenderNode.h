#ifndef __WTCRENDERNODE_H__
#define __WTCRENDERNODE_H__

/** 
* \brief This is a dynamic render tree branch. 
 * This class stores a dynamic list of cRenderObjects called mpObjects. cRenderNode inherits cRenderObject and so
 * can be stored in mpObjects of other cRenderNodes. Any translations applied to this cRenderNode will modify the 
 * base coordinates of any objects stored in mpObjects. This allows objects to be grouped for the purposes of translations.
 * A cRenderNode volume encompasses all objects beneath it in the render tree, this increases the speed of collision 
 * searches as a cRenderNode can remove all it's sub objects from the search.
*/
class cRenderNode : public vRenderObject
//public cMatrix4, public cSignal
{
 // Dynamic Linked List of renderable objects.
 cLinkedList<vRenderObject> *mpObjects;
 // cLinkedNode which owns this renderable object.
 cLinkedNode<vRenderObject> *mpNode;

 // cRenderNode which owns this renderable object.
 cRenderNode *mpRenderer;
 
public:
	/// Returns the cRenderNode which owns this object.
       cRenderNode *Renderer();

	// Current position in the render list mpObjects.
       cLinkedNode<vRenderObject> *mpCursor;

	/// Constructor for cRenderNode. 
       cRenderNode();
	/// Constructs a new cRenderNode which is owned by lpRenderer.
       cRenderNode(cRenderNode *lpRenderer);

       ~cRenderNode();
	
        void Initialise();
	

	/* 
	* \brief Will remove the current object from the render list. 
	* \param lpOld This should be mpNode.
	*/
       void Remove(cLinkedNode<vRenderObject> *lpOld);
	/* 
	* \brief Will add the current object to the render list owned by lpNew. 
	* \param lpNew This should be the cRenderNode that will control this object.
	*/
       cLinkedNode<vRenderObject> *Add(vRenderObject *lpNew);

	// Will return a pointer to this objects render list - mpObjects.
       cLinkedList<vRenderObject> *RenderList();

	// Will delete all the objects Controlled by this cRenderNode.
       void DeleteAll();


	// Will render all the objects in the render list mpObjects to the cPainter render list.
       void RenderToPainter();
	// Will render all the objects in the render list mpObjects from the cPainter render list to the screen, using the command liCommand.
       void RenderPainter(uint8 liLevel);
       // Will render all the object in the render 
       void RenderPainter();

	// Will render all the objects in the render list mpObjects to the screen.
       void Render();

       // The Collision Object that is linked to this cRenderNode.
	void LinkCollisionObject(cCollisionObject *lpObj);
 
// This will perform additional functions, when this object is rendered.
 void AdditionalRenderFunctions();

// void Signal(SIGNAL lsFlags);

	void UpdateCache();

	/// This will return the Local position of the selected object.
	float *GetPos();
	/// This will return the global position of the object as rendered at the end of last frame. Note, this will contain the camera matrix.
	float *GetGlobalPos();
};

#endif
