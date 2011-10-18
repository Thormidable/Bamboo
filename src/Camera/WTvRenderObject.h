#ifndef __WTVRENDEROBJECT_H__
#define __WTVRENDEROBJECT_H__


class cCollisionObject;
class vMesh;
class cRenderNode;
class cCollisionObject;
/// virtual function for producing renderable objects. see cRenderObject.
class vRenderObject : virtual public cMatrix4, virtual public cSignal
{

	
	
public:
  ///Matrix which Stores the final global position matrix of the object from the last frame. This is used to make collisions consistent and for finding object Global Positions. Note the Camera MAtrix will be included in this.
	cMatrix4 mmCache;
 // Destructor. Does Nothing but be virtual.
 virtual ~vRenderObject(){};
 /// Returns the cRenderNode which owns this object.
 virtual cRenderNode *Renderer()=0;
 /// Links The cCollisionObject lpObj to this Renderable Object.
 virtual void LinkCollisionObject(cCollisionObject *lpObj){(void) lpObj;};
 

 /// Renders this object from the cPainter render list to the screen.
virtual void RenderPainter()=0;

 /// Renders this object to the cPainter render list.
 virtual void RenderToPainter()=0;

 /// Renders this object to the screen.
 virtual void Render()=0;


///This will store any additional functions to be performed as the object is rendered. Updating Caches, etc.
  virtual void AdditionalRenderFunctions(){};

 ///This will update the cache matrix.
 virtual void UpdateCache()=0;

 /// This will return the position of the selected object.
  virtual float *GetPos()=0;
  /// This will return the global position of the object as rendered at the end of last frame. Note, this will contain the camera matrix.
  virtual float *GetGlobalPos()=0;

  
  virtual cVariableStore *Variables()=0;

};

#endif
