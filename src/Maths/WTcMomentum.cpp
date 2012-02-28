#include "../WTBamboo.h"

cMomentum::cMomentum(cMatrix4 *lpMatrix)
{
	mpMatrix=lpMatrix;
	memset(mfMomentum,0,sizeof(float)*6);
};

void cMomentum::ThrustX(float lfThrust)
{
 mfMomentum[0]+=lfThrust*mpMatrix->Xx();
 mfMomentum[1]+=lfThrust*mpMatrix->Xy();
 mfMomentum[2]+=lfThrust*mpMatrix->Xz();
};
void cMomentum::ThrustY(float lfThrust)
{
 mfMomentum[0]+=lfThrust*mpMatrix->Yx();
 mfMomentum[1]+=lfThrust*mpMatrix->Yy();
 mfMomentum[2]+=lfThrust*mpMatrix->Yz();
};
void cMomentum::ThrustZ(float lfThrust)
{
 mfMomentum[0]+=lfThrust*mpMatrix->Zx();
 mfMomentum[1]+=lfThrust*mpMatrix->Zy();
 mfMomentum[2]+=lfThrust*mpMatrix->Zz();
};

void cMomentum::GThrustX(float lfThrust)
{
 mfMomentum[0]+=lfThrust;
};
void cMomentum::GThrustY(float lfThrust)
{
 mfMomentum[1]+=lfThrust;
};
void cMomentum::GThrustZ(float lfThrust)
{
 mfMomentum[2]+=lfThrust;
};


void cMomentum::ThrustAngleX(float lfThrust)
{
 mfMomentum[3]+=lfThrust*mpMatrix->Xx();
 mfMomentum[4]+=lfThrust*mpMatrix->Xy();
 mfMomentum[5]+=lfThrust*mpMatrix->Xz();
};
void cMomentum::ThrustAngleY(float lfThrust)
{
 mfMomentum[3]+=lfThrust*mpMatrix->Yx();
 mfMomentum[4]+=lfThrust*mpMatrix->Yy();
 mfMomentum[5]+=lfThrust*mpMatrix->Yz();
};
void cMomentum::ThrustAngleZ(float lfThrust)
{
 mfMomentum[3]+=lfThrust*mpMatrix->Zx();
 mfMomentum[4]+=lfThrust*mpMatrix->Zy();
 mfMomentum[5]+=lfThrust*mpMatrix->Zz();
};

void cMomentum::GThrustAngleX(float lfThrust)
{
 mfMomentum[3]+=lfThrust;
};

void cMomentum::GThrustAngleY(float lfThrust)
{
 mfMomentum[4]+=lfThrust;
};

void cMomentum::GThrustAngleZ(float lfThrust)
{
 mfMomentum[5]+=lfThrust;
};

void cMomentum::Update()
{
	mpMatrix->GAdvance(mfMomentum[0]*0.001,mfMomentum[1]*0.001,mfMomentum[2]*0.001);
	mpMatrix->GRotateX(mfMomentum[3]*0.001);
	mpMatrix->GRotateY(mfMomentum[4]*0.001);
	mpMatrix->GRotateZ(mfMomentum[5]*0.001);
};

void cMomentum::DampenMomentum(float lfValue)
{
	mfMomentum[0]*=lfValue;
	mfMomentum[1]*=lfValue;
	mfMomentum[2]*=lfValue;
	mfMomentum[3]*=lfValue;
	mfMomentum[4]*=lfValue;
	mfMomentum[5]*=lfValue;
}
void cMomentum::DampenLinear(float lfValue)
{
	mfMomentum[0]*=lfValue;
	mfMomentum[1]*=lfValue;
	mfMomentum[2]*=lfValue;
}

void cMomentum::DampenAngular(float lfValue)
{
	mfMomentum[3]*=lfValue;
	mfMomentum[4]*=lfValue;
	mfMomentum[5]*=lfValue;
}

void cMomentum::Straighten(float lfThrust)
{


}

void cMomentum::Stabilise(float lfThrust)
{
 if(abs(mfMomentum[3])>lfThrust)
 {
	if(mfMomentum[3]>0.0f) mfMomentum[3]-=lfThrust;
	else mfMomentum[3]+=lfThrust;
 }
 else mfMomentum[3]=0.0f;

if(abs(mfMomentum[4])>lfThrust)
 {
	if(mfMomentum[4]>0.0f) mfMomentum[4]-=lfThrust;
	else mfMomentum[4]+=lfThrust;
 }
else mfMomentum[4]=0.0f;

if(abs(mfMomentum[5])>lfThrust)
 {
	if(mfMomentum[5]>0.0f) mfMomentum[3]-=lfThrust;
	else mfMomentum[5]+=lfThrust;
 }
 else mfMomentum[5]=0.0f;

}


c3DVf cMomentum::MomentumVector()
{
   return mfMomentum;
}

c3DVf cMomentum::RotationVector()
{
    return &mfMomentum[3];
}
