#ifndef __WTSETTINGS_H__
#define __WTSETTINGS_H__

class cSettings
{

	static void SetupVariables();

public:
	cSettings(){};
	~cSettings(){};
	virtual void Settings(){};

	friend class cBase;
	template<class cX,class cS> friend class cMainThread;
};

///This is the number of cCamera slots created in the cCameraHandler at start. The number of slots will be increased as required, but this involves some overhead.
extern uint8 WT_STARTING_CAMERA_SLOTS;
///This is the number of cViewport slots created in the cViewportHandler at start. The number of slots will be increased as required, but this involves some overhead.
extern uint8 WT_STARTING_VIEWPORT_SLOTS;


///This is the number of Textures which can be linked to any single object. The limit on this is based on teh graphics card. Almost all modern graphics cards support two, though some support up to 8. Keep this to the minimum number required for the shaders being used. If multitexturing is not being used set this to 1.
extern uint8 WT_TEXTURE_NUMBER_ALLOWED;
///This is the number of Items the Painter can hold at start. It will expand as required, but each expansion has a non negligable overhead.
extern uint16 WT_PAINTER_STARTING_SIZE;

///Flag defining the maximum number of levels that the cPushPopStack class will use.
extern uint16 StackDepth;

/// This sets the number of OpenGL Lights to use in Rendering. See cLight().
extern uint16 WT_OPENGL_LIGHTS;

///This will set the type of cCollisionHandler() to use. WT_COLLISION_HANDLER_TYPE_TREE or WT_COLLISION_HANDLER_TYPE_TYPE or WT_COLLISION_HANDLER_TYPE_BSP.
extern uint8 WT_COLLISION_HANDLER_TYPE;
///This will set the default type of cCollisionObject().WT_COLLISION_RADIUS or WT_COLLISION_MODEL or WT_COLLISION_RAY.
extern uint8 WT_COLLISION_DEFAULT_TYPE;

///This is the distance from 360 Degrees which is allowed for a point to be considered within a Polygon.
extern float WT_RAY_ANGLE_RANGE;

/// When true this will generate MipMap data on the fly, allowing changes to the MipMapData after file loading. There is an 'Undocumented feature' on ATI cards that requires this to be enabled to use textures.
extern bool WT_ALLOW_DYNAMIC_TEXTURES;

/// For cCollisionHandler() with type sorting this sets the number of cCollisionObject() Filter values required (and the range they can fall in)
extern uint16 WT_COLLISION_HANDLER_SIZE;
///This is only used by a BSP cCollisionHandlerType. This sets the number of dimensions to use. WT_COLLISION_HANDLER_DIMENSIONS_1D or WT_COLLISION_HANDLER_DIMENSIONS_2D or WT_COLLISION_HANDLER_DIMENSIONS_3D.
extern uint8 WT_COLLISION_HANDLER_DIMENSIONS;
/// This sets the size of one axis of a Spatial Partition box.
extern float WT_COLLISION_SPACE_SIZE;




/// This (I believe) is the number of levels that the collision detector will recurse before giving up and returning back up the scene graph.
extern uint8 WT_COLLISION_DEPTH;




/// The environments Gravity Setting for the X axis. This will only affect cGravityParticles and cMovement.
extern float _GRAVITY_X;
/// The environments Gravity Setting for the Y axis. This will only affect cGravityParticles and cMovement.
extern float _GRAVITY_Y;
/// The environments Gravity Setting for the Z axis. This will only affect cGravityParticles and cMovement.
extern float _GRAVITY_Z;

/// The environments wind Settings for the X axis. This will only affect cMovement.
extern float _WIND_X;
/// The environments wind Settings for the Y axis. This will only affect cMovement.
extern float _WIND_Y;
/// The environments wind Settings for the Z axis. This will only affect cMovement.
extern float _WIND_Z;

extern float _WIND_FACTOR;

///Starting Size of the cParticleHandler Array.
extern uint16 WT_MAX_PARTICLES;

///Whether cParticleHandler will automatically update the particle positions each frame.
extern bool WT_PARTICLE_HANDLER_UPDATE_PARTICLE_POSITIONS;

extern float WT_VERTEX_RANGE_CHECK_SIMILAR;

///This determines whether the engine will automatically track each processes parents and children. 1 is on, 0 is off.
extern bool WT_USE_PARENT_STACK;

extern float WT_LANDSCAPE_TEXTURE_PERCENTAGE_SIZE;

extern uint8 WT_STARTING_FRAMES_PER_SECOND;
extern uint8 WT_STARTING_PROCESSES_PER_FRAME;

extern uint32 WT_COLLISION_HANDLER_ARRAY_SIZE;

extern float WT_COLLISION_SPACE_SIZE_INV;

extern float WT_RAY_ANGLE_UPPER;
extern float WT_RAY_ANGLE_LOWER;

extern float WT_LANDSCAPE_TEXTURE_ACTUAL_SCALE;
extern float WT_LANDSCAPE_TEXTURE_PERCENTAGE_SHIFT;

#endif
