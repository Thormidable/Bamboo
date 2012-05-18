//#include "../WTBamboo.h"

template<class Type> c2DVt<Type>::c2DVt(Type lf0,Type lf1)
{
 v[0]=lf0;
 v[1]=lf1;
}
template<class Type> c2DVt<Type>::c2DVt(Type *lf0){memcpy(v,lf0,sizeof(Type)*2);}
template<class Type> c2DVt<Type>::c2DVt(const c2DVt<Type> &lfVect){ memcpy(v,lfVect.v,sizeof(Type)*2);};
template<class Type> c2DVt<Type>::c2DVt(c2DVt<Type> *lfVect){ memcpy(v,lfVect->v,sizeof(Type)*2);};


template<class Type> Type c2DVt<Type>::Magnitude()
{
 return sqrt(v[0]*v[0]+v[1]*v[1]);
}

template<class Type> void c2DVt<Type>::Normalise()
{
 Type lfDiv;
 lfDiv=1.0f/Magnitude();
 v[0]=v[0]*lfDiv;
 v[1]=v[1]*lfDiv;
}

template<class Type> Type &c2DVt<Type>::operator[](uint32 liPos){return v[liPos];};

template<class Type> c2DVt<Type> c2DVt<Type>::operator=(c2DVt<Type> *lpValue)
{
 memcpy(v,lpValue->v,2*sizeof(Type));
 return *this;
}


template<class Type> c2DVt<Type> c2DVt<Type>::operator=(c2DVt<Type> lpValue)
{
 memcpy(v,lpValue.v,2*sizeof(Type));
 return *this;
}


template<class Type> Type *c2DVt<Type>::operator=(Type *lpValue)
{
 memcpy(v,lpValue,2*sizeof(Type));
 return lpValue;
}

template<class Type> Type c2DVt<Type>::operator=(Type lpValue)
{
 v[0]=lpValue;
 v[1]=lpValue;
 return lpValue;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator+=(Type *lpValue)
{
 v[0]+=lpValue[0];
 v[1]+=lpValue[1];
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator+=(Type lpValue)
{
 v[0]+=lpValue;
 v[1]+=lpValue;
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator+=(c2DVt<Type> lpValue)
{
 v[0]+=lpValue.v[0];
 v[1]+=lpValue.v[1];
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator+=(c2DVt<Type> *lpValue)
{
 v[0]+=lpValue->v[0];
 v[1]+=lpValue->v[1];
 return *this;
}



template<class Type> c2DVt<Type> c2DVt<Type>::operator*=(Type *lpValue)
{
 v[0]*=lpValue[0];
 v[1]*=lpValue[1];
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator*=(Type lpValue)
{
 v[0]*=lpValue;
 v[1]*=lpValue;
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator*=(c2DVt<Type> lpValue)
{
 v[0]*=lpValue.v[0];
 v[1]*=lpValue.v[1];
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator*=(c2DVt<Type> *lpValue)
{
 v[0]*=lpValue->v[0];
 v[1]*=lpValue->v[1];
 return *this;
}


template<class Type> c2DVt<Type> c2DVt<Type>::operator/=(Type *lpValue)
{
 v[0]/=lpValue[0];
 v[1]/=lpValue[1];
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator/=(Type lpValue)
{
 v[0]/=lpValue;
 v[1]/=lpValue;
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator/=(c2DVt<Type> lpValue)
{
 v[0]/=lpValue.v[0];
 v[1]/=lpValue.v[1];
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator/=(c2DVt<Type> *lpValue)
{
 v[0]/=lpValue->v[0];
 v[1]/=lpValue->v[1];
 return *this;
}

template<class Type> Type c2DVt<Type>::Dot(c2DVt<Type> lpValue)
{
	return v[0]*lpValue.v[0]+v[1]*lpValue.v[1];
}

template<class Type> Type c2DVt<Type>::Dot(Type *lpValue)
{
	return v[0]*lpValue[0]+v[1]*lpValue[1];
}

template<class Type> Type c2DVt<Type>::Dot(c2DVt<Type> *lpValue)
{
	return v[0]*lpValue->v[0]+v[1]*lpValue->v[1];
}

	template<class Type> Type c2DVt<Type>::X(){return v[0];};
	template<class Type> Type c2DVt<Type>::Y(){return v[1];};

	template<class Type> void c2DVt<Type>::X(Type lfX){v[0]=lfX;};
	template<class Type> void c2DVt<Type>::Y(Type lfY){v[1]=lfY;};




template<class Type> c2DVt<Type> c2DVt<Type>::operator+(c2DVt<Type> *lvOther)
{
   c2DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther->v[0];
 lvReturn.v[1]=v[1]+lvOther->v[1];
 return lvReturn;
};

template<class Type> c2DVt<Type> c2DVt<Type>::operator+(c2DVt<Type> lvOther)
{
   c2DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther.v[0];
 lvReturn.v[1]=v[1]+lvOther.v[1];
 return lvReturn;
};

template<class Type> c2DVt<Type> c2DVt<Type>::operator+(Type *lvOther)
{
   c2DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther[0];
 lvReturn.v[1]=v[1]+lvOther[1];
 return lvReturn;
};

template<class Type> c2DVt<Type> c2DVt<Type>::operator+(Type lvOther)
{
   c2DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther;
 lvReturn.v[1]=v[1]+lvOther;
 return lvReturn;
};


template<class Type> c2DVt<Type> c2DVt<Type>::operator-(c2DVt<Type> *lvOther)
{
   c2DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther->v[0];
 lvReturn.v[1]=v[1]-lvOther->v[1];
 return lvReturn;
};

template<class Type> c2DVt<Type> c2DVt<Type>::operator-(c2DVt<Type> lvOther)
{
   c2DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther.v[0];
 lvReturn.v[1]=v[1]-lvOther.v[1];
 return lvReturn;
};

template<class Type> c2DVt<Type> c2DVt<Type>::operator-(Type *lvOther)
{
   c2DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther[0];
 lvReturn.v[1]=v[1]-lvOther[1];
 return lvReturn;
};

template<class Type> c2DVt<Type> c2DVt<Type>::operator-(Type lvOther)
{
   c2DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther;
 lvReturn.v[1]=v[1]-lvOther;
 return lvReturn;
};

template<class Type> c2DVt<Type> c2DVt<Type>::Perpendicular()
{
 c2DVt<Type> lvReturn;
 lvReturn.v[0]=-v[1];
 lvReturn.v[1]=v[0];
 return lvReturn;
};


template<class Type> c2DVt<Type> c2DVt<Type>::PerpendicularLH()
{
 c2DVt<Type> lvReturn;
 lvReturn.v[0]=-v[1];
 lvReturn.v[1]=v[0];
 return lvReturn;
};


template<class Type> c2DVt<Type> c2DVt<Type>::PerpendicularRH()
{
 c2DVt<Type> lvReturn;
 lvReturn.v[0]=v[1];
 lvReturn.v[1]=-v[0];
 return lvReturn;
};

template<class Type> float c2DVt<Type>::Angle(c2DVt<Type> lpOther)
{
    float lfBase=Magnitude()*lpOther.Magnitude();
    if(lfBase!=0.0f) return acos((Dot(lpOther))/(lfBase));
    return 0.0f;
}

template<class Type> float c2DVt<Type>::SignedAngle(c2DVt<Type> lpOther)
{
    float lf1=atan2(v[1],v[0]);
    float lf2=atan2(lpOther.v[1],lpOther.v[0]);
    lf1=lf2-lf1;

    if(lf1>(2*WT_PI)) lf1-=2*WT_PI;
    if(lf1<-(2*WT_PI)) lf1+=2*WT_PI;

    return lf1;
}

template<class Type> bool c2DVt<Type>::operator==(c2DVt *lpValue)
{
   return(v[0]<lpValue->X()+0.0001f && v[0]>lpValue->X()-0.0001f &&
       v[1]<lpValue->Y()+0.0001f && v[1]>lpValue->Y()-0.0001f);
};

template<class Type> bool c2DVt<Type>::operator==(c2DVt lpValue)
{
   return(v[0]<lpValue[0]+0.0001f && v[0]>lpValue[0]-0.0001f &&
       v[1]<lpValue[1]+0.0001f && v[1]>lpValue[1]-0.0001f);
};







template<class Type> c2DVt<Type> c2DVt<Type>::operator-=(Type *lpValue)
{
 v[0]-=lpValue[0];
 v[1]-=lpValue[1];
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator-=(Type lpValue)
{
 v[0]-=lpValue;
 v[1]-=lpValue;
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator-=(c2DVt<Type> lpValue)
{
 v[0]-=lpValue.v[0];
 v[1]-=lpValue.v[1];
 return *this;
}

template<class Type> c2DVt<Type> c2DVt<Type>::operator-=(c2DVt<Type> *lpValue)
{
 v[0]-=lpValue->v[0];
 v[1]-=lpValue->v[1];
 return *this;
}

template<class Type> Type c2DVt<Type>::MagnitudeSq()
{
    return v[0]*v[0]+v[1]*v[1];
};


	   template<class Type> c2DVt<Type> c2DVt<Type>::operator*(c2DVt lpValue)
	   {
		 c2DVt<Type> lfTemp;
		 lfTemp[0]=v[0]*lpValue[0];
		 lfTemp[1]=v[1]*lpValue[1];
		 lfTemp[2]=v[2]*lpValue[2];
		 return lfTemp;
	   };
       template<class Type> c2DVt<Type> c2DVt<Type>::operator*(c2DVt *lpValue)
	   {
		 c2DVt<Type> lfTemp;
		 lfTemp[0]=v[0]*lpValue[0];
		 lfTemp[1]=v[1]*lpValue[1];
		 lfTemp[2]=v[2]*lpValue[2];
		 return lfTemp;
	   };
       template<class Type> c2DVt<Type> c2DVt<Type>::operator*(Type *lpValue)
	   	   {
		 c2DVt<Type> lfTemp;
		 lfTemp[0]=v[0]*lpValue[0];
		 lfTemp[1]=v[1]*lpValue[1];
		 lfTemp[2]=v[2]*lpValue[2];
		 return lfTemp;
	   };
	   template<class Type> c2DVt<Type> c2DVt<Type>::operator*(Type lpValue)
	   {
		 c2DVt<Type> lfTemp;
		 lfTemp[0]=v[0]*lpValue;
		 lfTemp[1]=v[1]*lpValue;
		 lfTemp[2]=v[2]*lpValue;
		 return lfTemp;
	   };

	   template<class Type> c2DVt<Type> c2DVt<Type>::operator/(c2DVt lpValue)
	   {
		 c2DVt<Type> lfTemp;
		 lfTemp[0]=v[0]/lpValue[0];
		 lfTemp[1]=v[1]/lpValue[1];
		 lfTemp[2]=v[2]/lpValue[2];
		 return lfTemp;
	   };
       template<class Type> c2DVt<Type> c2DVt<Type>::operator/(c2DVt *lpValue)
	   {
		 c2DVt<Type> lfTemp;
		 lfTemp[0]=v[0]/lpValue[0];
		 lfTemp[1]=v[1]/lpValue[1];
		 lfTemp[2]=v[2]/lpValue[2];
		 return lfTemp;
	   };

       template<class Type> c2DVt<Type> c2DVt<Type>::operator/(Type *lpValue)
	   {
		 c2DVt<Type> lfTemp;
		 lfTemp[0]=v[0]/lpValue[0];
		 lfTemp[1]=v[1]/lpValue[1];
		 lfTemp[2]=v[2]/lpValue[2];
		 return lfTemp;
	   };
	   template<class Type> c2DVt<Type> c2DVt<Type>::operator/(Type lpValue)
	   {
		 c2DVt<Type> lfTemp;
		 lfTemp[0]=v[0]/lpValue;
		 lfTemp[1]=v[1]/lpValue;
		 lfTemp[2]=v[2]/lpValue;
		 return lfTemp;
	   };

	   template<class Type> void c2DVt<Type>::Equals(c2DVt *lpValue)
	   {
		v[0]=lpValue->X();
		v[1]=lpValue->Y();
	   };

       template<class Type> void c2DVt<Type>::Equals(c2DVt lpValue)
	   {
		v[0]=lpValue.X();
		v[1]=lpValue.Y();
	   };


       template<class Type> void c2DVt<Type>::Equals(Type *lpValue)
	   {
		v[0]=lpValue[0];
		v[1]=lpValue[1];
	   };

	   template<class Type> void c2DVt<Type>::Equals(Type lpValue)
	   {
		v[0]=lpValue;
		v[1]=lpValue;
	   };
