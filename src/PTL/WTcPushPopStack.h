#ifndef __WTCPUSHPOPSTACK_H__
#define __WTCPUSHPOPSTACK_H__

template<class cX> class cPushPopStack
{
 cX *List;
 uint8 miItems;
public:

	cPushPopStack(){miItems=0;List=new cX[PUSH_POP_STACK_DEPTH];};
 ~cPushPopStack(){delete []List;List=0;};

  cX *Push(cX lcTemp){if(miItems<PUSH_POP_STACK_DEPTH) {List[miItems++]=lcTemp; return &List[miItems-1];}else{++miItems; return 0;}};
  void Pop(){if(miItems) --miItems;};
  cX *Top(){return &List[miItems];};
  cX *Last(){if(miItems) return &List[miItems-1]; else return 0;};
  void Clear(){miItems=0;}
};


template<class cX> class cVariablePushPopStack : public cPushPopStack<cX>
{
 uint8 miSize;
public:
 cVariablePushPopStack(uint8 liSize): cPushPopStack<cX>::cPushPopStack(false)
 {
     cPushPopStack<cX>::miItems=0;cPushPopStack<cX>::List=new cX[liSize];
     miSize=liSize;
 }

 cX *Push(cX lcTemp)
 {
  if(cPushPopStack<cX>::miItems<miSize)
  {
      cPushPopStack<cX>::List[cPushPopStack<cX>::miItems++]=lcTemp;
      return &cPushPopStack<cX>::List[cPushPopStack<cX>::miItems-1];
  }
  else
  {
      ++cPushPopStack<cX>::miItems;
	  return 0;
  }
 }
};

#endif
