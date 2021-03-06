#ifndef __WTCMATRIX4_H__
#define __WTCMATRIX4_H__


class cCameraMatrix4;
class cDoubleMatrix4;
/**
* \brief this is a standard 4x4 translation matrix for objects.
* This is a standard 4x4 translation matrix for objects. It can be used for
* both 2D and 3D objects. By default it is a 3D matrix, It can be converted to a
* 2D matrix by using the function Set2D().
* The matrix Layout is four columns, each one representing a different axis or translation.
* Xx, Xy, Xz, 0.0f, Yx Yy Yz 0.0f, Zx Zy Zx 0.0f, Px, Py, Pz, 1.0f
*/
class cMatrix4
{
  friend class cCameraMatrix4;
protected:

 float mpData[16];

 //This is a pointer to a static array to allow this objects matrix to be quickly zeroed.
 static float mpZero[];
 // This is a pointer to a static array to allow this objects matrix to be quickly restored to an identity matrix.
 static float mpIdentity[];


public:

/// This is a boolean flag to define whether the object is 3D or 2D. True is 3D. False is 2D. See cMatrix4::Set3D() and cMatrix4::Set2D().
 bool mb3D;

    cMatrix4(const cDoubleMatrix4 &lpOther);
    cMatrix4(cDoubleMatrix4 *lpOther);
    cMatrix4(float *lpOther);
    cMatrix4(double *lpOther);
    cMatrix4(float lfX,float lfY,float lfZ);
	cMatrix4(float lfX,float lfY,float lfZ,float lfXA,float lfYA,float lfZA);

 // This will update the OpenGL matrix on the top of matrix stack to be identical to this matrix.
 void UpdateMatrix();
 // This appears to multiply this matrix by the matrix lpMatrix and equate this matrix to the result.
 void UpdateMatrix(float *lpMatrix);

 // This is a static cMatrix4 used to store data for operands.
 static cMatrix4 mpTemp;

  ///This will move the Object along the local axis the distance of lfX, lfY and lfZ.
 void Translate(float lfX,float lfY,float lfZ);

///This will move the Object along the local axis the distance of the array of three floats pointed to by lpDist.
 void Translate(float *lpDist);

 /// This will return a pointer to this objects matrix data.
 float *Matrix();
 /// This will return a pointer to the float numbered lcData in this objects matrix.
 float *Matrix(uint8 lcData);
 /// This will reutrn a pointer to this objects matrices position vector.
 float *Position();
 /// This will return this objects X position value.
 float X();
/// This will return this objects Y position value.
float Y();
/// This will return this objects Z position value.
 float Z();

 /// This will return the vector along this objects local X axis.
 float *XVect();
/// This will return the vector along this objects local Y axis.
float *YVect();
/// This will return the vector along this objects local Z axis.
 float *ZVect();

 ///X Component of the X axis.
 float Xx();
 ///Y Component of the X axis.
 float Xy();
 ///Z Component of the X axis.
 float Xz();

 ///X Component of the Y axis.
 float Yx();
 ///Y Component of the Y axis.
 float Yy();
 ///Z Component of the Y axis.
 float Yz();

 ///X Component of the Z axis.
 float Zx();
 ///Y Component of the Z axis.
 float Zy();
 ///Z Component of the Z axis.
 float Zz();


/// This will take 2 or three floats depending if this cMatrix4 is set to 2D or 3D operations and set the position of the object.
 void Position(float *lpPos);
 /// This will set the objects X position to be equal to lfX.
 void PositionX(float lfX);
/// This will set the objects Y position to be equal to lfX.
void PositionY(float lfY);
/// This will set the objects Z position to be equal to lfX.
 void PositionZ(float lfZ);

 ///This will make this object have the same Position as the cMatrix4 lpOther.
 void Position(cMatrix4 &lpOther);
 ///Will copy the position data from the matrix lpOther.
 void Position(cMatrix4 *lpOther);

 /// This will position the current object to the 2D Vector lpPosition. (X,Y)
 void Position(c2DVf *lpPosition);
  /// This will position the current object to the 2D Vector lpPosition. (X,Y)
 void Position(c2DVf lpPosition);
/// This will position the current object to lfX,lfY. (X,Y)
 void Position(float lfX,float lfY);

 /// This will position the current object to the 3D Vector lpPosition. (X,Y,Z)
 void Position(c3DVf *lpPosition);
 /// This will position the current object to the 3D Vector lpPosition. (X,Y,Z)
 void Position(c3DVf lpPosition);
 /// This will position the current object to lfX,lfY,lfX. (X,Y,Z)
 void Position(float lfX,float lfY,float lfZ);

 /// Will Advance the object along its local axis by the distance of the floats in the array lfDistance
 void Advance(float *lfDistance);
 /// Will Advance the object along its local X and Y axis by the Vector lfDistances;
 void Advance(c2DVf *lfDistances);
 /// Will Advance the object along its local X, Y and Z axis by the Vector lfDistances;
 void Advance(c3DVf *lfDistances);
 /// Will Advance the object along its local X and Y axis by the Vector lfDistances;
 void Advance(c2DVf &lfDistances);
 /// Will Advance the object along its local X, Y and Z axis by the Vector lfDistances;
 void Advance(c3DVf &lfDistances);
  ///This will advance an object along the (2D or 3D) Vector that is its facing by a distance of lfDistance;
void Advance(float lfDistance);
 /// This will advance the object along its local X axis by lfDistance.
 void AdvanceX(float lfDistance);
/// This will advance the object along its local Y axis by lfDistance.
void AdvanceY(float lfDistance);
/// This will advance the object along its local Z axis by lfDistance.
 void AdvanceZ(float lfDistance);
 /// This will move this matrix along its local X and Y axis by lfX and lfY respectively. Suitable for 2D objects
  void Advance(float lfX,float lfY);
 /// This will advance the object along its local X, Y and Z axis by lfX, lfY and lfZ.
 void Advance(float lfX,float lfY, float lfZ);

 /// Will Advance the object along its global axis by the distance of the floats in the array lfDistance
 void GAdvance(float *lfDistance);
/// This will advance the object along the global X axis by lfX.
void GAdvanceX(float lfX);
/// This will advance the object along the global Y axis by lfX.
void GAdvanceY(float lfX);
/// This will advance the object along the global Z axis by lfX.
void GAdvanceZ(float lfX);
 /// This will move this matrix along its global X and Y axis by lfX and lfY respectively.
  void GAdvance(float lfX,float lfY);
/// This will advance the object along the global X, Y and Z axis by lfX, lfY and lfZ.
void GAdvance(float lfX,float lfY,float lfZ);

/// This will set the angle of rotation about this matrices X axis to lfAngle radians. Suitable for 2D objects.
  void Angle(float lfAngle);
/// This will rotate this matrix in the X axis through 0,0 by lfAngle radians. Suitable for 2D objects.
  void GRotateOrigin(float lfAngle);
/// This will rotate this matrix in the X axis through lfX,lfY by lfAngle radians. Suitable for 2D objects.
  void GRotate(float lfAngle,float lfX,float lfY);

///Will copy the rotation of the matrix lpRotation
void Rotation(float *lpRotation);
///Will copy the rotation of the matrix lpRotation
void Rotation(cMatrix4 *lpRotation);
///This will make this object have the same Rotation as the cMatrix4 lpOther.
void Rotation(cMatrix4 &lpOther);

 /// This will rotate the object around its local Z axis by lfAngle radians. Suitable for 2D objects
 void Rotate(float lfAngle);
/// This will rotate the object around its local X axis by lfAngle radians.
 void RotateX(float lfAngle);
/// This will rotate the object around its local Y axis by lfAngle radians.
 void RotateY(float lfAngle);
/// This will rotate the object around its local Z axis by lfAngle radians.
 void RotateZ(float lfAngle);

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

///This will make the current object look at the point lfPoint in Local Co-ordinates.
 void LookAt(float *lfPoint);
 ///This will make the current object look at the point lfPoint in Local Co-ordinates.
 void LookAt(cMatrix4 *lfPoint);
 ///This will make the current object look at the point lfPoint in Local Co-ordinates.
 void LookAt(cMatrix4 &lfPoint);
 ///This will make the current object look at the point lfPoint in Local Co-ordinates.
 void LookAt(float lfX,float lfY,float lfZ);
///This will make the current object look at the point lfVect in Local Co-ordinates.
 void LookAt(c3DVf lfVect);

///This will make the current object look in the direction lfVect in Local Co-ordinates.
 void LookVector(float *lfVect);
 ///This will make the current object look in the direction lfX,lfY,lfZ in Local Co-ordinates.
 void LookVector(float lfX,float lfY,float lfZ);
 ///This will make the current object look in the direction lfVect in Local Co-ordinates.
 void LookVector(c3DVf lfVect);


 ///This will give the angle this object must roll (about X Axis) to have the point on its ZY Plane.
 float RollToPointPitch(float *lfPoint);
 ///This will give the angle this object must roll (about X Axis) to have the point on its ZX Plane.
 float RollToPointYaw(float *lfPoint);
 ///This will give the angle this object must Yaw (about Y Axis) to be 'facing' the Local point lfPoint.
 float YawToPoint(float *lfPoint);
 ///This will give the angle this object must pitch (about Z Axis) to be 'facing' the Local point lfPoint.
 float PitchToPoint(float *lfPoint);

///This will give the angle between this matrices z axis and the vector from this matrix to the point lfPoint.
float AngleToPoint(float *lfPoint);
///This will return true if the angle between this matrices z axis and the vector from this matrix to the point lfPoint is less than lfAngle.
bool AngleToPointCheck(float *lfPoint,float lfAngle);


 ///This will give the angle this object must roll (about X Axis) to have the Vector lfVector on its ZY Plane.
 float RollToVectorPitch(float *lfVector);
 ///This will give the angle this object must roll (about X Axis) to have the Vector lfVector on its ZX Plane.
 float RollToVectorYaw(float *lfVector);
 ///This will give the angle this object must Yaw (about Y Axis) to be inline with the Local Vector lfVector.
 float YawToVector(float *lfVector);
 ///This will give the angle this object must pitch (about Z Axis) to be inline with the Local Vector lfVector.
 float PitchToVector(float *lfVector);

///This will give the angle between this matrices z axis and the vector lfVector.
float AngleToVector(float *lfVector);
///This will return true if the angle between this matrices z axis and the vector lfVector is less than lfAngle. Otherwise will return false.
bool AngleToVectorCheck(float *lfVector,float lfAngle);


 ///This will give the angle this object must roll (about X Axis) to have the point on its ZY Plane.
 float RollToPointPitch(c3DVf lfPoint);
 ///This will give the angle this object must roll (about X Axis) to have the point on its ZX Plane.
 float RollToPointYaw(c3DVf lfPoint);
 ///This will give the angle this object must Yaw (about Y Axis) to be 'facing' the Local point lfPoint.
 float YawToPoint(c3DVf lfPoint);
 ///This will give the angle this object must pitch (about Z Axis) to be 'facing' the Local point lfPoint.
 float PitchToPoint(c3DVf lfPoint);

///This will give the angle between this matrices z axis and the vector from this matrix to the point lfPoint.
float AngleToPoint(c3DVf lfPoint);
///This will return true if the angle between this matrices z axis and the vector from this matrix to the point lfPoint is less than lfAngle.
bool AngleToPointCheck(c3DVf lfPoint,float lfAngle);


 ///This will give the angle this object must roll (about X Axis) to have the Vector lfVector on its ZY Plane.
 float RollToVectorPitch(c3DVf lfVector);
 ///This will give the angle this object must roll (about X Axis) to have the Vector lfVector on its ZX Plane.
 float RollToVectorYaw(c3DVf lfVector);
 ///This will give the angle this object must Yaw (about Y Axis) to be inline with the Local Vector lfVector.
 float YawToVector(c3DVf lfVector);
 ///This will give the angle this object must pitch (about Z Axis) to be inline with the Local Vector lfVector.
 float PitchToVector(c3DVf lfVector);

///This will give the angle between this matrices z axis and the vector lfVector.
float AngleToVector(c3DVf lfVector);
///This will return true if the angle between this matrices z axis and the vector lfVector is less than lfAngle. Otherwise will return false.
bool AngleToVectorCheck(c3DVf lfVector,float lfAngle);

///This will return the objects Roll angle (angle between the Y Axis and the Local objects Identity YZ Plane)
float Roll();
///This will return the objects Yaw angle (angle between the Z Axis and the Local objects Identity YZ Plane)
float Yaw();
///This will return the objects Pitch angle (angle between the Z Axis and the Local objects Identity XZ Plane)
float Pitch();


  ///Makes this matrix Equal the cMatrix4 pointed to by lpOther
  void Equals(cMatrix4 *lpOther);
  ///Makes this matrix Equal the cMatrix4 lpOther
  void Equals(cMatrix4 lpOther);
    ///Makes this matrix Equal the cDoubleMatrix4 pointed to by lpOther
  void Equals(cDoubleMatrix4 *lpOther);
  ///Makes this matrix Equal the cDoubleMatrix4 lpOther
  void Equals(cDoubleMatrix4 lpOther);
  ///Makes this matrix Equal the cCameraMatrix4 lpOther
  void Equals(cCameraMatrix4 &lpOther);
  ///Makes this matrix Equal the cCameraMatrix lpOther
  void Equals(cCameraMatrix4 *lpOther);
  ///Makes this matrix Equal the 4x4 float matrix pointed to by lpOther
  void Equals(float *lpOther);


  /// This will scale the object by a factor of lfScale.
 void Resize(float lfScale);
/// This will scale the object along its local X axis by a factor of lfScale.
 void ResizeX(float lfScale);
/// This will scale the object along its local Y axis by a factor of lfScale.
 void ResizeY(float lfScale);
/// This will scale the object along its local Z axis by a factor of lfScale.
 void ResizeZ(float lfScale);

/// This will scale the object along its global X axis by a factor of lfScale.
 void GResizeX(float lfScale);
/// This will scale the object along its global Y axis by a factor of lfScale.
 void GResizeY(float lfScale);
/// This will scale the object along its global Z axis by a factor of lfScale.
 void GResizeZ(float lfScale);

 ///This will set the objects X Axis to the scale lfScale.
 void ScaleX(float lfScale);
 ///This will set the objects Y Axis to the scale lfScale.
 void ScaleY(float lfScale);
 ///This will set the objects Z Axis to the scale lfScale.
 void ScaleZ(float lfScale);

 ///This will get the objects X Axis scale.
 float ScaleX();
 ///This will get the objects Y Axis scale.
 float ScaleY();
 ///This will get the objects Z Axis scale.
 float ScaleZ();

 ///This will set the objects Global X Axis to the scale lfScale.
 void GScaleX(float lfScale);
 ///This will set the objects Global Y Axis to the scale lfScale.
 void GScaleY(float lfScale);
 ///This will set the objects Global Z Axis to the scale lfScale.
 void GScaleZ(float lfScale);

 ///This will get the objects Global X Axis scale.
 float GScaleX();
 ///This will get the objects Global Y Axis scale.
 float GScaleY();
 ///This will get the objects Global Z Axis scale.
 float GScaleZ();


/// This will return the distance between this matrix and the cMatrix4 pointed to by lpOther.
 float Distance(cMatrix4 &lpOther);
  /// This will return the distance between this matrix and the cMatrix4 pointed to by lpOther.
 float Distance(cMatrix4 *lpOther);
 /// This will return the distance between this matrix and the Global Position lpOther.
 float Distance(float *lpOther);
 /// This will return the distance between this matrix and the Global Position lpOther.
 float Distance(c3DVf lpOther);

/// This will return the square of the distance between this matrix and the cMatrix4 pointed to by lpOther.
double DistanceSq(cMatrix4 *lpOther);
/// This will return the square of the distance between this matrix and the cMatrix4 pointed to by lpOther.
double DistanceSq(cMatrix4 lpOther);
/// This will return the square of the distance between this matrix and the Global Position lpOther.
double DistanceSq(float *lpOther);
/// This will return the square of the distance between this matrix and the Global Position lpOther.
double DistanceSq(c3DVf lpOther);

///This will return the distance between this matrix and the origin
float Distance();
///This will return the square of the distance between this matrix and the origin
double DistanceSq();

 /// This will return the float in position liPos in mpData.
 float &operator[](uint16 liPos);
/// This will return the float in position [liColumn,liRow] in mpData.
 float &operator()(uint16 liColumn,uint16 liRow);

// This will multiply every float in this objects matrix by lVal.
 cMatrix4 operator*(float &lVal);
// This will multiply every float in this objects matrix by lVal.
cMatrix4 operator*(const float lVal);
// This will this Matrix by the 4x4 array lVal. This is the same as multiplying two matrices.
 cMatrix4 operator*(float *lVal);

/* /// This will multiply this objects matrix by the matrix pointed to by lVal. Returns This.lVal .
 cMatrix4 &operator*(cMatrix4 &lVal);*/
// This will multiply this objects matrix by the matrix lVal. Returns This.lVal .
cMatrix4 *operator*(cMatrix4 *lVal);
// This will multiply this objects matrix by the matrix lVal. Returns This.lVal .
cMatrix4 operator*(cMatrix4 lVal);
// This will divide every float in this objects matrix by lVal.
 cMatrix4 operator/(float &lVal);
// This will divide every float in this objects matrix by lVal.
cMatrix4 operator/(const float lVal);

// This will add lVal to every float in this objects matrix.
 cMatrix4 operator+(float &lVal);
// This will add lVal to every float in this objects matrix.
 cMatrix4 operator+(const float lVal);
// This will add this matrix and the matrix lVal.
 cMatrix4 operator+(cMatrix4 &lVal);

// This will deduct lVal from every float in this objects matrix.
 cMatrix4 operator-(float &lVal);
// This will deduct lVal from every float in this objects matrix.
 cMatrix4 operator-(const float lVal);

// This will subtract the matrix lVal from this matrix.
cMatrix4 operator-(cMatrix4 &lVal);




// This will equate every float in mpData to lVal.
 float operator=(float &lVal);
// This will equate every float in mpData to lVal.
float operator=(const float lVal);
// This will equate the data in mpData to the data in lVal.mpData.
// cMatrix4 &operator=(cMatrix4 &lVal);
// This will equate the data in mpData to the data in lVal->mpData.
cMatrix4 operator=(cMatrix4 *lVal);
// This will equate the data in mpData to the data in lVal.mpData.
cMatrix4 operator=(cMatrix4 lVal);
cMatrix4 operator=(cDoubleMatrix4 *lVal);
// This will equate the data in mpData to the data in lVal.mpData.
cMatrix4 operator=(cDoubleMatrix4 lVal);

cMatrix4 operator=(float *lVal);








 /// This will set the current matrix to operate as if it is a 2D object.
  void Set2D();
/// This will set the current matrix to operate as if it is a 3D object.
  void Set3D();

// This will display the current matrix Textually
  void Display();


/// This will create a cMatrix4 object and will Set the matrix to an Identity Matrix;.
 cMatrix4();

 /// This will return the determinant of this objects matrix.
 float Determinant();

 ///Returns this Matrix. For objects which have inherited cMatrix4.
 cMatrix4 &ThisMatrix();

 ///Returns a pointer to this matrix
 cMatrix4 *ThisMatrixPointer();

 ///This will calculate the inversion matrix for this matrix.
 cMatrix4 InversionMatrix();
 /// This will return the transpose of this objects matrix.
 cMatrix4 Transpose();

 /// This will restore this objects matrix to an identity matrix.
 void Identity();
 /// This will set every float in this objects matrix to be equal to zero.
 void Zero();
 /// This will reset the objects Local Rotations.
 void ResetRotations();
 ///This will reset the objects Local Position.
 void ResetPosition();
 ///This will multiply this matrix by the cMatrix4 Other.
 void Multiply(cMatrix4 &Other);
 ///This will multiply this matrix by the cMatrix4 Other.
 void Multiply(cMatrix4 *Other);
 ///This will multiply this matrix by the cCameraMatrix4 Other.
 void Multiply(cCameraMatrix4 *Other);
 ///This will multiply this matrix by the cCameraMatrix4 Other.
 void Multiply(cCameraMatrix4 &Other);

 ///This will multiply this matrix by the 4x4 float Matrix pointed to by Other.
 void Multiply(float *Other);

 /// This will multiply this matrix by the 4 dimensional Vector lfVector.
 c4DVf MultiplyVector(float *lfVector);
 /// This will multiply this matrix by the 4 dimensional Vector lfVector.
 c4DVf MultiplyVector(c4DVf lfVector);
 /// This will multiply this matrix by the 4 dimensional Vector lfVector.
 c4DVf Multiply(c4DVf lfVector);

 /// This will multiply this matrices angles by the 3 dimensional Vector lfVector.
 c3DVf RotateVectorByAngles(float *lfVector);
 /// This will multiply this matrices angles by the 3 dimensional Vector lfVector.
 c3DVf RotateVectorByAngles(c3DVf lfVector);
 /// This will multiply this matrices angles by the 3 dimensional Vector lfVector.
 c3DVf Multiply(c3DVf lfVector);

 /// This will multiply this matrices position by the 3 dimensional Vector lfVector.
 c3DVf MultiplyVectorPosition(float *lfVector);
 /// This will multiply this matrices position by the 3 dimensional Vector lfVector.
 c3DVf MultiplyVectorPosition(c3DVf lfVector);


  /// This will return this cMatrix4 in the format of a cCameraMatrix4. This is because they have different formats.
  cCameraMatrix4 &ConvertToCameraMatrix();

  void InvSign();

  bool Is3D();

  ///This will transpose the point to be relative to this matrix, where the point SameSpace starts in the same space (Global / Camaera / Local)
  c3DVf FindPointRelative(c3DVf SameSpace);

};

class cIdentityMatrix : public cMatrix4
{
    cIdentityMatrix();
    static cIdentityMatrix *spInstance;
public:
    static cIdentityMatrix Instance();
};

class cZeroMatrix : public cMatrix4
{
    static cZeroMatrix *spInstance;
    cZeroMatrix();
public:
    static cZeroMatrix Instance();
};


#endif
