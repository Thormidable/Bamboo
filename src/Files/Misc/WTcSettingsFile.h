#ifndef __WTCSETTINGSFILE_H__
#define __WTCSETTINGSFILE_H__

class cSettingsStore;

template <class tType> class cSettingsValue
{
friend class cSettingsStore;
 string msName;
 tType mfValue;
public:
	bool Name(string lsName)
	{
	     return lsName==msName;
	};
	tType Value()
	{
	    return mfValue;
	};
	void SetValue(tType lfVal)
	{
        mfValue=lfVal;
	}

	void Set(string lsName,tType lfValue)
	{
	    msName=lsName;
	    mfValue=lfValue;
	}
};

template <class tType> class cSettingsArray
{
friend class cSettingsStore;
 string msName;
 tType *mpValue;
 uint32 miItems;
public:

	cSettingsArray()
	{
		mpValue=0;
		miItems=0;
	};
	bool Name(string lsName)
	{
	     return lsName==msName;
	};
	tType *Value()
	{
	    return mpValue;
	};
    uint32 Items()
    {
        return miItems;
    }
    void Set(string lsName, uint32 liItems,tType *lfValue)
    {
        msName=lsName;
        miItems=liItems;
        if(mpValue) delete []mpValue;
        mpValue=new tType[liItems];
        memcpy(mpValue,lfValue,sizeof(tType)*liItems);
    }

    void SetPointer(string lsName, uint32 liItems,tType *lfValue)
    {
        msName=lsName;
        miItems=liItems;
        if(mpValue) delete []mpValue;
        mpValue=new tType[liItems];
        for(uint32 liCount=0;liCount<liItems;++liCount)
        {
            mpValue[liCount]=lfValue[liCount];
        }
    }
};



class cSettingsStore
{
 cLimitedPointerList<cSettingsValue<float> > *mpFloats;
 cLimitedPointerList<cSettingsValue<int32> > *mpInts;
 cLimitedPointerList<cSettingsValue<string> > *mpStrings;
 cLimitedPointerList<cSettingsArray<int32> > *mpIntArrays;
 cLimitedPointerList<cSettingsArray<float> > *mpFloatArrays;
 cLimitedPointerList<cSettingsArray<string> > *mpStringArrays;

 ofstream mcFileStream;

 static cSettingsStore *mpInstance;
 cSettingsStore();
public:
 float GetFloat(string lsName);
 int32 GetInt(string lsName);
 string GetString(string lsName);
 int32 *GetIntArray(string lsName);
 float *GetFloatArray(string lsName);
 string *GetStringArray(string lsName);
 cSettingsArray<int32> *GetIntArrayObject(string lsName);
 cSettingsArray<float> *GetFloatArrayObject(string lsName);
 cSettingsArray<string> *GetStringArrayObject(string lsName);

 uint32 HasFloat(string lsName);
 uint32 HasInt(string lsName);
 uint32 HasString(string lsName);
 uint32 HasIntArray(string lsName);
 uint32 HasFloatArray(string lsName);
 uint32 HasStringArray(string lsName);

 void AddFloat(string lsName,float lfValue);
 void AddString(string lsName,string lfValue);
 void AddInt(string lsName,int32 lfValue);
 void AddIntArray(string lsName,uint32 liItems,int32 *lpValues);
 void AddFloatArray(string lsName,uint32 liItems,float *lpValues);
 void AddStringArray(string lsName,uint32 liItems,string *lpValues);

 void Load(const char *lpPath);
 void Output(string lpPath);
 void PrepareOutput(string lpPath);
 void OutputFloat(string lsName);
 void OutputInt(string lsName);
 void OutputString(string lsName);
 void OutputFloatArray(string lsName);
 void OutputIntArray(string lsName);
 void OutputStringArray(string lsName);
 void CloseOutput();
 static cSettingsStore *Instance();
};


#endif
