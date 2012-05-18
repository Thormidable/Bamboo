#ifndef __WTC3DVT_H__
#define __WTC3DVT_H__

class cRGB;
class cRGBA;

/// This is a 3 dimensional float vector object
template<class Type> class c3DVt
{
public:
	Type v[3];

	///Return this Vectors X Value
	Type X();
	///Return this Vectors Y Value
	Type Y();
	///Return this Vectors Z Value
	Type Z();

	///Set this Vectors X Value
	void X(Type lfX);
	///Set this Vectors Y Value
	void Y(Type lfY);
	///Set this Vectors Z Value
	void Z(Type lfZ);


	/// This will return the absolute size of this vector.
       Type Magnitude();
       /// This will return the squared absolute size of this vector.
       Type MagnitudeSq();

       /// This will return the Distance between this point and the point at lpOther.
       Type Distance(c3DVt<Type> lpOther);
       /// This will return the Distance between this point and the point at lpOther.
       Type Distance(c3DVt<Type> *lpOther);
       /// This will return the Distance between this point and the point at lpOther.
       Type Distance(Type *lpOther);
       /// This will return the Squared Distance between this point and the point at lpOther.
       Type DistanceSq(c3DVt<Type> lpOther);
       /// This will return the Squared Distance between this point and the point at lpOther.
       Type DistanceSq(c3DVt<Type> *lpOther);
       /// This will return the Squared Distance between this point and the point at lpOther.
       Type DistanceSq(Type *lpOther);

	/// This will make the magnitude of this vector 1 while maintaining its direction.
       void Normalise();

		///Constructor to allow the User to initialise 0-3 components
        c3DVt(Type lf0=0,Type lf1=0,Type lf2=0);
		///Constructor to initialise the object from an array of three Types.
        c3DVt(Type *lf0);
		///Constructor to initialise from a c3DVf pointer
		c3DVt(c3DVt *lfVect);
		///Constructor to initialise from a c3DVf reference
        c3DVt(const c3DVt &lfVect);

       c3DVt<Type> operator=(c3DVt *lpValue);
       //c3DVt<Type> operator=(c3DVt &lpValue);
       c3DVt<Type> operator=(c3DVt lpValue);
       c3DVt<Type> operator=(cRGB *lpValue);
       c3DVt<Type> operator=(cRGB &lpValue);
       Type *operator=(Type *lpValue);

       c3DVt<Type> operator+=(c3DVt lpValue);
       c3DVt<Type> operator+=(c3DVt *lpValue);
       c3DVt<Type> operator+=(Type *lpValue);
       c3DVt<Type> operator+=(Type lpValue);

       c3DVt<Type> operator-=(c3DVt lpValue);
       c3DVt<Type> operator-=(c3DVt *lpValue);
       c3DVt<Type> operator-=(Type *lpValue);
       c3DVt<Type> operator-=(Type lpValue);

       c3DVt<Type> operator*=(c3DVt lpValue);
       c3DVt<Type> operator*=(c3DVt *lpValue);
       c3DVt<Type> operator*=(Type *lpValue);
       c3DVt<Type> operator*=(Type lpValue);

       c3DVt<Type> operator/=(c3DVt lpValue);
       c3DVt<Type> operator/=(c3DVt *lpValue);
       c3DVt<Type> operator/=(Type *lpValue);
       c3DVt<Type> operator/=(Type lpValue);

       c3DVt<Type> operator-(c3DVt lpValue);
       c3DVt<Type> operator-(c3DVt *lpValue);
       c3DVt<Type> operator-(Type *lpValue);
       c3DVt<Type> operator-(Type lpValue);

       c3DVt<Type> operator+(c3DVt lpValue);
       c3DVt<Type> operator+(c3DVt *lpValue);
       c3DVt<Type> operator+(Type *lpValue);
       c3DVt<Type> operator+(Type lpValue);

       ///Will Find the cross Product of this vector and the vector lpValue.
       c3DVt<Type> operator*(c3DVt lpValue);
       c3DVt<Type> operator*(c3DVt *lpValue);
       c3DVt<Type> operator*(Type *lpValue);
	   c3DVt<Type> operator*(Type lpValue);

       c3DVt<Type> operator/(Type lpValue);
	   c3DVt<Type> operator/(Type *lpValue);
	   c3DVt<Type> operator/(c3DVt lpValue);
	   c3DVt<Type> operator/(c3DVt *lpValue);

	   bool operator==(Type *lpValue);
	   bool operator==(c3DVt<Type> lpValue);




	   ///Will Findthe Dot Product of this vector and the vector lpValue.
       Type Dot(c3DVt lpValue);
       Type Dot(Type *lpValue);
       Type Dot(c3DVt *lpValue);

       float Angle(c3DVt lpOther);

	   ///Allows the User to access the components as if an array of values.
       Type &operator[](uint32 liPos);

	   ///This will invert this vector (multiply each component by -1.0f).
	   c3DVt<Type> Invert();

};


#endif
