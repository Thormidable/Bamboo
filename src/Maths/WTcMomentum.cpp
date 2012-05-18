#include "../WTBamboo.h"

	#if WT_FULL_VERSION_BAMBOO
cMomentum::cMomentum(cMatrix4 *lpMatrix)
{
	mpMatrix=lpMatrix;
	memset(mfMomentum,0,sizeof(float)*6);
};



	void cMomentum::Thrust(c3DVf lfVect){ThrustX(lfVect[0]); ThrustY(lfVect[1]); ThrustZ(lfVect[2]); };
	void cMomentum::Thrust(float *lfVect){ThrustX(lfVect[0]); ThrustY(lfVect[1]); ThrustZ(lfVect[2]); };
	void cMomentum::Thrust(float lfX,float lfY,float lfZ){ThrustX(lfX); ThrustY(lfY); ThrustZ(lfZ); };

	void cMomentum::GThrust(c3DVf lfVect){GThrustX(lfVect[0]); GThrustY(lfVect[1]); GThrustZ(lfVect[2]); };
	void cMomentum::GThrust(float *lfVect){GThrustX(lfVect[0]); GThrustY(lfVect[1]); GThrustZ(lfVect[2]); };
	void cMomentum::GThrust(float lfX,float lfY,float lfZ){GThrustX(lfX); GThrustY(lfY); GThrustZ(lfZ); };

	void cMomentum::ThrustAngle(c3DVf lfVect){ThrustAngleX(lfVect[0]); ThrustAngleY(lfVect[1]); ThrustAngleZ(lfVect[2]); };
	void cMomentum::ThrustAngle(float *lfVect){ThrustAngleX(lfVect[0]); ThrustAngleY(lfVect[1]); ThrustAngleZ(lfVect[2]); };
	void cMomentum::ThrustAngle(float lfX,float lfY,float lfZ){ThrustAngleX(lfX); ThrustAngleY(lfY); ThrustAngleZ(lfZ); };

	void cMomentum::GThrustAngle(c3DVf lfVect){GThrustAngleX(lfVect[0]); GThrustAngleY(lfVect[1]); GThrustAngleZ(lfVect[2]); };
	void cMomentum::GThrustAngle(float *lfVect){GThrustAngleX(lfVect[0]); GThrustAngleY(lfVect[1]); GThrustAngleZ(lfVect[2]); };
	void cMomentum::GThrustAngle(float lfX,float lfY,float lfZ){GThrustAngleX(lfX); GThrustAngleY(lfY); GThrustAngleZ(lfZ); };


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
	mpMatrix->GRotateX(mfMomentum[3]*0.00001);
	mpMatrix->GRotateY(mfMomentum[4]*0.00001);
	mpMatrix->GRotateZ(mfMomentum[5]*0.00001);
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

void cMomentum::StraightenX(float lfThrust)
{

	ThrustX(ClampValue(-(mfMomentum[0]*mpMatrix->Xx()+mfMomentum[1]*mpMatrix->Xy()+mfMomentum[2]*mpMatrix->Xz()),lfThrust));
}

void cMomentum::StraightenY(float lfThrust)
{

	ThrustY(ClampValue(-(mfMomentum[0]*mpMatrix->Yx()+mfMomentum[1]*mpMatrix->Yy()+mfMomentum[2]*mpMatrix->Yz()),lfThrust));
}

void cMomentum::StraightenZ(float lfThrust)
{
	ThrustZ(ClampValue(-(mfMomentum[0]*mpMatrix->Zx()+mfMomentum[1]*mpMatrix->Zy()+mfMomentum[2]*mpMatrix->Zz()),lfThrust));
};

void cMomentum::Straighten(float lfThrust)
{

	ThrustX(ClampValue(-(mfMomentum[0]*mpMatrix->Xx()+mfMomentum[1]*mpMatrix->Xy()+mfMomentum[2]*mpMatrix->Xz()),lfThrust));
	ThrustY(ClampValue(-(mfMomentum[0]*mpMatrix->Yx()+mfMomentum[1]*mpMatrix->Yy()+mfMomentum[2]*mpMatrix->Yz()),lfThrust));
}

void cMomentum::Stabilise(float lfThrust)
{
 if(fabs(mfMomentum[3])>lfThrust)
 {
	if(mfMomentum[3]>0.0f) mfMomentum[3]-=lfThrust;
	else mfMomentum[3]+=lfThrust;
 }
 else mfMomentum[3]=0.0f;

if(fabs(mfMomentum[4])>lfThrust)
 {
	if(mfMomentum[4]>0.0f) mfMomentum[4]-=lfThrust;
	else mfMomentum[4]+=lfThrust;
 }
else mfMomentum[4]=0.0f;

if(fabs(mfMomentum[5])>lfThrust)
 {
	if(mfMomentum[5]>0.0f) mfMomentum[3]-=lfThrust;
	else mfMomentum[5]+=lfThrust;
 }
 else mfMomentum[5]=0.0f;

}


void cMomentum::StabiliseX(float lfThrust)
{
 if(fabs(mfMomentum[3])>lfThrust)
 {
	if(mfMomentum[3]>0.0f) mfMomentum[3]-=lfThrust;
	else mfMomentum[3]+=lfThrust;
 }
 else mfMomentum[3]=0.0f;


}

void cMomentum::StabiliseY(float lfThrust)
{


if(fabs(mfMomentum[4])>lfThrust)
 {
	if(mfMomentum[4]>0.0f) mfMomentum[4]-=lfThrust;
	else mfMomentum[4]+=lfThrust;
 }
else mfMomentum[4]=0.0f;


}

void cMomentum::StabiliseZ(float lfThrust)
{
if(fabs(mfMomentum[5])>lfThrust)
 {
	if(mfMomentum[5]>0.0f) mfMomentum[3]-=lfThrust;
	else mfMomentum[5]+=lfThrust;
 }
 else mfMomentum[5]=0.0f;

}

c3DVf cMomentum::GMomentumVector()
{
   return c3DVf(mfMomentum);
}

c3DVf cMomentum::RotationVector()
{
    return c3DVf(&mfMomentum[3]);
}

void cMomentum::LimitSpeedX(float lfLimit)
{
 float lfTemp=mfMomentum[0]*mpMatrix->Xx()+mfMomentum[1]*mpMatrix->Xy()+mfMomentum[2]*mpMatrix->Xz();
 if(lfTemp>lfLimit) lfTemp=lfTemp-lfLimit;
 else
 {
     if(lfTemp<-lfTemp) lfTemp=lfTemp+lfLimit;
     else return;
 }
    mfMomentum[0]-=lfTemp*mpMatrix->Xx();
 	mfMomentum[1]-=lfTemp*mpMatrix->Xy();
 	mfMomentum[2]-=lfTemp*mpMatrix->Xz();
}

void cMomentum::LimitSpeedY(float lfLimit)
{
 float lfTemp=mfMomentum[0]*mpMatrix->Yx()+mfMomentum[1]*mpMatrix->Yy()+mfMomentum[2]*mpMatrix->Yz();
 if(lfTemp>lfLimit) lfTemp=lfTemp-lfLimit;
 else
 {
     if(lfTemp<-lfTemp) lfTemp=lfTemp+lfLimit;
     else return;
 }
    mfMomentum[0]-=lfTemp*mpMatrix->Yx();
 	mfMomentum[1]-=lfTemp*mpMatrix->Yy();
 	mfMomentum[2]-=lfTemp*mpMatrix->Yz();
}

void cMomentum::LimitSpeedZ(float lfLimit)
{
 float lfTemp=mfMomentum[0]*mpMatrix->Zx()+mfMomentum[1]*mpMatrix->Zy()+mfMomentum[2]*mpMatrix->Zz();
 if(lfTemp>lfLimit) lfTemp=lfTemp-lfLimit;
 else
 {
     if(lfTemp<-lfTemp) lfTemp=lfTemp+lfLimit;
     else return;
 }
    mfMomentum[0]-=lfTemp*mpMatrix->Zx();
 	mfMomentum[1]-=lfTemp*mpMatrix->Zy();
 	mfMomentum[2]-=lfTemp*mpMatrix->Zz();
}

void cMomentum::LimitSpeeds(c3DVf lfVect)
{

 c3DVf lmTemp;
 float lfTemp=mfMomentum[0]*mpMatrix->Xx()+mfMomentum[1]*mpMatrix->Xy()+mfMomentum[2]*mpMatrix->Xz();
 if(!(lfTemp<lfVect[0] && lfTemp>-lfVect[0]))
 {
	if(lfTemp<0.0f) lfVect[0]=-lfVect[0];
 }
 else lfVect[0]=lfTemp;

 lfTemp=mfMomentum[0]*mpMatrix->Yx()+mfMomentum[1]*mpMatrix->Yy()+mfMomentum[2]*mpMatrix->Yz();
 if(!(lfTemp<lfVect[1] && lfTemp>-lfVect[1]))
 {
	if(lfTemp<0.0f) lfVect[1]=-lfVect[1];
 }
 else lfVect[1]=lfTemp;

 lfTemp=mfMomentum[0]*mpMatrix->Zx()+mfMomentum[1]*mpMatrix->Zy()+mfMomentum[2]*mpMatrix->Zz();
 if(!(lfTemp<lfVect[2] && lfTemp>-lfVect[2]))
 {
	if(lfTemp<0.0f) lfVect[2]=-lfVect[2];
 }
 else lfVect[2]=lfTemp;

 mfMomentum[0]=lfVect[0]*mpMatrix->Xx()+lfVect[1]*mpMatrix->Yx()+lfVect[2]*mpMatrix->Zx();
 mfMomentum[1]=lfVect[0]*mpMatrix->Xy()+lfVect[1]*mpMatrix->Yy()+lfVect[2]*mpMatrix->Zy();
 mfMomentum[2]=lfVect[0]*mpMatrix->Xz()+lfVect[1]*mpMatrix->Yz()+lfVect[2]*mpMatrix->Zz();

};

void cMomentum::LimitAngularSpeeds(c3DVf lfVect)
{
	if(mfMomentum[3]>lfVect[0]) mfMomentum[3]=lfVect[0];
	else if(mfMomentum[3]<-lfVect[0]) mfMomentum[3]=-lfVect[0];

	if(mfMomentum[4]>lfVect[1]) mfMomentum[4]=lfVect[1];
	else if(mfMomentum[4]<-lfVect[1]) mfMomentum[4]=-lfVect[1];

	if(mfMomentum[5]>lfVect[2]) mfMomentum[5]=lfVect[2];
	else if(mfMomentum[5]<-lfVect[2]) mfMomentum[5]=-lfVect[2];
};

void cMomentum::LimitAngularSpeedX(float lfLimit)
{
	if(mfMomentum[3]>lfLimit) mfMomentum[3]=lfLimit;
	else if(mfMomentum[3]<-lfLimit) mfMomentum[3]=-lfLimit;
};

void cMomentum::LimitAngularSpeedY(float lfLimit)
{
	if(mfMomentum[4]>lfLimit) mfMomentum[4]=lfLimit;
	else if(mfMomentum[4]<-lfLimit) mfMomentum[4]=-lfLimit;

};

void cMomentum::LimitAngularSpeedZ(float lfLimit)
{
	if(mfMomentum[5]>lfLimit) mfMomentum[5]=lfLimit;
	else if(mfMomentum[5]<-lfLimit) mfMomentum[5]=-lfLimit;
};

void cMomentum::LimitAll(c3DVf lfVect,c3DVf lfAngular)
{
 LimitSpeeds(lfVect);
 LimitAngularSpeeds(lfAngular);
};


	float cMomentum::SpeedX(){return mfMomentum[0]*mpMatrix->Xx()+mfMomentum[1]*mpMatrix->Xy()+mfMomentum[2]*mpMatrix->Xz();};
	float cMomentum::SpeedY(){return mfMomentum[0]*mpMatrix->Yx()+mfMomentum[1]*mpMatrix->Yy()+mfMomentum[2]*mpMatrix->Yz();};
	float cMomentum::SpeedZ(){return mfMomentum[0]*mpMatrix->Zx()+mfMomentum[1]*mpMatrix->Zy()+mfMomentum[2]*mpMatrix->Zz();};

	float cMomentum::GSpeedX(){return mfMomentum[0];};
	float cMomentum::GSpeedY(){return mfMomentum[1];};
	float cMomentum::GSpeedZ(){return mfMomentum[2];};

	float cMomentum::AngularSpeedX(){return mfMomentum[3];};
	float cMomentum::AngularSpeedY(){return mfMomentum[4];};
	float cMomentum::AngularSpeedZ(){return mfMomentum[5];};


	void cMomentum::LimitedThrust(c3DVf lfVect, c3DVf lfLimit)
	{
		LimitedThrustX(lfVect[0],lfLimit[0]);
		LimitedThrustY(lfVect[1],lfLimit[1]);
		LimitedThrustZ(lfVect[2],lfLimit[2]);
	};

	void cMomentum::LimitedThrust(float *lfVect)
	{
		LimitedThrustX(lfVect[0],lfVect[3+0]);
		LimitedThrustY(lfVect[1],lfVect[3+1]);
		LimitedThrustZ(lfVect[2],lfVect[3+2]);
	};

	void cMomentum::LimitedThrust(float lfX,float lfY,float lfZ,float lfXLimit,float lfYLimit,float lfZLimit)
	{
		LimitedThrustX(lfX,lfXLimit);
		LimitedThrustY(lfY,lfYLimit);
		LimitedThrustZ(lfZ,lfZLimit);
	};

	void cMomentum::LimitedThrustX(float lfThrust,float lfLimit)
	{
	    float lfSpeed=SpeedX();
	    if(lfThrust>0.0f) lfThrust=lfThrust*(lfLimit-lfSpeed)/lfLimit;
		else lfThrust=lfThrust*(lfLimit+lfSpeed)/lfLimit;

        mfMomentum[0]+=lfThrust*mpMatrix->Xx();
        mfMomentum[1]+=lfThrust*mpMatrix->Xy();
        mfMomentum[2]+=lfThrust*mpMatrix->Xz();
	};

	void cMomentum::LimitedThrustY(float lfThrust,float lfLimit)
	{
		float lfSpeed=SpeedY();
	    if(lfThrust>0.0f) lfThrust=lfThrust*(lfLimit-lfSpeed)/lfLimit;
		else lfThrust=lfThrust*(lfLimit+lfSpeed)/lfLimit;

            mfMomentum[0]+=lfThrust*mpMatrix->Yx();
            mfMomentum[1]+=lfThrust*mpMatrix->Yy();
            mfMomentum[2]+=lfThrust*mpMatrix->Yz();
	};

	void cMomentum::LimitedThrustZ(float lfThrust,float lfLimit)
	{
	    float lfSpeed=SpeedZ();

		if(lfThrust>0.0f) lfThrust=lfThrust*(lfLimit-lfSpeed)/lfLimit;
		else lfThrust=lfThrust*(lfLimit+lfSpeed)/lfLimit;

		    mfMomentum[0]+=lfThrust*mpMatrix->Zx();
            mfMomentum[1]+=lfThrust*mpMatrix->Zy();
            mfMomentum[2]+=lfThrust*mpMatrix->Zz();
	};


void cMomentum::VectorThrust(float lfThrust,float lfAngleThrust,c3DVf lfDistance,c3DVf lfFacing)
{
    mfMomentum[0]+=lfFacing[0]*lfThrust;
    mfMomentum[1]+=lfFacing[1]*lfThrust;
    mfMomentum[2]+=lfFacing[2]*lfThrust;

    mfMomentum[3]+=(lfFacing[2]*lfDistance[1]-lfFacing[1]*lfDistance[2])*lfAngleThrust;
    mfMomentum[4]+=(lfFacing[2]*lfDistance[0]-lfFacing[0]*lfDistance[2])*lfAngleThrust;
    mfMomentum[5]+=(lfFacing[1]*lfDistance[0]-lfFacing[0]*lfDistance[1])*lfAngleThrust;

};

void cMomentum::VectorThrust(float lfThrust,float lfAngleThrust,cMatrix4 *lpMatrix)
{
    float lfDistance[3];
    lfDistance[0]=lpMatrix->X()-mpMatrix->X();
    lfDistance[1]=lpMatrix->Y()-mpMatrix->Y();
    lfDistance[2]=lpMatrix->Z()-mpMatrix->Z();

    mfMomentum[0]+=lpMatrix->Zx()*lfThrust;
    mfMomentum[1]+=lpMatrix->Zy()*lfThrust;
    mfMomentum[2]+=lpMatrix->Zz()*lfThrust;

    mfMomentum[3]+=(lpMatrix->Zz()*lfDistance[1]-lpMatrix->Zy()*lfDistance[2])*lfAngleThrust;
    mfMomentum[4]+=(lpMatrix->Zz()*lfDistance[0]-lpMatrix->Zx()*lfDistance[2])*lfAngleThrust;
    mfMomentum[5]+=(lpMatrix->Zy()*lfDistance[0]-lpMatrix->Zx()*lfDistance[1])*lfAngleThrust;

};

void cMomentum::VectorThrust(float lfThrust,float lfAngleThrust,cMatrix4 lpMatrix)
{
    mfMomentum[0]+=lpMatrix[8]*lfThrust;
    mfMomentum[1]+=lpMatrix[9]*lfThrust;
    mfMomentum[2]+=lpMatrix[10]*lfThrust;

    float lfDistance[3];
    lfDistance[0]=lpMatrix.X()-mpMatrix->X();
    lfDistance[1]=lpMatrix.Y()-mpMatrix->Y();
    lfDistance[2]=lpMatrix.Z()-mpMatrix->Z();

    mfMomentum[3]+=(lpMatrix.Zz()*lfDistance[1]-lpMatrix.Zy()*lfDistance[2])*lfAngleThrust;
    mfMomentum[4]+=(lpMatrix.Zz()*lfDistance[0]-lpMatrix.Zx()*lfDistance[2])*lfAngleThrust;
    mfMomentum[5]+=(lpMatrix.Zy()*lfDistance[0]-lpMatrix.Zx()*lfDistance[1])*lfAngleThrust;

};


void cMomentum::LimitedVectorThrust(float lfThrust,float lfAngleThrust,float lfLimit,c3DVf lfDistance,c3DVf lfFacing)
{
    float lfInv=lfThrust/lfLimit;
    mfMomentum[0]+=lfFacing[0]*lfInv*(lfLimit-SpeedX());
    mfMomentum[1]+=lfFacing[1]*lfInv*(lfLimit-SpeedY());
    mfMomentum[2]+=lfFacing[2]*lfInv*(lfLimit-SpeedZ());

    mfMomentum[3]+=(lfFacing[2]*lfDistance[1]-lfFacing[1]*lfDistance[2])*lfAngleThrust;
    mfMomentum[4]+=(lfFacing[2]*lfDistance[0]-lfFacing[0]*lfDistance[2])*lfAngleThrust;
    mfMomentum[5]+=(lfFacing[1]*lfDistance[0]-lfFacing[0]*lfDistance[1])*lfAngleThrust;

};

void cMomentum::LimitedVectorThrust(float lfThrust,float lfAngleThrust,float lfLimit,cMatrix4 *lpMatrix)
{
    float lfDistance[3];
    lfDistance[0]=lpMatrix->X()-mpMatrix->X();
    lfDistance[1]=lpMatrix->Y()-mpMatrix->Y();
    lfDistance[2]=lpMatrix->Z()-mpMatrix->Z();

    float lfInv=lfThrust/lfLimit;
    mfMomentum[0]+=lpMatrix->Zx()*lfInv*(lfLimit-SpeedX());
    mfMomentum[1]+=lpMatrix->Zy()*lfInv*(lfLimit-SpeedY());
    mfMomentum[2]+=lpMatrix->Zz()*lfInv*(lfLimit-SpeedZ());

    mfMomentum[3]+=(lpMatrix->Zz()*lfDistance[1]-lpMatrix->Zy()*lfDistance[2])*lfAngleThrust;
    mfMomentum[4]+=(lpMatrix->Zz()*lfDistance[0]-lpMatrix->Zx()*lfDistance[2])*lfAngleThrust;
    mfMomentum[5]+=(lpMatrix->Zy()*lfDistance[0]-lpMatrix->Zx()*lfDistance[1])*lfAngleThrust;

};

void cMomentum::LimitedVectorThrust(float lfThrust,float lfAngleThrust,float lfLimit,cMatrix4 lpMatrix)
{
    float lfInv=lfThrust/lfLimit;
         mfMomentum[0]+=lpMatrix[8]*lfInv*(lfLimit-SpeedX());
    mfMomentum[1]+=lpMatrix[9]*lfInv*(lfLimit-SpeedY());
    mfMomentum[2]+=lpMatrix[10]*lfInv*(lfLimit-SpeedZ());

    float lfDistance[3];
    lfDistance[0]=lpMatrix.X()-mpMatrix->X();
    lfDistance[1]=lpMatrix.Y()-mpMatrix->Y();
    lfDistance[2]=lpMatrix.Z()-mpMatrix->Z();

    mfMomentum[3]+=(lpMatrix.Zz()*lfDistance[1]-lpMatrix.Zy()*lfDistance[2])*lfAngleThrust;
    mfMomentum[4]+=(lpMatrix.Zz()*lfDistance[0]-lpMatrix.Zx()*lfDistance[2])*lfAngleThrust;
    mfMomentum[5]+=(lpMatrix.Zy()*lfDistance[0]-lpMatrix.Zx()*lfDistance[1])*lfAngleThrust;

};

void cMomentum::EqualsRelative(cMomentum *lpOther,cMatrix4 *lpRelVec)
{
    memcpy(&mfMomentum[3],&(lpOther->mfMomentum[3]),sizeof(float)*3);

    mfMomentum[0]=lpOther->mfMomentum[0]-(lpOther->mfMomentum[5]*lpRelVec->Y()-lpOther->mfMomentum[4]*lpRelVec->Z())*0.01f;
    mfMomentum[1]=lpOther->mfMomentum[1]-(lpOther->mfMomentum[3]*lpRelVec->Z()-lpOther->mfMomentum[5]*lpRelVec->X())*0.01f;
    mfMomentum[2]=lpOther->mfMomentum[2]-(lpOther->mfMomentum[4]*lpRelVec->X()-lpOther->mfMomentum[3]*lpRelVec->Y())*0.01f;
}

void cMomentum::EqualsRelative(cMomentum *lpOther,c3DVf lpRelVec)
{
    memcpy(&mfMomentum[3],&(lpOther->mfMomentum[3]),sizeof(float)*3);

    mfMomentum[0]=lpOther->mfMomentum[0]-(lpOther->mfMomentum[5]*lpRelVec.Y()-lpOther->mfMomentum[4]*lpRelVec.Z())*0.01f;
    mfMomentum[1]=lpOther->mfMomentum[1]-(lpOther->mfMomentum[3]*lpRelVec.Z()-lpOther->mfMomentum[5]*lpRelVec.X())*0.01f;
    mfMomentum[2]=lpOther->mfMomentum[2]-(lpOther->mfMomentum[4]*lpRelVec.X()-lpOther->mfMomentum[3]*lpRelVec.Y())*0.01f;
}


void cMomentum::EqualsRelative(cMomentum *lpOther,cMatrix4 *lcThisPos,cMatrix4 *lcOtherPos)
{
    c3DVf lcThis=lcThisPos->Position();
    lcThis-=lcOtherPos->Position();

    memcpy(&mfMomentum[3],&(lpOther->mfMomentum[3]),sizeof(float)*3);

    mfMomentum[0]=lpOther->mfMomentum[0]-(lpOther->mfMomentum[5]*lcThis.Y()-lpOther->mfMomentum[4]*lcThis.Z())*0.01f;
    mfMomentum[1]=lpOther->mfMomentum[1]-(lpOther->mfMomentum[3]*lcThis.Z()-lpOther->mfMomentum[5]*lcThis.X())*0.01f;
    mfMomentum[2]=lpOther->mfMomentum[2]-(lpOther->mfMomentum[4]*lcThis.X()-lpOther->mfMomentum[3]*lcThis.Y())*0.01f;
}

void cMomentum::Equals(cMomentum *lpOther)
{
    memcpy(mfMomentum,lpOther->mfMomentum,sizeof(float)*6);
};

float *cMomentum::GSpeeds(){return mfMomentum;};
float *cMomentum::AngularSpeeds(){return &mfMomentum[3];};

#endif
