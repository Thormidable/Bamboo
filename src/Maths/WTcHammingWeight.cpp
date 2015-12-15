
#include "../WTBamboo.h"


#if WT_OS_TYPE == OS_WIN32

#if WT_OS_BITS == OS_64_BIT
	uint8 HammingWeight::PopCount(uint64 x)
	{
		return __popcnt64(x);
	}
	uint8 HammingWeight::PopCountSmallPop(uint64 x)
	{
		return __popcnt64(x);
	}
#endif

	uint8 HammingWeight::PopCount(uint32 x) 
	{
		return __popcnt(x);
	}

	uint8 HammingWeight::PopCount(uint16 x) 
	{
		return __popcnt16(x);
	}


#endif

#if WT_OS_BITS == OS_32_BIT || WT_OS_TYPE == OS_LINUX
uint8 HammingWeight::PopCount(uint64 x)
{
	x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
	x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
	x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
	return (x * h01) >> 56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
}

uint8 HammingWeight::PopCountSmallPop(uint64_t x) {
	int count;
	for (count = 0; x; count++)
		x &= x - 1;
	return count;
}
#endif

#if WT_OS_TYPE == OS_LINUX

	uint8 HammingWeight::PopCount(uint32 x) {
		x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
		x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
		x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
		x += x >> 8;  //put count of each 16 bits into their lowest 8 bits
		x += x >> 16;  //put count of each 32 bits into their lowest 8 bits		
		return x &0x3F;
	}

	uint8 HammingWeight::PopCount(uint16 x) {
		x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
		x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
		x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
		x += x >> 8;  //put count of each 16 bits into their lowest 8 bits
		return x & 0x1f;
	}

#endif

