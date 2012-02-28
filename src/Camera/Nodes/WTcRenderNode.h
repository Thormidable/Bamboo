#ifndef __WTCRENDERNODE_H__
#define __WTCRENDERNODE_H__



/**
* \brief This is a dynamic render tree branch.
 * This class stores a dynamic list of cRenderObjects called mpObjects. cRenderNode inherits cRenderObject and so
 * can be stored in mpObjects of other cRenderNodes. Any translations applied to this cRenderNode will modify the
 * base coordinates of any objects stored in mpObjects. This allows objects to be grouped for the purposes of translations.
 * A cRenderNode volume encompasses all objects beneath it in the render tree, this increases the speed of collision
 * searches as a cRenderNode can remove all it's sub objects from the search. cRenderNode is the dynamic equivalent of cNodeList.
 * cRenderNode is good for building structures which regularly change or are hard to predict the shape of.
*/
class cRenderNode : public vRenderNode
//public cMatrix4, public cSignal
{

 // Dynamic Linked List of renderable objects.
 cLinkedList<vRenderObject> *mpObjects;

public:

	// Current position in the render list mpObjects.
       cLinkedNode<vRenderObject> *mpCursor;

	/// Constructor for cRenderNode.
       cRenderNode();
	/// Constructs a new cRenderNode which is owned by lpRenderer.
       cRenderNode(vRenderNode *lpRenderer);

        //Constructor for generating Top level RenderNodes
       cRenderNode(bool lpTopLevel,cCamera *lpCamera);
	   cRenderNode(cCamera *lpCamera);

       ~cRenderNode();

        void Initialise();

  cMatrix4 *operator=(cMatrix4 *lpOther);
  cMatrix4 &operator=(cMatrix4 &lpOther);
  float *operator=(float *lpOther);

  void CalculateMatrices();
  void RecalculateTotalMatrix();
	/*
	* \brief Will remove the current object from the render list.
	* \param lpOld This should be mpNode.
	*/
       void Remove(cRenderOwner lpOld);
	/*
	* \brief Will add the current object to the render list owned by lpNew.
	* \param lpNew This should be the cRenderNode that will control this object.
	*/
       cRenderOwner Add(vRenderObject *lpNew);

	// Will return a pointer to this objects render list - mpObjects.
       cLinkedList<vRenderObject> *RenderList();

	// Will delete all the objects Controlled by this cRenderNode.
       void DeleteAll();


	// Will render all the objects in the render list mpObjects to the cPainter render list.
       void RenderToPainter();


       // The Collision Object that is linked to this cRenderNode.
	void LinkCollisionObject(cCollisionObject *lpObj);

    // This will perform additional functions, when this object is rendered.
    void AdditionalRenderFunctions();

    //This will Delete the tree from this point down.
    void StartKillAll();
    void KillAll();

};

#endif
