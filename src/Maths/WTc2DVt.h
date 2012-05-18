#ifndef __WTC2DVT_H__
#define __WTC2DVT_H__

class cRGB;
class cRGBA;

/// This is a 2 dimensional float vector object
template<class Type> class c2DVt
{
public:
	Type v[2];

	///Return this Vectors X Value
	Type X();
	///Return this Vectors Y Value
	Type Y();

	///Set this Vectors X Value
	void X(Type lfX);
	///Set this Vectors Y Value
	void Y(Type lfY);



	/// This will return the absolute size of this vector.
       Type Magnitude();
    /// This will return the squared absolute size of this vector.
       Type MagnitudeSq();
	/// This will make the magnitude of this vector 1 while maintaining its direction.
       void Normalise();

		///Constructor to allow the User to initialise 0-2 components
        c2DVt(Type lf0=0,Type lf1=0);
		///Constructor to initialise the object from an array of three Types.
        c2DVt(Type *lf0);

		c2DVt(c2DVt *lfVect);
        c2DVt(const c2DVt &lfVect);

       c2DVt<Type> operator=(c2DVt *lpValue);
       c2DVt<Type> operator=(c2DVt lpValue);
       Type *operator=(Type *lpValue);
	   Type operator=(Type lpValue);

       c2DVt<Type> operator+=(c2DVt lpValue);
       c2DVt<Type> operator+=(c2DVt *lpValue);
       c2DVt<Type> operator+=(Type *lpValue);
	   c2DVt<Type> operator+=(Type lpValue);

       c2DVt<Type> operator-=(c2DVt lpValue);
       c2DVt<Type> operator-=(c2DVt *lpValue);
       c2DVt<Type> operator-=(Type *lpValue);
	   c2DVt<Type> operator-=(Type lpValue);

       c2DVt<Type> operator-(c2DVt lpValue);
       c2DVt<Type> operator-(c2DVt *lpValue);
       c2DVt<Type> operator-(Type *lpValue);
	   c2DVt<Type> operator-(Type lpValue);

       c2DVt<Type> operator+(c2DVt lpValue);
       c2DVt<Type> operator+(c2DVt *lpValue);
       c2DVt<Type> operator+(Type *lpValue);
	   c2DVt<Type> operator+(Type lpValue);

	   c2DVt<Type> operator*(c2DVt lpValue);
       c2DVt<Type> operator*(c2DVt *lpValue);
       c2DVt<Type> operator*(Type *lpValue);
	   c2DVt<Type> operator*(Type lpValue);

       c2DVt<Type> operator/(c2DVt lpValue);
       c2DVt<Type> operator/(c2DVt *lpValue);
       c2DVt<Type> operator/(Type *lpValue);
	   c2DVt<Type> operator/(Type lpValue);

       c2DVt<Type> operator*=(c2DVt lpValue);
       c2DVt<Type> operator*=(c2DVt *lpValue);
       c2DVt<Type> operator*=(Type *lpValue);
	   c2DVt<Type> operator*=(Type lpValue);

       c2DVt<Type> operator/=(c2DVt lpValue);
       c2DVt<Type> operator/=(c2DVt *lpValue);
       c2DVt<Type> operator/=(Type *lpValue);
	   c2DVt<Type> operator/=(Type lpValue);


	   bool operator==(c2DVt *lpValue);
	   bool operator==(c2DVt lpValue);




	   ///Will Findthe Dot Product of this vector and the vector lpValue.
       Type Dot(c2DVt lpValue);
       Type Dot(Type *lpValue);
       Type Dot(c2DVt *lpValue);

       c2DVt<Type> Perpendicular();
       c2DVt<Type> PerpendicularLH();
       c2DVt<Type> PerpendicularRH();

        float Angle(c2DVt<Type> lpOther);
        float SignedAngle(c2DVt<Type> lpOther);

	   ///Allows the User to access the components as if an array of values.
       Type &operator[](uint32 liPos);

	   void Equals(c2DVt *lpValue);
       void Equals(c2DVt lpValue);
       void Equals(Type *lpValue);
	   void Equals(Type lpValue);

};


#endif
