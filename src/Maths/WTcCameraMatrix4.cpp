
#include "../WTBamboo.h"
#include <cmath>

c3DVf cCameraMatrix4::XVect()
{
    return c3DVf(mpData[0],mpData[4],mpData[8]);
};

c3DVf cCameraMatrix4::YVect()
{
    return c3DVf(mpData[1],mpData[5],mpData[9]);
};

c3DVf cCameraMatrix4::ZVect()
{
    return c3DVf(mpData[2],mpData[6],mpData[10]);
}
cCameraMatrix4 cCameraMatrix4::mpTemp;

float cCameraMatrix4::mpZero[]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
float cCameraMatrix4::mpIdentity[]={1.0f,0.0f,0.0f,0.0f,
                                    0.0f,1.0f,0.0f,0.0f,
                                    0.0f,0.0f,1.0f,0.0f,
                                    0.0f,0.0f,0.0f,1.0f};
float cCameraMatrix4::mpGlobalPosition[3]={0.0f,0.0f,0.0f};
float cCameraMatrix4::mpCameraMatrix[]={1.0f,0.0f,0.0f,0.0f,
                                    0.0f,1.0f,0.0f,0.0f,
                                    0.0f,0.0f,1.0f,0.0f,
                                    0.0f,0.0f,0.0f,1.0f};

cCameraMatrix4::cCameraMatrix4()
{


 Zero();
 mpCameraPosition[0]=0.0f;
 mpCameraPosition[1]=0.0f;
 mpCameraPosition[2]=0.0f;
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
 mpCameraPosition[0]=-lfX;
 mpCameraPosition[1]=-lfY;
}

void cCameraMatrix4::Position(float lfX,float lfY,float lfZ)
{
 mpCameraPosition[0]=-lfX;
 mpCameraPosition[1]=-lfY;
 mpCameraPosition[2]=-lfZ;
}


void cCameraMatrix4::Position(c2DVf *lpPosition)
{
 mpCameraPosition[0]=-lpPosition->v[0];
 mpCameraPosition[1]=-lpPosition->v[1];
}


void cCameraMatrix4::Position(c3DVf *lpPosition)
{
 mpCameraPosition[0]=-lpPosition->v[0];
 mpCameraPosition[1]=-lpPosition->v[1];
 mpCameraPosition[2]=-lpPosition->v[2];
}

void cCameraMatrix4::PositionX(float lfX)
{
 mpCameraPosition[0]=-lfX;
}
void cCameraMatrix4::PositionY(float lfY)
{
 mpCameraPosition[1]=-lfY;
}
void cCameraMatrix4::PositionZ(float lfZ)
{
 mpCameraPosition[2]=-lfZ;
}

void cCameraMatrix4::Rotate(float lfAngle)
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

void cCameraMatrix4::RotateX(float lfAngle)
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

void cCameraMatrix4::RotateY(float lfAngle)
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

void cCameraMatrix4::RotateZ(float lfAngle)
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

void cCameraMatrix4::ResizeX(float lfScale)
{
 mpData[0]=mpData[0]*lfScale;
 mpData[1]=mpData[1]*lfScale;
 mpData[2]=mpData[2]*lfScale;

}

void cCameraMatrix4::ResizeY(float lfScale)
{

 mpData[4]=mpData[4]*lfScale;
 mpData[5]=mpData[5]*lfScale;
 mpData[6]=mpData[6]*lfScale;

}

void cCameraMatrix4::ResizeZ(float lfScale)
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
mpCameraPosition[0]+=mpData[0]*lfDistance;
mpCameraPosition[1]+=mpData[4]*lfDistance;
mpCameraPosition[2]+=mpData[8]*lfDistance;
}

void cCameraMatrix4::AdvanceY(float lfDistance)
{
mpCameraPosition[0]+=mpData[1]*lfDistance;
mpCameraPosition[1]+=mpData[5]*lfDistance;
mpCameraPosition[2]+=mpData[9]*lfDistance;
}

void cCameraMatrix4::AdvanceZ(float lfDistance)
{
mpCameraPosition[0]+=mpData[2]*lfDistance;
mpCameraPosition[1]+=mpData[6]*lfDistance;
mpCameraPosition[2]+=mpData[10]*lfDistance;
}


void cCameraMatrix4::Advance(float lfX,float lfY,float lfZ)
{
mpCameraPosition[0]+=mpData[0]*lfX+mpData[1]*lfY+mpData[2]*lfZ;
mpCameraPosition[1]+=mpData[4]*lfX+mpData[5]*lfY+mpData[6]*lfZ;
mpCameraPosition[2]+=mpData[8]*lfX+mpData[9]*lfY+mpData[10]*lfZ;
}

void cCameraMatrix4::GAdvanceX(float lfDistance)
{mpCameraPosition[0]-=lfDistance;}

void cCameraMatrix4::GAdvanceY(float lfDistance)
{mpCameraPosition[1]-=lfDistance;}

void cCameraMatrix4::GAdvanceZ(float lfDistance)
{mpCameraPosition[2]-=lfDistance;}

void cCameraMatrix4::GAdvance(float lfX,float lfY,float lfZ)
{
 mpCameraPosition[0]-=lfX;
 mpCameraPosition[1]=-lfY;
 mpCameraPosition[2]=-lfZ;
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


//mpCameraPosition[0]-=lfX;
mpCameraPosition[1]+=lfY;
mpCameraPosition[2]+=lfZ;

mpTemp.mpData[13] = mpCameraPosition[1]*lfCos-mpCameraPosition[2]*lfSin;
mpTemp.mpData[14] = mpCameraPosition[1]*lfSin+mpCameraPosition[2]*lfCos;
//mpCameraPosition[0]+=lfX;
mpCameraPosition[1]=mpTemp.mpData[13]-lfY;
mpCameraPosition[2]=mpTemp.mpData[14]-lfZ;

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


mpCameraPosition[0]+=lfX;
mpCameraPosition[2]+=lfZ;
mpTemp.mpData[12]=mpCameraPosition[0]*lfCos-mpCameraPosition[2]*lfSin;
mpTemp.mpData[14]=mpCameraPosition[2]*lfCos+mpCameraPosition[0]*lfSin;
mpCameraPosition[0]=mpTemp.mpData[12]-lfX;
mpCameraPosition[2]=mpTemp.mpData[14]-lfZ;

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

mpCameraPosition[0]+=lfX;
mpCameraPosition[1]+=lfY;
mpTemp.mpData[12]=mpCameraPosition[0]*lfCos-mpCameraPosition[1]*lfSin;
mpTemp.mpData[13]=mpCameraPosition[0]*lfSin+mpCameraPosition[1]*lfCos;
mpCameraPosition[0]=mpTemp.mpData[12]-lfX;
mpCameraPosition[1]=mpTemp.mpData[13]-lfY;
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

void cCameraMatrix4::Advance(float lfDist)
{
    AdvanceZ(lfDist);
}
void cCameraMatrix4::Follow(vRenderObject *lpObj,float lfDist)
{
    Follow(&(lpObj->mmCache),lfDist);
};
void cCameraMatrix4::Follow(vRenderObject *lpObj,float lfX,float lfY,float lfZ)
{
    Follow(&(lpObj->mmCache),lfX,lfY,lfZ);
};
void cCameraMatrix4::PointAt(vRenderObject *lpObj)
{
    PointAt(&(lpObj->mmTotalCache));
};

void cCameraMatrix4::Follow(cMatrix4* lpOther,float lfX,float lfY,float lfZ)
{
    cMatrix4 lpInv=lpOther->InversionMatrix();

    memcpy(mpData,lpInv.Matrix(),sizeof(float)*12);

    RotateY(3.14159265);


	mpCameraPosition[0]=-lpOther->X();
	mpCameraPosition[1]=-lpOther->Y();
	mpCameraPosition[2]=-lpOther->Z();
    Advance(lfX,lfY,lfZ);
}


void cCameraMatrix4::Follow(cMatrix4 &lpOther,float lfX,float lfY,float lfZ)
{
 	Follow(&lpOther,lfX,lfY,lfZ);
}

void cCameraMatrix4::Follow(cMatrix4* lpOther,float lfDist)
{

    cMatrix4 lpInv=lpOther->InversionMatrix();
    memcpy(mpData,lpInv.Matrix(),sizeof(float)*12);

    RotateY(3.14159265);

	mpCameraPosition[0]=lpOther->X();
	mpCameraPosition[1]=lpOther->Y();
	mpCameraPosition[2]=lpOther->Z();
    Advance(lfDist);
}


void cCameraMatrix4::Follow(cMatrix4 &lpOther,float lfDist)
{
 	Follow(&lpOther,lfDist);
}


void cCameraMatrix4::PointAt(float *mpPos)
{

c3DVf Z;

Z[0]=mpPos[0]+mpCameraPosition[0];
Z[1]=mpPos[1]+mpCameraPosition[1];
Z[2]=mpPos[2]+mpCameraPosition[2];

double Yaw=atan2(Z[0],-Z[2]);

double Pitch=atan2(Z[1],sqrt(Z[0]*Z[0]+Z[2]*Z[2]));

Identity();
RotateY(-Yaw);
RotateX(Pitch);

}


void cCameraMatrix4::PointAt(cMatrix4 *mpPos)
{
 PointAt(mpPos->Matrix(12));
}

void cCameraMatrix4::PointAt(cMatrix4 &mpPos)
{
 PointAt(mpPos.Matrix(12));
}

void cCameraMatrix4::PointAt(c3DVf &mpPos)
{
 PointAt(mpPos.v);
}

void cCameraMatrix4::PointAt(c3DVf *mpPos)
{
 PointAt(mpPos->v);
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

cMatrix4 &cCameraMatrix4::ConvertToMatrix()
{
    cMatrix4::mpTemp.mpData[0]=-mpData[0];
    cMatrix4::mpTemp.mpData[4]=-mpData[1];
    cMatrix4::mpTemp.mpData[8]=-mpData[2];

    cMatrix4::mpTemp.mpData[1]=-mpData[4];
    cMatrix4::mpTemp.mpData[5]=-mpData[5];
    cMatrix4::mpTemp.mpData[9]=-mpData[6];
    //mpTemp.mpData[13]=mpData[7];

    cMatrix4::mpTemp.mpData[2]=-mpData[8];
    cMatrix4::mpTemp.mpData[6]=-mpData[9];
    cMatrix4::mpTemp.mpData[10]=-mpData[10];
    //mpTemp.mpData[14]=mpData[11];

    cMatrix4::mpTemp.mpData[3]=0.0f;
    cMatrix4::mpTemp.mpData[7]=0.0f;
    cMatrix4::mpTemp.mpData[11]=0.0f;
    cMatrix4::mpTemp.mpData[15]=1.0f;

    cMatrix4::mpTemp.mpData[12]=-mpCameraPosition[0];
    cMatrix4::mpTemp.mpData[13]=-mpCameraPosition[1];
    cMatrix4::mpTemp.mpData[14]=-mpCameraPosition[2];
    return cMatrix4::mpTemp;
}

void cCameraMatrix4::Display()
{

 printf("\n");
 printf("[%f %f %f %f,\n %f %f %f %f,\n %f %f %f %f,\n %f %f %f %f]\n",mpData[0],mpData[4],mpData[8],mpData[12],mpData[1],mpData[5],mpData[9],mpData[13],mpData[2],mpData[6],mpData[10],mpData[14],mpData[3],mpData[7],mpData[11],mpData[15]);
 printf("Position : %f %f %f\n",mpCameraPosition[0],mpCameraPosition[1],mpCameraPosition[2]);
}



void cCameraMatrix4::Equals(cCameraMatrix4 *lpOther)
{
    memcpy(mpData,lpOther->mpData,sizeof(float)*16);
    memcpy(mpCameraPosition,lpOther->mpCameraPosition,sizeof(float)*3);
}
void cCameraMatrix4::Equals(cCameraMatrix4 &lpOther)
{
    memcpy(mpData,lpOther.mpData,sizeof(float)*16);
    memcpy(mpCameraPosition,lpOther.mpCameraPosition,sizeof(float)*3);
}
void cCameraMatrix4::Equals(cMatrix4 *lpOther)
{
    Equals(lpOther->ConvertToCameraMatrix());
}
void cCameraMatrix4::Equals(cMatrix4 &lpOther)
{
    Equals(lpOther.ConvertToCameraMatrix());
}

void cCameraMatrix4::Multiply(cCameraMatrix4 *lpOther)
{
    Equals(operator*(lpOther));
}
void cCameraMatrix4::Multiply(cCameraMatrix4 &lpOther)
{
    operator*(lpOther);
	memcpy(mpData,mpTemp.Matrix(),sizeof(float)*16);
	memcpy(mpCameraPosition,mpTemp.Position(),sizeof(float)*3);
}
void cCameraMatrix4::Multiply(cMatrix4 *lpOther)
{
	cCameraMatrix4 lcTemp;
	lcTemp=lpOther->ConvertToCameraMatrix();
    operator*(lcTemp);
	memcpy(mpData,mpTemp.Matrix(),sizeof(float)*16);
	memcpy(mpCameraPosition,mpTemp.Position(),sizeof(float)*3);
}
void cCameraMatrix4::Multiply(cMatrix4 &lpOther)
{
    cCameraMatrix4 lcTemp;
	lcTemp=lpOther.ConvertToCameraMatrix();
    operator*(lcTemp);
	memcpy(mpData,mpTemp.Matrix(),sizeof(float)*16);
	memcpy(mpCameraPosition,mpTemp.Position(),sizeof(float)*3);
}

  float *cCameraMatrix4::Matrix(){return mpData;};
  float *cCameraMatrix4::Position()
  {
    mpGlobalPosition[0]=-mpCameraPosition[0];
    mpGlobalPosition[1]=-mpCameraPosition[1];
    mpGlobalPosition[2]=-mpCameraPosition[2];
    return mpGlobalPosition;
  };
  float cCameraMatrix4::X(){return -mpCameraPosition[0];};
  float cCameraMatrix4::Y(){return -mpCameraPosition[1];};
  float cCameraMatrix4::Z(){return -mpCameraPosition[2];};

float *cCameraMatrix4::ConstructCameraMatrix()
{

 memcpy(mpCameraMatrix,mpData,sizeof(float)*16);

 mpCameraMatrix[12]=mpCameraPosition[0]*mpData[0]+mpCameraPosition[1]*mpData[4]+mpCameraPosition[2]*mpData[8];
 mpCameraMatrix[13]=mpCameraPosition[0]*mpData[1]+mpCameraPosition[1]*mpData[5]+mpCameraPosition[2]*mpData[9];
 mpCameraMatrix[14]=mpCameraPosition[0]*mpData[2]+mpCameraPosition[1]*mpData[6]+mpCameraPosition[2]*mpData[10];

 return mpCameraMatrix;
}
