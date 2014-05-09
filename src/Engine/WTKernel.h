#ifndef __WTKERNEL_H__
#define __WTKERNEL_H__




using namespace std;
/**
* \brief Kernel Object. Handles Processes.
* Tracks, runs and deletes current processes. Has complete control over every cProcess object. Will run all awake alive processes
* every process cycle, will delete dead processes. Also controls the activation of rendering frames and handling interactions with the
* operating system.
*/
class cKernel
{
 // Flag to Tell when Program is exiting
 bool mbKillProgram;
 // List of Processes currently existing in the programs data space.
 cLinkedList<cProcess> *mpProcess;
 // Currently running process.
 cLinkedNode<cProcess> *mpCursor;
 cKernel();

 // Pointer holding current Kernal Instance.
 static cKernel *mpInstance;

 // Variable containing current Search position in the process list.
 static cLinkedNode<cProcess> *mpSearch;

 // current Tick Frequency
 float mfTickFreq;
public:

 ///Function which returns current Kernel Instance. Will Create a new instance if one does not already exist.
 static cKernel *Instance();

 /// Will kill the entire program. Will delete every process and then exit.
 void KillProgram();

 ~cKernel();
 // Will update the entire system by a single frame. Updates Processes, Rendering and Events
 void Update();

/*
 * \brief Will add the process pointed to by lpNew to the process list.
 * \param lpNew Pointer to newly created process.
 *
 * Add will add the process pointed to by lpNew to the list of processes in cKernel.
 * The constructor of a cProcess object will call this function automatically and hand itself as the parameter so
 * it will be updated every frame.
 */
 cLinkedNode<cProcess> *Add(cProcess *lpNew);
 /*
 * \brief Will remove the process pointed to by lpOld from the process list.
 * \param lpOld Pointer to process requiring removal from the process list.
 *
 * Remove will remove the process pointed to by lpOld from the list of processes in cKernel.
 * The Destructor of a cProcess object, will automatically call this function and hand itself as the parameter so
 * it can be deleted and will stop being updated every frame.
 */
 void Remove(cLinkedNode<cProcess> *lpOld);
 /// Will Delete all the processes in the current process list. This will effectively end the program.
 void DeleteAll();

/**
* \brief This Function will search for a process of either tType OR a type which has uses the type tType as a base type.
* \tparam tType is the type of the desired process.
* \return Will return a pointer to a process currently in the process list of the correct type.
*
* This Function will search for a process which is of type tType or
* inherits tType. Can be used to find processes of a certain type or genus. Each call of this function will continue
* searching from the position stored in mpSearch. Between searches for processes of different types
* use the function ResetFindProcess().
* \code
	cGunShip *mpGunShip;
	cBattleShip *mpBattleShip;

	mpGunShip = FindProcess(mpGunShip);
	ResetFindProcess();
	mpBattleShip = FindProcess(mpBattleShip);

* \endcode
*/
template<class tType> tType *FindProcess();

/// Like FindProcess() This function will search the Process List to find the next process of type tType. This will start the search from the item lpStart.
template<class tType> tType *FindProcess(tType *lpStart);

/// This Function will reset FindProcess() to search from the start of the process List.
 void ResetFindProcess();

///This will return a pointer to the Currently Running cProcess (Ensure you are beneath a call to cProcess::Run()). This is undefined during Rendering or within the cFrameUpdateHandler system.
 cProcess *CurrentProcess();

 template<class tType> void KillOtherProcesses();
 template<class tType> void KillType();
};

/**
 * \brief This class will allow the user to update a function on a regular basis without giving it the overhead of a process
 * Simply inherit this class into the class that is desired and define void FrameUpdate(). This will be called once per rendered frame (less than processes).
 * Expansions to allow, smoother distribution of tasks over several frames will be enabled in a future edition.
 */
class cFrameUpdateType
{

public:
    cFrameUpdateType();
    ~cFrameUpdateType();
    virtual void FrameUpdate()=0;
};

class cFrameUpdateHandler : public cLimitedPointerList<cFrameUpdateType>
{
  static cFrameUpdateHandler *mpInstance;
  cFrameUpdateHandler();
public:

  static cFrameUpdateHandler *Instance();
  static cFrameUpdateHandler *Pointer();

  void FrameUpdate();

};



template<class tType> tType *cKernel::FindProcess()
{
 tType *mpType;
 if (!mpSearch){mpSearch=mpProcess->Start();}
 while(mpSearch)
 {
  mpType=dynamic_cast<tType*>(mpSearch->Data());
  if (mpType) return mpType;
  mpSearch=mpSearch->Next();
 }
 return 0;
};

template<class tType> tType *cKernel::FindProcess(tType *lpStart)
{
 if(!lpStart) mpSearch=mpProcess->Start();
 else mpSearch=lpStart->mpNode->Next();
 tType *mpType;
 while(mpSearch)
 {
  mpType=dynamic_cast<tType*>(mpSearch->Data());
  if (mpType) return mpType;
  mpSearch=mpSearch->Next();
 }
 return 0;
};


#endif
