
#include "../../WTBamboo.h"

template<class tD> uint8 cVoxelOctTreeLevelBase<tD>::NodeLayout(){ return LevelBeneathValid; };
template<class tD> bool cVoxelOctTreeLevelBase<tD>::ContainsVoxels(){ return LevelBeneathValid>0; };
template<class tD> bool cVoxelOctTreeLevelBase<tD>::IsDense(){ return LevelBeneathValid==0xFF; };

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

	for (uint16 lItem = 1; lItem < 0xFF; ++lItem)
	{
		c3DVf &lcCur = mfCentre[lItem];
		
		for (uint8 lDim = 0; lDim < 3; ++lDim)
		{
			float32 lfL = static_cast<float32>(HammingWeight::PopCount(static_cast<uint16>(lInvMask[lDim] & lItem)));
			float32 lfU = static_cast<float32>(HammingWeight::PopCount(static_cast<uint16>(lMask[lDim] & lItem)));
			lcCur[lDim] = (0.25f*(lfU - lfL) / (lfU + lfL)) + 0.5f;
		}
	}

	mfCentre[0] = c3DVf(0.5f, 0.5f, 0.5f);
	mfCentre[0xFF] = c3DVf(0.5f, 0.5f, 0.5f);
}
