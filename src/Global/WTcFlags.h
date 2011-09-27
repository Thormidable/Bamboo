#ifndef __WTCFLAGS_H__
#define __WTCFLAGS_H__

#define DW_TEXTURED_OBJECT 0x1
#define DW_LIT_OBJECT 0x2

//these apply to process'
/// Signal passed by cProcess::Signal() telling the recieving cProcess object to remain in the cProcess list held by cKernel, but to stop processing code until further notice.
#define S_SLEEP 0
/// Signal passed by cProcess::Signal() telling the recieving cProcess object to start processing its code every frame. Works whether cProcess is S_SLEEP or S_AWAKE.
#define S_AWAKE 1

//these apply to renderables.
/// Signal passed by cRenderObject::Signal() telling the recieving cRenderObject to Remain in memory, but stop rendering to the screen every frame.
#define S_HIDE 0
/// Signal passed by cRenderObject::Signal() telling the recieving cRenderObject to start rendering every frme. Works whether cRenderObject is S_HIDE or S_SHOW.
#define S_SHOW 1

#endif
