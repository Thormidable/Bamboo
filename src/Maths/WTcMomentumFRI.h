#ifndef __WTcMomentumFRI_H__
#define __WTcMomentumFRI_H__

#if WT_FULL_VERSION_BAMBOO
/**
 * \brief This Class will store an objects momentum (assumed mass of 1.0) and automatically update its matrix when the function Update() is called.
 * This gives the user the options of global and local thrusts and will update the objects linear and angular momentum by the thrusts applied to it.
 * An instance of cMomentumFRI must be linked to a matrix. It will only update when the function Update() is called.
 * */
class cMomentumFRI 
{
 cMatrix4 *mpMatrix;
 float mfMomentum[6];
public:

	///Constructor passing this object a cMatrix4.
	cMomentumFRI(cMatrix4 *lpMatrix);

	///Applies a 3 axis linear thrust along Local axis
	void Thrust(c3DVf lfVect);
	///Applies a 3 axis linear thrust along Local axis
	void Thrust(float *lfVect);
	///Applies a 3 axis linear thrust along Local axis
	void Thrust(float lfX,float lfY,float lfZ);
	///Applies a linear thrust equal to lfThrust along the objects Local X Axis.
	void ThrustX(float lfThrust);
	///Applies a linear thrust equal to lfThrust along the objects Local Y Axis.
	void ThrustY(float lfThrust);
	///Applies a linear thrust equal to lfThrust along the objects Local Z Axis.
	void ThrustZ(float lfThrust);

	///Applies a 3 axis linear thrust about Local axis. Thrust effectiveness will deteriate as speed in the Local Axis increases.
	void LimitedThrust(c3DVf lfVect,c3DVf lfLimit);
	///Applies a 3 axis linear thrust about Local axis. Thrust effectiveness will deteriate as speed in the Local Axis increases.
	void LimitedThrust(float *lfVect);
	///Applies a 3 axis linear thrust about Local axis. Thrust effectiveness will deteriate as speed in the Local Axis increases.
	void LimitedThrust(float lfX,float lfY,float lfZ,float lfXLimit,float lfYLimit,float lfZLimit);
	///Applies a linear thrust along the Local X axis. Thrust effectiveness will deteriate as speed in the Local X Axis increases.
	void LimitedThrustX(float lfThrust,float lfLimit);
	///Applies a linear thrust along the Local X axis. Thrust effectiveness will deteriate as speed in the Local Y Axis increases.
	void LimitedThrustY(float lfThrust,float lfLimit);
	///Applies a linear thrust along the Local X axis. Thrust effectiveness will deteriate as speed in the Local Z Axis increases.
	void LimitedThrustZ(float lfThrust,float lfLimit);

	///Applies a 3 axis linear thrust about Global Axis
	void GThrust(c3DVf lfVect);
	///Applies a 3 axis linear thrust about Global Axis
	void GThrust(float *lfVect);
	///Applies a 3 axis linear thrust about Global Axis
	void GThrust(float lfX,float lfY,float lfZ);
	///Applies a linear thrust equal to lfThrust along the objects Global X Axis.
	void GThrustX(float lfThrust);
	///Applies a linear thrust equal to lfThrust along the objects Global Y Axis.
	void GThrustY(float lfThrust);
	///Applies a linear thrust equal to lfThrust along the objects Global Z Axis.
	void GThrustZ(float lfThrust);

    ///Applies a Thrust to the Object at a point lfDistance from its origin along the global axis with a global vector lfFacing
    void VectorThrust(float lfThrust,float lfAngleThrust,c3DVf lfDistance,c3DVf lfFacing);
    ///Applies a Thrust to the Object using the position and facing of the cMatrix4 lpMatrix.
    void VectorThrust(float lfThrust,float lfAngleThrust,cMatrix4 *lpMatrix);
    ///Applies a Thrust to the Object using the position and facing of the cMatrix4 lpMatrix.
    void VectorThrust(float lfThrust,float lfAngleThrust,cMatrix4 lpMatrix);
    ///Applies a Limited Thrust to the Object at a point lfDistance from its origin along the global axis with a global vector lfFacing
    void LimitedVectorThrust(float lfThrust,float lfAngleThrust,float lfLimit,c3DVf lfDistance,c3DVf lfFacing);
    ///Applies a Limited Thrust to the Object using the position and facing of the cMatrix4 lpMatrix.
    void LimitedVectorThrust(float lfThrust,float lfAngleThrust,float lfLimit,cMatrix4 *lpMatrix);
    ///Applies a Limited Thrust to the Object using the position and facing of the cMatrix4 lpMatrix.
    void LimitedVectorThrust(float lfThrust,float lfAngleThrust,float lfLimit,cMatrix4 lpMatrix);


	///Applies a 3 axis angular thrust about Local axis
	void ThrustAngle(c3DVf lfVect);
	///Applies a 3 axis angular thrust about Local axis
	void ThrustAngle(float *lfVect);
	///Applies a 3 axis angular thrust about Local axis
	void ThrustAngle(float lfX,float lfY,float lfZ);
	///Applies an angular thrust equal to lfThrust around the objects Local X Axis.
	void ThrustAngleX(float lfThrust);
	///Applies an angular thrust equal to lfThrust around the objects Local Y Axis.
	void ThrustAngleY(float lfThrust);
	///Applies an angular thrust equal to lfThrust around the objects Local Z Axis.
	void ThrustAngleZ(float lfThrust);

	///Applies a 3 axis angular thrust about Global axis
	void GThrustAngle(c3DVf lfVect);
	///Applies a 3 axis angular thrust about Global axis
	void GThrustAngle(float *lfVect);
	///Applies a 3 axis angular thrust about Global axis
	void GThrustAngle(float lfX,float lfY,float lfZ);
	///Applies an angular thrust equal to lfThrust around the objects Global X Axis.
	void GThrustAngleX(float lfThrust);
	///Applies an angular thrust equal to lfThrust around the objects Global Y Axis.
	void GThrustAngleY(float lfThrust);
	///Applies an angular thrust equal to lfThrust around the objects Global Z Axis.
	void GThrustAngleZ(float lfThrust);

	///This will dampen the momentum by the factor lfValue
	void DampenMomentum(float lfValue);
	///This will dampen the linear momentum by the factor lfValue
	void DampenLinear(float lfValue);
	///This will dampen the angular momentum by the factor lfValue
	void DampenAngular(float lfValue);
		
	///This Will apply thrust to reduce non-forward motion.
	void Straighten(float lfThrust);

	///This Will apply thrust to reduce Left/Right motion.
	void StraightenX(float lfThrust);
	///This Will apply thrust to reduce Up/Down motion.
	void StraightenY(float lfThrust);
	///This will apply thrust to reduce forwards / backwards motion
	void StraightenZ(float lfThrust);

	///This will apply thrust to reduce rotations.
	void Stabilise(float lfThrust);

	///This will apply thrust to reduce rotations about the X Axis
	void StabiliseX(float lfThrust);
	///This will apply thrust to reduce rotations about the Y Axis
	void StabiliseY(float lfThrust);
	///This will apply thrust to reduce rotations about the Z Axis
	void StabiliseZ(float lfThrust);

	///This will limit the Speeds along the three axis
	void LimitSpeeds(c3DVf lfVect);
	///This will limit the Speed along the Local X axis
	void LimitSpeedX(float lfLimit);
	///This will limit the Speed along the Local X axis
	void LimitSpeedY(float lfLimit);
	///This will limit the Speed along the Local X axis
	void LimitSpeedZ(float lfLimit);

	///This will limit the angular Speeds about all three axis
	void LimitAngularSpeeds(c3DVf lfVect);
	///This will limit the angular Speeds about the Local X axis
	void LimitAngularSpeedX(float lfLimit);
	///This will limit the angular Speeds about the Local Y axis
	void LimitAngularSpeedY(float lfLimit);
	///This will limit the angular Speeds about the Local Z axis
	void LimitAngularSpeedZ(float lfLimit);

	///This will limit the Speeds and angular speeds.
	void LimitAll(c3DVf lfVect,c3DVf lfAngular);

	///Will update the Matrix with the effects of the objects momentum.
	void Update();

	void UpdateFrameRateDependant();

	///Will return the speed along the Local X Axis
	float SpeedX();
	///Will return the speed along the Local Y Axis
	float SpeedY();
	///Will return the speed along the Local Z Axis
	float SpeedZ();
	///This will return the Global Speed Vector (Global X,Y,Z Axis Speeds)
	float *GSpeeds();
	///Will return the speed along the Global X Axis
	float GSpeedX();
	///Will return the speed along the Global Y Axis
	float GSpeedY();
	///Will return the speed along the Global Z Axis
	float GSpeedZ();
	///This will return the Angular Speed Vector (Global X,Y,Z Axis Speeds)
	float *AngularSpeeds();
	///Will return the Angular speed about the Local X Axis
	float AngularSpeedX();
	///Will return the Angular speed about the Local Y Axis
	float AngularSpeedY();
	///Will return the Angular speed about the Local Z Axis
	float AngularSpeedZ();

    ///Will return the Magnitude of the linear momentum vector.
    float Magnitude();
    ///Will return the magnitude of the angular momentum vector.
    float MagnitudeAngular();

    float MagnitudeSq();
    ///Will return the magnitude of the angular momentum vector.
    float MagnitudeAngularSq();


	///Will return the Current MomentumVector
	c3DVf GMomentumVector();
	///Will return the Current RotationVector
    c3DVf RotationVector();

    ///This will Make this momentum Base itself off the Matrix Translations lpRelVec from the Base Momentum.
    void EqualsRelative(cMomentumFRI *lpOther,cMatrix4 *lpRelVec);
    ///This will
    void EqualsRelative(cMomentumFRI *lpOther,c3DVf lpRelVec);


    void EqualsRelative(cMomentumFRI *lpOther,cMatrix4 *lcThisPos,cMatrix4 *lcOtherPos);

    void Equals(cMomentumFRI *lpOther);

};

#endif

#endif
