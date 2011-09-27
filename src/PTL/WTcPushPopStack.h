#ifndef __WTCPUSHPOPSTACK_H__
#define __WTCPUSHPOPSTACK_H__

template<class cX> class cPushPopStack
{
 cX *List;
 uint8 miItems;
public:

	cPushPopStack(){miItems=0;List=new cX[StackDepth];};
 ~cPushPopStack(){delete []List;List=0;};

  cX Push(cX lcTemp){if(miItems<StackDepth) {List[miItems++]=lcTemp;return lcTemp;}else{++miItems;}};
  void Pop(){if(miItems) --miItems;};
  cX Top(){return List[miItems];};
};

#endif
