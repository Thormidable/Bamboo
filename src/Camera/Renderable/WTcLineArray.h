#ifndef __WTCLINEARRAY_H__
#define __WTCLINEARRAY_H__
/**
* \brief A group of renderable Line object.
*/
class cLineArray :public cRenderObject
{
 cLineArrayData *mpData;

public:
 /// cLineArray constructor
 cLineArray();

 /// cLineArray constructor. Will be owned by lpRenderer.
 cLineArray(vRenderNode *lpRenderer);
/// cLineArray constructor. Will be owned by the cRenderNode of the cCamera lpCamera.
 cLineArray(cCamera *lpCamera);

 // Will render this object to the cPainter render list.
  void RenderPainter();
  void Data(cLineArrayData *lpData);

};

#endif
