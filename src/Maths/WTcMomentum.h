#ifndef __WTCMOMENTUM_H__
#define __WTCMOMENTUM_H__

/**
 * \brief This Class will store an objects momentum (assumed mass of 1.0) and automatically update its matrix when the function Update() is called.
 * This gives the user the options of global and local thrusts and will update the objects linear and angular momentum by the thrusts applied to it.
 * An instance of cMomentum must be linked to a matrix. It will only update whne the function Update() is called.
 * */
class cMomentum
{
 cMatrix4 *mpMatrix;
 float mfMomentum[6];
public:

	///Constructor passing this object a cMatrix4.
	cMomentum(cMatrix4 *lpMatrix);
	///Applies a linear thrust equal to lfThrust along the objects Local X Axis.
	void ThrustX(float lfThrust);
	///Applies a linear thrust equal to lfThrust along the objects Local Y Axis.
	void ThrustY(float lfThrust);
	///Applies a linear thrust equal to lfThrust along the objects Local Z Axis.
	void ThrustZ(float lfThrust);
	///Applies a linear thrust equal to lfThrust along the objects Global X Axis.
	void GThrustX(float lfThrust);
	///Applies a linear thrust equal to lfThrust along the objects Global Y Axis.
	void GThrustY(float lfThrust);
	///Applies a linear thrust equal to lfThrust along the objects Global Z Axis.
	void GThrustZ(float lfThrust);

	///Applies an angular thrust equal to lfThrust around the objects Local X Axis.
	void ThrustAngleX(float lfThrust);
	///Applies an angular thrust equal to lfThrust around the objects Local Y Axis.
	void ThrustAngleY(float lfThrust);
	///Applies an angular thrust equal to lfThrust around the objects Local Z Axis.
	void ThrustAngleZ(float lfThrust);
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

	///This Will apply thrust to reduce non-forward motion. Not Yet Implemented.
	void Straighten(float lfThrust);

	///This will apply thrust to reduce rotations.
	void Stabilise(float lfThrust);

	///Will update the Matrix with the effects of the objects momentum.
	void Update();

	c3DVf MomentumVector();
    c3DVf RotationVector();
};


#endif
