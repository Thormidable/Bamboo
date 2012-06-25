#ifndef __WTCCOLLISIONHANDLER_H__
#define __WTCCOLLISIONHANDLER_H__


/**
* \brief This is the Collision Handler. It will control any collision search the user performs.
* This Collision handler is created by using the Instance() and can ONLY be created using Instance(). _COLLISION_HANDLER is a quick pointer to the cCollisionHandler::Instance() pointer.
* This will store data for the search and will store the current position to resume searches.
* Calling the Function GenerateCollisionList() wil create a comprehensive list of pointers to cRenderobjects() that meet the
* collision parameters of GenerateCollisionList().
* This list can be accessed by using NextCollisionItem().
*
*The sizes and positions of objects are calculated during a render cycle.
*????Objects will not collide until after their first render cycle.
*
* There are three types of Collision Searches. Tree, Type and Binary Spatial Position. (defined by setting WT_COLLISION_HANDLER_TYPE
* to WT_COLLISION_HANDLER_TYPE_TYPE or WT_COLLISION_HANDLER_TYPE_BSP.
*
* Tree searches are performed by traversing the render tree. Each objects size is based on the size of the
* objects beneath it so if a Node does not collide all objects beneath that node can be ignored.
*
* Type searches are filtered by type. cCollisionBase's are given a cCollisionBase::CollisionFilter(uint32 liID) using which
* they are sorted into seperate lists of Collision objects. If a search is performed with a defined ID term, only the list containing
* objects with the desired filter value are searched.
*
*Binary Spatial Position Collision Handlers sort cCollisionBases into the spatial boxes they contact with. This means it is only neccessary
*to check other objects within the boxes the current object resides within.

*/
class cCollisionHandler
{
public:


	cCollisionHandler(){};
 /// This is a pointer to the classes current instance. There can only be one...
 static cCollisionHandler *spInstance;

  ///This will add the cCollisionBase pointed to by lpObject to the list mpList.
 virtual cLinkedNode<cCollisionBase> *Add(cCollisionBase *lpTemp)=0;

 ///This will turn off Collisions for the cLinkedNode lpOld. This should in turn call RemoveFromList().
 virtual void Remove(cLinkedNode<cCollisionBase> *lpOld){(void) lpOld;};
 ///This will acutally remove the clinkedNode from the relevant list.
 virtual void RemoveFromList(cLinkedNode<cCollisionBase> *lpOld){(void) lpOld;};

 /// This will return the Next item in the lists in order. (The item is pointed to by mpColCur). If an item is found will return true, else will return false.
 virtual bool NextListItem(){return 0;};
 /// This will return the Next item in the list storing lpType in order. (the item is pointed to by mpColCur).If an item is found will return true, else will return false.
 virtual bool NextListItem(uint32 lpType){(void) lpType; return 0;};

 ///This will return the list for the spatial slot lpPos[0],lpPos[1],lpPos[2]. (Array slots not spatial co-ordinates).
 virtual cLinkedList<cCollisionBase> *FindSlot(uint32 *lpPos){(void) lpPos; return 0;};

 ///This will set the current Position of the Spatial Array.
 virtual void Position(float *lpTemp){(void) lpTemp;};
 ///This will return the current Position of the Spatial Array.
 virtual float *Position(){return 0;};
public:

 /// This will find the appropriate array slot for the cCollisionBase lpObj. It will return the array position of the slot.
 virtual uint32 FindSlot(cCollisionBase *lpObj){(void) lpObj; return 0;};

 virtual uint32 FindSlot(float *lpPos){(void) lpPos;return 0;};
///This is an array for storing all Collision Objects, that are currently on. The size of the array is set by WT_COLLISION_HANDLER_ARRAY_SIZE.
 cLinkedList<cCollisionBase> *mpList;

 /// This will return a pointer to the classes current instance and if there is none it will create one.
 static cCollisionHandler *Instance();
/// This will Actually search the Collision Lists and create a cCollisionList with all the detected collisions with objects of type lpType.
 virtual cCollisionList *GenerateCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0)=0;
 /// This will Actually search the Collision Lists and create a cCollisionList with all the detected collisions with objects of type lpType, with extra collision detail.
 virtual cCollisionList *GenerateDetailedCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0)=0;
     ///This will Generate a list of all awake cCollisionObjects with the the correct filter and in the correct spatial slots. No Collision Checks will be performed.
 virtual cCollisionList *GeneratePossibleCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0)=0;
 /// This will deconstruct the class.
 virtual ~cCollisionHandler();

 /// This will reset both the cursors used to track position through the collision object lists. Does not point to the first item in the list.
 virtual void ResetCursors()=0;

 friend class cCollisionBase;

};

class cCollisionHandlerType : public cCollisionHandler
{
protected:


	//XXXXXXXXXXXXXXx may want to make this an Array of pointers. Need to check pointers before use. XXXXXXXXXXXXXX
	//This is the current cursor position in the array mpList.
	uint32 miCurPos;
	//This is the current cursor position (the current cLinkedNode) in the List mpList[miTypeCur].
	cLinkedNode<cCollisionBase> *mpColCur;


	//Private Constructor
	cCollisionHandlerType();

	//This will add the cCollisionBase pointed to by lpObject to the list mpList.
 	cLinkedNode<cCollisionBase> *Add(cCollisionBase *lpTemp);

	//This will turn off Collisions for the cLinkedNode lpOld. This should in turn call RemoveFromList().
	void Remove(cLinkedNode<cCollisionBase> *lpOld);
	//This will acutally remove the clinkedNode from the relevant list.
	void RemoveFromList(cLinkedNode<cCollisionBase> *lpOld);

	// This will return the Next item in the lists in order. (The item is pointed to by mpColCur). If an item is found will return true, else will return false.
	bool NextListItem();
	// This will return the Next item in the list storing lpType in order. (the item is pointed to by mpColCur).If an item is found will return true, else will return false.
	bool NextListItem(uint32 lpType);
	// This will find the appropriate array slot for the cCollisionBase lpObj. It will return the array position of the slot.
	virtual uint32 FindSlot(cCollisionBase *lpObj);


	//This will set the current Position of the Spatial Array.
	virtual void Position(float *lpTemp){(void) lpTemp;};
	//This will return the current Position of the Spatial Array.
	virtual float *Position(){return 0;};

	//This will Find the Spatial Slot for the position lpPos.
	virtual uint32 FindSlot(float *lpPos){(void) lpPos; return 0;};
	//This will return the list for the spatial slot lpPos[0],lpPos[1],lpPos[2]. (Array slots not spatial co-ordinates).
	virtual cLinkedList<cCollisionBase> *FindSlot(uint32 *lpPos){(void) lpPos; return 0;};

public:


	cCollisionList *GenerateCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);
	cCollisionList *GenerateDetailedCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);
    cCollisionList *GeneratePossibleCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);

	// This will reset both the cursors used to track position through the collision object lists.
	void ResetCursors();


	// This will deconstruct the class.
	virtual ~cCollisionHandlerType();

	friend class cCollisionHandler;
};

class cCollisionHandlerBSP : public cCollisionHandlerType
{

protected:
	// This stores the Current central position of the Spatial Array.
	float mfCentre[3];
	// This makes arrays dimensions order in X,Z,Y without hard coding it. (1D is X Axis, 2D is X,Z axis and 3D is X,Z,Y axis).
	static uint32 mpAxisOrder[3];

	cCollisionHandlerBSP();
public:

    // This will Actually search the Collision Lists and create a cCollisionList with all the detected collisions with objects of type lpType.
	cCollisionList *GenerateCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);
	//This will Actually search the Collision Lists and create a cCollisionList with all the detected collisions with objects of type lpType, with extra collision detail.
	cCollisionList *GenerateDetailedCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);
    cCollisionList *GeneratePossibleCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);
	void Position(float *lpTemp){memcpy(mfCentre,lpTemp,sizeof(float)*3);};
	float *Position(){return mfCentre;};
	uint32 FindSlot(cCollisionBase *lpObj);
	uint32 FindSlot(float *lpPos);
	cLinkedList<cCollisionBase> *FindSlot(uint32 *lpPos);

	virtual ~cCollisionHandlerBSP();

	friend class cCollisionHandler;
};


#endif
