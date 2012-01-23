#ifndef __WTLIMITEDLIST_H__
#define __WTLIMITEDLIST_H__

/**
* \brief Template class for creating 'dynamic' arrays using static arrays.
* This is best used for arrays which will not change size often, but requires the properties of a static array.
* Creates an array of type cX which can be accessed and used as if it were a static array.
* The User can change the size of the array as required.
* Will also expand the array to accomodated added items as required.
* Changing the array size has a fixed CPU cost so it is best managed by the user to keep array size changes to a minimum.
**/
template <class cX> class cLimitedList
{
protected:

public:

	cX *mpList;
	uint32 miSpaces;
	uint32 miItems;
    ///This will change the size of the list.
	void ChangeSize(uint32 liSize)
	{
	    if(!liSize || !mpList)
	    {
	        Init(liSize);
	    }
        else
        {
            cX *lpTemp;
            lpTemp=new cX[liSize];
            if(miItems>liSize)	miItems=liSize;
            memcpy(lpTemp,mpList,sizeof(cX)*miItems);

            miSpaces=liSize;
            delete []mpList;
            mpList=lpTemp;
        }

	};

    ///Constructor for producing a 0 length List
	cLimitedList(){mpList=0;miItems=0;miSpaces=0;};

    ///Will initialise the array to the size of liSpaces.This will destroy any data in the array.
	void Init(uint32 liSpaces)
	{
        if(!miSpaces) miSpaces=5;
		delete []mpList;
		miSpaces=liSpaces;
		mpList=new cX[miSpaces];

		memset(mpList,0,sizeof(cX)*miSpaces);

		miItems=0;
	}

    ///Constructor which will produce an array of length liSpaces.
	cLimitedList(uint32 liSpaces)
	{
		mpList=0;
		miSpaces=0;
		//miItems=0;
		Init(liSpaces);
	};

	///Destructor. This will destroy the objects in the array.
	~cLimitedList()
	{

		delete []mpList;
		mpList=0;
	};

    /// [] operator to allow access of any item as if it were a normal array.
	cX &operator[](uint32 liItem){return mpList[liItem];};

    /// = operator to allow copying a cLimitedList array.
    ///This SHOULD NOT be used with cX classes containing pointers.
	cLimitedList<cX> &operator=(cLimitedList<cX> &lpOther)
	{

		delete []mpList;
		miSpaces=lpOther.miSpaces;
		miItems=lpOther.miItems;
		mpList=new cX[miSpaces];

		memcpy(mpList,lpOther.mpList,sizeof(cX)*miItems);

		return this[0];
	};

	///Returns the number of items this array can currently hold.
	uint32 Spaces(){return miSpaces;};
	///Returns the number of items this array is currently holding.
	uint32 Items(){return miItems;};
	///Sets the number of items this array is currently holding. Should be used with caution.
	void SetItems(uint32 liItems){miItems=liItems;};

    ///Will copy the item pointed to by lpTemp to the array. Note this copies the item. It does not take the item into the array. Add will expand the array if required to add the item.
	void Add(cX *lpTemp){if(miItems>=miSpaces) ChangeSize(miSpaces*1.5); memcpy(&mpList[miItems++],lpTemp,sizeof(cX));};

    ///Will Remove the item in position liPos from the array. All items after the removed item will be shuffled down the array, so all data is continuously at the start of the array.
	void Remove(uint32 liPos)
	{
		--miItems;
		if(liPos<miItems)
		{
			memmove(&mpList[liPos],&mpList[liPos+1],sizeof(cX)*(miItems-liPos));
		}

	};
    ///Will switch the items in positions li1 and li2 in the array.
	void SwitchItems(uint32 li1,uint32 li2)
	{
		if(li1<miItems && li2<miItems && li1!=li2)
		{
		cX lpTemp;
		lpTemp=mpList[li1];
		mpList[li1]=mpList[li2];
		mpList[li2]=lpTemp;
		}
	};
};

/**
* \brief This is similar to the cLimitedList template class, but will uses pointers.
* The type cX is the base type. When a pointer is handed to the array, the list will store the pointer to the item and 'take ownership' of the object.
* This means that the item is NOT copied and when the list is deleted Items 'owned' to by the list will be deleted.
* This also makes array manipulation and size changing quicker. It will expand to accomodate new items added to the array.
*/
template<class cX> class cLimitedPointerList
{
protected:
	cX **mpList;
	uint32 miSpaces;
	uint32 miItems;
public:
    ///Constructor to create a new array of size liSpaces
	cLimitedPointerList(uint32 liSpaces)
	{
		miSpaces=liSpaces;
		miItems=0;
		mpList=new cX*[miSpaces];
	};
	///Constructor to create a 0 length array
	cLimitedPointerList(){mpList=0;miItems=0;miSpaces=0;};

    ///This will initialise the array to size liSpaces
	void Init(uint32 liSpaces)
	{
        if(!miSpaces) miSpaces=5;
		DeleteAll();
		miSpaces=liSpaces;
		mpList=new cX*[miSpaces];

		memset(mpList,0,sizeof(cX*)*miSpaces);

		miItems=0;
	};
    ///This will change the array size to liSize. Pointers will be copied across. If the new array is too short to store all the data. The excess objects will be deleted.
	void ChangeSize(uint32 liSize)
	{
	    if(!liSize || !mpList)
	    {
	        Init(liSize);
	    }
        else
        {
            cX **lpTemp;
            lpTemp=new cX*[liSize];

            while(miItems>liSize)
            {
                delete mpList[miItems];
                mpList[miItems]=0;
                --miItems;
            }

            memcpy(lpTemp,mpList,sizeof(cX*)*miItems);

            miSpaces=liSize;
            delete []mpList;
            mpList=lpTemp;
        }
	};
	uint32 Items(){return miItems;};
	uint32 Spaces(){return miSpaces;};
	///This will delete all items in the list. Clear the list to size 0. It will not delete this list object.
    void DeleteAll()
    {
		if(mpList)
		{
			uint32 liCount;
			for(liCount=0;liCount<miItems;++liCount); delete mpList[liCount];
        	delete []mpList;
			mpList=0;
		}
		miItems=0;
		miSpaces=0;
    }
    ///Deconstructor for this list object. This will calll DeleteAll()
	~cLimitedPointerList()
	{
        DeleteAll();
	};
    /// [] operatr to allow this to be used like a pointer array.
	cX *operator[](uint32 liItem){return mpList[liItem];};
	/// Will return the pointer at position liItem in the list.
	cX *Item(uint32 liItem){return mpList[liItem];};

    void ZeroItem(uint32 liItem){mpList[liItem]=0;};

    void SetItems(uint32 liItems){if(liItems<miSpaces) miItems=liItems; else miItems=miSpaces;};

	cX **ArrayPos(uint32 liItem){return mpList+liItem;};
	/// Will Add the pointer lpValue to the list. Once added the Array will control deleting the object pointed to by lpValue. It will also expand the array to acomodate the item as required.
	void Add(cX *lpValue){if(miItems>=miSpaces) ChangeSize(miSpaces*1.5); mpList[miItems++]=lpValue;};
	/// This will remove the item liPos from the List. It will delete the item and shuffle all the other items in teh list to the front of the list.
	void Remove(uint32 liPos)
	{
		if (mpList[liPos] && liPos<miItems)
		{
			delete mpList[liPos]; mpList[liPos]=0;
			--miItems;
			memmove(mpList[liPos],mpList[liPos+2],sizeof(cX*)*miItems-liPos);
		}
	};
    ///This will switch the positions of the items at positions li1 and li2 in the list.
	void SwitchItems(uint32 li1,uint32 li2)
	{
		if(li1<miItems && li2<miItems && li1!=li2)
		{
		cX *lpTemp;
		lpTemp=mpList[li1];
		mpList[li1]=mpList[li2];
		mpList[li2]=lpTemp;
		}
	};

    void Remove(cX* lpItem)
    {
        int32 liCheck=GetItemPos(lpItem);
        if(liCheck>=0) Remove(liCheck);
    };

	int32 GetItemPos(cX* lpItem)
	{
	    uint32 liCount;
	    for(liCount=0;liCount<miItems;++liCount)
	    {
	        if(mpList[liCount]==lpItem) return liCount;
	    }
	    return -1;
	};
};

#endif
