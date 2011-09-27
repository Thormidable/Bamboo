#ifndef __WTCPROCESS_H__
#define __WTCPROCESS_H__
/**
* \brief This is the base code for a process. 
* This will automatically create a new process. It will hand itself
* to cKernel to be processed every frame. Any Processes created by the user should inherit this type to be handled by cKernel automatically.
* Initialisation code should go in the constructor of the user type. Linking to cKernel is performed automatically by cProcess.
* Update code should go in the function Run().
* Destruction code should fo in the destructor of the user type.
* Code to handle interaction of two processes should go in either processes UserSignal() function.
* \code
* class cUserProcess : cProcess
* {
*  cTexturedModel *Model;
*  int32 LifeSpan;
* public:
*
* cUserProcess()
* {
* //Initialise the Process LifeSpan
*  LifeSpan=100;
* //Create a Model for this process.
*  Model=new cTexturedModel;
* //Give the Model some media to use.
* Model->Mesh(_GET_FILE(vMesh*,"UserMesh"));
* Model->Texture(_GET_FILE(vTexture*,"UserTexture"));
* Model->Shader(_GET_SHADER("UserShaderProgram"));
* };
* 
* Run()
* {
* //Move the Model in the direction it is facing.
*  Model->Advance(0.1f);
* //Reduce the remaining LifeSpan of this object.
*  --LifeSpan;
* //If the object is out of Lifespan it is dead.
*  if(!LifeSpan) _KILL(this);
* };
*
* ~cUserProcess()
* {
* //Clean Up the Object.
*  _KILL(MODEL);
* };
*
* }
*  \endcode
*/
class cProcess: public vProcess
{

friend class cKernel;
 //This variable stores the current Process List Node which holds this process.
 cLinkedNode<vProcess> *mpNode;
 //This variable points to the cParentStack Object which contains the Parenthood stack for this object.
 cParentStack *mpParent;
public:
 /**
 * \brief This Function stores the code which will update this process by a single frame.
 * This user defined function is the single most important function for any cProcess object.
 * Every object which inherits cProcess MUST define this function. This Function will be called on
 * every currently running process every frame. This should contain the code which tells the Process how to update
 * every frame. It should not contain initialisation or deconstruction code. It is likely to direct the cRenderableObjects which
 * represent this process. It should contain AI. I should process the state of the object. It should control generation of cSignal
 * calls and search for collisions as appropriate.
 */
 virtual void Run()=0;

 /** 
 * \brief This is an engine defined inter-Process Signal. It will change the run state of the current cProcess by lbSignal
 * \param lbSignal lbSignal hands the type of signal to send. Applicable signal types are listed in WTcFlags.h.
 * This function will change the run state of the current cProcess. It allows other processes to force this process to
 * _S_SLEEP or _S_WAKE or _S_KILL. Any System State signal will be processed in this function.
 */
 void Signal(SIGNAL lbSignal);
 /// This Function will kill all currently running cProcess and start the end of the program.
 void KillAll();

 /** \brief This is a user defined function allowing the user to add Process specific inter-process signals.
  * This Function should include the code for processing the signal as there is no signal buffer. It is useful to ensure a single detection
  * and activation of process interactions. One Process shoudl detect the interaction and signal the other to respond. This way the order of
  * Process evaluation is unimportant
  *
  */
 virtual void UserSignal(SIGNAL lsSignal,void *lpData);
 // Virtual function for extra processes to be performed when prossess is killed.
 void AdditionalKillFunctionality(){};
 void AdditionalSleepFunctionality(){};
 void AdditionalWakeFunctionality(){};
 /// cProcess Constructor. Will Initialise all generic cProcess variables and add the current process to the process list held by cKernel.
 cProcess();

 ///Will return a pointer to the cParentStack owned by this process.
 cParentStack *ParentStack();
 
protected:
  cKernel *mpKernel;

  /** \brief  cProcess destructor. Should not be called by User.
   * Will delete all generic cProcess variables and remove the current process from the process list held by ckernel.
   * This should only be called by cKernel. Instead use _KILL() or Signal(_S_KILL). 
   */
  ~cProcess();
};

#endif
