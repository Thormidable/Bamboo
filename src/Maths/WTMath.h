#ifndef __WTMATH_H__
#define __WTMATH_H__

class cRGB;
class cRGBA;
///This is a 1 Dimensional float vector object
class c1DVf
{
public:
	float v;
	float operator=(float lfFloat);
	float *operator=(float *lfFloat);
	c1DVf operator=(c1DVf Other);
	c1DVf *operator=(c1DVf *Other);

	float operator+(float lfFloat);
	float operator+(c1DVf Other);

	float operator-(float lfFloat);
	float operator-(c1DVf Other);

	float operator*(float lfFloat);
	float operator*(c1DVf Other);

	float operator/(float lfFloat);
	float operator/(c1DVf Other);

	void Normalise();

	float Magnatude();


};

///This is a 2 Dimensional float vector object.
class c2DVf
{
public:
	float v[2];
	///Return this Vectors X Value
	float X();
	///Return this Vectors Y Value
	float Y();
	//Set this Vectors X Value
	void X(float lfX);
	//Set this Vectors Y Value
	void Y(float lfY);
	/// This will return the angle of the vector in radians.
       double Angle();
	/// This will return the absolute size of the vector.
       float Magnitude();
	/// This will equate this vector to the c2DVf pointed to by lpValue.
       void operator=(c2DVf *lpValue);
	///Allows the user to access the components as an array of values.
       float &operator[](uint32 liPos){return v[liPos];};
};

/// This is a 3 dimensional float vector object
class c3DVf
{
public:
	float v[3];
	///Return this Vectors X Value
	float X();
	///Return this Vectors Y Value
	float Y();
	///Return this Vectors Z Value
	float Z();

	//Set this Vectors X Value
	void X(float lfX);
	//Set this Vectors Y Value
	void Y(float lfY);
	//Set this Vectors Z Value
	void Z(float lfZ);


	/// This will return the absolute size of this vector.
       float Magnitude();
	/// This will make the magnitude of this vector 1 while maintaining its direction.
       void Normalise();

		///Constructor to allow the User to initialise 0-3 components
        c3DVf(float lf0=0.0f,float lf1=0.0f,float lf2=0.0f);
		///Constructor to initialise the object from an array of three floats.
        c3DVf(float *lf0);

       c3DVf *operator=(c3DVf *lpValue);
       c3DVf operator=(c3DVf lpValue);
       float *operator=(float *lpValue);
       c3DVf operator+=(c3DVf lpValue);
       c3DVf *operator+=(c3DVf *lpValue);
       c3DVf *operator=(cRGB *lpValue);
       c3DVf &operator=(cRGB &lpValue);
	   ///Will Findthe Dot Product of this vector and the vector lpValue.
       float Dot(c3DVf lpValue);

	   ///Will Find the cross Product of this vector and the vector lpValue.
       c3DVf operator*(c3DVf lvOther);
	   ///Allows the User to access the components as if an array of values.
       float &operator[](uint32 liPos){return v[liPos];};
};
/// This is a 4 dimensional float vector object
class c4DVf
{

public:

	float v[4];
	///Return this Vectors X Value
	float X();
	///Return this Vectors Y Value
	float Y();
	///Return this Vectors Z Value
	float Z();
	///Return this Vectors W Value
	float W();

	//Set this Vectors X Value
	void X(float lfX);
	//Set this Vectors Y Value
	void Y(float lfY);
	//Set this Vectors Z Value
	void Z(float lfZ);
	//Set this Vectors W Value
	void W(float lfW);

			///Constructor to allow the User to initialise 0-4 components
        c4DVf(float lf0=0.0f,float lf1=0.0f,float lf2=0.0f,float lf3=0.0f);
				///Constructor to initialise the object from an array of four floats.
        c4DVf(float *lf0);

       c4DVf *operator=(c4DVf *lpValue);
       c4DVf &operator=(c4DVf &lpValue);
       float *operator=(float *lpValue);
       c4DVf &operator+=(c4DVf &lpValue);
       c4DVf *operator+=(c4DVf *lpValue);
       c4DVf *operator=(cRGBA *lpValue);
       c4DVf &operator=(cRGBA &lpValue);
       c4DVf *operator=(cRGB *lpValue);
       c4DVf &operator=(cRGB &lpValue);

///Allows the User to access the components as if an array of values.
       float &operator[](uint32 liPos);


};

/// This is a 2 Dimensional integer vector.
class c2DVi
{
public:
	int v[2];

		///Return this Vectors X Value
	int X();
	///Return this Vectors Y Value
	int Y();
	/// This will return the angle of the vector in radians.
       long Angle();
	/// This will return the absolute size of the vector.
       int Magnitude();
       c2DVi *operator=(c2DVi *lpValue);
	   ///Allows the User to access the components as if an array of values.
       int &operator[](uint32 liPos){return v[liPos];};
};

/// This is a 3 Dimensional integer vector.
class c3DVi
{
public:
	int v[3];

		///Return this Vectors X Value
	int X();
	///Return this Vectors Y Value
	int Y();
	///Return this Vectors Z Value
	int Z();
	/// This will return the absolute size of the vector.
       int Magnitude();
       c3DVi operator*(c3DVi lvOther);
       c3DVi *operator=(c3DVi *lpValue);
       c3DVi operator=(c3DVi lpValue);
	   	   ///Will Findthe Dot Product of this vector and the vector lpValue.
       float Dot(c3DVi lpValue);
	   ///Allows the User to access the components as if an array of values.
       int &operator[](uint32 liPos){return v[liPos];};
};

/// This function takes an angle in Degrees and will return it in radians.
float DegreestoRadians(float lfAngle);
/// This function takes an angle in radians and will return it in Degrees.
float RadianstoDegrees(float lfAngle);


#endif
