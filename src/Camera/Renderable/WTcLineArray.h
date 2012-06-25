#ifndef __WTCLINEARRAY_H__
#define __WTCLINEARRAY_H__
/**
* \brief A renderable Line object, which is more than a single straight line.
* These objects use cLineArrayData objects to supply their data.
* The data is composed of lines joining together a series of points.
*/
class cLineArray :public cRenderObject
{
 cLineArrayData *mpData;

 float mfWidth;

public:
 /// cLineArray constructor
 cLineArray();

 /// cLineArray constructor. Will be owned by lpRenderer.
 cLineArray(vRenderNode *lpRenderer);
/// cLineArray constructor. Will be owned by the cRenderNode of the cCamera lpCamera.
 cLineArray(cCamera *lpCamera);

 // Will render this object to the cPainter render list.
  void RenderPainter();
  ///Will set the cLineArrayData object this will for it's data source.
  void Data(cLineArrayData *lpData);

	  ///Will set the width for the line
	  void Width(float lfWidth);
	  ///Will return the lines width
	  float Width();


};

#endif
