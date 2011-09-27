#ifndef __WTCRENDEROBJECT_H__
#define __WTCRENDEROBJECT_H__

class cRenderNode;
/**
* \brief This class contains the base code for all renderable objects. Any renderable object should inherit this class.
* \param lpNode lpNode is not required, but will add the renderable object to the cRenderNode pointed to by lpNode.
* This class should be inherited by any renderable object. If it is handed 
* no parameters then it will add itself to cCamera::mpRenderList, which is owned 
* by cCamera. If you wish to produce a scene graph, the new renderable object can 
* be handed a pointer to a cRenderNode. Any translations applied to lpNode will 
* change the co-ordinate system for this renderable object.
* \code
	cRenderNode mpNode=new cRenderNode;
	cTexturedModel mpObject=new cTexturedModel(mpNode);
	mpNode.LAdvance(1.0f,0.0f,0.0f);
	mpObject.LAdvance(1.0f,0.0f,0.0f);
* \endcode
* After this code mpObject will be at 2.0f,0.0f,0.0. 
* This Function should only be used for Creating New Renderable Object Types. It should be virtual.
*/
class cRenderObject : public vRenderObject
{
 ///This pointer points to the cRenderNode which owns this cRenderObject.
 cRenderNode *mpRenderer;
 ///This pointer points to the cLinkedNode which owns this cRenderObject. (cLinkedNode fors a linked list owned by mpRenderer.
 cLinkedNode<vRenderObject> *mpNode;

 ///A Pointer to the cCollisionObject linked to this program.
 cCollisionObject *mpCollisionObject;

 virtual void Initialise();

protected:
  /// A Pointer to the cRenderPointer Object for this Renderable Object. Used when cPainter is enabled.
 cRenderPointer *mpPainterData;
 /// A Pointer to the position in the list that the cRenderPointer is at in cPainter.
 cRenderPointer **mpSlot;

 	/// The current shader that this program will use.
	vShaderProgram *mpShader;
 
public:

	/// Will set the shader this object will use.
	void Shader(vShaderProgram *lpShader);
	/// Will return a pointer to the Shader Program that is currently bound to this model.
	vShaderProgram *Shader();

 /// Constructor for cRenderObject. Creates a new render object and adds itself to cCamera::mpRenderList.
 cRenderObject();
 /// Constructor for cRenderObject. Creates a new render object and adds itself to lpNode.
 cRenderObject(cRenderNode *lpNode);
 // Destructor for cRenderObject.
 ~cRenderObject();

 ///This will set the Collision Object that is linked to this renderable object. This should be called automatically when a cCollisionObject is created.
 void LinkCollisionObject(cCollisionObject *lpObj);
 
 /// Returns the cRenderNode which owns this renderable process.
 cRenderNode *Renderer();
 

  /// virtual functions to allow polymorphism. see cCamera::RenderPainter();
  virtual void RenderPainter(){};
  /// virtual function to allow polymorphism. see cCamera::RenderPainter();
  virtual void RenderPainter(uint8 liLevel)=0;
  /// virtual function to allow polymorphism. see cCamera::RenderToPainter();
  virtual void RenderToPainter()=0;
  /// virtual function to allow polymorphiss. see cCamera::Render();
  virtual void Render()=0;

 /// Will remove this object from the render list owned by mpRenderer.
  void Delete();/// Will return a pointer to the Shader Program that is currently bound to this model.
 /**
 * \brief Will move the current renderable object from the current cRenderNode to lpNode.
 * \param lpNode The cRenderNode which will now own this renderable object.
 * \return This function returns the new cLinkedNode which now owns this renderable object.
 */
 cLinkedNode<vRenderObject> *SetRenderNode(cRenderNode *lpNode);
  
 /// virtual function for polymorphism. Should return the texture ID of this renderable objects Texture.
 unsigned int TextureNumber(){return 0;}
 
  ///This will contain additional functions to perform when an object renders.
  void AdditionalRenderFunctions();

  //This contains any Code to be run for this object in the event of its death (as deletion of the object may be delayed after death).
  virtual void AdditionalKillFunctionality();
  //This contains any Code to be run when the object is sent to sleep.
  virtual void AdditionalSleepFunctionality();
  //This contains any Code to be run when the object is woken up.
  virtual void AdditionalWakeFunctionality();
  ///This function will update the object cache. For consistency all Renderable Objects must update the cache as they are rendered. This will be the global position of the object and is used to get consistent positions throughout a frame for collision detection.
  void UpdateCache();  

  /// This will return the Local position of the selected object.
  float *GetPos();
  /// This will return the global position of the object as rendered at the end of last frame. Note, this will contain the camera matrix.
  float *GetGlobalPos();
};

#endif
