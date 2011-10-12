#include "../WTDivWin.h"

cMatrix4 cMatrix4::mpTemp;
float *cMatrix4::mpZero=0;
float *cMatrix4::mpIdentity=0;

cMatrix4::cMatrix4()
{
 if (!mpZero)
 {

  mpZero=new float[16];

     mpZero[0]=0.0f;
     mpZero[1]=0.0f;
     mpZero[2]=0.0f;
     mpZero[3]=0.0f;
     mpZero[4]=0.0f;
     mpZero[5]=0.0f;
     mpZero[6]=0.0f;
     mpZero[7]=0.0f;
     mpZero[8]=0.0f;
     mpZero[9]=0.0f;
     mpZero[10]=0.0f;
     mpZero[11]=0.0f;
     mpZero[12]=0.0f;
     mpZero[13]=0.0f;
     mpZero[14]=0.0f;
     mpZero[15]=0.0f;


  mpIdentity=new float[16];

     mpIdentity[0]=1.0f;
     mpIdentity[1]=0.0f;
     mpIdentity[2]=0.0f;
     mpIdentity[3]=0.0f;
     mpIdentity[4]=0.0f;
     mpIdentity[5]=1.0f;
     mpIdentity[6]=0.0f;
     mpIdentity[7]=0.0f;
     mpIdentity[8]=0.0f;
     mpIdentity[9]=0.0f;
     mpIdentity[10]=1.0f;
     mpIdentity[11]=0.0f;
     mpIdentity[12]=0.0f;
     mpIdentity[13]=0.0f;
     mpIdentity[14]=0.0f;
     mpIdentity[15]=1.0f;

 }
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


float *cMatrix4::operator=(float *lVal)
{
 memcpy(mpData,lVal,sizeof(float)*16);
 return lVal;
}

cMatrix4 cMatrix4::operator=(cMatrix4 lVal)
{
memcpy(mpData,lVal.mpData,sizeof(float)*16);
return lVal;
}

float cMatrix4::operator=(float &lVal)
{
 memset(mpData,lVal,sizeof(float)*16);
/*
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
*/
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
cMatrix4 *cMatrix4::operator=(cMatrix4 *lVal)
{
 memcpy(mpData,lVal->mpData,16*sizeof(float));
 return this;
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

cMatrix4 cMatrix4::Translate(float lfX,float lfY,float lfZ)
{
 
 mpData[12]=mpData[0]*lfX+mpData[4]*lfY+mpData[8]*lfZ+mpData[12];
 mpData[13]=mpData[1]*lfX+mpData[5]*lfY+mpData[9]*lfZ+mpData[13];
 mpData[14]=mpData[2]*lfX+mpData[6]*lfY+mpData[10]*lfZ+mpData[14];
 mpData[15]=mpData[3]*lfX+mpData[7]*lfY+mpData[11]*lfZ+mpData[15];

}

// 0 4 8  12   3  2  1  0
// 1 5 9  13   7  6  5  4
// 2 6 10 14   11 10 9  8
// 3 7 11 15   15 14 13 12
/*
cMatrix4 &cMatrix4::operator*(cMatrix4 &lVal)
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
*/
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

/* //this is HORRIBLY inefficient, however it represents the full
 //maths required to calculate the rotations
 mpRotate.Identity();
 
 mpRotate[10]=mpRotate[5]=cos(lfAngle);
 mpRotate[6]=sin(lfAngle);
 mpRotate[9]=-sin(lfAngle);

mpTemp.mpData[0]=mpData[0]*mpRotate.mpData[0]+mpData[4]*mpRotate.mpData[1]+mpData[8]*mpRotate.mpData[2]+mpData[12]*mpRotate.mpData[3];
mpTemp.mpData[1]=mpData[1]*mpRotate.mpData[0]+mpData[5]*mpRotate.mpData[1]+mpData[9]*mpRotate.mpData[2]+mpData[13]*mpRotate.mpData[3];
mpTemp.mpData[2]=mpData[2]*mpRotate.mpData[0]+mpData[6]*mpRotate.mpData[1]+mpData[10]*mpRotate.mpData[2]+mpData[14]*mpRotate.mpData[3];
mpTemp.mpData[3]=mpData[3]*mpRotate.mpData[0]+mpData[7]*mpRotate.mpData[1]+mpData[11]*mpRotate.mpData[2]+mpData[15]*mpRotate.mpData[3];

mpTemp.mpData[4]=mpData[0]*mpRotate.mpData[4]+mpData[4]*mpRotate.mpData[5]+mpData[8]*mpRotate.mpData[6]+mpData[12]*mpRotate.mpData[7];
mpTemp.mpData[5]=mpData[1]*mpRotate.mpData[4]+mpData[5]*mpRotate.mpData[5]+mpData[9]*mpRotate.mpData[6]+mpData[13]*mpRotate.mpData[7];
mpTemp.mpData[6]=mpData[2]*mpRotate.mpData[4]+mpData[6]*mpRotate.mpData[5]+mpData[10]*mpRotate.mpData[6]+mpData[14]*mpRotate.mpData[7];
mpTemp.mpData[7]=mpData[3]*mpRotate.mpData[4]+mpData[7]*mpRotate.mpData[5]+mpData[11]*mpRotate.mpData[6]+mpData[15]*mpRotate.mpData[7];

mpTemp.mpData[8]=mpData[0]*mpRotate.mpData[8]+mpData[4]*mpRotate.mpData[9]+mpData[8]*mpRotate.mpData[10]+mpData[12]*mpRotate.mpData[11];
mpTemp.mpData[9]=mpData[1]*mpRotate.mpData[8]+mpData[5]*mpRotate.mpData[9]+mpData[9]*mpRotate.mpData[10]+mpData[13]*mpRotate.mpData[11];
mpTemp.mpData[10]=mpData[2]*mpRotate.mpData[8]+mpData[6]*mpRotate.mpData[9]+mpData[10]*mpRotate.mpData[10]+mpData[14]*mpRotate.mpData[11];
mpTemp.mpData[11]=mpData[3]*mpRotate.mpData[8]+mpData[7]*mpRotate.mpData[9]+mpData[11]*mpRotate.mpData[10]+mpData[15]*mpRotate.mpData[11];

memcpy(mpData,mpTemp.mpData,12*sizeof(float));
*/

void cMatrix4::LRotateX(float lfAngle)
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


void cMatrix4::LRotateY(float lfAngle)
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


void cMatrix4::LRotateZ(float lfAngle)
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

void cMatrix4::LResizeX(float lfScale)
{
 mpData[0]=mpData[0]*lfScale;
 mpData[1]=mpData[1]*lfScale;
 mpData[2]=mpData[2]*lfScale;
}

void cMatrix4::LResizeY(float lfScale)
{

 mpData[4]=mpData[4]*lfScale;
 mpData[5]=mpData[5]*lfScale;
 mpData[6]=mpData[6]*lfScale;
}

void cMatrix4::LResizeZ(float lfScale)
{

 mpData[8]=mpData[8]*lfScale;
 mpData[9]=mpData[9]*lfScale;
 mpData[10]=mpData[10]*lfScale;
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

double cMatrix4::DistanceSq(float *lpOther)
{
 float lfX,lfY,lfZ;
 
 lfX=lpOther[0]-mpData[12];
 lfY=lpOther[1]-mpData[13];
 lfZ=lpOther[2]-mpData[14];
 
 return (lfX*lfX+lfY*lfY+lfZ*lfZ);
}

float cMatrix4::Distance(float *lpOther)
{
float lfX,lfY,lfZ;
 lfX=lpOther[0]-mpData[12];
 lfY=lpOther[1]-mpData[13];
 lfZ=lpOther[2]-mpData[14];

 return sqrt(lfX*lfX+lfY*lfY+lfZ*lfZ);
}


float cMatrix4::Distance(cMatrix4 *lpOther)
{
float lfX,lfY,lfZ;
 lfX=lpOther->mpData[12]-mpData[12];
 lfY=lpOther->mpData[13]-mpData[13];
 lfZ=lpOther->mpData[14]-mpData[14];

 return sqrt(lfX*lfX+lfY*lfY+lfZ*lfZ);
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
 mpData[14]=-1.1f;
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