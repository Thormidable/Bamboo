#include "../WTBamboo.h"

cMatrix4 cMatrix4::mpTemp;

float cMatrix4::mpZero[]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
float cMatrix4::mpIdentity[]={1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f};


cIdentityMatrix *cIdentityMatrix::spInstance=0;
cIdentityMatrix cIdentityMatrix::Instance()
{
    if(!spInstance) spInstance=new cIdentityMatrix();
    return *spInstance;
};

cMatrix4::cMatrix4(float lfX,float lfY,float lfZ,float lfXA,float lfYA,float lfZA)
{
    Identity();
    mb3D=true;
    Position(lfX,lfY,lfZ);
    if(lfXA) RotateX(lfXA);
    if(lfYA) RotateY(lfYA);
    if(lfZA) RotateZ(lfZA);
};

cMatrix4::cMatrix4(float lfX,float lfY,float lfZ)
{
    Identity();
    mb3D=true;
    Position(lfX,lfY,lfZ);
};


cZeroMatrix *cZeroMatrix::spInstance=0;
cZeroMatrix cZeroMatrix::Instance()
{
    if(!spInstance) spInstance=new cZeroMatrix();
    return *spInstance;
};

cMatrix4::cMatrix4(float *lpOther)
{
    memcpy(mpData,lpOther,sizeof(float));
    mb3D=true;
};

cMatrix4::cMatrix4(double *lpOther)
{
    mpData[0]=lpOther[0];
    mpData[1]=lpOther[1];
    mpData[2]=lpOther[2];
    mpData[3]=lpOther[3];
    mpData[4]=lpOther[4];
    mpData[5]=lpOther[5];
    mpData[6]=lpOther[6];
    mpData[7]=lpOther[7];
    mpData[8]=lpOther[8];
    mpData[9]=lpOther[9];
    mpData[10]=lpOther[10];
    mpData[11]=lpOther[11];
    mpData[12]=lpOther[12];
    mpData[13]=lpOther[13];
    mpData[14]=lpOther[14];
    mpData[15]=lpOther[15];
    mb3D=true;
};

cMatrix4::cMatrix4(const cDoubleMatrix4 &lpOther)
{
    mb3D=lpOther.mb3D;
    Equals(lpOther);
};
cMatrix4::cMatrix4(cDoubleMatrix4 *lpOther)
{
    mb3D=lpOther->Is3D();
    Equals(lpOther);
};

cMatrix4::cMatrix4()
{
 Identity();
 Set3D();
}

void cMatrix4::UpdateMatrix()
{
  if(!mb3D) _MATRIX_STACK->Identity();
 _MATRIX_STACK->Multiply(mpData);
}

void cMatrix4::UpdateMatrix(float *lpMultMatrix)
{
 mpTemp.mpData[0]=mpData[0]*lpMultMatrix[0]+mpData[4]*lpMultMatrix[1]+mpData[8]*lpMultMatrix[2]+mpData[12]*mpData[3];
 mpTemp.mpData[1]=mpData[1]*lpMultMatrix[0]+mpData[5]*lpMultMatrix[1]+mpData[9]*lpMultMatrix[2]+mpData[13]*mpData[3];
 mpTemp.mpData[2]=mpData[2]*lpMultMatrix[0]+mpData[6]*lpMultMatrix[1]+mpData[10]*lpMultMatrix[2]+mpData[14]*mpData[3];
 mpTemp.mpData[3]=mpData[3]*lpMultMatrix[0]+mpData[7]*lpMultMatrix[1]+mpData[11]*lpMultMatrix[2]+mpData[15]*mpData[3];

 mpTemp.mpData[4]=mpData[0]*lpMultMatrix[4]+mpData[4]*lpMultMatrix[5]+mpData[8]*lpMultMatrix[6]+mpData[12]*mpData[7];
 mpTemp.mpData[5]=mpData[1]*lpMultMatrix[4]+mpData[5]*lpMultMatrix[5]+mpData[9]*lpMultMatrix[6]+mpData[13]*mpData[7];
 mpTemp.mpData[6]=mpData[2]*lpMultMatrix[4]+mpData[6]*lpMultMatrix[5]+mpData[10]*lpMultMatrix[6]+mpData[14]*mpData[7];
 mpTemp.mpData[7]=mpData[3]*lpMultMatrix[4]+mpData[7]*lpMultMatrix[5]+mpData[11]*lpMultMatrix[6]+mpData[15]*mpData[7];

 mpTemp.mpData[8]=mpData[0]*lpMultMatrix[8]+mpData[4]*lpMultMatrix[9]+mpData[8]*lpMultMatrix[10]+mpData[12]*mpData[11];
 mpTemp.mpData[9]=mpData[1]*lpMultMatrix[8]+mpData[5]*lpMultMatrix[9]+mpData[9]*lpMultMatrix[10]+mpData[13]*mpData[11];
 mpTemp.mpData[10]=mpData[2]*lpMultMatrix[8]+mpData[6]*lpMultMatrix[9]+mpData[10]*lpMultMatrix[10]+mpData[14]*mpData[11];
 mpTemp.mpData[11]=mpData[3]*lpMultMatrix[8]+mpData[7]*lpMultMatrix[9]+mpData[11]*lpMultMatrix[10]+mpData[15]*mpData[11];

 mpTemp.mpData[12]=mpData[0]*lpMultMatrix[12]+mpData[4]*lpMultMatrix[13]+mpData[8]*lpMultMatrix[14]+mpData[12]*mpData[15];
 mpTemp.mpData[13]=mpData[1]*lpMultMatrix[12]+mpData[5]*lpMultMatrix[13]+mpData[9]*lpMultMatrix[14]+mpData[13]*mpData[15];
 mpTemp.mpData[14]=mpData[2]*lpMultMatrix[12]+mpData[6]*lpMultMatrix[13]+mpData[10]*lpMultMatrix[14]+mpData[14]*mpData[15];
 mpTemp.mpData[15]=mpData[3]*lpMultMatrix[12]+mpData[7]*lpMultMatrix[13]+mpData[11]*lpMultMatrix[14]+mpData[15]*mpData[15];

 memcpy(mpData,mpTemp.Matrix(),sizeof(float)*16);
}


cMatrix4 cMatrix4::operator+(float &lVal)
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

cMatrix4 cMatrix4::operator+(const float lVal)
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

cMatrix4 cMatrix4::operator-(float &lVal)
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

cMatrix4 cMatrix4::operator-(const float lVal)
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

cMatrix4 cMatrix4::operator*(float &lVal)
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

cMatrix4 cMatrix4::operator*(const float lVal)
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

cMatrix4 cMatrix4::operator/(float &lVal)
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

cMatrix4 cMatrix4::operator/(const float lVal)
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


cMatrix4 cMatrix4::operator=(float *lVal)
{
 memcpy(mpData,lVal,sizeof(float)*16);
 return *this;
}

cMatrix4 cMatrix4::operator=(cMatrix4 lVal)
{
memcpy(mpData,lVal.mpData,sizeof(float)*16);
return lVal;
}


cMatrix4 cMatrix4::operator=(cDoubleMatrix4 lVal)
{
    Equals(lVal);
return *this;
}


cMatrix4 cMatrix4::operator=(cDoubleMatrix4 *lVal)
{
Equals(lVal);
return *this;
}

float cMatrix4::operator=(float &lVal)
{
 memset(mpData,lVal,sizeof(float)*16);
 return lVal;
}

float cMatrix4::operator=(const float lVal)
{
// memset(mpData,lVal,9*sizeof(float));
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
cMatrix4 &cMatrix4::operator=(cMatrix4 &lVal)
{
 memcpy(mpData,lVal.mpData,16*sizeof(float));
 return this;
}
*/
cMatrix4 cMatrix4::operator=(cMatrix4 *lVal)
{
 memcpy(mpData,lVal->mpData,16*sizeof(float));
 return *this;
}

void cMatrix4::Zero()
{
 memcpy(mpData,mpZero,16*sizeof(float));
}

void cMatrix4::Identity()
{
 memcpy(mpData,mpIdentity,16*sizeof(float));
}

cMatrix4 cMatrix4::operator+(cMatrix4 &lVal)
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

cMatrix4 cMatrix4::operator-(cMatrix4 &lVal)
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


float cMatrix4::Determinant()
{
 return
 mpData[0]*(mpData[5]*(mpData[10]*mpData[15]-mpData[14]*mpData[11])-mpData[9]*(mpData[6]*mpData[15]-mpData[14]*mpData[7])+mpData[13]*(mpData[6]*mpData[11]-mpData[10]*mpData[7]))
 -mpData[4]*(mpData[1]*(mpData[10]*mpData[15]-mpData[11]*mpData[14])-mpData[9]*(mpData[2]*mpData[15]-mpData[14]*mpData[3])+mpData[13]*(mpData[2]*mpData[11]-mpData[10]*mpData[3]))
 +mpData[8]*(mpData[1]*(mpData[6]*mpData[10]-mpData[14]*mpData[7])-mpData[5]*(mpData[2]*mpData[15]-mpData[3]*mpData[14])+mpData[13]*(mpData[2]*mpData[7]-mpData[6]*mpData[3]))
 -mpData[12]*(mpData[1]*(mpData[6]*mpData[11]-mpData[10]*mpData[7])-mpData[5]*(mpData[2]*mpData[11]-mpData[10]*mpData[3])+mpData[9]*(mpData[2]*mpData[7]-mpData[6]*mpData[3]));
}
/*
cMatrix4 cMatrix4::InvertRotationMatrix()
{
uint32 CHECK_IF_THIS_SHOULD_INVERT_THE_SIGN_OF_THE_OUTPUTED_VALUES;
float Tmp[12];

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
	float Det = -1.0f / ((mpData[0] * mpTemp.mpData[0]) + (mpData[4] * mpTemp.mpData[1]) + (mpData[8] * mpTemp.mpData[2]) + (mpData[12] * mpTemp.mpData[3]));

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

cMatrix4 cMatrix4::InversionMatrix()
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
cMatrix4 cMatrix4::Transpose()
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

cMatrix4 cMatrix4::operator*(cMatrix4 lVal)
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


cMatrix4 *cMatrix4::operator*(cMatrix4 *lVal)
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


float &cMatrix4::operator[](uint16 liPos)
{
 return mpData[liPos];
}

float &cMatrix4::operator()(uint16 liColumn,uint16 liRow)
{
 return mpData[liColumn*4+liRow];
}

void cMatrix4::Position(float lfX,float lfY)
{
 mpData[12]=lfX;
 mpData[13]=lfY;
}

void cMatrix4::Position(float lfX,float lfY,float lfZ)
{
 mpData[12]=lfX;
 mpData[13]=lfY;
 mpData[14]=lfZ;
}

void cMatrix4::Position(float *lpPos)
{
 if(mb3D) memcpy(&mpData[12],lpPos,sizeof(float)*3);
 else memcpy(&mpData[12],lpPos,sizeof(float)*2);
}

void cMatrix4::Position(c2DVf *lpPosition)
{
 memcpy(&mpData[13],lpPosition->v,sizeof(float)*2);
}

void cMatrix4::Position(c3DVf *lpPosition)
{
 memcpy(&mpData[13],lpPosition->v,sizeof(float)*3);
}

void cMatrix4::PositionX(float lfX)
{
 mpData[12]=lfX;
}
void cMatrix4::PositionY(float lfY)
{
 mpData[13]=lfY;
}
void cMatrix4::PositionZ(float lfZ)
{
 mpData[14]=lfZ;
}

void cMatrix4::RotateX(float lfAngle)
{
 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[4]=mpData[4]*lfCos+mpData[8]*lfSin;
mpTemp.mpData[5]=mpData[5]*lfCos+mpData[9]*lfSin;
mpTemp.mpData[6]=mpData[6]*lfCos+mpData[10]*lfSin;
mpTemp.mpData[7]=0;

mpTemp.mpData[8] =mpData[8] *lfCos-mpData[4]*lfSin;
mpTemp.mpData[9] =mpData[9] *lfCos-mpData[5]*lfSin;
mpTemp.mpData[10]=mpData[10]*lfCos-mpData[6]*lfSin;

memcpy(&mpData[4],&mpTemp.mpData[4],7*sizeof(float));
}


void cMatrix4::RotateY(float lfAngle)
{
 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0]*lfCos-mpData[8]*lfSin;
mpTemp.mpData[1]=mpData[1]*lfCos-mpData[9]*lfSin;
mpTemp.mpData[2]=mpData[2]*lfCos-mpData[10]*lfSin;
mpTemp.mpData[3]=0;

memcpy(&mpTemp.mpData[4],&mpData[4],4*sizeof(float));

mpTemp.mpData[8]=mpData[0]*lfSin+mpData[8]*lfCos;
mpTemp.mpData[9]=mpData[1]*lfSin+mpData[9]*lfCos;
mpTemp.mpData[10]=mpData[2]*lfSin+mpData[10]*lfCos;

memcpy(mpData,mpTemp.mpData,11*sizeof(float));
}


void cMatrix4::RotateZ(float lfAngle)
{
 float lfCos,lfSin;

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
memcpy(mpData,mpTemp.mpData,8*sizeof(float));

}

void cMatrix4::AdvanceX(float lfDistance)
{
mpData[12]+=mpData[0]*lfDistance;
mpData[13]+=mpData[1]*lfDistance;
mpData[14]+=mpData[2]*lfDistance;
}

void cMatrix4::AdvanceY(float lfDistance)
{
mpData[12]+=mpData[4]*lfDistance;
mpData[13]+=mpData[5]*lfDistance;
mpData[14]+=mpData[6]*lfDistance;
}

void cMatrix4::AdvanceZ(float lfDistance)
{
mpData[12]+=mpData[8]*lfDistance;
mpData[13]+=mpData[9]*lfDistance;
mpData[14]+=mpData[10]*lfDistance;
}

void cMatrix4::Advance(float lfX,float lfY,float lfZ)
{
mpData[12]+=mpData[0]*lfX+mpData[4]*lfY+mpData[8]*lfZ;
mpData[13]+=mpData[1]*lfX+mpData[5]*lfY+mpData[9]*lfZ;
mpData[14]+=mpData[2]*lfX+mpData[6]*lfY+mpData[10]*lfZ;
}

void cMatrix4::GAdvance(float *lfDistance)
{
	mpData[12]+=lfDistance[0];
	mpData[13]+=lfDistance[1];
	mpData[14]+=lfDistance[2];
};

void cMatrix4::GAdvanceX(float lfX)
{mpData[12]+=lfX;}

void cMatrix4::GAdvanceY(float lfY)
{mpData[13]+=lfY;}

void cMatrix4::GAdvanceZ(float lfZ)
{mpData[14]+=lfZ;}

void cMatrix4::GAdvance(float lfX,float lfY,float lfZ)
{
 mpData[12]+=lfX;
 mpData[13]+=lfY;
 mpData[14]+=lfZ;
}

void cMatrix4::GRotateX(float lfAngle)
{
 float lfCos,lfSin;

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

memcpy(mpData,mpTemp.mpData,11*sizeof(float));
}


void cMatrix4::GRotateY(float lfAngle)
{

 float lfCos,lfSin;
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

memcpy(mpData,mpTemp.mpData,11*sizeof(float));
}

void cMatrix4::GRotateZ(float lfAngle)
{

float lfCos,lfSin;
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

memcpy(mpData,mpTemp.mpData,11*sizeof(float));

}

void cMatrix4::Resize(float lfScale)
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

void cMatrix4::ResizeX(float lfScale)
{
 mpData[0]=mpData[0]*lfScale;
 mpData[1]=mpData[1]*lfScale;
 mpData[2]=mpData[2]*lfScale;
}

void cMatrix4::ResizeY(float lfScale)
{

 mpData[4]=mpData[4]*lfScale;
 mpData[5]=mpData[5]*lfScale;
 mpData[6]=mpData[6]*lfScale;
}

void cMatrix4::ResizeZ(float lfScale)
{

 mpData[8]=mpData[8]*lfScale;
 mpData[9]=mpData[9]*lfScale;
 mpData[10]=mpData[10]*lfScale;
}

 void cMatrix4::ScaleX(float lfScale)
 {
     double lfCurrent=lfScale/ScaleX();
     mpData[0]*=lfCurrent;
     mpData[1]*=lfCurrent;
     mpData[2]*=lfCurrent;
 }
 void cMatrix4::ScaleY(float lfScale)
 {
     double lfCurrent=lfScale/ScaleY();
     mpData[4]*=lfCurrent;
     mpData[5]*=lfCurrent;
     mpData[6]*=lfCurrent;
 }

 void cMatrix4::ScaleZ(float lfScale)
 {
     double lfCurrent=lfScale/ScaleZ();
     mpData[8]*=lfCurrent;
     mpData[9]*=lfCurrent;
     mpData[10]*=lfCurrent;
 }

  void cMatrix4::GScaleX(float lfScale)
 {
     double lfCurrent=lfScale/GScaleX();
     mpData[0]*=lfCurrent;
     mpData[4]*=lfCurrent;
     mpData[8]*=lfCurrent;
 }
 void cMatrix4::GScaleY(float lfScale)
 {
     double lfCurrent=lfScale/GScaleY();
     mpData[1]*=lfCurrent;
     mpData[5]*=lfCurrent;
     mpData[9]*=lfCurrent;
 }

 void cMatrix4::GScaleZ(float lfScale)
 {
     double lfCurrent=lfScale/GScaleZ();
     mpData[2]*=lfCurrent;
     mpData[6]*=lfCurrent;
     mpData[10]*=lfCurrent;
 }


 float cMatrix4::ScaleX()
 {
     return sqrt(mpData[0]*mpData[0]+mpData[1]*mpData[1]+mpData[2]*mpData[2]);
 }

 float cMatrix4::ScaleY()
 {
     return sqrt(mpData[4]*mpData[4]+mpData[5]*mpData[5]+mpData[6]*mpData[6]);
 }

 float cMatrix4::ScaleZ()
 {
     return sqrt(mpData[8]*mpData[8]+mpData[9]*mpData[9]+mpData[10]*mpData[10]);
 }

  float cMatrix4::GScaleX()
 {
     return sqrt(mpData[0]*mpData[0]+mpData[4]*mpData[4]+mpData[8]*mpData[8]);
 }

 float cMatrix4::GScaleY()
 {
     return sqrt(mpData[1]*mpData[1]+mpData[5]*mpData[5]+mpData[9]*mpData[9]);
 }

 float cMatrix4::GScaleZ()
 {
     return sqrt(mpData[2]*mpData[2]+mpData[6]*mpData[6]+mpData[10]*mpData[10]);
 }

void cMatrix4::GResizeX(float lfScale)
{
 mpData[0]=mpData[0]*lfScale;
 mpData[4]=mpData[4]*lfScale;
 mpData[8]=mpData[8]*lfScale;
}

void cMatrix4::GResizeY(float lfScale)
{

 mpData[1]=mpData[1]*lfScale;
 mpData[5]=mpData[5]*lfScale;
 mpData[9]=mpData[9]*lfScale;

}
void cMatrix4::GResizeZ(float lfScale)
{
 mpData[2]=mpData[2]*lfScale;
 mpData[6]=mpData[6]*lfScale;
 mpData[10]=mpData[10]*lfScale;

}


void cMatrix4::GRotateOriginX(float lfAngle)
{
 float lfCos,lfSin;

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

memcpy(mpData,mpTemp.mpData,15*sizeof(float));
}

void cMatrix4::GRotateOriginY(float lfAngle)
{

 float lfCos,lfSin;
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

memcpy(mpData,mpTemp.mpData,15*sizeof(float));
}

void cMatrix4::GRotateOriginZ(float lfAngle)
{

float lfCos,lfSin;
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

memcpy(mpData,mpTemp.mpData,15*sizeof(float));
}

void cMatrix4::GRotateX(float lfAngle,float lfX,float lfY,float lfZ)
{
 (void) lfX;
 float lfCos,lfSin;

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

memcpy(&mpData[1],&mpTemp.mpData[1],14*sizeof(float));

}

void cMatrix4::GRotateY(float lfAngle,float lfX,float lfY,float lfZ)
{
(void) lfY;
 float lfCos,lfSin;
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

memcpy(mpData,mpTemp.mpData,15*sizeof(float));

}

void cMatrix4::GRotateZ(float lfAngle,float lfX,float lfY,float lfZ)
{
(void) lfZ;
float lfCos,lfSin;
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

memcpy(mpData,mpTemp.mpData,14*sizeof(float));
}

double cMatrix4::DistanceSq(cMatrix4 lpOther)
{
 float lfX,lfY,lfZ;

 lfX=lpOther.mpData[12]-mpData[12];
 lfY=lpOther.mpData[13]-mpData[13];
 lfZ=lpOther.mpData[14]-mpData[14];

 return (lfX*lfX+lfY*lfY+lfZ*lfZ);
}


double cMatrix4::DistanceSq(cMatrix4 *lpOther)
{
 float lfX,lfY,lfZ;
 lfX=lpOther->mpData[12]-mpData[12];
 lfY=lpOther->mpData[13]-mpData[13];
 lfZ=lpOther->mpData[14]-mpData[14];


 return (lfX*lfX+lfY*lfY+lfZ*lfZ);
}

double cMatrix4::DistanceSq(c3DVf lpOther)
{
 lpOther[0]=lpOther[0]-mpData[12];
 lpOther[1]=lpOther[1]-mpData[13];
 lpOther[2]=lpOther[2]-mpData[14];

 return lpOther[0]*lpOther[0]+lpOther[1]*lpOther[1]+lpOther[2]*lpOther[2];
}

float cMatrix4::Distance(c3DVf lpOther)
{
 lpOther[0]=lpOther[0]-mpData[12];
 lpOther[1]=lpOther[1]-mpData[13];
 lpOther[2]=lpOther[2]-mpData[14];

 return sqrt(lpOther[0]*lpOther[0]+lpOther[1]*lpOther[1]+lpOther[2]*lpOther[2]);
}


float cMatrix4::Distance(cMatrix4 *lpOther)
{
float lfX,lfY,lfZ;
 lfX=lpOther->mpData[12]-mpData[12];
 lfY=lpOther->mpData[13]-mpData[13];
 lfZ=lpOther->mpData[14]-mpData[14];

 return sqrt(lfX*lfX+lfY*lfY+lfZ*lfZ);
}

void cMatrix4::Advance(float lfDistance)
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

void cMatrix4::Advance(float lfX,float lfY)
{
mpData[12]+=mpData[0]*lfX+mpData[4]*lfY;
mpData[13]+=mpData[1]*lfX+mpData[5]*lfY;
}

void cMatrix4::GAdvance(float lfX,float lfY)
{
 mpData[12]+=lfX;
 mpData[13]+=lfY;
}

void cMatrix4::Angle(float lfAngle)
{
  mpData[5]=mpData[0]=cos(lfAngle);
  mpData[1]=sin(lfAngle);
  mpData[4]=-mpData[1];
}

void cMatrix4::Rotate(float lfAngle)
{
 float lfCos,lfSin;
      lfCos=cos(lfAngle);
      lfSin=sin(lfAngle);

 mpTemp.Identity();

mpTemp.mpData[0]=lfCos*mpData[0]-lfSin*mpData[1];
mpTemp.mpData[1]=lfSin*mpData[0]+lfCos*mpData[1];

mpTemp.mpData[4]=lfCos*mpData[4]-lfSin*mpData[5];
mpTemp.mpData[5]=lfSin*mpData[4]+lfCos*mpData[5];

memcpy(mpData,mpTemp.mpData,6*sizeof(float));
}

void cMatrix4::GRotateOrigin(float lfAngle)
{
float lfCos,lfSin;
      lfCos=cos(lfAngle);
      lfSin=sin(lfAngle);

 mpTemp.Identity();

mpTemp.mpData[0]=lfCos*mpData[0]-lfSin*mpData[1];
mpTemp.mpData[1]=lfSin*mpData[0]+lfCos*mpData[1];

mpTemp.mpData[4]=lfCos*mpData[4]-lfSin*mpData[5];
mpTemp.mpData[5]=lfSin*mpData[4]+lfCos*mpData[5];

mpTemp.mpData[12]=lfCos*mpData[12]-lfSin*mpData[13];
mpTemp.mpData[13]=lfSin*mpData[12]+lfCos*mpData[13];
memcpy(mpData,mpTemp.mpData,14*sizeof(float));
}

void cMatrix4::GRotate(float lfAngle,float lfX,float lfY)
{
float lfCos,lfSin;
      lfCos=cos(lfAngle);
      lfSin=sin(lfAngle);

mpTemp.Identity();

mpTemp.mpData[0]=lfCos*mpData[0]-lfSin*mpData[1];
mpTemp.mpData[1]=lfSin*mpData[0]+lfCos*mpData[1];

mpTemp.mpData[4]=lfCos*mpData[4]-lfSin*mpData[5];
mpTemp.mpData[5]=lfSin*mpData[4]+lfCos*mpData[5];

mpTemp.mpData[12]=lfCos*(mpData[12]-lfX)-lfSin*(mpData[13]-lfY);
mpTemp.mpData[13]=lfSin*(mpData[12]-lfX)+lfCos*(mpData[13]-lfY);
memcpy(mpData,mpTemp.mpData,14*sizeof(float));
}

void cMatrix4::Set2D()
{
 mb3D=0;
 Identity();
 mpData[10]=mpData[5]=mpData[0]=-1.0f;
 mpData[14]=0.0f;//-(_CAMERA->Near()+1.1f);
}

void cMatrix4::Set3D()
{
 mb3D=1;
 Identity();
}

void cMatrix4::Display()
{

 printf("\n");
 printf("[%f %f %f %f,\n %f %f %f %f,\n %f %f %f %f,\n %f %f %f %f]\n",mpData[0],mpData[4],mpData[8],mpData[12],mpData[1],mpData[5],mpData[9],mpData[13],mpData[2],mpData[6],mpData[10],mpData[14],mpData[3],mpData[7],mpData[11],mpData[15]);

}

cMatrix4 cMatrix4::operator*(float *lVal)
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

void cMatrix4::Rotation(float *lpRotation){memcpy(mpData,lpRotation,sizeof(float)*12);}
void cMatrix4::Rotation(cMatrix4 *lpRotation){memcpy(mpData,lpRotation->mpData,sizeof(float)*12);}
void cMatrix4::Position(cMatrix4 *lpOther){memcpy(Matrix(12),lpOther->Matrix(12),sizeof(float)*4);}
void cMatrix4::Position(cMatrix4 &lpOther){Position(&lpOther);}
void cMatrix4::Rotation(cMatrix4 &lpOther){Rotation(&lpOther);}



 float *cMatrix4::Matrix(){return mpData;};
 float *cMatrix4::Matrix(uint8 lcData){return &mpData[lcData];};
 float *cMatrix4::Position(){return &mpData[12];};

 float cMatrix4::X(){return mpData[12];};
 float cMatrix4::Y(){return mpData[13];};
 float cMatrix4::Z(){return mpData[14];};

 float *cMatrix4::XVect(){return mpData;};
 float *cMatrix4::YVect(){return &mpData[4];};
 float *cMatrix4::ZVect(){return &mpData[8];};


void cMatrix4::Advance(float *lfDistances)
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
 void cMatrix4::Advance(c2DVf *lfDistances)
 {
	 mpData[12]+=lfDistances->X()*mpData[0]+lfDistances->Y()*mpData[4];
	 mpData[13]+=lfDistances->X()*mpData[1]+lfDistances->Y()*mpData[5];
 }
 void cMatrix4::Advance(c3DVf *lfDistances)
  {
	 mpData[12]+=lfDistances->X()*mpData[0]+lfDistances->Y()*mpData[4]+lfDistances->Z()*mpData[8];
	 mpData[13]+=lfDistances->X()*mpData[1]+lfDistances->Y()*mpData[5]+lfDistances->Z()*mpData[9];
	if(mb3D) mpData[14]+=lfDistances->X()*mpData[2]+lfDistances->Y()*mpData[6]+lfDistances->Z()*mpData[10];
 }
 void cMatrix4::Advance(c2DVf &lfDistances)
  {
	 mpData[12]+=lfDistances.X()*mpData[0]+lfDistances.Y()*mpData[4];
	 mpData[13]+=lfDistances.X()*mpData[1]+lfDistances.Y()*mpData[5];
 }
 void cMatrix4::Advance(c3DVf &lfDistances)
  {
	 mpData[12]+=lfDistances.X()*mpData[0]+lfDistances.Y()*mpData[4]+lfDistances.Z()*mpData[8];
	 mpData[13]+=lfDistances.X()*mpData[1]+lfDistances.Y()*mpData[5]+lfDistances.Z()*mpData[9];
	if(mb3D) mpData[14]+=lfDistances.X()*mpData[2]+lfDistances.Y()*mpData[6]+lfDistances.Z()*mpData[10];
 }

 void cMatrix4::Equals(cMatrix4 *lpOther){memcpy(mpData,lpOther->Matrix(),sizeof(float)*16); mb3D=lpOther->Is3D();};
 void cMatrix4::Equals(cMatrix4 lpOther){memcpy(mpData,lpOther.Matrix(),sizeof(float)*16); mb3D=lpOther.Is3D();};
 void cMatrix4::Equals(cDoubleMatrix4 *lpOther)
 {
    double *lVal=lpOther->Matrix();
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
    mb3D=lpOther->Is3D();
 };
 void cMatrix4::Equals(cDoubleMatrix4 lVal)
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
    mb3D=lVal.Is3D();

 };




 float cMatrix4::Xx(){return mpData[0];};
 float cMatrix4::Xy(){return mpData[1];};
 float cMatrix4::Xz(){return mpData[2];};
 float cMatrix4::Yx(){return mpData[4];};
 float cMatrix4::Yy(){return mpData[5];};
 float cMatrix4::Yz(){return mpData[6];};
 float cMatrix4::Zx(){return mpData[8];};
 float cMatrix4::Zy(){return mpData[9];};
 float cMatrix4::Zz(){return mpData[10];};

cMatrix4 &cMatrix4::ThisMatrix()
{
    return *this;
};

cMatrix4 *cMatrix4::ThisMatrixPointer()
{
     return this;
};

void cMatrix4::ResetRotations()
{
    memcpy(mpData,mpIdentity,sizeof(float)*12);
};

void cMatrix4::ResetPosition()
{
    memcpy(&mpData[12],&mpIdentity[12],sizeof(float)*4);
};



bool cMatrix4::AngleToPointCheck(float *lfPoint,float lfAngle)
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
	float lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];

    return AngleToVectorCheck(lfVector,lfAngle);
}

float cMatrix4::AngleToPoint(float *lfPoint)
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
	float lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];
	return AngleToVector(lfVector);
}

float cMatrix4::RollToPointPitch(float *lfPoint)
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
	float lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];

    return RollToVectorPitch(lfVector);
}


float cMatrix4::RollToPointYaw(float *lfPoint)
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
	float lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];

    return RollToVectorYaw(lfVector);
}

float cMatrix4::YawToPoint(float *lfPoint)
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

	float lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];

    return YawToVector(lfVector);


}

float cMatrix4::PitchToPoint(float *lfPoint)
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

	float lfVector[3];

	lfVector[0]=lfPoint[0]-mpData[12];
	lfVector[1]=lfPoint[1]-mpData[13];
	lfVector[2]=lfPoint[2]-mpData[14];

    return PitchToVector(lfVector);

}

















bool cMatrix4::AngleToVectorCheck(float *lfVector,float lfAngle)
{

	float ZDist = mpData[8]*lfVector[0]+mpData[9]*lfVector[1]+mpData[10]*lfVector[2];
	lfAngle=1.0f-lfAngle;
    if((ZDist*ZDist)>=lfAngle*(lfVector[0]*lfVector[0]+lfVector[1]*lfVector[1]+lfVector[2]*lfVector[2])) return 1;
    return 0;
}

float cMatrix4::AngleToVector(float *lfVector)
{

	float ZDist = mpData[8]*lfVector[0]+mpData[9]*lfVector[1]+mpData[10]*lfVector[2];
    return acos((ZDist*ZDist)/(lfVector[0]*lfVector[0]+lfVector[1]*lfVector[1]+lfVector[2]*lfVector[2]));
}

float cMatrix4::RollToVectorPitch(float *lfVector)
{

    float XDist = mpData[0]*lfVector[0]+mpData[1]*lfVector[1]+mpData[2]*lfVector[2];
	float YDist = mpData[4]*lfVector[0]+mpData[5]*lfVector[1]+mpData[6]*lfVector[2];

	if(YDist>0.0f) return atan2(-XDist,YDist);
	return atan2(XDist,-YDist);

}


float cMatrix4::RollToVectorYaw(float *lfVector)
{

    float XDist = mpData[0]*lfVector[0]+mpData[1]*lfVector[1]+mpData[2]*lfVector[2];
	float YDist = mpData[4]*lfVector[0]+mpData[5]*lfVector[1]+mpData[6]*lfVector[2];

	if(XDist<0.0f) return atan2(YDist,-XDist);
	return atan2(-YDist,XDist);
}

float cMatrix4::YawToVector(float *lfVector)
{

    float XDist = mpData[0]*lfVector[0]+mpData[1]*lfVector[1]+mpData[2]*lfVector[2];
	float ZDist = mpData[8]*lfVector[0]+mpData[9]*lfVector[1]+mpData[10]*lfVector[2];

	return atan2(XDist,ZDist);


}

float cMatrix4::PitchToVector(float *lfVector)
{

	float YDist = mpData[4]*lfVector[0]+mpData[5]*lfVector[1]+mpData[6]*lfVector[2];
	float ZDist = mpData[8]*lfVector[0]+mpData[9]*lfVector[1]+mpData[10]*lfVector[2];

	return atan2(-YDist,ZDist);


}


bool cMatrix4::AngleToPointCheck(c3DVf lfPoint,float lfAngle){return AngleToPointCheck(lfPoint.v,lfAngle);}
float cMatrix4::AngleToPoint(c3DVf lfPoint){return AngleToPoint(lfPoint.v);}
float cMatrix4::RollToPointPitch(c3DVf lfPoint){return RollToPointPitch(lfPoint.v);}
float cMatrix4::RollToPointYaw(c3DVf lfPoint){return RollToPointYaw(lfPoint.v);}
float cMatrix4::YawToPoint(c3DVf lfPoint){return YawToPoint(lfPoint.v);}
float cMatrix4::PitchToPoint(c3DVf lfPoint){return PitchToPoint(lfPoint.v);}
bool cMatrix4::AngleToVectorCheck(c3DVf lfVector,float lfAngle){return AngleToVectorCheck(lfVector.v,lfAngle);}
float cMatrix4::AngleToVector(c3DVf lfVector){return AngleToVector(lfVector.v);}
float cMatrix4::RollToVectorPitch(c3DVf lfVector){return RollToVectorPitch(lfVector.v);}
float cMatrix4::RollToVectorYaw(c3DVf lfVector){return RollToVectorYaw(lfVector.v);}
float cMatrix4::YawToVector(c3DVf lfVector){return YawToVector(lfVector.v);}
float cMatrix4::PitchToVector(c3DVf lfVector){return PitchToVector(lfVector.v);}





























void cMatrix4::LookVector(float *lfVect)
{
    LookVector(c3DVf(lfVect));
};

void cMatrix4::LookVector(float lfX,float lfY,float lfZ)
{
    LookVector(c3DVf(lfX,lfY,lfZ));
};


void cMatrix4::LookVector(c3DVf lfVect)
{
    double Yaw=atan2(lfVect.X(),lfVect.Z());
    double Pitch=atan2(lfVect.Y(),sqrt(lfVect[0]*lfVect[0]+lfVect[2]*lfVect[2]));

    ResetRotations();
    RotateY(Yaw);
    RotateX(-Pitch);
};

void cMatrix4::LookAt(float *lfPoint)
{
    LookAt(c3DVf(lfPoint));
    /*
    c3DVf Z;

    Z.v[0]=mpData[12]-lfPoint[0];
    Z.v[1]=mpData[13]-lfPoint[1];
    Z.v[2]=mpData[14]-lfPoint[2];

    double Yaw=atan2(Z.v[0],Z.v[2]);
    double Pitch=atan2(Z.v[1],Z.v[2]);

    ResetRotations();
    RotateY(Yaw);
    RotateX(Pitch);*/
};

 void cMatrix4::LookAt(cMatrix4 *lfPoint)
 {
    LookAt(c3DVf(lfPoint->Position()));
 };
 void cMatrix4::LookAt(cMatrix4 &lfPoint)
 {
    LookAt(c3DVf(lfPoint.Position()));
 };
 void cMatrix4::LookAt(float lfX,float lfY,float lfZ)
 {
     LookAt(c3DVf(lfX,lfY,lfZ));
     /*
c3DVf Z;

Z.v[0]=mpData[12]-lfX;
Z.v[1]=mpData[13]-lfY;
Z.v[2]=mpData[14]-lfZ;

double Yaw=atan2(Z.v[0],Z.v[2]);
double Pitch=atan2(Z.v[1],Z.v[2]);

ResetRotations();
RotateY(Yaw);
RotateX(Pitch);*/
 };

 void cMatrix4::LookAt(c3DVf lfVect)
 {

lfVect.v[0]=mpData[12]-lfVect[0];
lfVect.v[1]=mpData[13]-lfVect[1];
lfVect.v[2]=mpData[14]-lfVect[2];

double Yaw=atan2(lfVect.v[0],-lfVect.v[2]);
double Pitch=atan2(lfVect.v[1],sqrt(lfVect[0]*lfVect[0]+lfVect[2]*lfVect[2]));

ResetRotations();
RotateY(-Yaw);
RotateX(Pitch);
 };


void cMatrix4::Translate(float *lpDist)
{
 mpData[12]+=mpData[0]*lpDist[0]+mpData[4]*lpDist[1]+mpData[8]*lpDist[2];
 mpData[13]+=mpData[1]*lpDist[0]+mpData[5]*lpDist[1]+mpData[9]*lpDist[2];
 mpData[14]+=mpData[2]*lpDist[0]+mpData[6]*lpDist[1]+mpData[10]*lpDist[2];
 mpData[15]+=mpData[3]*lpDist[0]+mpData[7]*lpDist[1]+mpData[11]*lpDist[2];
};

void cMatrix4::Translate(float lfX,float lfY,float lfZ)
{

 mpData[12]=mpData[0]*lfX+mpData[4]*lfY+mpData[8]*lfZ+mpData[12];
 mpData[13]=mpData[1]*lfX+mpData[5]*lfY+mpData[9]*lfZ+mpData[13];
 mpData[14]=mpData[2]*lfX+mpData[6]*lfY+mpData[10]*lfZ+mpData[14];
 mpData[15]=mpData[3]*lfX+mpData[7]*lfY+mpData[11]*lfZ+mpData[15];

};


void cMatrix4::Multiply(cMatrix4 &Other)
{
    Equals(operator*(&Other));
}

void cMatrix4::Multiply(cMatrix4 *Other)
 {
    Equals(operator*(Other));
 }

void cMatrix4::Multiply(float *Other)
{
    Equals(operator*(Other).Matrix());
}

void cMatrix4::Multiply(cCameraMatrix4 *Other)
{
	cMatrix4 lcTemp;
	lcTemp=Other->ConvertToMatrix();
    operator*(lcTemp);
	memcpy(mpData,mpTemp.Matrix(),sizeof(float)*16);
}

void cMatrix4::Multiply(cCameraMatrix4 &Other)
{
    cMatrix4 lcTemp;
	lcTemp=Other.ConvertToMatrix();
    operator*(lcTemp);
	memcpy(mpData,mpTemp.Matrix(),sizeof(float)*16);
}

void cMatrix4::Equals(float *lpOther)
{
    memcpy(mpData,lpOther,sizeof(float)*16);
}

void cMatrix4::Equals(cCameraMatrix4 &lpOther)
{
    memcpy(mpData,lpOther.ConvertToMatrix().Matrix(),sizeof(float)*16);
}

void cMatrix4::Equals(cCameraMatrix4 *lpOther)
{
    memcpy(mpData,lpOther->ConvertToMatrix().Matrix(),sizeof(float)*16);
}
cCameraMatrix4 &cMatrix4::ConvertToCameraMatrix()
{
    cCameraMatrix4::mpTemp.mpData[0]=-mpData[0];
    cCameraMatrix4::mpTemp.mpData[1]=-mpData[4];
    cCameraMatrix4::mpTemp.mpData[2]=-mpData[8];

    cCameraMatrix4::mpTemp.mpData[4]=-mpData[1];
    cCameraMatrix4::mpTemp.mpData[5]=-mpData[5];
    cCameraMatrix4::mpTemp.mpData[6]=-mpData[9];
    //mpTemp.mpData[13]=mpData[7];

    cCameraMatrix4::mpTemp.mpData[8]=-mpData[2];
    cCameraMatrix4::mpTemp.mpData[9]=-mpData[6];
    cCameraMatrix4::mpTemp.mpData[10]=-mpData[10];
    //mpTemp.mpData[14]=mpData[11];

    cCameraMatrix4::mpTemp.mpData[3]=0.0f;
    cCameraMatrix4::mpTemp.mpData[7]=0.0f;
    cCameraMatrix4::mpTemp.mpData[11]=0.0f;
    cCameraMatrix4::mpTemp.mpData[15]=1.0f;

    cCameraMatrix4::mpTemp.mpPosition[0]=-mpData[12];
    cCameraMatrix4::mpTemp.mpPosition[1]=-mpData[13];
    cCameraMatrix4::mpTemp.mpPosition[2]=-mpData[14];

    return cCameraMatrix4::mpTemp;

}

 c4DVf cMatrix4::MultiplyVector(float *lfVector){return MultiplyVector(c4DVf(lfVector));};
 c4DVf cMatrix4::Multiply(c4DVf lfVector){return MultiplyVector(lfVector);};
 c4DVf cMatrix4::MultiplyVector(c4DVf lfVector)
 {
  c4DVf Return;
  Return.v[0]=lfVector[0]*mpData[0]+lfVector[1]*mpData[1]+lfVector[2]*mpData[2]+lfVector[3]*mpData[3];
  Return.v[1]=lfVector[0]*mpData[4]+lfVector[1]*mpData[5]+lfVector[2]*mpData[6]+lfVector[3]*mpData[7];
  Return.v[2]=lfVector[0]*mpData[8]+lfVector[1]*mpData[9]+lfVector[2]*mpData[10]+lfVector[3]*mpData[11];
  Return.v[3]=lfVector[0]*mpData[12]+lfVector[1]*mpData[13]+lfVector[2]*mpData[14]+lfVector[3]*mpData[15];
  return Return;
 };



 c3DVf cMatrix4::RotateVectorByAngles(float *lfVector){return RotateVectorByAngles(c3DVf(lfVector));};
 c3DVf cMatrix4::Multiply(c3DVf lfVector){return RotateVectorByAngles(lfVector);};
 c3DVf cMatrix4::RotateVectorByAngles(c3DVf lfVector)
 {
  c3DVf Return;
  Return.v[0]=lfVector[0]*mpData[0]+lfVector[1]*mpData[1]+lfVector[2]*mpData[2];
  Return.v[1]=lfVector[0]*mpData[4]+lfVector[1]*mpData[5]+lfVector[2]*mpData[6];
  Return.v[2]=lfVector[0]*mpData[8]+lfVector[1]*mpData[9]+lfVector[2]*mpData[10];
  return Return;
 };


 c3DVf cMatrix4::MultiplyVectorPosition(float *lfVector){return MultiplyVectorPosition(c3DVf(lfVector));};
 c3DVf cMatrix4::MultiplyVectorPosition(c3DVf lfVector)
 {
     lfVector[0]=lfVector[0]*mpData[12];
     lfVector[1]=lfVector[1]*mpData[13];
     lfVector[2]=lfVector[2]*mpData[14];
     return lfVector;
 };

void cMatrix4::InvSign()
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

float cMatrix4::Distance(cMatrix4 &lpOther)
{
    return Distance(&lpOther);
}

float cMatrix4::Distance(float *lpOther)
{
    return Distance(c3DVf(lpOther));
}

double cMatrix4::DistanceSq(float *lpOther)
{
    return DistanceSq(c3DVf(lpOther));
}

float cMatrix4::Distance()
{
 return sqrt(mpData[12]*mpData[12]+mpData[13]*mpData[13]+mpData[14]*mpData[14]);
};

double cMatrix4::DistanceSq()
{
 return mpData[12]*mpData[12]+mpData[13]*mpData[13]+mpData[14]*mpData[14];
};


float cMatrix4::Roll()
{
	return atan2(-mpData[4],mpData[5]);
};

float cMatrix4::Yaw()
{
	return atan2(mpData[8],mpData[10]);
};

float cMatrix4::Pitch()
{
    return atan2(mpData[9],mpData[10]);
};

bool cMatrix4::Is3D(){return mb3D;};

c3DVf cMatrix4::FindPointRelative(c3DVf SameSpace)
{
    SameSpace-=Position();
 return c3DVf(SameSpace[0]*Xx()+SameSpace[1]*Xy()+SameSpace[2]*Xz(),SameSpace[0]*Yx()+SameSpace[1]*Yy()+SameSpace[2]*Yz(),SameSpace[0]*Zx()+SameSpace[1]*Zy()+SameSpace[2]*Zz());
}




cIdentityMatrix::cIdentityMatrix()
{
    memcpy(mpData,cMatrix4::mpIdentity,sizeof(16));
    mb3D=true;
};


cZeroMatrix::cZeroMatrix()
{
    memcpy(mpData,cMatrix4::mpZero,sizeof(16));
    mb3D=false;
};

