﻿#ifndef __WTBAMBOO_H__
#define __WTBAMBOO_H__



/**
 * \mainpage Starting with @EngineName
 * \section MainPageIntro Introduction
 * The @EngineName manual has several main sections.
 * - There is a section on installing @EngineName. This explains how to set up @EngineName for use.
 * - The lists of useful functions, and pre set variables are at the start of the document to make them easy to find and reference. You will refer back to these regularly while programming.
 * - There is a sction explaining the basics of programming. If you have not programmed before this is the place to start.
 * - There is the section explaining the different sections of the engine and how to use them. This is recommended as the first section to be read.
 * - Finally there is the section detailing all the classes you may use while making games. This is an advanced section and useful for learning more advanced topics.
 * .
 *
 * \section InstallationMainPage Installation
 * Windows:
 * Currently Codeblocks is the recommended IDE for using @EngineName. Codeblocks should be installed first, followed by @EngineName.msi. Installation of @EngineName will require admin access.
 *
 * Linux:
 * Run Install.sh. This will install @EngineName and fetch the required dependancies.
 *
 * \section NewProjectMainPage Starting a new Project
 * A New project can be started from Codeblocks:
 * - Open Codeblocks
 * - Click File->New->Project From Template.
 * - Select '@EngineName Project' or '@EngineName Project Win'
 * - Follow the dialogues and give it its own folder.
 * - Insert Code
 * .
 * \page ReferenceLists Reference Lists
 * This Section contains useful lists and information which may require regular visitation while using Bamboo.
 * -# \ref MacroListPage "List of Useful Macros"
 * -# \ref MatrixUsagePage "Positioning, Rotating and Moving Objects"
 * -# \ref CameraMatrixUsagePage "Positioning, Rotationg and Aiming the Camera"
 * -# \ref KeyIdentifiersList "List of Key Identifiers"
 * -# \ref EngineSettingsPage "Engine Settings"
 * -# \ref ObjectsUsingTheCreateMacro "List of types owned by Bamboo"
 * .
 * \section MacroListPage List of Useful Macros
 * This section contains a list of useful Macros for accessing various functions or variables.
 *  - RANDOM_NUMBER
 *  	- returns a Randomly generated number between 0.0f and 1.0f.
 *  	.
 *  - SIGNAL()
 *  	- A Class Type for passing Signals between Process', Render Objects and Collision Objects.
 *  	.
 *  - _KEY(KEY_CODE_ID)
 *  	- Function for accessing the array of key states. Takes Key ident as an input. Key Idents are defined in the Key List and start 'KEY_CODE_' .
 *  	.
 *  - _MOUSE
 *  	- Reference giving access the systems mouse states.
 *  	.
 *  - _LOAD(FileName)
 *  	- Function for loading a file. Takes the filename as an input. Same as _LOAD_FILE(FileName);
 *  	.
 *  - _LOAD_FILE(FileName)
 *  	- Function for loading a file. Takes the filename as an input. Same as _LOAD(FileName);
 *  	.
 *  - _GET_FILE(FileType,FileName)
 *  	- Function returning a pointer of type FileType to the IMF Object with the reference FileName.
 *  	.
 *  - _CREATE(Type)
 *  	- Function operating like the new operator. Will create a new Process, Render Object or Collision Object and return a pointer of type Type.
 *  	.
 *  - _KILL_THIS()
 *  	- Will Kill the current process.
 *  	.
 *  - _KILL(Pointer)
 *  	- Will Kill the process pointed to by Pointer.
 *  	.
 *  - _SLEEP(Process)
 *  	- Will Sleep the process pointer to by Process.
 *  	.
 *  - _SLEEP_THIS()
 *  	- Will Sleep the current process.
 *  	.
 *  - _WAKE(Process)
 *  	- Will Wake the process pointed to by Process.
 *  	.
 *  - _SIGNAL(Flag)
 *  	- Function which will send a signal to the process this function is called from, to signal the action, Flag. (Signal Flags are defined in the Signal List).
 *  	.
 *  - _USE_SHADER(FileName)
 *  	- Function telling the system to buffer for use the shader with reference FileName.
 *  	.
 *  - _GET_SHADER_FILE(Reference)
 *  	- Function returning a pointer to the cShaderProgram with the name Reference.
 *  	.
 *  - _GET_TEXTURE_FILE(Reference)
 *  	- Function returning a pointer to the vTexture Object with the name Reference.
 *  	.
 *  - _GET_MESH_FILE(Reference)
 *  	- Function returning a pointer to the vMesh Object with the name Reference.
 *  	.
 *  - _GET_FONT_FILE(Reference)
 *  	- Function returning a pointer to the cFont Object with the name Reference.
 *  	.
 *  - _GET_AUDIO_FILE(Reference)
 *  	- Function returning a pointer to the cAudioData Object with the name Reference.
 *  	.
 *  - _GET_COLLISION_MESH_FILE(Reference)
 *  	- Function returning a pointer to the cCollisionBoxFile Object with the name Reference (Collision Mesh).
 *  	.
 *  - _GET_LANDSCAPE_FILE(Reference)
 *  	- Function returning a pointer to the cmLandscape Object with the name Reference.
 *      .
 *  - _GET_COMPOUND_COLLISION_FILE(Reference)
 * 	    - Function returning a pointer to the cCompoundCollisonFile Object with the name Reference.
 *      .
 *  - _GET_MODELLIST_FILE(Reference)
 * 	    - Function returning a pointer to the cMeshTree Object with the name Reference.
 *  	.
 *  - _USE_FIXED_FUNCTION()
 *  	- Function telling the system to used the fixed function pipeline and not use shaders. This will slow the system and disable functionality. Disadvised.
 *  	.
 *  - _CAMERA
 *  	- A Pointer to the default cCamera Object.
 *  	.
 *  - _LIGHT
 *  	- A Pointer to the cLightHandler Object.
 *  	.
 *  - _KERNEL
 *  	- A Pointer to the cKernel Object.
 *  	.
 *  - _FILE
 *  	- A Pointer to the cFileHandler Object.
 *  	.
 *  - _COLLISION_HANDLER
 *  	- A Pointer to the cCollisionHandlerObject.
 *  	.
 *  - _RESET_COLLISION
 *  	- This will reset a stepping Collision Search, ready for a fresh search. (Not issue for Generating Collision Lists)
 *  	.
 *  - WT_TIME_IND
 *  	- This is the current frame length in seconds. Multiply anything time dependant by this to make it time independant. (It is a float multiplyer, think before use.)\n
 *  	.
 *  - _COLLISION_PROCESS_LOOP(lpList,lpVar)
 *  	- This will start a Loop to step through a collision list. lpList should point to the Collision List and lpVar will point at the current process in the collision list.\n
 *  	.
 *  - _COLLISION_RENDER_LOOP(lpList,lpVar)
 *  	- This will start a Loop to step through a collision list. lpList should point to the Collision List and lpVar will point at the current Render object in the collision list.\n
 *  	.
 *  .
 *
 * \section MatrixUsagePage Positioning, Rotating and Moving Objects.
 * cMatrix4.h \n
 *
 * The cMatrix4 class and cCameraMatrix classes are very similar. See the . The cCameraMatrix4 maintains an inverted cMatrix4 matrix as the translations applied to the camera must be inverted to give the same effect as to normal objects. Otherwise the effects are the same for cMatrix4 and cCameraMatrix. \n
 * Most Render Objects have inherited the cMatrix4 class meaning that these functions can be called to move and rotate Render Objects. Calling these functions, will apply the defined translations to the current object. Some are relative to the current translation and some are relative to the position of the Render Node controlling this object. Either way, the translations stack. \n
 * It is important to note that although the cCameraMatrix4 and cMatrix4 can interact with each other (and be set to match each other) cCameraMatrix4 is the inverse of cMatrix4. Also the order of rotations and postions to use the matrix is different. They can transfer rotations and positions between they types using the Equals and Copy functions. \n
 * \n
 * The X Axis points 90 to the Right perpendicular to the objects facing. \n
 * The Y Axis points 90 Upwards, perpendicular to the objects facing. \n
 * The Z Axis is the objects facing. \n
 * \n
 * These Classes can be used for 2D or 3D Translations. There are different functions for 2D and 3D translations. The standard @EngineName Objects automatically identify if they should be 2D or 3D. \n
 * \n
 * void cMatrix4::Identity(); \n
 * void cMatrix4::Zero(); \n
 * \n
 * 3D Object Translation Functions: \n
 * void cMatrix4::Set3D() \n
 * float cMatrix4::Determinant(); \n
 * cMatrix4 cMatrix4::InvertRotationMatrix(); \n
 * cMatrix4 cMatrix4::Transpose(); \n
 * void cMatrix4::Translate(float lfX,float lfY,float lfZ); \n
 * \n
 * float* cMatrix4::Matrix(); \n
 * float* cMatrix4::Matrix(uint8 lcData); \n
 * float* cMatrix4::Position(); \n
 * float cMatrix4::X(); \n
 * float cMatrix4::Y(); \n
 * float cMatrix4::Z(); \n
 * float* cMatrix4::XVect(); \n
 * float* cMatrix4::YVect(); \n
 * float* cMatrix4::ZVect(); \n
 * \n
 * void cMatrix4::Position(float *lpPos); \n
 * void cMatrix4::PositionX(float lfX); \n
 * void cMatrix4::PositionY(float lfY); \n
 * void cMatrix4::PositionZ(float lfZ); \n
 * void cMatrix4::Position(cMatrix4 &lpOther); \n
 * void cMatrix4::Position(cMatrix4 *lpOther); \n
 * void cMatrix4::Position(c2DVf *lpPosition); \n
 * void cMatrix4::Position(float lfX,float lfY); \n
 * void cMatrix4::Position(c3DVf *lpPosition); \n
 * void cMatrix4::Position(float lfX,float lfY,float lfZ);\n
 * \n
 * void cMatrix4::Advance(float *lfDistance); \n
 * void cMatrix4::Advance(c2DVf *lfDistances); \n
 * void cMatrix4::Advance(c3DVf *lfDistances); \n
 * void cMatrix4::Advance(c2DVf &lfDistances); \n
 * void cMatrix4::Advance(c3DVf &lfDistances); \n
 * void cMatrix4::Advance(float lfDistance); \n
 * void cMatrix4::AdvanceX(float lfDistance); \n
 * void cMatrix4::AdvanceY(float lfDistance); \n
 * void cMatrix4::AdvanceZ(float lfDistance); \n
 * void cMatrix4::Advance(float lfX,float lfY); \n
 * void cMatrix4::Advance(float lfX,float lfY, float lfZ); \n
 * void cMatrix4::GAdvanceX(float lfX); \n
 * void cMatrix4::GAdvanceY(float lfX); \n
 * void cMatrix4::GAdvanceZ(float lfX); \n
 * void cMatrix4::GAdvance(float lfX,float lfY); \n
 * void cMatrix4::GAdvance(float lfX,float lfY,float lfZ); \n
 * \n
 * void cMatrix4::Angle(float lfAngle); \n
 * \n
 * void cMatrix4::GRotateOrigin(float lfAngle); \n
 * void cMatrix4::GRotate(float lfAngle,float lfX,float lfY); \n
 * \n
 * void cMatrix4::Rotation(float *lpRotation); \n
 * void cMatrix4::Rotation(cMatrix4 *lpRotation); \n
 * void cMatrix4::Rotation(cMatrix4 &lpOther); \n
 * \n
 * void cMatrix4::Rotate(float lfAngle); \n
 * void cMatrix4::RotateX(float lfAngle); \n
 * void cMatrix4::RotateY(float lfAngle); \n
 * void cMatrix4::RotateZ(float lfAngle); \n
 * \n
 * void cMatrix4::GRotateX(float lfAngle); \n
 * void cMatrix4::GRotateY(float lfAngle); \n
 * void cMatrix4::GRotateZ(float lfAngle); \n
 * \n
 * void cMatrix4::GRotateX(float lfAngle,float lfX,float lfY,float lfZ); \n
 * void cMatrix4::GRotateY(float lfAngle,float lfX,float lfY,float lfZ); \n
 * void cMatrix4::GRotateZ(float lfAngle,float lfX,float lfY,float lfZ); \n
* \n
 * void cMatrix4::GRotateOriginX(float lfAngle); \n
 * void cMatrix4::GRotateOriginY(float lfAngle); \n
 * void cMatrix4::GRotateOriginZ(float lfAngle); \n
 * \n
 * void cMatrix4::Equals(float *lpOther); \n
 * void cMatrix4::Equals(cMatrix4 *lpOther); \n
 * void cMatrix4::Equals(cMatrix4 &lpOther); \n
 * void cMatrix4::Equals(cCameraMatrix4 &lpOther); \n
 * void cMatrix4::Equals(cCameraMatrix4 *lpOther); \n
 * \n
 * void cMatrix4::Resize(float lfScale); \n
 * \n
 * void cMatrix4::LResizeX(float lfScale); \n
 * void cMatrix4::LResizeY(float lfScale); \n
 * void cMatrix4::LResizeZ(float lfScale); \n
 * \n
 * void cMatrix4::GResizeX(float lfScale); \n
 * void cMatrix4::GResizeY(float lfScale); \n
 * void cMatrix4::GResizeZ(float lfScale); \n
 * \n
 * float cMatrix4::Distance(cMatrix4 *lpOther); \n
 * float cMatrix4::Distance(float *lpOther); \n
 * double cMatrix4::DistanceSq(cMatrix4 *lpOther); \n
 * double cMatrix4::DistanceSq(cMatrix4 lpOther); \n
 * double cMatrix4::DistanceSq(float *lpOther); \n
 * \n
 * float &cMatrix4::operator[](uint16 liPos); \n
 * float &cMatrix4::operator()(uint16 liColumn,uint16 liRow);
 * \n
 * 2D Object Translation Functions: \n
 * void cMatrix4::Set2D() \n
 * \n
 * void cMatrix4::Advance(float lfX,float lfY) \n
 * void cMatrix4::GAdvance(float lfX,float lfY) \n
 * \n
 * void cMatrix4::Angle(float lfAngle) \n
 * void cMatrix4::Rotate(float lfAngle) \n
 * void cMatrix4::GRotateOrigin(float lfAngle) \n
 * void cMatrix4::GRotate(float lfAngle,float lfX,float lfY) \n
 *
 * \section CameraMatrixUsagePage Positioning, Rotating and Moving The Camera
 * cCameraMatrix4.h
 * \n
 * The cCameraMatrix4 is the matrix used for the camera. The format is different to the cMatrix4 class as it is used in a different manner. Many of the functions are called the same thing and have the same function.
 * It also has a few additional functions which are useful for Camera manipulation. \n
 * \n
 * float* cCameraMatrix4::Matrix() \n
 * float* cCameraMatrix4::Position() \n
 * \n
 * float cCameraMatrix4::X() \n
 * float cCameraMatrix4::Y() \n
 * float cCameraMatrix4::Z() \n
 * \n
 * void cCameraMatrix4::Position(c3DVf *lpPosition) \n
 * void cCameraMatrix4::Position(float lfX,float lfY,float lfZ) \n
 * void cCameraMatrix4::PositionX(float lfX) \n
 * void cCameraMatrix4::PositionY(float lfY) \n
 * void cCameraMatrix4::PositionZ(float lfZ) \n
 * \n
 * void cCameraMatrix4::AdvanceX(float lfDistance) \n
 * void cCameraMatrix4::AdvanceY(float lfDistance) \n
 * void cCameraMatrix4::AdvanceZ(float lfDistance) \n
 * void cCameraMatrix4::Advance(float lfX,float lfY,float lfZ) \n
 * \n
 * void cCameraMatrix4::GAdvanceX(float lfDistance) \n
 * void cCameraMatrix4::GAdvanceY(float lfDistance) \n
 * void cCameraMatrix4::GAdvanceZ(float lfDistance) \n
 * void cCameraMatrix4::GAdvance(float lfX,float lfY,float lfZ) \n
 * \n
 * void cCameraMatrix4::Rotate(float lfAngle) \n
 * void cCameraMatrix4::RotateX(float lfAngle) \n
 * void cCameraMatrix4::RotateY(float lfAngle) \n
 * void cCameraMatrix4::RotateZ(float lfAngle) \n
 * \n
 * void cCameraMatrix4::GRotateX(float lfAngle) \n
 * void cCameraMatrix4::GRotateY(float lfAngle) \n
 * void cCameraMatrix4::GRotateZ(float lfAngle) \n
 * \n
 * void cCameraMatrix4::GRotateX(float lfAngle,float lfX,float lfY,float lfZ) \n
 * void cCameraMatrix4::GRotateY(float lfAngle,float lfX,float lfY,float lfZ) \n
 * void cCameraMatrix4::GRotateZ(float lfAngle,float lfX,float lfY,float lfZ) \n
 * \n
 * void cCameraMatrix4::Resize(float lfScale) \n
 * void cCameraMatrix4::ResizeX(float lfScale) \n
 * void cCameraMatrix4::ResizeY(float lfScale) \n
 * void cCameraMatrix4::ResizeZ(float lfScale) \n
 * \n
 * void cCameraMatrix4::GResizeX(float lfScale) \n
 * void cCameraMatrix4::GResizeY(float lfScale) \n
 * void cCameraMatrix4::GResizeZ(float lfScale) \n
 * \n
 * uint32 cCameraMatrix4::Distance3D(float *lpOther) \n
 * \n
 * void cCameraMatrix4::Follow(cMatrix4* lpOther,float lfDist) \n
 * void cCameraMatrix4::Follow(cMatrix4& lpOther,float lfDist) \n
 * void cCameraMatrix4::PointAt(float *mpPos) \n
 * void cCameraMatrix4::PointAt(cMatrix4 *mpPos) \n
 * void cCameraMatrix4::PointAt(cMatrix4 &mpPos) \n
 * void cCameraMatrix4::PointAt(c3DVf &mpPos) \n
 * void cCameraMatrix4::PointAt(c3DVf *mpPos) \n
 * \n
 * void cCameraMatrix4::Equals(cCameraMatrix4 *lpOther) \n
 * void cCameraMatrix4::Equals(cCameraMatrix4 &lpOther) \n
 * void cCameraMatrix4::Equals(cMatrix4 *lpOther) \n
 * void cCameraMatrix4::Equals(cMatrix4 &lpOther) \n
 * \n
 * void cCameraMatrix4::Multiply(cCameraMatrix4 *lpOther) \n
 * void cCameraMatrix4::Multiply(cCameraMatrix4 &lpOther) \n
 * void cCameraMatrix4::Multiply(cMatrix4 *lpOther) \n
 * void cCameraMatrix4::Multiply(cMatrix4 &lpOther) \n
 * \n
 * float &cCameraMatrix4::operator[](uint16 liPos) \n
 * float &cCameraMatrix4::operator()(uint16 liColumn,uint16 liRow) \n
 * \n
 * void cCameraMatrix4::Position(c2DVf *lpPosition) \n
 * void cCameraMatrix4::Position(float lfX,float lfY) \n
 * void cCameraMatrix4::Angle(float lfAngle) \n
 * uint32 cCameraMatrix4::Distance2D(float *lpOther) \n
 *
 * cMatrix4 &cCameraMatrix4::ConvertToMatrix() \n
 * cCameraMatrix4 cCameraMatrix4::Transpose() \n
 * void cCameraMatrix4::InvSign() \n
 * void cCameraMatrix4::Identity() \n
 * void cCameraMatrix4::Zero() \n
 * float cCameraMatrix4::Determinant() \n
 *
 * \section KeyIdentifiersList List of Key Identifiers
 *
 * These correspond to the states of keys:
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
 *  There are also accessor codes for the Macro _KEY(). These are actually unsigned integers and so can be passed as parameters.
 *
 * \code
 * if(_KEY(KEY_CODE_SPACE)) _CREATE(Bulltets());
 * if(_KEY(KEY_CODE_TAB)) _KERNEL->KillAll();
 *
 * \endcode
 *
 * KEY_CODE_BACKSPACE \n
 * KEY_CODE_TAB \n
 * KEY_CODE_ENTER \n
 * KEY_CODE_RETURN \n
 * KEY_CODE_SHIFT \n
 * KEY_CODE_CONTROL \n
 * KEY_CODE_CTRL \n
 * KEY_CODE_ALTERNATE \n
 * KEY_CODE_ALT \n
 * KEY_CODE_PAUSE \n
 * KEY_CODE_CAPSLOCK \n
 * KEY_CODE_CAPITALLOCK \n
 * KEY_CODE_ESCAPE \n
 * KEY_CODE_ESC \n
 * KEY_CODE_SPACE \n
 * KEY_CODE_PGUP \n
 * KEY_CODE_PAGEUP \n
 * KEY_CODE_PGDN \n
 * KEY_CODE_PAGEDOWN \n
 * KEY_CODE_END \n
 * KEY_CODE_HOME \n
 * KEY_CODE_LEFT \n
 * KEY_CODE_LEFTARROW \n
 * KEY_CODE_RIGHT \n
 * KEY_CODE_RIGHTARROW \n
 * KEY_CODE_UP \n
 * KEY_CODE_UPARROW \n
 * KEY_CODE_DOWN \n
 * KEY_CODE_DOWNARROW \n
 * KEY_CODE_SELECT \n
 * KEY_CODE_EARLYPRINT \n
 * KEY_CODE_EARLYPRINTSCREEN \n
 * KEY_CODE_EXECUTE \n
 * KEY_CODE_PRINT \n
 * KEY_CODE_PRINTSCREEN \n
 * KEY_CODE_INS \n
 * KEY_CODE_INSERT \n
 * KEY_CODE_DEL \n
 * KEY_CODE_DELETE \n
 * KEY_CODE_HELP \n
 * \n
 * KEY_CODE_0 \n
 * KEY_CODE_1 \n
 * KEY_CODE_2 \n
 * KEY_CODE_3 \n
 * KEY_CODE_4 \n
 * KEY_CODE_5 \n
 * KEY_CODE_6 \n
 * KEY_CODE_7 \n
 * KEY_CODE_8 \n
 * KEY_CODE_9 \n
 *  \n
 * KEY_CODE_A \n
 * KEY_CODE_B \n
 * KEY_CODE_C \n
 * KEY_CODE_D \n
 * KEY_CODE_E \n
 * KEY_CODE_F \n
 * KEY_CODE_G \n
 * KEY_CODE_H \n
 * KEY_CODE_I \n
 * KEY_CODE_J \n
 * KEY_CODE_K \n
 * KEY_CODE_L \n
 * KEY_CODE_M \n
 * KEY_CODE_N \n
 * KEY_CODE_O \n
 * KEY_CODE_P \n
 * KEY_CODE_Q \n
 * KEY_CODE_R \n
 * KEY_CODE_S \n
 * KEY_CODE_T \n
 * KEY_CODE_U \n
 * KEY_CODE_V \n
 * KEY_CODE_W \n
 * KEY_CODE_X \n
 * KEY_CODE_Y \n
 * KEY_CODE_Z \n
 *
 * KEY_CODE_a \n
 * KEY_CODE_b \n
 * KEY_CODE_c \n
 * KEY_CODE_d \n
 * KEY_CODE_e \n
 * KEY_CODE_f \n
 * KEY_CODE_g \n
 * KEY_CODE_h \n
 * KEY_CODE_i \n
 * KEY_CODE_j \n
 * KEY_CODE_k \n
 * KEY_CODE_l \n
 * KEY_CODE_m \n
 * KEY_CODE_n \n
 * KEY_CODE_o \n
 * KEY_CODE_p \n
 * KEY_CODE_q \n
 * KEY_CODE_r \n
 * KEY_CODE_s \n
 * KEY_CODE_t \n
 * KEY_CODE_u \n
 * KEY_CODE_v \n
 * KEY_CODE_w \n
 * KEY_CODE_x \n
 * KEY_CODE_y \n
 * KEY_CODE_z \n
 *
 * \section EngineSettingsPage Engine Settings
 *
 * This Section contains the complete list of engine settings. They are all variables. Most can be modified during run time. Ones which cannot are listed here.
 * - WT_STARTING_CAMERA_SLOTS
 *  - This is the number of cCamera slots created in the cCameraHandler at start. The number of slots will be increased as required, but this involves some overhead.
 *  .
 * - WT_STARTING_VIEWPORT_SLOTS
 *  - This is the number of cViewport slots created in the cViewportHandler at start. The number of slots will be increased as required, but this involves some overhead.
 *  .
 * - WT_TEXTURE_NUMBER_ALLOWED
 *	- This is the number of textures that can be applied to a single object. This is limited by your graphics card. Keep this as low as possible for the shaders used.
 *  .
 * - WT_OPENGL_LIGHTS
 *	- This is the number of Lights that you wish OpenGL to use simultaneously to light an object.
 *  .
 * - USE_LIGHT_HANDLER
 *	- The light handler will determine the closest WT_OPENGL_LIGHTS to the object and render the object only using their influence. This allows the user to improve performance and / or use more lights than OpenGL can support. This should not be changed while running
 *  .
 * - WT_COLLISION_HANDLER_TYPE WT_COLLISION_HANDLER_TYPE_TYPE
 *	- This determines the Type of Collision handler used to sort Collisions. It can be set to either WT_COLLISION_HANDLER_TYPE_TYPE or WT_COLLISION_HANDLER_TYPE_BSP.
 *  .
 * - WT_RAY_ANGLE_RANGE
 *	- This is the Angle Range for detecting whether a ray and polygon has collided. Should be smaller than 0.5 degrees. Large values will make the collisions more common.
 *  .
 * - WT_COLLISION_HANDLER_SIZE
 *	- This will set the number of slots that the Collision Handler will use for filtering collisions. See relevant documentation.Should not be modified at runtime
 *  .
 * - WT_COLLISION_HANDLER_DIMENSIONS
 *	- This sets the number of dimensions the BSP Collision Handler should use (1,2 or 3) WT_COLLISION_HANDLER_DIMENSIONS_1D,WT_COLLISION_HANDLER_DIMENSIONS_2D, WT_COLLISION_HANDLER_DIMENSIONS_3D. This should not be modified at runtime
 *  .
 * - WT_COLLISION_SPACE_SIZE
 *	- This is the spatial size of each slot for the BSP. It should be at least (preferably more) than half the largest object size, that will be involved in collisions.
 *  .
 * - WT_DEFINE_OS
 *	- This is the OS that the engine is running under. So far OS_LINUX or OS_WINDOWS. This should be determined automatically when compiled.
 *  .
 * - _GRAVITY_X
 *	- This is the X Axis value of gravity, to be used by particle objects.
 *  .
 * - _GRAVITY_Y
 *	- This is the Y Axis value of gravity, to be used by particle objects.
 *  .
 * - _GRAVITY_Z
 *	- This is the Z Axis value of gravity, to be used by particle objects.
 *  .
 * - _WIND_X
 *	- This is the X Axis value of wind, to be used by particle objects.
 *  .
 * - _WIND_Y
 *	- This is the Y Axis value of wind, to be used by particle objects.
 *  .
 * - _WIND_Z
 *	- This is the Z Axis value of wind, to be used by particle objects.
 *  .
 * - WT_MAX_PARTICLES
 *	- This is the maximum particles that cParticleHandler should need to maintain at any one time. Should not be modifed at run time.
 *  .
 * - WT_PARTICLE_HANDLER_UPDATE_PARTICLE_POSITIONS
 *	- When true, the Particle handler will automatically update the particles speed and position based on Wind and Gravity.
 *  .
 * - WT_VERTEX_RANGE_CHECK_SIMILAR
 *	- This is the maximum allowed distance between verteces in a collision object for them to be counted as a single vertex.
 *  .
 * - WT_USE_PARENT_STACK
 *	- This will determine whether the system should automatically track each process' parent and children.Should not be used (At the moment)
 *  .
 *
 * \section ObjectsUsingTheCreateMacro List of Objects using or not using the Create Macro.
 * This section contains information of which objects which are handled by Bamboo. This means they should be created using the _CREATE() macro and killed with signals.
 * These objects should never be deleted, they should only be destroyed by being signaled with a _KILL() signal or cSignal::Signal() function.
 * - cProcess
 * - cRenderObject
 * - cCamera
 * - cViewport
 *  - cImage
 *  - cModel
 *  - cTextButton
 *  - cButton
 *  - cText
 *  - cLandscape
 *  - cRenderNode
 *  - cNodeList
 *  - cBeamMesh
 *  - cLine
 *  - cPoint
 *  - cParticleGroup
 *  - cParticle
 *  .
 * - cCollisionObject
 * - cAudioObject
 * .
 * These objects can be used as instances and can be created and deleted as desired. The cFile objects are the types used when the _GET_FILE() macros are used. Otherwise you are unlikely to use them.
 * - c1DVf
 * - c2DVf
 * - c3DVf
 * - c4DVf
 * - c2DVi
 * - c3DVi
 * - cMatrix4
 * - cCameraMatrix4
 * - cMatrixStack
 * - cFile (These are for loaded media files. You should not need to create objects of these types)
 *  - cSoundObject
 *  - cMeshFileCollision
 *  - cTexture
 *  - cFont
 *  - cMesh
 *  - cmLandscape
 *  - cShader
 *  - cShaderProgram
 *  .
 * - cRGB
 * - cRGBA
 * - cCollisionList
 * .
 *
 *\section OptimisationTechniques Optimisation Techniques
 * Bamboo is written to be as optimised as possible while remaining very simple. There are many things that can be done to optimise your code. \n
 * <b>Reduce Collisions:</b> \n
 * It is very important to only check for collisions that matter. Collisions should only detected one way (I.E. either From the Tank to the Bullet OR from the Bullet to the Tank, not both).
 * Use cCollisionObject::CollisionFilter() to minimise the collision checks that are made. \n
 * <b>Turn off Lighting where not required:</b> \n
 *  If an object will not use the lighting settings there is no point in calculating the lighting values. Turn it off with the function cRenderObject::Lighting(bool).
 * <b>Reduce Matrix Multiplications:</b> \n
 * Where possible use the minimum of Matrix multiplications. Both in shaders and in programs. Don't use cRenderObject::CalculateGlobalMatrix() unless absolutely neccessay. try to use cRenderObject::GetCacheMatrix() instead.
 * It will not include changes to the Global matrix this frame but it is very fast. Use the highest level of Matrices possible in a shader. \n
 * <b>Avoid searching with strings:</b> \n
 * Pointers are much quicker for accessing Media objects loaded onto the harddrive. If a piece of media will be accessed many times get a pointer to it using the functions for getting files (_GET_AUDIO_FILE(),_GET_COLLISION_MESH_FILE(),_GET_FONT_FILE(),_GET_LANDSCAPE_FILE(),_GET_MESH_FILE(),_GET_SHADER_FILE(),_GET_TEXTURE_FILE()). Each takes a string and returns a pointer of the correct type to the media object. if it cannot be found it returns 0;
 * \section CommonMistakes Common Mistakes
 * <b> Nothing is showing on screen: </b> \n
 * Check your Render Objects have been given valid shader programs using cRenderObject::Shader(string) or cRenderObject::Shader(cShaderProgram*).
 * Check the camera is facing the objects. Check the objects are between the cameras near and far distances cCamera::Near() cCamera::Far().
 * Change the cameras clear color to be not black and not green using cViewportControl::ClearColor(float,float,float,float).
 * (Objects are most likely to default to black or green depending on the shader program and OS).
 * Finally check the version of OpenGL that is being used by Bamboo. This is displayed as the first piece of information in the debugging console. It should be at least 3.0.
 * <b> My Textures aren't working: </b> \n
 * Has the Mesh got UV Co-ordinates? The entire model will have random colors or be faded to a very dark color without UV co-ordinates. \n
 * The object must have its shader assigned before it can receive any textures.
 * <b> My Lighting isn't working: </b> \n
 * If the model is entirely black it may not have Normals. A Mesh without normals cannot use lighting.
 * If the lighting is not using the correct lights it may be worth checking if lighting is enabled for the current object with cRenderObject::Lighting(bool). \n
 * <b> My Transparent Textures and Images are not working:</b> \n
 * Check that the Texture has an alpha channel to enable transparency. Check that Transparency is enabled with cRenderObject::Transparent(bool) \n
 * <b>When I change an Objects shader it goes funny:</b> \n
 * Each shader assigns its variables to a location specific to that cShaderProgram. This is done by the graphics card. Variables should be reassigned when an objects shader is changed.
 * */

/**
* \page ProgrammingBasics Basic Programming Concepts
* This Section is for People who have never programmed. If you have programmed in C++ before this section is not neccessary reading. C++ has been used for this game engine due to its speed and power. C and C++ are used to make drivers for hardware, applications for industry nad mnay other vital situations.
* It is not a comprehensive tutorial for programming by far, but it covers the basics in a simple manner to give the skills required to use @EngineName. @EngineName uses C++ and is a library which suppliers all functionality required to make simple 3D games.
* There are extensions and plugins being produced all the time which can increase the functionality.
* -# \ref ProgrammingBasicsGlossary "Glossary of Jargon"
* -# \ref BasicsPageStructure "Overview C++"
* -# \ref BasicsPageVariables "Variables"
* -# \ref BasicsPagePointers "Pointers"
* -# \ref BasicsPageFunctions "Functions"
* -# \ref BasicsPageOperators "Operators"
* -# \ref BasicsPageMisc "Blocks"
* -# \ref BasicsPageConditionals "Conditionals"
* -# \ref BasicsPageLoops "Loops"
* -# \ref BasicsPageClasses "Classes"
* .
* \section ProgrammingBasicsGlossary Glossary of Jargon
* Computers only have four commands : Read a value, Write a value, Move to another line and check True/False. All the commands performed by a computer are build from these blocks.
* Jargon:
* - \b Syntax       : The commands, words, symbols and grammar used to give meaning in C++.
* - \b Compiler     : A Computer program which will convert instructions in a computer language (C++) into assembly language (true computer language).
* - \b Statement    : An elementary computer instruction, which can be converted into one or more machine code instructions by a compiler.
* - \b Expression   : A Single statement to which a single answer can be calculated.
* - \b Variable     : A location in memory with a named reference.
* - \b Address      : The number representing the postition of a specific memory location.
* - \b Operator     : A symbol or group of symbols that represents a specific action. They can use the items either side to perform their action.
* - \b Function     : A already defined piece of code for performing a specific action.
* - \b Called		: When a user activates and uses a function it is known as calling a function. A function is called when it is used.
* - \b Argument     : Values which a function uses to perform its actions.
* - \b Return Value : A Single Value which is the result of a function.
* - \b Bit          : A smallest piece of data possible. It can either be True or False. False is 0. True is 1. Everything else is also True.
* - \b Block        : Code grouped into a single unit. A Block can contain many statements.
* - \b Line         : A Single computer statement. Lines are ended with a semicolon.
* - \b Declaration  : A Statement which tells what type a varaible or function will have (Type, Return Value Type, Argument Types and Argument order).
* - \b Definition   : Defining the code which comprises a function.
* - \b Class        : A User defined variable type. This can contain both variables and functions.
* - \b Write        : Write a value into the computers memory.
* - \b Read         : Read a value from the computers memory.
* - \b User         : You
* - \b Comment		: Text to explain to humans how a program works. Is ignored by the computer.
* - \b void			: A variable with no storage capacity.
* - \b Class		: A conceptual object combining variablers and functions into a single object.
* - \b Member		: A function or variable which is stored inside a class is a member of that class. (Like humans can be members of a club or guild).
* - \b Instance		: A single copy of a class. There can be many existing copies of a particular class, each one is an Instance.
* - \b Inheritance	: Just as a child of a prent inherits their genes. A Class can inherit from another class and use its functions and properties. It can be used as the base class, but can also override functionality to make it more specific or expand on the functionality it provides.
* .
* \section BasicsPageStructure Overview C++
* C++ is a middle level language. This means that it implies the power and speed of assembly code (literally computer language) with the usability of a high level language. In reality it is nearly as simple as a high level language and nearly as fast as as low level language. C++ is one of the most used languages in industry and academia.
* C++ considers case. As such each of these instances of the word 'Uppercase' are all different in C++
* - UPPERCASE
* - UpperCase
* - uppercase
* - uPPercASe
* .
* C++ Starts works from the top of the code, and works through the code one line at a time. On each line, it will follow the commands on the line, then move to the next line. It is possible for the program to move teh line the computer is on so that code is not performed in the written order. \n
* You will also notice this symbol in a lot of the examples : \b // This symbol starts a single line comment. All text on the same text line to the right of the two slashes will be ignored by the computer. \n
* \n
* This tutorial briefly covers the major sections and covers all concepts required to use @EngineName. For further explanation or a more comprehensive study of C++ I recommend "The Complete Reference C++" by "Herbert Schildt". It comprehensively explains all material relevant to C++ through good examples and techincal descriptions.
* \section BasicsPageVariables Variables
* A Variable is a named storage location in the computers memory. When you create a variable you give it a name.
* This name is used to identify the variable either to write a value to it, or read the value stored in it.
* This name must not start with a number but can contain both characters and numbers. \n \n
* Variables can be imagined as named boxes containing a single card. The value written on the card in the box is always the value stored in the variable.
* Only one value can be stored in a variable at any one time. When a new value is assigned to the variable, the old card is removed from the box, the new value is written on a new piece of card which is placed in the box. \n
* There are many types of variable, but the 4 main types are float, int, bool and pointers.
* - A \b float is a 'real' number and is a number which can have a floating (or decimal) point. It is the only type that can store fractions.
* Floats are also available in a range of sizes - \b 32, \b 64 and \b 80 bits. The number of bits determines how much storage space it occupys and the range it can store.
* - An \b int (Integer) only uses 'whole' numbers, i.e. it cannot hold fractions. Integers can be signed or unsigned. Signed integers can store negative and positive values. Unsigned integers can only store 0 or positive values.
* Integers come in a range of sizes - \b 8, \b 16, \b 32 and \b 64 bits. The number of bits determines how much storage space it occupys and the range it can store.
* - A \b bool (Boolean) is a single bit.
* - A \b void is an empty type. It cannot store any data.
* - A \b pointer records the address location of another variable. See the section \ref BasicsPagePointers Pointers
* - Most of the types listed above have sub types. There are also 'classes' which can be imagined as user defined types.
* .
* Declaring a variable : \n
*       The line must start with the type of variable, followed by the user defined name of the variable and finishing with a semicolon.
* \code
* //Example of C++ Grammar
* Type Variable_Name;
* \endcode

* \code
* //Example of acceptable Variable definitions in C++
*
* //Declaring a new float variable of standard length called My_Float_Variable.
* float My_Float_Variable;
*
* //Declaring a new integer variable of standard length called My_Signed_Integer_Variable.
* int My_Signed_Integer_Variable;
*
* //Declaring a new unsigned integer variable of standard length called My_Unsigned_Integer_Variable.
* unsigned int My_Unsigned_Integer_Variable;
*
* //Declaring a new signed integer variable called Another_Signed_Integer_Variable.
* signed int Another_Signed_Integer_Variable;
*
* //Declaring a new boolean variable called My_Boolean.
* bool My_Boolean;
*
* //Declaring a new boolean variable callen Boolean02.
* bool Boolean02;
*
*
* //Example of Unacceptable declarations
*
* //Float cannot use the unsigned type
* unsigned float Unsigned_Float;
*
* //C++ Considers case. Float is different to float
* Float This_Is_Not_A_Type;
*
* //Must end with a semicolon
* int Must_End_With_A
*
* // unsigned must go before the variable type int
* int unsigned Order_Error;
* \endcode
*
* Variables must be declared before use so the computer knows how to access and store the data. \n
*
* To write a value to a variable use the equals sign. The variable which will store the value goes to the left of the equals sign. The value which will be written to the variable goes to the right of the equals sign. \n
* In the box/card model, this is equivalent to writing a value on a card and putting it into a box. Remember: Each variable can hold one number at a time - each box can only hold one card at a time.
* I.E. \n
* \code
* //Example C++ Code
* int Variable;
* Variable = 10;
* //Variable is now storing the value 10.
* Variable = 20;
* //Variable is now storing the value 20.
* \endcode

* \section BasicsPagePointers Pointers
* A pointer is a variable and stores a value. Pointer values are unsigned integer values, but the number of bits used is determined by the computer. Pointers are pointers to variables. This means that their type is a pointer to another type.
* The star symbol \b * is used between the type and variable name to show it is a pointer:
* \code
*  //Example C++ Code
*
* //Pointer to variables of type int
* int *Int_Pointer;
*
* //Pointer to varaibles of type float
* float *Float_Pointer;
*
* //Pointer to variables of type float pointer (Points to pointers to float type variables)
* float **Pointer_To_Float_Pointers;
* \endcode
* Every variable has an address, which is an integer value greater than 0. Pointers can store the value 0 which represents a null pointer I.E. It does not point to a variable. \n
* Variables are assigned an address when created. This cannot be chosen by the user. This represents their location in the computers memory.
* The variables name can be used to access it like before, but so can it's address. Pointers store the address of another variable and allow the user to access the variable through its address.
* The address a pointer stores can be accessed by accessing the pointer as if it was any other variable. \n
* To find the address of another variable the '&' character should be placed before the variable name.
* \code
* float Float_Variable;
* float *Float_Pointer;
* Float_Variable = 0;
* Float_Pointer = & Float_Variable
* // Float_Pointer is now storing the address of the variable Float_Variable.
* \endcode
* Float_Pointer is now storing the address of Float_Variable. This doesn't seem very useful, but there are two important ways that pointers can be used. They can be used to pass the address of variables without copying the original. This means that completely seperate parts of the program can affect the same variable. They can also be used to access arrays. \n
* \b Arrays: \n
* Array is a group of variables which have consecutive addresses. Arrays use this to allow you to access many variables from a single address.
* Variables are accessed based on their address relative to the first item in the array.
* An array is created and accessed using a set of square brackets \b '[' Number of Variables Required \b ']' . The address in the pointer is the address of the first variable. Variables in the array can be accessed based on their address relative to the first item. The first variable is 0 steps from the first variables address. The second variable is 1 step from the first variables address. And so on.
* To use the box / card example from earlier all the boxes are lined up in a row. They are given a number which represents their position in the line. Getting the address of the box is to get the number of that box. A Pointer can be imagined as having a big arrow which points all the way to the box with the same address as the value on the pointers card.
* \code
* //Example of Grammar
* //Declaring Arrays
* Type ArrayName[Number_of_Variables_Required];
*
* //Accessing a single variable in an array
* ArrayName[Position_Of_Variable_Desired];
* \endcode
* \code
* //Example of Array Use in C++
* //Create an arrray with 10 items from 0 - 9
* float My_Array_Of_10_Floats[10];
*
* //Assign the value 5.0 to the first float in the array
* My_Array_Of_10_Floats[0] = 5.0;
*
* //Assign the value 2.5 to the second float in the array
* My_Array_Of_10_Floats[1] = 2.5;
*
* //Assign the value 3.1 to the third float in the array
* My_Array_Of_10_Floats[2] = 3.1;
*
* //Assign the value 8.7 to the tenth float in the array
* My_Array_Of_10_Floats[9] = 8.7;
*
* float *Another_Float_Pointer;
*
* Another_Float_Pointer = My_Array_Of_10_Floats;
*
* //Assign the value 4.0 to the soxth float in the array.
* //Another_Float_Pointer and My_Array_Of_10_Floats are the same.
* Another_Float_Pointer[5] = 4.0;
* \endcode
*
* Pointers can also be used to access variables directly. This is done using the pointer operator. The pointer operator is composed of the dash symbol and the right pointing angled bracket \b -> .
* This allows the user to access functions within variables \ref BasicsPageFunctions Functions. Functions will be described in the next section.
* \code
* //Example of Grammar
*
* //cModel is a Type of variable specific to @EngineName
* cModel New_Textured_Model;
*
* //There can be pointers to every type of variable
* cModel *Textured_Model_Pointer;
*
* //Assigning the address of New_Textured_Model to Textured_Model_Pointer.
* Textured_Model_Pointer = &New_Textured_Model;
*
* //Have accessed the Function Position within New_Textured_Model by using its address stored in the pointer Textured_Model_Pointer
* Textured_Model_Pointer -> Position( 0.0 , 0.0 , 0.0 );
*
* //This will be used later extensively. For now it is important to recognise the pointer operator and where it goes.
* \endcode
* \section BasicsPageFunctions Functions
* Functions are used to perform a commonly used task. They can change variables, calculate values and perform many other tasks. \n
* A Recipe is a very good analogy for functions. You put in ingredients in the correct order. There are then a series of actions on the ingredients to turn them into the final product. A function can only result in a single product, however it does not need to have a result.
* The ingredients used in a recipe will affect the final result. If you are making vegetable soup, there will be a certain number of ingredients with some limitations on them. The limitations will be on what ingredients, their quality and the amount will all change the final result. However the steps of the recipe are applied and you end up with vegetable soup. If you use carrots you get carrot soup, if you use potatoes you get potatoe soup. \n
* A Function works in the same way. The 'ingredients' for a function are variables. These are called arguments of the function. When a function is defined it is given a list of acceptable arguments, this is a list of variable types. The order of the variables is important.
* The function applies a series of steps to the variables and can but is not required to produce a single result. The resulting value is called the return value.\n
* Functions are called by writing the function name and following it with the curved brackets () :
* \code
* //Example of Grammar
*
* //Performing a function without assigning the return value
* Function_Name();
*
* //Assigning the return value of a function to a variable.
* Variable = Function_Name();
* \endcode
* The functions arguments and are inserted between the curved brackets.
* The order and type of the arguments is very important. Functions can sometimes have several different sets of arguments. \n
* Functions can also return values in which case their result value can be used as if it were a variable. Everytime a function is used it will perform its calculations again, which means it will not neccessarilarly produce the same return value. One thing that could make a function return a different result is if one of the arguments has changed. \n
*
* Performing Functions with Arguments:
* \code
* //Example of Grammar

* //Performing a Function requiring three arguments and not returning a value
* Function_Name( Argument_1 , Argument_2 , Argument_3 );
*
* //Performing a function requiring 3 arguments and assigning the return value to a variable
* Store_Return_Value = Function_Name( Argument_1 , Argument_2 , Argument_3);
*
* //Performing a Function without arguments or assigning the return value.
* Function_Name();
*
* //Performing a Function without arguments but assigning the return value to a variable.
* Variable_To_Store_Return = Function_Name();
* \endcode
*
* You can produce your own functions. A producing a function requires two sections. A declaration and a definition. The declaration specifies the form of the function, what return type it has and what the arguments are. \n
* A function cannot be used until after it has been declared, however it can be used before it is defined. A definition without a declaration counts for both. \n
* If the function returns no value the result type is void, otherwise any type can be used.
* To return the value from the function use the return statement. The value returned will be the result of the function.
* When the return statement is called the function will immediately stop and no other code in the function will be performed.
* Writing Functions:
* \code
* //Example of Grammar
*
* //Declaration of a Function
* Result_Type Function_Name( Argument_1_Type Argument_1_Name , Argument_2_Type Argument_2_Name , Argument_3_Type Argument_3_Name);
*
* //Definition of the previous Function
* Result_Type Function_Name( Argument_1_Type Argument_1_Name , Argument_2_Type Argument_2_Name , Argument_3_Type Argument_3_Name)
* {
* //Code goes here
* return Result_Value;
* };
*
* //Declaration of a Function with no return value.
* void Function_Name( Argument_1_Type Argument_1_Name , Argument_2_Type Argument_2_Name , Argument_3_Type Argument_3_Name);
*
* //Definition of the previous Function.
* void Function_Name( Argument_1_Type Argument_1_Name , Argument_2_Type Argument_2_Name , Argument_3_Type Argument_3_Name)
* {
* //Code forming the function goes here
* };
*
* //Declaration of a Function with no arguments but a return value
* Result_Type Function_Name();
*
* //Declaration of the previous Function
* Result_Type Function_Name()
* {
*  //Code forming the function goes here
* return Result_Value;
* };
*
* //Definition of a Function with no return value or arguments.
* void Function_Name();
*
* //Declaration of the previous Function.
* void Function_Name()
* {
*  //Code forming the function goes here
* };
* \endcode
*
*
*
* Writing your own functions:
*\code
* //Example of C++ Code
*
* //This will create a function which will add the two values assigned to First_Value and Second_Value.
* int Add(int First_Value,int Second_Value)
* {
*
* //Here it returns the result which equals First_Value + Second_Value
*   return First_Value+Second_Value;
*
* //This line will not be performed as it is after the return statement.
* First_Value = 10;
* };
*
* //This will calculate the length of the hypotenuse of a right angled triangle if given the lengths of the other two sides.
* float Hypotenuese( float Adjacent_Length , float Opposite_Length )
* {
*
* //Declaring variables to be used in this function.
* float Squared_Adjacent;
* float Squared_Opposite;
* float Squared_Total;
*
* //Calculate the squares of the other sides
* Squared_Adjacent = Adjacent_Length * Adjacent_Length;
* Squared_Opposite = Opposite_Length * Opposite_Length;
*
* //Calculate the square total of lengths.
* Squared_Total = Squared_Adjacent + Squared_Opposite;
*
* //This will return the Square Root of the square total which is the length of the hypotenuse.
* return sqrt(Squared_Total);
* //Notice how another function has been called within this function.
* };
* \endcode
* \section BasicsPageOperators Operators
* The Third is operators. Most people recognise some operators: \b + ,\b - ,\b * ,\b \ ,\b = for plus, minus, times, divide and equals. \n
* C++ Uses many other operators but the most important ones for using @EngineName are explained here: \n
* Arithmetic operators :
* These are listed in the priority order the computer uses to caluclate a result. The items at the top of the list are performed before any other arithmetic operator. The order can be changed by using teh curved brackets.
* - \b *	To muliply one value by another use the multiplication operator.
* - \b /	To divide one value by another use the divide operator. The variable to the left of the division operator is divided by the variable on the right of the division operator.
* - \b +	To add two values together use the addition operator.
* - \b -	To subtract one value from another use the subtraction operator. The variable to the right of the subtraction sign is subtracted from the variable on the left of the subtraction operator.
* - \b =	Assigns the value to the right of the equals sign to the variable to the left of the equals sign.
* - \b ()   Curved brackets can be used to group code informing the computer to calculate the statement within the brackets and use its result.
*
* \code
* //The answer to this is 8 as the multiplication is done first.
* 1 + 2 * 3 + 1
*
* //The answer to this is 12 as the statements in the brackets are done first.
* ( 1 + 2 ) * ( 3 + 1 )
*
* //The answer to this is 12 as the statements in the brackets are done first.
* ( 1 + 2 + 3 ) * 2
*
* //The answer to this is 9 as the multiplication is done first.
* 1 + 2 + 3 * 2
* \endcode
* - \b //	Indicates a comment. Anything to the left of a // symbol on the same line as the symbol is ignored by the computer. This allows you to include explanations of how your code works.
* - \b ;	Indicates the end of a line. Some code will be placed on several different lines but count as a single line of code. It is lines of code which must be terminated with this symbol. Unless specified otherwise a line should end with a ; character.
* \code
* //Example of C++ Code showing the operators being used
* MyVariable = MyOtherVariable;
* NewVariable = 10;
* ThirdVariable = MyVariable + NewVariable;
* FinalVariable = MyVariable - 100;
* \endcode
* \n

* \section BasicsPageMisc Blocks
* Finally there are a few other things which should be covered:
* - Forming Blocks: \n
* 	C++ operates using blocks. Sections of code can be combined into a block using the curly brackets { }. C++ sees code in curly brackets as a single block of code. Curly brackets automatically count as a terminated line of code. Curly brackets can be put within curly brackets. The position left and right of the brackets does not matter, but moving inner brackets further right makes it clear where different blocks start and finish.
*\code
* //Example of Grammar
* A Simple Block
* { }
*
* Another Simple Block
* {
*
* }
*
* Blocks can be within other blocks
* {
*  { }
*  { }
* }
*
* //Example of a complicated Block Structure
* //Start Block 1
* {
*
* //Start Block 2 inside Block 1
* {
*
*	//Start Block 3 inside Block 2
*	{
*
*		//Block 4 inside Block 3
* 		{}
*
* 	//Finish Block 3
* 	}
*
* 	//Start Block 5 inside Block 2
* 	{

*   //Finish Block 5
* 	}
*
* //Finish Block 2
* }
*
* //Finish Block 1
* }
*\endcode

* \section BasicsPageConditionals Conditionals
* Conditionals are statements which depend on a statement which is either true or false. They use the conditional operators : or,and,==,>,<,<=,>= and != \n
*
* Conditional Operators: \n
* Conditional operators are a special type of operator. They are used to determine if a statement is true or false. 0 is considered to be false. Everything else is true. If true is measured as a number it will be 1. If false will be measured as a number it will be 0.
* Conditional operators compare values and determine whether they meet the specified conditions and return a value of true or false. As with Arithmetic operators the conditional operators will be listed in the order of precedence from higest priority (performed first) to lowest priority.
* - \b >	Will test whether the variable to the left of the angled bracket is greather than the variable to the right.
* \code
* //This is false
* 1 > 1
*
* //This is also false
* 0 > 1
*
* //This is also false
* -1 > 1
*
* //This is true
* 4 > 3
*
* //This is also true
* 3 > -4
* \endcode
* - \b >=	Will test whether the variable to the left of the angled bracket is greather than or equal to the variable to the right of the symbol.
* \code
* //This is true
* 1 >= 1
*
* //This is false
* 0 >= 1
*
* //This is also false
* -1 >= 1
*
* //This is true
* 4 >= 3
*
* //This is also true
* 3 >= -4
* \endcode
* - \b <	Will test whether the variable to the left of the angled bracket is less than the varible to the right.
* \code
* //This is false
* 1 < 1
*
* //This is true
* 0 < 1
*
* //This is also true
* -1 < 1
*
* //This is also true
* 3 < 4
*
* //This is false
* 4 < 3
* \endcode
* - \b <=	Will test whether the variable to the left of the angled bracket is less than or equal to the variable to the right of the symbol.
* \code
* //This is true
* 1 <= 1
*
* //This is true
* 0 <= 1
*
* //This is also true
* -1 <= 1
*
* //This is false
* 4 <= 3
*
* //This is also false
* 3 <= -4
* \endcode
* - \b ==	Will test whether two variables are equal. It will return true if they are exactly the same otherwise it will return false. Neither varible will be modified. Note it is \b two equals symbols together.
* \code
* //This is true
* 1 == 1
*
* //This is false
* 0 == 1
*
* //This is also false
* -1 == 1
*
* //This is also false
* 3 == 4
*
* //This is true
* 3 == 3
* \endcode
* - \b !=	Will test whether the value of two variables are different. It will return true if their values are different. If they are exactly the same it will return false.
* \code
* //This is false
* 1 != 1
*
* //This is true
* 0 != 1
*
* //This is also true
* -1 != 1
*
* //This is also true
* 3 != 4
*
* //This is false
* 3 != 3
* \endcode
* - \b and	(Alternatively the && operator) Will be true only if BOTH statements next to it are true. If either is false it is false.
* \code
* //This is true
* 1 == 1 and 2 == 2
*
* //This is false
* 1 > 1 and 1 == 1
*
* //This is false
* 0 > 1 and 3 == 3
*
* //This is false
* 1 == 0 and 2 > 2
*
* //This is true
* 1 == 1 && 2 > -2
*
* //This is false
* 1 == 0 && 0 == 0
*
* \endcode
* - \b or	(Alternatively the || operator) Will be true if EITHER statement next to it is true. If both are true it is still true.
* \code
* //This is true
* 1 == 1 or 1 == 0
*
* //This is true
* 1 > 1 or 1 == 1
*
* //This is true
* 2 > 1 or 3 == 3
*
* //This is false
* 1 == 0 or 2 > 2
*
* //This is true
* 1 == 1 || 2 > 2
*
* //This is false
* 1 == 0 || 0 == -2
*
* \endcode
* - \b !	Will invert a returned value I.E. From true to false and false to true. It is placed immediately to the left of the value to be switched.
* \code
* //This is false
* !1
*
* //This is true
* !0
*
* //This is false
* ! 1 == 1
*
* //This is true
* ! 1 == 2
*
* //This is false
* ! 3 > -4
* \endcode
* If else statements:
* The if statement allows the user to choose whether to run code. It will direct the computer to process different blocks of code depending on whether a specified conditional expression is true or false. \n
* The code can be imagined as a river. The computer drifts along the river down the page, following the commands on each line as it is reached. \n
* The if statement represents the river splitting into two streams.
* At the branch in the river, either the left or the right branch can be taken, but not both. The Conditional expression determines which branch in the river should be traversed. \n
* Each time the computer processes an if statement the program branches like the river. Once the code covered by the if statement has been processed the two streams rejoin to form a single main channel.
* The statement is given a block of code representing the path for when the conditional expression is true.
* It may also be given a block of code representing the path for when the conditional expression is false.
* There must be a block of code in the true branch of the if statement, there can be a block of code in the false branch of the if statement.
* Part of the if statement holds a conditional expression which is can be composed of variables, values and the conditional operators.
* Once the relevant branch has been completed, the computer will continue the program from immediately after the if statement. \n
* The if statement begins the conditional statement and includes the conditional expression between curved brackets. It is then followed by a block of code. This can be seen as if (Conditional statement is true) then do this block of code.
* After the block of code representing the path for when the conditional expression is true is the else statement. This can be seen as saying if the conditional statement is true then do the first block, else do the second block.
* \code
* //Example of Grammar
* if ( Conditional_Statement )
* * //This is the block performed when the Conditional_Statement is true
* {  }
* //The else statement indicates that this if statement has a branch if the conditional expression false branch
* else
*  //This is the block performed when the Conditional_Statement is true
* {  }
* \endcode
* Note that the if is lower case, there
* \code
* //Example of C++ Code
*
* int Value;
* Value = 0;
*
* int Answer;
* Answer = 1;
*
* // Value is less than 1 so the conditional is true.
* if( Value < 1 )
* //This block is performed as the conditional is true.
* {
* //Value is set to 3.
*  Value = 3;
* }
* //This is not performed as it is for when the conditional is false.
* else
* {
*  Value = 2;
* }
* // At this point Value is storing the value 3.
* // This line is performed as it is after the blocks of code for the if else statement
* Answer = Value * 2 ;
* // Answer now is storing the value 6
*
* // Value is not less than 1 so the conditional is false.
* if( Value < 1 )
* //This block is not performed as the conditional is false.
* {
*  Value = 3;
* }
* //This block is performed as the conditional is false.
* else
* {
* // Value is set to 2
*  Value = 2;
* }
* // At this point Value is storing the value 2.
* // This line is performed as it is after the blocks of code for the if else statement
* Answer = Value * 2 ;
* // Answer now is storing the value 4
* \endcode
* \code
* //Example of C++ Code
*
* //If Statement with a single block of code.
* //If Damage is greater than life then the object should be dead.
* if(Damage > Life)
* {
*  //If conditional expression is true then make this dead
*  MakeThisDead();
* }
* \endcode
* \code
* //Example of C++ Code
* // If statement with an else section.
* if(LightShouldBeOn())
* {
* //The Light should be on.
*   MakeLightOn();
* }
* else
* {
* // The Light should be off.
*   MakeLightOff();
* }
* \endcode
* \code
* //Example of C++ Code
*
* // If statement with an else section.
* int32 My_Integer;
* if(ChooseHighValue())
* {
* //Choose the Higher Value.
*   My_Integer=20;
* }
* else
* {
* //Do not choose the Higher Value.
*   My_Integer=10;
* }
* //The two branches both lead to here.
* // My_Integer is now either 10 or 20.
* My_Integer = 3 * My_Integer;
* //My_Integer is now either 30 or 60
* \endcode
*
* \section BasicsPageLoops Loops
* Loops allow the user to perform a block of code multiple times under different conditions. This can be very useful to produce code which performs a task many times.
* The most commonly used loop is the for loop. The for loop contains three statements and a block of code.
* - An Initialiser which sets the starting conditions. This statement is performed only at the start of the loop.
* - A Conditional which determines whether the block of code should be performed. The block of code is only ever run after checking the conditional.
* - A Step Statement which will change variables values each time the block of code is run. The step function is used after the block has been processed.
* .
* A Step by step analysis of the operation of the  for loop :
* - The Start statement is performed.
* - The Conditional statement is checked. If true, the block of code will be processed. If the conditional is false the loop will stop and be exited.
* - The Block of code is processed.
* - The Step statement is processed to update the variables for the next repetition.
* - The loop goes back to the second item on this list. (I.E Checking the conditional statement).
* .
*
* \code
* //Example of Grammar
* for(Initialiser;Condition;Step)
* {
*  //This is the block of code.
* }
* \endcode
* \code
* //Example of C++ Code
* //The function PrintValue will be called 100 times with values from 0 up to 99.
* //The Initialiser Statement means that Counter is 0 at the start of the loop.
* //The Conditional Statement ensures that the loop will repeat if Counter is less than 100.
* //After The block of code { PrintValue(Counter); } the Step function is called which will increase the value stored in Counter by 1.
* //So the block will be performed with Counter storing every value from 0 to 99 in order.
* uin32 Counter;
* for(Counter=0;Counter<100;Counter=Counter+1)
* {
*	PrintValue(Counter);
* }
* \endcode
* \code
* //Example of C++ Code
* //The function PrintValue will be called 100 times with values from 100 down to 1.
* //The Initialiser Statement means that Counter is 100 at the start of the loop.
* //The Conditional Statement ensures that the loop will repeat if Counter is greater than 0.
* //After The block of code { PrintValue(Counter); } the Step function is called which will reduce the value stored in Counter by 1.
* //So the block will be performed with Counter storing every value from 100 down to 1 in order.
* uint32 Counter;
* for(Counter=100;Counter>0;Counter=Counter-1)
* {
*	PrintValue(Counter);
* }
* \endcode
*
* \section BasicsPageClasses Classes
* Classes are the key to C++'s true power. It is the major difference between C and C++. Classes make C++ an Object Orientated programming language.
* A Class is a user defined variable type. It usually contains other variables and functions. The concept of classes is very simple.
* A Class contains all the code and data relating to a single object in the program. By keeping the data and functions within the class they can be used without seeing the inner workings. \n
* In @EngineName almost every thing is based on a class. A Renderable Object is one which will display on the screen.
* As it is a class it can be controlled by using appropriate functions without having to manipulate the data manunally.
* A function within a class should affect the class or instance to which is belongs.
* The \b . operator allows the access to variables and functions within a variable whose type is a class.
* \code
* //Example of C++ Code
* //cModel is a Renderable object supplied by @EngineName.
* cModel My_Textured_Model;
* //Position( float , float , float) is a function within the class cModel.
* My_Textured_Model.Position( 1.0 , 1.0 , 1.0 );
* // My_Textured_Model is now Positioned at 1.0 , 1.0 , 1.0 .
* \endcode
* Creating a copy of My_Textured_Model would result in having two cModel objects on screen.
* This is where the true value of the pointer symbol comes into play.
* By creating a pointer to an object it will allow other parts of the program to control the class without making a copy of it.
* A Pointer to a class allows the user to access the variables and functions within a class.
* \code
* //Example of C++ Code
* //cModel is a Renderable object supplied by @EngineName.
* cModel My_Textured_Model;
* cModel *My_Textured_Model_Pointer;
*
* //Get the pointer to My_Textured_Model;
* My_Textured_Model_Pointer = &My_Textured_Model;
*
* //Position( float , float , float ) is within the class cModel.
* //This will position the cModel My_Textured_Model at:
* // X Co-ordinate of 1.0
* // Y Co-ordinate of 1.0
* // Z Co-ordinate of 1.0
* My_Textured_Model_Pointer -> Position( 1.0 , 1.0 , 1.0 );
* \endcode
* The user does not need to understand the maths that positions the cModel at 1.0 , 1.0 , 1.0 .
* Thanks to classes moving and rotating Renderable Objects becomes quick and simple. \n
*
* Creating New Classes : \n
* While using Bamboo you will need to create new class types. If you do not with to investigate the intricacies of class creation, then you can follow the basic template for Bamboo.
* Read this then move on to the section on using Bamboo.
* \code
* _PROCESS( Process_Name )
* {
* public:
*
* Process_Name()
* {
*  //Initialiser Code goes here.
*  //This should _CREATE all the objects required for this process.
*  //It should set their variable values etc.
*  //File Loading should be carefully considered before being placed here.
*  //As this code is run EVERY time an instance of this process is created.
* };
*
* void Stop()
* {
*  //Destructor Code goes here.
*  //This should send a _KILL signal to objects you wish to die when this process dies.
*  //This should set pointers to 0.
*  //You should not use the command word delete here.
* };
*
* void Run()
* {
*  //Code to update this process each frame goes here.
*  //This should check for collisions as required.
*  //Send signals to other processes.
*  //Move renderable objects.
*  //Play sounds.
*  //etc.
* };
*
* };
* \endcode
* Classes have a declaration like functions. All functions and variables in the class must be declared within the declaration of the class.
* Classes don't have a definition, but every function must have a definition before an instance of a class can be created.
* Classes have a few special functions. Classes can have Constructors and Destructors. Constructors are automatically processed any time an instance of a class is created. Destructors are automatically processed any time an instance of a class is deleted.
* This means that a Constructor can be used to setup a class ready to be used. A Destructor should be used to 'clean' up a class which is being deleted.
* The Constructor is a function with no return type (not even void) and a name which exactly matches the name of the class. It can have arguments.
* The Destructor is a function called Stop() with no return type (void). Stop will be called whenever a process is killed. Do not use the normal c++ destructor using the tilde key '~' as it is unpredictable about when this will occur.
* \code
* class My_Class
* {
*
* public:
*
*	// Constructor for the class My_Class.
*	My_Class()
*	{
*	};
*
*	// Constructor for My_Class with a single integer argument.
*	// This would be called using the syntax:
*	// _CREATE( My_Class( 123 ) );
* 	My_Class(int Integer)
*	{
*	};

*
*	Define a function called Run which does not return a value.
*	void Run()
*	{
*
*	};
*
*	// Destructor for the class My_Class.
*	void Stop()
*	{
*	};
*
* };
* \endcode
* You may notice the use of the command word 'public:'. This indicates that functions and variables following the public: keyword will have the public property. There are three main states that the accessibility property of a function or variable can have in a class.
* - \b public : It can be accessed by any class or function in the program.
* - \b private : It can only be accessed by the owning class.
* - \b protected : It counts as private but can be used as public, by other classes which inherit this class.
* .
* By default a class will use the property private for variables and functions. While declaring Processes in Bamboo you can make all functions and variables public.\n
* All functions and variables declared in the block of code after the classes declaration are members of the class.
* Each Instance of a class has a copy of all the variables. Each function will operate on the variables for the specific Instance which called it by using the dot operator ( \b . ) or the pointer operator (\b -> ).
* Bamboo owns all the instances of objects so it can update and destroy them as required. This means that within Bamboo you should only need to use the pointer operator ( \b -> ). \n
*
* The only other aspect of classes which is noteworthy for using Bamboo is inheritance.
* Inheritance means taking the variables, properties and code which compose a class an including them in a new class.
* The class which originally held the code is called the base class. The class which inherits the code is called the derived class.
* The derived class counts as a class of the base type as well as the derived type. This means a pointer to the base type can also point to an Instance of the derived type.
* It also means that the derived class will behave like the base class. This is how Bamboo makes Processes. All processes must inherit from the base type of cProcess.
* In the template when you type :
* \code
* _PROCESS( Process_Name )
* \endcode
* What it really means is you are inheriting from cProcess. Outside of Bamboo this would be typed
* \code
* class Process_Name : public cProcess
* \endcode
* This means that your process will act like all the other cProcess objects. Although variables and code has been inherited it can still be modified in the derived class, without affecting the Base class.
* This is called redefining. You can change what a version of a function does in the derived class.
* The function void Run() works like this. When you write code it will be different for your derived class to what it is in the base class. This is how you can create different processes which operate different ways.
* There are many other wonderful things about classes, but these are not critical to using @EngineName so they will not be discussed here.
**/

/**
* \page UsingEnginePage Using @EngineName
* In this Section are a few sub sections:
* -# \ref MainLoop "Overview of Bamboo"
* -# \ref KernelPage "The Kernel"
* -# \ref ProcessObjectsPage "How to use Process Objects"
* -# \ref RenderObjectsPage "How to use Render Objects"
* -# \ref FilesAccessPage "Loading and Accessing Files"
* -# \ref InputsPage "Accessing User Inputs"
* -# \ref AudioPage "Using the Audio System"
* -# \ref SignalsPage "Signals and Flags"
* -# \ref CollisionsPage "Detecting Collisions"
* -# \ref RenderNodesPage "Creating Local Co-ordinate systems"
* -# \ref MultipleCamerasViewports "Multiple Cameras and Viewport Control"
* -# \ref IMFGenerationPage "IMF File Generation and Usage"
* .
* \section MainLoop Overview of Bamboo
*WT@EngineName.h
*
* @EngineName is based on a Process / Renderable Object mentality. Process' are classes with behavioural code which tell them how to behave. They take inputs from the OS, signal other process' and tell Renderable objects how to display. Once a Process is written, the user should create a new instance. The system will record the information add it to the system and make the process enact it's behaviour, with no further input form the user (Fire and Forget). This way many similar objects can be created easily once the behavioural code is written. Render Objects should not have any behavioural code and are entirely directed by Process'.
* The Process' are controlled by cKernel which will track and update all the process'.
* Render Objects actually display on the screen. They are moved around in 3D space and cCamera renders them to the screen.
* Collision Objects must be handed a Render Object at startup, which they will follow and determine collisions with other Collision Objects.
* Files are loaded by the FileHandler and can be asked to provide media data for Render Objects and Collision Objects.
* Lighting effects are controlled by the LightHandler. \n
* In Bamboo programs the ESC key is automatically assigned to exit the program. Any Bamboo program can be quit by pressing ESC or clicking the close button in the top right of the window.
*
*The Main Loop:
* In the template there is the main loop. Create a new project and look at the file main.cpp. In the file you will see the following code:
*\code
* //Using @EngineName in Windows
* #include <WTBamboo.h>
*
* //Windows Specific Main function. This will give access to inputs and windows signals.
* int WINAPI WinMain (HINSTANCE hInstance,
*                    HINSTANCE hPrevInstance,
*                    LPSTR lpCmdLine,
*                    int iCmdShow)
* {
* //This will Start @EngineName with cCore as the Core Process.
* //cUserSettings is the class which will initialise the Engine Settings.
* //hInstance is a Windows hook to allow creating a new window.
* return _START_PROGRAM(cCore,cUserSettings,hInstance);
};
*\endcode
*\code
* //Using @EngineName in Linux
* #include <WTBamboo.h>
*
* //C++ standard main function.
* int main ()
* {
* //This will Start @EngineName with cCore as the Core Process.
* //cUserSettings is the class which will initialise the Engine Settings.
*  return _START_PROGRAM(cCore,cUserSettings);
* };
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
*
 * \section KernelPage The Kernel
 * WTKernel.h
 *
 * Using the kernel system by William Thorley
 *
 * The Kernel does not need to be understood by the user, but is refered to later so a brief description will be given here. The Kernel owns and controls all the processes in the program.
 * The kernel will create itself as soon as any Process is created. It will automatically grab any process as soon as it is created and can sort their run order. A Pointer to the cKernel can always be found by calling the macro _KERNEL (cKernel::Instance()). If this function is called and there is no cKernel, the function will create one. The Constructor is private, so there can be only one cKernel.
 * The Kernel is entirely automatic and should require no inputs from the user. However it can supply useful information and functionality to the user.
 * cKernel::KillAll():
 * Calling cKernel::KillAll() will kill every running process. This will cause Update() to exit, and traditionally end the program. However it is possible to cKernel::KillAll(), then create a new core process, and call Update() again, thereby ‘restarting’ the program.
 *
 * _FIND_PROCESS(TYPE)
 * Calling _FIND_PROCESS() will automatically search the cKernel for any processes of class type TYPE. It will return a pointer to the next process of class type TYPE everytime it is called. When there are no more processes of class type TYPE it will return 0.
 * \section FirstProcessPage Your First Process
 *
 * WTcProcess.h
 *
 * The First Process is exactly the same as every other process. i.e. it must inherit cProcess.
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
 *  void Stop();
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
* Run():
*	Run() is run once every frame as long as cCore is alive and controls the entire program. The Run() function should is explicity designed to be re-written by the user to give each cProcess class their functionality. This Code can be seen as the behaviour that the process should follow. It should rotate and position the Process' Renderobjects, send signals, receive inputs, anything the Process may want to do as part of it's behaviour. The function cCore::Run() can be used like any other process, but is usually used to oversee the running of the program.
* \code
* void cCore::Run()
* {
*
*  if(KEY_SPACE) _CAMERA->Far(10.0f);
*   else _CAMERA->Far(1000.0f);
*  _CAMERA->Frustum();
*
*  _CREATE(AnotherProcess());
*  mpRenderObjectPointer->Advance(0.1f);
*
* }
* \endcode
*
*
* Stop():
*	This is called whenever the cCore Process is Killed. This will only activate if the process was alive and is now dead. This should be used to kill or transfer control of Render Objects that are owned by this process, or unload files that are no longer used.
*
* \code
* void cCore::Stop()
* {
* _KILL(mpRenderObjectPointer);
* mpProcessPointer_SIGNAL(_S_SLEEP);
* }
* \endcode
*
* OnSleep():
*	This is called whenever the cCore Process is made to Sleep. This will only activate if the process was awake and is now asleep. This is generally used to sleep Render Objects that are owned by this process.
*
* \code
* void cCore::OnSleep()
* {
 * mpRenderObjectPointer->Signal(_S_SLEEP);
 * }
 * \endcode
 *
 * OnWake():
 *	This is called whenever the cCore Process is made to Wake. This will only activate if the process was asleep and is now awake. This is generally used to wake Render Objects that were slept when cCore was sent to sleep.
 *
 * \code
 * void cCore::OnWake()
 * {
 * mpRenderObjectPointer->Signal(_S_WAKE);
 * }
 * \endcode
 *
 * \section ProcessObjectsPage How to use Process Objects
 * WTcProcess.h
 *
 * Using William Thorley’s Process Handler System
 *
 * When properly implemented the process handler automatically links and runs all processes.
 * A process must inherit cProcess. It must also define the virtual function Run() a process without a Run() function is useless, and will be deleted during the frame it is created.
 *
 * Declaring a new process class called player:
 * \code
 * //This is the same as _PROCESS(player)
 * class player : public cProcess
 * {
 * public :
 * void Run();
 * };
 * \endcode
 *
 * void cProcess::Run();
 *	The function Run() is a virtual function already defined. This function is called every time the process must run its code (usually once a frame).
 *  The code that defines how the process acts goes in Run().
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
 * Killing a Process:
 *	Process' must not be destroyed by deleting the process. Processes can be be deleted either by calling the macro _KILL(); or by calling the Function Signal(SIGNAL lsFlags) with the flag _S_KILL. if _KILL() is called without a pointer it will automatically use the pointer this. Process' will not be destroyed when the signal is sent, they will be deacticated, but the memory will remain allocated until cKernel reaches the correct stage to delete the object. Objects can remain allocated into the next frame, but not the frame after that. Both pieces of following code have the same effect. The Process pointed to by mpPointerToAnotherProcess is Killed and then this process is killed.
 * \code
 * void player::Run()
 * {
 *
 * if(KEY_k)
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
 * if(KEY_k)
 *	{
 *	 _KILL(mpPointerToAnotherProcess);
 *	 _KILL();
 *	}
 *
 * }
 * \endcode
 *
 * Sleeping a Process:
 *	A Process can be sent to sleep by calling the cSignal::Signal(SIGNAL lsFlags) function with the value _S_SLEEP. Sleeping a process leaves the process in the process list, but stops the Run() function being called every frame. This allows the Signal(SIGNAL lsFlags) function to be used to return it to ‘active duty’. The memory will remain allocated. Sending repeated Sleep calls to a process will not affect the process or the stability of the system, the Process will remain asleep.
 *
 * Waking a Process:
 * A Process can be awakend by calling the cSignal::Signal(SIGNAL lsFlags) function with the value _S_WAKE. Sending repeated Waking calls to a process will not affect the process or the stability of the system, the Process will remain awake.
 * \code
 *
 * void player::Run()
 * {
 *
 * if(KEY_s) mpPointerToAnotherProcess->Signal(_S_SLEEP);
 * if(KEY_w) mpPointerToAnotherProcess->Signal(_S_WAKE);
 *
 * }
 * \endcode
 *
 * Removing a Process:
 *	A Process can be killed by the cKernel object. Calling the cKernel::Remove() function will kill the process and free the memory. This must not be done to the currently running process or the system may crash. Use on the current process at your peril. The pointer is to the cLinkedNode<vProcess> which owns this process. Each Process has a pointer (mpNode) to its cLinkedNode<vProcess>.
 * \code
 *
 * void player::Run()
 * {
 *
 * if(KEY_k) _KERNEL->Remove(mpPointerToAProcessesNode);
 *
 * }
 * \endcode
 * \section RenderObjectsPage How to use Render Objects
 * WTcRenderObject.h
 *
 *
 * All Render Objects are inherited from class vRenderObject, through class cRenderObject.
 * The object also Inherits the class cMatrix4. This is a 3D Translation class, and can handle 2D rotations (about X axis), 3D rotations, 3D Translations and 3D scaling. All cMatrix4 functions can be called from a pointer to any Render Object and will move the cRenderObject based on the cMatrix4 function called.
 * Render Objects must be assigned a Shader to render to screen. Due to depreciation of OpenGL Functionality shaders are required to position an object in 3D space. All objects must be given a cShaderProgram to render.
 * Creating RenderObjects:
 * cRenderObjects can be created using the _CREATE macro as per a Process. This will return a pointer to the RenderObject.
 * \code
 * void player::Run()
 * {
 * 	mpHull=_CREATE(cModel(mpShipNode));
 *	mpHull->Mesh("Mesh");
 *	mpHull->Texture("Texture");
 *	mpHull->Shader("TexturingProgram");
 * }
 *\endcode
 *
 * Currently there are lots of Render Objects:
 *
 * class cModel; \n
 * class cLandscape; \n
 * class cBeamMesh; \n
 * class cImage; \n
 * class cTextureText; \n
 * class cLine; \n
 * class cParticle; \n
 * class cParticleGroup; \n
 * class cParticleHandler; \n
 * class cPoint; \n
 * class cButton; \n
 * class cTextButton; \n
 * \n
 * There are also Render Nodes. These do not display on the screen bu manipulate the position of other objects.
 * Essentially they create new co-ordinate systems. This allows objects to be positioned and rotated to other objects or points in space.
 * This allows the 'gluing' or 'linking' of objects together. This allows the creating of models with limbs, or turrets etc. \n
 * class cRenderNode; \n
 * class cNodeList; \n
 * \n
 * See the relevant documentation for each for how to use them. \n
 *\n
 * The Renderable Object allows the user to develop their own Renderable Objects and links them to the renderer.
 * A Renderable object must inherit cRenderObject and must also define the virtual function Render(), This will be called every time the renderable object needs to be rendered.
 * It should also define all empty virtual functions in vRenderObject and cRenderObject.
 *
 * \section MultiTexturing Texturing Objects
 * In the latest release Multiple Textures have been implemented. This means that you can send, a texture, a bump map and a lighting map to a single model and produce much more complicated shader effects. \n
 * For those who don't want a detailed overview.
 * - Your shaders should call their uniform sampler2D variables "Texture0" "Texture1" "Texture2" etc.
 * - In the class cUserSettings set the variable WT_TEXTURE_NUMBER_ALLOWED to the number of simultaneous textures required. This is 2 by default.
 * - An Object can only have textures applied to it once it has a shader. Use the function cRenderObject::Shader(cShaderProgram*).
 * - Use the function cRenderObject::AddTexture(cTexture*) to add a texture to a cRenderObject. They will be added to the object and placed in slots in the order they are added.
 * \n
 * Textures are applied to Renderable objects using the function AddTexture(string,cTexture*). This function will add the Texture pointer to the Texture slot with the name matching lsTextureSlot.
 * Alternatively AddTexture(cTexture*) or AddTexture(string) can be used. This will add the texture to the next free texture slot in the shader named "Texture0" "Texture1" "Texture2" etc. \n
 * Declaring Textures in Fragment Shaders:
 * Multitexturing in shaders is controlled using uniform sampler types:
 * \code
 * uniform sampler2D Texture0;
 * \endcode
 * This takes a 2D Texture and names it Texture0. By default Bamboo shaders use the names Texture0, Texture1 ,Texture2 etc. If you use different names for your texture samplers they will need to be linked to their textures using AddTexture(string,cTexture*). \n

 * \section FilesAccessPage Loading and Accessing Files
 *
 * WTcFile.h
 *
 * The Filehandler is an automatic system for controlling files loaded in @EngineName. All files should be of type IMF, though others can be loaded. When a file is loaded it is automatically linked into the system. This allows any process to access any loaded file.
 * All Objects (blocks within IMF Files) are given a Reference (a character string) to allow them to be easily identified. And in the event of an OS clearing data (for instance Windows clearing Textures on Minimize) the file handler will automatically reload all the files.
 * IMF Files can be created using the IMF Handler. This allows other files to be loaded and compiled into IMF Files. IMF Files are designed to not require any processing to speed loading times. It also allows the system to use object references which makes accessing components much much easier.
 *
 * To create a new File Class and make it use the file handler, have it inherit cFile, This will require #include “WTcFile.h”.
 * To load a new file use the macro _LOAD_FILE(FileName).
 *
 * IMF Files contain many types of data:
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
 *
 * Useful Macros:
 *
 * These will return a pointer to the file of the appropriate type with the Test Identifier 'Reference'. The files are checked for type, however giving files the same text
 * identifier is bad practice.
 * _GET_TEXTURE_FILE(Reference)
 * _GET_MESH_FILE(Reference)
 * _GET_FONT_FILE(Reference)
 * _GET_AUDIO_FILE(Reference)
 * _GET_COLLISION_MESH_FILE(Reference)
 * _GET_LANDSCAPE_FILE(Reference)
 * _GET_COMPOUND_COLLISION_FILE(Reference)
 * _GET_MODELLIST_FILE(Reference)
 * _GET_FILE(FileType,FileName) Will allow you to specify a type for the file and a text identifier reference. This should only be used for used defined File types.
 *
 * The default linking code is of the Form cFileHandler::Instance()->File<FileType>(FileName). The Macros above automatically select the appropriate Internal class.
 * \section InputsPage Accessing User Inputs
 *
 * There are two main types on input. Mouse inputs and Key inputs. Both are updated every frame and buffered until the next frame. This means that a key press or mouse position will be consistent throughout the entire frame. THe inputs re recieved as interupts so will be recieved in line with the OS.
 * Key states are boolean and can be accessed using the macro _KEY(Key Identifier). A list of Key Identifiers can be found on page \ref KeyIdentifiersList "Key Identifiers". True is key pressed, false is key not pressed.\n The Key Identifiers are unsigned integer values and can be handled as such, this means they can be passed to functions and processes as unsigned integer values. They can also be manipulated mathematically if the actual values they hold are know.\n \n
 * The Mouse can be accessed using the macro _MOUSE() which is a pointer to the cMouse Object. The mouse has three buttons (for now) left, right and middle, because that is enough for most people. Like keys these are boolean values, with true for pressed and false for not pressed. The mouse also has x,y and z which are the cursor position in pixels from the window position 0,0. Finally the mouse has xs and ys which is the amount the cursor has moved (in pixels) since the last frame.\n \n
 * The macro _MOUSE() is of the form cEventHandler::Instance()->Mouse()\n
 * The macro _KEY() is of the form cEventHandler::Instance()->Key.GetKey(_CHOSEN_KEY)\n
 * \section AudioPage Using the Audio System
 *
 * The class cAudioObject are used to play sounds from the sound card. Audio files are included into IMF Files and loaded like any other IMF file.
 * A Sound file is passed to the buffer and played with the Play() command. When the sound is played it will take up a channel on the sound card.
 * A Audio Media File can be accessed using the _GET_AUDIO_FILE() Macro like anyother type of media.
 *
 * \code
 *
 * //Create a new cAudioObject.
 * cAudioObject *mAO;
 *
 * // Load an IMF file with some audio media.
 * _LOAD_FILE("./src/User/Audio/wave1.imf");
 *
 * //Create the cAudioObject to buffer the sound file in.
 * mAO = new cAudioObject;
 *
 * //Load the sound file into the buffer
 * mAO->SetBuffer( "SoundReference" );
 *
 * //Play the sound
 * mAO->Play();
 *
 * \endcode
 *
 *
 * \section SignalsPage Signals and Flags
 *
 * There are a range of Signal macros which allow you to send signals to other processes.
 * \code
 * if(KEY_SPACE) _SLEEP_THIS();
 * cProcess *OtherProcess;
 * OtherProcess=_FIND_PROCESS(cChildProcess);
 * _KILL(OtherProcess);
 * \endcode
 * \n \n
 * List of macros:
 * _KILL(PROCESS)  : Will kill the object pointed to by PROCESS.
 * _SLEEP(PROCESS) : Will sleep the object pointed to by PROCESS.
 * _WAKE(PROCESS)  : Will wake the object pointed to by PROCESS.
 * _KILL_THIS()  : Will kill this object. Code after this will still be run, once this frame. The command return will allow the user to exit the object without running further code.
 * _SLEEP_THIS() : Will sleep this object. Code after this will still be run, once this frame. The command return will allow the user to exit the object without running further code.
 * _WAKE_THIS()  : Will never have an effect. (As the code will not run if this object is asleep and there is no waking to be done if the process is awake).
 *
 * You can send your own signals between processes by defining the function cUserSignal::UserSignal(SIGNAL lsSignal,void * lpData) in your process class. This function is empty and virtual so
 * This function is entirely user defined  which means you can use your own flags to signal different actions for different processes. The void pointer allows you to send any additional information you may want.
 * UserSignal() is a part of cProcess so any cProcess pointer can use it and will select the version of the function in the derived class. \n
 *
 * For Advanced Programmers: \n
 * The macros above actually link to the inherited function Signal(uint8) in cSignal. This takes the following flags to have the desired effects.
 * This will activate cSignal::AdditionalKillFunctionality(), cSignal::AdditionalSleepFunctionality(), cSignal::AdditionalWakeFunctionality() when Killed, slept of woken.
 * - _S_KILL
 *  - Kill the process. It will be deactivated and no longer run. Once it is safe to do so, the Kernel will delete the object. This techincally Sleeps the object (so it won't run) then deletes the object once it is handled.
 * - _S_SLEEP
 *  - Sleep the process. It will be deactivated, but will not get deleted. The Process will continue to exist, but will not run. Objects this Process controls will remain and can be controlled from other processes.
 * - _S_WAKE
 *  - Wake the Process. A Sleeping process will be reawakened and will start to run again.
 * - _S_KILL_TREE
 *  - If the Variable WT_USE_PARENT_TREE is true, this will kill the signaled object and any child objects it created. This will act recursively until all children, grandchildren, great grandchildren etc. have been killed.
 * - _S_SLEEP_TREE
 *  - If the Variable WT_USE_PARENT_TREE is true, this will Sleep the signaled object and any child objects it created. This will act recursively until all children, grandchildren, great grandchildren etc. have been Slept.
 * - _S_WAKE_TREE
 *  - If the Variable WT_USE_PARENT_TREE is true, this will Wake the signaled object and any child objects it created. This will act recursively until all children, grandchildren, great grandchildren etc. have been Wakened.
 * .
 * \section CollisionsPage Detecting Collisions
 *
 *
 * Collision Objects will only collide with other collision objects, NOT Render Objects. When a Collision Object is created it must be passed a pointer to a Render Object which will define it's translation. This should be the first argument passed to a Collision Object.
 *
 * Collision Objects are created using the _CREATE() Macro and killed using the _KILL() Macro, as per a process. They can be slept and woken, like other objects.
 * When Created a Collision Object needs to be linked to a process and a Renderable object. In the initialiser a pointer to a Render Object and a cProcess should be handed to the object.
 * Collisions can be Filtered based on an unsigned integer value. When a Collision check is made, a filter can be specified (if not specified or specified as 0 then all collision objects will be checked for a collision) allowing the user only to check against objects the user is interested in.
 * Collisions are very slow and the number of checks should always be minimised. Sphere Collisions are the fastest type, but do not allow any adjustment to fit the object. Objects should be given a filter value to allow them to be searched based on user defined properties. If the objects have no filter they will only be searched when a filter free search is performed.
 * Collision Objects need a media type to define how and when they collide. Objects which are linked to a Renderable Object will be killed when their Renderable object is killed. As such Killing them is not required.
 * This is defined using the Type Function which gives the Collision Object the data it needs and sets the type of collision Object it will be.
 * There are many ways that Type can be set - either handing a pointer to Collision Data object:
 * \n \n
 * Types of Collision Data:
 *	cCollisionSphere\n
 *	cMeshCollision\n
 *	cCollisionRay\n
 *	cCollisionBeam\n
 *	cCollisionBox\n
 *	cCollisionBoxFile\n \n
 * or Handing it the data it needs to generate one:\n
 * Float : Sphere Collision.\n
 * Two Floats : Beam - (Length, Radius) \n
 * Six Floats : Box Collision - (+X, -X, +Y, -Y, +Z, -Z) \n
 * Float Pointer to Six Floats : Box Collision - (+X, -X, +Y, -Y, +Z, -Z) \n
 * cRenderObject Pointer : Ray Object (will generate a beam encapsulating the space the object has moved through this frame - suitable for fast moving objects which will be modelled as spheres). \n
 *
 * \code
 *
 * MyProcess::MyProcess()
 * {
 *  mpRender=_CREATE(TexturedModel());
 *  mpCollision=_CREATE(cCollisionObject(mpRender,this));
 *
 *  mpCollision->SetType(10.0f);
 *  mpCollision->CollisionFilter(1);
 * }
 *
 * void MyProcess::Run()
 * {
 * uint32 CollisionFilterValue;
 * CollisionFilterValue=2;
 *  vProcess *lpProc;
 *  cCollisionList* lpList;
 *  lpList = mpCollision -> GenerateCollisionList( CollisionFilterValue );
 *	_COLLISION_PROCESS_LIST(lpList,lpProc)
 *	{
 * 		 		_KILL(lpProc);
 *	}
 *	delete lpList;
 *
 * }
 * \endcode
 * \section RenderNodesPage Creating Local Co-ordinate systems
 *
 * WTcRenderNode.h
 * WTcNodeList.h
 *
 * <b> cRenderNode: </b>
 * RenderNodes are a special type of Render Object. Render Nodes have no visual rendering to screen. Instead they manipulate other Render Objects. Specifically, a Translation applied to a Render Node will affect any Render Objects Controlled by the RenderNode.
 * This means the objects controlled by the Render Node will move as if the Render Nodes position was 0,0,0.
 *
 * \code
 * mpNodePoint=_CREATE(cRenderNode());
 * mpNodePoint->Position(0.0f,0.0f,0.0f);
 * mpModel=_CREATE(cModel(mpNodePoint));
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
 * Render Node objects can control any Render Object, including Render Nodes. This means that there can be many levels of Render Nodes before reaching a Renderable Object, making positioning of complex positional relationships easy. \n
 *\n
 *<b> cNodeList:</b>
 * There are also NodeLists. These are static objects. They are initialised to hold a certain number of objects and only support rotations around the local axis.
 * These are good for predictable structure shapes which do not change often.
 * Each object is given a level and will position and rotate itself around the last object with a lower depth value.
 *
 * \code
 * //Create a Tree with 14 slots.
 * mpNodeList=_CREATE(cNodeList(14));
 *
 * //Create 14 new cModels to fill the NodeList
 * uint32 liCount;
 * for(liCount=0;liCount<14;++liCount)
 * {
 * 	_CREATE(mpNodeList);
 * }
 *
 * //Set Mesh and Level for each Item
 * //Make Object 0 use the Mesh "Torso"
 * mpNodeList->GetListItem(0)->Mesh("Torso"));
 * //The torso is the top of the tree. This is the object all other objects will base their position on.
 * mpNodeList->SetLevel(0,0);
 *
 * //Make Object 1 use the Mesh "Head"
 * mpNodeList->GetListItem(1)->Mesh("Head"));
 * //Make Object 1 linked to the Torso (last object with a Depth lower than this objects)
 * mpNodeList->SetLevel(1,1);
 *
 * //Make Object 2 use the Mesh "LeftUpperArm"
 * mpNodeList->GetListItem(2)->Mesh("LeftUpperArm"));
 * //Make Object 2 linked to the Torso.
 * mpNodeList->SetLevel(2,1);
 *
 * //Make Object 3 use the Mesh "LeftForeArm"
 * mpNodeList->GetListItem(3)->Mesh("LeftForeArm"));
 * //Make Object 3 Linked to the LeftUpperArm
 * mpNodeList->SetLevel(3,2);
 *
 * //Make Object 4 use the Mesh "LeftHand"
 * mpNodeList->GetListItem(4)->Mesh("LeftHand"));
 * //Make Object 4 Linked to the "LeftForeArm"
 * mpNodeList->SetLevel(4,3);
 *
 * //You have now built a torso with a head and a left arm. repeat for the other limbs.
 * mpNodeList->GetListItem(5)->Mesh("RightUpperArm");
 * mpNodeList->SetLevel(5,1);
 *
 * mpNodeList->GetListItem(6)->Mesh("RightForeArm");
 * mpNodeList->SetLevel(6,2);
 *
 * mpNodeList->GetListItem(7)->Mesh("RightHand");
 * mpNodeList->SetLevel(7,3);
 *
 * mpNodeList->GetListItem(8)->Mesh("LeftThigh");
 * mpNodeList->SetLevel(8,1);
 *
 * mpNodeList->GetListItem(9)->Mesh("LeftShin");
 * mpNodeList->SetLevel(9,2);
 *
 * mpNodeList->GetListItem(10)->Mesh("LeftFoot");
 * mpNodeList->SetLevel(10,3);

 * mpNodeList->GetListItem(11)->Mesh("RightThigh");
 * mpNodeList->SetLevel(11,1);
 *
 * mpNodeList->GetListItem(12)->Mesh("RightShin");
 * mpNodeList->SetLevel(12,2);
 *
 * mpNodeList->GetListItem(13)->Mesh("RightFoot");
 * mpNodeList->SetLevel(13,3);
 *
 * //You now have a skeleton for a humanoid robot. Moving limbs requires moving any one object and the rest of the objects linked will autoamtically move.
 * //This can be build into a MeshTree in the IMF Handler so it can be loaded from a file.
 * \endcode
 * \section MultipleCamerasViewports Multiple Cameras and Viewports
 * Bamboo has full support for multiple cCamera Objects, cViewport objects and rendering to specified regions.
 * cCameras are seperate cameras. They store a scene graph (tree of vRenderObjects and vRenderNodes) and will render them to the specified region of the screen.
 * cCameras are controlled by signals, so _CREATE() should be used to create them and _KILL() should be used to kill them. Once killed, all objects in their scene graph will be destroyed and so should not be accessed.
 * Each cCamera Object has it's own objects so creating a Render Object in one will not affect another. \n
 * cViewports are slightly different. They also render a scene graph to the screen in a specified region, but do not have a scene graph of their own.
 * All cViewports are owned by a cCamera object and will render the cCamera objects scene graph. This is much more efficient than using a second cCamera as only one scene graph is stored and updated. It allows the user to view the same scene as it's camera from a different position, rotation or perspective.
 * All vRenderObjects can be passed a cCamera as an argument in their constructor which will make them use the specified cCamera. If they are passed a vRenderNode as a parameter, they will become a child of the cCamera which owns the vRenderNode which owns the vRenderObject.
 * the _CAMERA pointer will always point to the first cCamera object and will be used as a default when no cCamera is specified.
 * \code
 * //Create a Model on the default cCamera object and have the cCamera follow it at a distance of 60.
 * cModel* lpModel=_CREATE(cModel);
 * lpModel->Mesh("MyMesh");
 * lpModel->Shader("TexturingProgram");
 * lpModel->Texture("MyTexture");
 * _CAMERA->Follow(lpModel,60.0f);
 *
 * //Create a Viewport owned by the default cCamera object. and have the cCamera follow it at a distance of 60.
 * cViewport *lpViewport=_CREATE(cViewport);
 * //Set the View port to render to the area X : 100 - 300 and Y : 100 - 400.
 * lpViewport->Viewport(100.0,100.0,200.0,300.0);
 * //Set the Viewport to follow the model at a distance of 20
 * lpViewport->Follow(lpModel,20.0);
 *
 * //The model will appear twice on screen.
 * //Once across the entire screen at a distance of 60.
 * //Once in the area, X:100-300 Y:100-400 at a distance of 20.
 *
 *
 * //Create a new cCamera. Set it to use the region proportional to the screen size of X:0.5-0.75 Y:0.5-0.6.
 * cCamera *lpCamera=_CREATE(cCamera);
 * lpCamera->Proportional(true);
 * lpCamera->Viewport(0.5,0.25,0.5,0.1);
 *
 * //Create a Model and make the cCamera lpCamera its parent.
 * cModel* lpModel2=_CREATE(cModel(lpCamera));
 * lpModel2->Mesh("MySecondMesh");
 * lpModel2->Shader("TexturingProgram");
 * lpModel2->Texture("MySecondTexture");
 *
 * //Make the second Camera Follow lpModel2.
 * lpCamera->Follow(lpModel2,30);
 *
 * //lpModel will not appear in the screen region used by lpCamera as the object is not owned by lpCamera.
 * //lpModel2 will not appear in either the screen region used by the default camera or its viewport.
 * //As the object is not owned by the default camera.
 * \endcode
 * \section IMFGenerationPage IMF File Generation and Usage
 *
 * IMF Files are generated by the IMF Compiler. The IMF Compiler is a seperate program to the @EngineName engine and has a text based interface. The Compiler should be run from the terminal, so the user can view and use the interface.
 *
 * Everytime the user runs the program will start with an empty IMF File. IMF Files contain media blocks. Each block begins with a type identifier to identify the type of media stored in the block. This is followed by a size specifier defining the amount of data in the remainder of the block. Finally the Block has a character string storing the reference.\n
 * The main task the user will perform is to add Media to the IMF File. Each Media file added will require a reference (a character string which allows the media to be identified in the @EngineName Engine) and often other data to fully define the object.\n
 * Media can often be converted into several different types of IMF Blocks. e.g. A image can be converted to a 2D Texture, a Landscape height map or if it is 64 times taller than it is wide into a font. Each of these require different information to generate the object.\n
 * An IMF File can contain many blocks all with different media types in. This allows the user to group media into sensible sets which are interdependant, eg a tank body model, a tank turret model, a tank shell model, a texture for the tank, and a model list representing the skeletal structure for the tank. This ensures that all inter dependant media can be loaded with a single call.\n
 * Each level of the menu defines the options available to the user, selecting 0 will always move the user back up to the previous level. Otherwise, the user should select the desired option, insert the number representing it and press enter.\n
 *
 * To add each item, select 1 from the main menu. Each file Name (including file type) which is entered will be added to the IMF File as a new block. The system will request all the information required to generate the object, then add it to the IMF File as a new block. Take care when selecting the references as they are the only way to access the media in the @EngineName Engine.\n
 * Once all the required media files are added to the IMF file, it can be written to the harddrive, by selecting option 7. The IMF file type should be included by the user.\n
 * IMF Files can be loaded and will add all their blocks to the end of all the blocks in the current IMF File. This allows the user to add new media to previous groupings.\n
 *
 * Media Types Supported:\n
 * Shader Code:\n
 *	.shd			(text files containing GLSL (GL Shader Language) shader code)\n
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
 * Sound Files: \n
 *  .wav\n
 * Sound Files can be converted into:\n
 *  Audio Data files\n
 * \n
 * \subsection IMFUse Using the IMF Handler :
 * The IMF Handler has a graphical interface to ease control of it.
 * The large list box on the left of the GUI lists all the references of objects in the file.
 * Clicking on an item in the list will display the objects information in the middle section of the GUI.
 * On the right are the settings and controls for the IMF Handler.
 * \subsection IMFControls Using the IMF Handler Controls :
 * The "Add Media File" button :\n
 * Clicking the "Add Media File" button will open a file dialog. Selecting a file will load it into the current IMF.
 * The IMF Handler will then ask for a string reference to identify the media file in the game engine.
 * The files can be filtered based on types. Only types supported by the IMF Handler will be displayed.
 * When the file is loaded it will use the current settings on the GUI.
 * This means settings should be set before trying to add a new media file.
 * These settings determine what type of internal format the file will be loaded into.
 * The specifics of loading each file type will be listed in the section for the appropriate file types. \n
 * The "Add Shader Program" button :\n
 * Shader Programs are not loaded from a file, but generated in the IMF Handler itself.
 * The "Add Shader Program" button will ask for a string reference to identify the shader program.
 * It will then create a new Shader Program in the current Media file.
 * This can be modified by following the instructions in the Shader Program section. \n
 * The "Add Render Tree" button :\n
 * This allows the user to generate cNodeList Objects and store them in an IMF file. \n
 * The "Save IMF As..." button :\n
 * Clicking the "Save IMF As..." button will save the current IMF. It will create a dialog to ask for the file name to use.
 * This will write all the objects and references currently loaded into an IMF file.
 * You do not need to add '.imf' to the end of the file name. The files can then be loaded by Bamboo. \n
 * The "Remove Media" button :\n
 * The "Remove media" button will remove a single selected media item from the list. Select the item from the Reference List and then click the "Remove Media" button.
 * The "Clear File" button :\n
 * The "Clear File" button will remove all the items from the IMF File. Essentially this will clear the current IMF file and create a new empty file. \n
 * The "Quit" button :\n
 * The "Quit" button will quit the program. It will not save the IMF. All changes to the file will be lost.
 * \subsection IMFSettings IMF Handler Settings :
 * The Handler Settings section can be found in the top right of the GUI. \n
 * "Load Model Files As..." : \n
 * This section has two check boxes. If the "Renderable Object" check box is ticked any model file will be converted into a Renderable mesh.
 * If the "Collision Objects" check box is ticked any model file will be converted into a collision mesh. In both cases, the IMF Handler will require a reference for the generated mesh.
 * If both boxes are ticked both will be generated. The Renderable Mesh will be generated first and will require its reference first. \n
 * "Load Image Files As..." : \n
 * This section has two radio boxes. Only one can ticked at any time.
 * While the "Textures" radio button is ticked, Image files will be converted into textures.
 * Textures are images that can be glued onto 3D models to texture their surface.
 * While the "Height Maps" radio button is ticked, Image files will be converted into a Landscape height map.
 * The lightness of each pixel represents the height of the landscapes vertex.
 * RGB  = 0,0,0 is the lowest point on the height map, RGB = 255,255,255 being the highest point on the height map.
 * "Load Shaders As..." : \n
 * The "Load Shaders As..." section has three radio buttons. Only one can be selected at any time.
 * While the "Vertex Shaders" radio button is ticked any shader files will be loaded, and processed as Vertex shaders.
 * This means they will operate on each vertex. They can receive Uniform or Attribute variables. They can produce varying values for passing to fragment shaders.
 * While the "Fragment Shaders" radio button is ticked and shader files will be loaded, and processes as Fragment shaders.
 * This means they will operate on each fragment. They can receive Uniform and varying variables. Attributes cannot be accessed by fragment shaders.
 * Varying variables which have been produced by a vertex shader can be accessed by a Fragment shader.
 * The varying values are interpolated from the varying values created by the verteces.
 * Currently the "Geometric Shaders" radio button cannot be ticked.
 * "Set Font Resolution..." : \n
 * The "Set Font Resolution..." value is the width and height of font characters that will be generated.
 * When true type font files are loaded into Bamboo, they are rendered into character textures as OpenGL is optimised for rendering textures rather than true type fonts.
 * For optimal performance these characters are restricted to multiples of 8.
 * The larger the character size the clearer the characters will be, however the larger the files generated will be.
 * \subsection IMFTypes Specifics of media types :
 * General Media Information : \n
 * All media will require a reference to allow it to be identified in Bamboo. This is a string.
 * The IMF Handler will automatically assign it a new reference string, but this should be set as a descriptive string by the user.
 * This can be changed for all media types by selecting the media files reference from the Reference List on the left of the GUI
 * and typing a new reference ino the box labelled "Reference:" in the middle section of the GUI. This will change the medias reference. \n
 * Selecting a file from the Reference List on the left will also configure the middle section of the GUI to display settings controls and data relating to the file selected.\n
 * Model Meshes : \n
 * When a Models reference is selected in the references list.
 * It will configure the middle section of the GUI to display the models.
 * It will show the list of Verteces, Normals, UV Co-ordinates and Vertex Indices requried to generate the triangulated faces.
 * All faces are triangulated when compiled to optimise performance in OpenGL. \n
 * Collision Meshes : \n
 * A Collision Mesh cannot have any concave faces. Any concave faces (or holes in the surface) will lead to unexpected collision events.
 * Concave faces will mean some collisions which should collide are missed. Conversely holes will catch collisions which do not exist.
 * It also needs to have a minimal number of faces to define the boundaries of the object it is representing.
 * Accuracy of collision meshes is less important than speed of calculations. The system will optimise out any polygon that will statistically have a minimal chance of affecting whether a collision is detected or not.
 * Traditionally Collision Meshes have 10 - 30 polygons, but obviously the number required depends on the complexity of the model being represented. \n
 * When a collision mesh is selected from the Reference List it will display the collision meshes critical data. A collision Mesh is actually compiled into two seperate data sets.
 * A set of verteces and a set of polygons. A vertex has three positions representing the X,Y and Z co-ordiantes of the vertex.
 * A Plane is composed of four values.
 * Three values for multiplying with vertex co-ordinates to generate a distance from the origin perpendicular to the plane.
 * The fourth value is the planes distance from the origin. This makes it quick to calculate if any point in the same co-ordinate system is above or beneath the plane.
 * Texture Images : \n
 * Textures should have a width and height which is a power of 2 (2,4,8,16,32,64...).
 * This will make UV mapping more accurate and avoid the texture being padded by the graphics card.
 * The larger the texture the larger the file generated, but the resulting image will be clearer at large magnifications.
 * OpenGL will automatically generate mip maps for rendering the image at lower magnifications, so only the largest texture resolution desired need be compiled.
 * When selected from the reference list the IMF Handler will display the width, height and color depth of the texture loaded.
 * Height Maps : \n
 * Landscapes are created from a square matrix of polygons. Each pixel in the image used to generate a height map will create a vertex.
 * This means the landscape generated will have a number of verteces across equal to the width of the image in pixels.
 * The landscape will have a number of verteces along equal to the height of the image in pixels.
 * This means the number of polygons across and along are one less than the images width and height.
 * The height of each vertex is determined by the lightness of its pixel.
 * RGB = 0,0,0 is the lowest point on the height map, RGB = 255,255,255 being the highest point on the height map.
 * When a Height Map is selected from the reference list the IMF Handler will display the dimensions of the height map generated.
 * It will also update the GUI with some settings specific to the landscape selected. Changing the values will only update the selected landscape.
 * - The value labelled "Tile X Size" is the distance in the X dimension between each vertex in the landscape.
 * - The value labelled "Tile Z Size" is the distance in the Z dimension between each vertex in the landscape.
 * - The value labelled "Height Range" is the value that the Y dimension of a vertex will be for a pixel with RGB = 255,255,255.
 * This sets the highest point that is possible in the landscape.
 * - The "Gradient Factor" is a 'skewing' effect. With verteces which are the same distance apart the gradient of any plane is determined solely by the height difference between the verteces used to generate them.
 * This means that a vertical plane is impossible.
 * The gradient factor determines how much verteces can move towards each other based on the height difference in the verteces.
 * A gradient factor of one can produce a vertical plane from sufficiently spread verteces.
 * Essentially this makes the landscape less rolling based on the range of 0 to 1.
 * Every time the gradient effect is applied it is irreversable and stacks with any other gradient factor applied. To apply the gradient effect, click the "Apply Gradient" button.
 * - The "Apply Gradient" button will apply the currently selected gradient factor to the landscape.
 * .
 * Shader Files : \n
 * Shader Files are text files. Shaders are simply programs which are performed by the graphics card. Many shaders are available on the internet.
 * The GLSL (GL Shading Language) is similar to C but with extra variable types, defined variables and values specific to rendering images.
 * There are three types of Shader program. Vertex, Fragment and Geometric. Currently Geometic is not supported. Shaders are combined into Shader Programs.
 * A shader program must have at least one vertex shader and one fragment shader. Geometry shaders are optional.
 * Vertex Shaders control the vertices that make up a mesh.
 * They can change the position of the verteces, values of different properties at the vertices (which are linearly interpolated across a polygons face). \n
 * Bamboo Offers a selction of useful 'positioning matrices' mmGlobal , mmCamera , mmProjection , mmCombined. \n
 * It will pass the objects Global Position Matrix in to a mat4 called mmGlobal.
 * \code uniform mat4 mmGlobal;
 * \endcode
 * mmCamera is just the Camera Matrix. This is the Cameras Position and Rotation
 * \code uniform mat4 mmCamera;
 * \endcode
 * mmProjection is just the Projection Matrix. This is the function to map 3D co-oridinates to the screen. Essentially it controls Perspective.
 * \code uniform mat4 mmProjection;
 * \endcode
 * mmCombined is the Camera and Projection Matrices multiplied together.
 * \code uniform mat4 mmCombined;
 * \endcode
 * These should be used to find the position of each vertex, there are several common ways to use the matrices (They should be used to find an objects position). The order of Matrix multiplications do matter. Using mmCombined is much more efficient but some shaders will want to use the camera and Projection matrices seperately.
 * \code
 gl_Position=mmCombined*mmGlobal*gl_Vertex;
 gl_Position=mmProjection*mmCamera*mmGlobal*gl_Vertex;
 * \endcode
 * For 2D Objects only the mmProjection and mmGlobal are passed. The mmCamera Matrix will always be an identity matrix for 2D objects.
 * Fragment Shaders control the render color of individual pixels. The Vertex shader is run once for every vertex in the model.
 * The Fragment shader is run once for every pixel on the screen where the model is visible.
 * A Geometry Shader (GS) is a Shader program that governs the processing of primitives.
 * It happens after primitive assembly, as an additional optional step in that part of the pipeline.
 * A GS can create new primitives, unlike vertex shaders, which are limited to a 1:1 input to output ratio.
 * A GS can also do layered rendering; this means that the GS can specifically say that a primitive is to be rendered to a particular layer of the framebuffer.
 * GS will be enabled in a later version of Bamboo. \n
 * <b> One requirement is that attribute and uniform variables are declared individually on their own line. This is a requirement of the IMF Handler rather than GLSL. </b> \n
 * When a shader is selected from the Reference List it will modify the GUI to display the Shader File display.
 * This gives the option to change the type of shader that the currently selected shader will be used as.
 * Clicking the appropriate radio button in the middle section of the GUI will change the type of the shader. Geometry shaders cannot be selected.
 * It will also display the detected variables and whether they are uniform or attribute.
 * Finally it will also display the shaders code. \n
 * Shader Programs : \n
 * A Shader program is a collection of Shader files, which forms a Shader Program. It must have at least one Vertex Shader and one Fragment shader. You cannot include any shader in a Shader Program more than once.
 * If you run out of spaces in a Shader Program you must increase the Shader Programs size as described later before you can add more shader files.
  * All vertex shaders should be included first. Followed by all the Fragment Shaders.
 * The "Add Shader Program" button will create a Shader Program. It will then ask for a reference for the Shader Program.
 * It is important that Shader Files are loaded before loading a Shader Program which contains them. If in the same IMF it is important put the Shader Files before any Shader Program which uses them.
 * Selecting the Shader Program from the Reference List will modify the GUI to display the Shader File display. \n
 * The value labelled "Number of Shaders" is the number of Shader files that the Shader Program will use. This can be changed by the user. \n
 * The box labelled "New Shader:" is used to add new Shader Files to the Shader Program. Type in the Reference of the Shader File in the box, press enter and it will be added to the current Shader Program. \n
 * The button labelled "Select Shader From File" will bring up a idalog listing all the references for Sahder Files in the current IMF File.
 * Select the desired reference from the drop down menu and click 'OK' to add it to the currently selected Shader Program. This will only list vertex objects in the current file. \n
 * The "Remove Shader Reference" button will remove the Shader Reference in the Shader Program from the Shader Program.
 * Sound Files : \n
 * Sound files are all compiled from .wav files.
 * When a sound file is selected from the reference list on the left it will produce a list of information about the file.
 * - Format:
 * - BlockSize:
 * - Sample Rate:
 * - Byte Rate:
 * - Block Align:
 * - Data Volume:
 * - Compression:
 * - Channels:
 * - Bits Per Sample:
 * - Contains Extra Data
 * .
 * Font Files : \n
 * Font files are formed from ttf files.
 * For speed the IMF Handler renders individual images for each character at the font size specified in the GUI controls section.
 * Some fonts extend beyond the area that Bamboo uses. This can cause the IMF Handler to crash.
 * The IMF Handler should detect this is the case and raise a warning asking if you wish to continue.
 * Often the IMF Handler will be able to handle fonts which extend outside the acceptable range but not always.
 * If a warning is raised it may crash the IMF Handler, so continue at your own risk. \n
 * Selecting a font file from the Reference List on the left of the GUI will modify the central section of the GUI to display the fonts character dimensions and color depth.
 * Font files are compiled as 32 bit as they require an alpha channel and this allows effects to be applied to them in future versions. \n
 * Mesh Trees : \n
 * Mesh Trees are generated in the IMF Handler. They allow you to produce structures composed of seperate objects.
 * These objects can be ordered into a tree with a hierachy of linking. This means an object can be linked to another object making its movements based off the movements of the object with a lower depth.
 * Objects in a Mesh Tree must be cModel types and so can be given a Mesh, Texture and shader. The Mesh and Shader are compulsory for an object to be rendered. The Texture is optional.
 * The objects are also given a depth. Each object will be linked to the previous object in the list with a lower depth value. 0 should be the base object. Objects which base their movement off of the base object should have a depth value of 1.
 * Objects based off of an object with a depth of 1 should have a depth of 2 and be after the object they wish to follow and before the next object with a depth value of 1. \n
 * \n
 * \n
 * A0 \n
 *  |- B1 \n
 *  |  |- E2 \n
 *  |  |  |- K3 \n
 *  |  |\n
 *  |  |- F2 \n
 *  |\n
 *  |- C1
 *  |  | \n
 *  |  |- G2 \n
 *  |  |- H2 \n
 *  |\n
 *  |- D1 \n
 *     |
 *     |- I2 \n
 *     |- J2 \n
 * \n
 * would be listed (Showing order and depth value of each item): \n
 * A0 \n
 * B1 \n
 * E2 \n
 * K3 \n
 * F2 \n
 * C1 \n
 * G2 \n
 * H2 \n
 * D1 \n
 * I2 \n
 * J2 \n

 * \page CodeProgramExamples Examples of Games Code
 * This section will give a series of examples of programs for games. Initially they will be very simple. Later examples will show expanded functionality.
 * -# \ref BouncingBallExample "Example of a bouncing ball"
 * -# \ref ThreeDimensionBouncingBallExample "Example of a ball bouncing in 3 Dimensions"
 * -# \ref SoundBouncingBallExample "Example of a bouncing ball with a bounce sound"
 * -# \ref BulletsBouncingBallExample "Making the camera controllable. Adding bullets"
 * -# \ref CollisionsBouncingBallExample "Example with Bullet and Ball collisions"
 * -# \ref ReSpwaningBouncingBallExample "Example of Signals. Giving a continual supply of targets."
 * -# \ref CompleteNoCommentsBouncingBallExample "Previous Example without comments"
 * .
 * \section BouncingBallExample Example of a bouncing ball.
 * So lets start with a bouncing ball. This ball will bounce up and down on a plane going through Y = 0.
 * When using Bamboo Programs the ESC key is automatically tagged to exit the program.
 *
 *\code
 //Declare a new type of Process cCore.
 //class cCore : public cProcess
 _PROCESS(cCore)
 {
 public:
 //Create pointer so cCore can  access the object it creates.
 cModel *BallPointer;

 float BallSpeed;

  //Constructor - Initialisation code.
 	cCore()
	{
	//Load the imf pack with objects for demonstration 1.
	//This contains a renderable spherical mesh called BallModel.
	//This contains a texture called BallTexture.
	//This also contains a shader called TexturingProgram.
		 _LOAD_FILE( "Demonstration1.imf" );

	//Create a Textured Model to put the ball on screen.
		BallPointer =  _CREATE(cModel);

	//Set the mesh it will use.
		BallPointer -> Mesh( "BallModel" );

	//Set the Texture it will use.
		BallPointer -> Texture( "BallTexture" );

	//Set the Shader it will use.
		BallPointer -> Shader( "TexturingProgram" );

	//Set a start position.
	//This is relative to the camera.
	// The first value is left and right position of the object.
	// The second value is up and down position of the object.
	// The third value is forwards nd backwards.
		BallPointer -> Position( 0.0 , 20.0 , 30.0 );

	//The ball has been placed 30 units in front of the camera.
	//The ball has been placed 20 units up from the camera.

	//Set the ball so it is not moving at the start.
		BallSpeed = 0.0;
	};

	//This function will update the balls position every process cycle.
	void Run()
	{
		//Increase the balls speed downwards by a small amount.
			BallSpeed = BallSpeed - 0.01;

		//Advance the Ball by its speed.
		//This uses the Global Y Axis as BallSpeed.
		//BallSpeed stores the balls speed.
		//A Local Advance would be affected by rotations.
		//A Global Advance will not.
			BallPointer -> GAdvanceY( BallSpeed );

		//If the ball is closer to the 'ground' than its radius
		//then it has collided with the floor.
		//We will assume it has no radius to make this easier to follow.
		//This means the centre of the ball will touch the 'ground'
		if( BallPointer -> Y()  < 0.0 )
		{
			//If the ball touched the ground
			//it must be moving downwards
			//so make the Ballspeed positive
			//Making it bounce.
			//abs() is a function which will return a positive value
			//whether it was negative or not before.
			//This will make the ball always bounce to the same height.
				BallSpeed = abs( BallSpeed );

			//Changing the above line of code
			//to the following line of code will reduce
			//the height the ball bounces with each bounce.
			//BallSpeed = abs( BallSpeed ) * 0.9 ;
		}
	};

	void Stop()
	{
		//When this dies we want the ball to disappear.
			_KILL( BallPointer );

		//Stop BallPointer pointing at the model as it has been killed.
			BallPointer = 0;
	};
};
\endcode
* \section ThreeDimensionBouncingBallExample Example of a ball bouncing in 3 Dimensions.
* Now lets enclose it in a box of size +/- 30 about 0,0,0
* (The boundaries are
*  - X: -30 / 30
*  - Y: -30 / 30
*  - Z: -30 / 30
* Lets also start it moving in a random direction.
 *
 *\code
 //Declare a new type of Process cCore.
 //class cCore : public cProcess
 _PROCESS(cCore)
 {
 public:
 //Create pointer so cCore can  access the object it creates.
 cModel *BallPointer;

 //Create a variable for each dimension the ball moves in.
 //This could be a c3DVf which is a 3 dimensional vector
 float BallSpeedX;
 float BallSpeedY;
 float BallSpeedZ;

  //Constructor - Initialisation code.
 	cCore()
	{

	//Load the imf pack with objects for demonstration 1.
	//This contains a renderable spherical mesh called BallModel.
	//This contains a texture called BallTexture.
	//This also contains a shader called TexturingProgram.
	 _LOAD_FILE( "Demonstration1.imf" );

	//Create a Textured Model to put the ball on screen.
	BallPointer =  _CREATE(cModel);

	//Set the mesh it will use.
	BallPointer -> Mesh( "BallModel" );

	//Set the Texture it will use.
	BallPointer -> Texture( "BallTexture" );

	//Set the Shader it will use.
	BallPointer -> Shader( "TexturingProgram" );

	//Set a start position.
	//This is relative to the camera.
	// The first value is left and right position of the object.
	// The second value is up and down position of the object.
	// The third value is forwards and backwards.
	BallPointer -> Position( 0.0 , 0.0 , 0.0 );

	//Move the camera back 60 units so it is outside the box.
	//It will look forwards and so look at the ball.
	_CAMERA -> Position (0.0 , 0.0 , -60);

	//Set the ball to move in a random direction at 0.1 units per frame
	//RANDOM_NUMBER is a random float between 0.0 and 1.0.
	BallSpeedX = RANDOM_NUMBER * 0.1;
	BallSpeedY = RANDOM_NUMBER * 0.1;
	BallSpeedZ = RANDOM_NUMBER * 0.1;

	};

	//This function will update the balls position every process cycle.
	void Run()
	{
		//Increase the balls speed downwards by a small amount.
		BallSpeedY = BallSpeedY - 0.01;

			//Advance the Ball by its speed in all three Global axis.
			//This is global as mentioned in the last example.
		BallPointer -> GAdvance( BallSpeedX , BallSpeedY , BallSpeedZ );

		//If the ball is outside any of the boundaries
		//reverse its direction in the appriopriate axis.
		//This is the same as previously, but with 6 boundaries instead of 1.
		if( BallPointer -> X()  < - 30.0 )
		{
			BallSpeedX = abs( BallSpeedX );
		}
		if( BallPointer -> X()  >  30.0 )
		{
			BallSpeedX = -abs( BallSpeedX );
		}

		if( BallPointer -> Y()  < - 30.0 )
		{
			BallSpeedY = abs( BallSpeedY );
		}
		if( BallPointer -> Y()  >  30.0 )
		{
			BallSpeedY = -abs( BallSpeedY );
		}

		if( BallPointer -> Z()  < - 30.0 )
		{
			BallSpeedZ = abs( BallSpeedZ );
		}
		if( BallPointer -> Z()  >  30.0 )
		{
			BallSpeedZ = -abs( BallSpeedZ );
		}

	};

	void Stop()
	{
		//When this dies we want the ball to disappear.
		_KILL(BallPointer);
		//Stop BallPointer pointing at the model as it is killed.
		BallPointer = 0;
	};
};
\endcode
* \section SoundBouncingBallExample Example of a bouncing ball with a bounce sound.
* Lets take the program we used before and give it a bounce sound.
*
*\code
 //Declare a new type of Process cCore.
 _PROCESS(cCore)
 {
 public:
 //Create pointer so cCore can  access the object it creates.
 cModel *BallPointer;

 //Create a pointer so cCore can play the bounce sound.
 cAudioObject *BallBounce;

 //Create a variable for each dimension the ball moves in.
 //This could be a c3DVf which is a 3 dimensional vector
 c3DVf BallSpeed;

  //Constructor - Initialisation code.
 	cCore()
	{
	//Load the imf pack with objects for demonstration 2.
	//This contains a renderable spherical mesh called BallModel.
	//This contains a texture called BallTexture.
	//This also contains a shader called TexturingProgram.
	//This also contains a bounce sound called BounceSound.
		 _LOAD_FILE( "Demonstration2.imf" );

	//Create a Textured Model to put the ball on screen.
		BallPointer =  _CREATE(cModel);

	//Set the mesh it will use.
		BallPointer -> Mesh( "BallModel" );

	//Set the Texture it will use.
		BallPointer -> Texture( "BallTexture" );

	//Set the Shader it will use.
		BallPointer -> Shader( "TexturingProgram" );

	//Set a start position.
	//This is relative to the camera.
	// The first value is left and right position of the object.
	// The second value is up and down position of the object.
	// The third value is forwards and backwards.
		BallPointer -> Position( 0.0 , 0.0 , 0.0 );

	//Set the ball to move in a random direction at 0.1 units per frame
	//RANDOM_NUMBER is a random float between 0.0 and 1.0.

	//Because this is an instance
    //(not a Bamboo engine object)
    //it should be accessed using the dot operator.
		BallSpeed.X( RANDOM_NUMBER * 0.1 );
		BallSpeed.Y( RANDOM_NUMBER * 0.1 );
		BallSpeed.Z( RANDOM_NUMBER * 0.1 );

	//Create an audio file for playing the bounce sound.
		BallBounce = _CREATE(cAudioObject);

	//Create Buffer the sound we want to play into the cAudioObject.
		BallBounce -> Buffer ( "BallSound" );

	};

	//This is the function that will update the balls position every process cycle.
	void Run()
	{
		//Increase the balls speed downwards by a small amount.
			BallSpeedY = BallSpeedY - 0.01;

		//Advance the Ball by its speed in all three Global axis.
			BallPointer -> GAdvance( BallSpeed.X() , BallSpeed.Y() , BallSpeed.Z() );

		//If the ball is outside any of the boundaries.
		//There are much more concise ways of doing this but this is the clearest.
		//This is the same as previously, but with 6 boundaries instead of 1.
		if( BallPointer -> X()  < - 30.0  || BallPointer -> X() > 30.0)
		{
			BallSpeed.X( -BallSpeed.X() ) ;
			BallBounce -> Play();
		}
		if( BallPointer -> Y()  < - 30.0  || BallPointer -> Y() > 30.0)
		{
			BallSpeed.Y( -BallSpeed.Y() ) ;
			BallBounce -> Play();
		}
		if( BallPointer -> Z()  < - 30.0  || BallPointer -> Z() > 30.0)
		{
			BallSpeed.Z( -BallSpeed.Z() ) ;
			BallBounce -> Play();
		}

	};

	void Stop()
	{

		//When this dies we want the ball to disappear.
			_KILL(BallPointer);
			_KILL(BallSound);

		//Stop BallPointer pointing at the model as it is killed.
			BallPointer = 0;
			BallSound = 0;
	};
};
\endcode
* \section BulletsBouncingBallExample Making the camera controllable. Adding bullets.
* Lets let the mouse control the camera. Lets also allow the user to spawn bullets to shoot at the ball.
* We will be making new processes so I will divide it into 3 processes.
*  - The cCore process which loads files, controls the camera and spawns the other processes.
*  - The cBall Process which will control the ball.
*  - The cBullet Process which will control an individual bullet.
*  .
*\code

//Declare and Define a process for controlling the ball.
//class cBall : public cProcess
 _PROCESS(cBall)
 {
 public:
 //Create pointer so cCore can  access the object it creates.
 cModel *BallPointer;

 //Create a pointer so cCore can play the bounce sound.
 cAudioObject *BallBounce;

 //Create a variable for each dimension the ball moves in.
 //This could be a c3DVf which is a 3 dimensional vector
 c3DVf BallSpeed;

  //Constructor - Initialisation code.
 	cBall()
	{
		//Note the media will have been loaded in cCore.
		//Since cCore will create this process
		//media will be loaded before we get to this point.
		//Create a Textured Model to put the ball on screen.
	BallPointer =  _CREATE( cModel );

		//Set the mesh it will use.
	BallPointer -> Mesh( "BallModel" );

		//Set the Texture it will use.
	BallPointer -> Texture( "BallTexture" );

		//Set the Shader it will use.
	BallPointer -> Shader( "TexturingProgram" );

		//Set a start position.
		//This is relative to the camera.
		// The first value is left and right position of the object.
		// The second value is up and down position of the object.
		// The third value is forwards and backwards.
	BallPointer -> Position( 0.0 , 0.0 , 0.0 );

		//Move the camera back 60 units so it is outside the box and looking at the ball.
	_CAMERA -> Position (0.0 , 0.0 , -60);

		//Set the ball to move in a random direction at 0.1 units per frame
		//RANDOM_NUMBER is a random float between 0.0 and 1.0.
		//Because this is an instance
		//(not a Bamboo engine object)
		//it should be accessed using the dot operator.

	BallSpeed.X( RANDOM_NUMBER * 0.1 );
	BallSpeed.Y( RANDOM_NUMBER * 0.1 );
	BallSpeed.Z( RANDOM_NUMBER * 0.1 );

	//Create an audio file for playing the bounce sound.
	BallBounce = _CREATE(cAudioObject);

	//Create Buffer the sound we want to play into the cAudioObject.
	BallBounce -> Buffer ( "BallSound" );

	};

	//This is the function that will update the balls position every process cycle.
	void Run()
	{
		//Increase the balls speed downwards by a small amount.
		BallSpeedY = BallSpeedY - 0.01;

		//Advance the Ball by its speed in all three Global axis.
		BallPointer -> GAdvance( BallSpeed.X() , BallSpeed.Y() , BallSpeed.Z() );

		//If the ball is outside any of the boundaries.
		//Reverse it's direction in that axis
		if( BallPointer -> X()  < - 30.0  || BallPointer -> X() > 30.0)
		{
			BallSpeed.X( -BallSpeed.X() ) ;
			BallBounce -> Play();
		}
		if( BallPointer -> Y()  < - 30.0  || BallPointer -> Y() > 30.0)
		{
			BallSpeed.Y( -BallSpeed.Y() ) ;
			BallBounce -> Play();
		}
		if( BallPointer -> Z()  < - 30.0  || BallPointer -> Z() > 30.0)
		{
			BallSpeed.Z( -BallSpeed.Z() ) ;
			BallBounce -> Play();
		}

	};

	void Stop()
	{
		//When this dies we want the ball to disappear.
		_KILL(BallPointer);
		_KILL(BallSound);

		//Stop BallPointer pointing at the model as it is killed.
		BallPointer = 0;
		BallSound = 0;
	};
};

//Create a new process to be our bullets.
//class cBullet : public cProcess
_PROCESS(cBullet)
{
 public:

  //Give this a pointer to a render object.
  cPoint *RenderPoint;

  //Give this a float to count the bullets lifespan
  //This is a good idea as processes will run for ever unless limited by code.
  //Every process takes some small amount of CPU time.
  //Processes which stop having a use should be killed.
  //Some processes will want to run for ever.
  //Eventually bullets will leave the area they can do anything
  //As such it is worth considering a life span for them
  float Life;

   cBullet(cCameraMatrix4 *MatrixMatch)
   {
		//Create a point object for this object.
		RenderPoint = _CREATE( cPoint );

		//Make this start with the same transalation as the camera.
		RenderPoint -> Copy( MatrixMatch );

		//Give this point a shader to use.
		RenderPoint -> Shader( "BasicProgram" );

		//Give this bullet a life span.
		Life = 100.0;
   };

   void Run()
   {
		//Make the bullet move in the direction it is moving.
		RenderPoint -> AdvanceZ( 0.01 );

		//Reduce the bullets remaining life.
		//Eventually it will have run out of life.
		Life = Life - 0.1;

		//If the bullet has run out of life it should be killed
		if( Life < 0.0 )
		{
			//Kill this bullet.
			_KILL_THIS();

			//As we know this bullet is dying we can kill the point.
			_KILL( RenderPoint );

			//Since RenderPoint is being killed
			//We don't want to use its pointer any more.
			RenderPoint = 0;
		}
   };

   void Stop()
   {
		//If something else killed this bullet RenderPoint is not dead.
		//If this bullet killed itself, RenderPoint is 0.
		//You Should not use a pointer when it is zero.
		if(RenderPoint != 0)
		{
			//Kill RenderPoint.
			_KILL( RenderPoint );

			//Stop Pointing at the cPoint Object.
			RenderPoint = 0;
		}
   };
};

 //Declare a new type of Process cCore.
//A Single instance of this process will be created
// by the engine at the start of the program.
//class cCore : public cProcess
 _PROCESS(cCore)
 {
  public:
	cCore()
	{
	//Load the imf pack with objects for demonstration 3.
	//This contains a renderable spherical mesh called BallModel.
	//This contains a texture called BallTexture.
	//This also contains a shader called TexturingProgram.
	//This also contains a bounce sound called BounceSound.
	//This also contains a second shader called BasicProgram.
	 	_LOAD_FILE( "Demonstration3.imf" );

	//Move the camera back 60 units so it is outside the box and looking at the ball.
		_CAMERA -> Position (0.0 , 0.0 , -60);

	//Create a cBall Object.
	 	_CREATE(cBall);

	};

	void Run()
	{
		//Change the Yaw by the change in the mouse position.
		//Multiply by a small value to slow it down.
			_CAMERA -> RotateY( _MOUSE->XSpeed() * 0.01 );

		//Change the Pitch by the change in the mouse position.
		//Multiply by a small value to slow it down.
			_CAMERA -> RotateZ( _MOUSE->YSpeed() * 0.01 );

		//If the left mouse button is clicked - Fire bullets
		if( _MOUSE -> Left() )
		{
			//Create Our bullets
				_CREATE( cBullet( _CAMERA ) );
		}
	};

	void Stop()
	{

	};


 };
\endcode
* \section CollisionsBouncingBallExample Example with Bullet and Ball collisions.
* Lets add collisions so we can detect collisions between the Ball and the bullets.
* For now we will just kill the ball. We should also limit how fast the bullets can be fired.
*\code

//Declare and Define a process for controlling the ball.
//class cBall : public cBall
 _PROCESS(cBall)
 {
 public:
 //Create pointer so cCore can  access the object it creates.
 cModel *BallPointer;

 //Create a pointer so cCore can play the bounce sound.
 cAudioObject *BallBounce;

 //Create a new Collision Object
 cCollisionObject *BallCollision;

 //Create a variable for each dimension the ball moves in.
 //This could be a c3DVf which is a 3 dimensional vector
 c3DVf BallSpeed;

  //Constructor - Initialisation code.
 	cBall()
	{
		//Note the media will have been loaded in cCore.
		//Since cCore Creates this process media will be loaded before we get to this point.
		//Create a Textured Model to put the ball on screen.
	BallPointer =  _CREATE(cModel);
		//Set the mesh it will use.
	BallPointer -> Mesh( "BallModel" ) );
		//Set the Texture it will use.
	BallPointer -> Texture( _GET_MESH_FILE( "BallTexture" ) );
		//Set the Shader it will use.
	BallPointer -> Shader( _GET_SHADER_FILE( "TexturingProgram" ) );

		//Set a start position.
		//This is relative to the camera.
		// The first value is left and right position of the object.
		// The second value is up and down position of the object.
		// The third value is forwards and backwards.
		// Position it randomly between -20 and +20 on each axis.
	BallPointer -> Position( ZEROED_RANDOM_NUMBER * 20 , ZEROED_RANDOM_NUMBER * 20 , ZEROED_RANDOM_NUMBER * 20 );

		//Create a Collision Object to enable collisions for the Ball.
		//Have it follow the position of the Ball.
		//Have it linked to this process.
	BallCollision = _CREATE( cCollisionObject( BallPointer , this ) );

		//Set Type will set the type of collision. By handing it values it will generate an object at run time.
		//A Single float will make it a sphere of the specified radius.
	BallCollision -> SetType( 1.0 );

		//We also need to set the filter value for the collision. This is important to maintain the speed of collision detection.
		//This means that this collision object will be checked under the value 1.
	BallCollision -> CollisionFilter( 1 );

		//Move the camera back 60 units so it is outside the box and looking at the ball.
	_CAMERA -> Position (0.0 , 0.0 , -60);

		//Set the ball to move in a random direction at 0.1 units per frame
		//RANDOM_NUMBER is a random float between 0.0 and 1.0.
		//Because this is an instance (not a Bamboo engine object) it should be accessed using the dot operator.
	BallSpeed.X( RANDOM_NUMBER * 0.1 );
	BallSpeed.Y( RANDOM_NUMBER * 0.1 );
	BallSpeed.Z( RANDOM_NUMBER * 0.1 );

	//Create an audio file for playing the bounce sound.
	BallBounce = _CREATE(cAudioObject);
	//Create Buffer the sound we want to play into the cAudioObject.
	BallBounce -> Buffer (_GET_AUDIO_FILE( "BallSound" );

	};

	//This is the function that will update the balls position every process cycle.
	void Run()
	{
		//Increase the balls speed downwards by a small amount.
		BallSpeedY = BallSpeedY - 0.01;

			//Advance the Ball by its speed in all three Global axis.
			//If this was a Local axis you would not notice a change until you rotated the ball around.
		BallPointer -> GAdvance( BallSpeed.X() , BallSpeed.Y() , BallSpeed.Z() );

			//If the ball is outside any of the boundaries.
			//There are much more concise ways of doing this but this is the clearest.
			//This is exactly the same as previously, but with 6 boundaries instead of 1.
		if( BallPointer -> X()  < - 30.0  || BallPointer -> X() > 30.0)
		{
			BallSpeed.X( -BallSpeed.X() ) ;
			BallBounce -> Play();
		}
		if( BallPointer -> Y()  < - 30.0  || BallPointer -> Y() > 30.0)
		{
			BallSpeed.Y( -BallSpeed.Y() ) ;
			BallBounce -> Play();
		}
		if( BallPointer -> Z()  < - 30.0  || BallPointer -> Z() > 30.0)
		{
			BallSpeed.Z( -BallSpeed.Z() ) ;
			BallBounce -> Play();
		}

	};

	void Stop()
	{
			//When this dies we want the ball to disappear.
		_KILL(BallPointer);
		_KILL(BallSound);
			//Stop BallPointer pointing at the model as it has been killed.
		BallPointer = 0;
		BallSound = 0;
	};
};


_PROCESS(cBullet)
{
 public:
	//Create a cPoint pointer for accessing the bullet render object.
  cPoint *RenderPoint;

  	//Create a cCollisionObject for bullet collisions.
  cCollisionObject *PointCollision;

   //Variable to stre the remaining lifespan of the bullet
  float Life;

   cBullet(cCameraMatrix4 *MatrixMatch)
   {
		//Create a point object for this object.
		RenderPoint = _CREATE( cPoint );

		//Make this start with the same transalation as the camera.
		RenderPoint -> Copy( MatrixMatch );

		//Give this point a shader to use.
		RenderPoint -> Shader( _GET_SHADER_FILE( "BasicProgram" ) );

		//Create a new collision object for bullet collisions.
		//Have it follow the RenderPoint (Bullet object).
		//Have it linked to this process.
		PointCollision = _CREATE( cCollisionObject( RenderPoint , this ) );

		//This will set the type of collision that this collision will use.
		//This will make a sphere or radius 0.5 units.
		PointCollision -> SetType ( 0.5 );

		//This Collision Filter value is different to the one for cBall.
		//This is so we can differentiate between the different collisions.
		PointCollision -> CollisionFilter( 2 );

		//Give this bullet a life span.
		Life = 100.0;
   };

   void Run()
   {
		//Make the bullet move in the direction it is moving.
		RenderPoint -> AdvanceZ( 0.01 );

		//Reduce the bullets remaining life. Eventually it will have run out of life.
		Life = Life - 0.1;

		//If the bullet has run out of life it should be killed
		if( Life < 0.0 )
		{
			//Kill this bullet.
			_KILL_THIS();

			//As we know thi bullet is dying we can kill the point.
			_KILL( RenderPoint );

			//Since RenderPoint is being killed we should not point at it any more.
			RenderPoint = 0;
		}

		//cProcess Pointer to use in the loop.
		cProcess *CollidingProcess;

		//cCollisionList to access the list of collisions
		cCollisionList *ListOfCollisions;

		//Generate a list of all collisions with this bullet.
		//Only check cCollisionObject s with the filter value 1.
		//I.E. Generate collisions between this bullet and any Balls.
		ListOfCollisions = PointCollision -> GenerateCollisionList( 1 );

		//This will perform this code on every collision with
		//On each loop CollidingProcess will point to
		// the process linked to each colliding object.
		_COLLISION_PROCESS_LOOP( ListOfCollisions, CollidingProcess )
		{
			//A Bullet has hit a ball so kill the ball.
			_KILL(CollidingProcess);
		}

		delete ListOfCollisions;
   };

   void Stop()
   {
			//If something else has killed this bullet then RenderPoint will still be alive.
		if(RenderPoint != 0)
		{
			//Kill RenderPoint.
			_KILL( RenderPoint );

			//Stop Pointing at the cPoint Object.
			RenderPoint = 0;

			//Notice how we do not kill PointCollision.
			//Killing it will not break the program.
			//cCollisionObject's a killed when their cRenderObject is killed.
			//So we do not need to kill PointCollision.
			//They can be killed separatly to their cRenderObject but should be killed first.
		}
   };
};

//Declare a new type of Process cCore.
//A Single instance of this process will be created
// by the engine at the start of the program.
_PROCESS(cCore)
{
public:

		//Create a float to account for reloading time on firing the bullets.
	float Reload;

	cCore()
	{
	//Load the imf pack with objects for demonstration 3.
	//This contains a renderable spherical mesh called BallModel.
	//This contains a texture called BallTexture.
	//This also contains a shader called TexturingProgram.
	//This also contains a bounce sound called BounceSound.
	//This also contains a second shader called BasicProgram.
	 _LOAD_FILE( "Demonstration3.imf" );

	//Move the camera back 60 units so it is outside the box and looking at the ball.
	_CAMERA -> Position (0.0 , 0.0 , -60);

	//Create a cBall (Defined earlier).
	 _CREATE(cBall);

	};

	void Run()
	{
		//Change the Yaw by the change in the mouse position.
		//Multiply by a small value to slow it down.
		_CAMERA -> RotateY( _MOUSE->XSpeed() * 0.01 );

		//Change the Pitch by the change in the mouse position.
		//Multiply by a small value to slow it down.
		_CAMERA -> RotateZ( _MOUSE->YSpeed() * 0.01 );

		//If the gun is not reloaded, do a bit more reloading.
		if( Reload < 10.0 ) { Reload = Reload + 0.11; }

		//If the left mouse button is pressed.
		//AND reloading is completed
		// Fire a bullet and unload the gun.
		if( _MOUSE -> Left() && Reload >= 10.0)
		{
			//Fire a Bullet
			//Give it the cCameraMatrix4.
			_CREATE( cBullet( _CAMERA ) );

			//Tell the gun it is unloaded.
			Reload = 0.0 ;
		}
	};

	void Stop()
	{

	};


 };
\endcode
* \section ReSpwaningBouncingBallExample Example with a continual supply of balls.
* We have collisions. So lets add health to the ball. Once it runs out of health it dies.
* We will also have the balls respawn so you get a new target when you shoot one.
* Finally lets have three balls on the screen at once.
*\code

//Declare and Define a process for controlling the ball.
//class cBall : public cProcess
 _PROCESS(cBall)
 {
 public:

 	//Create pointer so cCore can  access the object it creates.
 cModel *BallPointer;

 	//Create a pointer so cCore can play the bounce sound.
 cAudioObject *BallBounce;

 	//Create a new Collision Object
 cCollisionObject *BallCollision;

 	//Create a variable for each dimension the ball moves in.
 	//This could be a c3DVf which is a 3 dimensional vector
 c3DVf BallSpeed;

 	//Give this Ball a variable to store its health.
 float Health;

  //Constructor - Initialisation code.
 	cBall()
	{
	//Note the media will have been loaded in cCore.
	//Since cCore Creates this process
	//Our media will be loaded before we get to this point.
	//Create a Textured Model to put the ball on screen.
		BallPointer =  _CREATE(cModel);

	//Set the mesh it will use.
		BallPointer -> Mesh( "BallModel" );

	//Set the Texture it will use.
		BallPointer -> Texture( "BallTexture" );

	//Set the Shader it will use.
		BallPointer -> Shader( "TexturingProgram" );

	//Set a start position.
	//This is relative to the global position 0.0 , 0.0 , 0.0
	// Position it randomly between -20 and +20 on each axis.
		BallPointer -> Position( ZEROED_RANDOM_NUMBER * 20 ,
								 ZEROED_RANDOM_NUMBER * 20 ,
								 ZEROED_RANDOM_NUMBER * 20 );

	//Create a Collision Object to enable collisions for the Ball.
	//Have it follow the position of the Ball.
	//Have it linked to this process.
		BallCollision = _CREATE( cCollisionObject( BallPointer , this ) );

	//Set Type will set the type of collision. By handing it values it will generate an object at run time.
	//A Single float will make it a sphere of the specified radius.
		BallCollision -> SetType( 1.0 );

	//We also need to set the filter value for the collision. This is important to maintain the speed of collision detection.
	//This means that this collision object will be checked under the value 1.
		BallCollision -> CollisionFilter( 1 );

	//Move the camera back 60 units so it is outside the box and looking at the ball.
		_CAMERA -> Position (0.0 , 0.0 , -60);

	//Set the ball to move in a random direction at 0.1 units per frame
	//RANDOM_NUMBER is a random float between 0.0 and 1.0.
	//Because this is an instance (not a Bamboo engine object) it should be accessed using the dot operator.
		BallSpeed.X( RANDOM_NUMBER * 0.1 );
		BallSpeed.Y( RANDOM_NUMBER * 0.1 );
		BallSpeed.Z( RANDOM_NUMBER * 0.1 );

	//Create an audio file for playing the bounce sound.
		BallBounce = _CREATE( cAudioObject );

	//Create Buffer the sound we want to play into the cAudioObject.
		BallBounce -> Buffer ( "BallSound" );

	//Set the health to 100 percent.
		Health = 100.0 ;

	};

	//This is the function that will update the balls position every process cycle.
	void Run()
	{
		//Increase the balls speed downwards by a small amount.
			BallSpeedY = BallSpeedY - 0.01;

		//Advance the Ball by its speed in all three Global axis.
		//If this was a Local axis you would not notice a change until you rotated the ball around.
			BallPointer -> GAdvance( BallSpeed.X() , BallSpeed.Y() , BallSpeed.Z() );

		//If the ball is outside any of the boundaries.
		//There are much more concise ways of doing this but this is the clearest.
		//This is exactly the same as previously, but with 6 boundaries instead of 1.
		if( BallPointer -> X()  < - 30.0  || BallPointer -> X() > 30.0)
		{
			BallSpeed.X( -BallSpeed.X() ) ;
			BallBounce -> Play();
		}
		if( BallPointer -> Y()  < - 30.0  || BallPointer -> Y() > 30.0)
		{
			BallSpeed.Y( -BallSpeed.Y() ) ;
			BallBounce -> Play();
		}
		if( BallPointer -> Z()  < - 30.0  || BallPointer -> Z() > 30.0)
		{
			BallSpeed.Z( -BallSpeed.Z() ) ;
			BallBounce -> Play();
		}

	};

	void Stop()
	{
		//When this dies we want the ball to disappear.
			_KILL(BallPointer);
			_KILL(BallSound);

		//Stop BallPointer pointing at the model as it has been killed.
			BallPointer = 0;
			BallSound = 0;
	};

	//This is a Userdefined signal. see cUserSignal.
	//This allows you to send signals and information between cProcess Objects.
	//If you know the process type you can access member variables and functions directly.
	//Using signals allows you to contain an objects code entirely within it.
	void UserSignal( SIGNAL liSignal , void *lpData )
	{
		//if liSignal == 1 it indicates that a bullet has collided with this processes ball.
		//We should take some damage. The amount of damage is passed through lpData.
		if( liSignal == 1 )
		{
			//A bullet has collided.
			//Deduct the Damage from the bullet from the health of the ball.
			float *Damage;
			Damage = lpData;
			Health = Health - Damage[0];

			//If health is less than zero, this ball has died.
			//Kill this ball and create a new one to replace it as a target.
			if( Health < 0 ) { _KILL_THIS(); _CREATE(cBall); }
		}

	};
};

//Create a new process type (class) cBullet.
//This will control a single bullet
//class cBullet : public cProcess
_PROCESS(cBullet)
{
 public:
	//Create a cPoint pointer for accessing the bullet render object.
  cPoint *RenderPoint;

  	//Create a cCollisionObject for bullet collisions.
  cCollisionObject *PointCollision;

   //Variable to stre the remaining lifespan of the bullet
  float Life;

   cBullet(cCameraMatrix4 *MatrixMatch)
   {
		//Create a point object for this object.
			RenderPoint = _CREATE( cPoint );

		//Make this start with the same transalation as the camera.
			RenderPoint -> Copy( MatrixMatch );

		//Give this point a shader to use.
			RenderPoint -> Shader( "BasicProgram" );

		//Create a new collision object for bullet collisions.
		//Have it follow the RenderPoint (Bullet object).
		//Have it linked to this process.
			PointCollision = _CREATE( cCollisionObject( RenderPoint , this ) );

		//This will set the type of collision that this collision will use.
		//This will make a sphere or radius 0.5 units.
			PointCollision -> SetType ( 0.5 );

		//This Collision Filter value is different to the one used for the balls.
		//This is so we can differentiate between the different collisions.
			PointCollision -> CollisionFilter( 2 );

		//Give this bullet a life span.
			Life = 100.0;
   };

   void Run()
   {
		//Make the bullet move in the direction it is moving.
			RenderPoint -> AdvanceZ( 0.01 );

		//Reduce the bullets remaining life. Eventually it will have run out of life.
			Life = Life - 0.1;

		//If the bullet has run out of life it should be killed
		if( Life < 0.0 )
		{
			//Kill this bullet.
				_KILL_THIS();

			//As we know this bullet is dying we can kill the point.
				_KILL( RenderPoint );

			//Since RenderPoint is being killed we should not point at it any more.
				RenderPoint = 0;
		}

		cProcess *CollidingProcess;
		cCollisionList *ListOfCollisions;

		//Generate a list of all collisions between this bullet and Collision Objects.
		//Only cCollisionObject s with the filter value 1 will be checked.
		//I.E. Generate collisions between this bullet and any Balls.
			ListOfCollisions = PointCollision -> GenerateCollisionList( 1 );

			//This will perform this code on every collision with CollidingProcess
			//In each loop CollidingProcess will point to the process linked to the colliding objects.
		_COLLISION_PROCESS_LOOP( ListOfCollisions, CollidingProcess )
		{
				//A Bullet has hit a ball so we signal the ball to say it has been damaged.
			float Damage;

				//Generate a Random amount of damage between 0 and 50.
			Damage = RANDOM_NUMBER * 50;

				//Signal the Ball we collided with to damage it.
			CollidingProcess -> UserSignal( 1 , &Damage );

				This bullet has hit a target so we kill it.
			_KILL_THIS();
		}

		delete ListOfCollisions;
   };

   void Stop()
   {
			//If something else has killed this bullet then RenderPoint will still be alive.
		if(RenderPoint != 0)
		{
				//Kill RenderPoint.
			_KILL( RenderPoint );

				//Stop Pointing at the cPoint Object.
			RenderPoint = 0;

				//Notice how we do not kill PointCollision.
				//Killing it will nto break the program,
				//cCollisionObject s a killed when their cRenderObject is killed.
				//As such we do not need to kill it.
				//They can be killed seperatly to their cRenderObject.
				//A cCollisionObject should be killed before its cRenderObject.
		}
   };
};

//Declare a new type of Process cCore.
//A Single instance of this process will be created
// by the engine at the start of the program.
//class cCore : public cProcess
_PROCESS(cCore)
{
public:

	//Create a float to account for reloading time on firing the bullets.
	float Reload;

	cCore()
	{
	//Load the imf pack with objects for demonstration 3.
	//This contains a renderable spherical mesh called BallModel.
	//This contains a texture called BallTexture.
	//This also contains a shader called TexturingProgram.
	//This also contains a bounce sound called BounceSound.
	//This also contains a second shader for rendering Point Objects BasicProgram.
	 	_LOAD_FILE( "Demonstration3.imf" );

	//Move the camera back 60 units so it is outside the box.
	// The box will now be in front of the camera.
		_CAMERA -> Position (0.0 , 0.0 , -60);

	//Here we create a ball.
	 	_CREATE(cBall);

	//Lets create 2 more so we have three targets
		_CREATE(cBall);
		_CREATE(cBall);

	};

	void Run()
	{
		//Change the Yaw by the change in the mouse position.
		//Multiply by a small value to slow it down.
			_CAMERA -> RotateY( _MOUSE->XSpeed() * 0.01 );

		//Change the Pitch by the change in the mouse position.
		//Multiply by a small value to slow it down.
			_CAMERA -> RotateZ( _MOUSE->YSpeed() * 0.01 );

		//If the gun is not reloaded, do a bit more reloading.
			if( Reload < 10.0 ) { Reload = Reload + 0.11; }

		//If the left mouse button is pressed.
		//AND reloading is completed
		// Fire a bullet and unload the gun.
		if( _MOUSE -> Left() && Reload >= 10.0)
		{
			//Fire a Bullet
				_CREATE(cBullet);

			//Tell the gun it is unloaded.
				Reload = 0.0 ;
		}
	};

	void Stop()
	{

	};


 };
\endcode
* \section CompleteNoCommentsBouncingBallExample Previous Example without comments
* Same Code without comments to show amount of code required to make this simple game.
\code
 _PROCESS(cBall)
 {
 public:


 cModel *BallPointer;
 cAudioObject *BallBounce;
 cCollisionObject *BallCollision;
 c3DVf BallSpeed;
 float Health;

 	cBall()
	{
	BallPointer =  _CREATE(cModel);
	BallPointer -> Mesh( "BallModel" );
	BallPointer -> Texture( "BallTexture" );
	BallPointer -> Shader( "TexturingProgram" );
	BallPointer -> Position( ZEROED_RANDOM_NUMBER * 20 ,
							 ZEROED_RANDOM_NUMBER * 20 ,
							 ZEROED_RANDOM_NUMBER * 20 );

	BallCollision = _CREATE( cCollisionObject( BallPointer , this ) );
	BallCollision -> SetType( 1.0 );
	BallCollision -> CollisionFilter( 1 );

	BallSpeed.X( RANDOM_NUMBER * 0.1 );
	BallSpeed.Y( RANDOM_NUMBER * 0.1 );
	BallSpeed.Z( RANDOM_NUMBER * 0.1 );

	BallBounce = _CREATE(cAudioObject);
	BallBounce -> Buffer ( "BallSound" );

	Health = 100.0 ;
	};

	void Run()
	{
		BallSpeedY = BallSpeedY - 0.01;

		BallPointer -> GAdvance( BallSpeed.X() , BallSpeed.Y() , BallSpeed.Z() );

		if( BallPointer -> X()  < - 30.0  || BallPointer -> X() > 30.0)
		{
			BallSpeed.X( -BallSpeed.X() ) ;
			BallBounce -> Play();
		}
		if( BallPointer -> Y()  < - 30.0  || BallPointer -> Y() > 30.0)
		{
			BallSpeed.Y( -BallSpeed.Y() ) ;
			BallBounce -> Play();
		}
		if( BallPointer -> Z()  < - 30.0  || BallPointer -> Z() > 30.0)
		{
			BallSpeed.Z( -BallSpeed.Z() ) ;
			BallBounce -> Play();
		}

	};

	void Stop()
	{

		_KILL(BallPointer);
		_KILL(BallSound);

		BallPointer = 0;
		BallSound = 0;
	};

	void UserSignal( SIGNAL liSignal , void *lpData )
	{
		if( liSignal == 1 )
		{
			float *Damage;
			Damage = lpData;
			Health = Health - Damage[0];

			if( Health < 0 ) { _KILL_THIS(); _CREATE(cBall); }
		}

	};
};


_PROCESS(cBullet)
{
 public:

  cPoint *RenderPoint;
  cCollisionObject *PointCollision;
  float Life;

   cBullet(cCameraMatrix4 *MatrixMatch)
   {
		RenderPoint = _CREATE( cPoint );
		RenderPoint -> Copy( MatrixMatch );
		RenderPoint -> Shader( "BasicProgram" );

		PointCollision = _CREATE( cCollisionObject( RenderPoint , this ) );
		PointCollision -> SetType ( 0.5 );
		PointCollision -> CollisionFilter( 2 );

		Life = 100.0;
   };

   void Run()
   {

		RenderPoint -> AdvanceZ( 0.01 );
		Life = Life - 0.1;

		if( Life < 0.0 )
		{
			_KILL_THIS();
			_KILL( RenderPoint );
			RenderPoint = 0;
		}

		cProcess *CollidingProcess;
		cCollisionList *ListOfCollisions;

		ListOfCollisions = PointCollision -> GenerateCollisionList( 1 );
		_COLLISION_PROCESS_LOOP( ListOfCollisions, CollidingProcess )
		{
			float Damage;
			Damage = RANDOM_NUMBER * 50;
			CollidingProcess -> UserSignal( 1 , &Damage );
			_KILL_THIS();
		}

		delete ListOfCollisions;
   };

   void Stop()
   {
		if(RenderPoint != 0)
		{
			_KILL( RenderPoint );
			RenderPoint = 0;
		}
   };
};


_PROCESS(cCore)
{
public:

	float Reload;

	cCore()
	{
	 _LOAD_FILE( "Demonstration3.imf" );

	_CAMERA -> Position (0.0 , 0.0 , -60);


    _CREATE(cBall);
	_CREATE(cBall);
	_CREATE(cBall);

	};

	void Run()
	{
		_CAMERA -> RotateY( _MOUSE->XSpeed() * 0.01 );
		_CAMERA -> RotateZ( _MOUSE->YSpeed() * 0.01 );

		if( Reload < 10.0 ) { Reload = Reload + 0.11; }

		if( _MOUSE -> Left() && Reload >= 10.0)
		{
			_CREATE(cBullet);
			Reload = 0.0 ;
		}
	};

	void Stop()
	{

	};

 };
\endcode
* That is less than 200 lines, including spacings and empty lines.
* Probably less than 150 lines of code to make a simple game!
*/

#ifdef _MSC_VER
	typedef __int32 int32_t;
	typedef unsigned __int32 uint32_t;
	typedef __int64 int64_t;
	typedef unsigned __int64 uint64_t;

#else
	#include <stdint.h>
	#include <unistd.h>
#endif



#include "./WTOsBits.h"

#include "./Global/WTKeyStateDefinitions.h"

#if WT_OS_TYPE==OS_WIN32
	#include <windows.h>

    #define GLEW_STATIC 1

	#include <glew.h>
    #include <glext.h>
    #include <wglext.h>
    #include <GL/gl.h>

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
#include "./Global/IMFDefinitions.h"
#include "./Global/WTcFlags.h"


#include <typeinfo>

//#include <GL/gl.h>




#include <cmath>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "./Global/GlobalPointers.h"
#include "./Global/log.h"
#include "./Global/CException.h"
#include "./PTL/WTcSingleton.h"
#include "./PTL/WTRadix.h"
#include "./Windows/WTcSync.h"

#include "./Windows/WTcWindow.h"

#include "./PTL/WTLLTemplate.h"
#include "./PTL/WTMinLinkedList.h"
#include "./PTL/WTLimitedList.h"
#include "./PTL/WTcPushPopStack.h"


#include "./Maths/WTMath.h"
#include "./Maths/WTc2DVt.h"
#include "./Maths/WTc3DVt.h"
#include "./Maths/WTc4DVt.h"
#include "./Maths/WTcColors.h"
#include "./Maths/WTcMatrix4.h"
#include "./Maths/WTcDoubleMatrix4.h"
#include "./Maths/WTcMomentum.h"
#include "./Maths/WTcPerspectiveMatrix.h"
#include "./Maths/WTcMatrixStack.h"
#include "./Maths/WTcCameraMatrix4.h"
#include "./Maths/WTcPredictiveTracking.h"
#include "./Maths/WTcSimplexNoise.h"
#include "./Files/WTString.h"



#include "./Maths/WTc2DVtCode.h"
#include "./Maths/WTc3DVtCode.h"
#include "./Maths/WTc4DVtCode.h"

#include "./Engine/WTcSignal.h"
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

#include "./Physics/WTcCollisionBase.h"
#include "./Files/CollisionMeshes/WTvCollisionData.h"
#include "./Files/CollisionMeshes/WTcSphereCollision.h"
#include "./Files/CollisionMeshes/WTcMeshCollision.h"
#include "./Files/CollisionMeshes/WTcBeamCollision.h"
#include "./Files/CollisionMeshes/WTcRayCollision.h"
#include "./Files/CollisionMeshes/WTcMeshFileCollision.h"
#include "./Files/CollisionMeshes/WTcCompoundCollision.h"
#include "./Files/CollisionMeshes/WTcCompoundCollisionFile.h"
#include "./Files/CollisionMeshes/WTcMouseCollision.h"

#include "./Files/Textures/WTcTexture.h"
#include "./Files/Textures/WTcSeamlessTextureClasses.h"
#include "./Files/Textures/WTcTextureGenerator.h"
#include "./Files/Fonts/WTcFont.h"

#include "./Files/Shaders/WTcShader.h"
#include "./Files/Shaders/WTcShaderVariables.h"
#include "./Files/Shaders/WTcUserDefinedShaderVariable.h"
#include "./Files/Shaders/WTcShaderProgram.h"

#include "./Camera/FX/WTcFog.h"
#include "./Camera/WTcRenderOwner.h"
#include "./Camera/WTvRenderObject.h"
#include "./Files/Meshes/WTcMesh.h"
#include "./Files/Meshes/WTcAsteroid.h"
#include "./Files/Meshes/WTcUVSphere.h"
#include "./Files/Meshes/WTcIcoSphere.h"

#include "./Files/Misc/WTcMeshTreeNode.h"
#include "./Files/Misc/WTvMeshTree.h"
#include "./Files/Misc/WTcMeshTree.h"
#include "./Files/Misc/WTcLineArrayData.h"

#include "./Files/Meshes/WTv2DPolygon.h"

#include "./Physics/WTcCollisionObject.h"

#include "./Camera/WTcTextureStack.h"
#include "./Camera/WTcPerspectiveControl.h"
#include "./Camera/WTcCamera.h"
#include "./Camera/WTcExtraViewport.h"
#include "./Camera/WTcRenderPointer.h"
#include "./Camera/WTcRenderObject.h"

#include "./Physics/WTcMouseCollisionObject.h"

#include "./Camera/Nodes/WTcRenderNode.h"
#include "./Camera/Nodes/WTcNodeList.h"

#include "./Camera/Renderable/WTcAttributeData.h"

#include "./Files/Meshes/WTcmLandscape.h"


     #include "./Camera/FX/WTcMaterial.h"
     #include "./Camera/FX/WTvLight.h"
	 #include "./Camera/WTcLightHandler.h"
         #include "./Camera/FX/WTcLight.h"
         #include "./Camera/FX/WTcSpotLight.h"

         #include "./Camera/Renderable/WTcImage.h"
         #include "./Camera/Renderable/WTcTextureText.h"
         #include "./Camera/Renderable/WTcModel.h"
	 #include "./Camera/Renderable/WTcLandscape.h"
	 #include "./Camera/Renderable/WTcPoint.h"
	 #include "./Camera/Renderable/WTcBillBoard.h"
	 #include "./Camera/Renderable/WTcLine.h"
	 #include "./Camera/Renderable/WTcLineArray.h"
	 #include "./Camera/Renderable/WTcParticleSettings.h"
	 #include "./Camera/Renderable/WTcParticle.h"
	 #include "./Camera/Renderable/WTcParticleGroup.h"
	 #include "./Camera/Renderable/WTcBeamMesh.h"
	 #include "./Camera/Renderable/WTcButton.h"
	 #include "./Camera/Renderable/WTcStarMap.h"

#include "./Camera/WTcPainter.h"

#include "./Windows/EventHandler/WTcKeyStore.h"
#include "./Windows/EventHandler/WTcKeyToggle.h"
#include "./Windows/EventHandler/WTcMouse.h"
#include "./Windows/EventHandler/WTcEventHandler.h"

#include "./Audio/WTcAudioDevice.h"
#include "./Audio/WTcAudioBuffer.h"
#include "./Audio/WTcAudioObject.h"
#include "./Files/Audio/WTcAudioData.h"
#include "./Files/Audio/WTcSoundObject.h"

#include "./Physics/WTcCollisionList.h"
#include "./Physics/WTcCollisionHandler.h"

#include "./Engine/WTcBase.h"



#endif
