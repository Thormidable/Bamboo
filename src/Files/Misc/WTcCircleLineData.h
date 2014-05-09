#ifndef __WTCCIRCLELINEDATA_H__
#define __WTCCIRCLELINEDATA_H__
/**
* \brief A Data object for storing Circle Line objects.
* Inherits from cLineArrayData and is passed to cLineArrays to render to screen.
* This includes functionality for generating Circles.
*/
class cCircleLineData : public cLineArrayData
{

public:
 // cLineArrayData constructor
 cCircleLineData(float lfRadius,uint16 miSegments=100);
 cCircleLineData(cCircleLineData *lpOther);

 ~cCircleLineData();

  void GenerateCircle(float lfRadius,uint16 miSegments=100);
  void Radius(float lfSize);

};

#endif
