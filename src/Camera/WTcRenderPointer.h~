#ifndef __WTCRENDERPOINTER_H__
#define __WTCRENDERPOINTER_H__

/// This class is a temporary store for a cRenderObjects data. This is the complete render matrix and all other data required to render the object.
/**
 * \brief This is a storage class for the cPainter class.
 * It stores all the relevant data about a Renderable Object to allow it to be processed by cPainter.

 **/
class cRenderPointer
{
protected:
  cRenderObject  *mpObject;
  uint32         miDist;
  psize mpTexture;
  bool           mbAlpha;
  psize mpShader;
  cShaderProgram *ShaderPoint;
  bool mbReRender;

public:
	cRenderPointer();
	cRenderPointer operator=(cRenderPointer lcOther);

	///Will Set the cRenderObject that this will link to.
void SetObject(cRenderObject *lpObject);
///This will set the shader to be used by the object.
void SetShader(cShaderProgram *lpShader);
///This will set the Alpha of the object.
void SetAlpha(bool lbAlpha);
///This will all the user to set some / all of the parameters for this object.
void SetAll(cRenderObject *lpObject,cShaderProgram *lpShader=0,bool lbAlpha=0);
///This tells cPainter that this object will require rendering in the painter algorithm to allow it to be displayed on the screen.
void RenderAgain();

void UpdateTexture(uint8 liTexSlot);
 friend class cPainter;

};



#endif
