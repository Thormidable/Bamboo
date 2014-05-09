#include "stdafx.h"
#include "../../WTBamboo.h"

cSettingsStore *cSettingsStore::mpInstance=0;
/*
bool cSettingsValue::Name(string lsName)
{
 return lsName==msName;
};

float cSettingsFloat::Value(){return mfValue;};

int32 cSettingsInt::Value(){return mfValue;};

string cSettingsString::Value(){return mfValue;};
*/
cSettingsStore::cSettingsStore()
{
 mpFloats=0;
 mpInts=0;
 mpStrings=0;
 mpIntArrays=0;
 mpFloatArrays=0;
 mpStringArrays=0;
};

cSettingsStore *cSettingsStore::Instance()
{
 if(!mpInstance) mpInstance=new cSettingsStore;
 return mpInstance;
};

void cSettingsStore::Load(const char *lpPath)
{
	TRACE("Load Settings File " << lpPath);

	ifstream FileStream;
	FileStream.open(lpPath,ios::binary);

	if(!FileStream.is_open())
	{
		string msg("Couldn't open Settings File ");
		msg=msg+lpPath;
		TRACE(msg);
		throw CException(msg);
	}

	cParser lcData;
	uint32 liSize=100;
	uint32 liCount=0;
	char *lcString=new char[100];
	char *lcCursor;
	while(!FileStream.eof())
	{
	 FileStream.read(&lcString[liCount++],1);
	 if(liCount==liSize)
	 {
		lcCursor=lcString;
		lcString=new char[liSize+100];
		memcpy(lcString,lcCursor,liSize);
		liSize+=100;
		delete []lcCursor;
	 }
	}

	lcString[liCount-1]=0;

	FileStream.close();

	lcCursor=lcString;
	char EOLChar;
	if(FindOn(lcString,0x0A)) EOLChar=0x0A;
	else EOLChar=0x0D;
 	do
	{
		if(lcData.ParseString(lcCursor,"%R %v%R :%R %S%[,%S%]%z"))
		{
			if(!mpStringArrays) {mpStringArrays=new cLimitedPointerList<cSettingsArray<string> >(5);}

			AddStringArray(lcData.GetString(0),lcData.StringNumber(),lcData.Strings());

			lcCursor=FindOn(lcCursor,EOLChar);
			if(!lcCursor) break;
			++lcCursor;
			continue;
		};

		if(lcData.ParseString(lcCursor,"%R %v%R :%R %i%[,%i%]%z"))
		{
			if(!mpIntArrays) {mpIntArrays=new cLimitedPointerList<cSettingsArray<int32> >(5);}

			AddIntArray(lcData.GetString(0),lcData.IntNumber(),lcData.Ints());

			lcCursor=FindOn(lcCursor,EOLChar);
			if(!lcCursor) break;
			++lcCursor;
			continue;
		};

	    if(lcData.ParseString(lcCursor,"%R %v%R :%R %f%[,%f%]%z"))
		{
			if(!mpFloatArrays) {mpFloatArrays=new cLimitedPointerList<cSettingsArray<float> >(5);}

			AddFloatArray(lcData.GetString(0),lcData.FloatNumber(),lcData.Floats());

			lcCursor=FindOn(lcCursor,EOLChar);
			if(!lcCursor) break;
			++lcCursor;
			continue;
		};



        if(lcData.ParseString(lcCursor,"%R %v%R :%R %v%[,%v%]%z"))
		{
			if(!mpStringArrays) {mpStringArrays=new cLimitedPointerList<cSettingsArray<string> >(5);}

			AddStringArray(lcData.GetString(0),lcData.StringNumber(),lcData.Strings());

			lcCursor=FindOn(lcCursor,EOLChar);
			if(!lcCursor) break;
			++lcCursor;
			continue;
		};

		if(lcData.ParseString(lcCursor,"%R %v%R :%R %S%z"))
		{
			if(!mpStrings) {mpStrings=new cLimitedPointerList<cSettingsValue<string> >(5);}
			AddString(lcData.GetString(0),lcData.GetString(1));

			lcCursor=FindOn(lcCursor,EOLChar);
			if(!lcCursor) break;
			++lcCursor;
			continue;
		};

		if(lcData.ParseString(lcCursor,"%R %v%R :%R %i%!.%z"))
		{
			if(!mpInts) {mpInts=new cLimitedPointerList<cSettingsValue<int32> >(5);}

			AddInt(lcData.GetString(0),lcData.GetInt(0));

			lcCursor=FindOn(lcCursor,EOLChar);
			if(!lcCursor) break;
			++lcCursor;
			continue;
		};

		if(FindOnString(lcCursor,'.') && lcData.ParseString(lcCursor,"%R %v%R :%R %f%z"))
		{
			if(!mpFloats) {mpFloats=new cLimitedPointerList<cSettingsValue<float> >(5);}

			AddFloat(lcData.GetString(0),lcData.GetFloat(0));

			lcCursor=FindOn(lcCursor,EOLChar);
			if(!lcCursor) break;
			++lcCursor;
			continue;
		};



		if(lcData.ParseString(lcCursor,"%R %v%R :%R %v%z"))
		{
			if(!mpStrings) {mpStrings=new cLimitedPointerList<cSettingsValue<string> >(5);}
			AddString(lcData.GetString(0),lcData.GetString(1));

			lcCursor=FindOn(lcCursor,EOLChar);
			if(!lcCursor) break;
			++lcCursor;
			continue;
		};

         lcCursor=FindOn(lcCursor,EOLChar);
         if(!lcCursor) break;
         ++lcCursor;
	} while(lcCursor[0]);

	delete []lcString;
}

float cSettingsStore::GetFloat(string lsName)
{
 if(mpFloats)
 {
	for(uint32 liCount=0;liCount<mpFloats->Items();++liCount)
	{
		if(mpFloats->Item(liCount)->Name(lsName)) return mpFloats->Item(liCount)->Value();
	}
 }
 return 0.0f;
};


int32 cSettingsStore::GetInt(string lsName)
{
 if(mpInts)
 {
	for(uint32 liCount=0;liCount<mpInts->Items();++liCount)
	{
		if(mpInts->Item(liCount)->Name(lsName)) return mpInts->Item(liCount)->Value();
	}
 }
 return 0;
};

string cSettingsStore::GetString(string lsName)
{
 if(mpStrings)
 {
	for(uint32 liCount=0;liCount<mpStrings->Items();++liCount)
	{
		if(mpStrings->Item(liCount)->Name(lsName)) return mpStrings->Item(liCount)->Value();
	}
 }
 return "";

};

uint32 cSettingsStore::HasFloat(string lsName)
{
 if(mpFloats)
 {
	for(uint32 liCount=0;liCount<mpFloats->Items();++liCount)
	{
		if(mpFloats->Item(liCount)->Name(lsName)) return liCount;
	}
 }
 return 0;
};

uint32 cSettingsStore::HasInt(string lsName)
{
 if(mpInts)
 {
	for(uint32 liCount=0;liCount<mpInts->Items();++liCount)
	{
		if(mpInts->Item(liCount)->Name(lsName)) return liCount;
	}
 }
 return 0;
};

uint32 cSettingsStore::HasIntArray(string lsName)
{
 if(mpIntArrays)
 {
	for(uint32 liCount=0;liCount<mpIntArrays->Items();++liCount)
	{
		if(mpIntArrays->Item(liCount)->Name(lsName)) return liCount;
	}
 }
 return 0;
};

uint32 cSettingsStore::HasFloatArray(string lsName)
{
 if(mpFloatArrays)
 {
	for(uint32 liCount=0;liCount<mpFloatArrays->Items();++liCount)
	{
		if(mpFloatArrays->Item(liCount)->Name(lsName)) return liCount;
	}
 }
 return 0;
};

uint32 cSettingsStore::HasStringArray(string lsName)
{
 if(mpStringArrays)
 {
	for(uint32 liCount=0;liCount<mpStringArrays->Items();++liCount)
	{
		if(mpStringArrays->Item(liCount)->Name(lsName)) return liCount;
	}
 }
 return 0;
};

uint32 cSettingsStore::HasString(string lsName)
{
if(mpStrings)
 {
	for(uint32 liCount=0;liCount<mpStrings->Items();++liCount)
	{
		if(mpStrings->Item(liCount)->Name(lsName)) return liCount;
	}
 }
 return 0;
};


 void cSettingsStore::AddIntArray(string lsName,uint32 liItems,int32 *lfValue)
 {
    cSettingsArray<int32> *lpTemp;
	uint32 liPos=HasIntArray(lsName);
	if(!liPos) lpTemp=new cSettingsArray<int32>;
	else lpTemp=mpIntArrays->Item(liPos);

	lpTemp->Set(lsName,liItems,lfValue);
    mpIntArrays->Add(lpTemp);

	TRACE("Add IntArray : " << lsName << " : " << liItems << " : ");
 };


 void cSettingsStore::AddFloatArray(string lsName,uint32 liItems,float *lfValue)
 {
    cSettingsArray<float> *lpTemp;
	uint32 liPos=HasFloatArray(lsName);
	if(!liPos) lpTemp=new cSettingsArray<float>;
	else lpTemp=mpFloatArrays->Item(liPos);

	lpTemp->Set(lsName,liItems,lfValue);
	mpFloatArrays->Add(lpTemp);

	TRACE("Add FloatArray : " << lsName << " : " << liItems << " : ");
 };


 void cSettingsStore::AddStringArray(string lsName,uint32 liItems,string *lfValue)
 {
    cSettingsArray<string> *lpTemp;
	uint32 liPos=HasStringArray(lsName);
	if(!liPos) lpTemp=new cSettingsArray<string>;
	else lpTemp=mpStringArrays->Item(liPos);

	lpTemp->SetPointer(lsName,liItems,lfValue);
	mpStringArrays->Add(lpTemp);

	TRACE("Add StringArray : " << lsName << " : " << liItems << " : ");
 };

 void cSettingsStore::AddFloat(string lsName,float lfValue)
 {
	uint32 liPos=HasFloat(lsName);
	if(liPos)
	{
		mpFloats->Item(liPos)->mfValue=lfValue;
		return;
	}
    cSettingsValue<float> *lpTemp=new cSettingsValue<float>;
    lpTemp->msName=lsName;
    lpTemp->mfValue=lfValue;
	mpFloats->Add(lpTemp);

	TRACE("Add Float : " << lsName << " : " << lfValue);
 };
 void cSettingsStore::AddString(string lsName,string lfValue)
 {
	uint32 liPos=HasString(lsName);
	if(liPos)
	{
		mpStrings->Item(liPos)->mfValue=lfValue;
		return;
	}

    cSettingsValue<string> *lpTemp=new cSettingsValue<string>;
    lpTemp->msName=lsName;
    lpTemp->mfValue=lfValue;
	mpStrings->Add(lpTemp);

	TRACE("Add String : " << lsName << " : " << lfValue);
 };
 void cSettingsStore::AddInt(string lsName,int32 lfValue)
 {
	uint32 liPos=HasInt(lsName);
	if(liPos)
	{
		mpInts->Item(liPos)->mfValue=lfValue;
		return;
	}
    cSettingsValue<int32> *lpTemp=new cSettingsValue<int32>;
    lpTemp->msName=lsName;
    lpTemp->mfValue=lfValue;
	mpInts->Add(lpTemp);

	TRACE("Add Int : " << lsName << " : " << lfValue);
 };

void cSettingsStore::Output(string lpPath)
{
 mcFileStream.open(lpPath.c_str(),ios::trunc);
 mcFileStream.precision(5);

 if(mpFloats) for(uint32 liCount=0;liCount<mpFloats->Items();++liCount) mcFileStream << fixed << mpFloats->Item(liCount)->msName << " : " << mpFloats->Item(liCount)->mfValue << endl;
 if(mpInts) for(uint32 liCount=0;liCount<mpInts->Items();++liCount) mcFileStream << mpInts->Item(liCount)->msName << " : " << mpInts->Item(liCount)->mfValue << endl;
 if(mpStrings) for(uint32 liCount=0;liCount<mpStrings->Items();++liCount) mcFileStream << mpStrings->Item(liCount)->msName << " : " << '"' << mpStrings->Item(liCount)->mfValue << '"' << endl;
 if(mpIntArrays) for(uint32 liCount=0;liCount<mpIntArrays->Items();++liCount)
 {
	 int32 *lpTemp=mpIntArrays->Item(liCount)->Value();
	 uint32 liTotal=mpIntArrays->Item(liCount)->Items();

	 mcFileStream << mpStrings->Item(liCount)->msName << " : " << lpTemp[0];
	for(uint32 liItem=1;liItem<liTotal;++liItem)
	{
		 mcFileStream << ',' << lpTemp[liItem];
	}
	mcFileStream << endl;
 }
 if(mpFloatArrays) for(uint32 liCount=0;liCount<mpFloatArrays->Items();++liCount)
 {
	 float *lpTemp=mpFloatArrays->Item(liCount)->Value();
	 uint32 liTotal=mpFloatArrays->Item(liCount)->Items();

	 mcFileStream << mpStrings->Item(liCount)->msName << " : " << lpTemp[0];

	for(uint32 liItem=1;liItem<liTotal;++liItem)
	{
		 mcFileStream << ',' << lpTemp[liItem];
	}
	mcFileStream << endl;
 }
 if(mpStringArrays) for(uint32 liCount=0;liCount<mpStringArrays->Items();++liCount)
 {
	 string *lpTemp=mpStringArrays->Item(liCount)->Value();
	 uint32 liTotal=mpStringArrays->Item(liCount)->Items();

	 mcFileStream << mpStrings->Item(liCount)->msName << " : " << '"' << lpTemp[0];
	for(uint32 liItem=1;liItem<liTotal;++liItem)
	{
		 mcFileStream << ',' << lpTemp[liItem];
	}
	mcFileStream << '"' << endl;
 }
 mcFileStream.close();
};

void cSettingsStore::PrepareOutput(string lpPath)
{
 mcFileStream.open(lpPath.c_str(),ios::trunc);
 mcFileStream.precision(5);
}

void cSettingsStore::OutputFloat(string lsName)
{
	mcFileStream << fixed << lsName << " : " << GetFloat(lsName.c_str()) << endl;
}

void cSettingsStore::OutputInt(string lsName)
{
	mcFileStream << fixed << lsName << " : " << GetInt(lsName.c_str()) << endl;
}

void cSettingsStore::OutputString(string lsName)
{
	mcFileStream << fixed << lsName << " : " << '"' << GetString(lsName.c_str()) << '"' << endl;
}

void cSettingsStore::OutputStringArray(string lsName)
{
	cSettingsArray<string> *lpObj=GetStringArrayObject(lsName);

	 string *lpTemp=lpObj->Value();
	 uint32 liTotal=lpObj->Items();

	mcFileStream << lpObj->msName << " : " << '"' << lpTemp[0];
	for(uint32 liItem=1;liItem<liTotal;++liItem)
	{
		 mcFileStream << ',' << lpTemp[liItem];
	}
	mcFileStream << '"' << endl;
}

void cSettingsStore::OutputIntArray(string lsName)
{
	cSettingsArray<int32> *lpObj=GetIntArrayObject(lsName);

	 int32 *lpTemp=lpObj->Value();
	 uint32 liTotal=lpObj->Items();

	mcFileStream << lpObj->msName << " : " << lpTemp[0];
	for(uint32 liItem=1;liItem<liTotal;++liItem)
	{
		 mcFileStream << ',' << lpTemp[liItem];
	}
	mcFileStream << endl;
}

void cSettingsStore::OutputFloatArray(string lsName)
{
	cSettingsArray<float> *lpObj=GetFloatArrayObject(lsName);

	 float *lpTemp=lpObj->Value();
	 uint32 liTotal=lpObj->Items();

	mcFileStream << lpObj->msName << " : " << lpTemp[0];
	for(uint32 liItem=1;liItem<liTotal;++liItem)
	{
		 mcFileStream << ',' << lpTemp[liItem];
	}
	mcFileStream << endl;
}

void cSettingsStore::CloseOutput()
{
 mcFileStream.close();
}


int32 *cSettingsStore::GetIntArray(string lsName)
{
   if(mpIntArrays)
 {
	for(uint32 liCount=0;liCount<mpIntArrays->Items();++liCount)
	{
		if(mpIntArrays->Item(liCount)->Name(lsName)) return mpIntArrays->Item(liCount)->mpValue;
	}
 }
 return 0;
};

cSettingsArray<int32> *cSettingsStore::GetIntArrayObject(string lsName)
{
   if(mpIntArrays)
 {
	for(uint32 liCount=0;liCount<mpIntArrays->Items();++liCount)
	{
		if(mpIntArrays->Item(liCount)->Name(lsName)) return mpIntArrays->Item(liCount);
	}
 }
 return 0;
};

float *cSettingsStore::GetFloatArray(string lsName)
{
   if(mpFloatArrays)
 {
	for(uint32 liCount=0;liCount<mpFloatArrays->Items();++liCount)
	{
		if(mpFloatArrays->Item(liCount)->Name(lsName)) return mpFloatArrays->Item(liCount)->mpValue;
	}
 }
 return 0;
};

cSettingsArray<float> *cSettingsStore::GetFloatArrayObject(string lsName)
{
   if(mpFloatArrays)
 {
	for(uint32 liCount=0;liCount<mpFloatArrays->Items();++liCount)
	{
		if(mpFloatArrays->Item(liCount)->Name(lsName)) return mpFloatArrays->Item(liCount);
	}
 }
 return 0;
};

string *cSettingsStore::GetStringArray(string lsName)
{
   if(mpStringArrays)
 {
	for(uint32 liCount=0;liCount<mpStringArrays->Items();++liCount)
	{
		if(mpStringArrays->Item(liCount)->Name(lsName)) return mpStringArrays->Item(liCount)->mpValue;
	}
 }
 return 0;
};

cSettingsArray<string> *cSettingsStore::GetStringArrayObject(string lsName)
{
   if(mpStringArrays)
 {
	for(uint32 liCount=0;liCount<mpStringArrays->Items();++liCount)
	{
		if(mpStringArrays->Item(liCount)->Name(lsName)) return mpStringArrays->Item(liCount);
	}
 }
 return 0;
};
