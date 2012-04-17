#ifndef __WTCPREDICTIVETRACKING_H__
#define __WTCPREDICTIVETRACKING_H__

#if WT_FULL_VERSION_BAMBOO
/**
 * \brief This class will calculate the vector to hit a moving target from a firing object given the relevant data.
 * It will store the information about the expected interception, Vector to launch projectile in global co-oridinates, expected interception point in global co-ordinates
 * Expected number of time steps to interception and whether the projectile can hit the target. This uses a linear extrapolation technique to predict the targets movement.
 * See also cPredictiveTracking
 */
class cPredictiveAiming
{
protected:
 c3DVf mvVector;
 c3DVf mvInterceptionPoint;
 float mfTimeSteps;
 bool mbCanHit;
public:

	cPredictiveAiming();
	c3DVf Calculate(c3DVf mvTargetPosition,c3DVf mvTargetVelocity,c3DVf mvFirerPosition,float lfProjectileSpeed);

	///This will return the vector the projectile should follow (normalised) to hit the target. It assumes the user wishes the easliest possible time of collision.
	c3DVf InterceptionVector();

	///This will return the point the projectile is expected to intercept the target at. It assumes the user wishes the easliest possible time of collision.
	c3DVf InterceptionPoint();

	///This will return false if the projectile is not expected to hit the target. This can be caused by the target travelling away from the projectiles too fast.
	bool CanHit();

	///This will return the expected number of time steps before the bullet hits the target.
	float TimeStepsToInterception();

};


/**
 * \brief This class will track an object relative to another object and give the vector to be fired to intercept the target (given projectile speed)
 * This class inherits from cPredictiveAiming, but automatically tracks a target relative to a firing objec. This class is set to follow two objects, and firer and a target. It can be polled for a most likely targeting vector to hit the target.
 * It can also return the expected number of time steps before collisions. This can be roughly assumed to be inversely proportional to the likelyhood of a hit.
 * The Vector returned is the direction the projectile should be traveling in global co-ordinates. This assumes that the Firers velocity is not going to affect the projectiles velocity.
 * To update This class MUST point at a living target and a living firer. If either die, the dead object should be replaced or the class deleted.
 * */
class cPredictiveTracking : public cPredictiveAiming
{
 cMatrix4 *mpTarget;
 cMatrix4 *mpFirer;

 c3DVf mvLast;
 c3DVf mvCurrent;

public:

	cPredictiveTracking(vRenderObject *lpTarget,vRenderObject *lpFirer);
	cPredictiveTracking(cMatrix4 *lpTarget,cMatrix4 *lpFirer);
	cPredictiveTracking(cMatrix4 *lpTarget,vRenderObject *lpFirer);
	cPredictiveTracking(vRenderObject *lpTarget,cMatrix4 *lpFirer);

	void Initialise(cMatrix4 *lpTarget,cMatrix4 *lpFirer);
	~cPredictiveTracking();

	///This will keep the tracking active but not calculate the targeting vector. After this function is used a targeting vector will not be calculated.
	void UpdateFast();

	///This should be called once a time step, it will update the calculations of the objects.
	void Update(float lfProjectileSpeed);

	///This will change the Target.
	void ChangeTarget(vRenderObject *lpTarg);
	///This will change the Target.
	void ChangeTarget(cMatrix4 *lpTarg);


	///This will change the Firer.
	void ChangeFirer(vRenderObject *lpFirer);
	///This will change the Firer.
	void ChangeFirer(cMatrix4 *lpFirer);

};

#endif

#endif
