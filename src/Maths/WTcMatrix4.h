#ifndef __WTCMATRIX4_H__
#define __WTCMATRIX4_H__
//#include "WTDivWin.h"
/**
* \brief this is a standard 4x4 translation matrix for objects.
* This is a standard 4x4 translation matrix for objects. It can be used for 
* both 2D and 3D objects. By default it is a 3D matrix, It can be converted to a 
* 2D matrix by using the function Set2D().
*/

class cCameraMatrix4;
class cMatrix4
{
  friend class cCameraMatrix4;
  /// This is a pointer to a static array to allow this objects matrix to be quickly zeroed.
 static float *mpZero;
 /// This is a pointer to a static array to allow this objects matrix to be quickly restored to an identity matrix.
 static float *mpIdentity;


protected:
// 0 4 8 12
 // 1 5 9 13
 // 2 6 10 14
 // 3 7 11 15
 /// This stores a 4x4 matrix of floats representing the current translation of the objet.
 float mpData[16];

 /// This si a boolean flag to define whether the object is 3D or 2D. True is 3D. False is 2D.
 bool mb3D;

public:
 /// This will update the OpenGL matrix on the top of matrix stack to be identical to this matrix.
 void UpdateMatrix();
 /// This appears to multiply this matrix by the matrix lpMatrix and equate this matrix to the result.
 void UpdateMatrix(float *lpMatrix);

 /// This is a static cMatrix4 used to store data for operands.
 static cMatrix4 mpTemp;//,mpRotate;

 /// This will create a cMatrix4 object and will initialise all the static data required.
 cMatrix4();

 /// This will return the determinant of this objects matrix.
 float Determinant();

 /// THis will find the inverse of the matrix if it is a standard rotation / translation matrix. (0,1,2,4,5,6,8,9,10 are orthogonal. 3,7,11 are zero. 12,13,14 are position and 15 is one.)
 cMatrix4 InvertRotationMatrix();
 /// This will return the transpose of this objects matrix.
 cMatrix4 Transpose();

 cMatrix4 Translate(float lfX,float lfY,float lfZ);

 /// This will return a pointer to this objects matrix data.
 float *Matrix(){return mpData;};
 /// This will return a pointer to the float numbered lcData in this objects matrix.
 float *Matrix(uint8 lcData){return &mpData[lcData];};
 /// This will reutrn a pointer to this objects matrices position vector.
 float *Position(){return &mpData[12];};
 /// This will return this objects X position value.
 float X(){return mpData[12];};
/// This will return this objects Y position value. 
float Y(){return mpData[13];};
/// This will return this objects Z position value.
 float Z(){return mpData[14];};

 /// This will return the vector along this objects local X axis.
 float *XVect(){return mpData;};
/// This will return the vector along this objects local Y axis. 
float *YVect(){return &mpData[4];};
/// This will return the vector along this objects local Z axis.
 float *ZVect(){return &mpData[8];};
 
 /// This will restore this objects matrix to an identity matrix.
 void Identity();
 /// This will set every float in this objects matrix to be equal to zero.
 void Zero();

 /// This will multiply every float in this objects matrix by lVal.
 cMatrix4 operator*(float &lVal);
/// This will multiply every float in this objects matrix by lVal. 
cMatrix4 operator*(const float lVal);
 /// This will multiply every float in this objects matrix by lVal.
 cMatrix4 operator*(float *lVal);

/* /// This will multiply this objects matrix by the matrix pointed to by lVal. Returns This.lVal .
 cMatrix4 &operator*(cMatrix4 &lVal);*/
/// This will multiply this objects matrix by the matrix lVal. Returns This.lVal . 
cMatrix4 *operator*(cMatrix4 *lVal);
/// This will multiply this objects matrix by the matrix lVal. Returns This.lVal .
cMatrix4 operator*(cMatrix4 lVal);
 /// This will divide every float in this objects matrix by lVal.
 cMatrix4 operator/(float &lVal);
/// This will divide every float in this objects matrix by lVal. 
cMatrix4 operator/(const float lVal);

 /// This will add lVal to every float in this objects matrix.
 cMatrix4 operator+(float &lVal);
 /// This will add lVal to every float in this objects matrix.
 cMatrix4 operator+(const float lVal);
 /// This will add this matrix and the matrix lVal.
 cMatrix4 operator+(cMatrix4 &lVal);

/// This will deduct lVal from every float in this objects matrix.
 cMatrix4 operator-(float &lVal);
/// This will deduct lVal from every float in this objects matrix.
 cMatrix4 operator-(const float lVal);
/// This will subtract the matrix lVal from this matrix. 
cMatrix4 operator-(cMatrix4 &lVal);


 /// This will return the float in position liPos in mpData.
 float &operator[](uint16 liPos);
/// This will return the float in position [liColumn,liRow] in mpData.
 float &operator()(uint16 liColumn,uint16 liRow);

 /// This will equate every float in mpData to lVal. 
 float operator=(float &lVal);
/// This will equate every float in mpData to lVal. 
float operator=(const float lVal);
 /// This will equate the data in mpData to the data in lVal.mpData.
// cMatrix4 &operator=(cMatrix4 &lVal);
/// This will equate the data in mpData to the data in lVal->mpData. 
cMatrix4 *operator=(cMatrix4 *lVal);
/// This will equate the data in mpData to the data in lVal.mpData.
cMatrix4 operator=(cMatrix4 lVal);

float *operator=(float *lVal);

 /// This will position the current object to the 2D Vector lpPosition. (X,Y)
 void Position(c2DVf *lpPosition);
/// This will position the current object to lfX,lfY. (X,Y)
 void Position(float lfX,float lfY);

 /// This will position the current object to the 3D Vector lpPosition. (X,Y,Z)
 void Position(c3DVf *lpPosition);
/// This will position the current object to lfX,lfY,lfX. (X,Y,Z) 
void Position(float lfX,float lfY,float lfZ);

 /// This will take 2 or three floats depending if this cMatrix4 is set to 2D or 3D operations and set the position of the object.
 void Position(float *lpPos);
 
 /// This will set the objects X position to be equal to lfX.
 void PositionX(float lfX);
/// This will set the objects Y position to be equal to lfX. 
void PositionY(float lfY);
/// This will set the objects Z position to be equal to lfX.
 void PositionZ(float lfZ);

 /// This will advance the object along its local X axis by lfDistance.
 void AdvanceX(float lfDistance);
/// This will advance the object along its local Y axis by lfDistance. 
void AdvanceY(float lfDistance);
/// This will advance the object along its local Z axis by lfDistance.
 void AdvanceZ(float lfDistance);

 /// This will advance the object along its local X, Y and Z axis by lfX, lfY and lfZ.
 void Advance(float lfX,float lfY, float lfZ);

/// This will advance the object along the global X axis by lfX.
void GAdvanceX(float lfX);
/// This will advance the object along the global Y axis by lfX.
void GAdvanceY(float lfX);
/// This will advance the object along the global Z axis by lfX.
void GAdvanceZ(float lfX);
/// This will advance the object along the global X, Y and Z axis by lfX, lfY and lfZ.
void GAdvance(float lfX,float lfY,float lfZ);

 /// This will rotate the object around its local Z axis by lfAngle radians. Suitable for 2D objects
 void LRotate(float lfAngle);
/// This will rotate the object around its local X axis by lfAngle radians.
 void LRotateX(float lfAngle);
/// This will rotate the object around its local Y axis by lfAngle radians.
 void LRotateY(float lfAngle);
/// This will rotate the object around its local Z axis by lfAngle radians.
 void LRotateZ(float lfAngle);

/// This will rotate the object around its global X axis by lfAngle radians.
 void GRotateX(float lfAngle);
/// This will rotate the object around its global X axis by lfAngle radians.
 void GRotateY(float lfAngle);
/// This will rotate the object around its global X axis by lfAngle radians.
 void GRotateZ(float lfAngle);

/// This will rotate the object around the global X axis at point lfX,lfY,lfZ by lfAngle radians.
 void GRotateX(float lfAngle,float lfX,float lfY,float lfZ);
/// This will rotate the object around the global Y axis at point lfX,lfY,lfZ by lfAngle radians.
 void GRotateY(float lfAngle,float lfX,float lfY,float lfZ);
/// This will rotate the object around the global Z axis at point lfX,lfY,lfZ by lfAngle radians.
 void GRotateZ(float lfAngle,float lfX,float lfY,float lfZ);

/// This will rotate the object around the global X axis at point 0,0,0 by lfAngle radians.
 void GRotateOriginX(float lfAngle);
/// This will rotate the object around the global Y axis at point 0,0,0 by lfAngle radians.
 void GRotateOriginY(float lfAngle);
/// This will rotate the object around the global Z axis at point 0,0,0 by lfAngle radians.
 void GRotateOriginZ(float lfAngle);

/// This will scale the object by a factor of lfScale.
 void Resize(float lfScale);
/// This will scale the object along its local X axis by a factor of lfScale.
 void LResizeX(float lfScale);
/// This will scale the object along its local Y axis by a factor of lfScale.
 void LResizeY(float lfScale);
/// This will scale the object along its local Z axis by a factor of lfScale.
 void LResizeZ(float lfScale);

/// This will scale the object along its global X axis by a factor of lfScale.
 void GResizeX(float lfScale);
/// This will scale the object along its global Y axis by a factor of lfScale.
 void GResizeY(float lfScale);
/// This will scale the object along its global Z axis by a factor of lfScale.
 void GResizeZ(float lfScale);

 /// This will return the distance between this matrix and the cMatrix4 pointed to by lpOther.
 float Distance(cMatrix4 *lpOther);
 float Distance(float *lpOther);

/// This will return the square of the distance between this matrix and the cMatrix4 pointed to by lpOther. 
double DistanceSq(cMatrix4 *lpOther);
double DistanceSq(cMatrix4 lpOther);
double DistanceSq(float *lpOther);

 /// This will move this matrix along its local X and Y axis by lfX and lfY respectively. Suitable for 2D objects
  void Advance(float lfX,float lfY);
 /// This will move this matrix along its global X and Y axis by lfX and lfY respectively.
  void GAdvance(float lfX,float lfY);

 /// This will set the angle of rotation about this matrices X axis to lfAngle radians. Suitable for 2D objects.
  void Angle(float lfAngle);
/// This will rotate this matrix about its X axis by lfAngle radians. Suitable for 2D objects. 
 void Rotate(float lfAngle);
/// This will rotate this matrix in the X axis through 0,0 by lfAngle radians. Suitable for 2D objects. 
  void GRotateOrigin(float lfAngle);
/// This will rotate this matrix in the X axis through lfX,lfY by lfAngle radians. Suitable for 2D objects. 
  void GRotate(float lfAngle,float lfX,float lfY);

 /// This will set the current matrix to operate as if it is a 2D object.
  void Set2D();
/// This will set the current matrix to operate as if it is a 3D object.
  void Set3D();

/// This will display the current matrix Textually
  void Display();
///Will Copy the translation / Rotation matrix of the object lpOther;
 void CopyTranslation(cMatrix4 *lpOther);
  
  cMatrix4* Equals(cMatrix4* lpOther){memcpy(mpData,lpOther->Matrix(),sizeof(float)*16);return this;};
  cMatrix4* ThisMatrix(){return this;};

};

#endif
