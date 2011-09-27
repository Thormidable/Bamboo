#ifndef __MINLINKEDLIST_H__
#define __MINLINKEDLIST_H__

template<class T> class cMinLL;

/// Linked Nodes Lite. I'm not sure I use this. But quick small and simple templated Linked List nodes.
template<class T> class cMinLN
{
friend class cMinLL<T>;

 cMinLN *mpNext;
 cMinLN *mpPrev;

public:
 T *mpData;
       cMinLN<T> *Next(){return mpNext;}
       cMinLN<T> *Previous(){return mpPrev;}
};

/// Linked List Lite. I'm not sure I use this. But quick small and simple templated Linked List.
template<class T> class cMinLL
{
public:
       cMinLL(T *lpData);

        ~cMinLL()
        {
         mpCursor=mpStart;
         while(mpCursor->mpNext)
         {
           mpCursor=mpCursor->mpNext;
           delete mpCursor->mpPrev;
           --miSize;
         }
        delete mpCursor;
         --miSize;

        };

       cMinLN<T> *mpStart;
       cMinLN<T> *mpEnd;
       cMinLN<T> *mpCursor;
       static cMinLN<T> *mpTemp;

	uint32 miSize;
	uint32 Size(){return miSize;};

      

       //Insert New item at a location this is Before the location (to include 0)
       cMinLN<T> *Insert(int liN,T *lpData);
       cMinLN<T> *InsertE(T *lpData);
       cMinLN<T> *InsertB(T *lpData);

       //Delete Item at a certain location Cursor will move Forward if forced
       bool Delete(int liN);
       bool Delete(cMinLN<T> *lpOld);
       
       void Sleep(cMinLN<T> *lpOld);
       void Wake(int liN,cMinLN<T> *lpOld);

       void Output();

};

template<class T> cMinLN<T> *cMinLL<T>::mpTemp;

template<class T> bool cMinLL<T>::Delete(cMinLN<T> *lpOld)
{
 if (mpCursor==lpOld) mpCursor=mpCursor->mpNext;

  if (lpOld->mpNext) {lpOld->mpNext->mpPrev=lpOld->mpPrev;}
  //else at Start
  else {mpEnd=lpOld->mpPrev; mpEnd->mpNext=0;}

  if (lpOld->mpPrev){lpOld->mpPrev->mpNext=lpOld->mpNext; delete lpOld;}
  //else at End
  else {mpStart=lpOld->mpNext; mpStart->mpPrev=0; delete lpOld;}

  --miSize;

 return true;
}

template<class T> void cMinLL<T>::Sleep(cMinLN<T> *lpOld)
{
 if (mpCursor==lpOld) mpCursor=mpCursor->mpNext;

  if (lpOld->mpNext) {lpOld->mpNext->mpPrev=lpOld->mpPrev;}
  //else at Start
  else {mpEnd=lpOld->mpPrev; mpEnd->mpNext=0;}

  if (lpOld->mpPrev){lpOld->mpPrev->mpNext=lpOld->mpNext;}
  //else at End
  else {mpStart=lpOld->mpNext; mpStart->mpPrev=0;}
  --miSize;
}

template<class T> void cMinLL<T>::Wake(int liN,cMinLN<T> *lpWake)
{

 if (liN>=miSize || liN<0) return 0;

 cMinLN<T> *lpIns=mpStart;

 while(liN)
 {
  lpIns=lpIns->mpNext;
  --liN;
 }

 lpWake->mpNext=lpIns;
 lpWake->mpPrev=lpIns->mpPrev;

 if (mpStart==lpIns)
 {
  mpStart=lpWake;
  lpWake->mpPrev=0;
 }
 else
 {
  lpWake->mpPrev=lpIns->mpPrev;
  lpIns->mpNext->mpPrev=lpIns;
 }

 lpIns->mpPrev=lpWake;
 ++miSize;
}

template<class T> cMinLL<T>::cMinLL(T *lpData)
        {mpStart=new cMinLN<T>;
         mpCursor=mpStart;
         mpEnd=mpStart;
         mpCursor->mpPrev=0;
         mpCursor->mpNext=0;
         mpCursor->mpData=lpData;
         miSize=0;
        }

template<class T> void cMinLL<T>::Output()
{
#if WT_OS_TYPE==OS_WIN32
 cMinLN<T> *lpCursor=mpStart;
 
 while(lpCursor!=mpEnd)
 {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
  if (lpCursor==mpCursor) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
  printf("Prev:%i  Cur:%i  Next:%i  Point:%i\n",lpCursor->mpPrev,lpCursor,lpCursor->mpNext,lpCursor->mpData);
  lpCursor=lpCursor->mpNext;
 }
 
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
  if (lpCursor==mpCursor) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);

  printf("Prev:%i  Cur:%i  Next:%i  Point:%i\n",lpCursor->mpPrev,lpCursor,lpCursor->mpNext,lpCursor->mpData);

SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

  printf("Size:%i\n\n",miSize);
#endif
#if WT_OS_TYPE==OS_LINUX

cMinLN<T> *lpCursor=mpStart;
 
 while(lpCursor!=mpEnd)
 {
  trace("Prev: "<< lpCursor->mpPrev << " Cur: "<< lpCursor << " Next: "<< lpCursor->mpNext << "Point: " << lpCursor->mpData);
  lpCursor=lpCursor->mpNext;
 }
 
 trace("Prev:" << lpCursor->mpPrev << "Cur: " <<lpCursor<< " Next: " << lpCursor->mpNext << " Point: "<< lpCursor->mpData);

 trace("Size: "<< miSize);

#endif

};

//This will insert Backwards.
template<class T> cMinLN<T> *cMinLL<T>::Insert(int liN,T *lpData)
{
 if (liN>=miSize || liN<0) return 0;
 
 cMinLN<T> *lpIns=mpStart;
 cMinLN<T> *lpNew=new cMinLN<T>;

 
 while(liN)
 {
  lpIns=lpIns->mpNext;
  --liN;
 }
 
 lpNew->mpNext=lpIns;
 lpNew->mpPrev=lpIns->mpPrev;
 
 if (mpStart==lpIns)
 {
  mpStart=lpNew;
  lpNew->mpPrev=0;
 }
 else
 {
  lpNew->mpPrev=lpIns->mpPrev;
  lpIns->mpNext->mpPrev=lpIns;
 }
 
 lpIns->mpPrev=lpNew;
 lpNew->mpData=lpData;
 ++miSize;
return lpNew;
}

template<class T> cMinLN<T> *cMinLL<T>::InsertE(T *lpData)
{

 cMinLN<T> *lpNew=new cMinLN<T>;

 lpNew->mpNext=0;
 mpEnd->mpNext=lpNew;
 
 lpNew->mpPrev=mpEnd;
 lpNew->mpData=lpData;
 mpEnd=lpNew;

 ++miSize;
return lpNew;
}

template<class T> cMinLN<T> *cMinLL<T>::InsertB(T *lpData)
{
 cMinLN<T> *lpNew=new cMinLN<T>;

 lpNew->mpPrev=0;
 mpStart->mpPrev=lpNew;

 lpNew->mpNext=mpStart;
 lpNew->mpData=lpData;
 mpStart=lpNew;

 ++miSize;
return lpNew;
}

//This will Delete Forwards
template<class T> bool cMinLL<T>::Delete(int liN)
{
 if (liN>miSize || liN<0) return false;
 mpTemp=mpStart;
 
 while (liN)
 {
  mpTemp=mpTemp->mpNext;
  --liN;
 }
  if (mpCursor==mpTemp)
  {if (mpCursor->mpNext) mpCursor=mpCursor->mpNext;
   else
   {mpCursor=mpCursor->mpPrev;
   }
  }
   if (mpTemp->mpNext) {mpTemp->mpNext->mpPrev=mpTemp->mpPrev;}
  //else at Start
  else {mpEnd=mpTemp->mpPrev; mpEnd->mpNext=0;}

  if (mpTemp->mpPrev){mpTemp->mpPrev->mpNext=mpTemp->mpNext; delete mpTemp;}
  //else at End
  else {mpStart=mpTemp->mpNext; mpStart->mpPrev=0; delete mpTemp;}
  
  --miSize;
  
 return true;
}


#endif
