
#include "../../WTBamboo.h"


const uint8 cVoxelBaseFunctions::lNodeMask[8] = { 1, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7 };

template<class tD> bool cVoxelOctTreeLevelBase<tD>::ContainsVoxels(){ return !IsEmpty(); };
template<class tD> bool cVoxelOctTreeLevelBase<tD>::ParitallyFull(){ return !IsEmpty() && !IsDense(); };
template<class tD> bool cVoxelOctTreeLevelBase<tD>::IsDense(){ return LevelBeneathValid == 0xFF; };
template<class tD> bool cVoxelOctTreeLevelBase<tD>::IsEmpty(){ return LevelBeneathValid == 0; };
template<class tD> bool cVoxelOctTreeLevelBase<tD>::ShouldSkip(VoxelSkip lSkip)
{
	if (LevelBeneathValid == 0)
	{
		if (lSkip&VoxelSkipFlags::EMPTY) return true;
		else return false;
	}
	if (LevelBeneathValid == 0xFF)
	{
		if (lSkip&VoxelSkipFlags::DENSE) return true;
		else return false;
	}
	if(lSkip&VoxelSkipFlags::PARTIAL) return true;
	return false;
};

template class cVoxelOctTreeLevelBase<uint8>;

VoxelBlockCentreOfMass::VoxelBlockCentreOfMass()
{
	uint16 lMask[3];
	lMask[0] = GetXBitMask();
	lMask[1] = GetYBitMask();
	lMask[2] = GetZBitMask();

	uint16 lInvMask[3];
	lInvMask[0] = GetInvXBitMask();
	lInvMask[1] = GetInvYBitMask();
	lInvMask[2] = GetInvZBitMask();

	uint8 lDimPow[3];
	lDimPow[0] = 1;
	lDimPow[1] = 2;
	lDimPow[2] = 4;

	for (uint16 lItem = 1; lItem < 0xFF; ++lItem)
	{	
		c3DVf &lcCur = mfCentre[lItem];
		
		for (uint8 lDim = 0; lDim < 3; ++lDim)
		{
			uint16 lL = HammingWeight::PopCount(static_cast<uint16>(lInvMask[lDim] & lItem));
			uint16 lU = HammingWeight::PopCount(static_cast<uint16>(lMask[lDim] & lItem));
			float32 lfL = static_cast<float32>(lL);
			float32 lfU = static_cast<float32>(lU);
			lcCur[lDim] = (0.25f*(lfU - lfL) / (lfU + lfL)) + 0.5f;

			if (lL < 4 && lL >0) mSurroundingConnections[lItem] += lDimPow[lDim];
			if (lU < 4 && lU >0) mSurroundingConnections[lItem] += lDimPow[lDim]+8;
		}
	}

	mfCentre[0] = c3DVf(0.5f, 0.5f, 0.5f);
	mfCentre[0xFF] = c3DVf(0.5f, 0.5f, 0.5f);
	mSurroundingConnections[0] = 0;
	mSurroundingConnections[0xFF] = 0;
}
