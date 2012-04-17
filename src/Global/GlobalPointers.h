#ifndef __GLOBALPOINTERS_H__
#define __GLOBALPOINTERS_H__

#if WT_OS_TYPE==OS_WIN32
extern HDC gvHdc;
#endif

class cWindow;
extern cWindow *gpWindow;


class cSync;
extern cSync *gpTimer;


class cProcess;
extern cProcess *gpParent;

#if WT_FULL_VERSION_BAMBOO
	class cElementArray;
	extern cElementArray *gpElementArray;
#endif

#endif




