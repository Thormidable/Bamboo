#ifndef __WTCFRAMERATE_H__
#define __WTCFRAMERATE_H__
/** \brief This class will store data for controlling the Frame Rate.
 *   There are several settings that can be adjusted:
 *  - Processes Per Frame
 *  - Frames Per Second
 *  - Frame Time and Process Time
 *  .
 *  These are the amount of time that passes every Frame and Process Cycle measured in seconds. Multiplying any distances moved by this will convert them into distance per second.
 * This allows the user to change the running frame rate without affecting the speed the user experiences. If the Frame rate and Process Rate are not going to be changed this can be ignored.
 */
class cFrameRate
{

static uint8 giProcessesPerFrame;
static uint8 giFramesPerSecond;
static float giInvFramesPerSecond;
static float giInvProcesesPerSecond;
static int8 giSyncingDelay;
cFrameRate();
public:
    static void Initialise();
	///This is the number of Frames that will be rendered each second. This results in smooth consistent timings for every Process Cycle and Rendered Frame. This is best set to 60 / 70 though in extreme cases it can be set to 30. Rendering is very compoutationally expensive, so should be maintained at the lowest rate to produce a smooth visual image.
	static void SetFrameRate(uint8 lfFramesPerSecond);
	/// This is the number of times the Process cycle will be run for every rendered frame. Rendering is very slow and CPU intensive compared to the Procesing cycle. The Human eye cannot differentiate between very fast rendering rates, but increased numbers of processing cycles will increase accuracy of collisions and make events smoother.
	static void SetProcessesPerFrame(uint8 liPPS);
	/// this will return the amount of time that passes for every rendered frame.
	static float FrameTime();
	/// This is the amount of time that passes every Process Cycle measured in seconds. Multiplying any distances moved by this will convert them into distance per second. This allows the user to change the running frame rate without affecting the speed the user experiences. If the Frame rate and Process Rate are not going to be changed this can be ignored.
	static float ProcessTime();
	/// This will return the current set number of Frames per Second.
	static uint8 FramesPerSecond();
	/// This will return the current set number of Process Cycles per Rendered Frame.
	static uint8 ProcessesPerFrame();

};


#endif
