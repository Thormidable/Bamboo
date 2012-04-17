#ifndef __WTOSBITS_H__
#define __WTOSBITS_H__

/// This will define Windows as the current operating system.
#define OS_WIN32 1
/// This will define Linux as the current operating system.
#define OS_LINUX 2

#define OS_32_BIT 32

#define OS_64_BIT 64

#ifdef __linux
    #define WT_OS_TYPE OS_LINUX
#endif


#ifdef _MSC_VER
    #define WT_OS_TYPE OS_WIN32
    #ifdef __WIN64
        #define WT_OS_BITS OS_64_BIT
    #else
        #define WT_OS_BITS OS_32_BIT
    #endif
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
// #pragma warning comment Base Pointer size undetectable for your archetecture. Needs to be set manually in WTBamboo.h . Library may need recompiling.
#endif

//Manual def of OS Type.
#ifndef WT_OS_TYPE
    #pragma warning (OS Not Detected).
    //#define WT_OS_TYPE OS_LINUX
	#define WT_OS_TYPE OS_WIN32
#endif

//Manual definition of pointer size for Architecture base.
#ifndef WT_OS_BITS
    #pragma warning (OS Bit Base Not Detected).
    #define WT_OS_BITS OS_32_BIT
#endif

#endif
