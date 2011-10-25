#ifndef __WTDIVWIN_H__
#define __WTDIVWIN_H__

/**
* \page DivWinExplanation 1.Using DivWin
*
*WTDivWin.h
*
*Using DivWin by William Thorley
*
* DivWin is based on a Process / Renderable Object mentality. Process' are classes with behavioural code which tell them how to behave. They take inputs from the OS, signal other process' and tell Renderable objects how to display. Once a Process is written, the user should create a new instance. The system will record the information add it to the system and make the process enact it's behaviour, with no further input form the user (Fire and Forget). This way many similar objects can be created easily once the behavioural code is written. Render Objects should not have any behavioural code and are entirely directed by Process'.
*
* The Process' are controlled by cKernel which will track and update all the process'.
*
* Render Objects actually display on the screen. They are moved around in 3D space and cCamera renders them to the screen.
*
* Collision Objects must be handed a Render Object at startup, which they will follow and determine collisions with other Collision Objects.
*
* Files are loaded by the FileHandler and can be asked to provide media data for Render Objects and Collision Objects.
*
* Lighting effects are controlled by the LightHandler.
*
*
*The Main Loop:
*
*\code
*#include <WTDivWin.h>
*int WINAPI WinMain (HINSTANCE hInstance,
*                    HINSTANCE hPrevInstance,
*                    LPSTR lpCmdLine,
*                    int iCmdShow)
*{
* //_START_PROGRAM(First_Process_Type,User_Settings_Type,Instance);
* return _START_PROGRAM(cCore,cUserSettings,hInstance);

};
*\endcode
*\code
* //Using DivWin in Linux
*#include <WTDivWin.h>
*
*int main ()
*{
*  //_START_PROGRAM(First_Process_Type,User_Settings_Type);
*  return _START_PROGRAM(cCore,cUserSettings);
*
*}
*\endcode
*
*Main Loop Explanation:
*This will call the main function which will initialise the various components of the system.
* First_Process_Type must be a class type which inherits cProcess and should be the process that initialises and creates all the other processes required for the game.
* User_Settings_Type must be a class type which inherits cSettings. The virtual function UserSettings() in the derived class should set all the variables the user wishes to define. If the User does not wish to define ANY settings, use cSettings here and the defaults will be used.
* hInstance is a Windows only variable which is passed from the operating system to the WinMain function. Use the first HINSTANCE Passed to the function.\n
* First _START_PROGRAM will set the settings for the game to use.\n
* Then it will initialise the various components of the engine.\n
* It will create an instance of the class type First_Process_Type which should initilise the game and create other processes to start the game.\n
* While there are processes alive (and the system has not received an exit signal) the system will continue to cycle.\n
* As the system exit, it will clear data, close links to devices and hardware and return a suitable exit signal for the Operating system. This should be returned from the funciton main().\n
**/


/**
 * \page cKernelExplanation 2. Using the cKernel
 *WTKernel.h
 *
 *Using the kernel system by William Thorley
 *
 *The kernel will create itself as soon as any Process is created. It will automatically link the process, and sort their run order. A Pointer to the cKernel can always be found by calling the macro _KERNEL (cKernel::Instance()). If this function is called and there is no cKernel, the function will create one. The Constructor is private, so there can be only one cKernel.
 *The Kernel is entirely automatic and should require no inputs from the user. However it can supply useful information and functionality to the user.
 *KillAll():
 *Calling KillAll() will kill every running process. This will cause Update() to exit, and traditionally end the program. However it is possible to KillAll(), then create a new core process, and call Update() again, thereby ‘restarting’ the program.
 *
 *_FIND_PROCESS(TYPE)
 *Calling _FIND_PROCESS() will automatically search the cKernel for any processes of class type TYPE. It will return a pointer to the next process of class type TYPE everytime it is called. When there are no more processes of class type TYPE it will return 0.
 **/


/**
 * \page CoreExamples 3. The First Process
 *
 *WTcProcess.h
 *
 *Using William Thorley’s Process system
 *
 *The First Process is exactly the same as every other process. i.e. it must inherit cProcess.
 * What is special about the Process passed to the _START_PROGRAM() call is that it is the automatically called when the Kernel is initialized. This means that the constructor for the first process is the initialization code for the entire program. Usually the process’ which will form the program are started here as well as loading files for the system.
 * For these examples I wil call the class cCore.
 *
 * This shows the declaration for cCore. Using _PROCESS(Type) is the same as calling class Type : public cProcess to inherit cProcess.
 * Declaration:
 * \code
 * _PROCESS(cCore)
 * {
 *  public:
 *  cCore();
 *
 *  void Run();
 *
 *  ~cCore();
 *
 * void AdditionalKillFunctionality();
 * void AdditionalSleepFunctionality();
 * void AdditionalWakeFunctionality();
 *
 * };
 * \endcode
 *
 * cCore():
 * This shows the constructor for cCore. As it is the first object it will load media for the rest of the program and kick off the other processes.
 * \code
 * cCore::cCore()
 * {
 * //Load IMF Files into memory.
 *  _LOAD_FILE("../src/User/Models/AShipModel.imf");
 *  _LOAD_FILE("../src/User/Models/StartShip.imf");
 *  _LOAD_FILE("../src/User/Textures/ATexture.imf");
 *  _LOAD_FILE("../src/User/CollisionObjects/ACollision.imf");
 *  _LOAD_FILE("../src/User/Objects/AIMFFileWithSeveralComponents.imf");
 *
 * // Setup the camera.
 *  _CAMERA->Far(1000.0f);
 *  _CAMERA->Frustum();
 *
 * //Create a new process and a renderable object.
 *  mpProcessPointer=_CREATE(MyFirstProcess());
 *  mpRenderObjectPointer=_CREATE(MyFirstRenderObject());
 *
 * }
 * \endcode
 *
 *Run():
 *	Run() is run once every frame as long as cCore is alive and controls the entire program. The Run() function should is explicity designed to be re-written by the user to give each cProcess class their functionality. This Code can be seen as the behaviour that the process should follow. It should rotate and position the Process' Renderobjects, send signals, receive inputs, anything the Process may want to do as part of it's behaviour. The function cCore::Run() can be used like any other process, but is usually used to oversee the running of the program.
 * \code
 * void cCore::Run()
 * {
 *
 *  if(_KEY(KEY_SPACE)) _CAMERA->Far(10.0f);
 *   else _CAMERA->Far(1000.0f);
 *  _CAMERA->Frustum();
 *
 *  _CREATE(AnotherProcess());
 *  mpRenderObjectPointer->Advance(0.1f);
 *
 * }
 * \endcode
 *
 *~cCore():
 *	This is called when the object is deleted, not when it is killed. It is difficult to predict reliably where this will be called, so it is best not to put code in this function. Use AdditionalKillFunctionality() instead, to ensure the code runs when then object is killed.
 *
 *AdditionalKillFunctionality():
 *	This is called whenever the cCore Process is Killed. This will only activate if the process was alive and is now dead. This should be used to kill or transfer control of Render Objects that are owned by this process, or unload files that are no longer used.
 *
 *\code
 *void cCore::AdditionalKillFunctionality()
 *{
	 * _KILL(mpRenderObjectPointer);
	 * mpProcessPointer_SIGNAL(_S_SLEEP);
	 *}
	 *\endcode
	 *
	 *AdditionalSleepFunctionality():
	 *	This is called whenever the cCore Process is made to Sleep. This will only activate if the process was awake and is now asleep. This is generally used to sleep Render Objects that are owned by this process.
	 *
	 *\code
	 *void cCore::AdditionalSleepFunctionality()
	 *{
		 * mpRenderObjectPointer->Signal(_S_SLEEP);
		 *}
		 *\endcode
		 *
		 *AdditionalWakeFunctionality():
		 *	This is called whenever the cCore Process is made to Wake. This will only activate if the process was asleep and is now awake. This is generally used to wake Render Objects that were slept when cCore was sent to sleep.
		 *
		 *void cCore::AdditionalSleepFunctionality()
		 *{
			 * mpRenderObjectPointer->Signal(_S_WAKE);
			 *}
			 *\endcode

 **/


/**
 * \page ProcessExplanation 4. How to use Process Objects
 *WTcProcess.h
 *
 *Using William Thorley’s Process Handler System
 *
 *When properly implemented the process handler automatically links and runs all processes. A process must inherit cProcess. It must also define the virtual function Run() a process without a Run() function is useless, and will be deleted during the frame it is created.
 *
 *Declaring a new process class called player:
 *\code
 * //This is the same as _PROCESS(player)
 *class player : public cProcess
 *{
	 *public :
	 void Run();
	 *};
	 *\endcode
	 *
	 * void cProcess::Run();
	 *	The function Run() is a virtual function already defined. This function is called every time the process must run its code (usually once a frame). The code that defines how the process acts goes in Run().
	 *
	 * Creating a Process:
	 * 	Call the macro _CREATE(Type); This will return a pointer to the new process of type Type.
	 * \code
	 *
	 * player *mpNewProcessPointer;
	 * NewProcessPointer=_CREATE(player());
	 * _CREATE(AnotherProcess(Argument1,Argument2));
	 *
	 * \endcode
	 *
	 *Killing a Process:
	 *	Process' must not be destroyed by deleting the process. Processes can be be deleted either by calling the macro _KILL(); or by calling the Function Signal(SIGNAL lsFlags) with the flag _S_KILL. if _KILL() is called without a pointer it will automatically use the pointer this. Process' will not be destroyed when the signal is sent, they will be deacticated, but the memory will remain allocated until cKernel reaches the correct stage to delete the object. Objects can remain allocated into the next frame, but not the frame after that. Both pieces of following code have the same effect. The Process pointed to by mpPointerToAnotherProcess is Killed and then this process is killed.
	 * \code
	 * void player::Run()
	 * {
	 *
	 * if(_KEY(KEY_k))
	 * {
	 * mpPointerToAnotherProcess->Signal(_S_KILL);
	 * _KILL(this);
	 * }
	 *
	 * }
	 * \endcode
	 *
	 * \code
	 * void player::Run()
	 * {
	 *
	 * if(_KEY(KEY_k))
	 * {
	 * _KILL(mpPointerToAnotherProcess);
	 * _KILL();
	 * }
	 *
	 * }
	 * \endcode
	 *
	 *Sleeping a Process:
	 *	A Process can be sent to sleep by calling the cSignal::Signal(SIGNAL lsFlags) function with the value _S_SLEEP. Sleeping a process leaves the process in the process list, but stops the Run() function being called every frame. This allows the Signal(SIGNAL lsFlags) function to be used to return it to ‘active duty’. The memory will remain allocated. Sending repeated Sleep calls to a process will not affect the process or the stability of the system, the Process will remain asleep.
	 *
	 *Waking a Process:
	 A Process can be awakend by calling the cSignal::Signal(SIGNAL lsFlags) function with the value _S_WAKE. Sending repeated Waking calls to a process will not affect the process or the stability of the system, the Process will remain awake.
	 * \code
	 *
	 * void player::Run()
	 * {
	 *
	 * if(_KEY(KEY_s)) mpPointerToAnotherProcess->Signal(_S_SLEEP);
	 * if(_KEY(KEY_w)) mpPointerToAnotherProcess->Signal(_S_WAKE);
	 *
	 * }
	 * \endcode
	 *
	 *Removing a Process:
	 *	A Process can be killed by the cKernel object. Calling the cKernel::Remove() function will kill the process and free the memory. This must not be done to the currently running process or the system may crash. Use on the current process at your peril. The pointer is to the cLinkedNode<vProcess> which owns this process. Each Process has a pointer (mpNode) to its cLinkedNode<vProcess>.
	 * * \code
	 *
	 * void player::Run()
	 * {
	 *
	 * if(_KEY(KEY_k)) _KERNEL->Remove(mpPointerToAProcessesNode);
	 *
	 * }
	 * \endcode
**/


/**
 * \page RenderObjectExplanation 5. How to use Render Objects
 * WTcRenderObject.h
 *
 *Using William Thorley’s Renderable Object System
 *
 *All Render Objects are inherited from class vRenderObject, through class cRenderObject.
 The object also Inherits the class cMatrix4. This is a 3D Translation class, and can handle 2D rotations (about X axis), 3D rotations, 3D Translations and 3D scaling. Calling the cMatrix4 functions will move the cRenderObject.
 *
 * Creating RenderObjects:
 * 	cRenderObjects can be created using the _CREATE macro as per a Process. This will return a pointer to the RenderObject.
 * \code
 * void player::Run()
 * {
 * 	mpHull=_CREATE(cTexturedModel(mpShipNode));
 *	mpHull->Mesh(_GET_FILE(vMesh*,"Mesh"));
 *	mpHull->Texture(_GET_FILE(vTexture*,"Texture"));
 *	mpHull->Shader(_GET_SHADER("TexturingProgram"));
 * }
 *\endcode
 *
 * Currently there are lots of Render Objects:
 *
 * class cTexturedModel;
 * class cLandscape;
 * class cRenderNode;
 * class cBeamMesh;
 * class cImage;
 * class cTextureText;
 * class cLine;
 * class cParticle;
 * class cParticleGroup;
 * class cParticleHandler;
 * class cModelList;
 * class cPoint;
 *
 * See the relevant documentation for each for how to use them.
 *
 *
 *The Renderable Object allows the user to develop their own Renderable Objects and links them to the renderer. A Renderable object must inherit cRenderObject and must also define the virtual function Render(), This will be called every time the renderable object needs to be rendered. It should also define all empty virtual functions in vRenderObject and cRenderObject,
 *
 *Declaration of a Renderable Object:
 *	class player : public cRenderObject, public  cMatrix4
 *{
	 *public : Render();
	 *};
	 *
	 *Render():
	 *
	 *
**/

/**
 * \page Matrix4Explanation 6. Use of the cMatrix4 and cCameraMatrix Classes
 * \n
 * cMatrix4.h \n
 * cCameraMatrix.h \n
 * \n
 * Use of the Translation matrix classes by William Thorley. \n
 * \n
 * The cMatrix4 class and cCameraMatrix classes are very similar. The CameraMatrix maintains an inverted cMatrix4 matrix as the translations applied to the camera must be inverted to give the same effect as to normal objects. Otherwise the effects are the same for cMatrix4 and cCameraMatrix. \n
 * Most Render Objects have inherited the cMatrix4 class meaning that these functions can be called to move and rotate Render Objects. Calling these functions, will apply the defined translations to the current object. Some are relative to the current translation and some are relative to the position of the Render Node controlling this object. Either way, the translations stack. \n
 * \n
 * The X Axis points 90 to the Right perpendicular to the objects facing. \n
 * The Y Axis points 90 Upwards, perpendicular to the objects facing. \n
 * The Z Axis is the objects facing. \n
 * \n
 * These Classes can be used for 2D or 3D Translations. There are different functions for 2D and 3D translations. The standard DivWin Objects automatically identify if they should be 2D or 3D. \n
 * \n
 * 3D Object Translation Functions: \n
 * void Set3D() \n
 * \n
 * float *Position() \n
 * float X() \n
 * float Y() \n
 * float Z() \n
 * \n
 * float *XVect() \n
 * float *YVect() \n
 * float *ZVect() \n
 * \n
 * void Position(c2DVf *lpPosition) \n
 * void Position(float lfX,float lfY) \n
 * void Position(c3DVf *lpPosition) \n
 * void Position(float lfX,float lfY,float lfZ) \n
 * void PositionX(float lfX) \n
 * void PositionY(float lfY) \n
 * void PositionZ(float lfZ) \n
 * \n
 * void AdvanceX(float lfDistance) \n
 * void AdvanceY(float lfDistance) \n
 * void AdvanceZ(float lfDistance) \n
 * void Advance(float lfX,float lfY, float lfZ) \n
 * \n
 * void GAdvanceX(float lfX) \n
 * void GAdvanceY(float lfX) \n
 * void GAdvanceZ(float lfX) \n
 * void GAdvance(float lfX,float lfY,float lfZ) \n
 * \n
 * void LRotate(float lfAngle) \n
 * void LRotateX(float lfAngle) \n
 * void LRotateY(float lfAngle) \n
 * void LRotateZ(float lfAngle) \n
 * \n
 * void GRotateX(float lfAngle) \n
 * void GRotateY(float lfAngle) \n
 * void GRotateZ(float lfAngle) \n
 * \n
 * void GRotateOriginX(float lfAngle) \n
 * void GRotateOriginY(float lfAngle) \n
 * void GRotateOriginZ(float lfAngle) \n
 * \n
 * void GRotateX(float lfAngle,float lfX,float lfY,float lfZ) \n
 * void GRotateY(float lfAngle,float lfX,float lfY,float lfZ) \n
 * void GRotateZ(float lfAngle,float lfX,float lfY,float lfZ) \n
 * \n
 * void Resize(float lfScale) \n
 * void LResizeX(float lfScale) \n
 * void LResizeY(float lfScale) \n
 * void LResizeZ(float lfScale) \n
 * \n
 * void GResizeX(float lfScale) \n
 * void GResizeY(float lfScale) \n
 * void GResizeZ(float lfScale) \n
 * \n
 * 2D Object Translation Functions: \n
 * void Set2D() \n
 * \n
 * void Advance(float lfX,float lfY) \n
 * void GAdvance(float lfX,float lfY) \n
 * \n
 * void Angle(float lfAngle) \n
 * void Rotate(float lfAngle) \n
 * void GRotateOrigin(float lfAngle) \n
 * void GRotate(float lfAngle,float lfX,float lfY) \n
 *
 **/


/**
 * \page FileHandlerExplanation 7. Explanatory page for indicating the use of files
 *
 *WTcFile.h
 *
 *Using the file handler by William Thorley
 *
 *The Filehandler is an automatic system for controlling files loaded in DivWin. All files should be of type IMF, though others can be loaded. When a file is loaded it is automatically linked into the system. This allows any process to access any loaded file. All Objects (blocks within IMF Files) are given a Reference (a character string) to allow them to be easily identified. And in the event of an OS clearing data (for instance Windows clearing Textures on Minimize) the file handler will automatically reload all the files.
 *Non IMF Files will use the Filename as the Reference for the purposes of Identification.
 *
 *To create a new File Class and make it use the file handler, have it inherit cFile, This will require #include “WTcFile.h”.
 *To load a new file use the macro _LOAD_FILE(FileName).
 *
 *IMF Files contain many types of data:
 *
 * Models
 * Textures
 * Fonts
 * Model Trees
 * Reference Lists
 * Shaders
 * Shader Programs
 * Collision Objects
 * Landscape Models
 *
 * See the specific files for each type for more information.
 **/

/**
 * \page InputSystemExplanation 8. Explanation of the Input System.
 *
 * There are two main types on input. Mouse inputs and Key inputs. Both are updated every frame and buffered until the next frame. This means that a key press or mouse position will be consistent throughout the entire frame. THe inputs re recieved as interupts so will be recieved in line with the OS.
 * Key states are boolean and can be accessed using the macro _KEY(Key Identifier). A list of Key Identifiers can be found on page \ref KeyIdentifiersList KeyIdentifiersList. True is key pressed, false is key not pressed.\n \n
 * The Mouse can be accessed using the macro _MOUSE() which is a reference to the cMouse Object. The mouse has three buttons (for now) left, right and middle, because that is enough for most people. Like keys these are boolean values, with true for pressed and false for not pressed. The mouse also has x,y and z which are the cursor position in pixels from the window position 0,0. Finally the mouse has xs and ys which is the amount the cursor has moved (in pixels) since the last frame.
**/


/**
 *\page Audio 9. Using the Audio System
 *
 * How to use the Audio System by William Thorley.
 *
 * The class cAudioObject are used to play sounds from the sound card. Currently sound files are loaded by creating a new cWav() with the file path and name as the first argument. They will be added to the file list in cFileHandler and can be found by searching the list for the filepath and name, once sound files are added to IMF files they will be loaded with the _LOAD() macro.. A Sound file is passed to the buffer and played with the Play() command. When the sound is played it will take up a channel on the sound card.
 *
 * \code
 *
 *  * // Load the Sound file
 * mWav = new cWav("./User/Audio/wave1.wav");
 * //Create the cAudioObject to buffer the sound file in.
 * mAO = new cAudioObject;
 * //Load the sound file into the buffer
 * mAO->SetBuffer(mWav);
 * //Play the sound
 * mAO->Play();
 *
 * \endcode
 *
 *
 **/

/**
 * \page SignalExplanation 10. class cSignal Explanation and Flags List
 *
 * These correspond to the Flag values for cSignal::Signal(SIGNAL lsFlags).
 * \code
 * Signal(_S_SLEEP);
 * lpOtherProcess->Signal(_S_WAKE_TREE);
 *
 * \endcode
 *
 * _S_KILL
 *	- Kill the process. It will be deactivated and no longer run. Once the system is stable, the Kernel will delete the object.
 * _S_SLEEP
 *	- Sleep the process. It will be deactivated, but will not get deleted. The Process will continue to exist, but will not run. Objects this Process controls will remain and can be controlled from other processes.
 * _S_WAKE
 *	- Wake the Process. A Sleeping process will be reawakened and will start to run again.
 * _S_KILL_TREE
 *	- If the Variable WT_USE_PARENT_TREE is true, this will kill the signaled object and any child objects it created. This will act recursively until all children, grandchildren, great grandchildren etc. have been killed.
 * _S_SLEEP_TREE
 *	- If the Variable WT_USE_PARENT_TREE is true, this will Sleep the signaled object and any child objects it created. This will act recursively until all children, grandchildren, great grandchildren etc. have been Slept.
 * _S_WAKE_TREE
 *	- If the Variable WT_USE_PARENT_TREE is true, this will Wake the signaled object and any child objects it created. This will act recursively until all children, grandchildren, great grandchildren etc. have been Wakened.
 **/

/**
 * \page CollisionObjectExamples 11. Examples of how to use Collision Objects
 *
 *
 * Collision Objects will only collide with other collision objects, NOT Render Objects. When a Collision Object is created it must be passed a pointer to a Render Object which will define it's translation. This should be the first argument passed to a Collision Object.
 *
 * Collision Objects are created using the _CREATE() Macro and killed using the _KILL() Macro, as per a process. They can be slept and woken.
 * Collision Objects need a media type to define how and when they collide.
 * This is defined using the Type Function which gives the Collision Object the data it needs and sets the type of collision Object it will be.
 * A Collision object should also be linked to a Process so that processes can transfer information or signals in the event of a collision.
 *
 *
 * Types of Collision Object:
 *	cCollisionSphere
 *	cMeshCollision
 *	cCollisionRay
 *	cCollisionBeam
 *	cCollisionBox
 *	cCollisionBoxFile
 *
 * \code
 *
 * MyProcess::MyProcess()
 * {
 *  mpRender=_CREATE(TexturedModel());
 *  mpCollision=_CREATE(cCollisionObject(mpRender));
 *
 *  mpCollision->SetLink(this);
 *  mpCollision->SetType(10.0f);
 * }
 *
 * void MyProcess::Run()
 * {
 *  vProcess *lpProc;
 *  cCollisionList* lpList=_COLLISION_HANDLER->GenerateCollisionList(mpHullColl);//,WT_ENEMY_UNIT
 *	_COLLISION_PROCESS_LIST(lpList,lpProc)
 *	{
 * 		 		_KILL(lpProc);
 *	}
 *	delete lpList;
 *
 * }
 * \endcode
 **/


/**
 * \page RenderNodeExplanation 12. How to use cRenderNode Objects
 *
 * WTcRenderNode.h
 *
 * How to use Render Nodes by William Thorley.
 *
 * RenderNodes are a special type of Render Object. Render Nodes have no visual rendering to screen. Instead they manipulate other Render Objects. Specifically, a Translation applied to a Render Node will affect any Render Objects Controlled by the RenderNode. This means the objects controlled by the Render Node will move as if the Render Nodes position was 0,0,0.
 *
 * \code
 * mpNodePoint=_CREATE(cRenderNode());
 * mpNodePoint->Position(0.0f,0.0f,0.0f);
 * mpModel=_CREATE(cTexturedModel(mpNodePoint));
 * mpModel->Position(10.0f,0.0f,0.0f);
 *
 * // mpModel is now at 10.0f,0.0f,0.0f.
 *
 * mpNodePoint->Position(10.0f,0.0f,10.0f);
 *
 * // mpModel is now at 20.0f,0.0f,10.0f.
 *
 * mpNodePoint->RotateY(3.1416); //(rotate 90 degrees)
 *
 * //Model is now at 0.0f,0.0f,-10.0f.
 *
 * \endcode
 *
 * To control a Render Object by a Render Node object pass a pointer to the Render Node as the first argument in the Render Objects Constructor.
 * Render Node objects can control any Render Object, including Render Nodes. This means that there can be many levels of Render Nodes before reaching a Renderable Object, making positioning of complex positional relationships easy.
 *
 *
 * See Also: cModelList
 **/


/**
 * \page IMFFiles IMF File Generation and Usage
 *
 * IMF Files are generated by the IMF Compiler. The IMF Compiler is a seperate program to the DivWin engine and has a text based interface. The Compiler should be run from the terminal, so the user can view and use the interface.
 *
 * Everytime the user runs the program will start with an empty IMF File. IMF Files contain media blocks. Each block begins with a type identifier to identify the type of media stored in the block. This is followed by a size specifier defining the amount of data in the remainder of the block. Finally the Block has a character string storing the reference.\n
 * The main task the user will perform is to add Media to the IMF File. Each Media file added will require a reference (a character string which allows the media to be identified in the DivWin Engine) and often other data to fully define the object.\n
 * Media can often be converted into several different types of IMF Blocks. e.g. A image can be converted to a 2D Texture, a Landscape height map or if it is 64 times taller than it is wide into a font. Each of these require different information to generate the object.\n
 * An IMF File can contain many blocks all with different media types in. This allows the user to group media into sensible sets which are interdependant, eg a tank body model, a tank turret model, a tank shell model, a texture for the tank, and a model list representing the skeletal structure for the tank. This ensures that all inter dependant media can be loaded with a single call.\n
 * Each level of the menu defines the options available to the user, selecting 0 will always move the user back up to the previous level. Otherwise, the user should select the desired option, insert the number representing it and press enter.\n
 *
 * To add each item, select 1 from the main menu. Each file Name (including file type) which is entered will be added to the IMF File as a new block. The system will request all the information required to generate the object, then add it to the IMF File as a new block. Take care when selecting the references as they are the only way to access the media in the DivWin Engine.\n
 * Once all the required media files are added to the IMF file, it can be written to the harddrive, by selecting option 7. The IMF file type should be included by the user.\n
 * IMF Files can be loaded and will add all their blocks to the end of all the blocks in the current IMF File. This allows the user to add new media to previous groupings.\n
 *
 * Media Types Supported:\n
 * Shader Code:\n
 *	.shd			(text files containing the shader code)\n
 * Model Files:\n
 *	.x\n
 *	.obj\n
 *	.q3d\n
 * Model Files can be converted into:\n
 *	Meshes 			(3D Models, including Normals and UV if available)\n
 *	Collision Objects 	(Currently only supporting convex faces)\n
 *	Box Collision Objects \n
 * Images:\n
 *	.bmp\n
 * Image Files can be converted into:\n
 *	2D Textures\n
 *	Fonts 			(are composed of 64 vertical characters, with equal width and height)\n
 *	Landscape Height Maps 	(Produces a map with a polygon per pixel in the image, with RGB(0,0,0) being no height and RGB(1,1,1) being maximum terrain height)\n
 *\n
 * User Generated Media Types:\n
 * All data in these types is entered by the user into the IMF Compiler and the files are produced from that data. To activate them, insert the desired media type instead of a filename, in the add file menu.\n
 * * Shader Programs:\n
 *	Insert 'Shader Program' as file name.\n
 * Model Lists:\n
 *	Insert 'Model List' as file name.\n
 * Render Trees:\n
 *	Insert 'Render Tree' as file name.\n
 */

/**
 * \page MacroList I. A List of Useful Macros for accessing functions and pointers
 *
 * \n
 *  RANDOM_NUMBER
 *  - returns a Randomly generated number between 0.0f and 1.0f.\n
 *  SIGNAL()
 *  - A Class Type for passing Signals between Process', Render Objects and Collision Objects.\n
 *  _KEY(KEY_ID)
 *  - Function for accessing the array of key states. Takes Key ident as an input. Key Idents are defined in the Key List.\n
 *  _MOUSE
 *  - Reference giving access the systems mouse states.\n
 *  _LOAD(FileName)
 *  - Function for loading a file. Takes the filename as an input. Same as _LOAD_FILE(FileName);\n
 *  _LOAD_FILE(FileName)
 *  - Function for loading a file. Takes the filename as an input. Same as _LOAD(FileName);\n
 *  _GET_FILE(FileType,FileName)
 *  - Function returning a pointer of type FileType to the IMF Object with the reference FileName.\n
 *  _CREATE(Type)
 *  - Function operating like the new operator. Will create a new Process, Render Object or Collision Object and return a pointer of type Type.\n
 *  _KILL()
 *  - Will Kill the current process.\n
 *  _KILL(Pointer)
 *  - Will Kill the process pointed to by Pointer.\n
 *  _SLEEP(Process)
 *  - Will Sleep the process pointer to by Process.\n
 *  _WAKE(Process)
 *  - Will Wake the process pointed to by Process.\n
 *  _SIGNAL(Flag)
 *  - Function which will send a signal to the process this function is called from, to signal the action, Flag. (Signal Flags are defined in the Signal List).\n
 *  _USE_SHADER(FileName)
 *  - Function telling the system to buffer for use the shader with reference FileName.\n
 *  _GET_SHADER(FileName)
 *  - Function returning a pointer to the cShader Object with the reference FileName.\n
 *  _USE_FIXED_FUNCTION()
 *  - Function telling the system to used the fixed function pipeline and not use shaders.\n
 *  _CAMERA
 *  - A Pointer to the cCamera Object.\n
 *  _LIGHT
 *  - A Pointer to the cLightHandler Object.\n
 *  _KERNEL
 *  - A Pointer to the cKernel Object.\n
 *  _FILE
 *  - A Pointer to the cFileHandler Object.\n
 *  _PAINTER
 *  - A Pointer to the cPainter Object.\n
 *  _COLLISION_HANDLER
 *  - A Pointer to the cCollisionHandlerObject.\n
 *  _RESET_COLLISION
 *  - This will reset a stepping Collision Search, ready for a fresh search. (Not issue for Generating Collision Lists)\n
 *  WT_TIME_IND
 *  - This is the current frame length in seconds. Multiply anything time dependant by this to make it time independant. (It is a float multiplyer, think before use.)\n
 *  _COLLISION_PROCESS_LOOP(lpList,lpVar)
 *  - This will start a Loop to step through a collision list. lpList should point to the Collision List and lpVar will point at the current process in the collision list.\n
 *  _COLLISION_RENDER_LOOP(lpList,lpVar)
 *  - This will start a Loop to step through a collision list. lpList should point to the Collision List and lpVar will point at the current Render object in the collision list.\n
 *
 **/


/**
 * \page SettingsList II. A List of Settings which can be used to modify the way the engine works
 *
 *
 *\n
 * WT_USE_PAINTER_ALGORITHM
 *	- This determines whether the system will render objects in the order they sit in the Render Tree, or to use the Painter Algorithm and sort them for speed.\n
 * WT_OPENGL_LIGHTS
 *	- This is the number of Lights that you wish OpenGL to use simultaneously to light an object.\n
 * USE_LIGHT_HANDLER
 *	- The light handler will determine the closest WT_OPENGL_LIGHTS to the object and render the object only using their influence. This allows the user to improve performance and / or use more lights than OpenGL can support.\n
 * WT_COLLISION_HANDLER_TYPE WT_COLLISION_HANDLER_TYPE_TYPE
 *	- This determines the Type of Collision handler used to sort Collisions. It can be set to either WT_COLLISION_HANDLER_TYPE_TYPE or WT_COLLISION_HANDLER_TYPE_BSP.\n
 * WT_RAY_ANGLE_RANGE
 *	- Ummmm, something to do with Ray Angles.\n
 * WT_ALLOW_DYNAMIC_TEXTURES
 *	- This determines whether the user wants to be able to update textures once loaded into memory. Being able to do so will result in a reduction in performance.\n
 * WT_COLLISION_HANDLER_SIZE
 *	- This will set the number of slots that the Collision Handler will use for filtering collisions. See relevant documentation.\n
 * WT_COLLISION_HANDLER_DIMENSIONS
 *	- This sets the number of dimensions the BSP Collision Handler should use (1,2 or 3) WT_COLLISION_HANDLER_DIMENSIONS_1D,WT_COLLISION_HANDLER_DIMENSIONS_2D, WT_COLLISION_HANDLER_DIMENSIONS_3D.\n
 * WT_COLLISION_SPACE_SIZE
 *	- This is the spatial size of each slot for the BSP. It should be at least (preferably more) than half the largest object size, that will be involved in collisions.\n
 * WT_DEFINE_OS
 *	- This is the OS that the engine is running under. So far OS_LINUX or OS_WINDOWS.\n
 * WT_COLLISION_DEPTH
 *	- This shouldn't be used anymore. Why did I leave it in here. Was from the good ol' days of Collision Trees.\n
 * _GRAVITY_X
 *	- This is the X Axis value of gravity, to be used by particle objects.\n
 * _GRAVITY_Y
 *	- This is the Y Axis value of gravity, to be used by particle objects.\n
 * _GRAVITY_Z
 *	- This is the Z Axis value of gravity, to be used by particle objects.\n
 * _WIND_X
 *	- This is the X Axis value of wind, to be used by particle objects.\n
 * _WIND_Y
 *	- This is the Y Axis value of wind, to be used by particle objects.\n
 * _WIND_Z
 *	- This is the Z Axis value of wind, to be used by particle objects.\n
 * WT_MAX_PARTICLES
 *	- This is the maximum particles that cParticleHandler should need to maintain at any one time.\n
 * WT_PARTICLE_HANDLER_UPDATE_PARTICLE_POSITIONS
 *	- When true, the Particle handler will automatically update the particles speed and position based on Wind and Gravity.\n
 * WT_VERTEX_RANGE_CHECK_SIMILAR
 *	- This is the maximum allowed distance between verteces in a collision object for them to be counted as a single vertex.\n
 * WT_USE_PARENT_STACK
 *	- This will determine whether the system should automatically track each process' parent and children.\n
 *
 **/
/**
 * \page KeyIdentifiersList III. List of Key Identifiers for accessing the Key States
 *
 * These correspond to the Key codes for the Macro _KEY()
 * \code
 * if(_KEY(KEY_SPACE)) _CREATE(Bulltets());
 * if(_KEY(KEY_TAB)) _KERNEL->KillAll();
 *
 * \endcode
 *
 * KEY_BACKSPACE \n
 * KEY_TAB \n
 * KEY_ENTER \n
 * KEY_RETURN \n
 * KEY_SHIFT \n
 * KEY_CONTROL \n
 * KEY_CTRL \n
 * KEY_ALTERNATE \n
 * KEY_ALT \n
 * KEY_PAUSE \n
 * KEY_CAPSLOCK \n
 * KEY_CAPITALLOCK \n
 * KEY_ESCAPE \n
 * KEY_ESC \n
 * KEY_SPACE \n
 * KEY_PGUP \n
 * KEY_PAGEUP \n
 * KEY_PGDN \n
 * KEY_PAGEDOWN \n
 * KEY_END \n
 * KEY_HOME \n
 * KEY_LEFT \n
 * KEY_LEFTARROW \n
 * KEY_RIGHT \n
 * KEY_RIGHTARROW \n
 * KEY_UP \n
 * KEY_UPARROW \n
 * KEY_DOWN \n
 * KEY_DOWNARROW \n
 * KEY_SELECT \n
 * KEY_EARLYPRINT \n
 * KEY_EARLYPRINTSCREEN \n
 * KEY_EXECUTE \n
 * KEY_PRINT \n
 * KEY_PRINTSCREEN \n
 * KEY_INS \n
 * KEY_INSERT \n
 * KEY_DEL \n
 * KEY_DELETE \n
 * KEY_HELP \n
 * \n
 * KEY_0 \n
 * KEY_1 \n
 * KEY_2 \n
 * KEY_3 \n
 * KEY_4 \n
 * KEY_5 \n
 * KEY_6 \n
 * KEY_7 \n
 * KEY_8 \n
 * KEY_9 \n
 *  \n
 * KEY_A \n
 * KEY_B \n
 * KEY_C \n
 * KEY_D \n
 * KEY_E \n
 * KEY_F \n
 * KEY_G \n
 * KEY_H \n
 * KEY_I \n
 * KEY_J \n
 * KEY_K \n
 * KEY_L \n
 * KEY_M \n
 * KEY_N \n
 * KEY_O \n
 * KEY_P \n
 * KEY_Q \n
 * KEY_R \n
 * KEY_S \n
 * KEY_T \n
 * KEY_U \n
 * KEY_V \n
 * KEY_W \n
 * KEY_X \n
 * KEY_Y \n
 * KEY_Z \n
 *
 * KEY_a \n
 * KEY_b \n
 * KEY_c \n
 * KEY_d \n
 * KEY_e \n
 * KEY_f \n
 * KEY_g \n
 * KEY_h \n
 * KEY_i \n
 * KEY_j \n
 * KEY_k \n
 * KEY_l \n
 * KEY_m \n
 * KEY_n \n
 * KEY_o \n
 * KEY_p \n
 * KEY_q \n
 * KEY_r \n
 * KEY_s \n
 * KEY_t \n
 * KEY_u \n
 * KEY_v \n
 * KEY_w \n
 * KEY_x \n
 * KEY_y \n
 * KEY_z \n
 *
 **/

#include <stdint.h>
#include <unistd.h>

/// This will define Windows as the current operating system.
#define OS_WIN32 1
/// This will define Linux as the current operating system.
#define OS_LINUX 2

#define OS_32_BIT 32

#define OS_64_BIT 64

#ifdef __linux
    #define WT_OS_TYPE OS_LINUX
#endif

#ifdef __WIN32
    #define WT_OS_TYPE OS_WIN32
    #ifdef __WIN64
        #define WT_OS_BITS OS_64_BIT
    #else
        #define WT_OS_BITS OS_32_BIT
    #endif
#endif

#if defined(__i386__)
	#define WT_OS_BITS OS_32_BIT
#elif defined(__x86_64__)
   #define WT_OS_BITS OS_64_BIT
#else
	#warning comment Base Pointer size undetectable for your archetecture. Needs to be set manually in WTDivWin.h . Library may need recompiling.
#endif

//Manual def of OS Type.
#ifndef WT_OS_TYPE
    #warning comment OS Not Detected.
    #define WT_OS_TYPE OS_LINUX
#endif

//Manual definition of pointer size for Architecture base.
#ifndef WT_OS_BITS
    #warning comment OS Bit Base Not Detected.
    #define WT_OS_BITS OS_32_BIT
#endif

#if WT_OS_TYPE==OS_WIN32
	#include <windows.h>

    #define GLEW_STATIC 1

	#include <GL/glew.h>
    #include "./Windows/ExtensionWrapper/glext.h"
    #include "./Windows/ExtensionWrapper/wglext.h"
    #include <GL/gl.h>
    //#include <GL/glext.h>


	//#include "./Windows/gl3.h"
    #include "./Windows/ExtensionWrapper/ExtensionWrapper.h"

    #include <al.h>
    #include <alc.h>

	#include "./Windows/WTWindowsKeyCodes.h"
#endif

#if WT_OS_TYPE==OS_LINUX
	#include <GL/glxew.h>

	#include <sys/time.h>

	#include <X11/keysym.h>
	#include <X11/Xlib.h>
	#include <X11/X.h>

#include <AL/al.h>
#include <AL/alc.h>

	#include "./Windows/WTXWindowsKeyCodes.h"
#endif

#include "./Global/WTDefinitions.h"
#include "./Global/WTSettings.h"


#include "./Global/WTSetDefinitions.h"
#include "./Global/WTGameSettings.h"
#include "./Global/IMFDefinitions.h"
#include "./Global/WTcFlags.h"


#include <typeinfo>

//#include <GL/gl.h>




#include <cmath>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

#include "./Global/GlobalPointers.h"
#include "./Global/log.h"
#include "./Global/CException.h"

#include "./PTL/WTRadix.h"
#include "./Windows/WTcSync.h"

#include "./Windows/WTcWindow.h"

#include "./PTL/WTLLTemplate.h"
#include "./PTL/WTMinLinkedList.h"
#include "./PTL/WTLimitedList.h"
#include "./PTL/WTcPushPopStack.h"


#include "./Maths/WTMath.h"
#include "./Maths/WTcMatrix4.h"
#include "./Maths/WTcPerspectiveMatrix.h"
#include "./Maths/WTcMatrixStack.h"
#include "./Maths/WTcCameraMatrix4.h"
#include "./Files/WTString.h"

#include "./Engine/WTcSignal.h"
#include "./Engine/Process/WTvProcess.h"
#include "./Engine/WTKernel.h"
#include "./Engine/Process/WTcParentStack.h"
#include "./Engine/Process/WTcProcess.h"
#include "./Engine/WTcFrameRate.h"

#include "./Files/WTvFile.h"
#include "./Files/WTcFileHandler.h"
#include "./Files/WTcFile.h"

#include "./Files/Misc/WTcReferenceList.h"

#include "./Files/WTcIMFLoader.h"

#include "./Files/Meshes/MeshClasses/WTcVertex.h"
#include "./Files/Meshes/MeshClasses/WTcPlane.h"
#include "./Files/Meshes/MeshClasses/WTcFace.h"
#include "./Files/Meshes/MeshClasses/WTcFullFaceData.h"
#include "./Files/Meshes/MeshClasses/WTcPolygon.h"
#include "./Files/Meshes/MeshClasses/WTcCluster.h"


#include "./Files/CollisionMeshes/WTvCollisionData.h"
//#include "./Files/CollisionMeshes/WTcCollisionMesh.h"


#include "./Files/Textures/WTvTexture.h"
#include "./Files/Textures/WTcTexture.h"

#include "./Files/Fonts/WTvFont.h"
#include "./Files/Fonts/WTcFont.h"

#include "./Files/Shaders/WTvShader.h"
#include "./Files/Shaders/WTcShader.h"
#include "./Files/Shaders/WTcShaderVariables.h"
#include "./Files/Shaders/WTvShaderProgram.h"
#include "./Files/Shaders/WTcShaderProgram.h"
#include "./Files/Shaders/WTcUserDefinedShaderVariable.h"


#include "./Camera/FX/WTcFog.h"
#include "./Camera/WTvRenderObject.h"
#include "./Files/Meshes/WTvMesh.h"
#include "./Files/Meshes/WTcMesh.h"

#include "./Files/Misc/WTcMeshTreeNode.h"
#include "./Files/Misc/WTvMeshTree.h"
#include "./Files/Misc/WTcMeshTree.h"

#include "./Files/Meshes/WTv2DPolygon.h"

#include "./Physics/WTcCollisionObject.h"

#include "./Camera/WTcCamera.h"
#include "./Camera/WTcRenderPointer.h"
#include "./Camera/WTcRenderObject.h"

#include "./Camera/Nodes/WTcRenderNode.h"

#include "./Files/Meshes/WTvmLandscape.h"
#include "./Files/Meshes/WTcmLandscape.h"


         #include "./Camera/FX/WTcMaterial.h"

	 #include "./Camera/FX/WTvLight.h"
	 #include "./Camera/WTcLightHandler.h"
         #include "./Camera/FX/WTcLight.h"
         #include "./Camera/FX/WTcSpotLight.h"

         #include "./Camera/Renderable/WTcImage.h"
         #include "./Camera/Renderable/WTcTextureText.h"
         #include "./Camera/Renderable/WTcTexturedModel.h"
         #include "./Camera/Renderable/WTcModelList.h"
         #include "./Camera/Renderable/WTcLandscape.h"
	 #include "./Camera/Renderable/WTcPoint.h"
	 #include "./Camera/Renderable/WTcLine.h"
	 #include "./Camera/Renderable/WTcParticleGroup.h"
	 #include "./Camera/Renderable/WTcParticle.h"
	 #include "./Camera/Renderable/WTcBeamMesh.h"

#include "./Camera/WTcPainter.h"

#include "./Windows/EventHandler/WTcKeyStore.h"
#include "./Windows/EventHandler/WTcMouse.h"
#include "./Windows/EventHandler/WTcEventHandler.h"

#include "./Audio/WTcAudioDevice.h"
#include "./Audio/WTcAudioBuffer.h"
#include "./Audio/WTcAudioObject.h"
#include "./Files/Audio/WTcWav.h"

#include "./Physics/WTcCollisionList.h"
#include "./Physics/WTcCollisionHandler.h"

#include "./Engine/WTcBase.h"
#endif
