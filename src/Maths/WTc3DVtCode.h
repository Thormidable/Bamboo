//#include "../WTBamboo.h"

template<class Type> c3DVt<Type>::c3DVt(Type lf0,Type lf1,Type lf2)
{
 v[0]=lf0;
 v[1]=lf1;
 v[2]=lf2;
}
template<class Type> c3DVt<Type>::c3DVt(Type *lf0){memcpy(v,lf0,sizeof(Type)*3);}
template<class Type> c3DVt<Type>::c3DVt(const c3DVt<Type> &lfVect){ memcpy(v,lfVect.v,sizeof(Type)*3);};
template<class Type> c3DVt<Type>::c3DVt(c3DVt<Type> *lfVect){ memcpy(v,lfVect->v,sizeof(Type)*3);};


template<class Type> Type c3DVt<Type>::Magnitude()
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

template<class Type> bool c3DVt<Type>::operator==(Type *lpValue)
{
    if(v[0]<lpValue[0]+0.0001f && v[0]>lpValue[0]-0.0001f &&
       v[1]<lpValue[1]+0.0001f && v[1]>lpValue[1]-0.0001f &&
       v[2]<lpValue[2]+0.0001f && v[2]>lpValue[2]-0.0001f) return 1;
    return 0;
};
template<class Type> bool c3DVt<Type>::operator==(c3DVt<Type> lpValue)
{
if(v[0]<lpValue[0]+0.0001f && v[0]>lpValue[0]-0.0001f &&
       v[1]<lpValue[1]+0.0001f && v[1]>lpValue[1]-0.0001f &&
       v[2]<lpValue[2]+0.0001f && v[2]>lpValue[2]-0.0001f) return 1;
    return 0;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator*(c3DVt<Type> *lvOther)
{
   c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[1]*lvOther->v[2]-v[2]*lvOther->v[1];
 lvReturn.v[1]=v[2]*lvOther->v[0]-v[0]*lvOther->v[2];
 lvReturn.v[2]=v[0]*lvOther->v[1]-v[1]*lvOther->v[0];
 return lvReturn;
};
template<class Type> c3DVt<Type> c3DVt<Type>::operator*(c3DVt<Type> lvOther)
{
 c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[1]*lvOther.v[2]-v[2]*lvOther.v[1];
 lvReturn.v[1]=v[2]*lvOther.v[0]-v[0]*lvOther.v[2];
 lvReturn.v[2]=v[0]*lvOther.v[1]-v[1]*lvOther.v[0];
 return lvReturn;
}
template<class Type> c3DVt<Type> c3DVt<Type>::operator*(Type *lfV)
{
 c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[1]*lfV[2]-v[2]*lfV[1];
 lvReturn.v[1]=v[2]*lfV[0]-v[0]*lfV[2];
 lvReturn.v[2]=v[0]*lfV[1]-v[1]*lfV[0];
 return lvReturn;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator*(Type lpValue)
{
  c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]*lpValue;
 lvReturn.v[1]=v[1]*lpValue;
 lvReturn.v[2]=v[2]*lpValue;
 return lvReturn;
};


template<class Type> c3DVt<Type> c3DVt<Type>::operator*=(c3DVt<Type> *lvOther)
{
   c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[1]*lvOther->v[2]-v[2]*lvOther->v[1];
 lvReturn.v[1]=v[2]*lvOther->v[0]-v[0]*lvOther->v[2];
 lvReturn.v[2]=v[0]*lvOther->v[1]-v[1]*lvOther->v[0];
 memcpy(v,lvReturn.v,sizeof(Type)*3);
 return *this;
};
template<class Type> c3DVt<Type> c3DVt<Type>::operator*=(c3DVt<Type> lvOther)
{
 c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[1]*lvOther.v[2]-v[2]*lvOther.v[1];
 lvReturn.v[1]=v[2]*lvOther.v[0]-v[0]*lvOther.v[2];
 lvReturn.v[2]=v[0]*lvOther.v[1]-v[1]*lvOther.v[0];
 memcpy(v,lvReturn.v,sizeof(Type)*3);
 return *this;
}
template<class Type> c3DVt<Type> c3DVt<Type>::operator*=(Type *lfV)
{
 c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[1]*lfV[2]-v[2]*lfV[1];
 lvReturn.v[1]=v[2]*lfV[0]-v[0]*lfV[2];
 lvReturn.v[2]=v[0]*lfV[1]-v[1]*lfV[0];
 memcpy(v,lvReturn.v,sizeof(Type)*3);
 return *this;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator*=(Type lpValue)
{
  c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]*lpValue;
 lvReturn.v[1]=v[1]*lpValue;
 lvReturn.v[2]=v[2]*lpValue;
 memcpy(v,lvReturn.v,sizeof(Type)*3);
 return *this;
};

template<class Type> Type &c3DVt<Type>::operator[](uint32 liPos){return v[liPos];};

template<class Type> c3DVt<Type> c3DVt<Type>::operator=(c3DVt<Type> *lpValue)
{
 memcpy(v,lpValue->v,3*sizeof(Type));
 return *this;
}
/*
template<class Type> c3DVt<Type> c3DVt<Type>::operator=(c3DVt<Type> &lpValue)
{
 memcpy(v,lpValue.v,3*sizeof(Type));
 return *this;
}*/

template<class Type> c3DVt<Type> c3DVt<Type>::operator=(c3DVt<Type> lpValue)
{
 memcpy(v,lpValue.v,3*sizeof(Type));
 return *this;
}


template<class Type> Type *c3DVt<Type>::operator=(Type *lpValue)
{
 memcpy(v,lpValue,3*sizeof(Type));
 return lpValue;
}

template<class Type> c3DVt<Type> c3DVt<Type>::operator=(cRGB *lpValue)
{
 memcpy(v,lpValue->Color(),sizeof(Type)*3);
 return *this;
}

template<class Type> c3DVt<Type> c3DVt<Type>::operator=(cRGB &lpValue)
{
 memcpy(v,lpValue.Color(),sizeof(Type)*3);
 return *this;
}


template<class Type> c3DVt<Type> c3DVt<Type>::operator+=(Type *lpValue)
{
 v[0]+=lpValue[0];
 v[1]+=lpValue[1];
 v[2]+=lpValue[2];
 return *this;
}

template<class Type> c3DVt<Type> c3DVt<Type>::operator+=(c3DVt<Type> lpValue)
{
 v[0]+=lpValue.v[0];
 v[1]+=lpValue.v[1];
 v[2]+=lpValue.v[2];
 return *this;
}

template<class Type> c3DVt<Type> c3DVt<Type>::operator+=(c3DVt<Type> *lpValue)
{
 v[0]+=lpValue->v[0];
 v[1]+=lpValue->v[1];
 v[2]+=lpValue->v[2];
 return *this;
}

template<class Type> Type c3DVt<Type>::Dot(c3DVt<Type> lpValue)
{
	return v[0]*lpValue.v[0]+v[1]*lpValue.v[1]+v[2]*lpValue.v[2];
}

template<class Type> Type c3DVt<Type>::Dot(Type *lpValue)
{
	return v[0]*lpValue[0]+v[1]*lpValue[1]+v[2]*lpValue[2];
}

template<class Type> Type c3DVt<Type>::Dot(c3DVt<Type> *lpValue)
{
	return v[0]*lpValue->v[0]+v[1]*lpValue->v[1]+v[2]*lpValue->v[2];
}


	template<class Type> Type c3DVt<Type>::X(){return v[0];};
	template<class Type> Type c3DVt<Type>::Y(){return v[1];};
	template<class Type> Type c3DVt<Type>::Z(){return v[2];};

	template<class Type> void c3DVt<Type>::X(Type lfX){v[0]=lfX;};
	template<class Type> void c3DVt<Type>::Y(Type lfY){v[1]=lfY;};
	template<class Type> void c3DVt<Type>::Z(Type lfZ){v[2]=lfZ;};

		template<class Type> c3DVt<Type> c3DVt<Type>::operator/(Type *lpValue)
		{
		    c3DVt<Type> lfReturn;
			lfReturn.v[0]=v[0]/lpValue[0];
			lfReturn.v[1]=v[1]/lpValue[1];
			lfReturn.v[2]=v[2]/lpValue[2];
			return lfReturn;
		};

		template<class Type> c3DVt<Type> c3DVt<Type>::operator/(Type lpValue)
		{
		    c3DVt<Type> lfReturn;
			lfReturn.v[0]=v[0]/lpValue;
			lfReturn.v[1]=v[1]/lpValue;
			lfReturn.v[2]=v[2]/lpValue;
			return lfReturn;
		};

	   template<class Type> c3DVt<Type> c3DVt<Type>::operator/(c3DVt lpValue)
	   {
	       c3DVt<Type> lfReturn;
			lfReturn.v[0]=v[0]/lpValue.v[0];
			lfReturn.v[1]=v[1]/lpValue.v[1];
			lfReturn.v[2]=v[2]/lpValue.v[2];
			return lfReturn;
		};
	   template<class Type> c3DVt<Type> c3DVt<Type>::operator/(c3DVt *lpValue)
	   {
	       c3DVt<Type> lfReturn;
			lfReturn.v[0]=v[0]/lpValue.v[0];
			lfReturn.v[1]=v[1]/lpValue.v[1];
			lfReturn.v[2]=v[2]/lpValue.v[2];
			return lfReturn;
		};

        template<class Type> c3DVt<Type> c3DVt<Type>::operator/=(Type *lpValue)
		{
			v[0]/=lpValue[0];
			v[1]/=lpValue[1];
			v[2]/=lpValue[2];
			return *this;
		};

		template<class Type> c3DVt<Type> c3DVt<Type>::operator/=(Type lpValue)
		{
			v[0]/=lpValue;
			v[1]/=lpValue;
			v[2]/=lpValue;
			return *this;
		};

	   template<class Type> c3DVt<Type> c3DVt<Type>::operator/=(c3DVt lpValue)
	   {
			v[0]/=lpValue.v[0];
			v[1]/=lpValue.v[1];
			v[2]/=lpValue.v[2];
			return *this;
		};
	   template<class Type> c3DVt<Type> c3DVt<Type>::operator/=(c3DVt *lpValue)
	   {
			v[0]/=lpValue.v[0];
			v[1]/=lpValue.v[1];
			v[2]/=lpValue.v[2];
			return *this;
		};






template<class Type> c3DVt<Type> c3DVt<Type>::operator+(c3DVt<Type> *lvOther)
{
   c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther->v[0];
 lvReturn.v[1]=v[1]+lvOther->v[1];
 lvReturn.v[2]=v[2]+lvOther->v[2];
 return lvReturn;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator+(c3DVt<Type> lvOther)
{
   c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther.v[0];
 lvReturn.v[1]=v[1]+lvOther.v[1];
 lvReturn.v[2]=v[2]+lvOther.v[2];
 return lvReturn;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator+(Type *lvOther)
{
   c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther[0];
 lvReturn.v[1]=v[1]+lvOther[1];
 lvReturn.v[2]=v[2]+lvOther[2];
 return lvReturn;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator+(Type lvOther)
{
   c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther;
 lvReturn.v[1]=v[1]+lvOther;
 lvReturn.v[2]=v[2]+lvOther;
 return lvReturn;
};


template<class Type> c3DVt<Type> c3DVt<Type>::operator-(c3DVt<Type> *lvOther)
{
   c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther->v[0];
 lvReturn.v[1]=v[1]-lvOther->v[1];
 lvReturn.v[2]=v[2]-lvOther->v[2];
 return lvReturn;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator-(c3DVt<Type> lvOther)
{
   c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther.v[0];
 lvReturn.v[1]=v[1]-lvOther.v[1];
 lvReturn.v[2]=v[2]-lvOther.v[2];
 return lvReturn;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator-(Type *lvOther)
{
   c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther[0];
 lvReturn.v[1]=v[1]-lvOther[1];
 lvReturn.v[2]=v[2]-lvOther[2];
 return lvReturn;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator-(Type lvOther)
{
   c3DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther;
 lvReturn.v[1]=v[1]-lvOther;
 lvReturn.v[2]=v[2]-lvOther;
 return lvReturn;
};

template<class Type> c3DVt<Type> c3DVt<Type>::operator-=(Type *lpValue)
{
 v[0]-=lpValue[0];
 v[1]-=lpValue[1];
 v[2]-=lpValue[2];
 return *this;
}

template<class Type> c3DVt<Type> c3DVt<Type>::operator-=(c3DVt<Type> lpValue)
{
 v[0]-=lpValue.v[0];
 v[1]-=lpValue.v[1];
 v[2]-=lpValue.v[2];
 return *this;
}

template<class Type> c3DVt<Type> c3DVt<Type>::operator-=(c3DVt<Type> *lpValue)
{
 v[0]-=lpValue->v[0];
 v[1]-=lpValue->v[1];
 v[2]-=lpValue->v[2];
 return *this;
}


template<class Type> Type c3DVt<Type>::MagnitudeSq()
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

template<class Type> float c3DVt<Type>::Angle(c3DVt lpOther)
{
    return acos(Dot(lpOther)/(lpOther.Magnitude()*Magnitude()));
};
