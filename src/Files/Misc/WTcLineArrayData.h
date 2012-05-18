#ifndef __WTCLINEARRAYDATA_H__
#define __WTCLINEARRAYDATA_H__
/**
* \brief A group of renderable Line object.
*/
class cLineArrayData : public cLimitedList<c3DVf>
{
 GLuint miBufferID;
 bool lbBuffer;

public:
 /// cLineArrayData constructor
 cLineArrayData();

 ~cLineArrayData();

 // Will render this object to the cPainter render list.
  void RenderLines();

     ///Will Add a new Line between last point in array and the point lfPoint.
     void Add(c3DVf lfPoint);
     ///Will Add a new Line between last point in array and the point lfPoint.
     void Add(float *lfPoint);

    void Buffer();

};

#endif
