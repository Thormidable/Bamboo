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
	Type X()const;
	///Return this Vectors Y Value
	Type Y()const;
	///Return this Vectors Z Value
	Type Z()const;

	///Set this Vectors X Value
	void X(Type lfX);
	///Set this Vectors Y Value
	void Y(Type lfY);
	///Set this Vectors Z Value
	void Z(Type lfZ);


	/// This will return the absolute size of this vector.
	Type Magnitude()const;
       /// This will return the squared absolute size of this vector.
	   Type MagnitudeSq()const;

       /// This will return the Distance between this point and the point at lpOther.
	   Type Distance(const c3DVt<Type> &lpOther)const;       
       /// This will return the Distance between this point and the point at lpOther.
	   Type Distance(const Type *lpOther)const;
       /// This will return the Squared Distance between this point and the point at lpOther.
	   Type DistanceSq(const c3DVt<Type> &lpOther)const;
       /// This will return the Squared Distance between this point and the point at lpOther.
	   Type DistanceSq(const Type *lpOther)const;

	/// This will make the magnitude of this vector 1 while maintaining its direction.
       void Normalise();

		///Constructor to allow the User to initialise 0-3 components
        c3DVt(Type lf0=0,Type lf1=0,Type lf2=0);
		///Constructor to initialise the object from an array of three Types.
        c3DVt(Type *lf0);
		///Constructor to initialise from a c3DVf reference
        c3DVt(const c3DVt &lfVect);

		template<class Other> c3DVt(const c3DVt<Other> &lfVect)
		{
			v[0] = static_cast<Type>(lfVect[0]);
			v[1] = static_cast<Type>(lfVect[1]);
			v[2] = static_cast<Type>(lfVect[2]);
		}

       c3DVt<Type> &operator=(const c3DVt &lpValue);
       c3DVt<Type> &operator=(const cRGB lpValue);
       c3DVt<Type> &operator=(const cRGB &lpValue);
	   c3DVt<Type> &operator=(const Type *lpValue);
	   c3DVt<Type> &operator=(Type lpValue);

	   c3DVt<Type> &operator+=(const c3DVt &lpValue);
	   c3DVt<Type> &operator+=(const Type *lpValue);
	   c3DVt<Type> &operator+=(Type lpValue);

	   c3DVt<Type> &operator-=(const c3DVt &lpValue);
	   c3DVt<Type> &operator-=(const Type *lpValue);
	   c3DVt<Type> &operator-=(Type lpValue);

	   c3DVt<Type> &operator*=(const c3DVt &lpValue);
	   c3DVt<Type> &operator*=(const Type *lpValue);
	   c3DVt<Type> &operator*=(Type lpValue);

	   c3DVt<Type> &operator/=(const c3DVt &lpValue);
	   c3DVt<Type> &operator/=(const Type *lpValue);
	   c3DVt<Type> &operator/=(Type lpValue);

	   c3DVt<Type> operator-(const c3DVt &lpValue)const;	   
	   c3DVt<Type> operator-(const Type *lpValue)const;
	   c3DVt<Type> operator-(Type lpValue)const;
				   
	   c3DVt<Type> operator+(const c3DVt &lpValue)const;
	   c3DVt<Type> operator+(const Type *lpValue)const;
	   c3DVt<Type> operator+(Type lpValue)const;

       ///Will Find the cross Product of this vector and the vector lpValue.
	   c3DVt<Type> operator*(const c3DVt &lpValue)const;
	   c3DVt<Type> operator*(const Type *lpValue)const;
	   c3DVt<Type> operator*(Type lpValue)const;

	   c3DVt<Type> operator/(const c3DVt &lpValue)const;
	   c3DVt<Type> operator/(const Type *lpValue)const;
	   c3DVt<Type> operator/(Type lpValue)const;

	   bool operator==(const Type *lpValue)const;
	   bool operator==(const c3DVt &lpValue)const;




	   ///Will Findthe Dot Product of this vector and the vector lpValue.
       Type Dot(const c3DVt &lpValue) const;
	   Type Dot(const Type *lpValue) const;	   

	   float Angle(const c3DVt &lpOther) const;

	   ///Allows the User to access the components as if an array of values.
       Type &operator[](uint32 liPos);
	   const Type &operator[](uint32 liPos) const;

	   ///This will invert this vector (multiply each component by -1.0f).
	   c3DVt<Type> Invert();

	   void Yaw(float lfAngle);

};


#endif
