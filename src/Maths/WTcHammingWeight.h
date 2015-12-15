
#pragma once

class HammingWeight
{
public:

	static uint8 PopCount(uint64 x);
	static uint8 PopCount(uint32 x);
	static uint8 PopCount(uint16 x);
	static uint8 PopCountSmallPop(uint64 x);

#if WT_OS_TYPE == OS_LINUX
	const uint64_t m1 = 0x5555555555555555; //binary: 0101...
	const uint64_t m2 = 0x3333333333333333; //binary: 00110011..
	const uint64_t m4 = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
	const uint64_t m8 = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
	const uint64_t m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
	const uint64_t m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones
	const uint64_t hff = 0xffffffffffffffff; //binary: all ones
	const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...
#endif
};
