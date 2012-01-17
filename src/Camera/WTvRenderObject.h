#ifndef __WTVRENDEROBJECT_H__
#define __WTVRENDEROBJECT_H__

class cRenderOwner;
class cCollisionObject;
class vMesh;
class cRenderNode;
class cCollisionObject;
class vRenderNode;

class vRenderObject : virtual public cMatrix4, virtual public cSignal
{
protected:

public:
  ///Matrix which Stores the final global position matrix of the object from the last frame. This is used to make collisions consistent and for finding object Global Positions. Note the Camera Matrix will be included in this.
	cMatrix4 mmCache;
	cMatrix4 mmTotalCache;
 // Destructor. Does Nothing but be virtual.
 virtual ~vRenderObject(){};
 /// Returns the cRenderNode which owns this object.
 virtual vRenderNode *Renderer()=0;
 /// Links The cCollisionObject lpObj to this Renderable Object.
 virtual void LinkCollisionObject(cCollisionObject *lpObj){(void) lpObj;};


 /// Renders this object from the cPainter render list to the screen.
virtual void RenderPainter()=0;
virtual void RenderToPainter()=0;


///This will store any additional functions to be performed as the object is rendered. Updating Caches, etc.
  virtual void AdditionalRenderFunctions(){};

 ///This will update the cache matrix.
 virtual void UpdateCache()=0;

 /// This will return the local position of the selected object.
  virtual float *GetPos()=0;
  /// This will return the global position of the object as rendered at the end of last frame. Note, this will contain the camera matrix.
  virtual float *GetCachedGlobalMatrix()=0;

 virtual cVariableStore *Variables()=0;

 virtual void Transparency(bool lbTrans){(void)lbTrans;};
 virtual bool Transparency(){return 0;};

/**
* \brief This will calculate on the fly the global position matrix of the object. It does not contain Cameras Position Matrix.
* This will actually traverse the render tree and calculate the Global position matrix. This is pretty slow and best avoided if possible.
* The function cRenderObject::GetCachedGlobal() is very fast and will return the final global position matrix of the object when it was last rendered.
**/
 virtual cMatrix4 CalculateGlobalMatrix();

 };

 class vRenderNode : public vRenderObject
{
protected:
	// This is the vRenderNode which owns this renderable object.
   vRenderNode *mpRenderer;
    // cLinkedNode which owns this renderable object.
 cRenderOwner mcOwnerNode;
public:
    	/// Returns the cRenderNode which owns this object.
       vRenderNode *Renderer();

       //virtual void Remove(cRenderOwner lpOld)=0;

       virtual cRenderOwner Add(vRenderObject *lpNew)=0;

	   virtual void RenderPainter();
	   virtual void RenderToPainter()=0;
	   virtual void UpdateCache();
       virtual float* GetPos();
       virtual float* GetCachedGlobalMatrix();
       virtual cVariableStore* Variables();

       void AdditionalKillFunctionality();

};

#endif
