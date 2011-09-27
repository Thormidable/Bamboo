#ifndef __WTCCOLLISIONLIST_H__
#define __WTCCOLLISIONLIST_H__

class cCollisionListObject 
{
	cCollisionObject *mpObj;
	float mfDistance;
public:
	cCollisionListObject(cCollisionObject *lpObj){mpObj=lpObj;};
	float GetDistance(){return mfDistance;};
};

class cCollisionList
{


cLinkedNode<cCollisionObject> *mpCurPos;
cLinkedList<cCollisionObject> *mpCollisionList;

public:
	///The Constructor for cCollisionList
cCollisionList();
///This will Add the object lpObject to the list of objects colliding with the current searching object.
void AddCollision(cCollisionObject *lpObject);
///This will return the next item from the list mpCollisionList that has been stocked by GenerateCollisionList() as a CollisionObject pointer.
cCollisionObject *NextCollisionItem();

///This will return the process owning renderable object creating the next detected collision.
vProcess *NextCollisionP();

///This will return the renderable object involved in the next detected collision.
vRenderObject *NextCollisionR();

/// This will reset the collision search to the start of mpList.
void ResetList();

///This is the destructor for cCollisionList
~cCollisionList();
///This will sort the list of collisionobjects into distance from the colliding object order. This allows the user to resolve the collisions in 'Chronological' order.
void SortByDistance();

};

#endif