#include "../WTDivWin.h"

cFrameRate *cFrameRate::mpInstance=0;

cFrameRate *cFrameRate::Instance()
{
	if(!mpInstance) mpInstance=new cFrameRate; return mpInstance;
	
};

cFrameRate::cFrameRate()
{
  giProcessesPerFrame=WT_STARTING_PROCESSES_PER_FRAME;
  giFramesPerSecond=WT_STARTING_FRAMES_PER_SECOND;
  giInvFramesPerSecond=1.0f/giFramesPerSecond;
  giInvProcesesPerSecond=giInvFramesPerSecond/giProcessesPerFrame;
};

void cFrameRate::SetFrameRate(uint8 lfFramesPerSecond){giFramesPerSecond=lfFramesPerSecond;giInvFramesPerSecond=1.0f/giFramesPerSecond; giInvProcesesPerSecond=giInvFramesPerSecond/giProcessesPerFrame;};
void cFrameRate::SetProcessesPerFrame(uint8 liPPS){giProcessesPerFrame=liPPS; giInvProcesesPerSecond=giInvFramesPerSecond/giProcessesPerFrame;};
float cFrameRate::FrameTime(){return giInvFramesPerSecond;};
float cFrameRate::ProcessTime(){return giInvProcesesPerSecond;};
uint8 cFrameRate::FramesPerSecond(){return giFramesPerSecond;};
uint8 cFrameRate::ProcessesPerFrame(){return giProcessesPerFrame;};
