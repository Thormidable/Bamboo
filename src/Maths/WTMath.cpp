#include "../WTBamboo.h"



float DegreestoRadians(float lfAngle)
{
 return lfAngle*0.01745329252f;
}

float RadianstoDegrees(float lfAngle)
{
 return lfAngle*57.295779513f;
}


/*
c1DVf::c1DVf(float *lfVect){    v=*lfVect;};
c1DVf::c1DVf(float lfVect){    v=lfVect;};
c1DVf::c1DVf(c1DVf &lfVect){    v=lfVect.v;};
c1DVf::c1DVf(c1DVf *lfVect){    v=lfVect->v;};


c2DVf::c2DVf(c2DVf &lfVect){ memcpy(v,lfVect.v,sizeof(float)*2);};
c2DVf::c2DVf(c2DVf *lfVect){ memcpy(v,lfVect->v,sizeof(float)*2);};


c3DVf::c3DVf(const c3DVf &lfVect){ memcpy(v,lfVect.v,sizeof(float)*3);};
c3DVf::c3DVf(c3DVf *lfVect){ memcpy(v,lfVect->v,sizeof(float)*3);};


c4DVf::c4DVf(c4DVf &lfVect){ memcpy(v,lfVect.v,sizeof(float)*4);};
c4DVf::c4DVf(c4DVf *lfVect){ memcpy(v,lfVect->v,sizeof(float)*4);};

c2DVi::c2DVi(int *liVect){ memcpy(v,liVect,sizeof(int)*2);};
c2DVi::c2DVi(int liX,int liY){ v[0]=liX;v[1]=liY;};
c2DVi::c2DVi(c2DVi &liVect){ memcpy(v,liVect.v,sizeof(int)*2);};
c2DVi::c2DVi(c2DVi *liVect){ memcpy(v,liVect->v,sizeof(int)*2);};

c3DVi::c3DVi(int *liVect){ memcpy(v,liVect,sizeof(int)*3);};
c3DVi::c3DVi(int liX,int liY,int liZ){ v[0]=liX;v[1]=liY;v[2]=liZ;};
c3DVi::c3DVi(c3DVi &liVect){ memcpy(v,liVect.v,sizeof(int)*3);};
c3DVi::c3DVi(c3DVi *liVect){ memcpy(v,liVect->v,sizeof(int)*3);};

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


c3DVf c3DVf::operator*(c3DVf *lvOther)
{
   c3DVf lvReturn;
 lvReturn.v[0]=v[1]*lvOther->v[2]-v[2]*lvOther->v[1];
 lvReturn.v[1]=v[2]*lvOther->v[0]-v[0]*lvOther->v[2];
 lvReturn.v[2]=v[0]*lvOther->v[1]-v[1]*lvOther->v[0];
 return lvReturn;
};
c3DVf c3DVf::operator*(c3DVf &lvOther)
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

c3DVf c3DVf::operator=(c3DVf *lpValue)
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


c3DVf c3DVf::operator+=(c3DVf &lpValue)
{
 v[0]+=lpValue.v[0];
 v[1]+=lpValue.v[1];
 v[2]+=lpValue.v[2];
 return lpValue;
}

c3DVf c3DVf::operator+=(c3DVf *lpValue)
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

c3DVi c3DVi::operator=(c3DVi *lpValue)
{
 memcpy(v,lpValue->v,sizeof(int));
 return *lpValue;
}

c3DVi c3DVi::operator=(c3DVi lpValue)
{
 memcpy(v,lpValue.v,3*sizeof(int));
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
c4DVf &c4DVf::operator=(c4DVf &lpValue)
{
 		memcpy(v,lpValue.v,sizeof(float)*4);
		return *this;

}

float *c4DVf::operator=(float *lpValue)
{
 memcpy(v,lpValue,sizeof(float)*4);
 return lpValue;
}

c4DVf &c4DVf::operator+=(c4DVf &lpValue)
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


c4DVf::c4DVf(float lf0,float lf1,float lf2,float lf3)
{
 v[0]=lf0;
 v[1]=lf1;
 v[2]=lf2;
 v[3]=lf3;
}

c4DVf::c4DVf(float *lf0)
{
    memcpy(v,lf0,sizeof(float)*4);
}

c3DVf::c3DVf(float lf0,float lf1,float lf2)
{
 v[0]=lf0;
 v[1]=lf1;
 v[2]=lf2;
}

c3DVf::c3DVf(float *lf0)
{
    memcpy(v,lf0,sizeof(float)*3);
}


c4DVf *c4DVf::operator=(cRGBA *lpValue)
{
   memcpy(v,lpValue->Color(),sizeof(float)*4);
    return this;
}

c4DVf &c4DVf::operator=(cRGBA &lpValue)
{
   memcpy(v,lpValue.Color(),sizeof(float)*4);
   return *this;
}

c4DVf *c4DVf::operator=(cRGB *lpValue)
{
       memcpy(v,lpValue->Color(),sizeof(float)*3);
       v[3]=1.0f;
    return this;
}
c4DVf &c4DVf::operator=(cRGB &lpValue)
{
       memcpy(v,lpValue.Color(),sizeof(float)*3);
       v[3]=1.0f;
   return *this;

}

c3DVf c3DVf::operator=(cRGB *lpValue)
{
 memcpy(v,lpValue->Color(),sizeof(float)*3);
 return *this;
}

c3DVf c3DVf::operator=(cRGB &lpValue)
{
 memcpy(v,lpValue.Color(),sizeof(float)*3);
 return *this;
}


	float c2DVf::X(){return v[0];};
	float c2DVf::Y(){return v[1];};
	float c3DVf::X(){return v[0];};
	float c3DVf::Y(){return v[1];};
	float c3DVf::Z(){return v[2];};
	float c4DVf::X(){return v[0];};
	float c4DVf::Y(){return v[1];};
	float c4DVf::Z(){return v[2];};
	float c4DVf::W(){return v[3];};

	int c2DVi::X(){return v[0];};
	int c2DVi::Y(){return v[1];};
	int c3DVi::X(){return v[0];};
	int c3DVi::Y(){return v[1];};
	int c3DVi::Z(){return v[2];};


	void c2DVf::X(float lfX){v[0]=lfX;};
	void c2DVf::Y(float lfY){v[1]=lfY;};

	void c3DVf::X(float lfX){v[0]=lfX;};
	void c3DVf::Y(float lfY){v[1]=lfY;};
	void c3DVf::Z(float lfZ){v[2]=lfZ;};

	void c4DVf::X(float lfX){v[0]=lfX;};
	void c4DVf::Y(float lfY){v[1]=lfY;};
	void c4DVf::Z(float lfZ){v[2]=lfZ;};
	void c4DVf::W(float lfW){v[3]=lfW;};
*/
