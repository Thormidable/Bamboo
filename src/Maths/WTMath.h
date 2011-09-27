#ifndef __WTMATH_H__
#define __WTMATH_H__
///This is a 2 Dimensional float vector object.
class c2DVf
{
public:
	float v[2];
	/*
	/// This stores the x vector for this object.
       float x;
	
	/// This stores the y vector for this object.
	float y;
	*/
	/// This will return the angle of the vector in radians.
       double Angle();
	/// This will return the absolute size of the vector.
       float Magnitude();
	/// This will equate this vector to the c2DVf pointed to by lpValue.
       void operator=(c2DVf *lpValue);

       float &operator[](uint32 liPos){return v[liPos];};
};

/// This is a 3 dimensional float vector object
class c3DVf
{
public:
	float v[3];
	/*
	/// This stores the x vector for this object.
       float x;
	/// This stores the y vector for this object.
	float y;
	/// This stores the z vector for this object.
	float z;
	*/
	/// This will return the absolute size of this vector.
       float Magnitude();
	/// This will make the magnitude of this vector 1 while maintaining its direction.
       void Normalise();
	
       c3DVf *operator=(c3DVf *lpValue);
       c3DVf operator=(c3DVf lpValue);
       float *operator=(float *lpValue);
       c3DVf operator+=(c3DVf lpValue);
       c3DVf *operator+=(c3DVf *lpValue);
       float Dot(c3DVf lpValue);
       
       c3DVf operator*(c3DVf lvOther);
       float &operator[](uint32 liPos){return v[liPos];};
};

/// This is a 2 Dimensional integer vector.
class c2DVi
{
public:
	int v[2];
	/*
	/// This stores the X component of the vector.
       int x;
	/// This stores the Y component of the vector.
	int y;
	*/
	/// This will return the angle of the vector in radians.
       long Angle();
	/// This will return the absolute size of the vector.
       int Magnitude();
       c2DVi *operator=(c2DVi *lpValue);
       int &operator[](uint32 liPos){return v[liPos];};
};

/// This is a 3 Dimensional integer vector.
class c3DVi
{
public:
	int v[3];
	/*
	/// This stores the X component of the vector.
       int x;
	/// This stores the Y component of the vector.
	int y;
	/// This stores the Z component of the vector.
	int z;
*/
	/// This will return the absolute size of the vector.
       int Magnitude();
       c3DVi operator*(c3DVi lvOther);
       c3DVi *operator=(c3DVi *lpValue);
       c3DVi operator=(c3DVi lpValue);
       float Dot(c3DVi lpValue);
       int &operator[](uint32 liPos){return v[liPos];};
};

/// This function takes an angle in Degrees and will return it in radians.
float DegreestoRadians(float lfAngle);
/// This function takes an angle in radians and will return it in Degrees.
float RadianstoDegrees(float lfAngle);
#endif
