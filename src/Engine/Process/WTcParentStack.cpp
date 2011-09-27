#include "../../WTDivWin.h"

cParentStack::cParentStack(vProcess *lpChild)
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

vProcess *cParentStack::Child()
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


void cParentStack::SetParent(vProcess *lpPar)
{
	mpParent=lpPar;
};

cLinkedNode<vProcess> *cParentStack::AddChild(vProcess *lpChild)
{
	return ChildStack.Insert(lpChild);
};

void cParentStack::RemoveChild(cLinkedNode<vProcess> *lpNode)
{
	ChildStack.Remove(lpNode);
};

void cParentStack::ClearParent()
{
	mpParent=0;
};

vProcess *cParentStack::Parent()
{
	return mpParent;
};

