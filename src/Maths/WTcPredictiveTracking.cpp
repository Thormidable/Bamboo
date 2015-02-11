
#include "../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

cPredictiveAiming::cPredictiveAiming()
{
	mfTimeSteps=0;
	mbCanHit=false;
	mvVector=c3DVf(0.0f,0.0f,1.0f);
};


	c3DVf cPredictiveAiming::InterceptionVector(){return mvVector;};
	float cPredictiveAiming::TimeStepsToInterception(){return mfTimeSteps;};
	bool cPredictiveAiming::CanHit(){return mbCanHit;};
	c3DVf cPredictiveAiming::InterceptionPoint(){return mvInterceptionPoint;};


c3DVf cPredictiveAiming::Calculate(c3DVf mvTargetPosition,c3DVf mvTargetVelocity,c3DVf mvFirerPosition,float lfProjectileSpeed)
{

mvFirerPosition=mvTargetPosition-mvFirerPosition;

 double a=mvTargetVelocity.Dot(mvTargetVelocity)-lfProjectileSpeed*lfProjectileSpeed;
 double b=mvFirerPosition.Dot(mvTargetVelocity)*2;
 double c=mvFirerPosition.Dot(mvFirerPosition);



 c=b*b-4*a*c;
 if(c>0.0f)
 {
	 c=sqrt(c);

	 if(a>0.0f)
	 {
		if(-b-c>0.0f) c=-b-c;
		else c=-b+c;
	 }
	 else
	 {
		 //a is -ve
		if(-b+c<0.0f) c=-b+c;
		else c=-b-c;
	 }

	 c=c/(2*a);
	 if(c>0.0f)
	 {
 		mfTimeSteps=c;

		mvInterceptionPoint=mvTargetPosition+(mvTargetVelocity*mfTimeSteps);
		mvVector=mvInterceptionPoint+mvFirerPosition-mvTargetPosition;
		mvVector.Normalise();


	 	mbCanHit=true;
	 }
	 else
	 {
		mbCanHit=false;
	 }
 }
 else mbCanHit=false;

 return mvVector;

};

	void cPredictiveTracking::Initialise(cMatrix4 *lpTarget,cMatrix4 *lpFirer)
	{
		mpTarget=lpTarget;
		mpFirer=lpFirer;
		UpdateFast();
		mvLast=mvCurrent;
	}

	cPredictiveTracking::cPredictiveTracking(vRenderObject *lpTarget,vRenderObject *lpFirer)
	{
		Initialise(&(lpTarget->mmCache),&(lpFirer->mmCache));
	};

	cPredictiveTracking::cPredictiveTracking(cMatrix4 *lpTarget,vRenderObject *lpFirer)
	{
		Initialise(lpTarget,&(lpFirer->mmCache));
	};

	cPredictiveTracking::cPredictiveTracking(vRenderObject *lpTarget,cMatrix4 *lpFirer)
	{
		Initialise(&(lpTarget->mmCache),lpFirer);
	};

	cPredictiveTracking::cPredictiveTracking(cMatrix4 *lpTarget,cMatrix4 *lpFirer)
	{
		Initialise(lpTarget,lpFirer);
	};

	cPredictiveTracking::~cPredictiveTracking()
	{

	};

	void cPredictiveTracking::ChangeTarget(vRenderObject *lpTarg)
	{
		mpTarget=&(lpTarg->mmCache);
	}

	void cPredictiveTracking::ChangeFirer(vRenderObject *lpFirer)
	{
		mpFirer=&(lpFirer->mmCache);
	}

	void cPredictiveTracking::ChangeTarget(cMatrix4 *lpTarg)
	{
		mpTarget=lpTarg;
	}

	void cPredictiveTracking::ChangeFirer(cMatrix4 *lpFirer)
	{
		mpFirer=lpFirer;
	}

	void cPredictiveTracking::UpdateFast()
	{
		mvLast=mvCurrent;
		mvCurrent=c3DVf(mpTarget->Position());
		mbCanHit=false;
	};

	void cPredictiveTracking::Update(float lfProjectileSpeed)
	{
		UpdateFast();

		Calculate(mvCurrent,mvCurrent-mvLast,c3DVf(mpFirer->Position()),lfProjectileSpeed);
	};

#endif
