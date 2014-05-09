#include "stdafx.h"
#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

float cParticleSettings::sfStore[6];

	cParticleSettings &cParticleSettings::operator=(cParticleSettings &lpOther)
	{
		memcpy(RGB,lpOther.RGB,sizeof(float)*8);
		memcpy(Position,lpOther.Position,sizeof(float)*6);
		memcpy(Speed,lpOther.Speed,sizeof(float)*5);
		memcpy(Size,lpOther.Size,sizeof(float)*2);
		memcpy(Life,lpOther.Life,sizeof(float)*2);
		return this[0];
	};

	void cParticleSettings::SetColours(float *lpRGB){memcpy(RGB,lpRGB,sizeof(float)*8);};
	void cParticleSettings::SetSizes(float *lpSize){memcpy(Size,lpSize,sizeof(float)*2);};
	void cParticleSettings::SetLife(float *lpLife){memcpy(Life,lpLife,sizeof(float)*2);};
	void cParticleSettings::SetSpeeds(float *lpSpeed){memcpy(Speed,lpSpeed,sizeof(float)*5);};
	void cParticleSettings::SetPositions(float *lpPos){memcpy(Position,lpPos,sizeof(float)*6);};



#endif
