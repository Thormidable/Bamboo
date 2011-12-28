#ifndef __WTCCAMERAMATRIX4_H__
#define __WTCCAMERAMATRIX4_H__
/**
* \brief This is a translation matrix for a camera object.
* This is a translation matrix for a camera. All the translations
* are inverted. Distances are 'reversed', Local rotations are 'globalised'
* and Global roatations are 'localised'. Effectively all the translations are
* inverted before they are applied to this matrix.
* The matrix Layout is four columns, each one representing a different axis or translation. \n
* Xx, Yx, Zx, 0.0f, Xy Yy Zy 0.0f, Xz Yz Xz 0.0f, 0.0, 0.0, 0.0, 1.0f. \n
* The Position of the Camera Matrix is kept seperate to the 4x4 matrix.
* Functions which accept cCameraMatrix objects or pointers automatically account for the differences in format.
* Otherwise one or the other should be Converted using the cMatrix4::ConvertToCameraMatrix() or cCameraMatrix4::ConvertToMatrix() functions.
*/
class cCameraMatrix4
{
 friend class cMatrix4;

 // This stores the 4x4 matrix of floats that is the rotation matrix.
 float mpData[16];
 // This is a static cCameraMatrix4 to store data for operations.
 static cCameraMatrix4 mpTemp;
 // This is a static 4x4 matrix to allow fast zeroing of this 4x4 matrix.
 static float mpZero[];
 // This is a static 4x4 matrix to allow fast restoration of this matrix to an identity matrix.
 static float mpIdentity[];

public:



 /// This will return a pointer to this objects matrix.
 float *Matrix();
 /// This will return the position vector of this objects matrix.
 float *Position();

/// The position of this matrix has been seperated from the rest of the matrix as the camera should rotate around 0,0,0, not itself?
float mpPosition[3];

 /// This will return the X position of this objects matrix.
 float X();
/// This will return the Y position of this objects matrix.
float Y();
/// This will return the Z position of this objects matrix.
float Z();



 /// This will set this objects matrix position vector to be the same as lpPosition.
 void Position(c3DVf *lpPosition);
/// This will set this objects matrix position vector to be lfX,lfY,lfZ.
 void Position(float lfX,float lfY,float lfZ);
 /// This will set this objects X position to he lfX.
void PositionX(float lfX);
 /// This will set this objects Y position to he lfY.
void PositionY(float lfY);
 /// This will set this objects Z position to he lfZ.
void PositionZ(float lfZ);


/// This will advance the position of this objects X position by lfDistance along local axis.
void AdvanceX(float lfDistance);
/// This will advance the position of this objects Y position by lfDistance along local axis.
void AdvanceY(float lfDistance);
/// This will advance the position of this objects Z position by lfDistance along local axis.
void AdvanceZ(float lfDistance);
/// This will advance the position of this objects X,Y and Z positions by lfX,lfY and lfZ along local axis.
void Advance(float lfX,float lfY,float lfZ);

/// This will advance the position of this objects X position by lfDistance along global axis.
void GAdvanceX(float lfDistance);
/// This will advance the position of this objects Y position by lfDistance along global axis.
void GAdvanceY(float lfDistance);
/// This will advance the position of this objects Z position by lfDistance along global axis.
void GAdvanceZ(float lfDistance);
/// This will advance the position of this objects X,Y and Z positions by lfX,lfY and lfZ along global axis.
void GAdvance(float lfX,float lfY,float lfZ);

 /// This will localy rotate the object by lfAngle radians about the Z axis. This is suitable to be used by 2D objects.
 void Rotate(float lfAngle);
 /// This will rotate the object by lfAngle radians about its local X axis. This is suitable for use by 3D objects.
 void RotateX(float lfAngle);
/// This will rotate the object by lfAngle radians about its local Y axis. This is suitable for use by 3D objects.
void RotateY(float lfAngle);
/// This will rotate the object by lfAngle radians about its local Z axis. This is suitable for use by 3D objects.
 void RotateZ(float lfAngle);

/// This will rotate the object by lfAngle radians about its global X axis. This is suitable for use by 3D objects.
 void GRotateX(float lfAngle);
/// This will rotate the object by lfAngle radians about its global Y axis. This is suitable for use by 3D objects.
 void GRotateY(float lfAngle);
/// This will rotate the object by lfAngle radians about its global Z axis. This is suitable for use by 3D objects.
 void GRotateZ(float lfAngle);

/// This will rotate the object by lfAngle radians about the global X axis of the point lfX,lfY,lfZ. This is suitable for use by 3D objects.
 void GRotateX(float lfAngle,float lfX,float lfY,float lfZ);
/// This will rotate the object by lfAngle radians about the global Y axis of the point lfX,lfY,lfZ. This is suitable for use by 3D objects.
 void GRotateY(float lfAngle,float lfX,float lfY,float lfZ);
/// This will rotate the object by lfAngle radians about the global Z axis of the point lfX,lfY,lfZ. This is suitable for use by 3D objects.
 void GRotateZ(float lfAngle,float lfX,float lfY,float lfZ);



 /// This will scale this objects matrix by a factor of lfScale.
 void Resize(float lfScale);
 /// This will scale this objects local X axis by a factor of lfScale.
 void ResizeX(float lfScale);
/// This will scale this objects local Y axis by a factor of lfScale.
void ResizeY(float lfScale);
/// This will scale this objects local Z axis by a factor of lfScale.
 void ResizeZ(float lfScale);

/// This will scale this objects globally along the X axis by a factor of lfScale.
 void GResizeX(float lfScale);
/// This will scale this objects globally along the Y axis by a factor of lfScale.
 void GResizeY(float lfScale);
/// This will scale this objects globally along the Z axis by a factor of lfScale.
 void GResizeZ(float lfScale);

 /// This will return the 3D distance between this matrix and the matrix pointed to by lpOther.
 uint32 Distance3D(float *lpOther);
///This will make the camera position itself the distance lfDist behind the matrix lpOther facing in the same direction as the matrix lpOther.
void Follow(cMatrix4* lpOther,float lfDist);
///This will make the camera position itself the distance lfDist behind the matrix lpOther facing in the same direction as the matrix lpOther.
void Follow(cMatrix4& lpOther,float lfDist);
///This will make the camera point itself at the global point defined by the three float array lpPos.
void PointAt(float *mpPos);
///This will make the camera point itself at the global point defined by the three float array lpPos.
void PointAt(cMatrix4 *mpPos);
///This will make the camera point itself at the global point defined by the three float array lpPos.
void PointAt(cMatrix4 &mpPos);
///This will make the camera point itself at the global point defined by the three float array lpPos.
void PointAt(c3DVf &mpPos);
///This will make the camera point itself at the global point defined by the three float array lpPos.
void PointAt(c3DVf *mpPos);


///Will Make this equal the 4x4 cCameraMatrix4 lpOther
void Equals(cCameraMatrix4 *lpOther);
///Will Make this equal the 4x4 cCameraMatrix4 lpOther
void Equals(cCameraMatrix4 &lpOther);
///Will Make this equal the 4x4 cMatrix4 lpOther
void Equals(cMatrix4 *lpOther);
///Will Make this equal the 4x4 cMatrix4 lpOther
void Equals(cMatrix4 &lpOther);

///Will multiply this matrix by the 4x4 cCameraMatrix pointed to by lpOther
void Multiply(cCameraMatrix4 *lpOther);
///Will multiply this matrix by the 4x4 cCameraMatrix lpOther
void Multiply(cCameraMatrix4 &lpOther);
///Will multiply this matrix by the cMatrix4 pointed to by lpOther
void Multiply(cMatrix4 *lpOther);
///Will multiply this matrix by the cMatrix4 lpOther
void Multiply(cMatrix4 &lpOther);

 /// This will return the float in the position liPos in this objects matrix.
 float &operator[](uint16 liPos);
/// This will return the float in the position [liColumn,liRow] in this objects matrix.
 float &operator()(uint16 liColumn,uint16 liRow);

 // This will multiplty the matrix by a float.
 cCameraMatrix4 operator*(float &lVal);
// This will multiplty the matrix by a float.
 cCameraMatrix4 operator*(const float lVal);
/*
* \brief This will multiply this matrix by the matrix lVal.
* \param lVal is a cCameraMatrix4 object to be multiplied by this matrix.
* This will multiply a cCameraMatrix4 object by this objects matrix. This.lVal
*/
 cCameraMatrix4 operator*(cCameraMatrix4 &lVal);
/*
* \brief This will multiply this matrix by the matrix pointed to by lVal.
* \param lVal is a pointer to a cCameraMatrix4 object to be multiplied by this matrix.
* This will multiply the cCameraMatrix4 object pointed to by lVal by this objects matrix. This.lVal
*/
 cCameraMatrix4 *operator*(cCameraMatrix4 *lVal);

// This will devide this objects matrix by the float lVal
 cCameraMatrix4 operator/(float &lVal);
// This will devide this objects matrix by the float lVal
cCameraMatrix4 operator/(const float lVal);

// This will add lVal to this objects matrix. lVal is added to every position in the matrix.
 cCameraMatrix4 operator+(float &lVal);
// This will add lVal to this objects matrix. lVal is added to every position in the matrix.
 cCameraMatrix4 operator+(const float lVal);
// This will add this objects matrix and the matrix lVal.
 cCameraMatrix4 operator+(cCameraMatrix4 &lVal);

// This will deduct lVal from this objects matrix. lVal is deducted from every position in the matrix.
 cCameraMatrix4 operator-(float &lVal);
// This will deduct lVal from this objects matrix. lVal is deducted from every position in the matrix.
 cCameraMatrix4 operator-(const float lVal);
// This will deduct the matrix lVal from this objects matrix.
 cCameraMatrix4 operator-(cCameraMatrix4 &lVal);



// This will set every float in this objects matrix to lVal.
 float operator=(float &lVal);
// This will set every float in this objects matrix to lVal.
float operator=(const float lVal);
// This will set this objects matrix to be the same as the matrix lVal.
 cCameraMatrix4 operator=(cCameraMatrix4 &lVal);
// This will set this objects matrix to be the same as the matrix lVal.
 cCameraMatrix4 *operator=(cCameraMatrix4 *lVal);

/// This will set this objects matrix position (2D - X,Y) vector to be the same as lpPosition.
 void Position(c2DVf *lpPosition);
  /// This will set this objects matrix position vector to be lfX,lfY.
void Position(float lfX,float lfY);
 /// This will set the current objects matrix to be rotated to the absolute angle lfAngle. This is suitable for 2D objects.
 void Angle(float lfAngle);
 /// This will return the 2D distance between this matrix and the matrix pointed to by lpOther.
uint32 Distance2D(float *lpOther);

 /// This will return this cCameraMatrix in the format of a cMatrix4. This is because they have different formats.
 cMatrix4 &ConvertToMatrix();

 /// This will return the transpose of this objects matrix ready for multiplications etc.
 cCameraMatrix4 Transpose();
  /// This will make all terms of the matrix, the opposite sign to what they area.
 void InvSign();
 /// This will restore this objects matrix to an Identity matrix.
 void Identity();
 /// This will make the entire objects matrix equal to zero.
 void Zero();
  /// This will create this matrix, and initialise all the static data for operations.
 cCameraMatrix4();
 /// This will return the determinant of this matrix.
 float Determinant();

 void Display();
};


#endif
