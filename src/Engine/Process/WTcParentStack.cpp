#include "../../WTDivWin.h"

cParentStack::cParentStack(cProcess *lpChild)
{
 SetParent(gpParent);
 if(mpParent && mpParent->ParentStack()) mpParentNode=mpParent->ParentStack()->AddChild(lpChild);
 else mpParentNode=0;
 ChildStack.Initialise();
};

cParentStack::~cParentStack()
{
 if(mpParentNode && mpParent && mpParent->ParentStack()) mpParent->ParentStack()->RemoveChild(mpParentNode);
 StripChildrensParent();
 mpParent=0;
}

void cParentStack::Signal(SIGNAL liFlags)
{
	ChildSignal(liFlags);
	if(liFlags&WT_SIGNAL_VALUE_KILL) StripChildrensParent();
}

void cParentStack::StripChildrensParent()
{
 ChildStack.mpTemp=ChildStack.Start();
 while(ChildStack.mpTemp)
 {
	 if(ChildStack.mpTemp->mpData && ChildStack.mpTemp->mpData->ParentStack()) {ChildStack.mpTemp->mpData->ParentStack()->ClearParent();}
  ChildStack.mpTemp=ChildStack.mpTemp->Next();
 }
}

void cParentStack::ChildSignal(SIGNAL lsSignal)
{
 ChildStack.mpTemp=ChildStack.Start();
 while(ChildStack.mpTemp)
 {
  ChildStack.mpTemp->mpData->Signal(lsSignal);
  ChildStack.mpTemp=ChildStack.mpTemp->Next();
 }
}

cProcess *cParentStack::Child()
{
 if(ChildCursor)
 {
  if(ChildCursor->Next())
  {
   ChildCursor=ChildCursor->Next();
   return ChildCursor->mpData;
  }
  ChildCursor=0;
  return 0;
 }
 else
 {
  ChildCursor=ChildStack.Start();
  return ChildCursor->mpData;
 }

}


void cParentStack::SetParent(cProcess *lpPar)
{
	mpParent=lpPar;
};

cLinkedNode<cProcess> *cParentStack::AddChild(cProcess *lpChild)
{
	return ChildStack.Insert(lpChild);
};

void cParentStack::RemoveChild(cLinkedNode<cProcess> *lpNode)
{
	ChildStack.Remove(lpNode);
};

void cParentStack::ClearParent()
{
	mpParent=0;
};

cProcess *cParentStack::Parent()
{
	return mpParent;
};

