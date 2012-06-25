#ifndef __WTCLINE_H__
#define __WTCLINE_H__
/**
* \brief A standard renderable Line object.
*/
class cLine :public cRenderObject
{

 float mfPosition[3];
 float mfEnd[3];
 float mfVector[3];
 float mfWidth;

public:
 /// cLine constructor
 cLine();
 /// cLine constructor. Will be owned by lpRenderer.
 cLine(vRenderNode *lpRenderer);
/// cLine constructor. Will be owned by the cRenderNode of the cCamera lpCamera.
 cLine(cCamera *lpCamera);


 // Will render this object to the cPainter render list.
  void RenderPainter();

      ///Will return a pointer to the position of this line object (XYZ).
      float *Position();
      ///Will set the position of this object to the float array pointed to by lfPos. Expects 3 floats (XYZ).
      void Position(float* lfPos);
      ///Will set the position of this object to the values specified (XYZ).
      void Position(float lfX,float lfY,float lfZ=0.0f);

      ///Will return a pointer to the vector of this line object (XYZ).
      float *Vector();
      ///Will set the vector of this object to the float array pointed to by lfPos. Expects 3 floats (XYZ).
      void Vector(float* lfPos);
      ///Will set the vector of this object to the values specified (XYZ).
      void Vector(float lfX,float lfY,float lfZ=0.0f);

	  ///Will set the width for the line
	  void Width(float lfWidth);
	  ///Will return the lines width
	  float Width();

    float GetSize();
    double GetSizeSq();
};

#endif
