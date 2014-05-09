#ifndef __WTLLTemplate_H__
#define __WTLLTemplate_H__

//#include <windows.h>
//#include <cstdio>


template<class T> class cLinkedList;
/**
* \brief This is a node class to allow templating of the cLinkedList class.
* This node will store pointers to the nodes either side of this node in the linked list
* and a pointer to the object his node owns.
*/
template<class T> class cLinkedNode
{
	friend class cLinkedList<T>;

	cLinkedNode(T *lpNew){mpNext=0;mpPrev=0;mpData=lpNew;mpList=0;}

	/// This is a pointer to the next cLinkedNode owned by the linked list cLinkedList.
	cLinkedNode *mpNext;
	/// This is a pointer to the previous cLinkedNode owned by the linked list cLinkedList.
	cLinkedNode *mpPrev;

	cLinkedList<T> *mpList;

	void List(cLinkedList<T> *lpTemp){mpList=lpTemp;};
		/// This is a pointer to the data owned by this node.
	T *mpData;

public:
	/// This will delete the data owned by this node as it is deconstructed.
	~cLinkedNode()
	{
		delete mpData;
		mpData=0;
		mpNext=0;
		mpPrev=0;
	};

	/// This will return a pointer to the next node in the linked list. see cLinkedList.
	cLinkedNode<T> *Next(){return mpNext;}
	/// This will return a pointer to the previous node in the linked list. see cLinkedList.
	cLinkedNode<T> *Previous(){return mpPrev;}
	///Will return a pointer to this nodes current list
	cLinkedList<T> *List(){return mpList;}

	T *Data(){return mpData;};
};

/**
* \brief This is the control for a linked list.
* It controls a linked list of cLinkedNodes which each point to their item in the list.
* Each cLinkedNode poitns to the cLinkedNode s either side of themselves and the data they own.
* cLinkedList is templated and so can be a linked list of any type.
*/
template<class T> class cLinkedList
{
protected:
/// This is a pointer to the first cLinkedNode in the list.
       cLinkedNode<T> *mpStart;
	/// This is a pointer to the last cLinkedNode in the list.
       cLinkedNode<T> *mpEnd;

	   cLinkedNode<T> *mpCursor;

public:

	void StitchOut(cLinkedNode<T> *lpNode);
	static void StitchOutStatic(cLinkedNode<T> *lpNode);
	void StitchIn(cLinkedNode<T> *lpNode);
	//This will insert the data item lpNode immediately after the Node lpPos.
	void StitchIn(cLinkedNode<T> *lpNode,cLinkedNode<T> *lpPos);


	/// This holds a pointer of the relevant type for the list and will create the list by making the item lpData the first item in the list.
       cLinkedList(T *lpData);
	cLinkedList();
	/// This will delete the list and delete every item in the list.
	~cLinkedList()
	{
		DeleteAll();
	};

	cLinkedNode<T> *Start(){return mpStart;};

      cLinkedNode<T> *End(){return mpEnd;};
	/// This is a pointer that can be used as a cursor by this linked list.
       static cLinkedNode<T> *mpTemp;
	/// This is the number of items in the list.
       //int miSize;

	/// This will return the cLinkedNode which owns the item lpData in this list.
       cLinkedNode<T> *Find(T *lpData);

	/// This will create a cLinkedNode give it lpData and add that node to the end of the list.
       //Insert New item Before or After Cursor
       cLinkedNode<T> *Insert(T *lpData);

		cLinkedNode<T> *Insert(T *lpNode,cLinkedNode<T> *lpPosition);
	/// This will delete the cLinkedNode pointed to by lpOld and remove it from the list including mpData.
        void Delete(cLinkedNode<T> *lpOld);

	void Initialise();

	/// This will Move the node lpFrom to be before lpPosition.
	static void Move(cLinkedNode<T> *lpFrom,cLinkedNode<T> *lpPosition);
	static void Move(cLinkedNode<T> *lpFrom,cLinkedList<T> *lpPosition);

	void ClearAll();
	void DeleteAll();


	void Display();
	/// This will delete the cLinkedNode pointed to by lpOld and remove it from the list, but not delete mpData.
	void Remove(cLinkedNode<T> *lpNode);

	T *FindStart(){mpCursor=Start(); if(mpCursor) return mpCursor->Data(); return 0; };
	T *FindNext(){mpCursor=mpCursor->Next(); if(mpCursor) return mpCursor->Data(); else return 0;};
};

template<class T> void cLinkedList<T>::Initialise()
{
  mpStart=0;
  mpEnd=0;

//  mpTemp=0;
//  miSize=0;
}

template<class T> void cLinkedList<T>::DeleteAll()
{

if(mpStart)
{
 mpTemp=mpStart;
 while(mpTemp->mpNext && mpTemp!=mpEnd)
 {
  cLinkedNode<T> *lpKill;
  lpKill=mpTemp;
  mpTemp=mpTemp->mpNext;


  delete lpKill;
 }
 delete mpTemp;
 Initialise();
}

}


template<class T> void cLinkedList<T>::Remove(cLinkedNode<T> *lpNode)
{
 StitchOut(lpNode);
 lpNode->mpData=0;
 delete lpNode;
}


template<class T> void cLinkedList<T>::StitchOut(cLinkedNode<T> *lpNode)
{
if(lpNode->mpList!=this)
{
    lpNode->mpList->StitchOut(lpNode); return;
}
// if lpNode is Not the end
if (lpNode!=mpEnd) {lpNode->mpNext->mpPrev=lpNode->mpPrev;}
// if lpNode is the End
else
{
	mpEnd=lpNode->mpPrev;
	//If lpNode was not the start
	if(mpEnd) mpEnd->mpNext=0;


}

if (lpNode!=mpStart){lpNode->mpPrev->mpNext=lpNode->mpNext;}
else {mpStart=lpNode->mpNext; if(mpStart) mpStart->mpPrev=0; }

}


template<class T> void cLinkedList<T>::StitchOutStatic(cLinkedNode<T> *lpNode)
{
    lpNode->mpList->StitchOut(lpNode); return;
}

template<class T> cLinkedList<T>::cLinkedList()
{
 Initialise();

}

template<class T> void cLinkedList<T>::ClearAll()
{
	//trace("About to Clear a linked list")
	if(mpStart)
	{
		mpTemp=mpStart;
		while(mpTemp->mpNext)
		{
			mpTemp->mpData=0;
			mpTemp=mpTemp->mpNext;
			delete mpTemp->mpPrev;
		}
		mpTemp->mpData=0;
		delete mpTemp;
	}
	//trace("Done, you linked list is clear")
	Initialise();
}

template<class T> void cLinkedList<T>::Move(cLinkedNode<T> *lpFrom,cLinkedList<T> *lpPosition)
{
 cLinkedNode<T> *lpTemp;

  StitchOut(lpFrom);
  lpPosition->StitchIn(lpFrom);
}

template<class T> cLinkedNode<T> *cLinkedList<T>::mpTemp=0;


template<class T> cLinkedNode<T> *cLinkedList<T>::Find(T *lpData)
{
	mpTemp=mpStart;
	while (mpTemp && mpTemp->mpData!=lpData)
		{mpTemp=mpTemp->Next();}
}

template<class T> void cLinkedList<T>::Delete(cLinkedNode<T> *lpOld)
{

	StitchOut(lpOld);
	//lpOld->mpData=0;
	delete lpOld;
}


template<class T> void cLinkedList<T>::StitchIn(cLinkedNode<T> *lpNode)
{
lpNode->List(this);
if(mpStart && mpEnd)
{
	lpNode->mpPrev=mpEnd;
	mpEnd->mpNext=lpNode;

	lpNode->mpNext=0;
	mpEnd=lpNode;
}
else
{
	mpStart=lpNode;
	mpEnd=lpNode;
	lpNode->mpPrev=lpNode->mpNext=0;
}
	//++miSize;
}

template<class T> void cLinkedList<T>::StitchIn(cLinkedNode<T> *lpNode,cLinkedNode<T> *lpPos)
{
 lpNode->List(lpPos->mpList);
 if(lpPos->mpNext)
 {
  lpNode->mpPrev=lpPos;
  lpNode->mpNext=lpPos->mpNext;

  lpNode->mpNext->mpPrev=lpNode;
  lpPos->mpNext=lpNode;
 }
 else
 {
  lpNode->mpNext=0;
  lpNode->mpPrev=lpPos;
  lpPos->mpNext=lpNode;
  mpEnd=lpNode;
 }

}

template<class T> cLinkedList<T>::cLinkedList(T *lpData)
{
//  cLinkedNode<T> *mpTemp;
	Initialise();
	mpTemp=new cLinkedNode<T>(lpData);
	StitchIn(mpTemp);
	//mpTemp->mpData=lpData;

//	mpTemp=0;

	//miSize=1;Empty
}

template<class T> cLinkedNode<T> *cLinkedList<T>::Insert(T *lpData)
{

	mpTemp=new cLinkedNode<T>(lpData);
	StitchIn(mpTemp);
	//mpTemp->mpData=lpData;

	//++miSize;
	return mpTemp;
}

template<class T> cLinkedNode<T> *cLinkedList<T>::Insert(T *lpData,cLinkedNode<T> *lpPos)
{
	if(lpPos)
	{
		mpTemp=new cLinkedNode<T>(lpData);
		StitchIn(mpTemp,lpPos);
		return mpTemp;
	}
	else
	{
		mpTemp=new cLinkedNode<T>(lpData);
		mpTemp->List(this);
		if(mpStart)
		{
			mpTemp->mpNext=mpStart;
			mpStart->mpPrev=mpTemp;
			mpStart=mpTemp;
		}
		else
		{
			mpStart=mpTemp;
			mpEnd=mpTemp;
			mpTemp->mpPrev=mpTemp->mpNext=0;
		}
		return mpTemp;
	}
}

template<class T> void cLinkedList<T>::Display()
{
 printf("Linked List::Display()\n");
 if(mpStart)
 {
 mpTemp=Start();
 printf("Start : %p\n",mpStart);
 while(mpTemp->Next())
 {
  printf("Next : %p\n",mpTemp->Next());
  mpTemp=mpTemp->Next();
 }
 printf("Linked List::Display() Ended\nI Hope You enjoyed the show\n");
 }
 else printf("LinkedList::Empty\n");
}

#endif
