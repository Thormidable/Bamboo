#ifndef __WTCRENDEROWNER_H__
#define __WTCRENDEROWNER_H__

class cNodeListNode;


class cRenderOwner
{
public:
    cLinkedNode<vRenderObject> *Node;
    cNodeListNode *List;

};

#endif
