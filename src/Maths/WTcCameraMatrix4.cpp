#include "../WTDivWin.h"
#include <cmath>

cCameraMatrix4 cCameraMatrix4::mpTemp;

float *cCameraMatrix4::mpZero=0;
float *cCameraMatrix4::mpIdentity=0;

cCameraMatrix4::cCameraMatrix4()
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

 Zero();
 mpPosition[0]=0.0f;
 mpPosition[1]=0.0f;
 mpPosition[2]=0.0f;
}

cCameraMatrix4 cCameraMatrix4::operator+(float &lVal)
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

cCameraMatrix4 cCameraMatrix4::operator+(const float lVal)
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

cCameraMatrix4 cCameraMatrix4::operator-(float &lVal)
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

cCameraMatrix4 cCameraMatrix4::operator-(const float lVal)
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

cCameraMatrix4 cCameraMatrix4::operator*(float &lVal)
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

cCameraMatrix4 cCameraMatrix4::operator*(const float lVal)
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

cCameraMatrix4 cCameraMatrix4::operator/(float &lVal)
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

cCameraMatrix4 cCameraMatrix4::operator/(const float lVal)
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


float cCameraMatrix4::operator=(float &lVal)
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

float cCameraMatrix4::operator=(const float lVal)
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

cCameraMatrix4 cCameraMatrix4::operator=(cCameraMatrix4 &lVal)
{
 memcpy(mpData,lVal.mpData,16*sizeof(float));
 return *this;
}

cCameraMatrix4 *cCameraMatrix4::operator=(cCameraMatrix4 *lVal)
{
 memcpy(mpData,lVal->mpData,16*sizeof(float));
 return this;
}

void cCameraMatrix4::Zero()
{
 memcpy(mpData,mpZero,16*sizeof(float));
}

void cCameraMatrix4::Identity()
{
 memcpy(mpData,mpIdentity,16*sizeof(float));
}

cCameraMatrix4 cCameraMatrix4::operator+(cCameraMatrix4 &lVal)
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

cCameraMatrix4 cCameraMatrix4::operator-(cCameraMatrix4 &lVal)
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


float cCameraMatrix4::Determinant()
{
 return
 mpData[0]*(mpData[5]*(mpData[10]*mpData[15]-mpData[14]*mpData[11])-mpData[9]*(mpData[6]*mpData[15]-mpData[14]*mpData[7])+mpData[13]*(mpData[6]*mpData[11]-mpData[10]*mpData[7]))
 -mpData[4]*(mpData[1]*(mpData[10]*mpData[15]-mpData[11]*mpData[14])-mpData[9]*(mpData[2]*mpData[15]-mpData[14]*mpData[3])+mpData[13]*(mpData[2]*mpData[11]-mpData[10]*mpData[3]))
 +mpData[8]*(mpData[1]*(mpData[6]*mpData[10]-mpData[14]*mpData[7])-mpData[5]*(mpData[2]*mpData[15]-mpData[3]*mpData[14])+mpData[13]*(mpData[2]*mpData[7]-mpData[6]*mpData[3]))
 -mpData[12]*(mpData[1]*(mpData[6]*mpData[11]-mpData[10]*mpData[7])-mpData[5]*(mpData[2]*mpData[11]-mpData[10]*mpData[3])+mpData[9]*(mpData[2]*mpData[7]-mpData[6]*mpData[3]));
}

cCameraMatrix4 cCameraMatrix4::Transpose()
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

// 0 4 8  12   3  2  1  0
// 1 5 9  13   7  6  5  4
// 2 6 10 14   11 10 9  8
// 3 7 11 15   15 14 13 12

cCameraMatrix4 cCameraMatrix4::operator*(cCameraMatrix4 &lVal)
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


cCameraMatrix4 *cCameraMatrix4::operator*(cCameraMatrix4 *lVal)
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


float &cCameraMatrix4::operator[](uint16 liPos)
{
 return mpData[liPos];
}

float &cCameraMatrix4::operator()(uint16 liColumn,uint16 liRow)
{
 return mpData[liColumn*4+liRow];
}

void cCameraMatrix4::Position(float lfX,float lfY)
{
 mpPosition[0]=-lfX;
 mpPosition[1]=-lfY;
}

void cCameraMatrix4::Position(float lfX,float lfY,float lfZ)
{
 mpPosition[0]=-lfX;
 mpPosition[1]=-lfY;
 mpPosition[2]=-lfZ;
}


void cCameraMatrix4::Position(c2DVf *lpPosition)
{
 mpPosition[0]=-lpPosition->v[0];
 mpPosition[1]=-lpPosition->v[1];
}


void cCameraMatrix4::Position(c3DVf *lpPosition)
{
 mpPosition[0]=-lpPosition->v[0];
 mpPosition[1]=-lpPosition->v[1];
 mpPosition[2]=-lpPosition->v[2];
}

void cCameraMatrix4::PositionX(float lfX)
{
 mpPosition[0]=-lfX;
}
void cCameraMatrix4::PositionY(float lfY)
{
 mpPosition[1]=-lfY;
}
void cCameraMatrix4::PositionZ(float lfZ)
{
 mpPosition[2]=-lfZ;
}

void cCameraMatrix4::LRotate(float lfAngle)
{
 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0];
mpTemp.mpData[1]=lfCos*mpData[1]+lfSin*mpData[2];
mpTemp.mpData[2]=lfCos*mpData[2]-lfSin*mpData[1];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=mpData[4];
mpTemp.mpData[5]=lfCos*mpData[5]+lfSin*mpData[6];
mpTemp.mpData[6]=lfCos*mpData[6]-lfSin*mpData[5];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=mpData[8];
mpTemp.mpData[9]=lfCos*mpData[9]+lfSin*mpData[10];
mpTemp.mpData[10]=lfCos*mpData[10]-lfSin*mpData[9];

memcpy(mpData,mpTemp.mpData,11*sizeof(float));

}

void cCameraMatrix4::Angle(float lfAngle)
{
  mpData[5]=mpData[0]=-cos(lfAngle);
  mpData[4]=sin(lfAngle);
  mpData[1]=-mpData[4];
}

void cCameraMatrix4::LRotateX(float lfAngle)
{
 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0];
mpTemp.mpData[1]=lfCos*mpData[1]+lfSin*mpData[2];
mpTemp.mpData[2]=lfCos*mpData[2]-lfSin*mpData[1];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=mpData[4];
mpTemp.mpData[5]=lfCos*mpData[5]+lfSin*mpData[6];
mpTemp.mpData[6]=lfCos*mpData[6]-lfSin*mpData[5];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=mpData[8];
mpTemp.mpData[9]=lfCos*mpData[9]+lfSin*mpData[10];
mpTemp.mpData[10]=lfCos*mpData[10]-lfSin*mpData[9];

memcpy(mpData,mpTemp.mpData,11*sizeof(float));

}

void cCameraMatrix4::LRotateY(float lfAngle)
{

float lfCos,lfSin;
      lfCos=cos(lfAngle);
      lfSin=sin(lfAngle);

mpTemp.mpData[0]=lfCos*mpData[0]-lfSin*mpData[2];
mpTemp.mpData[1]=mpData[1];
mpTemp.mpData[2]=lfSin*mpData[0]+lfCos*mpData[2];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=lfCos*mpData[4]-lfSin*mpData[6];
mpTemp.mpData[5]=mpData[5];
mpTemp.mpData[6]=lfSin*mpData[4]+lfCos*mpData[6];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=lfCos*mpData[8]-lfSin*mpData[10];
mpTemp.mpData[9]=mpData[9];
mpTemp.mpData[10]=lfSin*mpData[8]+lfCos*mpData[10];

memcpy(mpData,mpTemp.mpData,11*sizeof(float));
}

void cCameraMatrix4::LRotateZ(float lfAngle)
{

 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=lfCos*mpData[0]+lfSin*mpData[1];
mpTemp.mpData[1]=lfCos*mpData[1]-lfSin*mpData[0];
mpTemp.mpData[2]=mpData[2];
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=lfCos*mpData[4]+lfSin*mpData[5];
mpTemp.mpData[5]=lfCos*mpData[5]-lfSin*mpData[4];
mpTemp.mpData[6]=mpData[6];
mpTemp.mpData[7]=0;

mpTemp.mpData[8]=lfCos*mpData[8]+lfSin*mpData[9];
mpTemp.mpData[9]=lfCos*mpData[9]-lfSin*mpData[8];
mpTemp.mpData[10]=mpData[10];

memcpy(mpData,mpTemp.mpData,11*sizeof(float));

}

void cCameraMatrix4::Resize(float lfScale)
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

void cCameraMatrix4::LResizeX(float lfScale)
{
 mpData[0]=mpData[0]*lfScale;
 mpData[1]=mpData[1]*lfScale;
 mpData[2]=mpData[2]*lfScale;

}

void cCameraMatrix4::LResizeY(float lfScale)
{

 mpData[4]=mpData[4]*lfScale;
 mpData[5]=mpData[5]*lfScale;
 mpData[6]=mpData[6]*lfScale;

}

void cCameraMatrix4::LResizeZ(float lfScale)
{

 mpData[8]=mpData[8]*lfScale;
 mpData[9]=mpData[9]*lfScale;
 mpData[10]=mpData[10]*lfScale;


}

void cCameraMatrix4::GResizeX(float lfScale)
{
 mpData[0]=mpData[0]*lfScale;
 mpData[4]=mpData[4]*lfScale;
 mpData[8]=mpData[8]*lfScale;

}

void cCameraMatrix4::GResizeY(float lfScale)
{

 mpData[1]=mpData[1]*lfScale;
 mpData[5]=mpData[5]*lfScale;
 mpData[9]=mpData[9]*lfScale;

}
void cCameraMatrix4::GResizeZ(float lfScale)
{
 mpData[2]=mpData[2]*lfScale;
 mpData[6]=mpData[6]*lfScale;
 mpData[10]=mpData[10]*lfScale;

}

void cCameraMatrix4::GRotateX(float lfAngle)
{
 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[4]=mpData[4]*lfCos-mpData[8]*lfSin;
mpTemp.mpData[5]=mpData[5]*lfCos-mpData[9]*lfSin;
mpTemp.mpData[6]=mpData[6]*lfCos-mpData[10]*lfSin;
mpTemp.mpData[7]=0;

mpTemp.mpData[8] =mpData[4]*lfSin+mpData[8]*lfCos;
mpTemp.mpData[9] =mpData[5]*lfSin+mpData[9]*lfCos;
mpTemp.mpData[10]=mpData[6]*lfSin+mpData[10]*lfCos;

memcpy(&mpData[4],&mpTemp.mpData[4],7*sizeof(float));

}


void cCameraMatrix4::GRotateY(float lfAngle)
{
 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0]*lfCos+mpData[8]*lfSin;
mpTemp.mpData[1]=mpData[1]*lfCos+mpData[9]*lfSin;
mpTemp.mpData[2]=mpData[2]*lfCos+mpData[10]*lfSin;
mpTemp.mpData[3]=0;

memcpy(&mpTemp.mpData[4],&mpData[4],4*sizeof(float));

mpTemp.mpData[8]= mpData[8]*lfCos-mpData[0]*lfSin;
mpTemp.mpData[9]= mpData[9]*lfCos-mpData[1]*lfSin;
mpTemp.mpData[10]=mpData[10]*lfCos-mpData[2]*lfSin;

memcpy(mpData,mpTemp.mpData,11*sizeof(float));
}


void cCameraMatrix4::GRotateZ(float lfAngle)
{
 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0]*lfCos-mpData[4]*lfSin;
mpTemp.mpData[1]=mpData[1]*lfCos-mpData[5]*lfSin;
mpTemp.mpData[2]=mpData[2]*lfCos-mpData[6]*lfSin;
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=mpData[0]*lfSin+mpData[4]*lfCos;
mpTemp.mpData[5]=mpData[1]*lfSin+mpData[5]*lfCos;
mpTemp.mpData[6]=mpData[2]*lfSin+mpData[6]*lfCos;

memcpy(mpData,mpTemp.mpData,7*sizeof(float));
}

void cCameraMatrix4::AdvanceX(float lfDistance)
{
mpPosition[0]+=mpData[0]*lfDistance;
mpPosition[1]+=mpData[4]*lfDistance;
mpPosition[2]+=mpData[8]*lfDistance;
}

void cCameraMatrix4::AdvanceY(float lfDistance)
{
mpPosition[0]+=mpData[1]*lfDistance;
mpPosition[1]+=mpData[5]*lfDistance;
mpPosition[2]+=mpData[9]*lfDistance;
}

void cCameraMatrix4::AdvanceZ(float lfDistance)
{
mpPosition[0]+=mpData[2]*lfDistance;
mpPosition[1]+=mpData[6]*lfDistance;
mpPosition[2]+=mpData[10]*lfDistance;
}


void cCameraMatrix4::Advance(float lfX,float lfY,float lfZ)
{
mpPosition[0]+=mpData[0]*lfX+mpData[1]*lfY+mpData[2]*lfZ;
mpPosition[1]+=mpData[4]*lfX+mpData[5]*lfY+mpData[6]*lfZ;
mpPosition[2]+=mpData[8]*lfX+mpData[9]*lfY+mpData[10]*lfZ;
}

void cCameraMatrix4::GAdvanceX(float lfDistance)
{mpPosition[0]-=lfDistance;}

void cCameraMatrix4::GAdvanceY(float lfDistance)
{mpPosition[1]-=lfDistance;}

void cCameraMatrix4::GAdvanceZ(float lfDistance)
{mpPosition[2]-=lfDistance;}

void cCameraMatrix4::GAdvance(float lfX,float lfY,float lfZ)
{
 mpPosition[0]-=lfX;
 mpPosition[1]=-lfY;
 mpPosition[2]=-lfZ;
}

void cCameraMatrix4::GRotateX(float lfAngle,float lfX,float lfY,float lfZ)
{
 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);


mpTemp.mpData[4]=mpData[4]*lfCos-mpData[8]*lfSin;
mpTemp.mpData[5]=mpData[5]*lfCos-mpData[9]*lfSin;
mpTemp.mpData[6]=mpData[6]*lfCos-mpData[10]*lfSin;
mpTemp.mpData[7]=0;

mpTemp.mpData[8] =mpData[4]*lfSin+mpData[8]*lfCos;
mpTemp.mpData[9] =mpData[5]*lfSin+mpData[9]*lfCos;
mpTemp.mpData[10]=mpData[6]*lfSin+mpData[10]*lfCos;

memcpy(&mpData[4],&mpTemp.mpData[4],7*sizeof(float));


mpPosition[0]-=lfX;
mpPosition[1]-=lfY;
mpPosition[2]-=lfZ;

mpTemp.mpData[13] = mpPosition[1]*lfCos-mpPosition[2]*lfSin;
mpTemp.mpData[14] = mpPosition[1]*lfSin+mpPosition[2]*lfCos;
mpPosition[1]=mpTemp.mpData[13]+lfY;
mpPosition[2]=mpTemp.mpData[14]+lfZ;

}

void cCameraMatrix4::GRotateY(float lfAngle,float lfX,float lfY,float lfZ)
{
 (void) lfY;
 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0]*lfCos+mpData[8]*lfSin;
mpTemp.mpData[1]=mpData[1]*lfCos+mpData[9]*lfSin;
mpTemp.mpData[2]=mpData[2]*lfCos+mpData[10]*lfSin;
mpTemp.mpData[3]=0;

memcpy(&mpTemp.mpData[4],&mpData[4],4*sizeof(float));

mpTemp.mpData[8]= mpData[8]*lfCos-mpData[0]*lfSin;
mpTemp.mpData[9]= mpData[9]*lfCos-mpData[1]*lfSin;
mpTemp.mpData[10]=mpData[10]*lfCos-mpData[2]*lfSin;

memcpy(mpData,mpTemp.mpData,11*sizeof(float));


mpPosition[0]-=lfX;
mpPosition[2]-=lfZ;
mpTemp.mpData[12]=mpPosition[0]*lfCos+mpPosition[2]*lfSin;
mpTemp.mpData[14]=mpPosition[2]*lfCos-mpPosition[0]*lfSin;
mpPosition[0]=mpTemp.mpData[12]+lfX;
mpPosition[2]=mpTemp.mpData[14]+lfZ;

}

void cCameraMatrix4::GRotateZ(float lfAngle,float lfX,float lfY,float lfZ)
{
 (void) lfZ;
 float lfCos,lfSin;
 lfCos=cos(lfAngle);
 lfSin=sin(lfAngle);

mpTemp.mpData[0]=mpData[0]*lfCos-mpData[4]*lfSin;
mpTemp.mpData[1]=mpData[1]*lfCos-mpData[5]*lfSin;
mpTemp.mpData[2]=mpData[2]*lfCos-mpData[6]*lfSin;
mpTemp.mpData[3]=0;

mpTemp.mpData[4]=mpData[0]*lfSin+mpData[4]*lfCos;
mpTemp.mpData[5]=mpData[1]*lfSin+mpData[5]*lfCos;
mpTemp.mpData[6]=mpData[2]*lfSin+mpData[6]*lfCos;

memcpy(mpData,mpTemp.mpData,7*sizeof(float));

mpPosition[0]-=lfX;
mpPosition[1]-=lfY;
mpTemp.mpData[12]=mpPosition[0]*lfCos-mpPosition[1]*lfSin;
mpTemp.mpData[13]=mpPosition[0]*lfSin+mpPosition[1]*lfCos;
mpPosition[0]=mpTemp.mpData[12]+lfX;
mpPosition[1]=mpTemp.mpData[13]+lfY;
}


uint32 cCameraMatrix4::Distance3D(float *lpOther)
{
 float lfX,lfY,lfZ;
 lfX=lpOther[0]-mpData[12];
 lfY=lpOther[1]-mpData[13];
 lfZ=lpOther[2]-mpData[14];
 return (uint32)(lfX*lfX+lfY*lfY+lfZ*lfZ);
}

uint32 cCameraMatrix4::Distance2D(float *lpOther)
{
 float lfX,lfY;
 lfX=lpOther[0]-mpData[12];
 lfY=lpOther[1]-mpData[13];
 return (uint32)(lfX*lfX+lfY*lfY);
}

void cCameraMatrix4::Follow(cMatrix4* lpOther,float lfDist)
{
	cMatrix4 lpInv=lpOther->InvertRotationMatrix();
	  
	 memcpy(&mpData[0],&(lpInv.Matrix())[0],sizeof(float)*12);

	 //InvSign();
	 
	mpPosition[0]=-lpOther->Matrix()[12];
	mpPosition[1]=-lpOther->Matrix()[13];
	mpPosition[2]=-lpOther->Matrix()[14];
	
	AdvanceZ(-lfDist);
}

void cCameraMatrix4::PointAt(float *mpPos)
{

c3DVf Z;

Z.v[0]=mpPos[0]+mpPosition[0];
Z.v[1]=mpPos[1]+mpPosition[1];
Z.v[2]=mpPos[2]+mpPosition[2];

double Yaw=atan2(Z.v[0],Z.v[2]);
double Pitch=atan2(Z.v[1],Z.v[2]);

Identity();
LRotateY(Yaw);
LRotateX(Pitch);


}

void cCameraMatrix4::InvSign()
{
	mpData[0]=-mpData[0];
	mpData[1]=-mpData[1];
	mpData[2]=-mpData[2];
	
	
	mpData[4]=-mpData[4];
	mpData[5]=-mpData[5];
	mpData[6]=-mpData[6];
	
	mpData[8]=-mpData[8];
	mpData[9]=-mpData[9];
	mpData[10]=-mpData[10];
}
