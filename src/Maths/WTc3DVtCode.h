//#include "../WTBamboo.h"

template<class Type> c3DVt<Type>::c3DVt(Type lf0,Type lf1,Type lf2)
{
 v[0]=lf0;
 v[1]=lf1;
 v[2]=lf2;
}
template<class Type> c3DVt<Type>::c3DVt(Type *lf0){memcpy(v,lf0,sizeof(Type)*3);}
template<class Type> c3DVt<Type>::c3DVt(const c3DVt<Type> &lfVect){ memcpy(v,lfVect.v,sizeof(Type)*3);};

template<class Type> Type c3DVt<Type>::Magnitude()const
{
 return sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

template<class Type> void c3DVt<Type>::Normalise()
{
 Type lfDiv;
 lfDiv=1.0f/Magnitude();
 v[0]=v[0]*lfDiv;
 v[1]=v[1]*lfDiv;
 v[2]=v[2]*lfDiv;
}

template<class Type> bool c3DVt<Type>::operator==(const Type *lpValue)const
{
    if(v[0]<lpValue[0]+0.0001f && v[0]>lpValue[0]-0.0001f &&
       v[1]<lpValue[1]+0.0001f && v[1]>lpValue[1]-0.0001f &&
       v[2]<lpValue[2]+0.0001f && v[2]>lpValue[2]-0.0001f) return 1;
    return 0;
};

template<class Type> bool c3DVt<Type>::operator==(const c3DVt<Type> &lpValue)const
{
if(v[0]<lpValue[0]+0.0001f && v[0]>lpValue[0]-0.0001f &&
       v[1]<lpValue[1]+0.0001f && v[1]>lpValue[1]-0.0001f &&
       v[2]<lpValue[2]+0.0001f && v[2]>lpValue[2]-0.0001f) return 1;
    return 0;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator*(const c3DVt<Type> &lvOther)const
{
	c3DVt<Type> lvReturn(*this);
	return lvReturn *= lvOther;
}
template<class Type> c3DVt<Type> c3DVt<Type>::operator*(const Type *lfV)const
{
 c3DVt<Type> lvReturn(*this);
 return lvReturn *= lfV;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator*(Type lpValue)const
{
	c3DVt<Type> lvReturn(*this);
	return lvReturn *= lpValue;
};

template<class Type> c3DVt<Type> &c3DVt<Type>::operator*=(const c3DVt<Type> &lvOther)
{
	c3DVt<Type> lvReturn;
	lvReturn.v[0] = v[1] * lvOther.v[2] - v[2] * lvOther.v[1];
	lvReturn.v[1] = v[2] * lvOther.v[0] - v[0] * lvOther.v[2];
	lvReturn.v[2] = v[0] * lvOther.v[1] - v[1] * lvOther.v[0];
	memcpy(v, lvReturn.v, sizeof(Type) * 3);
	return *this;
}
template<class Type> c3DVt<Type> &c3DVt<Type>::operator*=(const Type *lfV)
{
 c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[1]*lfV[2]-v[2]*lfV[1];
 lvReturn.v[1]=v[2]*lfV[0]-v[0]*lfV[2];
 lvReturn.v[2]=v[0]*lfV[1]-v[1]*lfV[0];
 memcpy(v,lvReturn.v,sizeof(Type)*3);
 return *this;
};

template<class Type> c3DVt<Type> &c3DVt<Type>::operator*=(const Type lpValue)
{
  c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]*lpValue;
 lvReturn.v[1]=v[1]*lpValue;
 lvReturn.v[2]=v[2]*lpValue;
 memcpy(v,lvReturn.v,sizeof(Type)*3);
 return *this;
};

template<class Type> Type &c3DVt<Type>::operator[](uint32 liPos){return v[liPos];};
template<class Type> const Type &c3DVt<Type>::operator[](uint32 liPos) const{ return v[liPos]; };

template<class Type> c3DVt<Type> &c3DVt<Type>::operator=(const c3DVt<Type> &lpValue)
{
 memcpy(v,lpValue.v,3*sizeof(Type));
 return *this;
}

template<class Type> c3DVt<Type> &c3DVt<Type>::operator=(const Type *lpValue)
{
 memcpy(v,lpValue,3*sizeof(Type));
 return *this;
}

template<class Type> c3DVt<Type> &c3DVt<Type>::operator=(const cRGB lpValue)
{
 memcpy(v,lpValue->Color(),sizeof(Type)*3);
 return *this;
}

template<class Type> c3DVt<Type> &c3DVt<Type>::operator=(const cRGB &lpValue)
{
 memcpy(v,lpValue.Color(),sizeof(Type)*3);
 return *this;
}


template<class Type> c3DVt<Type> &c3DVt<Type>::operator+=(const Type *lpValue)
{
 v[0]+=lpValue[0];
 v[1]+=lpValue[1];
 v[2]+=lpValue[2];
 return *this;
}

template<class Type> c3DVt<Type> &c3DVt<Type>::operator+=(const c3DVt<Type> &lpValue)
{
	v[0] += lpValue.v[0];
	v[1] += lpValue.v[1];
	v[2] += lpValue.v[2];
 return *this;
}

template<class Type> Type c3DVt<Type>::Dot(const Type *lpValue)const
{
	return v[0]*lpValue[0]+v[1]*lpValue[1]+v[2]*lpValue[2];
}

template<class Type> Type c3DVt<Type>::Dot(const c3DVt<Type> &lpValue)const
{
	return v[0]*lpValue.v[0]+v[1]*lpValue.v[1]+v[2]*lpValue.v[2];
}


	template<class Type> Type c3DVt<Type>::X()const {return v[0];};
	template<class Type> Type c3DVt<Type>::Y()const {return v[1];};
	template<class Type> Type c3DVt<Type>::Z()const {return v[2];};

	template<class Type> void c3DVt<Type>::X(Type lfX){v[0]=lfX;};
	template<class Type> void c3DVt<Type>::Y(Type lfY){v[1]=lfY;};
	template<class Type> void c3DVt<Type>::Z(Type lfZ){v[2]=lfZ;};

	template<class Type> c3DVt<Type> c3DVt<Type>::operator/(const Type *lpValue)const
		{
			c3DVt<Type> lvReturn(*this);
			return lvReturn /= lpValue;
		};

	template<class Type> c3DVt<Type> c3DVt<Type>::operator/(const Type lpValue)const
		{
			c3DVt<Type> lvReturn(*this);
			return lvReturn /= lpValue;
		};

	template<class Type> c3DVt<Type> c3DVt<Type>::operator/(const c3DVt &lpValue)const
	   {
		   c3DVt<Type> lvReturn(*this);
		   return lvReturn /= lpValue;
		};

	template<class Type> c3DVt<Type> &c3DVt<Type>::operator/=(const Type *lpValue)
		{
			v[0]/=lpValue[0];
			v[1]/=lpValue[1];
			v[2]/=lpValue[2];
			return *this;
		};

	template<class Type> c3DVt<Type> &c3DVt<Type>::operator/=(const Type lpValue)
		{
			v[0]/=lpValue;
			v[1]/=lpValue;
			v[2]/=lpValue;
			return *this;
		};

	template<class Type> c3DVt<Type> &c3DVt<Type>::operator/=(const c3DVt &lpValue)
	   {
			v[0]/=lpValue.v[0];
			v[1]/=lpValue.v[1];
			v[2]/=lpValue.v[2];
			return *this;
		};

	template<class Type> c3DVt<Type> c3DVt<Type>::operator+(const c3DVt<Type> &lvOther)const
{
	c3DVt<Type> lvReturn(*this);
	return lvReturn += lvOther;
};

	template<class Type> c3DVt<Type> c3DVt<Type>::operator+(const Type *lvOther)const
{
	c3DVt<Type> lvReturn(*this);
	return lvReturn += lvOther;
};

	template<class Type> c3DVt<Type> c3DVt<Type>::operator+(const Type lvOther)const
{
	c3DVt<Type> lvReturn(*this);
	return lvReturn += lvOther;
};


	template<class Type> c3DVt<Type> c3DVt<Type>::operator-(const c3DVt<Type> &lvOther)const
{
	c3DVt<Type> lvReturn(*this);
	return lvReturn -= lvOther;
};

	template<class Type> c3DVt<Type> c3DVt<Type>::operator-(const Type *lvOther)const
{
	c3DVt<Type> lvReturn(*this);
	return lvReturn -= lvOther;
};

	template<class Type> c3DVt<Type> c3DVt<Type>::operator-(const Type lvOther)const
{
	c3DVt<Type> lvReturn(*this);
	return lvReturn -= lvOther;
};

	template<class Type> c3DVt<Type> &c3DVt<Type>::operator-=(const Type *lpValue)
{
 v[0]-=lpValue[0];
 v[1]-=lpValue[1];
 v[2]-=lpValue[2];
 return *this;
}

	template<class Type> c3DVt<Type> &c3DVt<Type>::operator-=(const c3DVt<Type> &lpValue)
{
	v[0] -= lpValue.v[0];
	v[1] -= lpValue.v[1];
	v[2] -= lpValue.v[2];
 return *this;
}

template<class Type> Type c3DVt<Type>::Distance(const c3DVt<Type> &lpOther)const
{
 c3DVf lpTemp(v);
 lpTemp-=lpOther;
 return lpTemp.Magnitude();
};

template<class Type> Type c3DVt<Type>::Distance(const Type *lpOther)const
{
 c3DVf lpTemp(v);
 lpTemp-=lpOther;
 return lpTemp.Magnitude();
};

template<class Type> Type c3DVt<Type>::DistanceSq(const c3DVt<Type> &lpOther)const
{
 c3DVf lpTemp(v);
 lpTemp-=lpOther;
 return lpTemp.MagnitudeSq();
};

template<class Type> Type c3DVt<Type>::DistanceSq(const Type *lpOther)const
{
 c3DVf lpTemp(v);
 lpTemp-=lpOther;
 return lpTemp.MagnitudeSq();
};;


template<class Type> Type c3DVt<Type>::MagnitudeSq()const
{
    return v[0]*v[0]+v[1]*v[1]+v[2]*v[2];
};


template<class Type> c3DVt<Type> c3DVt<Type>::Invert()
{
 v[0]=-v[0];
 v[1]=-v[1];
 v[2]=-v[2];
 return *this;
};

template<class Type> float c3DVt<Type>::Angle(const c3DVt &lpOther)const
{
    return acos(Dot(lpOther)/(lpOther.Magnitude()*Magnitude()));
};

template<class Type> void c3DVt<Type>::Yaw(float lfAngle)
{
    float lfCos=cos(lfAngle);
    float lfSin=sin(lfAngle);

    float lfX,lfZ;

    lfX=lfCos*v[0]-lfSin*v[2];
    lfZ=lfSin*v[0]+lfCos*v[2];

    v[0]=lfX;
    v[2]=lfZ;

}

