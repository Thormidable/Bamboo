#include "../WTDivWin.h"
  
double c2DVf::Angle()
{
 return atan2(v[0],v[1]);
}

float c2DVf::Magnitude()
{
 return sqrt(v[0]*v[0]+v[1]*v[1]);
}

float c3DVf::Magnitude()
{
 return sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

void c3DVf::Normalise()
{
 float lfDiv;
 lfDiv=1.0f/Magnitude();
 v[0]=v[0]*lfDiv;
 v[1]=v[1]*lfDiv;
 v[2]=v[2]*lfDiv;
}

c3DVf c3DVf::operator*(c3DVf lvOther)
{
 c3DVf lvReturn;
 lvReturn.v[0]=v[1]*lvOther.v[2]-v[2]*lvOther.v[1];
 lvReturn.v[1]=v[2]*lvOther.v[0]-v[0]*lvOther.v[2];
 lvReturn.v[2]=v[0]*lvOther.v[1]-v[1]*lvOther.v[0];
 return lvReturn;
}

void c2DVf::operator=(c2DVf *lpValue)
{
 memcpy(v,lpValue->v,2*sizeof(float));
}

c3DVf *c3DVf::operator=(c3DVf *lpValue)
{
 memcpy(v,lpValue->v,3*sizeof(float));
 return lpValue;
}

c3DVf c3DVf::operator=(c3DVf lpValue)
{
 memcpy(v,lpValue.v,3*sizeof(float));
 return lpValue;
}

float *c3DVf::operator=(float *lpValue)
{
 memcpy(v,lpValue,3*sizeof(float));
 return lpValue;
}

c3DVf c3DVf::operator+=(c3DVf lpValue)
{
 v[0]+=lpValue.v[0];
 v[1]+=lpValue.v[1];
 v[2]+=lpValue.v[2];
 return lpValue;
}

c3DVf *c3DVf::operator+=(c3DVf *lpValue)
{
 v[0]+=lpValue->v[0];
 v[1]+=lpValue->v[1];
 v[2]+=lpValue->v[2];
 return lpValue;
}

long c2DVi::Angle()
{
 return (long) atan2(v[0],v[1]);
}

int c2DVi::Magnitude()
{
 return (int) sqrt(v[0]*v[0]+v[1]*v[1]);
}

int c3DVi::Magnitude()
{
 return (int) sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

c2DVi *c2DVi::operator=(c2DVi *lpValue)
{
 memcpy(v,lpValue->v,sizeof(int)*2);
 return lpValue;
}

c3DVi *c3DVi::operator=(c3DVi *lpValue)
{
 memcpy(v,lpValue->v,sizeof(int));
 /*
 v[0]=lpValue->v[0];
 v[1]=lpValue->v[1];
 v[2]=lpValue->v[2];*/
 return lpValue;
}

c3DVi c3DVi::operator=(c3DVi lpValue)
{
 memcpy(v,lpValue.v,3*sizeof(int));
 /*v[0]=lpValue.v[0];
 v[1]=lpValue.v[1];
 v[2]=lpValue.v[2];*/
 return lpValue;
}

c3DVi c3DVi::operator*(c3DVi lvOther)
{
 c3DVi lvReturn;
 lvReturn.v[0]=v[1]*lvOther.v[2]-v[2]*lvOther.v[1];
 lvReturn.v[1]=v[2]*lvOther.v[0]-v[0]*lvOther.v[2];
 lvReturn.v[2]=v[0]*lvOther.v[1]-v[1]*lvOther.v[0];
 return lvReturn;
}


float DegreestoRadians(float lfAngle)
{
 return lfAngle*0.01745329252f;
}

float RadianstoDegrees(float lfAngle)
{
 return lfAngle*57.295779513f;
}

float c3DVi::Dot(c3DVi lpValue)
{

	return v[0]*lpValue.v[0]+v[1]*lpValue.v[1]+v[2]*lpValue.v[2];

}


float c3DVf::Dot(c3DVf lpValue)
{
	return v[0]*lpValue.v[0]+v[1]*lpValue.v[1]+v[2]*lpValue.v[2];	
}

c4DVf *c4DVf::operator=(c4DVf *lpValue)
 {
 		memcpy(v,lpValue->v,sizeof(float)*4);
		return lpValue;
}
c4DVf c4DVf::operator=(c4DVf lpValue)
{
 		memcpy(v,lpValue.v,sizeof(float)*4);
		return lpValue;

}

float *c4DVf::operator=(float *lpValue)
{
 memcpy(v,lpValue,sizeof(float)*4);
 return lpValue;
}

c4DVf c4DVf::operator+=(c4DVf lpValue)
{
 v[0]+=lpValue.v[0];
 v[1]+=lpValue.v[1];
 v[2]+=lpValue.v[2];
 v[3]+=lpValue.v[3];
 return *this;
}
c4DVf *c4DVf::operator+=(c4DVf *lpValue)
{
 v[0]+=lpValue->v[0];
 v[1]+=lpValue->v[1];
 v[2]+=lpValue->v[2];
 v[3]+=lpValue->v[3];
 return this;

}

float &c4DVf::operator[](uint32 liPos){return v[liPos];};


	float c1DVf::operator=(float lfFloat){v=lfFloat; return lfFloat;};
	float *c1DVf::operator=(float *lfFloat){v=lfFloat[0]; return lfFloat;};
	c1DVf c1DVf::operator=(c1DVf Other){v=Other.v; return Other;};
	c1DVf *c1DVf::operator=(c1DVf *Other){v=Other->v; return Other;};

	float c1DVf::operator/(float lfFloat){return v/lfFloat;};
	float c1DVf::operator/(c1DVf Other){return v/Other.v;};

	float c1DVf::operator-(float lfFloat){return v-lfFloat;};
	float c1DVf::operator-(c1DVf Other){return v-Other.v;};

	float c1DVf::operator*(float lfFloat){return v*lfFloat;};
	float c1DVf::operator*(c1DVf Other){return v*Other.v;};

	float c1DVf::operator+(float lfFloat){return v+lfFloat;};
	float c1DVf::operator+(c1DVf Other){return v+Other.v;};

	void c1DVf::Normalise(){v=1.0f;};

	float c1DVf::Magnatude(){return v;};
	
