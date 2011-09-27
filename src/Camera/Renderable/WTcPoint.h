#ifndef __WTCPOINT_H__
#define __WTCPOINT_H__
/**
* \brief A Renderable object for rendering single points.
*/
class cPoint :public cRenderObject
{
 float mfColor[4];
 float mfPointSize;

public:
 /// cPoint constructor
 cPoint();
 /// cPoint constructor. Will be owned by lpRenderer.
 cPoint(cRenderNode *lpRenderer);
 
 // Will render this object to the cPainter render list.
  void RenderPainter(uint8 liLevel);
 // Will render this object from the cPainter render list to the screen.
  void RenderToPainter();
 // Will render this object to the screen.
  void Render();

      ///Will return the color of this point object.
      float* Color();
      ///Will set the color of this point object. Expects 4 floats (RGBA).
      void Color(float* lfColor);
      ///Will set the color of this point object. (RGBA).
      void Color(float lfR,float lfG,float lfB,float lfA);
      ///Will return the size of this point in pixels (Distance does not affect size without using an appropriate cShaderProgram).
      float PointSize(){return mfPointSize;};
      ///Will set the size of this point in pixels.
      void PointSize(float lfPointSize);
};

#endif
