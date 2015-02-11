
#include "../WTBamboo.h"

cDoubleMatrix4 cDoubleMatrix4::mpTemp;

cDoubleMatrix4::cDoubleMatrix4(cMatrix4 *lpOther)
{
    mb3D=lpOther->Is3D();
    Equals(lpOther);
};
/*
cDoubleMatrix4::cDoubleMatrix4(cDoubleMatrix4 *lpOther)
{
    mb3D=lpOther->Is3D();
    Equals(lpOther);
};

cDoubleMatrix4::cDoubleMatrix4(const cDoubleMatrix4 &lpOther)
{
    mb3D=lpOther.mb3D;
    Equals(lpOther);
};*/


cDoubleMatrix4::cDoubleMatrix4(const cMatrix4 &lpOther)
{
    mb3D=lpOther.mb3D;
    Equals(lpOther);
};


double cDoubleMatrix4::mpZero[]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
double cDoubleMatrix4::mpIdentity[]={1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f};

cDoubleMatrix4::cDoubleMatrix4()
{
Set3D();
}



cDoubleMatrix4 cDoubleMatrix4::operator+(double &lVal)
{
 mpTemp.mpData[0]=mpData[0]+lVal;
 mpTemp.mpData[1]=mpData[1]+lVal;
 mpTemp.mpData[2]=mpData[2]+lVal;
 mpTemp.mpData[3]=mpData[3]+lVal;
 mpTemp.mpData[4]=mpData[4]+lVal;
 mpTemp.mpData[5]=mpData[5]+lVal;
 mpTemp.mpData[6]=mpData[6]+lVal;
 mpTemp.mpData[7]=mpData[7]+lVal;
 mpTemp.mpData[8]=mpData[8]+lVal;
 mpTemp.mpData[9]=mpData[9]+lVal;
 mpTemp.mpData[10]=mpData[10]+lVal;
 mpTemp.mpData[11]=mpData[11]+lVal;
 mpTemp.mpData[12]=mpData[12]+lVal;
 mpTemp.mpData[13]=mpData[13]+lVal;
 mpTemp.mpData[14]=mpData[14]+lVal;
 mpTemp.mpData[15]=mpData[15]+lVal;

 return mpTemp;
}

cDoubleMatrix4 cDoubleMatrix4::operator+(const double lVal)
{
 mpTemp.mpData[0]=mpData[0]+lVal;
 mpTemp.mpData[1]=mpData[1]+lVal;
 mpTemp.mpData[2]=mpData[2]+lVal;
 mpTemp.mpData[3]=mpData[3]+lVal;
 mpTemp.mpData[4]=mpData[4]+lVal;
 mpTemp.mpData[5]=mpData[5]+lVal;
 mpTemp.mpData[6]=mpData[6]+lVal;
 mpTemp.mpData[7]=mpData[7]+lVal;
 mpTemp.mpData[8]=mpData[8]+lVal;
 mpTemp.mpData[9]=mpData[9]+lVal;
 mpTemp.mpData[10]=mpData[10]+lVal;
 mpTemp.mpData[11]=mpData[11]+lVal;
 mpTemp.mpData[12]=mpData[12]+lVal;
 mpTemp.mpData[13]=mpData[13]+lVal;
 mpTemp.mpData[14]=mpData[14]+lVal;
 mpTemp.mpData[15]=mpData[15]+lVal;
 return mpTemp;
}

cDoubleMatrix4 cDoubleMatrix4::operator-(double &lVal)
{
 mpTemp.mpData[0]=mpData[0]-lVal;
 mpTemp.mpData[1]=mpData[1]-lVal;
 mpTemp.mpData[2]=mpData[2]-lVal;
 mpTemp.mpData[3]=mpData[3]-lVal;
 mpTemp.mpData[4]=mpData[4]-lVal;
 mpTemp.mpData[5]=mpData[5]-lVal;
 mpTemp.mpData[6]=mpData[6]-lVal;
 mpTemp.mpData[7]=mpData[7]-lVal;
 mpTemp.mpData[8]=mpData[8]-lVal;
 mpTemp.mpData[9]=mpData[9]-lVal;
 mpTemp.mpData[10]=mpData[10]-lVal;
 mpTemp.mpData[11]=mpData[11]-lVal;
 mpTemp.mpData[12]=mpData[12]-lVal;
 mpTemp.mpData[13]=mpData[13]-lVal;
 mpTemp.mpData[14]=mpData[14]-lVal;
 mpTemp.mpData[15]=mpData[15]-lVal;


 return mpTemp;
}

cDoubleMatrix4 cDoubleMatrix4::operator-(const double lVal)
{
 mpTemp.mpData[0]=mpData[0]-lVal;
 mpTemp.mpData[1]=mpData[1]-lVal;
 mpTemp.mpData[2]=mpData[2]-lVal;
 mpTemp.mpData[3]=mpData[3]-lVal;
 mpTemp.mpData[4]=mpData[4]-lVal;
 mpTemp.mpData[5]=mpData[5]-lVal;
 mpTemp.mpData[6]=mpData[6]-lVal;
 mpTemp.mpData[7]=mpData[7]-lVal;
 mpTemp.mpData[8]=mpData[8]-lVal;
 mpTemp.mpData[9]=mpData[9]-lVal;
 mpTemp.mpData[10]=mpData[10]-lVal;
 mpTemp.mpData[11]=mpData[11]-lVal;
 mpTemp.mpData[12]=mpData[12]-lVal;
 mpTemp.mpData[13]=mpData[13]-lVal;
 mpTemp.mpData[14]=mpData[14]-lVal;
 mpTemp.mpData[15]=mpData[15]-lVal;
 return mpTemp;
}

cDoubleMatrix4 cDoubleMatrix4::operator*(double &lVal)
{
 mpTemp.mpData[0]=mpData[0]*lVal;
 mpTemp.mpData[1]=mpData[1]*lVal;
 mpTemp.mpData[2]=mpData[2]*lVal;
 mpTemp.mpData[3]=mpData[3]*lVal;
 mpTemp.mpData[4]=mpData[4]*lVal;
 mpTemp.mpData[5]=mpData[5]*lVal;
 mpTemp.mpData[6]=mpData[6]*lVal;
 mpTemp.mpData[7]=mpData[7]*lVal;
 mpTemp.mpData[8]=mpData[8]*lVal;
 mpTemp.mpData[9]=mpData[9]*lVal;
 mpTemp.mpData[10]=mpData[10]*lVal;
 mpTemp.mpData[11]=mpData[11]*lVal;
 mpTemp.mpData[12]=mpData[12]*lVal;
 mpTemp.mpData[13]=mpData[13]*lVal;
 mpTemp.mpData[14]=mpData[14]*lVal;
 mpTemp.mpData[15]=mpData[15]*lVal;


 return mpTemp;
}

cDoubleMatrix4 cDoubleMatrix4::operator*(const double lVal)
{
 mpTemp.mpData[0]=mpData[0]*lVal;
 mpTemp.mpData[1]=mpData[1]*lVal;
 mpTemp.mpData[2]=mpData[2]*lVal;
 mpTemp.mpData[3]=mpData[3]*lVal;
 mpTemp.mpData[4]=mpData[4]*lVal;
 mpTemp.mpData[5]=mpData[5]*lVal;
 mpTemp.mpData[6]=mpData[6]*lVal;
 mpTemp.mpData[7]=mpData[7]*lVal;
 mpTemp.mpData[8]=mpData[8]*lVal;
 mpTemp.mpData[9]=mpData[9]*lVal;
 mpTemp.mpData[10]=mpData[10]*lVal;
 mpTemp.mpData[11]=mpData[11]*lVal;
 mpTemp.mpData[12]=mpData[12]*lVal;
 mpTemp.mpData[13]=mpData[13]*lVal;
 mpTemp.mpData[14]=mpData[14]*lVal;
 mpTemp.mpData[15]=mpData[15]*lVal;

 return mpTemp;
}

cDoubleMatrix4 cDoubleMatrix4::operator/(double &lVal)
{
 mpTemp.mpData[0]=mpData[0]/lVal;
 mpTemp.mpData[1]=mpData[1]/lVal;
 mpTemp.mpData[2]=mpData[2]/lVal;
 mpTemp.mpData[3]=mpData[3]/lVal;
 mpTemp.mpData[4]=mpData[4]/lVal;
 mpTemp.mpData[5]=mpData[5]/lVal;
 mpTemp.mpData[6]=mpData[6]/lVal;
 mpTemp.mpData[7]=mpData[7]/lVal;
 mpTemp.mpData[8]=mpData[8]/lVal;
 mpTemp.mpData[9]=mpData[9]/lVal;
 mpTemp.mpData[10]=mpData[10]/lVal;
 mpTemp.mpData[11]=mpData[11]/lVal;
 mpTemp.mpData[12]=mpData[12]/lVal;
 mpTemp.mpData[13]=mpData[13]/lVal;
 mpTemp.mpData[14]=mpData[14]/lVal;
 mpTemp.mpData[15]=mpData[15]/lVal;

 return mpTemp;
}

cDoubleMatrix4 cDoubleMatrix4::operator/(const double lVal)
{
 mpTemp.mpData[0]=mpData[0]/lVal;
 mpTemp.mpData[1]=mpData[1]/lVal;
 mpTemp.mpData[2]=mpData[2]/lVal;
 mpTemp.mpData[3]=mpData[3]/lVal;
 mpTemp.mpData[4]=mpData[4]/lVal;
 mpTemp.mpData[5]=mpData[5]/lVal;
 mpTemp.mpData[6]=mpData[6]/lVal;
 mpTemp.mpData[7]=mpData[7]/lVal;
 mpTemp.mpData[8]=mpData[8]/lVal;
 mpTemp.mpData[9]=mpData[9]/lVal;
 mpTemp.mpData[10]=mpData[10]/lVal;
 mpTemp.mpData[11]=mpData[11]/lVal;
 mpTemp.mpData[12]=mpData[12]/lVal;
 mpTemp.mpData[13]=mpData[13]/lVal;
 mpTemp.mpData[14]=mpData[14]/lVal;
 mpTemp.mpData[15]=mpData[15]/lVal;

 return mpTemp;
}


double *cDoubleMatrix4::operator=(double *lVal)
{
 memcpy(mpData,lVal,sizeof(double)*16);
 return lVal;
}

cDoubleMatrix4 cDoubleMatrix4::operator=(cDoubleMatrix4 lVal)
{
memcpy(mpData,lVal.mpData,sizeof(double)*16);
return lVal;
}

cDoubleMatrix4 cDoubleMatrix4::operator=(cMatrix4 lVal)
{
mpData[0]=lVal[0];
mpData[1]=lVal[1];
mpData[2]=lVal[2];
mpData[3]=lVal[3];
mpData[4]=lVal[4];
mpData[5]=lVal[5];
mpData[6]=lVal[6];
mpData[7]=lVal[7];
mpData[8]=lVal[8];
mpData[9]=lVal[9];
mpData[10]=lVal[10];
mpData[11]=lVal[11];
mpData[12]=lVal[12];
mpData[13]=lVal[13];
mpData[14]=lVal[14];
mpData[15]=lVal[15];

return *this;
}

cDoubleMatrix4 cDoubleMatrix4::operator=(cMatrix4 *lpOther)
{
 float *lVal=lpOther->Matrix();
mpData[0]=lVal[0];
mpData[1]=lVal[1];
mpData[2]=lVal[2];
mpData[3]=lVal[3];
mpData[4]=lVal[4];
mpData[5]=lVal[5];
mpData[6]=lVal[6];
mpData[7]=lVal[7];
mpData[8]=lVal[8];
mpData[9]=lVal[9];
mpData[10]=lVal[10];
mpData[11]=lVal[11];
mpData[12]=lVal[12];
mpData[13]=lVal[13];
mpData[14]=lVal[14];
mpData[15]=lVal[15];

return *this;
}

double cDoubleMatrix4::operator=(double &lVal)
{
 memset(mpData,lVal,sizeof(double)*16);
 return lVal;
}

double cDoubleMatrix4::operator=(const double lVal)
{
// memset(mpData,lVal,9*sizeof(double));
 mpData[0]=lVal;
 mpData[1]=lVal;
 mpData[2]=lVal;
 mpData[3]=lVal;
 mpData[4]=lVal;
 mpData[5]=lVal;
 mpData[6]=lVal;
 mpData[7]=lVal;
 mpData[8]=lVal;
 mpData[9]=lVal;
 mpData[10]=lVal;
 mpData[11]=lVal;
 mpData[12]=lVal;
 mpData[13]=lVal;
 mpData[14]=lVal;
 mpData[15]=lVal;

 return lVal;
}
/*
cDoubleMatrix4 &cDoubleMatrix4::operator=(cDoubleMatrix4 &lVal)
{
 memcpy(mpData,lVal.mpData,16*sizeof(double));
 return this;
}
*/
cDoubleMatrix4 *cDoubleMatrix4::operator=(cDoubleMatrix4 *lVal)
{
 memcpy(mpData,lVal->mpData,16*sizeof(double));
 return this;
}

void cDoubleMatrix4::Zero()
{
 memcpy(mpData,mpZero,16*sizeof(double));
}

void cDoubleMatrix4::Identity()
{
 memcpy(mpData,mpIdentity,16*sizeof(double));
}

cDoubleMatrix4 cDoubleMatrix4::operator+(cDoubleMatrix4 &lVal)
{
 mpTemp.mpData[0]=mpData[0]+lVal.mpData[0];
 mpTemp.mpData[1]=mpData[1]+lVal.mpData[1];
 mpTemp.mpData[2]=mpData[2]+lVal.mpData[2];
 mpTemp.mpData[3]=mpData[3]+lVal.mpData[3];
 mpTemp.mpData[4]=mpData[4]+lVal.mpData[4];
 mpTemp.mpData[5]=mpData[5]+lVal.mpData[5];
 mpTemp.mpData[6]=mpData[6]+lVal.mpData[6];
 mpTemp.mpData[7]=mpData[7]+lVal.mpData[7];
 mpTemp.mpData[8]=mpData[8]+lVal.mpData[8];
 mpTemp.mpData[9]=mpData[9]+lVal.mpData[9];
 mpTemp.mpData[10]=mpData[10]+lVal.mpData[10];
 mpTemp.mpData[11]=mpData[11]+lVal.mpData[11];
 mpTemp.mpData[12]=mpData[12]+lVal.mpData[12];
 mpTemp.mpData[13]=mpData[13]+lVal.mpData[13];
 mpTemp.mpData[14]=mpData[14]+lVal.mpData[14];
 mpTemp.mpData[15]=mpData[15]+lVal.mpData[15];
 return mpTemp;
}

cDoubleMatrix4 cDoubleMatrix4::operator-(cDoubleMatrix4 &lVal)
{
 mpTemp.mpData[0]=mpData[0]-lVal.mpData[0];
 mpTemp.mpData[1]=mpData[1]-lVal.mpData[1];
 mpTemp.mpData[2]=mpData[2]-lVal.mpData[2];
 mpTemp.mpData[3]=mpData[3]-lVal.mpData[3];
 mpTemp.mpData[4]=mpData[4]-lVal.mpData[4];
 mpTemp.mpData[5]=mpData[5]-lVal.mpData[5];
 mpTemp.mpData[6]=mpData[6]-lVal.mpData[6];
 mpTemp.mpData[7]=mpData[7]-lVal.mpData[7];
 mpTemp.mpData[8]=mpData[8]-lVal.mpData[8];
 mpTemp.mpData[9]=mpData[9]-lVal.mpData[9];
 mpTemp.mpData[10]=mpData[10]-lVal.mpData[10];
 mpTemp.mpData[11]=mpData[11]-lVal.mpData[11];
 mpTemp.mpData[12]=mpData[12]-lVal.mpData[12];
 mpTemp.mpData[13]=mpData[13]-lVal.mpData[13];
 mpTemp.mpData[14]=mpData[14]-lVal.mpData[14];
 mpTemp.mpData[15]=mpData[15]-lVal.mpData[15];
 return mpTemp;
}


double cDoubleMatrix4::Determinant()
{
 return
 mpData[0]*(mpData[5]*(mpData[10]*mpData[15]-mpData[14]*mpData[11])-mpData[9]*(mpData[6]*mpData[15]-mpData[14]*mpData[7])+mpData[13]*(mpData[6]*mpData[11]-mpData[10]*mpData[7]))
 -mpData[4]*(mpData[1]*(mpData[10]*mpData[15]-mpData[11]*mpData[14])-mpData[9]*(mpData[2]*mpData[15]-mpData[14]*mpData[3])+mpData[13]*(mpData[2]*mpData[11]-mpData[10]*mpData[3]))
 +mpData[8]*(mpData[1]*(mpData[6]*mpData[10]-mpData[14]*mpData[7])-mpData[5]*(mpData[2]*mpData[15]-mpData[3]*mpData[14])+mpData[13]*(mpData[2]*mpData[7]-mpData[6]*mpData[3]))
 -mpData[12]*(mpData[1]*(mpData[6]*mpData[11]-mpData[10]*mpData[7])-mpData[5]*(mpData[2]*mpData[11]-mpData[10]*mpData[3])+mpData[9]*(mpData[2]*mpData[7]-mpData[6]*mpData[3]));
}
/*
cDoubleMatrix4 cDoubleMatrix4::InvertRotationMatrix()
{
uint32 CHECK_IF_THIS_SHOULD_INVERT_THE_SIGN_OF_THE_OUTPUTED_VALUES;
double Tmp[12];

	// Cache pairs for first cofactor set calculation
	Tmp[0] = mpData[10] * mpData[15];
	Tmp[1] = mpData[14] * mpData[11];
	Tmp[2] = mpData[6] * mpData[15];
	Tmp[3] = mpData[14] * mpData[7];
	Tmp[4] = mpData[6] * mpData[11];
	Tmp[5] = mpData[10] * mpData[7];
	Tmp[6] = mpData[2] * mpData[15];
	Tmp[7] = mpData[14] * mpData[3];
	Tmp[8] = mpData[2] * mpData[11];
	Tmp[9] = mpData[10] * mpData[3];
	Tmp[10] = mpData[2] * mpData[7];
	Tmp[11] = mpData[6] * mpData[3];

	// Calculate first cofactor set
	mpTemp.mpData[0] = (Tmp[0] * mpData[5]) + (Tmp[3] * mpData[9]) + (Tmp[4] * mpData[13]);
	mpTemp.mpData[0] -= (Tmp[1] * mpData[5]) + (Tmp[2] * mpData[9]) + (Tmp[5] * mpData[13]);
	mpTemp.mpData[1] = (Tmp[1] * mpData[1]) + (Tmp[6] * mpData[9]) + (Tmp[9] * mpData[13]);
	mpTemp.mpData[1] -= (Tmp[0] * mpData[1]) + (Tmp[7] * mpData[9]) + (Tmp[8] * mpData[13]);
	mpTemp.mpData[2] = (Tmp[2] * mpData[1]) + (Tmp[7] * mpData[5]) + (Tmp[10] * mpData[13]);
	mpTemp.mpData[2] -= (Tmp[3] * mpData[1]) + (Tmp[6] * mpData[5]) + (Tmp[11] * mpData[13]);
	mpTemp.mpData[3] = (Tmp[5] * mpData[1]) + (Tmp[8] * mpData[5]) + (Tmp[11] * mpData[9]);
	mpTemp.mpData[3] -= (Tmp[4] * mpData[1]) + (Tmp[9] * mpData[5]) + (Tmp[10] * mpData[9]);
	mpTemp.mpData[4] = (Tmp[1] * mpData[4]) + (Tmp[2] * mpData[8]) + (Tmp[5] * mpData[12]);
	mpTemp.mpData[4] -= (Tmp[0] * mpData[4]) + (Tmp[3] * mpData[8]) + (Tmp[4] * mpData[12]);
	mpTemp.mpData[5] = (Tmp[0] * mpData[0]) + (Tmp[7] * mpData[8]) + (Tmp[8] * mpData[12]);
	mpTemp.mpData[5] -= (Tmp[1] * mpData[0]) + (Tmp[6] * mpData[8]) + (Tmp[9] * mpData[12]);
	mpTemp.mpData[6] = (Tmp[3] * mpData[0]) + (Tmp[6] * mpData[4]) + (Tmp[11] * mpData[12]);
	mpTemp.mpData[6] -= (Tmp[2] * mpData[0]) + (Tmp[7] * mpData[4]) + (Tmp[10] * mpData[12]);
	mpTemp.mpData[7] = (Tmp[4] * mpData[0]) + (Tmp[9] * mpData[4]) + (Tmp[10] * mpData[8]);
	mpTemp.mpData[7] -= (Tmp[5] * mpData[0]) + (Tmp[8] * mpData[4]) + (Tmp[11] * mpData[8]);

	// Cache pairs for more cofactor calculation
	Tmp[0] = mpData[8] * mpData[13];
	Tmp[1] = mpData[12] * mpData[9];
	Tmp[2] = mpData[4] * mpData[13];
	Tmp[3] = mpData[12] * mpData[5];
	Tmp[4] = mpData[4] * mpData[9];
	Tmp[5] = mpData[8] * mpData[5];
	Tmp[6] = mpData[0] * mpData[13];
	Tmp[7] = mpData[12] * mpData[1];
	Tmp[8] = mpData[0] * mpData[9];
	Tmp[9] = mpData[8] * mpData[1];
	Tmp[10] = mpData[0] * mpData[5];
	Tmp[11] = mpData[4] * mpData[1];

	// Calculate more cofactors
	mpTemp.mpData[8] = (Tmp[0] * mpData[7]) + (Tmp[3] * mpData[11]) + (Tmp[4] * mpData[15]);
	mpTemp.mpData[8] -= (Tmp[1] * mpData[7]) + (Tmp[2] * mpData[11]) + (Tmp[5] * mpData[15]);
	mpTemp.mpData[9] = (Tmp[1] * mpData[3]) + (Tmp[6] * mpData[11]) + (Tmp[9] * mpData[15]);
	mpTemp.mpData[9] -= (Tmp[0] * mpData[3]) + (Tmp[7] * mpData[11]) + (Tmp[8] * mpData[15]);
	mpTemp.mpData[10] = (Tmp[2] * mpData[3]) + (Tmp[7] * mpData[7]) + (Tmp[10] * mpData[15]);
	mpTemp.mpData[10] -= (Tmp[3] * mpData[3]) + (Tmp[6] * mpData[7]) + (Tmp[11] * mpData[15]);
	mpTemp.mpData[11] = (Tmp[5] * mpData[3]) + (Tmp[8] * mpData[7]) + (Tmp[11] * mpData[11]);
	mpTemp.mpData[11] -= (Tmp[4] * mpData[3]) + (Tmp[9] * mpData[7]) + (Tmp[10] * mpData[11]);
	mpTemp.mpData[12] = (Tmp[2] * mpData[10]) + (Tmp[5] * mpData[14]) + (Tmp[1] * mpData[6]);
	mpTemp.mpData[12] -= (Tmp[4] * mpData[14]) + (Tmp[0] * mpData[6]) + (Tmp[3] * mpData[10]);
	mpTemp.mpData[13] = (Tmp[8] * mpData[14]) + (Tmp[0] * mpData[2]) + (Tmp[7] * mpData[10]);
	mpTemp.mpData[13] -= (Tmp[6] * mpData[10]) + (Tmp[9] * mpData[14]) + (Tmp[1] * mpData[2]);
	mpTemp.mpData[14] = (Tmp[6] * mpData[6]) + (Tmp[11] * mpData[14]) + (Tmp[3] * mpData[2]);
	mpTemp.mpData[14] -= (Tmp[10] * mpData[14]) + (Tmp[2] * mpData[2]) + (Tmp[7] * mpData[6]);
	mpTemp.mpData[15] = (Tmp[10] * mpData[10]) + (Tmp[4] * mpData[2]) + (Tmp[9] * mpData[6]);
	mpTemp.mpData[15] -= (Tmp[8] * mpData[6]) + (Tmp[11] * mpData[10]) + (Tmp[5] * mpData[2]);

	// Calculate determinant
	double Det = -1.0f / ((mpData[0] * mpTemp.mpData[0]) + (mpData[4] * mpTemp.mpData[1]) + (mpData[8] * mpTemp.mpData[2]) + (mpData[12] * mpTemp.mpData[3]));

	// Calculate inverse matrix
	mpTemp.mpData[0] *= Det;
	mpTemp.mpData[1] *= Det;
	mpTemp.mpData[2] *= Det;
	mpTemp.mpData[3] *= Det;
	mpTemp.mpData[4] *= Det;
	mpTemp.mpData[5] *= Det;
	mpTemp.mpData[6] *= Det;
	mpTemp.mpData[7] *= Det;
	mpTemp.mpData[8] *= Det;
	mpTemp.mpData[9] *= Det;
	mpTemp.mpData[10] *= Det;
	mpTemp.mpData[11] *= Det;
	mpTemp.mpData[12] *= Det;
	mpTemp.mpData[13] *= Det;
	mpTemp.mpData[14] *= Det;
	mpTemp.mpData[15] *= Det;

	return mpTemp;

}
*/

cDoubleMatrix4 cDoubleMatrix4::InversionMatrix()
{
    mpTemp.mpData[0]=mpData[0];
    mpTemp.mpData[1]=mpData[4];
    mpTemp.mpData[2]=mpData[8];
    mpTemp.mpData[3]=0.0f;

    mpTemp.mpData[4]=mpData[1];
    mpTemp.mpData[5]=mpData[5];
    mpTemp.mpData[6]=mpData[9];
    mpTemp.mpData[7]=0.0f;

    mpTemp.mpData[8]=mpData[2];
    mpTemp.mpData[9]=mpData[6];
    mpTemp.mpData[10]=mpData[10];
    mpTemp.mpData[11]=0.0f;

    mpTemp.mpData[12]=-mpData[12];
    mpTemp.mpData[13]=-mpData[13];
    mpTemp.mpData[14]=-mpData[14];
    mpTemp.mpData[15]=1.0f;
/*
    mpTemp.mpData[12]=-(mpTemp.mpData[0]*mpData[12]+mpTemp.mpData[1]*mpData[13]+mpTemp.mpData[2]*mpData[14]);
    mpTemp.mpData[13]=-(mpTemp.mpData[4]*mpData[12]+mpTemp.mpData[5]*mpData[13]+mpTemp.mpData[6]*mpData[14]);
    mpTemp.mpData[14]=-(mpTemp.mpData[8]*mpData[12]+mpTemp.mpData[9]*mpData[13]+mpTemp.mpData[10]*mpData[14]);
    mpTemp.mpData[15]=1.0f;
*/
	return mpTemp;

}
cDoubleMatrix4 cDoubleMatrix4::Transpose()
{
mpTemp.mpData[0]=mpData[3];
mpTemp.mpData[1]=mpData[7];
mpTemp.mpData[2]=mpData[11];
mpTemp.mpData[3]=mpData[15];
mpTemp.mpData[4]=mpData[2];
mpTemp.mpData[5]=mpData[6];
mpTemp.mpData[6]=mpData[10];
mpTemp.mpData[7]=mpData[14];
mpTemp.mpData[8]=mpData[1];
mpTemp.mpData[9]=mpData[5];
mpTemp.mpData[10]=mpData[9];
mpTemp.mpData[11]=mpData[13];
mpTemp.mpData[12]=mpData[0];
mpTemp.mpData[13]=mpData[4];
mpTemp.mpData[14]=mpData[8];
mpTemp.mpData[15]=mpData[12];
return mpTemp;

}

cDoubleMatrix4 cDoubleMatrix4::operator*(cDoubleMatrix4 lVal)
{
 mpTemp.mpData[0]=mpData[0]*lVal.mpData[0]+mpData[4]*lVal.mpData[1]+mpData[8]*lVal.mpData[2]+mpData[12]*lVal.mpData[3];
 mpTemp.mpData[1]=mpData[1]*lVal.mpData[0]+mpData[5]*lVal.mpData[1]+mpData[9]*lVal.mpData[2]+mpData[13]*lVal.mpData[3];
 mpTemp.mpData[2]=mpData[2]*lVal.mpData[0]+mpData[6]*lVal.mpData[1]+mpData[10]*lVal.mpData[2]+mpData[14]*lVal.mpData[3];
 mpTemp.mpData[3]=mpData[3]*lVal.mpData[0]+mpData[7]*lVal.mpData[1]+mpData[11]*lVal.mpData[2]+mpData[15]*lVal.mpData[3];

 mpTemp.mpData[4]=mpData[0]*lVal.mpData[4]+mpData[4]*lVal.mpData[5]+mpData[8]*lVal.mpData[6]+mpData[12]*lVal.mpData[7];
 mpTemp.mpData[5]=mpData[1]*lVal.mpData[4]+mpData[5]*lVal.mpData[5]+mpData[9]*lVal.mpData[6]+mpData[13]*lVal.mpData[7];
 mpTemp.mpData[6]=mpData[2]*lVal.mpData[4]+mpData[6]*lVal.mpData[5]+mpData[10]*lVal.mpData[6]+mpData[14]*lVal.mpData[7];
 mpTemp.mpData[7]=mpData[3]*lVal.mpData[4]+mpData[7]*lVal.mpData[5]+mpData[11]*lVal.mpData[6]+mpData[15]*lVal.mpData[7];

 mpTemp.mpData[8]=mpData[0]*lVal.mpData[8]+mpData[4]*lVal.mpData[9]+mpData[8]*lVal.mpData[10]+mpData[12]*lVal.mpData[11];
 mpTemp.mpData[9]=mpData[1]*lVal.mpData[8]+mpData[5]*lVal.mpData[9]+mpData[9]*lVal.mpData[10]+mpData[13]*lVal.mpData[11];
 mpTemp.mpData[10]=mpData[2]*lVal.mpData[8]+mpData[6]*lVal.mpData[9]+mpData[10]*lVal.mpData[10]+mpData[14]*lVal.mpData[11];
 mpTemp.mpData[11]=mpData[3]*lVal.mpData[8]+mpData[7]*lVal.mpData[9]+mpData[11]*lVal.mpData[10]+mpData[15]*lVal.mpData[11];

 mpTemp.mpData[12]=mpData[0]*lVal.mpData[12]+mpData[4]*lVal.mpData[13]+mpData[8]*lVal.mpData[14]+mpData[12]*lVal.mpData[15];
 mpTemp.mpData[13]=mpData[1]*lVal.mpData[12]+mpData[5]*lVal.mpData[13]+mpData[9]*lVal.mpData[14]+mpData[13]*lVal.mpData[15];
 mpTemp.mpData[14]=mpData[2]*lVal.mpData[12]+mpData[6]*lVal.mpData[13]+mpData[10]*lVal.mpData[14]+mpData[14]*lVal.mpData[15];
 mpTemp.mpData[15]=mpData[3]*lVal.mpData[12]+mpData[7]*lVal.mpData[13]+mpData[11]*lVal.mpData[14]+mpData[15]*lVal.mpData[15];

 return mpTemp;
}


cDoubleMatrix4 *cDoubleMatrix4::operator*(cDoubleMatrix4 *lVal)
{
 mpTemp.mpData[0]=mpData[0]*lVal->mpData[0]+mpData[4]*lVal->mpData[1]+mpData[8]*lVal->mpData[2]+mpData[12]*lVal->mpData[3];
 mpTemp.mpData[1]=mpData[1]*lVal->mpData[0]+mpData[5]*lVal->mpData[1]+mpData[9]*lVal->mpData[2]+mpData[13]*lVal->mpData[3];
 mpTemp.mpData[2]=mpData[2]*lVal->mpData[0]+mpData[6]*lVal->mpData[1]+mpData[10]*lVal->mpData[2]+mpData[14]*lVal->mpData[3];
 mpTemp.mpData[3]=mpData[3]*lVal->mpData[0]+mpData[7]*lVal->mpData[1]+mpData[11]*lVal->mpData[2]+mpData[15]*lVal->mpData[3];

 mpTemp.mpData[4]=mpData[0]*lVal->mpData[4]+mpData[4]*lVal->mpData[5]+mpData[8]*lVal->mpData[6]+mpData[12]*lVal->mpData[7];
 mpTemp.mpData[5]=mpData[1]*lVal->mpData[4]+mpData[5]*lVal->mpData[5]+mpData[9]*lVal->mpData[6]+mpData[13]*lVal->mpData[7];
 mpTemp.mpData[6]=mpData[2]*lVal->mpData[4]+mpData[6]*lVal->mpData[5]+mpData[10]*lVal->mpData[6]+mpData[14]*lVal->mpData[7];
 mpTemp.mpData[7]=mpData[3]*lVal->mpData[4]+mpData[7]*lVal->mpData[5]+mpData[11]*lVal->mpData[6]+mpData[15]*lVal->mpData[7];

 mpTemp.mpData[8]=mpData[0]*lVal->mpData[8]+mpData[4]*lVal->mpData[9]+mpData[8]*lVal->mpData[10]+mpData[12]*lVal->mpData[11];
 mpTemp.mpData[9]=mpData[1]*lVal->mpData[8]+mpData[5]*lVal->mpData[9]+mpData[9]*lVal->mpData[10]+mpData[13]*lVal->mpData[11];
 mpTemp.mpData[10]=mpData[2]*lVal->mpData[8]+mpData[6]*lVal->mpData[9]+mpData[10]*lVal->mpData[10]+mpData[14]*lVal->mpData[11];
 mpTemp.mpData[11]=mpData[3]*lVal->mpData[8]+mpData[7]*lVal->mpData[9]+mpData[11]*lVal->mpData[10]+mpData[15]*lVal->mpData[11];

 mpTemp.mpData[12]=mpData[0]*lVal->mpData[12]+mpData[4]*lVal->mpData[13]+mpData[8]*lVal->mpData[14]+mpData[12]*lVal->mpData[15];
 mpTemp.mpData[13]=mpData[1]*lVal->mpData[12]+mpData[5]*lVal->mpData[13]+mpData[9]*lVal->mpData[14]+mpData[13]*lVal->mpData[15];
 mpTemp.mpData[14]=mpData[2]*lVal->mpData[12]+mpData[6]*lVal->mpData[13]+mpData[10]*lVal->mpData[14]+mpData[14]*lVal->mpData[15];
 mpTemp.mpData[15]=mpData[3]*lVal->mpData[12]+mpData[7]*lVal->mpData[13]+mpData[11]*lVal->mpData[14]+mpData[15]*lVal->mpData[15];

 return &mpTemp;
}


double &cDoubleMatrix4::operator[](uint16 liPos)
{
 return mpData[liPos];
}

double &cDoubleMatrix4::operator()(uint16 liColumn,uint16 liRow)
{
 return mpData[liColumn*4+liRow];
}

void cDoubleMatrix4::Position(double lfX,double lfY)
{
 mpData[12]=lfX;
 mpData[13]=lfY;
}

void cDoubleMatrix4::Position(double lfX,double lfY,double lfZ)
{
 mpData[12]=lfX;
 mpData[13]=lfY;
 mpData[14]=lfZ;
}

void cDoubleMatrix4::Position(double *lpPos)
{
 if(mb3D) memcpy(&mpData[12],lpPos,sizeof(double)*3);
 else memcpy(&mpData[12],lpPos,sizeof(double)*2);
}

void cDoubleMatrix4::Position(c2DVd *lpPosition)
{
 memcpy(&mpData[13],lpPosition->v,sizeof(double)*2);
}

void cDoubleMatrix4::Position(c3DVd *lpPosition)
{
 memcpy(&mpData[13],lpPosition->v,sizeof(double)*3);
}

void cDoubleMatrix4::PositionX(double lfX)
{
 mpData[12]=lfX;
}
void cDoubleMatrix4::PositionY(double lfY)
{
 mpData[13]=lfY;
}
void cDoubleMatrix4::PositionZ(double lfZ)
{
 mpData[14]=lfZ;
}

void cDoubleMatrix4::RotateX(double lfAngle)
{
 double lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[4]=mpData[4]*lfCos+mpData[8]*lfSin;
mpTemp.mpData[5]=mpData[5]*lfCos+mpData[9]*lfSin;
mpTemp.mpData[6]=mpData[6]*lfCos+mpData[10]*lfSin;
mpTemp.mpData[7]=0;

mpTemp.mpData[8] =mpData[8] *lfCos-mpData[4]*lfSin;
mpTemp.mpData[9] =mpData[9] *lfCos-mpData[5]*lfSin;
mpTemp.mpData[10]=mpData[10]*lfCos-mpData[6]*lfSin;

memcpy(&mpData[4],&mpTemp.mpData[4],7*sizeof(double));
}


void cDoubleMatrix4::RotateY(double lfAngle)
{
 double lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0]*lfCos-mpData[8]*lfSin;
mpTemp.mpData[1]=mpData[1]*lfCos-mpData[9]*lfSin;
mpTemp.mpData[2]=mpData[2]*lfCos-mpData[10]*lfSin;
mpTemp.mpData[3]=0;

memcpy(&mpTemp.mpData[4],&mpData[4],4*sizeof(double));

mpTemp.mpData[8]=mpData[0]*lfSin+mpData[8]*lfCos;
mpTemp.mpData[9]=mpData[1]*lfSin+mpData[9]*lfCos;
mpTemp.mpData[10]=mpData[2]*lfSin+mpData[10]*lfCos;

memcpy(mpData,mpTemp.mpData,11*sizeof(double));
}


void cDoubleMatrix4::RotateZ(double lfAngle)
{
 double lfCos,lfSin;

 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0]*lfCos+mpData[4]*lfSin;
mpTemp.mpData[1]=mpData[1]*lfCos+mpData[5]*lfSin;
mpTemp.mpData[2]=mpData[2]*lfCos+mpData[6]*lfSin;
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=mpData[4]*lfCos-mpData[0]*lfSin;
mpTemp.mpData[5]=mpData[5]*lfCos-mpData[1]*lfSin;
mpTemp.mpData[6]=mpData[6]*lfCos-mpData[2]*lfSin;
mpTemp.mpData[7]=0;
memcpy(mpData,mpTemp.mpData,8*sizeof(double));

}

void cDoubleMatrix4::AdvanceX(double lfDistance)
{
mpData[12]+=mpData[0]*lfDistance;
mpData[13]+=mpData[1]*lfDistance;
mpData[14]+=mpData[2]*lfDistance;
}

void cDoubleMatrix4::AdvanceY(double lfDistance)
{
mpData[12]+=mpData[4]*lfDistance;
mpData[13]+=mpData[5]*lfDistance;
mpData[14]+=mpData[6]*lfDistance;
}

void cDoubleMatrix4::AdvanceZ(double lfDistance)
{
mpData[12]+=mpData[8]*lfDistance;
mpData[13]+=mpData[9]*lfDistance;
mpData[14]+=mpData[10]*lfDistance;
}

void cDoubleMatrix4::Advance(double lfX,double lfY,double lfZ)
{
mpData[12]+=mpData[0]*lfX+mpData[4]*lfY+mpData[8]*lfZ;
mpData[13]+=mpData[1]*lfX+mpData[5]*lfY+mpData[9]*lfZ;
mpData[14]+=mpData[2]*lfX+mpData[6]*lfY+mpData[10]*lfZ;
}

void cDoubleMatrix4::GAdvance(double *lfDistance)
{
	mpData[12]+=lfDistance[0];
	mpData[13]+=lfDistance[1];
	mpData[14]+=lfDistance[2];
};

void cDoubleMatrix4::GAdvanceX(double lfX)
{mpData[12]+=lfX;}

void cDoubleMatrix4::GAdvanceY(double lfY)
{mpData[13]+=lfY;}

void cDoubleMatrix4::GAdvanceZ(double lfZ)
{mpData[14]+=lfZ;}

void cDoubleMatrix4::GAdvance(double lfX,double lfY,double lfZ)
{
 mpData[12]+=lfX;
 mpData[13]+=lfY;
 mpData[14]+=lfZ;
}

void cDoubleMatrix4::GRotateX(double lfAngle)
{
 double lfCos,lfSin;

 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0];
mpTemp.mpData[1]=lfCos*mpData[1]-lfSin*mpData[2];
mpTemp.mpData[2]=lfSin*mpData[1]+lfCos*mpData[2];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=mpData[4];
mpTemp.mpData[5]=lfCos*mpData[5]-lfSin*mpData[6];
mpTemp.mpData[6]=lfSin*mpData[5]+lfCos*mpData[6];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=mpData[8];
mpTemp.mpData[9]=lfCos*mpData[9]-lfSin*mpData[10];
mpTemp.mpData[10]=lfSin*mpData[9]+lfCos*mpData[10];

memcpy(mpData,mpTemp.mpData,11*sizeof(double));
}


void cDoubleMatrix4::GRotateY(double lfAngle)
{

 double lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=lfCos*mpData[0]+lfSin*mpData[2];
mpTemp.mpData[1]=mpData[1];
mpTemp.mpData[2]=lfCos*mpData[2]-lfSin*mpData[0];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=lfCos*mpData[4]+lfSin*mpData[6];
mpTemp.mpData[5]=mpData[5];
mpTemp.mpData[6]=lfCos*mpData[6]-lfSin*mpData[4];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=lfCos*mpData[8]+lfSin*mpData[10];
mpTemp.mpData[9]=mpData[9];
mpTemp.mpData[10]=lfCos*mpData[10]-lfSin*mpData[8];

memcpy(mpData,mpTemp.mpData,11*sizeof(double));
}

void cDoubleMatrix4::GRotateZ(double lfAngle)
{

double lfCos,lfSin;
      lfCos=cos(lfAngle);
      lfSin=sin(lfAngle);

mpTemp.mpData[0]=lfCos*mpData[0]-lfSin*mpData[1];
mpTemp.mpData[1]=lfSin*mpData[0]+lfCos*mpData[1];
mpTemp.mpData[2]=mpData[2];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=lfCos*mpData[4]-lfSin*mpData[5];
mpTemp.mpData[5]=lfSin*mpData[4]+lfCos*mpData[5];
mpTemp.mpData[6]=mpData[6];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=lfCos*mpData[8]-lfSin*mpData[9];
mpTemp.mpData[9]=lfSin*mpData[8]+lfCos*mpData[9];
mpTemp.mpData[10]=mpData[10];

memcpy(mpData,mpTemp.mpData,11*sizeof(double));

}

void cDoubleMatrix4::Resize(double lfScale)
{
 mpData[0]=mpData[0]*lfScale;
 mpData[1]=mpData[1]*lfScale;
 mpData[2]=mpData[2]*lfScale;

 mpData[4]=mpData[4]*lfScale;
 mpData[5]=mpData[5]*lfScale;
 mpData[6]=mpData[6]*lfScale;

 mpData[8]=mpData[8]*lfScale;
 mpData[9]=mpData[9]*lfScale;
 mpData[10]=mpData[10]*lfScale;
}

void cDoubleMatrix4::ResizeX(double lfScale)
{
 mpData[0]=mpData[0]*lfScale;
 mpData[1]=mpData[1]*lfScale;
 mpData[2]=mpData[2]*lfScale;
}

void cDoubleMatrix4::ResizeY(double lfScale)
{

 mpData[4]=mpData[4]*lfScale;
 mpData[5]=mpData[5]*lfScale;
 mpData[6]=mpData[6]*lfScale;
}

void cDoubleMatrix4::ResizeZ(double lfScale)
{

 mpData[8]=mpData[8]*lfScale;
 mpData[9]=mpData[9]*lfScale;
 mpData[10]=mpData[10]*lfScale;
}

 void cDoubleMatrix4::ScaleX(double lfScale)
 {
     double lfCurrent=lfScale/ScaleX();
     mpData[0]*=lfCurrent;
     mpData[1]*=lfCurrent;
     mpData[2]*=lfCurrent;
 }
 void cDoubleMatrix4::ScaleY(double lfScale)
 {
     double lfCurrent=lfScale/ScaleY();
     mpData[4]*=lfCurrent;
     mpData[5]*=lfCurrent;
     mpData[6]*=lfCurrent;
 }

 void cDoubleMatrix4::ScaleZ(double lfScale)
 {
     double lfCurrent=lfScale/ScaleZ();
     mpData[8]*=lfCurrent;
     mpData[9]*=lfCurrent;
     mpData[10]*=lfCurrent;
 }

  void cDoubleMatrix4::GScaleX(double lfScale)
 {
     double lfCurrent=lfScale/GScaleX();
     mpData[0]*=lfCurrent;
     mpData[4]*=lfCurrent;
     mpData[8]*=lfCurrent;
 }
 void cDoubleMatrix4::GScaleY(double lfScale)
 {
     double lfCurrent=lfScale/GScaleY();
     mpData[1]*=lfCurrent;
     mpData[5]*=lfCurrent;
     mpData[9]*=lfCurrent;
 }

 void cDoubleMatrix4::GScaleZ(double lfScale)
 {
     double lfCurrent=lfScale/GScaleZ();
     mpData[2]*=lfCurrent;
     mpData[6]*=lfCurrent;
     mpData[10]*=lfCurrent;
 }


 double cDoubleMatrix4::ScaleX()
 {
     return sqrt(mpData[0]*mpData[0]+mpData[1]*mpData[1]+mpData[2]*mpData[2]);
 }

 double cDoubleMatrix4::ScaleY()
 {
     return sqrt(mpData[4]*mpData[4]+mpData[5]*mpData[5]+mpData[6]*mpData[6]);
 }

 double cDoubleMatrix4::ScaleZ()
 {
     return sqrt(mpData[8]*mpData[8]+mpData[9]*mpData[9]+mpData[10]*mpData[10]);
 }

  double cDoubleMatrix4::GScaleX()
 {
     return sqrt(mpData[0]*mpData[0]+mpData[4]*mpData[4]+mpData[8]*mpData[8]);
 }

 double cDoubleMatrix4::GScaleY()
 {
     return sqrt(mpData[1]*mpData[1]+mpData[5]*mpData[5]+mpData[9]*mpData[9]);
 }

 double cDoubleMatrix4::GScaleZ()
 {
     return sqrt(mpData[2]*mpData[2]+mpData[6]*mpData[6]+mpData[10]*mpData[10]);
 }

void cDoubleMatrix4::GResizeX(double lfScale)
{
 mpData[0]=mpData[0]*lfScale;
 mpData[4]=mpData[4]*lfScale;
 mpData[8]=mpData[8]*lfScale;
}

void cDoubleMatrix4::GResizeY(double lfScale)
{

 mpData[1]=mpData[1]*lfScale;
 mpData[5]=mpData[5]*lfScale;
 mpData[9]=mpData[9]*lfScale;

}
void cDoubleMatrix4::GResizeZ(double lfScale)
{
 mpData[2]=mpData[2]*lfScale;
 mpData[6]=mpData[6]*lfScale;
 mpData[10]=mpData[10]*lfScale;

}


void cDoubleMatrix4::GRotateOriginX(double lfAngle)
{
 double lfCos,lfSin;

 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0];
mpTemp.mpData[1]=lfCos*mpData[1]-lfSin*mpData[2];
mpTemp.mpData[2]=lfSin*mpData[1]+lfCos*mpData[2];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=mpData[4];
mpTemp.mpData[5]=lfCos*mpData[5]-lfSin*mpData[6];
mpTemp.mpData[6]=lfSin*mpData[5]+lfCos*mpData[6];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=mpData[8];
mpTemp.mpData[9]=lfCos*mpData[9]-lfSin*mpData[10];
mpTemp.mpData[10]=lfSin*mpData[9]+lfCos*mpData[10];
mpTemp.mpData[11]=0;

mpTemp.mpData[12]=mpData[12];
mpTemp.mpData[13]=lfCos*mpData[13]-lfSin*mpData[14];
mpTemp.mpData[14]=lfSin*mpData[13]+lfCos*mpData[14];

memcpy(mpData,mpTemp.mpData,15*sizeof(double));
}

void cDoubleMatrix4::GRotateOriginY(double lfAngle)
{

 double lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=lfCos*mpData[0]+lfSin*mpData[2];
mpTemp.mpData[1]=mpData[1];
mpTemp.mpData[2]=lfCos*mpData[2]-lfSin*mpData[0];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=lfCos*mpData[4]+lfSin*mpData[6];
mpTemp.mpData[5]=mpData[5];
mpTemp.mpData[6]=lfCos*mpData[6]-lfSin*mpData[4];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=lfCos*mpData[8]+lfSin*mpData[10];
mpTemp.mpData[9]=mpData[9];
mpTemp.mpData[10]=lfCos*mpData[10]-lfSin*mpData[8];
mpTemp.mpData[11]=0;

mpTemp.mpData[12]=lfCos*mpData[12]+lfSin*mpData[14];
mpTemp.mpData[13]=mpData[13];
mpTemp.mpData[14]=lfCos*mpData[14]-lfSin*mpData[12];

memcpy(mpData,mpTemp.mpData,15*sizeof(double));
}

void cDoubleMatrix4::GRotateOriginZ(double lfAngle)
{

double lfCos,lfSin;
      lfCos=cos(lfAngle);
      lfSin=sin(lfAngle);

mpTemp.mpData[0]=lfCos*mpData[0]-lfSin*mpData[1];
mpTemp.mpData[1]=lfSin*mpData[0]+lfCos*mpData[1];
mpTemp.mpData[2]=mpData[2];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=lfCos*mpData[4]-lfSin*mpData[5];
mpTemp.mpData[5]=lfSin*mpData[4]+lfCos*mpData[5];
mpTemp.mpData[6]=mpData[6];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=lfCos*mpData[8]-lfSin*mpData[9];
mpTemp.mpData[9]=lfSin*mpData[8]+lfCos*mpData[9];
mpTemp.mpData[10]=mpData[10];
mpTemp.mpData[11]=0;

mpTemp.mpData[12]=lfCos*mpData[12]-lfSin*mpData[13];
mpTemp.mpData[13]=lfSin*mpData[12]+lfCos*mpData[13];
mpTemp.mpData[14]=mpData[14];

memcpy(mpData,mpTemp.mpData,15*sizeof(double));
}

void cDoubleMatrix4::GRotateX(double lfAngle,double lfX,double lfY,double lfZ)
{
 (void) lfX;
 double lfCos,lfSin;

 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0];
mpTemp.mpData[1]=lfCos*mpData[1]-lfSin*mpData[2];
mpTemp.mpData[2]=lfSin*mpData[1]+lfCos*mpData[2];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=mpData[4];
mpTemp.mpData[5]=lfCos*mpData[5]-lfSin*mpData[6];
mpTemp.mpData[6]=lfSin*mpData[5]+lfCos*mpData[6];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=mpData[8];
mpTemp.mpData[9]=lfCos*mpData[9]-lfSin*mpData[10];
mpTemp.mpData[10]=lfSin*mpData[9]+lfCos*mpData[10];
mpTemp.mpData[11]=0;

mpData[13]-=lfY;
mpData[14]-=lfZ;
mpTemp.mpData[12]=mpData[12];
mpTemp.mpData[13]=lfCos*mpData[13]-lfSin*mpData[14]+lfY;
mpTemp.mpData[14]=lfCos*mpData[13]+lfSin*mpData[14]+lfZ;

memcpy(&mpData[1],&mpTemp.mpData[1],14*sizeof(double));

}

void cDoubleMatrix4::GRotateY(double lfAngle,double lfX,double lfY,double lfZ)
{
(void) lfY;
 double lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=lfCos*mpData[0]+lfSin*mpData[2];
mpTemp.mpData[1]=mpData[1];
mpTemp.mpData[2]=lfCos*mpData[2]-lfSin*mpData[0];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=lfCos*mpData[4]+lfSin*mpData[6];
mpTemp.mpData[5]=mpData[5];
mpTemp.mpData[6]=lfCos*mpData[6]-lfSin*mpData[4];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=lfCos*mpData[8]+lfSin*mpData[10];
mpTemp.mpData[9]=mpData[9];
mpTemp.mpData[10]=lfCos*mpData[10]-lfSin*mpData[8];
mpTemp.mpData[11]=0;

mpData[12]-=lfX;
mpData[14]-=lfZ;

mpTemp.mpData[12]=lfCos*mpData[12]+lfSin*mpData[14];
mpTemp.mpData[13]=mpData[13];
mpTemp.mpData[14]=lfCos*mpData[14]-lfSin*mpData[12];

memcpy(mpData,mpTemp.mpData,15*sizeof(double));

}

void cDoubleMatrix4::GRotateZ(double lfAngle,double lfX,double lfY,double lfZ)
{
(void) lfZ;
double lfCos,lfSin;
      lfCos=cos(lfAngle);
      lfSin=sin(lfAngle);

mpTemp.mpData[0]=lfCos*mpData[0]-lfSin*mpData[1];
mpTemp.mpData[1]=lfSin*mpData[0]+lfCos*mpData[1];
mpTemp.mpData[2]=mpData[2];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=lfCos*mpData[4]-lfSin*mpData[5];
mpTemp.mpData[5]=lfSin*mpData[4]+lfCos*mpData[5];
mpTemp.mpData[6]=mpData[6];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=lfCos*mpData[8]-lfSin*mpData[9];
mpTemp.mpData[9]=lfSin*mpData[8]+lfCos*mpData[9];
mpTemp.mpData[10]=mpData[10];
mpTemp.mpData[11]=0;

mpData[12]-=lfX;
mpData[13]-=lfY;

mpTemp.mpData[12]=lfCos*mpData[12]-lfSin*mpData[13]+lfX;
mpTemp.mpData[13]=lfSin*mpData[12]+lfCos*mpData[13]+lfY;
//mpTemp.mpData[14]=mpData[14];

memcpy(mpData,mpTemp.mpData,14*sizeof(double));
}

double cDoubleMatrix4::DistanceSq(cDoubleMatrix4 lpOther)
{
 double lfX,lfY,lfZ;

 lfX=lpOther.mpData[12]-mpData[12];
 lfY=lpOther.mpData[13]-mpData[13];
 lfZ=lpOther.mpData[14]-mpData[14];

 return (lfX*lfX+lfY*lfY+lfZ*lfZ);
}


double cDoubleMatrix4::DistanceSq(cDoubleMatrix4 *lpOther)
{
 double lfX,lfY,lfZ;
 lfX=lpOther->mpData[12]-mpData[12];
 lfY=lpOther->mpData[13]-mpData[13];
 lfZ=lpOther->mpData[14]-mpData[14];


 return (lfX*lfX+lfY*lfY+lfZ*lfZ);
}

double cDoubleMatrix4::DistanceSq(c3DVd lpOther)
{
 lpOther[0]=lpOther[0]-mpData[12];
 lpOther[1]=lpOther[1]-mpData[13];
 lpOther[2]=lpOther[2]-mpData[14];

 return lpOther[0]*lpOther[0]+lpOther[1]*lpOther[1]+lpOther[2]*lpOther[2];
}

double cDoubleMatrix4::Distance(c3DVd lpOther)
{
 lpOther[0]=lpOther[0]-mpData[12];
 lpOther[1]=lpOther[1]-mpData[13];
 lpOther[2]=lpOther[2]-mpData[14];

 return sqrt(lpOther[0]*lpOther[0]+lpOther[1]*lpOther[1]+lpOther[2]*lpOther[2]);
}


double cDoubleMatrix4::Distance(cDoubleMatrix4 *lpOther)
{
double lfX,lfY,lfZ;
 lfX=lpOther->mpData[12]-mpData[12];
 lfY=lpOther->mpData[13]-mpData[13];
 lfZ=lpOther->mpData[14]-mpData[14];

 return sqrt(lfX*lfX+lfY*lfY+lfZ*lfZ);
}

void cDoubleMatrix4::Advance(double lfDistance)
{
    if(mb3D)
    {
        mpData[12]+=mpData[8]*lfDistance;
        mpData[13]+=mpData[9]*lfDistance;
        mpData[14]+=mpData[10]*lfDistance;
    }
    else
    {
        mpData[12]+=mpData[0]*lfDistance;
        mpData[13]+=mpData[1]*lfDistance;
    }
}

void cDoubleMatrix4::Advance(double lfX,double lfY)
{
mpData[12]+=mpData[0]*lfX+mpData[4]*lfY;
mpData[13]+=mpData[1]*lfX+mpData[5]*lfY;
}

void cDoubleMatrix4::GAdvance(double lfX,double lfY)
{
 mpData[12]+=lfX;
 mpData[13]+=lfY;
}

void cDoubleMatrix4::Angle(double lfAngle)
{
  mpData[5]=mpData[0]=cos(lfAngle);
  mpData[1]=sin(lfAngle);
  mpData[4]=-mpData[1];
}

void cDoubleMatrix4::Rotate(double lfAngle)
{
 double lfCos,lfSin;
      lfCos=cos(lfAngle);
      lfSin=sin(lfAngle);

 mpTemp.Identity();

mpTemp.mpData[0]=lfCos*mpData[0]-lfSin*mpData[1];
mpTemp.mpData[1]=lfSin*mpData[0]+lfCos*mpData[1];

mpTemp.mpData[4]=lfCos*mpData[4]-lfSin*mpData[5];
mpTemp.mpData[5]=lfSin*mpData[4]+lfCos*mpData[5];

memcpy(mpData,mpTemp.mpData,6*sizeof(double));
}

void cDoubleMatrix4::GRotateOrigin(double lfAngle)
{
double lfCos,lfSin;
      lfCos=cos(lfAngle);
      lfSin=sin(lfAngle);

 mpTemp.Identity();

mpTemp.mpData[0]=lfCos*mpData[0]-lfSin*mpData[1];
mpTemp.mpData[1]=lfSin*mpData[0]+lfCos*mpData[1];

mpTemp.mpData[4]=lfCos*mpData[4]-lfSin*mpData[5];
mpTemp.mpData[5]=lfSin*mpData[4]+lfCos*mpData[5];

mpTemp.mpData[12]=lfCos*mpData[12]-lfSin*mpData[13];
mpTemp.mpData[13]=lfSin*mpData[12]+lfCos*mpData[13];
memcpy(mpData,mpTemp.mpData,14*sizeof(double));
}

void cDoubleMatrix4::GRotate(double lfAngle,double lfX,double lfY)
{
double lfCos,lfSin;
      lfCos=cos(lfAngle);
      lfSin=sin(lfAngle);

mpTemp.Identity();

mpTemp.mpData[0]=lfCos*mpData[0]-lfSin*mpData[1];
mpTemp.mpData[1]=lfSin*mpData[0]+lfCos*mpData[1];

mpTemp.mpData[4]=lfCos*mpData[4]-lfSin*mpData[5];
mpTemp.mpData[5]=lfSin*mpData[4]+lfCos*mpData[5];

mpTemp.mpData[12]=lfCos*(mpData[12]-lfX)-lfSin*(mpData[13]-lfY);
mpTemp.mpData[13]=lfSin*(mpData[12]-lfX)+lfCos*(mpData[13]-lfY);
memcpy(mpData,mpTemp.mpData,14*sizeof(double));
}

void cDoubleMatrix4::Set2D()
{
 mb3D=0;
 Identity();
 mpData[10]=mpData[5]=mpData[0]=-1.0f;
 mpData[14]=0.0f;//-(_CAMERA->Near()+1.1f);
}

void cDoubleMatrix4::Set3D()
{
 mb3D=1;
 Identity();
}

void cDoubleMatrix4::Display()
{

 printf("\n");
 printf("[%f %f %f %f,\n %f %f %f %f,\n %f %f %f %f,\n %f %f %f %f]\n",mpData[0],mpData[4],mpData[8],mpData[12],mpData[1],mpData[5],mpData[9],mpData[13],mpData[2],mpData[6],mpData[10],mpData[14],mpData[3],mpData[7],mpData[11],mpData[15]);

}

cDoubleMatrix4 cDoubleMatrix4::operator*(double *lVal)
{
 mpTemp.mpData[0]=mpData[0]*lVal[0]+mpData[4]*lVal[1]+mpData[8]*lVal[2]+mpData[12]*lVal[3];
 mpTemp.mpData[1]=mpData[1]*lVal[0]+mpData[5]*lVal[1]+mpData[9]*lVal[2]+mpData[13]*lVal[3];
 mpTemp.mpData[2]=mpData[2]*lVal[0]+mpData[6]*lVal[1]+mpData[10]*lVal[2]+mpData[14]*lVal[3];
 mpTemp.mpData[3]=mpData[3]*lVal[0]+mpData[7]*lVal[1]+mpData[11]*lVal[2]+mpData[15]*lVal[3];

 mpTemp.mpData[4]=mpData[0]*lVal[4]+mpData[4]*lVal[5]+mpData[8]*lVal[6]+mpData[12]*lVal[7];
 mpTemp.mpData[5]=mpData[1]*lVal[4]+mpData[5]*lVal[5]+mpData[9]*lVal[6]+mpData[13]*lVal[7];
 mpTemp.mpData[6]=mpData[2]*lVal[4]+mpData[6]*lVal[5]+mpData[10]*lVal[6]+mpData[14]*lVal[7];
 mpTemp.mpData[7]=mpData[3]*lVal[4]+mpData[7]*lVal[5]+mpData[11]*lVal[6]+mpData[15]*lVal[7];

 mpTemp.mpData[8]=mpData[0]*lVal[8]+mpData[4]*lVal[9]+mpData[8]*lVal[10]+mpData[12]*lVal[11];
 mpTemp.mpData[9]=mpData[1]*lVal[8]+mpData[5]*lVal[9]+mpData[9]*lVal[10]+mpData[13]*lVal[11];
 mpTemp.mpData[10]=mpData[2]*lVal[8]+mpData[6]*lVal[9]+mpData[10]*lVal[10]+mpData[14]*lVal[11];
 mpTemp.mpData[11]=mpData[3]*lVal[8]+mpData[7]*lVal[9]+mpData[11]*lVal[10]+mpData[15]*lVal[11];

 mpTemp.mpData[12]=mpData[0]*lVal[12]+mpData[4]*lVal[13]+mpData[8]*lVal[14]+mpData[12]*lVal[15];
 mpTemp.mpData[13]=mpData[1]*lVal[12]+mpData[5]*lVal[13]+mpData[9]*lVal[14]+mpData[13]*lVal[15];
 mpTemp.mpData[14]=mpData[2]*lVal[12]+mpData[6]*lVal[13]+mpData[10]*lVal[14]+mpData[14]*lVal[15];
 mpTemp.mpData[15]=mpData[3]*lVal[12]+mpData[7]*lVal[13]+mpData[11]*lVal[14]+mpData[15]*lVal[15];

 return mpTemp;

}

void cDoubleMatrix4::Rotation(double *lpRotation){memcpy(mpData,lpRotation,sizeof(double)*12);}
void cDoubleMatrix4::Rotation(cDoubleMatrix4 *lpRotation){memcpy(mpData,lpRotation->mpData,sizeof(double)*12);}
void cDoubleMatrix4::Position(cDoubleMatrix4 *lpOther){memcpy(Matrix(12),lpOther->Matrix(12),sizeof(double)*4);}
void cDoubleMatrix4::Position(cDoubleMatrix4 &lpOther){Position(&lpOther);}
void cDoubleMatrix4::Rotation(cDoubleMatrix4 &lpOther){Rotation(&lpOther);}



 double *cDoubleMatrix4::Matrix(){return mpData;};
 double *cDoubleMatrix4::Matrix(uint8 lcData){return &mpData[lcData];};
 double *cDoubleMatrix4::Position(){return &mpData[12];};

 double cDoubleMatrix4::X(){return mpData[12];};
 double cDoubleMatrix4::Y(){return mpData[13];};
 double cDoubleMatrix4::Z(){return mpData[14];};

 double *cDoubleMatrix4::XVect(){return mpData;};
 double *cDoubleMatrix4::YVect(){return &mpData[4];};
 double *cDoubleMatrix4::ZVect(){return &mpData[8];};


void cDoubleMatrix4::Advance(double *lfDistances)
{
 if(mb3D)
 {
     mpData[12]+=lfDistances[0]*mpData[0]+lfDistances[1]*mpData[4]+lfDistances[2]*mpData[8];
     mpData[13]+=lfDistances[0]*mpData[1]+lfDistances[1]*mpData[5]+lfDistances[2]*mpData[9];
     mpData[14]+=lfDistances[0]*mpData[2]+lfDistances[1]*mpData[6]+lfDistances[2]*mpData[10];
 }
 else
 {
     mpData[12]+=lfDistances[0]*mpData[0]+lfDistances[1]*mpData[4];
     mpData[13]+=lfDistances[0]*mpData[1]+lfDistances[1]*mpData[5];
 }
}
 void cDoubleMatrix4::Advance(c2DVd *lfDistances)
 {
	 mpData[12]+=lfDistances->X()*mpData[0]+lfDistances->Y()*mpData[4];
	 mpData[13]+=lfDistances->X()*mpData[1]+lfDistances->Y()*mpData[5];
 }
 void cDoubleMatrix4::Advance(c3DVd *lfDistances)
  {
	 mpData[12]+=lfDistances->X()*mpData[0]+lfDistances->Y()*mpData[4]+lfDistances->Z()*mpData[8];
	 mpData[13]+=lfDistances->X()*mpData[1]+lfDistances->Y()*mpData[5]+lfDistances->Z()*mpData[9];
	if(mb3D) mpData[14]+=lfDistances->X()*mpData[2]+lfDistances->Y()*mpData[6]+lfDistances->Z()*mpData[10];
 }
 void cDoubleMatrix4::Advance(c2DVd &lfDistances)
  {
	 mpData[12]+=lfDistances.X()*mpData[0]+lfDistances.Y()*mpData[4];
	 mpData[13]+=lfDistances.X()*mpData[1]+lfDistances.Y()*mpData[5];
 }
 void cDoubleMatrix4::Advance(c3DVd &lfDistances)
  {
	 mpData[12]+=lfDistances.X()*mpData[0]+lfDistances.Y()*mpData[4]+lfDistances.Z()*mpData[8];
	 mpData[13]+=lfDistances.X()*mpData[1]+lfDistances.Y()*mpData[5]+lfDistances.Z()*mpData[9];
	if(mb3D) mpData[14]+=lfDistances.X()*mpData[2]+lfDistances.Y()*mpData[6]+lfDistances.Z()*mpData[10];
 }

 void cDoubleMatrix4::Equals(cDoubleMatrix4 *lpOther){memcpy(mpData,lpOther->Matrix(),sizeof(double)*16);};
 void cDoubleMatrix4::Equals(cDoubleMatrix4 lpOther){memcpy(mpData,lpOther.Matrix(),sizeof(double)*16);};


void cDoubleMatrix4::Equals(cMatrix4 lVal)
{
mpData[0]=lVal[0];
mpData[1]=lVal[1];
mpData[2]=lVal[2];
mpData[3]=lVal[3];
mpData[4]=lVal[4];
mpData[5]=lVal[5];
mpData[6]=lVal[6];
mpData[7]=lVal[7];
mpData[8]=lVal[8];
mpData[9]=lVal[9];
mpData[10]=lVal[10];
mpData[11]=lVal[11];
mpData[12]=lVal[12];
mpData[13]=lVal[13];
mpData[14]=lVal[14];
mpData[15]=lVal[15];

}

void cDoubleMatrix4::Equals(cMatrix4 *lpOther)
{
 float *lVal=lpOther->Matrix();
mpData[0]=lVal[0];
mpData[1]=lVal[1];
mpData[2]=lVal[2];
mpData[3]=lVal[3];
mpData[4]=lVal[4];
mpData[5]=lVal[5];
mpData[6]=lVal[6];
mpData[7]=lVal[7];
mpData[8]=lVal[8];
mpData[9]=lVal[9];
mpData[10]=lVal[10];
mpData[11]=lVal[11];
mpData[12]=lVal[12];
mpData[13]=lVal[13];
mpData[14]=lVal[14];
mpData[15]=lVal[15];

}



 double cDoubleMatrix4::Xx(){return mpData[0];};
 double cDoubleMatrix4::Xy(){return mpData[1];};
 double cDoubleMatrix4::Xz(){return mpData[2];};
 double cDoubleMatrix4::Yx(){return mpData[4];};
 double cDoubleMatrix4::Yy(){return mpData[5];};
 double cDoubleMatrix4::Yz(){return mpData[6];};
 double cDoubleMatrix4::Zx(){return mpData[8];};
 double cDoubleMatrix4::Zy(){return mpData[9];};
 double cDoubleMatrix4::Zz(){return mpData[10];};

cDoubleMatrix4 &cDoubleMatrix4::ThisMatrix()
{
    return *this;
};

cDoubleMatrix4 *cDoubleMatrix4::ThisMatrixPointer()
{
     return this;
};

void cDoubleMatrix4::ResetRotations()
{
    memcpy(mpData,mpIdentity,sizeof(double)*12);
};

void cDoubleMatrix4::ResetPosition()
{
    memcpy(&mpData[12],&mpIdentity[12],sizeof(double)*4);
};



bool cDoubleMatrix4::AngleToPointCheck(double *lfPoint,double lfAngle)
{

    //X Axis is normal for Y/Z Plane
	//Y Axis is normal for X/Z Plane
	//Z Axis is normal for Y/X Plane

	//Can find distance from plane by counting it as the plane equation.

	//Y Plane Value = Yx()*X()+Yy()*Y()+Yz()*Z();
	//Y Point Value = Yx()*PointX+Yy()*PointY+Yz()*PointZ;
	//YDistance = Y Point Value - Y Plane Value

	//Z Plane Value = Zx()*X()+Zy()*Y()+Zz()*Z();
	//Z Point Value = Zx()*PointX+Zy()*PointY+Zz()*PointZ;
	//ZDistance = Z Point Value - Z Plane Value
	double lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];

    return AngleToVectorCheck(lfVector,lfAngle);
}

double cDoubleMatrix4::AngleToPoint(double *lfPoint)
{
    //X Axis is normal for Y/Z Plane
	//Y Axis is normal for X/Z Plane
	//Z Axis is normal for Y/X Plane

	//Can find distance from plane by counting it as the plane equation.

	//Y Plane Value = Yx()*X()+Yy()*Y()+Yz()*Z();
	//Y Point Value = Yx()*PointX+Yy()*PointY+Yz()*PointZ;
	//YDistance = Y Point Value - Y Plane Value

	//Z Plane Value = Zx()*X()+Zy()*Y()+Zz()*Z();
	//Z Point Value = Zx()*PointX+Zy()*PointY+Zz()*PointZ;
	//ZDistance = Z Point Value - Z Plane Value
	double lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];
	return AngleToVector(lfVector);
}

double cDoubleMatrix4::RollToPointPitch(double *lfPoint)
{
	//X Axis is normal for Y/Z Plane
	//Y Axis is normal for X/Z Plane
	//Z Axis is normal for Y/X Plane

	//Can find distance from plane by counting it as the plane equation.

	//Y Plane Value = Yx()*X()+Yy()*Y()+Yz()*Z();
	//Y Point Value = Yx()*PointX+Yy()*PointY+Yz()*PointZ;
	//YDistance = Y Point Value - Y Plane Value

	//Z Plane Value = Zx()*X()+Zy()*Y()+Zz()*Z();
	//Z Point Value = Zx()*PointX+Zy()*PointY+Zz()*PointZ;
	//ZDistance = Z Point Value - Z Plane Value
	double lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];

    return RollToVectorPitch(lfVector);
}


double cDoubleMatrix4::RollToPointYaw(double *lfPoint)
{
	//X Axis is normal for Y/Z Plane
	//Y Axis is normal for X/Z Plane
	//Z Axis is normal for Y/X Plane

	//Can find distance from plane by counting it as the plane equation.

	//Y Plane Value = Yx()*X()+Yy()*Y()+Yz()*Z();
	//Y Point Value = Yx()*PointX+Yy()*PointY+Yz()*PointZ;
	//YDistance = Y Point Value - Y Plane Value

	//Z Plane Value = Zx()*X()+Zy()*Y()+Zz()*Z();
	//Z Point Value = Zx()*PointX+Zy()*PointY+Zz()*PointZ;
	//ZDistance = Z Point Value - Z Plane Value
	double lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];

    return RollToVectorYaw(lfVector);
}

double cDoubleMatrix4::YawToPoint(double *lfPoint)
{
	//X Axis is normal for Y/Z Plane
	//Y Axis is normal for X/Z Plane
	//Z Axis is normal for Y/X Plane

	//X Plane Value = Xx()*X()+Xy()*Y()+Xz()*Z();
	//X Point Value = Xx()*PointX+Xy()*PointY+Xz()*PointZ;
	//XDistance = X Point Value - X Plane Value

	//Z Plane Value = Zx()*X()+Zy()*Y()+Zz()*Z();
	//Z Point Value = Zx()*PoingpPlayer->mpHull->Position()tX+Zy()*PointY+Zz()*PointZ;
	//ZDistance = Z Point Value - Z Plane Value

	double lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];

    return YawToVector(lfVector);


}

double cDoubleMatrix4::PitchToPoint(double *lfPoint)
{
	//X Axis is normal for Y/Z Plane
	//Y Axis is normal for X/Z Plane
	//Z Axis is normal for Y/X Plane

	//Can find distance from plane by counting it as the plane equation.

	//X Plane Value = Xx()*X()+Xy()*Y()+Xz()*Z();
	//X Point Value = Xx()*PointX+Xy()*PointY+Xz()*PointZ;
	//XDistance = X Point Value - X Plane Value

	//Y Plane Value = Yx()*X()+Yy()*Y()+Yz()*Z();
	//Y Point Value = Yx()*PointX+Yy()*PointY+Yz()*PointZ;
	//YDistance = Y Point Value - Y Plane Value

	double lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];

    return PitchToVector(lfVector);

}

















bool cDoubleMatrix4::AngleToVectorCheck(double *lfVector,double lfAngle)
{

	double ZDist = mpData[8]*lfVector[0]+mpData[9]*lfVector[1]+mpData[10]*lfVector[2];
	lfAngle=1.0f-lfAngle;
    if((ZDist*ZDist)>=lfAngle*(lfVector[0]*lfVector[0]+lfVector[1]*lfVector[1]+lfVector[2]*lfVector[2])) return 1;
    return 0;
}

double cDoubleMatrix4::AngleToVector(double *lfVector)
{

	double ZDist = mpData[8]*lfVector[0]+mpData[9]*lfVector[1]+mpData[10]*lfVector[2];
    return acos((ZDist*ZDist)/(lfVector[0]*lfVector[0]+lfVector[1]*lfVector[1]+lfVector[2]*lfVector[2]));
}

double cDoubleMatrix4::RollToVectorPitch(double *lfVector)
{

    double XDist = mpData[0]*lfVector[0]+mpData[1]*lfVector[1]+mpData[2]*lfVector[2];
	double YDist = mpData[4]*lfVector[0]+mpData[5]*lfVector[1]+mpData[6]*lfVector[2];

	if(YDist>0.0f) return atan2(-XDist,YDist);
	return atan2(XDist,-YDist);

}


double cDoubleMatrix4::RollToVectorYaw(double *lfVector)
{

    double XDist = mpData[0]*lfVector[0]+mpData[1]*lfVector[1]+mpData[2]*lfVector[2];
	double YDist = mpData[4]*lfVector[0]+mpData[5]*lfVector[1]+mpData[6]*lfVector[2];

	if(XDist<0.0f) return atan2(YDist,-XDist);
	return atan2(-YDist,XDist);
}

double cDoubleMatrix4::YawToVector(double *lfVector)
{

    double XDist = mpData[0]*lfVector[0]+mpData[1]*lfVector[1]+mpData[2]*lfVector[2];
	double ZDist = mpData[8]*lfVector[0]+mpData[9]*lfVector[1]+mpData[10]*lfVector[2];

	return atan2(XDist,ZDist);


}

double cDoubleMatrix4::PitchToVector(double *lfVector)
{

	double YDist = mpData[4]*lfVector[0]+mpData[5]*lfVector[1]+mpData[6]*lfVector[2];
	double ZDist = mpData[8]*lfVector[0]+mpData[9]*lfVector[1]+mpData[10]*lfVector[2];

	return atan2(-YDist,ZDist);


}


bool cDoubleMatrix4::AngleToPointCheck(c3DVd lfPoint,double lfAngle){return AngleToPointCheck(lfPoint.v,lfAngle);}
double cDoubleMatrix4::AngleToPoint(c3DVd lfPoint){return AngleToPoint(lfPoint.v);}
double cDoubleMatrix4::RollToPointPitch(c3DVd lfPoint){return RollToPointPitch(lfPoint.v);}
double cDoubleMatrix4::RollToPointYaw(c3DVd lfPoint){return RollToPointYaw(lfPoint.v);}
double cDoubleMatrix4::YawToPoint(c3DVd lfPoint){return YawToPoint(lfPoint.v);}
double cDoubleMatrix4::PitchToPoint(c3DVd lfPoint){return PitchToPoint(lfPoint.v);}
bool cDoubleMatrix4::AngleToVectorCheck(c3DVd lfVector,double lfAngle){return AngleToVectorCheck(lfVector.v,lfAngle);}
double cDoubleMatrix4::AngleToVector(c3DVd lfVector){return AngleToVector(lfVector.v);}
double cDoubleMatrix4::RollToVectorPitch(c3DVd lfVector){return RollToVectorPitch(lfVector.v);}
double cDoubleMatrix4::RollToVectorYaw(c3DVd lfVector){return RollToVectorYaw(lfVector.v);}
double cDoubleMatrix4::YawToVector(c3DVd lfVector){return YawToVector(lfVector.v);}
double cDoubleMatrix4::PitchToVector(c3DVd lfVector){return PitchToVector(lfVector.v);}





























void cDoubleMatrix4::LookVector(double *lfVect)
{
    LookVector(c3DVd(lfVect));
};

void cDoubleMatrix4::LookVector(double lfX,double lfY,double lfZ)
{
    LookVector(c3DVd(lfX,lfY,lfZ));
};


void cDoubleMatrix4::LookVector(c3DVd lfVect)
{
    double Yaw=atan2(lfVect.X(),lfVect.Z());
    double Pitch=atan2(lfVect.Y(),lfVect.Z());

    ResetRotations();
    RotateY(Yaw);
    RotateX(Pitch);
};

void cDoubleMatrix4::LookAt(double *lfPoint)
{
    LookAt(c3DVd(lfPoint));
    /*
    c3DVd Z;

    Z.v[0]=mpData[12]-lfPoint[0];
    Z.v[1]=mpData[13]-lfPoint[1];
    Z.v[2]=mpData[14]-lfPoint[2];

    double Yaw=atan2(Z.v[0],Z.v[2]);
    double Pitch=atan2(Z.v[1],Z.v[2]);

    ResetRotations();
    RotateY(Yaw);
    RotateX(Pitch);*/
};

 void cDoubleMatrix4::LookAt(cDoubleMatrix4 *lfPoint)
 {
    LookAt(c3DVd(lfPoint->Position()));
 };
 void cDoubleMatrix4::LookAt(cDoubleMatrix4 &lfPoint)
 {
    LookAt(c3DVd(lfPoint.Position()));
 };
 void cDoubleMatrix4::LookAt(double lfX,double lfY,double lfZ)
 {
     LookAt(c3DVd(lfX,lfY,lfZ));
     /*
c3DVd Z;

Z.v[0]=mpData[12]-lfX;
Z.v[1]=mpData[13]-lfY;
Z.v[2]=mpData[14]-lfZ;

double Yaw=atan2(Z.v[0],Z.v[2]);
double Pitch=atan2(Z.v[1],Z.v[2]);

ResetRotations();
RotateY(Yaw);
RotateX(Pitch);*/
 };

 void cDoubleMatrix4::LookAt(c3DVd lfVect)
 {

lfVect.v[0]=mpData[12]-lfVect[0];
lfVect.v[1]=mpData[13]-lfVect[1];
lfVect.v[2]=mpData[14]-lfVect[2];

double Yaw=atan2(lfVect.v[0],lfVect.v[2]);
double Pitch=atan2(lfVect.v[1],lfVect.v[2]);

ResetRotations();
RotateY(Yaw);
RotateX(Pitch);
 };


void cDoubleMatrix4::Translate(double *lpDist)
{
 mpData[12]+=mpData[0]*lpDist[0]+mpData[4]*lpDist[1]+mpData[8]*lpDist[2];
 mpData[13]+=mpData[1]*lpDist[0]+mpData[5]*lpDist[1]+mpData[9]*lpDist[2];
 mpData[14]+=mpData[2]*lpDist[0]+mpData[6]*lpDist[1]+mpData[10]*lpDist[2];
 mpData[15]+=mpData[3]*lpDist[0]+mpData[7]*lpDist[1]+mpData[11]*lpDist[2];
};

void cDoubleMatrix4::Translate(double lfX,double lfY,double lfZ)
{

 mpData[12]=mpData[0]*lfX+mpData[4]*lfY+mpData[8]*lfZ+mpData[12];
 mpData[13]=mpData[1]*lfX+mpData[5]*lfY+mpData[9]*lfZ+mpData[13];
 mpData[14]=mpData[2]*lfX+mpData[6]*lfY+mpData[10]*lfZ+mpData[14];
 mpData[15]=mpData[3]*lfX+mpData[7]*lfY+mpData[11]*lfZ+mpData[15];

};


void cDoubleMatrix4::Multiply(cDoubleMatrix4 &Other)
{
    Equals(operator*(&Other));
}

void cDoubleMatrix4::Multiply(cDoubleMatrix4 *Other)
 {
    Equals(operator*(Other));
 }

void cDoubleMatrix4::Multiply(double *Other)
{
    Equals(operator*(Other).Matrix());
}


void cDoubleMatrix4::Equals(double *lpOther)
{
    memcpy(mpData,lpOther,sizeof(double)*16);
}


 c4DVd cDoubleMatrix4::MultiplyVector(double *lfVector){return MultiplyVector(c4DVd(lfVector));};
 c4DVd cDoubleMatrix4::Multiply(c4DVd lfVector){return MultiplyVector(lfVector);};
 c4DVd cDoubleMatrix4::MultiplyVector(c4DVd lfVector)
 {
  c4DVd Return;
  Return.v[0]=lfVector[0]*mpData[0]+lfVector[1]*mpData[1]+lfVector[2]*mpData[2]+lfVector[3]*mpData[3];
  Return.v[1]=lfVector[0]*mpData[4]+lfVector[1]*mpData[5]+lfVector[2]*mpData[6]+lfVector[3]*mpData[7];
  Return.v[2]=lfVector[0]*mpData[8]+lfVector[1]*mpData[9]+lfVector[2]*mpData[10]+lfVector[3]*mpData[11];
  Return.v[3]=lfVector[0]*mpData[12]+lfVector[1]*mpData[13]+lfVector[2]*mpData[14]+lfVector[3]*mpData[15];
  return Return;
 };



 c3DVd cDoubleMatrix4::RotateVectorByAngles(double *lfVector){return RotateVectorByAngles(c3DVd(lfVector));};
 c3DVd cDoubleMatrix4::Multiply(c3DVd lfVector){return RotateVectorByAngles(lfVector);};
 c3DVd cDoubleMatrix4::RotateVectorByAngles(c3DVd lfVector)
 {
  c3DVd Return;
  Return.v[0]=lfVector[0]*mpData[0]+lfVector[1]*mpData[1]+lfVector[2]*mpData[2];
  Return.v[1]=lfVector[0]*mpData[4]+lfVector[1]*mpData[5]+lfVector[2]*mpData[6];
  Return.v[2]=lfVector[0]*mpData[8]+lfVector[1]*mpData[9]+lfVector[2]*mpData[10];
  return Return;
 };


 c3DVd cDoubleMatrix4::MultiplyVectorPosition(double *lfVector){return MultiplyVectorPosition(c3DVd(lfVector));};
 c3DVd cDoubleMatrix4::MultiplyVectorPosition(c3DVd lfVector)
 {
     lfVector[0]=lfVector[0]*mpData[12];
     lfVector[1]=lfVector[1]*mpData[13];
     lfVector[2]=lfVector[2]*mpData[14];
     return lfVector;
 };

void cDoubleMatrix4::InvSign()
{
  mpData[0]=-mpData[0];
  mpData[1]=-mpData[1];
  mpData[2]=-mpData[2];
  mpData[3]=-mpData[3];
  mpData[4]=-mpData[4];
  mpData[5]=-mpData[5];
  mpData[6]=-mpData[6];
  mpData[7]=-mpData[7];
  mpData[8]=-mpData[8];
  mpData[9]=-mpData[9];
  mpData[10]=-mpData[10];
  mpData[11]=-mpData[11];
  mpData[12]=-mpData[12];
  mpData[13]=-mpData[13];
  mpData[14]=-mpData[14];
  mpData[15]=-mpData[15];

};

double cDoubleMatrix4::Distance(cDoubleMatrix4 &lpOther)
{
    return Distance(&lpOther);
}

double cDoubleMatrix4::Distance(double *lpOther)
{
    return Distance(c3DVd(lpOther));
}

double cDoubleMatrix4::DistanceSq(double *lpOther)
{
    return DistanceSq(c3DVd(lpOther));
}

double cDoubleMatrix4::Distance()
{
 return sqrt(mpData[12]*mpData[12]+mpData[13]*mpData[13]+mpData[14]*mpData[14]);
};

double cDoubleMatrix4::DistanceSq()
{
 return mpData[12]*mpData[12]+mpData[13]*mpData[13]+mpData[14]*mpData[14];
};


double cDoubleMatrix4::Roll()
{
	return atan2(-mpData[4],mpData[5]);
};

double cDoubleMatrix4::Yaw()
{
	return atan2(mpData[8],mpData[10]);
};

double cDoubleMatrix4::Pitch()
{
    return atan2(mpData[9],mpData[10]);
};

bool cDoubleMatrix4::Is3D(){return mb3D;};
