#ifndef __WTDEFINITIONS_H__
#define __WTDEFINITIONS_H__


#define RANDOM_NUMBER static_cast<double>(rand())/static_cast<double>(RAND_MAX)
#define ZEROED_RANDOM_NUMBER ((static_cast<double>(rand())/static_cast<double>(RAND_MAX)-0.5)*2)

#define SIGNAL unsigned char

#if WT_OS_BITS==OS_32_BIT

	#define int64 long long
	#define int32 long
	#define int16 short
	#define int8  char

	#define uint64 unsigned int64
	#define uint32 unsigned int32
	#define uint16 unsigned int16
	#define uint8  unsigned int8

	#define bit bool

	#define real double
	#define integer long

	#define float80 long double
	#define float64 double
	#define float32 float

	#define psize uint32
	#define pbits (sizeof(uint32*)*8)
#endif

#if WT_OS_BITS==OS_64_BIT
	#define int64 long
	#define int32 int
	#define int16 short
	#define int8  char

	#define uint64 unsigned int64
	#define uint32 unsigned int32
	#define uint16 unsigned int16
	#define uint8  unsigned int8

	#define bit bool

	#define real double
	#define integer long

	#define float80 long double
	#define float64 double
	#define float32 float

	#define psize uint64
	#define pbits (sizeof(uint32*)*8)
#endif

#define _PROCESS(TYPE) class TYPE : public cProcess

#define WT_EXIT_SUCCESS 0
#define WT_FORCED_EXIT 1
#define WT_AUDIO_BUFFER_ERROR 2
#define WT_AUDIO_FILE_LOAD_ERROR 3
#define WT_AUDIO_DEVICE_OPENING_ERROR 4


/// This tells a cCollisionObject to use a spherical collision for detecting collisions.
#define WT_COLLISION_RADIUS 1
/// This tells a cCollisionObject to use a cCollisionMesh to determine Collisions.
#define WT_COLLISION_MODEL 2
/// This tells a cCollisionObject to use a Ray to determine Collisions.
#define WT_COLLISION_RAY 3
/// This tells a cCollisionObject to use a Plane to determine Collisions.
#define WT_COLLISION_PLANE 4
/// This is the type for a cCollisionObject using a beam object for collisions.
#define WT_COLLISION_BEAM 5
///This tells a cCollisionObject to use a Landscape to determine collisions.
#define WT_COLLISION_LANDSCAPE 5


#define WT_LINEFEED 0x0A
#define WT_CARRIAGERETURN 0x0D
#define WT_NEWLINE 0x0D0A


///This is a quick code for accessing the pointer to the mouse of type cMouse.
#define _MOUSE cEventHandler::Instance()->Mouse()
///This is a quick code for accessing Key states, returns a bool, for _CHOSEN_KEY.
#define _KEY(_CHOSEN_KEY) cEventHandler::Instance()->Key.GetKey(_CHOSEN_KEY)
///This is a quick code for accessing the Keyboard object of type cKeyStore.
#define _KEYBOARD cEventHandler::Instance()->Keyboard()

///This is a quick code for Loading an IMF file with cIMF::L0.0oadIMF()
#define _LOAD_FILE(FileName) cIMF::LoadIMF(FileName)
///This is a quick macro for returning the pointer to a file. (cFileHandler::File()).
#define _GET_FILE(FileType,FileName) (cFileHandler::Instance()->File<FileType>(FileName))

///Will activate the shader with the reference. This is a slow and inefficient way to call shaders. Get a pointer and call ->Use().
#define _USE_SHADER(FileName) _GET_FILE(cShaderProgram,FileName)->Use()

///Will return a pointer to a Shader Program object in memory with the text identifier Reference.
#define _GET_SHADER_FILE(Reference) _GET_FILE(cShaderProgram,Reference)
///Will return a pointer to a Texture object in memory with the text identifier Reference.
#define _GET_TEXTURE_FILE(Reference) _GET_FILE(cTexture,Reference)
///Will return a pointer to a Mesh object in memory with the text identifier Reference.
#define _GET_MESH_FILE(Reference) _GET_FILE(cMesh,Reference)
///Will return a pointer to a Font object in memory with the text identifier Reference.
#define _GET_FONT_FILE(Reference) _GET_FILE(cFont,Reference)
///Will return a pointer to a Audio Data object in memory with the text identifier Reference.
#define _GET_AUDIO_FILE(Reference) _GET_FILE(cSoundObject,Reference)
///Will return a pointer to a Collision Mesh object in memory with the text identifier Reference.
#define _GET_COLLISION_MESH_FILE(Reference) _GET_FILE(cMeshFileCollision,Reference)
///Will return a pointer to a Landscape Mesh object in memory with the text identifier Reference.
#define _GET_LANDSCAPE_FILE(Reference) _GET_FILE(cLandscapeMeshFile,Reference)

///Will turn off Shaders. If an object has a shader set it will override this. Also note that Fixed function is much much slower than using shaders.
#define _USE_FIXED_FUNCTION() cShaderProgram::UseFixedFunction()

#define _MODEL_POINTER cTexturedModel*
#define _LAND_POINTER cLandscape*
#define _IMAGE_POINTER cImage*
#define _TEXT_POINTER cTexturedText*
#define _AUDIO_POINTER cAudioObject*
#define _BEAM_POINTER cBeamMesh*
#define _COLLISION_POINTER cCollisionObject*


#define WT_SIGNAL_VALUE_ALIVE 0x1
#define WT_SIGNAL_VALUE_WAKE 0x2
#define WT_SIGNAL_VALUE_TREE 0x4
#define WT_SIGNAL_VALUE_KILL 0x8
#define WT_SIGNAL_VALUE_SLEEP 0x10


#define _S_WAKE (WT_SIGNAL_VALUE_ALIVE|WT_SIGNAL_VALUE_WAKE)
#define _S_SLEEP (WT_SIGNAL_VALUE_ALIVE|WT_SIGNAL_VALUE_SLEEP)
#define _S_KILL (WT_SIGNAL_VALUE_KILL)
#define _S_WAKE_TREE (_S_WAKE|WT_SIGNAL_TREE)
#define _S_SLEEP_TREE (_S_SLEEP|WT_SIGNAL_TREE)
#define _S_KILL_TREE (_S_KILL|WT_SIGNAL_TREE)

///This is a quick code for accessing the pointer to cCamera()
#define _CAMERA cCamera::Instance()
///This is a quick code for accessing the pointer to cLightHandler()
#define _LIGHT cLightHandler::Instance()
///This is a quick code for accessing the pointer to cKernel()
#define _KERNEL cKernel::Instance()
///This is a quick code for accessing the pointer to cFileHandler()
#define _FILE cFileHandler::Instance()

///This is a quick code for accessing the pointer to cPainter()
#define _PAINTER cPainter::Instance()

///This is a quick code for Loading an IMF file with cIMF::LoadIMF()
#define _LOAD(FileName) cIMF::LoadIMF(FileName)

///This is a quick code for accessing the pointer to cCollisionHandler()
#define _COLLISION_HANDLER cCollisionHandler::Instance()
///This is a quick macro for Reseting the Collision Search
#define _RESET_COLLISION cCollisionHandler::Instance()->ResetSearch()


///This is a macro to create of new Process and Render objects.

///This is a macro to destroy the current process. Code after this statement will run once for this frame.
#define _KILL_THIS() Signal(_S_KILL)
///This is a macro to destroy Process and Render objects.
#define _KILL(Pointer) Pointer->Signal(_S_KILL)
///This is a macro to sleep the current process. Code after this statement will run once for this frame.
#define _SLEEP_THIS() Signal(_S_SLEEP)
///This is a macro to sleep Process and Render Objects. The object pointed to by Process will sleep. If the object has not run this frame it will not run. If it has already run, then it has already run.
#define _SLEEP(Process) Process->Signal(_S_SLEEP)
///This is a macro to wake Process and Render Objects. The object pointed to by Process will awaken. It may first run this frame or next (depending on order).
#define _WAKE(Process) Process->Signal(_S_WAKE)
///This is a macro to wake the current process. This is useless. As code in a sleeping process will never run.
#define _WAKE_THIS()

///Will enable the Uniform variable for an object linked to a shader. Each Object will have its own uniform variable. The variable is of Type TYPE and name VAR. (int, float, Matrix etc)
#define _ADD_UNIFORM(TYPE,VAR) AddUniform<TYPE>(VAR)

///This is a macro to declare the start of a Collision Loop cycling valid collision processes. It will cycle every valid process pointer.
#define _COLLISION_PROCESS_LOOP(lpList,lpVar) for(lpVar=lpList->NextCollisionP();lpVar;lpVar=lpList->NextCollisionP())


///This will allow the user to create a new process of Type TYPE. This can be handed initialisation values.
#define _CREATE(TYPE) new TYPE
///This is for returning a pointer when parent tracking is enabled.
#define _CREATE_CHILD(POINTER,TYPE) gpParent=this; POINTER=new TYPE
//#define _CREATE(TYPE) cKernel::Instance()->CreateProcess<class TYPE>(this)
//#define _CREATE(TYPE(PARAMETERS)) cKernel::Instance()->CreateProcess<class TYPE>(this,PARAMETERS)

//First 16 bytes say 'HEY YOOOOUUU GUYS!' TURN all 1's on.
//Secdond 16 byte say 'HEY YOOOUUU GUYS!' Turn all 1's off;
//Can only use first 16 bytes to check that flags are on.


///This is the code to say that the current cCollisionHandler() will check Collisions based on a Tree structure.
#define WT_COLLISION_HANDLER_TYPE_TREE 0x1
///This is the code to say that the current cCollisionHandler() will check Collisions based on a Type sorting structure.
#define WT_COLLISION_HANDLER_TYPE_TYPE 0x2
///This is the code to say that the current cCollisionHandler() will check Collisions based on a Binary spatial partitioning structure.
#define WT_COLLISION_HANDLER_TYPE_BSP 0x3

///This is the code to set a BSP cCollisionHandler() to use 1 dimension.
#define WT_COLLISION_HANDLER_DIMENSIONS_1D 0x1
///This is the code to set a BSP cCollisionHandler() to use 2 dimensions.
#define WT_COLLISION_HANDLER_DIMENSIONS_2D 0x2
///This is the code to set a BSP cCollisionHandler() to use 3 dimensions.
#define WT_COLLISION_HANDLER_DIMENSIONS_3D 0x3

/// This will return the proportion of a second the last frame took to process. Multiply a speed value by this and it will be adjusted to be a constant speed irrespective of frame rate.
#define WT_TIME_IND gpTimer->GetTimeMod()


///Flags for Arc limitation Code X Axis.
#define __ARC_LIMITATION_X_AXIS 0
///Flags for Arc limitation Code Y Axis.
#define __ARC_LIMITATION_Y_AXIS 1
///Flags for Arc limitation Code Z Axis.
#define __ARC_LIMITATION_Z_AXIS 2

///Flags for Arc limitation Code defining the X component of the relevant axis.
#define __ARC_LIMITATION_X_COMPONENT 0
///Flags for Arc limitation Code defining the Y component of the relevant axis.
#define __ARC_LIMITATION_Y_COMPONENT 1
///Flags for Arc limitation Code defining the Z component of the relevant axis.
#define __ARC_LIMITATION_Z_COMPONENT 2

///Flag defining the current Arc limit as an Upper Limit.
#define __ARC_LIMITATION_UPPER_LIMIT 0
///Flag defining the current Arc limit as an Lower Limit.
#define __ARC_LIMITATION_LOWER_LIMIT 1
///Flag defining the current Arc limit as a Fixed Value.
#define __ARC_LIMITATION_FIXED_LIMIT 2

/// The environments Gravity Setting for the X axis. This will only affect cGravityParticles and cMovement.
#define _PARTICLE_GRAV_X _GRAVITY_X*WT_TIME_IND
/// The environments Gravity Setting for the Y axis. This will only affect cGravityParticles and cMovement.
#define _PARTICLE_GRAV_Y _GRAVITY_Y*WT_TIME_IND
/// The environments Gravity Setting for the Z axis. This will only affect cGravityParticles and cMovement.
#define _PARTICLE_GRAV_Z _GRAVITY_Z*WT_TIME_IND

/// The environments wind Settings for the X axis. This will only affect cMovement.
#define _PARTICLE_WIND_X _WIND_X*WT_TIME_IND
/// The environments wind Settings for the Y axis. This will only affect cMovement.
#define _PARTICLE_WIND_Y _WIND_Y*WT_TIME_IND
/// The environments wind Settings for the Z axis. This will only affect cMovement.
#define _PARTICLE_WIND_Z _WIND_Z*WT_TIME_IND

#define WT_LANDSCAPE_TEXTURE_METHOD_WHOLE 0
#define WT_LANDSCAPE_TEXTURE_METHOD_INDIVIDUAL 1
#define WT_LANDSCAPE_TEXTURE_METHOD_RANDOM 2

///Accessor for the Frame Rate class. Returns a pointer to the class for controlling Frame rate.
#define _FRAME_RATE cFrameRate::Instance()
///Returns a float specifying the current time for a frame measured in seconds.
#define _TIME_PER_FRAME _FRAME_RATE->FrameTime()
///Returns an unsigned integer specifying the number of frames per second.
#define _FPS _FRAME_RATE->FramesPerSecond()
///Returns an unsigned integer specifying number of processor cycles run for each frame.
#define _PPF _FRAME_RATE->ProcessesPerFrame()
///Returns a float specifying the amount of time for each process in seconds.
#define _PROCESS_TIME _FRAME_RATE->ProcessTime()

#if WT_OS_TYPE==OS_WIN32
	///Function which will start the engine running. See \ref DivWinExplanation.
	#define _START_PROGRAM(TYPE,SETTINGS,INSTANCE) cMainThread<TYPE,SETTINGS>::Start(INSTANCE)

	#if WT_OS_BITS==OS_32_BIT
		#define UINT_MAX 0xFFFFFFFF
	#endif
	#if WT_OS_BITS==OS_64_BIT
		#define UINT_MAX 0xFFFFFFFFFFFFFFFF
	#endif
#endif

#if WT_OS_TYPE==OS_LINUX
	///Function which will start the engine running. See \ref DivWinExplanation.
	#define _START_PROGRAM(TYPE,SETTINGS) cMainThread<TYPE,SETTINGS>::Start()

#endif
/// Function for accessing cKernel::FindProcess(). Will search for any Process of class type TYPE.
#define _FIND_PROCESS(TYPE) _KERNEL->FindProcess<TYPE>()

///Pointer to the Matrix Stack.
#define _MATRIX_STACK cMatrixStack::Instance()
///Allows the User to set the maximum depth the Matrix stack will store.
#define _MATRIX_STACK_MAX_DEPTH(VALUE) cMatrixStack::SetDepth(VALUE)

#endif
