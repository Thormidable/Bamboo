#ifndef __WTCLINEARRAYDATA_H__
#define __WTCLINEARRAYDATA_H__
/**
* \brief A data for use by cLineArray objects.
* This will draw a line from the first point added to the last point added to the class. It will draw a straight line from each point to the next point to travel from the first point to the last point.
* Inherits from cLimitedList. List can be modified using the cLimitedList functions.
*/
class cLineArrayData : public cLimitedList<c3DVf>
{
protected:
 GLuint miBufferID;
 bool lbBuffer;

public:
 /// cLineArrayData constructor
 cLineArrayData();
 cLineArrayData(cLineArrayData *lpOther);

 ~cLineArrayData();

 // Will render this object to the cPainter render list.
  void RenderLines();

     ///Will Add a new Line between last point in array and the point lfPoint.
     void Add(c3DVf lfPoint);
     ///Will Add a new Line between last point in array and the point lfPoint.
     void Add(float *lfPoint);

    void Buffer();

    void Equals(cLineArrayData *lpOther);
    void operator=(cLineArrayData *lpOther);
    void operator=(cLineArrayData &lpOther);

};

#endif
