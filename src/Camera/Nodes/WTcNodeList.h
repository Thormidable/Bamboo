#ifndef __WTCNODELIST_H__
#define __WTCNODELIST_H__

#if WT_FULL_VERSION_BAMBOO

#define WT_MODELLIST_NEWLEVEL 0xFF

class cNodeList;
/**
 *\brief Storage Node class for cNodeList.
 * This is an interface class for cNodeList and Renderable Objects. It also stores the objects depth in the current tree.
 *
 */
class cNodeListNode
{
  vRenderObject *mpObject;
  uint8 miLevel;
  public:
    void LoadNode(cMeshTreeNode *lpNode);
    ~cNodeListNode();
    cNodeListNode();
    cNodeListNode(vRenderObject *lpObject,uint8 liLevel=0);
  friend class cNodeList;
};

/**
* \brief Node list is a 'static' render tree holding data for a series of renderable objects. It counts as a single renderable object.
* \param lpTree a pointer to the cMeshTree object loaded from cIMF::LoadIMF()
* \param lpRenderer Places this object beneath lpRenderer in the scene graph.
* This is another type of Render Node. Similar to cRenderNode. cRenderNode is a dynamic Node designed for shallow trees with regularly changing sizes and shapes.
* cNodeList is a 'static' Node designed for deep trees which do not regularly change. These can be loaded from files (Mesh Trees). And are suitable for building structures with lots of components glued to other components.
* Each object is given a depth. The object will base its co-ordinate system off the last object with a lower depth value.
* cNodeList holds a static array of cNodeListNode. cNodeListNode holds all the relative data about each object in the render tree.
* cNodeList objects loaded from files are cModel objects. cNodeLists can have cRenderNodes or cNodeLists as parents. They can contain any Render Object which includes cRenderNodes or cNodeLists.
* Just Pass the pointer to the cNodeList which you want to parent a new object and it will add itself to the cNodeList.
* It is more efficient to build a single large cNodeList than to put one inside another. Global Rotations are mapped as Local Rotations inside cNodeList as the objects are deemed to be glued and so are limited to Local Rotations.
* cRenderNode s fully support Global Rotations.
*/
class cNodeList : public vRenderNode
{
// This stores the current depth in render branches.
 int8 miLevel;

    cLimitedPointerList<cNodeListNode> mpList;

 cMeshTree *mpMeshTree;
// Static Function to aid finding the size.
static float lsPosition[16];

float mfSize;

uint32 miCursor;
public:
 /**
 * \brief This is the constructor for cNodeList. It will create the list based on the cMeshTree file lpTree.
 * \param lpTree This is the file containing the data for the structure (and models etc.) of the render tree.
 */
 cNodeList(cMeshTree *lpTree);
/**
 * \brief This is the constructor for cNodeList. It will create the list based on the cMeshTree file lpTree, and will be owned by lpRenderer.
 * \param lpTree This is the file containing the data for the structure (and models etc.) of the render tree.
 * \param lpRenderer This is the vRenderNode which will own this renderable object.
 */
cNodeList(cMeshTree *lpTree,vRenderNode *lpRenderer);
cNodeList(cMeshTree *lpTree,cCamera *lpCamera);
cNodeList(uint32 liLength,cCamera *lpCamera);
cNodeList(bool lpTopLevel,uint32 liLength,cCamera *lpCamera);
cNodeList(const char *lsTree);
cNodeList(const char *lpTree,vRenderNode *lpRenderer);
cNodeList(const char *lpTree,cCamera *lpCamera);

/// Will re-initialise this cNodeList using the file lpTree. It will have the structure and models of the file.
void LoadTree(cMeshTree *lpTree);
///Will re-initialise this cNodeList using the ModelList with reference lcTree. It will have the structure and models of the file.
void LoadTree(string lcTree);

 /// Create an empty cNodeList of size liLength.
 cNodeList(uint32 liLength);
 /// Create an empty cNodeList of size liLength. lpRenderer will own this ModelList.
 cNodeList(uint32 liLength,vRenderNode *lpRenderer);

 ~cNodeList();

 /// Will reset this object to be an empty cNodeList of size liLength.
 void InitialiseList(uint32 liLength);

 /// Will return the current size of the cNodeList.
 uint32 ListLength();

///Will return a pointer to the item in Position liPos;
 vRenderObject *GetListItem(uint16 liPos);
 ///Will return the level value of the item in Position liPos;
 uint8 GetItemLevel(uint16 liPos);

 // Renders this cNodeList to the cPainter render list.
 void RenderToPainter();


cRenderOwner Add(vRenderObject*);
cRenderOwner Add(vRenderObject *lpNew,uint8 miLevel);
void Delete(cRenderOwner Owner);

void RecalculateTotalMatrix();
void CalculateMatrices();


///Will delete all Render Obnjects inside this object
 void DeleteAll();

public:

/**
 * \brief This will set a command for a single model in the model list.
 * \param liPos the number of the object in mpList this function will affect.
 * \param liCom The command to be called before rendering model number liPos.
 * The commands determine how the matrix stack is modified before the object is rendered.
 * WT_MODELLIST_NEW_LEVEL will push the current matrix onto the matrix stack.
 * Anything else is the number of matrices that will be popped off the matrix stack.
 */
 void SetLevel(uint16 liPos,uint8 liCom);

 void StartKillAll();
 void KillAll();

	cMatrix4 *CalculateGlobalMatrix();

	cRenderOwner MoveItem(vRenderObject *lpObj,vRenderNode *lpRenderer);

	void MoveAll(vRenderNode *lpRender);

	vRenderObject *FindStart();
	vRenderObject *FindNext();

	bool ContainsItems();

	float GetSize();
	double GetSizeSq();

	void TreeProcessUserSignal(SIGNAL lsSignal,void *lpData);
	void TreeProcessSignal(SIGNAL lsSignal);

	void TreeSignal(SIGNAL lsSignal);
};

#endif

#endif
