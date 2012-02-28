//#include "../WTBamboo.h"

template<class Type> c4DVt<Type>::c4DVt(Type lf0,Type lf1,Type lf2,Type lf3)
{
 v[0]=lf0;
 v[1]=lf1;
 v[2]=lf2;
 v[3]=lf3;
}
template<class Type> c4DVt<Type>::c4DVt(Type *lf0){memcpy(v,lf0,sizeof(Type)*4);}
template<class Type> c4DVt<Type>::c4DVt(const c4DVt<Type> &lfVect){ memcpy(v,lfVect.v,sizeof(Type)*4);};
template<class Type> c4DVt<Type>::c4DVt(c4DVt<Type> *lfVect){ memcpy(v,lfVect->v,sizeof(Type)*4);};


template<class Type> Type c4DVt<Type>::Magnitude()
{
 return sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
}

template<class Type> void c4DVt<Type>::Normalise()
{
 Type lfDiv;
 lfDiv=1.0f/Magnitude();
 v[0]=v[0]*lfDiv;
 v[1]=v[1]*lfDiv;
 v[2]=v[2]*lfDiv;
 v[3]=v[3]*lfDiv;
}
/*
template<class Type> c4DVt<Type> c4DVt<Type>::operator*(c4DVt<Type> *lvOther)
{
   c4DVt<Type> lvReturn;
 lvReturn.v[0]=v[1]*lvOther->v[2]-v[2]*lvOther->v[1];
 lvReturn.v[1]=v[2]*lvOther->v[0]-v[0]*lvOther->v[2];
 lvReturn.v[2]=v[0]*lvOther->v[1]-v[1]*lvOther->v[0];
 return lvReturn;
};
template<class Type> c4DVt<Type> c4DVt<Type>::operator*(c4DVt<Type> &lvOther)
{
 c4DVt<Type> lvReturn;
 lvReturn.v[0]=v[1]*lvOther.v[2]-v[2]*lvOther.v[1];
 lvReturn.v[1]=v[2]*lvOther.v[0]-v[0]*lvOther.v[2];
 lvReturn.v[2]=v[0]*lvOther.v[1]-v[1]*lvOther.v[0];
 return lvReturn;
}
template<class Type> c4DVt<Type> c4DVt<Type>::operator*(Type *lfV)
{
 c4DVt<Type> lvReturn;
 lvReturn.v[0]=v[1]*lfV[2]-v[2]*lfV[1];
 lvReturn.v[1]=v[2]*lfV[0]-v[0]*lfV[2];
 lvReturn.v[2]=v[0]*lfV[1]-v[1]*lfV[0];
 return lvReturn;
};*/

template<class Type> Type &c4DVt<Type>::operator[](uint32 liPos){return v[liPos];};

template<class Type> c4DVt<Type> c4DVt<Type>::operator=(c4DVt<Type> *lpValue)
{
 memcpy(v,lpValue->v,4*sizeof(Type));
 return lpValue;
}

template<class Type> c4DVt<Type> c4DVt<Type>::operator=(c4DVt<Type> &lpValue)
{
 memcpy(v,lpValue.v,4*sizeof(Type));
 return lpValue;
}

template<class Type> c4DVt<Type> c4DVt<Type>::operator=(c4DVt<Type> lpValue)
{
 memcpy(v,lpValue.v,4*sizeof(Type));
 return *this;
}


template<class Type> Type *c4DVt<Type>::operator=(Type *lpValue)
{
 memcpy(v,lpValue,4*sizeof(Type));
 return lpValue;
}

template<class Type> c4DVt<Type> c4DVt<Type>::operator=(cRGBA *lpValue)
{
 memcpy(v,lpValue->Color(),sizeof(Type)*4);
 return *this;
}

template<class Type> c4DVt<Type> c4DVt<Type>::operator=(cRGBA &lpValue)
{
 memcpy(v,lpValue.Color(),sizeof(Type)*4);
 return *this;
}


template<class Type> c4DVt<Type> c4DVt<Type>::operator+=(Type *lpValue)
{
 v[0]+=lpValue[0];
 v[1]+=lpValue[1];
 v[2]+=lpValue[2];
 v[3]+=lpValue[3];
 return *this;
}

template<class Type> c4DVt<Type> c4DVt<Type>::operator+=(c4DVt<Type> &lpValue)
{
 v[0]+=lpValue.v[0];
 v[1]+=lpValue.v[1];
 v[2]+=lpValue.v[2];
 v[3]+=lpValue.v[3];
 return *this;
}

template<class Type> c4DVt<Type> c4DVt<Type>::operator+=(c4DVt<Type> *lpValue)
{
 v[0]+=lpValue->v[0];
 v[1]+=lpValue->v[1];
 v[2]+=lpValue->v[2];
 v[3]+=lpValue->v[3];
 return *this;
}

template<class Type> Type c4DVt<Type>::Dot(c4DVt<Type> &lpValue)
{
	return v[0]*lpValue.v[0]+v[1]*lpValue.v[1]+v[2]*lpValue.v[2]+v[3]*lpValue.v[3];
}

template<class Type> Type c4DVt<Type>::Dot(Type *lpValue)
{
	return v[0]*lpValue[0]+v[1]*lpValue[1]+v[2]*lpValue[2]+v[3]*lpValue[3];
}

template<class Type> Type c4DVt<Type>::Dot(c4DVt<Type> *lpValue)
{
	return v[0]*lpValue->v[0]+v[1]*lpValue->v[1]+v[2]*lpValue->v[2]+v[3]*lpValue->v[3];
}


	template<class Type> Type c4DVt<Type>::X(){return v[0];};
	template<class Type> Type c4DVt<Type>::Y(){return v[1];};
	template<class Type> Type c4DVt<Type>::Z(){return v[2];};
    template<class Type> Type c4DVt<Type>::W(){return v[3];};
	template<class Type> void c4DVt<Type>::X(Type lfX){v[0]=lfX;};
	template<class Type> void c4DVt<Type>::Y(Type lfY){v[1]=lfY;};
	template<class Type> void c4DVt<Type>::Z(Type lfZ){v[2]=lfZ;};
    template<class Type> void c4DVt<Type>::W(Type lfW){v[3]=lfW;};









template<class Type> c4DVt<Type> c4DVt<Type>::operator+(c4DVt<Type> *lvOther)
{
   c4DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther->v[0];
 lvReturn.v[1]=v[1]+lvOther->v[1];
 lvReturn.v[2]=v[2]+lvOther->v[2];
 lvReturn.v[3]=v[3]+lvOther->v[3];
 return lvReturn;
};

template<class Type> c4DVt<Type> c4DVt<Type>::operator+(c4DVt<Type> &lvOther)
{
   c4DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther.v[0];
 lvReturn.v[1]=v[1]+lvOther.v[1];
 lvReturn.v[2]=v[2]+lvOther.v[2];
 lvReturn.v[3]=v[3]+lvOther.v[3];
 return lvReturn;
};

template<class Type> c4DVt<Type> c4DVt<Type>::operator+(Type *lvOther)
{
   c4DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]+lvOther[0];
 lvReturn.v[1]=v[1]+lvOther[1];
 lvReturn.v[2]=v[2]+lvOther[2];
 lvReturn.v[3]=v[3]+lvOther[3];
 return lvReturn;
};


template<class Type> c4DVt<Type> c4DVt<Type>::operator-(c4DVt<Type> *lvOther)
{
   c4DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther->v[0];
 lvReturn.v[1]=v[1]-lvOther->v[1];
 lvReturn.v[2]=v[2]-lvOther->v[2];
 lvReturn.v[3]=v[3]-lvOther->v[3];
 return lvReturn;
};

template<class Type> c4DVt<Type> c4DVt<Type>::operator-(c4DVt<Type> &lvOther)
{
   c4DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther.v[0];
 lvReturn.v[1]=v[1]-lvOther.v[1];
 lvReturn.v[2]=v[2]-lvOther.v[2];
 lvReturn.v[3]=v[3]-lvOther.v[3];
 return lvReturn;
};

template<class Type> c4DVt<Type> c4DVt<Type>::operator-(Type *lvOther)
{
   c4DVt<Type> lvReturn;
 lvReturn.v[0]=v[0]-lvOther[0];
 lvReturn.v[1]=v[1]-lvOther[1];
 lvReturn.v[2]=v[2]-lvOther[2];
 lvReturn.v[3]=v[3]-lvOther[3];
 return lvReturn;
};



template<class Type> c4DVt<Type> c4DVt<Type>::operator-=(Type *lpValue)
{
 v[0]-=lpValue[0];
 v[1]-=lpValue[1];
 v[2]-=lpValue[2];
 v[3]-=lpValue[3];
 return *this;
}

template<class Type> c4DVt<Type> c4DVt<Type>::operator-=(c4DVt<Type> &lpValue)
{
 v[0]-=lpValue.v[0];
 v[1]-=lpValue.v[1];
 v[2]-=lpValue.v[2];
 v[3]-=lpValue.v[3];
 return *this;
}

template<class Type> c4DVt<Type> c4DVt<Type>::operator-=(c4DVt<Type> *lpValue)
{
 v[0]-=lpValue->v[0];
 v[1]-=lpValue->v[1];
 v[2]-=lpValue->v[2];
 v[3]-=lpValue->v[3];
 return *this;
}
