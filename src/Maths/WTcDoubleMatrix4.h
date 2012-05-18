#ifndef __WTCDOUBLEMATRIX4_H__
#define __WTCDOUBLEMATRIX4_H__

/**
* \brief this is a standard 4x4 translation matrix for objects with components consisting of double.
* This is a standard 4x4 translation matrix for objects. It can be used for
* both 2D and 3D objects. By default it is a 3D matrix, It can be converted to a
* 2D matrix by using the function Set2D().
* The matrix Layout is four columns, each one representing a different axis or translation.
* Xx, Xy, Xz, 0.0f, Yx Yy Yz 0.0f, Zx Zy Zx 0.0f, Px, Py, Pz, 1.0f
*/
class cDoubleMatrix4
{
  //friend class cCameraMatrix4;
  //friend class cDoubleCameraMatrix4;
protected:

 double mpData[16];

 //This is a pointer to a static array to allow this objects matrix to be quickly zeroed.
 static double mpZero[];
 // This is a pointer to a static array to allow this objects matrix to be quickly restored to an identity matrix.
 static double mpIdentity[];

public:
 /// This is a boolean flag to define whether the object is 3D or 2D. True is 3D. False is 2D. See cDoubleMatrix4::Set3D() and cDoubleMatrix4::Set2D().
 bool mb3D;
/*
    cDoubleMatrix4(const cDoubleMatrix4 &lpOther);
    cDoubleMatrix4(cDoubleMatrix4 *lpOther);
    */
    cDoubleMatrix4(const cMatrix4 &lpOther);
    cDoubleMatrix4(cMatrix4 *lpOther);



 // This is a static cDoubleMatrix4 used to store data for operands.
 static cDoubleMatrix4 mpTemp;

  ///This will move the Object along the local axis the distance of lfX, lfY and lfZ.
 void Translate(double lfX,double lfY,double lfZ);

///This will move the Object along the local axis the distance of the array of three doubles pointed to by lpDist.
 void Translate(double *lpDist);

 /// This will return a pointer to this objects matrix data.
 double *Matrix();
 /// This will return a pointer to the double numbered lcData in this objects matrix.
 double *Matrix(uint8 lcData);
 /// This will reutrn a pointer to this objects matrices position vector.
 double *Position();
 /// This will return this objects X position value.
 double X();
/// This will return this objects Y position value.
double Y();
/// This will return this objects Z position value.
 double Z();

 /// This will return the vector along this objects local X axis.
 double *XVect();
/// This will return the vector along this objects local Y axis.
double *YVect();
/// This will return the vector along this objects local Z axis.
 double *ZVect();

 ///X Component of the X axis.
 double Xx();
 ///Y Component of the X axis.
 double Xy();
 ///Z Component of the X axis.
 double Xz();

 ///X Component of the Y axis.
 double Yx();
 ///Y Component of the Y axis.
 double Yy();
 ///Z Component of the Y axis.
 double Yz();

 ///X Component of the Z axis.
 double Zx();
 ///Y Component of the Z axis.
 double Zy();
 ///Z Component of the Z axis.
 double Zz();


/// This will take 2 or three doubles depending if this cDoubleMatrix4 is set to 2D or 3D operations and set the position of the object.
 void Position(double *lpPos);
 /// This will set the objects X position to be equal to lfX.
 void PositionX(double lfX);
/// This will set the objects Y position to be equal to lfX.
void PositionY(double lfY);
/// This will set the objects Z position to be equal to lfX.
 void PositionZ(double lfZ);

 ///This will make this object have the same Position as the cDoubleMatrix4 lpOther.
 void Position(cDoubleMatrix4 &lpOther);
 ///Will copy the position data from the matrix lpOther.
 void Position(cDoubleMatrix4 *lpOther);

 /// This will position the current object to the 2D Vector lpPosition. (X,Y)
 void Position(c2DVd *lpPosition);
/// This will position the current object to lfX,lfY. (X,Y)
 void Position(double lfX,double lfY);

 /// This will position the current object to the 3D Vector lpPosition. (X,Y,Z)
 void Position(c3DVd *lpPosition);
 /// This will position the current object to lfX,lfY,lfX. (X,Y,Z)
 void Position(double lfX,double lfY,double lfZ);

 /// Will Advance the object along its local axis by the distance of the doubles in the array lfDistance
 void Advance(double *lfDistance);
 /// Will Advance the object along its local X and Y axis by the Vector lfDistances;
 void Advance(c2DVd *lfDistances);
 /// Will Advance the object along its local X, Y and Z axis by the Vector lfDistances;
 void Advance(c3DVd *lfDistances);
 /// Will Advance the object along its local X and Y axis by the Vector lfDistances;
 void Advance(c2DVd &lfDistances);
 /// Will Advance the object along its local X, Y and Z axis by the Vector lfDistances;
 void Advance(c3DVd &lfDistances);
  ///This will advance an object along the (2D or 3D) Vector that is its facing by a distance of lfDistance;
void Advance(double lfDistance);
 /// This will advance the object along its local X axis by lfDistance.
 void AdvanceX(double lfDistance);
/// This will advance the object along its local Y axis by lfDistance.
void AdvanceY(double lfDistance);
/// This will advance the object along its local Z axis by lfDistance.
 void AdvanceZ(double lfDistance);
 /// This will move this matrix along its local X and Y axis by lfX and lfY respectively. Suitable for 2D objects
  void Advance(double lfX,double lfY);
 /// This will advance the object along its local X, Y and Z axis by lfX, lfY and lfZ.
 void Advance(double lfX,double lfY, double lfZ);

 /// Will Advance the object along its global axis by the distance of the doubles in the array lfDistance
 void GAdvance(double *lfDistance);
/// This will advance the object along the global X axis by lfX.
void GAdvanceX(double lfX);
/// This will advance the object along the global Y axis by lfX.
void GAdvanceY(double lfX);
/// This will advance the object along the global Z axis by lfX.
void GAdvanceZ(double lfX);
 /// This will move this matrix along its global X and Y axis by lfX and lfY respectively.
  void GAdvance(double lfX,double lfY);
/// This will advance the object along the global X, Y and Z axis by lfX, lfY and lfZ.
void GAdvance(double lfX,double lfY,double lfZ);

/// This will set the angle of rotation about this matrices X axis to lfAngle radians. Suitable for 2D objects.
  void Angle(double lfAngle);
/// This will rotate this matrix in the X axis through 0,0 by lfAngle radians. Suitable for 2D objects.
  void GRotateOrigin(double lfAngle);
/// This will rotate this matrix in the X axis through lfX,lfY by lfAngle radians. Suitable for 2D objects.
  void GRotate(double lfAngle,double lfX,double lfY);

///Will copy the rotation of the matrix lpRotation
void Rotation(double *lpRotation);
///Will copy the rotation of the matrix lpRotation
void Rotation(cDoubleMatrix4 *lpRotation);
///This will make this object have the same Rotation as the cDoubleMatrix4 lpOther.
void Rotation(cDoubleMatrix4 &lpOther);

 /// This will rotate the object around its local Z axis by lfAngle radians. Suitable for 2D objects
 void Rotate(double lfAngle);
/// This will rotate the object around its local X axis by lfAngle radians.
 void RotateX(double lfAngle);
/// This will rotate the object around its local Y axis by lfAngle radians.
 void RotateY(double lfAngle);
/// This will rotate the object around its local Z axis by lfAngle radians.
 void RotateZ(double lfAngle);

/// This will rotate the object around its global X axis by lfAngle radians.
 void GRotateX(double lfAngle);
/// This will rotate the object around its global X axis by lfAngle radians.
 void GRotateY(double lfAngle);
/// This will rotate the object around its global X axis by lfAngle radians.
 void GRotateZ(double lfAngle);

/// This will rotate the object around the global X axis at point lfX,lfY,lfZ by lfAngle radians.
 void GRotateX(double lfAngle,double lfX,double lfY,double lfZ);
/// This will rotate the object around the global Y axis at point lfX,lfY,lfZ by lfAngle radians.
 void GRotateY(double lfAngle,double lfX,double lfY,double lfZ);
/// This will rotate the object around the global Z axis at point lfX,lfY,lfZ by lfAngle radians.
 void GRotateZ(double lfAngle,double lfX,double lfY,double lfZ);

/// This will rotate the object around the global X axis at point 0,0,0 by lfAngle radians.
 void GRotateOriginX(double lfAngle);
/// This will rotate the object around the global Y axis at point 0,0,0 by lfAngle radians.
 void GRotateOriginY(double lfAngle);
/// This will rotate the object around the global Z axis at point 0,0,0 by lfAngle radians.
 void GRotateOriginZ(double lfAngle);

///This will make the current object look at the point lfPoint in Local Co-ordinates.
 void LookAt(double *lfPoint);
 ///This will make the current object look at the point lfPoint in Local Co-ordinates.
 void LookAt(cDoubleMatrix4 *lfPoint);
 ///This will make the current object look at the point lfPoint in Local Co-ordinates.
 void LookAt(cDoubleMatrix4 &lfPoint);
 ///This will make the current object look at the point lfPoint in Local Co-ordinates.
 void LookAt(double lfX,double lfY,double lfZ);
///This will make the current object look at the point lfVect in Local Co-ordinates.
 void LookAt(c3DVd lfVect);

///This will make the current object look in the direction lfVect in Local Co-ordinates.
 void LookVector(double *lfVect);
 ///This will make the current object look in the direction lfX,lfY,lfZ in Local Co-ordinates.
 void LookVector(double lfX,double lfY,double lfZ);
 ///This will make the current object look in the direction lfVect in Local Co-ordinates.
 void LookVector(c3DVd lfVect);


 ///This will give the angle this object must roll (about X Axis) to have the point on its ZY Plane.
 double RollToPointPitch(double *lfPoint);
 ///This will give the angle this object must roll (about X Axis) to have the point on its ZX Plane.
 double RollToPointYaw(double *lfPoint);
 ///This will give the angle this object must Yaw (about Y Axis) to be 'facing' the Local point lfPoint.
 double YawToPoint(double *lfPoint);
 ///This will give the angle this object must pitch (about Z Axis) to be 'facing' the Local point lfPoint.
 double PitchToPoint(double *lfPoint);

///This will give the angle between this matrices z axis and the vector from this matrix to the point lfPoint.
double AngleToPoint(double *lfPoint);
///This will return true if the angle between this matrices z axis and the vector from this matrix to the point lfPoint is less than lfAngle.
bool AngleToPointCheck(double *lfPoint,double lfAngle);


 ///This will give the angle this object must roll (about X Axis) to have the Vector lfVector on its ZY Plane.
 double RollToVectorPitch(double *lfVector);
 ///This will give the angle this object must roll (about X Axis) to have the Vector lfVector on its ZX Plane.
 double RollToVectorYaw(double *lfVector);
 ///This will give the angle this object must Yaw (about Y Axis) to be inline with the Local Vector lfVector.
 double YawToVector(double *lfVector);
 ///This will give the angle this object must pitch (about Z Axis) to be inline with the Local Vector lfVector.
 double PitchToVector(double *lfVector);

///This will give the angle between this matrices z axis and the vector lfVector.
double AngleToVector(double *lfVector);
///This will return true if the angle between this matrices z axis and the vector lfVector is less than lfAngle. Otherwise will return false.
bool AngleToVectorCheck(double *lfVector,double lfAngle);


 ///This will give the angle this object must roll (about X Axis) to have the point on its ZY Plane.
 double RollToPointPitch(c3DVd lfPoint);
 ///This will give the angle this object must roll (about X Axis) to have the point on its ZX Plane.
 double RollToPointYaw(c3DVd lfPoint);
 ///This will give the angle this object must Yaw (about Y Axis) to be 'facing' the Local point lfPoint.
 double YawToPoint(c3DVd lfPoint);
 ///This will give the angle this object must pitch (about Z Axis) to be 'facing' the Local point lfPoint.
 double PitchToPoint(c3DVd lfPoint);

///This will give the angle between this matrices z axis and the vector from this matrix to the point lfPoint.
double AngleToPoint(c3DVd lfPoint);
///This will return true if the angle between this matrices z axis and the vector from this matrix to the point lfPoint is less than lfAngle.
bool AngleToPointCheck(c3DVd lfPoint,double lfAngle);


 ///This will give the angle this object must roll (about X Axis) to have the Vector lfVector on its ZY Plane.
 double RollToVectorPitch(c3DVd lfVector);
 ///This will give the angle this object must roll (about X Axis) to have the Vector lfVector on its ZX Plane.
 double RollToVectorYaw(c3DVd lfVector);
 ///This will give the angle this object must Yaw (about Y Axis) to be inline with the Local Vector lfVector.
 double YawToVector(c3DVd lfVector);
 ///This will give the angle this object must pitch (about Z Axis) to be inline with the Local Vector lfVector.
 double PitchToVector(c3DVd lfVector);

///This will give the angle between this matrices z axis and the vector lfVector.
double AngleToVector(c3DVd lfVector);
///This will return true if the angle between this matrices z axis and the vector lfVector is less than lfAngle. Otherwise will return false.
bool AngleToVectorCheck(c3DVd lfVector,double lfAngle);

///This will return the objects Roll angle (angle between the Y Axis and the Local objects Identity YZ Plane)
double Roll();
///This will return the objects Yaw angle (angle between the Z Axis and the Local objects Identity YZ Plane)
double Yaw();
///This will return the objects Pitch angle (angle between the Z Axis and the Local objects Identity XZ Plane)
double Pitch();


  ///Makes this matrix Equal the cDoubleMatrix4 pointed to by lpOther
  void Equals(cDoubleMatrix4 *lpOther);
  ///Makes this matrix Equal the cDoubleMatrix4 lpOther
  void Equals(cDoubleMatrix4 lpOther);
  ///Makes this matrix Equal the cMatrix4 pointed to by lpOther
  void Equals(cMatrix4 *lpOther);
  ///Makes this matrix Equal the cMatrix4 lpOther
  void Equals(cMatrix4 lpOther);
  ///Makes this matrix Equal the 4x4 double matrix pointed to by lpOther
  void Equals(double *lpOther);


  /// This will scale the object by a factor of lfScale.
 void Resize(double lfScale);
/// This will scale the object along its local X axis by a factor of lfScale.
 void ResizeX(double lfScale);
/// This will scale the object along its local Y axis by a factor of lfScale.
 void ResizeY(double lfScale);
/// This will scale the object along its local Z axis by a factor of lfScale.
 void ResizeZ(double lfScale);

/// This will scale the object along its global X axis by a factor of lfScale.
 void GResizeX(double lfScale);
/// This will scale the object along its global Y axis by a factor of lfScale.
 void GResizeY(double lfScale);
/// This will scale the object along its global Z axis by a factor of lfScale.
 void GResizeZ(double lfScale);

 ///This will set the objects X Axis to the scale lfScale.
 void ScaleX(double lfScale);
 ///This will set the objects Y Axis to the scale lfScale.
 void ScaleY(double lfScale);
 ///This will set the objects Z Axis to the scale lfScale.
 void ScaleZ(double lfScale);

 ///This will get the objects X Axis scale.
 double ScaleX();
 ///This will get the objects Y Axis scale.
 double ScaleY();
 ///This will get the objects Z Axis scale.
 double ScaleZ();

 ///This will set the objects Global X Axis to the scale lfScale.
 void GScaleX(double lfScale);
 ///This will set the objects Global Y Axis to the scale lfScale.
 void GScaleY(double lfScale);
 ///This will set the objects Global Z Axis to the scale lfScale.
 void GScaleZ(double lfScale);

 ///This will get the objects Global X Axis scale.
 double GScaleX();
 ///This will get the objects Global Y Axis scale.
 double GScaleY();
 ///This will get the objects Global Z Axis scale.
 double GScaleZ();


/// This will return the distance between this matrix and the cDoubleMatrix4 pointed to by lpOther.
 double Distance(cDoubleMatrix4 &lpOther);
  /// This will return the distance between this matrix and the cDoubleMatrix4 pointed to by lpOther.
 double Distance(cDoubleMatrix4 *lpOther);
 /// This will return the distance between this matrix and the Global Position lpOther.
 double Distance(double *lpOther);
 /// This will return the distance between this matrix and the Global Position lpOther.
 double Distance(c3DVd lpOther);

/// This will return the square of the distance between this matrix and the cDoubleMatrix4 pointed to by lpOther.
double DistanceSq(cDoubleMatrix4 *lpOther);
/// This will return the square of the distance between this matrix and the cDoubleMatrix4 pointed to by lpOther.
double DistanceSq(cDoubleMatrix4 lpOther);
/// This will return the square of the distance between this matrix and the Global Position lpOther.
double DistanceSq(double *lpOther);
/// This will return the square of the distance between this matrix and the Global Position lpOther.
double DistanceSq(c3DVd lpOther);

///This will return the distance between this matrix and the origin
double Distance();
///This will return the square of the distance between this matrix and the origin
double DistanceSq();

 /// This will return the double in position liPos in mpData.
 double &operator[](uint16 liPos);
/// This will return the double in position [liColumn,liRow] in mpData.
 double &operator()(uint16 liColumn,uint16 liRow);

// This will multiply every double in this objects matrix by lVal.
 cDoubleMatrix4 operator*(double &lVal);
// This will multiply every double in this objects matrix by lVal.
cDoubleMatrix4 operator*(const double lVal);
// This will this Matrix by the 4x4 array lVal. This is the same as multiplying two matrices.
 cDoubleMatrix4 operator*(double *lVal);

/* /// This will multiply this objects matrix by the matrix pointed to by lVal. Returns This.lVal .
 cDoubleMatrix4 &operator*(cDoubleMatrix4 &lVal);*/
// This will multiply this objects matrix by the matrix lVal. Returns This.lVal .
cDoubleMatrix4 *operator*(cDoubleMatrix4 *lVal);
// This will multiply this objects matrix by the matrix lVal. Returns This.lVal .
cDoubleMatrix4 operator*(cDoubleMatrix4 lVal);
// This will divide every double in this objects matrix by lVal.
 cDoubleMatrix4 operator/(double &lVal);
// This will divide every double in this objects matrix by lVal.
cDoubleMatrix4 operator/(const double lVal);

// This will add lVal to every double in this objects matrix.
 cDoubleMatrix4 operator+(double &lVal);
// This will add lVal to every double in this objects matrix.
 cDoubleMatrix4 operator+(const double lVal);
// This will add this matrix and the matrix lVal.
 cDoubleMatrix4 operator+(cDoubleMatrix4 &lVal);

// This will deduct lVal from every double in this objects matrix.
 cDoubleMatrix4 operator-(double &lVal);
// This will deduct lVal from every double in this objects matrix.
 cDoubleMatrix4 operator-(const double lVal);

// This will subtract the matrix lVal from this matrix.
cDoubleMatrix4 operator-(cDoubleMatrix4 &lVal);




// This will equate every double in mpData to lVal.
 double operator=(double &lVal);
// This will equate every double in mpData to lVal.
double operator=(const double lVal);
// This will equate the data in mpData to the data in lVal.mpData.
// cDoubleMatrix4 &operator=(cDoubleMatrix4 &lVal);
// This will equate the data in mpData to the data in lVal->mpData.
cDoubleMatrix4 *operator=(cDoubleMatrix4 *lVal);
// This will equate the data in mpData to the data in lVal.mpData.
cDoubleMatrix4 operator=(cDoubleMatrix4 lVal);
cDoubleMatrix4 operator=(cMatrix4 *lVal);
// This will equate the data in mpData to the data in lVal.mpData.
cDoubleMatrix4 operator=(cMatrix4 lVal);

double *operator=(double *lVal);








 /// This will set the current matrix to operate as if it is a 2D object.
  void Set2D();
/// This will set the current matrix to operate as if it is a 3D object.
  void Set3D();

// This will display the current matrix Textually
  void Display();


/// This will create a cDoubleMatrix4 object and will Set the matrix to an Identity Matrix;.
 cDoubleMatrix4();

 /// This will return the determinant of this objects matrix.
 double Determinant();

 ///Returns this Matrix. For objects which have inherited cDoubleMatrix4.
 cDoubleMatrix4 &ThisMatrix();

 ///Returns a pointer to this matrix
 cDoubleMatrix4 *ThisMatrixPointer();

 ///This will calculate the inversion matrix for this matrix.
 cDoubleMatrix4 InversionMatrix();
 /// This will return the transpose of this objects matrix.
 cDoubleMatrix4 Transpose();

 /// This will restore this objects matrix to an identity matrix.
 void Identity();
 /// This will set every double in this objects matrix to be equal to zero.
 void Zero();
 /// This will reset the objects Local Rotations.
 void ResetRotations();
 ///This will reset the objects Local Position.
 void ResetPosition();
 ///This will multiply this matrix by the cDoubleMatrix4 Other.
 void Multiply(cDoubleMatrix4 &Other);
 ///This will multiply this matrix by the cDoubleMatrix4 Other.
 void Multiply(cDoubleMatrix4 *Other);

 ///This will multiply this matrix by the 4x4 double Matrix pointed to by Other.
 void Multiply(double *Other);

 /// This will multiply this matrix by the 4 dimensional Vector lfVector.
 c4DVd MultiplyVector(double *lfVector);
 /// This will multiply this matrix by the 4 dimensional Vector lfVector.
 c4DVd MultiplyVector(c4DVd lfVector);
 /// This will multiply this matrix by the 4 dimensional Vector lfVector.
 c4DVd Multiply(c4DVd lfVector);

 /// This will multiply this matrices angles by the 3 dimensional Vector lfVector.
 c3DVd RotateVectorByAngles(double *lfVector);
 /// This will multiply this matrices angles by the 3 dimensional Vector lfVector.
 c3DVd RotateVectorByAngles(c3DVd lfVector);
 /// This will multiply this matrices angles by the 3 dimensional Vector lfVector.
 c3DVd Multiply(c3DVd lfVector);

 /// This will multiply this matrices position by the 3 dimensional Vector lfVector.
 c3DVd MultiplyVectorPosition(double *lfVector);
 /// This will multiply this matrices position by the 3 dimensional Vector lfVector.
 c3DVd MultiplyVectorPosition(c3DVd lfVector);

  void InvSign();

   bool Is3D();
};

#endif
