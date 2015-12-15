
#include "../WTBamboo.h"


#if WT_OS_TYPE == OS_WIN32

#if WT_OS_BITS == OS_64_BIT
	uint8 HammingWeight::PopCount(uint64 x)
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
		return __popcnt16(x)
	}

	uint8 HammingWeight::PopCountSmallPop(uint64 x) 
	{
		return __popcnt64(x);
	}
#endif

#if WT_OS_BITS == OS_64_BIT || WT_OS_TYPE == OS_LINUX
uint8 HammingWeight::PopCount(uint64 x)
{
	x -= (x >> 1) & m1;             //put count of each 2 bits into those 2 bits
	x = (x & m2) + ((x >> 2) & m2); //put count of each 4 bits into those 4 bits 
	x = (x + (x >> 4)) & m4;        //put count of each 8 bits into those 8 bits 
	return (x * h01) >> 56;  //returns left 8 bits of x + (x<<8) + (x<<16) + (x<<24) + ... 
}
#endif

#if WT_OS_TYPE == OS_LINUX
	const uint64_t m1 = 0x5555555555555555; //binary: 0101...
	const uint64_t m2 = 0x3333333333333333; //binary: 00110011..
	const uint64_t m4 = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
	const uint64_t m8 = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
	const uint64_t m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
	const uint64_t m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones
	const uint64_t hff = 0xffffffffffffffff; //binary: all ones
	const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...

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

	uint8 HammingWeight::PopCountSmallPop(uint64_t x) {
		int count;
		for (count = 0; x; count++)
			x &= x - 1;
		return count;
	}
#endif

