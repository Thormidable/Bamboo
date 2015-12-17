
#pragma once

enum VoxelSkipFlags : uint8
{
	NONE = 0,
	EMPTY = 1,
	DENSE = 2,
	PARTIAL = 4
};

typedef uint8 VoxelSkip;

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
	static inline bool GetXFromNodeID(uint8 lNodeID){return (lNodeID&0x4)>0;}
	static inline bool GetYFromNodeID(uint8 lNodeID){ return (lNodeID&0x2)>0; }
	static inline bool GetZFromNodeID(uint8 lNodeID){return (lNodeID&0x1)>0;}
	
	static inline uint8 GetXBitMask (){ return 0xF0;}
	static inline uint8 GetYBitMask (){ return 0xCC;}
	static inline uint8 GetZBitMask (){ return 0x55;}
	static inline uint8 GetInvXBitMask(){ return ~GetXBitMask(); }
	static inline uint8 GetInvYBitMask(){ return ~GetYBitMask(); }
	static inline uint8 GetInvZBitMask(){ return ~GetZBitMask(); }
	static const uint8 lNodeMask[8];

	static void DisplayNodeLayout(uint8 lNodeLayout)
	{
		// X = 1, Y = 1, Z = 0 
		if (lNodeLayout & lNodeMask[0x6]) cout << "x"; else cout << "O";
		cout << "\n / \\ \n";
		// X = 0, Y = 1, Z = 0 
		if (lNodeLayout & lNodeMask[0x2]) cout << "x"; else cout << "O";
		cout << "   ";
		// X = 1, Y = 1, Z = 1 
		if (lNodeLayout & lNodeMask[0x7]) cout << ("x"); else cout << ("O");
		cout << ("\n|\\ /|\n");
		// X = 0, Y = 1, Z = 1 
		if (lNodeLayout & lNodeMask[0x3]) cout << ("x"); else cout << ("O");
		cout << ("\n| | |\n");
		// X = 1, Y = 0, Z = 0 
		if (lNodeLayout & lNodeMask[04]) cout << ("x"); else cout << ("O");
		cout << ("\n / \\ \n");
		// X = 0, Y = 0, Z = 0 
		if (lNodeLayout & lNodeMask[0x0]) cout << ("x"); else cout << ("O");
		cout << ("   ");
		// X = 1, Y = 0, Z = 1 
		if (lNodeLayout & lNodeMask[0x5]) cout << ("x"); else cout << ("O");
		cout << ("\n|\\ /|\n");
		// X = 0, Y = 0, Z = 1 
		if (lNodeLayout & lNodeMask[0x1]) cout << ("x"); else cout << ("O");
	}
};

template<class tD> class cVoxelOctTreeLevelBase
{
protected:
	uint8 LevelBeneathValid;
public:
	bool ContainsVoxels();
	bool ParitallyFull();
	bool IsDense();
	bool IsEmpty();
	bool ShouldSkip(VoxelSkip lSkip);
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
	uint8 mSurroundingConnections[0x100];
	c3DVf mfCentre[0x100];
	friend class cSingleton<VoxelBlockCentreOfMass>;
protected:
	VoxelBlockCentreOfMass();

	
};

