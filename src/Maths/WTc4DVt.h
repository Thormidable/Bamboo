#ifndef __WTC4DVF_H__
#define __WTC4DVF_H__

class cRGB;
class cRGBA;

/// This is a 4 dimensional float vector object
template<class Type> class c4DVt
{
public:
	Type v[4];

	///Return this Vectors X Value
	Type X();
	///Return this Vectors Y Value
	Type Y();
	///Return this Vectors Z Value
	Type Z();
	///Return this Vectors W Value
	Type W();

	///Set this Vectors X Value
	void X(Type lfX);
	///Set this Vectors Y Value
	void Y(Type lfY);
	///Set this Vectors Z Value
	void Z(Type lfZ);
	///Set this Vectors W Value
	void W(Type lfZ);


	/// This will return the absolute size of this vector.
       Type Magnitude();
	/// This will make the magnitude of this vector 1 while maintaining its direction.
       void Normalise();

		///Constructor to allow the User to initialise 0-4 components
        c4DVt(Type lf0=0,Type lf1=0,Type lf2=0,Type lf3=0);
		///Constructor to initialise the object from an array of three Types.
        c4DVt(Type *lf0);

       c4DVt<Type> operator=(c4DVt *lpValue);
       c4DVt<Type> operator=(c4DVt &lpValue);
       c4DVt<Type> operator=(c4DVt lpValue);
       c4DVt<Type> operator=(cRGBA *lpValue);
       c4DVt<Type> operator=(cRGBA &lpValue);
       Type *operator=(Type *lpValue);

       c4DVt<Type> operator+=(c4DVt &lpValue);
       c4DVt<Type> operator+=(c4DVt *lpValue);
       c4DVt<Type> operator+=(Type *lpValue);

       c4DVt<Type> operator-=(c4DVt &lpValue);
       c4DVt<Type> operator-=(c4DVt *lpValue);
       c4DVt<Type> operator-=(Type *lpValue);

       c4DVt<Type> operator-(c4DVt &lpValue);
       c4DVt<Type> operator-(c4DVt *lpValue);
       c4DVt<Type> operator-(Type *lpValue);

       c4DVt<Type> operator+(c4DVt &lpValue);
       c4DVt<Type> operator+(c4DVt *lpValue);
       c4DVt<Type> operator+(Type *lpValue);
/*
       ///Will Find the cross Product of this vector and the vector lpValue.
       c4DVt<Type> operator*(c4DVt &lpValue);
       c4DVt<Type> operator*(c4DVt *lpValue);
       c4DVt<Type> operator*(Type *lpValue);
*/

	   ///Will Findthe Dot Product of this vector and the vector lpValue.
       Type Dot(c4DVt &lpValue);
       Type Dot(Type *lpValue);
       Type Dot(c4DVt *lpValue);


	   ///Allows the User to access the components as if an array of values.
       Type &operator[](uint32 liPos);
        c4DVt(c4DVt *lfVect);
        c4DVt(const c4DVt &lfVect);
};
#endif
