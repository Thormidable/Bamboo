#ifndef __WTCPARENTSTACK_H__
#define __WTCPARENTSTACK_H__
/** \brief This class will automatically track the parents and children of each process.
 * When a new process is created, the process that created is stored as the new processes parent. The new process is added as a child of the creating process.
 * This allows Processes to get their parent (a rather inefficient method). It also allows use of the TREE signal commands to send a signal to a process, all it's children recursively. See cSignal for more information.
 *
 */
class cParentStack
{

private:
 vProcess *mpParent;
 cLinkedNode<vProcess> *mpParentNode;
 cLinkedList<vProcess> ChildStack;
 cLinkedNode<vProcess> *ChildCursor;
 
public:
  ///Constructor. The process lpChild is a pointer to the newly created process which will become a child of the current process.
 cParentStack(vProcess *lpChild);
 ~cParentStack();
 //This will set the parent process of the vProcess that owns this Parent Stack.
 void SetParent(vProcess *lpPar);
 //Will add the vProcess lpChild as a child of the process that owns this Parent Stack.
 cLinkedNode<vProcess> *AddChild(vProcess *lpChild);
 //Will Remove the Child contained in lpNode as no longer a child of this process.
 void RemoveChild(cLinkedNode<vProcess> *lpNode);
 //This will go to every child of this process and remove their Parent pointer.
 void StripChildrensParent();
 //This will Clear the parent of the process which owns this parent stack.
 void ClearParent();
 ///Returns the parent for the process which owns this cParentStack.
 vProcess *Parent();
 ///Returns the next child for the process which owns this cParentStack.
 vProcess *Child();
 ///Once a signal is identified as containing the TREE flag calling this will apply the Signal as appropriate down the tree.
 void Signal(SIGNAL lsSignal);
 ///Once a signal is identified as containing the TREE flag this will apply the Signal to all the Children of this cParentStack.
 void ChildSignal(SIGNAL lsSignal);


};


template < typename T, typename Arg1 >
T* SetParent(cProcess *lpProcess, Arg1 const & arg1 ) {
	gpParent=lpProcess;
	return ( new T ( arg1 ) );
};

template < typename T, typename Arg1 >
T* SetParent1(Arg1 const & arg1 ) {
	//gpParent=lpProcess;
	return ( new T ( arg1 ) );
};

#endif
