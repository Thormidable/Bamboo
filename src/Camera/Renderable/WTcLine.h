#ifndef __WTCLINE_H__
#define __WTCLINE_H__
/**
* \brief A standard renderable Line object.
*/
class cLine :public cRenderObject
{
protected:
 c3DVf mfPosition;
 c3DVf mfEnd;
 c3DVf mfVector;
 float mfWidth;

public:
 /// cLine constructor
 cLine(bool lbNoTex=1);
 /// cLine constructor. Will be owned by lpRenderer.
 cLine(vRenderNode *lpRenderer,bool lbNoTex=1);
/// cLine constructor. Will be owned by the cRenderNode of the cCamera lpCamera.
 cLine(cCamera *lpCamera,bool lbNoTex=1);


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

      ///Will return a pointer to the end point of this line object (XYZ).
      float *EndPoint();
      ///Will set the end point of this object to the float array pointed to by lfPos. Expects 3 floats (XYZ).
      void EndPoint(float* lfPos);
      ///Will set the end point of this object to the values specified (XYZ).
      void EndPoint(float lfX,float lfY,float lfZ=0.0f);


	  ///Will set the width for the line
	  void Width(float lfWidth);
	  ///Will return the lines width
	  float Width();

    float GetSize();
    double GetSizeSq();
};

/**
 * \brief cRenderObject Type for rendering rectangles in the X,Y plane.
 * Will start with corners at T:1.0f B:0.0f L:0.0f R:0.0f. Order is TBLR. Designed primarilarly for use as a 2D object.
*/
class cLineRectangle :public cRenderObject
{

 c4DVf mvEdges;
 float mfWidth;

public:
 /// cLineRectangle constructor.
 cLineRectangle();
 /// cLineRectangle constructor making this owned by lpRenderer.
 cLineRectangle(vRenderNode *lpRenderer);
/// cLineRectangle constructor making this owned by the root vRenderNode of lpCamera.
 cLineRectangle(cCamera *lpCamera);

 // Will render this object to the cPainter render list.
  void RenderPainter();

  /// Will set the position of the four edges in order TBLR.
  void Edges(c4DVf lvTBLR);
  /// Will set the position of the Top Left Edges and the Bottom Right Edges.
  void Edges(c2DVf lvTL,c2DVf lvBR);

  /// Will return the Edge positions for this object.
  c4DVf Edges();

  /// Will set the position of the Top edge.
  void Top(float lfTop);
  /// Will set the position of the Bottom edge.
  void Bottom(float lfBottom);
  /// Will set the position of the Right edge.
  void Right(float lfRight);
  /// Will set the position of the Left edge.
  void Left(float lfLeft);

  /// Will return the Top Edge position for this object.
  float Top();
  /// Will return the Bottom Edge position for this object.
  float Bottom();
  /// Will return the Right Edge position for this object.
  float Right();
  /// Will return the Left Edge position for this object.
  float Left();

  /// Will return the Line width this will use (in pixels)
  float Width();
  /// Will set the Line width this will use (in pixels).
  void Width(float lfWidth);
};

#endif
