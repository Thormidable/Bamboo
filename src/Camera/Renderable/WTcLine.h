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
 cRGBA mfColor;

 uint32 CAN_MAKE_THIS_MORE_EFFICIENT_BY_USING_CMATRIX_DATA_FOR_STORING_VALUES;
 /*
  * float *mfPosition;
  * float *mfEnd;
  * float *mfVector;
  * float *mfColor;
  */

public:
 /// cLine constructor
 cLine();
 /// cLine constructor. Will be owned by lpRenderer.
 cLine(cRenderNode *lpRenderer);



 // Will render this object to the cPainter render list.
  void RenderPainter(uint8 liLevel);
 // Will render this object from the cPainter render list to the screen.
  void RenderToPainter();

      ///Will return a pointer to the color of this line (RGBA).
      cRGBA* Color();
      ///Will Set the color of this object to the float array pointed to by lfColor. Expects 4 floats (RGBA).
      void Color(cRGBA &lpColor);
	  ///See cLine::Color(cRGBA &lpColor).
      void Color(cRGBA *lpColor);
	  ///See cLine::Color(cRGBA &lpColor).
      void Color(cRGB &lpColor);
	  ///See cLine::Color(cRGBA &lpColor).
      void Color(cRGB *lpColor);
	  ///See cLine::Color(cRGBA &lpColor).
      void Color(float *lpColor);
	  ///See cLine::Color(cRGBA &lpColor).
      void Color(float lpR,float lpG,float lpB,float lpA=1.0);



      ///Will return a pointer to the position of this line object (XYZ).
      float *Position();
      ///Will set the position of this object to the float array pointed to by lfPos. Expects 3 floats (XYZ).
      void Position(float* lfPos);
      ///Will set the position of this object to the values specified (XYZ).
      void Position(float lfX,float lfY,float lfZ);

      ///Will return a pointer to the vector of this line object (XYZ).
      float *Vector();
      ///Will set the vector of this object to the float array pointed to by lfPos. Expects 3 floats (XYZ).
      void Vector(float* lfPos);
      ///Will set the vector of this object to the values specified (XYZ).
      void Vector(float lfX,float lfY,float lfZ);

};

#endif
