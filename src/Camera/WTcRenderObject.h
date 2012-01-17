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
	cModel mpObject=new cModel(mpNode);
	mpNode.Advance(1.0f,0.0f,0.0f);
	mpObject.Advance(1.0f,0.0f,0.0f);
* \endcode
* After this code mpObject will be at 2.0f,0.0f,0.0.
* This Function should only be used for Creating New Renderable Object Types. It should be virtual.
*/
class cRenderObject : public vRenderObject, public cTextureStack
{

 //This pointer points to the cRenderNode which owns this cRenderObject.
 vRenderNode *mpRenderer;
 //This pointer points to the cLinkedNode which owns this cRenderObject. (cLinkedNode fors a linked list owned by mpRenderer.
 cRenderOwner mcOwnerNode;

 //A Pointer to the cCollisionObject linked to this program.
 cCollisionObject *mpCollisionObject;


 virtual void Initialise();

 bool mbAlpha;
 bool mbLighting;



protected:


void SetPainterVariables();
  // A Pointer to the cRenderPointer Object for this Renderable Object. Used when cPainter is enabled.
 cRenderPointer *mpPainterData;
 // A Pointer to the position in the list that the cRenderPointer is at in cPainter.
 cRenderPointer **mpSlot;


public:

	/// Will set the shader this object will use.
	void Shader(cShaderProgram *lpShader);
	/// Will return a pointer to the Shader Program that is currently bound to this model.
	cShaderProgram *Shader();

 /// Constructor for cRenderObject. Creates a new render object and adds itself to cCamera::mpRenderList.
 cRenderObject();
 /// Constructor for cRenderObject. Creates a new render object and adds itself to lpNode.
 cRenderObject(vRenderNode *lpNode);
 /// Constructor for cRenderObject. Creates a new render object and adds itself to cCamera::mpRenderList.
 cRenderObject(bool lbNoTextures);
 /// Constructor for cRenderObject. Creates a new render object and adds itself to lpNode.
 cRenderObject(vRenderNode *lpNode,bool lbNoTextures);

 // Destructor for cRenderObject.
 ~cRenderObject();

 ///This will set the Collision Object that is linked to this renderable object. This should be called automatically when a cCollisionObject is created.
 void LinkCollisionObject(cCollisionObject *lpObj);

 /// Returns the vRenderNode which owns this renderable process.
 vRenderNode *Renderer();


  // virtual functions to allow polymorphism. see cCamera::RenderPainter();
  virtual void RenderPainter()=0;

  void RenderToPainter();
 /// Will remove this object from the render list owned by mpRenderer.
  void Delete();/// Will return a pointer to the Shader Program that is currently bound to this model.
 /**
 * \brief Will move the current renderable object from the current cRenderNode to lpNode.
 * \param lpNode The cRenderNode which will now own this renderable object.
 * \return This function returns the new cLinkedNode which now owns this renderable object.
 */
 cRenderOwner &SetRenderNode(vRenderNode *lpNode);


  //This will contain additional functions to perform when an object renders.
  void AdditionalRenderFunctions();

  //This contains any Code to be run for this object in the event of its death (as deletion of the object may be delayed after death).
  virtual void AdditionalKillFunctionality();
  //This contains any Code to be run when the object is sent to sleep.
  virtual void AdditionalSleepFunctionality();
  //This contains any Code to be run when the object is woken up.
  virtual void AdditionalWakeFunctionality();
  ///This function will update the object cache. For consistency all Renderable Objects must update the cache as they are rendered. This will be the global position of the object and is used to get consistent positions throughout a frame for collision detection.
  void UpdateCache();

  using cTextureStack::AddTexture;
	///Will Add the Texture lpTexture to the next Texture Slot.
   void AddTexture(string lsTextureSlot,cTexture *lpTexture);
    ///This will Add the Texture to the next free Texture sampler following the default rules (default is "Texture0" "Texture1" "Texture2") This is a slow compared to AddTexture(string,cTexture*) . It also allows for mistakes in naming of samplers in the shader.
   void AddTexture(cTexture *lpTexture);

   ///Will remove the texture in TextureSlot labelled lsTextureSlot.
   void RemoveTexture(string lsTextureSlot);

   ///Will remove the texture in Textureslot number liTexSlot. (Texture0 Texture1 Texture2 etc.)
   void RemoveTexture(uint8 liTexSlot);

  /// This will return the Local position of the selected object.
  float *GetPos();
  /**
  * \brief This will return the global position of the object as rendered at the end of last frame.
  * This will return the cached Global position matrix as it was at the end of the last frame.
  * This will only be updated when rendering occurs. For a 'current' global matrix the function cCameraMatrix4::CalculateGlobalMatrix() will actually calculate the current matrix. However it is very slow.
  **/
  float *GetCachedGlobalMatrix();




  ///This will set whether this object uses transparency (Transparent objects are rendered after all other objects and in reverse distance order).
   void Transparency(bool lbTrans);
   ///This will return whether this object is using transparency.
   bool Transparency();

	///This will set whether lighting is used for the object.
   void Lighting(bool lbLighting);
	///This will return whether lighting is enabled for the object.
   bool Lighting();



   protected:
cVariableStore *mpVariables;
cShaderProgram *mpShader;

public:


  ///This function returns a pointer to the Buffering object for the Uniform Variable with ID liPos in the currently assigned cShaderProgram. See cUniformStore. cType should be a class which inherites from cUniformStore.
  template <class cType> cType* AddUniform(uint32 liPos);
  ///This function returns a pointer to the Buffering object for the Uniform Variable with ID liPos in the currently assigned cShaderProgram. See cAttributeStore.  cType should be a class which inherites from cAttributeStore.
  template <class cType> cType* AddAttribute(uint32 liPos);
  ///This function returns a pointer to the Buffering object for the Uniform Variable called 'name' in the currently assigned cShaderProgram. See cUniformStore.  cType should be a class which inherites from cUniformStore.
  template <class cType> cType* AddUniform(string name);
  ///This function returns a pointer to the Buffering object for the Attribute Variable called 'name' in the currently assigned cShaderProgram. See cAttributeStore.  cType should be a class which inherites from cAttributeStore.
  template <class cType> cType* AddAttribute(string name);


  void SetShaderVariables();

  cVariableStore* Variables();

};

template <class cType> cType* cRenderObject::AddUniform(uint32 liPos)
{
 return Variables()->CreateUniform(liPos,new cType);
};

template <class cType> cType* cRenderObject::AddAttribute(uint32 liPos)
{
 return Variables()->CreateAttribute(liPos,new cType);
};

template <class cType> cType* cRenderObject::AddUniform(string name)
{
	uint32 liPos=mpShader->ShaderVariables()->GetUniformPosition(name);
 if(liPos) return Variables()->CreateUniform(liPos-1,new cType);
 else return 0;
};

template <class cType> cType* cRenderObject::AddAttribute(string name)
{
 uint32 liPos=mpShader->ShaderVariables()->GetAttributePosition(name);
 if(liPos) return Variables()->CreateAttribute(liPos-1,new cType);
 else return 0;
};


#endif
