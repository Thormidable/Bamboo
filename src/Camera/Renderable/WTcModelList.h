#ifndef __WTCMODELLIST_H__
#define __WTCMODELLIST_H__

#define WT_MODELLIST_NEWLEVEL 0xFF

class cModelList;
/// Class for storing data about a single node on in the Model List.
class cModelListNode
{
 vMesh *mpMesh;
 vTexture *mpTexture;
 cMatrix4 mmMatrix;
  uint8 miLevel;
  vShaderProgram *mpShader;
	// Will take a cMeshTreeNode as loaded from cIMF::LoadIMF() and will link Object names to files in memory.
	void LoadNode(cMeshTreeNode *lpNode);
	float mfSize;
public:
	vMesh *Mesh(){return mpMesh;}
	cModelListNode();
	~cModelListNode();

 cRenderPointer *mpPainterData;
 cRenderPointer **mpSlot;

friend class cModelList;
};

/**
* \brief Model list is a 'static' render tree holding data for a series of renderable objects. It counts as a single renderable object.
* \param lpTree a pointer to the vMeshTree object loaded from cIMF::LoadIMF()
* \param lpRenderer Places this object beneath lpRenderer in the scene graph.
* This works like a scene graph, The relative depths of the objects is controlled by
* cModelListNode::miLevel. cModelList holds a static array of cModelListNode. cModelListNode holds all the relative data about each object in the render tree. 
*/
class cModelList : public cMaterial, public cRenderObject
{
// This stores the current number of slots in the render tree.
 uint32 miLength;
// This stores the current depth in render branches.
 int16 miLevel;
// This is the array of slots in the render tree.
 cModelListNode *mpList;

// This is the cRenderNode which owns this renderable object.
   cRenderNode *mpRenderer;
// This is the cLinkedNode which owns this renderable object.
   cLinkedNode<vRenderObject> *mpNode;

 vMeshTree *mpMeshTree;

// Static Function to aid finding the size.
static float lsPosition[16];

float mfSize;
public:
 /**
 * \brief This is the constructor for cModelList. It will create the list based on the vMeshTree file lpTree.
 * \param lpTree This is the file containing the data for the structure (and models etc.) of the render tree.
 */
 cModelList(vMeshTree *lpTree);
/**
 * \brief This is the constructor for cModelList. It will create the list based on the vMeshTree file lpTree, and will be owned by lpRenderer.
 * \param lpTree This is the file containing the data for the structure (and models etc.) of the render tree.
 * \param lpRenderer This is the cRenderNode which will own this renderable object.
 */ 
cModelList(cRenderNode *lpRenderer,vMeshTree *lpTree);

/// Will re-initialise this cModelList using the file lpTree. It will have the structure and models of the file.
void LoadTree(vMeshTree *lpTree);

 /// Create an empty cModelList of size liLength.
 cModelList(uint32 liLength);
 /// Create an empty cModelList of size liLength. lpRenderer will own this ModelList.
 cModelList(cRenderNode *lpRenderer,uint32 liLength);
 ~cModelList();

 /// Will reset this object to be an empty cModelList of size liLength.
 void Initialise(uint32 liLength);

 /// Will return the current size of the cModelList.
 uint32 ListLength();

 /**
 * \brief Will return a pointer to the matrix of model[liPos].
 * \param liPos The number of the object in the list.
 * \return returns a pointer to the matrix of model[liPos]
 */
 cMatrix4 &GetMatrix(uint32 liPos);


 // Renders this cModelList to the cPainter render list.
 void RenderToPainter();
 void RenderNodePainter(uint8 liListPos);


 //Renders model[liCommand] from the cPainter list. Parameter liCommand is the model number in mpList that will be rendered from the cPainter render list. It is required to render each object in mpList individually from the cPainter render list.

 void RenderPainter(uint8 liLevel);

 // Will process the entire model list to the screen.
 void Render();
private :
 //Renders a single object from mpList to the screen.The Paramter liPos is the number of the object to be rendered to the screen. This will render mpList[liPos] to the screen.
  inline void RenderCode(cModelListNode *lpNode);
public:

 /**
 * \brief This will bind a texture for a single model in the model list.
 * \param liPos the number of the object in mpList this function will affect.
 * \param lpTexture a pointer to the Texture to bind to object number liPos.
 */
 void SetTexture(uint32 liPos, vTexture *lpTexture);
 /**
 * \brief This will bind a texture for a single model in the model list.
 * \param liPos the number of the object in mpList this function will affect.
 * \param lpTexture a pointer to the Shader for object number liPos to use.
 */
 void SetShader(uint32 liPos, vShaderProgram *lpShader);

 /**
 * \brief This will set a mesh for a single model in the model list.
 * \param liPos the number of the object in mpList this function will affect.
 * \param lpMesh a pointer to the mesh to use for object number liPos.
 */ 
void SetMesh(uint32 liPos, vMesh *lpMesh);
/**
 * \brief This will set a command for a single model in the model list.
 * \param liPos the number of the object in mpList this function will affect.
 * \param liCom The command to be called before rendering model number liPos.
 * The commands determine how the matrix stack is modified before the object is rendered.
 * WT_MODELLIST_NEW_LEVEL will push the current matrix onto the matrix stack.
 * Anything else is the number of matrices that will be popped off the matrix stack.
 */ 
 void SetCommand(uint32 liPos,uint8 liCom);

 
 //This can probably be removed
 //void UpdateSize();


};

#endif
