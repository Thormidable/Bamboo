#ifndef __WTVRENDEROBJECT_H__
#define __WTVRENDEROBJECT_H__
class cCamera;
class cRenderOwner;
class cCollisionObject;
class vMesh;
class cRenderNode;
class cCollisionObject;
class vRenderNode;
class cViewport;

class vRenderObject : virtual public cMatrix4, virtual public cSignal
{
protected:
//This pointer points to the cLinkedNode which owns this cRenderObject. (cLinkedNode fors a linked list owned by mpRenderer.
 cRenderOwner mcOwnerNode;

 cCamera *mpCamera;

   //A Pointer to the cCollisionObject linked to this program.
 cCollisionObject *mpCollisionObject;

 cProcess *mpProcess;

public:

 //This pointer points to the cRenderNode which owns this cRenderObject.
 vRenderNode *mpRenderer;

  ///Matrix which Stores the final global position matrix of the object from the last frame. This is used to make collisions consistent and for finding object Global Positions. Note the Camera Matrix will be included in this.
	cMatrix4 mmCache;
	cMatrix4 mmTotalCache;
  vRenderObject();

  virtual ~vRenderObject(){};

 /// Returns the cRenderNode which owns this object.
 virtual vRenderNode *Renderer();

 /// Links The cCollisionObject lpObj to this Renderable Object.
 virtual void LinkCollisionObject(cCollisionObject *lpObj);

 virtual void RecalculateTotalMatrix()=0;
 virtual void CalculateMatrices()=0;

 /// Renders this object from the cPainter render list to the screen.
virtual void RenderPainter()=0;
virtual void RenderToPainter()=0;


///This will store any additional functions to be performed as the object is rendered. Updating Caches, etc.
  virtual void AdditionalRenderFunctions(){};

 ///This will update the cache matrix.
 virtual void UpdateCache();

 /// This will return the local position of the selected object.
  virtual float *GetPos();
  /**
  * \brief This will return the global position of the object as rendered at the end of last frame.
  * This will return the cached Global position matrix as it was at the end of the last frame.
  * This will only be updated when rendering occurs. For a 'current' global matrix the function cCameraMatrix4::CalculateGlobalMatrix() will actually calculate the current matrix. However it is very slow.
  **/
  virtual float *GetCachedGlobalMatrix();

 virtual cVariableStore *Variables()=0;

 virtual void Transparency(uint8 lbTrans){(void)lbTrans;};
 virtual uint8 Transparency(){return 0;};

 virtual void KillAll()=0;

 /**
 * \brief Will move the current renderable object from the current cRenderNode to lpNode.
 * \param lpNode The cRenderNode which will now own this renderable object.
 * \return This function returns the new cLinkedNode which now owns this renderable object.
 */
 cRenderOwner &SetRenderNode(vRenderNode *lpNode);

/**
* \brief This will calculate on the fly the global position matrix of the object. It does not contain Cameras Position Matrix.
* This will actually traverse the render tree and calculate the Global position matrix. This is pretty slow and best avoided if possible.
* The function cRenderObject::GetCachedGlobal() is very fast and will return the final global position matrix of the object when it was last rendered.
**/
 virtual cMatrix4 *CalculateGlobalMatrix();

 ///This will return to the cCamera Object which owns the tree containing this object.
cCamera *Camera();

#if WT_FULL_VERSION_BAMBOO
		///This will return a c2DVf vector with this objects Screen coordinates for the default camera view.
		c3DVf GetScreenPosition();
		///This will return a float with this objects Screen X coordinate for the default camera view.
		float GetScreenX();
		///This will return a float with this objects Screen Y coordinate for the default camera view.
		float GetScreenY();

		///This will return a c2DVf vector with this objects Screen coordinates for the viewport lpView. This does not check if the viewport is associated with the cCamera object which owns the tree which contains this object.
		c3DVf GetScreenPosition(cViewport *lpView);
		///This will return a float with this objects Screen X coordinate for the viewport lpView. This does not check if the viewport is associated with the cCamera object which owns the tree which contains this object.
		float GetScreenX(cViewport *lpView);
		///This will return a float with this objects Screen X coordinate for the viewport lpView. This does not check if the viewport is associated with the cCamera object which owns the tree which contains this object.
		float GetScreenY(cViewport *lpView);

#endif

		void Renderer(vRenderNode *lpNode);

		cRenderOwner RenderOwner();
		void RenderOwner(cRenderOwner lcNew);

		void Process(cProcess *lpProcess);
		cProcess *Process();

		virtual float GetSize();
		virtual double GetSizeSq();

		///This will signal all objects with processes above this Node in the tree, with the function UserSignal()
		virtual void TreeProcessUserSignal(SIGNAL lsSignal,void *lpData){(void) lsSignal; (void) lpData;};

		///This will signal all objects with processes above this Node in the tree, with the function Signal()
		virtual void TreeProcessSignal(SIGNAL lsSignal){(void) lsSignal; };


		virtual void TreeSignal(SIGNAL lsSignal){Signal(lsSignal);};

        c3DVf FindRelativeCoord(c3DVf GlobalPos);
 };

 class vRenderNode : public vRenderObject
{
protected:


public:


       virtual cRenderOwner Add(vRenderObject *lpNew)=0;

        virtual void Delete(cRenderOwner lpOwner)=0;

	   virtual void RenderPainter();
	   virtual void RenderToPainter()=0;
	   //virtual void UpdateCache();
       virtual cVariableStore* Variables();
	   virtual void RecalculateTotalMatrix()=0;
	   virtual void CalculateMatrices()=0;


       void Stop();
       void OnWake();
       void OnSleep();

         ~vRenderNode();
        virtual void StartKillAll()=0;

		virtual cRenderOwner MoveItem(vRenderObject *lpObj,vRenderNode *lpRenderer)=0;
		virtual cRenderOwner MoveItem(vRenderObject *lpObj);

		virtual void MoveAll(vRenderNode *lpRender)=0;

		virtual vRenderObject *FindStart()=0;
		virtual vRenderObject *FindNext()=0;
		virtual bool ContainsItems()=0;

		///This will return a pointer to the first Node above the renderlist for this tree.
		vRenderNode *GetBaseOfTree();

		vRenderNode();
		vRenderNode(cCamera *lpCamera);
		vRenderNode(vRenderNode *lpRenderer);
		vRenderNode(bool lbToplevel);
		vRenderNode(bool lbTopLevel,cCamera *lpCamera);


};

#endif
