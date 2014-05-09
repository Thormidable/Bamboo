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
*The sizes and positions of objects are calculated during a render cycle. Objects will not collide until after their first render cycle, This is because the Global position of the object is used and is only calculated when the object is rendered.
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

/*
class cCollisionHandler
{

protected:
	//This is the current cursor position in the array mpList.
	uint32 miCurPos;
	//This is the current cursor position (the current cLinkedNode) in the List mpList[miTypeCur].
	cLinkedNode<cCollisionBase> *mpColCur;
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

public:

 /// This will find the appropriate array slot for the cCollisionBase lpObj. It will return the array position of the slot.
 virtual uint32 FindSlot(cCollisionBase *lpObj){(void) lpObj; return 0;};
 /// This will return the spatial slot for an object at lpPos.
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

 virtual bool RequiresSlotUpdate(){return 0;};

 friend class cCollisionBase;

 inline cLinkedNode<cCollisionBase> *GetCurrentObject(){return mpColCur;};
 inline uint32 GetCurrentSlot(){return miCurPos;};

};

class cCollisionHandlerType : public cCollisionHandler
{
protected:

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
	c3DVf mfCentre;
	c3DVf mfOffSet;

    bool mbEdgecase;
    uint32 miCurCentreSlot;
    uint8 miCurCurrentSlot;
    uint32 *mpCurSlotArray;
	// This makes arrays dimensions order in X,Z,Y without hard coding it. (1D is X Axis, 2D is X,Z axis and 3D is X,Z,Y axis).
	cCollisionHandlerBSP();
public:
    static int16 *mpSlotArray;
    static uint8 msCoords[3];
    static uint8 mpAxisOrder[3];

      // This will Actually search the Collision Lists and create a cCollisionList with all the detected collisions with objects of type lpType.
	cCollisionList *GenerateCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);
	//This will Actually search the Collision Lists and create a cCollisionList with all the detected collisions with objects of type lpType, with extra collision detail.
	cCollisionList *GenerateDetailedCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);
	cCollisionList *GeneratePossibleCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);

	// This will set the Centre of the Spatial Grid.
	void Position(float *lpTemp){memcpy(mfCentre.v,lpTemp,sizeof(float)*3);};
	// This will return the Centre of the Spatial Grid.
	c3DVf Position(){return mfCentre;};
	// This will find the slot that the cCollisionBase object should be in.
	uint32 FindSlot(cCollisionBase *lpObj);
	// This will find the slot that the position lpPos should be in.
	uint32 FindSlot(float *lpPos);
	// This will return the slot at spatial box index lpPos[0],lpPos[1],lpPos[2].
	cLinkedList<cCollisionBase> *FindSlot(uint32 *lpPos);

	// This will set msCoords to the current coords of the Slot at lpPos.
	void FindSlotCoord(float *lpPos);

    c3DVf FindSlotCentre(uint32 liSlot);
    // Will return the spatial centre of the Slot liSlot.
    c3DVf FindSlotCentre(uint8 liX,uint8 liY,uint8 liZ);
    // Will return the spatial centre of the Slot at index lpX[0],lpX[1],lpX[2].
    c3DVf FindSlotCentre(uint8 *lpX);
	//Tells the Kernel that this cCollisionHandler requires Slotupdates to be processed.
	bool RequiresSlotUpdate(){return 1;};

    void ResetSlotCursor(c3DVf &lpPos);
    void ResetSlotCursor(cMatrix4 *lpPos);
    void ResetSlotCursor(float *lpPos);
    void ResetSlotCursor(cCollisionBase *lpPos);
    //void ResetSlotCursor(uint32 liPos);
	// This will generate the array of boxes which need checking for collision detections.
	void GenerateSlotArray();
	// This will return the Next slot in the Slot array generated by GenerateSlotArray().
	uint32 NextSlot();
	inline bool EndOfSlotSearch(){return !miCurCurrentSlot;};

	static uint8 *SlotIndexToCoord(uint32 liSlot);

	virtual ~cCollisionHandlerBSP();

	friend class cCollisionHandler;
};
*/

class cCollisionHandler
{

protected:
	//This is the current cursor position in the array mpList.
	uint32 miCurPos;
	//This is the current cursor position (the current cLinkedNode) in the List mpList[miTypeCur].
	cLinkedNode<cCollisionBase> *mpColCur;
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

public:

 /// This will find the appropriate array slot for the cCollisionBase lpObj. It will return the array position of the slot.
 virtual uint32 FindSlot(cCollisionBase *lpObj){(void) lpObj; return 0;};
 /// This will return the spatial slot for an object at lpPos.
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

 virtual bool RequiresSlotUpdate(){return 0;};

 friend class cCollisionBase;

 inline cLinkedNode<cCollisionBase> *GetCurrentObject(){return mpColCur;};
 inline uint32 GetCurrentSlot(){return miCurPos;};

};

class cCollisionHandlerType : public cCollisionHandler
{
protected:

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
	c3DVf mfCentre;
	c3DVf mfOffSet;

    bool mbEdgecase;
    uint32 miCurCentreSlot;
    uint8 miCurCurrentSlot;
    uint32 *mpCurSlotArray;
	// This makes arrays dimensions order in X,Z,Y without hard coding it. (1D is X Axis, 2D is X,Z axis and 3D is X,Z,Y axis).
	cCollisionHandlerBSP();
public:
    static int16 *mpSlotArray;
    static uint8 msCoords[3];
    static uint8 mpAxisOrder[3];

      // This will Actually search the Collision Lists and create a cCollisionList with all the detected collisions with objects of type lpType.
	cCollisionList *GenerateCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);
	//This will Actually search the Collision Lists and create a cCollisionList with all the detected collisions with objects of type lpType, with extra collision detail.
	cCollisionList *GenerateDetailedCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);
	cCollisionList *GeneratePossibleCollisionList(cCollisionBase *lpObj,uint32 lpType=0,cCollisionList *lpList=0);

	// This will set the Centre of the Spatial Grid.
	void Position(float *lpTemp){memcpy(mfCentre.v,lpTemp,sizeof(float)*3);};
	// This will return the Centre of the Spatial Grid.
	c3DVf Position(){return mfCentre;};
	// This will find the slot that the cCollisionBase object should be in.
	uint32 FindSlot(cCollisionBase *lpObj);
	// This will find the slot that the position lpPos should be in.
	uint32 FindSlot(float *lpPos);
	// This will return the slot at spatial box index lpPos[0],lpPos[1],lpPos[2].
	cLinkedList<cCollisionBase> *FindSlot(uint32 *lpPos);

	// This will set msCoords to the current coords of the Slot at lpPos.
	void FindSlotCoord(float *lpPos);

    c3DVf FindSlotCentre(uint32 liSlot);
    // Will return the spatial centre of the Slot liSlot.
    c3DVf FindSlotCentre(uint8 liX,uint8 liY,uint8 liZ);
    // Will return the spatial centre of the Slot at index lpX[0],lpX[1],lpX[2].
    c3DVf FindSlotCentre(uint8 *lpX);
	//Tells the Kernel that this cCollisionHandler requires Slotupdates to be processed.
	bool RequiresSlotUpdate(){return 1;};

    void ResetSlotCursor(c3DVf &lpPos);
    void ResetSlotCursor(cMatrix4 *lpPos);
    void ResetSlotCursor(float *lpPos);
    void ResetSlotCursor(cCollisionBase *lpPos);
    //void ResetSlotCursor(uint32 liPos);
	// This will generate the array of boxes which need checking for collision detections.
	void GenerateSlotArray();
	// This will return the Next slot in the Slot array generated by GenerateSlotArray().
	uint32 NextSlot();
	inline bool EndOfSlotSearch(){return !miCurCurrentSlot;};

	static uint8 *SlotIndexToCoord(uint32 liSlot);

	virtual ~cCollisionHandlerBSP();

	friend class cCollisionHandler;
};


#endif
