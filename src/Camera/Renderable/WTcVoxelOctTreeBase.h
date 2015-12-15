
#pragma once

class cVoxelBaseFunctions
{
public:

	static inline uint8 GetNodeID(bool lX, bool lY, bool lZ)
	{
		uint8 lReturn = 0;
		if (lX) lReturn += 4;
		if (lY) lReturn += 2;
		if (lZ) lReturn += 1;
		return lReturn;
	}
	static inline bool GetXFromNodeID(uint8 lNodeID){return lNodeID&0x4;}
	static inline bool GetYFromNodeID(uint8 lNodeID){ return lNodeID&0x2; }
	static inline bool GetZFromNodeID(uint8 lNodeID){return lNodeID&0x1;}


	static inline uint8 GetXBitMask (){ return 0xF0;}
	static inline uint8 GetYBitMask (){ return 0xCC;}
	static inline uint8 GetZBitMask (){ return 0x55;}
	static inline uint8 GetInvXBitMask(){ return ~GetXBitMask(); }
	static inline uint8 GetInvYBitMask(){ return ~GetYBitMask(); }
	static inline uint8 GetInvZBitMask(){ return ~GetZBitMask(); }
};

template<class tD> class cVoxelOctTreeLevelBase
{
protected:
	uint8 LevelBeneathValid;
public:
	uint8 NodeLayout();
	bool ContainsVoxels();
	bool IsDense();
};

template<class tD> class cVoxelIteratorTypes
{
public:
	typedef void(*LevelIterator)(cVoxelOctTreeLevelBase<tD> *);
	typedef bool(*CollisionCheckFunction)(cVoxelOctTreeLevelBase<tD> *);
	typedef void(*NodeIterator)(tD &);
};

class VoxelBlockCentreOfMass : public cSingleton<VoxelBlockCentreOfMass>, public cVoxelBaseFunctions
{
public:
	c3DVf mfCentre[0x100];
	
	friend class cSingleton<VoxelBlockCentreOfMass>;
protected:
	VoxelBlockCentreOfMass();

	
};

