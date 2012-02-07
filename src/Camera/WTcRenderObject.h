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

	/// Will set the shader to use the Shader Program with the specified reference.
	void Shader(string lcString);
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
 /// Constructor for cRenderObject. Creates a new render object and adds itself to the cRenderNode of the cCamera lpCamera.
 cRenderObject(cCamera *lpCamera);
/// Constructor for cRenderObject. Creates a new render object and adds itself to the cRenderNode of the cCamera lpCamera.
 cRenderObject(cCamera *lpCamera,bool lbNoTextures);

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

  //This contains any Code to be run when this process .
  virtual void Stop();
  //This contains any Code to be run when the object is sent to sleep.
  virtual void OnSleep();
  //This contains any Code to be run when the object is woken up.
  virtual void OnWake();
  ///This function will update the object cache. For consistency all Renderable Objects must update the cache as they are rendered. This will be the global position of the object and is used to get consistent positions throughout a frame for collision detection.
  void UpdateCache();

  using cTextureStack::AddTexture;
	/**
	* \brief Will Add the Texture lpTexture to the Texture slot with the name matching lsTextureSlot.
	* Multitexturing in shaders is controlled using uniform sampler types:
	* \code
	* uniform sampler2D Texture0;
	* \endcode
	* This takes a 2D Texture and names it Texture0. By default Bamboo shaders use the names Texture0, Texture1 ,Texture2 etc.
	* If you use different names for your texture samplers they will need to be linked to the correct sampler name using this function.
	* This is faster than AddTexture(cTexture*)
	*/
   void AddTexture(string lsTextureSlot,cTexture *lpTexture);

   void AddTexture(string lsTextureSlot,string lcTextureReference);

    /**This will Add the Texture to the next free Texture sampler following the default rules (default is "Texture0" "Texture1" "Texture2") This is a slow compared to AddTexture(string,cTexture*)
    * It also allows for mistakes in naming of samplers in the shader if the samplers are not named "Texture0" "Texture1" "Texture2" etc.
    */
   void AddTexture(cTexture *lpTexture);

   void AddTexture(string lcTextureReference);

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

   void KillAll();

   void RecalculateTotalMatrix();
   void CalculateMatrices();


   protected:
cVariableStore *mpVariables;
cShaderProgram *mpShader;

public:


  ///This will set a Uniform Variable named lcString. This will store the data and not automatically update. The data can be deallocated at any time.
  void SetUniform(string lcString,void *Data);
  ///This will set an Attribute Array Variable named lcString. This will store the data and not automatically update. The data can be deallocated at any time.
  void SetAttribute(string lcString,void *Data,uint32 liElements);
  ///This will set a Uniform Variable named lcString. This will store the data and not automatically update. The data can be deallocated at any time.
  void SetVariable(string lcString,void *Data);
  ///This will set an Attribute Array Variable named lcString. This will store the data and not automatically update. The data can be deallocated at any time.
  void SetVariable(string lcString,void *Data,uint32 liElements);

  ///This will set the pointer for the Variable named lcString. This will not store the data and will automatically update with changes to the data stored in Data. The data should not be deallocated while the Shader is in use.
  void SetUniformPointer(string lcString,void *Data);
  ///This will set the pointer for the Attribute Array Variable named lcString. This will not store the data and will automatically update with changes to the data stored in Data. The data should not be deallocated while the Shader is in use.
  void SetAttributePointer(string lcString,void *Data,uint32 liElements);
  ///This will set the pointer for the Variable named lcString. This will not store the data and will automatically update with changes to the data stored in Data. The data should not be deallocated while the Shader is in use.
  void SetVariablePointer(string lcString,void *Data);
  ///This will set the pointer for the Attribute Array Variable named lcString. This will not store the data and will automatically update with changes to the data stored in Data. The data should not be deallocated while the Shader is in use.
  void SetVariablePointer(string lcString,void *Data,uint32 liElements);

   ///This will return a pointer to the Variable of Type cType with the reference lcString.
  template<class cType> cType *GetVariable(string lcString);
  ///This will return a pointer to the Variable of Type cType in position liPos of the Variable List.
  template<class cType> cType *GetVariable(uint32 liPos);

  void SetShaderVariables();

  cVariableStore* Variables();

};

template <class cType> cType* cRenderObject::GetVariable(uint32 liPos)
{
 if(liPos<mpVariables->Variables())
 {
	return dynamic_cast<cType*>(&(mpVariables->GetVariable(liPos)));
 }
 return 0;
};

template <class cType> cType* cRenderObject::GetVariable(string lcString)
{
 uint32 liPos=mpShader->ShaderVariableSet()->GetVariablePosition(lcString);
 if(liPos)
 {
	return GetVariable<cType>(liPos-1);
 }
 return 0;
};






#endif
