#ifndef __WTLIMITEDLIST_H__
#define __WTLIMITEDLIST_H__


template <class cX> class cLimitedList
{
protected:
	
public:

	cX *mpList;
	uint32 miSpaces;
	uint32 miItems;

	void ChangeSize(uint32 liSize)
	{
		
		cX *lpTemp;
		lpTemp=new cX[liSize];
		if(miItems>liSize)	miItems=liSize;
		memcpy(lpTemp,mpList,sizeof(cX)*miItems);
		
		miSpaces=liSize;
		delete []mpList;
		mpList=lpTemp;
		
	}
	
	cLimitedList(){mpList=0;miItems=0;};
	
	void Init(uint32 liSpaces)
	{
		
		delete []mpList;
		miSpaces=liSpaces;
		mpList=new cX[miSpaces];
		
		memset(mpList,0,sizeof(cX)*miSpaces);
		
		miItems=0;
	}

	cLimitedList(uint32 liSpaces)
	{
		mpList=0;
		Init(liSpaces);
	};
	~cLimitedList()
	{
		
		delete []mpList;
		mpList=0;
	};
	
	cX &operator[](uint32 liItem){return mpList[liItem];};
	
	cLimitedList<cX> &operator=(cLimitedList<cX> &lpOther)
	{
		//This SHOULD NOT be used with cX classes containing pointers
		
		delete []mpList;
		miSpaces=lpOther.miSpaces;
		miItems=lpOther.miItems;
		mpList=new cX[miSpaces];
		
		memcpy(mpList,lpOther.mpList,sizeof(cX)*miItems);
		
		return this[0];
	};
	uint32 Spaces(){return miSpaces;};
	uint32 Items(){return miItems;};
	void SetItems(uint32 liItems){miItems=liItems;};
	
	void Add(cX *lpTemp){memcpy(&mpList[miItems++],lpTemp,sizeof(cX));};
	
	void Remove(uint32 liPos)
	{
		--miItems;
		if(liPos<miItems)
		{
			memmove(&mpList[liPos],&mpList[liPos+1],sizeof(cX)*(miItems-liPos));
		}
		
	};

	void SwitchItems(uint32 li1,uint32 li2)
	{
		if(li1<miItems && li2<miItems && li1!=li2)
		{
		// cX *lpTemp;
		//lpTemp=new cX;
		//memcpy(lpTemp,&mpList[li1],sizeof(cX));
		//memcpy(&mpList[li1],&mpList[li2],sizeof(cX));
		//memcpy(&mpList[li2],&lpTemp,sizeof(cX));
		//delete lpTemp;
		cX lpTemp;
		lpTemp=mpList[li1];
		mpList[li1]=mpList[li2];
		mpList[li2]=lpTemp;
		
		
		
		}
	};
};


template<class cX> class cLimitedPointerList
{
	cX **mpList;
	uint32 miSpaces;
	uint32 miItems;
public:
	cLimitedPointerList(uint32 liSpaces)
	{
		miSpaces=liSpaces;
		miItems=0;
		mpList=new cX*[miSpaces];
	};
	~cLimitedPointerList()
	{
		uint32 liCount;
		for(liCount=0;liCount<miItems;++liCount); delete []mpList[liCount];
			      delete []mpList;
		mpList=0;
	};
	
	cX *operator[](uint32 liItem){return mpList[liItem];};
	cX *Item(uint32 liItem){return mpList[liItem];};
	void Add(cX *lpValue){mpList[miItems++]=lpValue;};
	void Remove(uint32 liPos)
	{
		if (mpList[liPos] && liPos<miItems)
		{
			delete []mpList[liPos]; mpList[liPos]=0;
			--miItems;
			memmove(mpList[liPos],mpList[liPos+2],sizeof(cX*)*miItems-liPos);
			//memcpy(mpList[liPos],mpList[liPos+2],sizeof(cX*)*miItems-liPos);
		}
	};
};

#endif
