#ifndef __WTCBILLBOARD_H__
#define __WTCBILLBOARD_H__

/**
* \brief A Renderable object for rendering Textured Billboards. (This uses the opengl type points).
*/
class cBillBoard :public cRenderObject
{

public:
 /// cBillBoard constructor
 cBillBoard();
 /// cBillBoard constructor. Will be owned by lpRenderer.
 cBillBoard(vRenderNode *lpRenderer);
 /// cBillBoard constructor. Will be owned by the cRenderNode of cCamera lpCamera.
 cBillBoard(cCamera *lpCamera);

 // Will render this object to the cPainter render list.
  void RenderPainter();

};

#endif
