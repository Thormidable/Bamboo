#ifndef __WTCLIGHT_H__
#define __WTCLIGHT_H__

#if WT_FULL_VERSION_BAMBOO
// Creates an OpenGL light effect
class cLight : public vLight
{
protected:

 // A vector for the lights position.
 float mpPosition[4];
 // A RGBA color for the ambient light from the source.
 cRGBA mpAmbient;
 // A RGBA color for the diffuse light from the source.
 cRGBA mpDiffuse;
 // A RGBA color for the Specular color of the source.
 cRGBA mpSpecular;

 // Stores the Attenuation Factor for the light source.
 float miAttenuation;
 //Stores the Attenuation Type. 0=constant. 1=linear. 2=Quadratic.
 uint32 miAttenuationType;

 static cLightHandler *mpLightHandler;
 cLinkedNode<vLight> *mpNode;

  public:
	/// Constructor, will create a new light source.
        cLight();
	/// Destructor will delete the current light source.
	~cLight();

	/// Will Move the light to Global position lfX,lfY,lfZ.
        void Position(float lfX,float lfY,float lfZ);
    /// Will Move the light to Global position of the vector lfPos.
        void Position(float *lfX);
        /// Will Move the light to Global position of the vector lfPos.
        void Position(c3DVf *lfPos);
        /// Will Move the light to Global position of the vector lfPos.
        void Position(c3DVf &lfPos);
	/// Will Return the Current position of the light.
	float *Position(){return mpPosition;};

	/// Will set the Ambient light color for the light source (RGBA).
	void Ambient(float lfR=0.0f,float lfG=0.0f,float lfB=0.0f,float lfA=1.0f);
	/// Will set the Ambient light color for the light source (RGBA).
	void Ambient(cRGBA &lcColor);
	/// Will set the Ambient light color for the light source (RGBA).
	void Ambient(cRGBA *lcColor);
	/// Will set the Ambient light color for the light source (RGBA).
	void Ambient(cRGB &lcColor);
	/// Will set the Ambient light color for the light source (RGBA).
	void Ambient(cRGB *lcColor);

    /// Will set the Diffuse light color for the light source (RGBA).
	void Diffuse(float lfR=0.0f,float lfG=0.0f,float lfB=0.0f,float lfA=1.0f);
	/// Will set the Diffuse light color for the light source (RGBA).
	void Diffuse(cRGBA &lcColor);
	/// Will set the Diffuse light color for the light source (RGBA).
	void Diffuse(cRGBA *lcColor);
	/// Will set the Diffuse light color for the light source (RGBA).
	void Diffuse(cRGB &lcColor);
	/// Will set the Diffuse light color for the light source (RGBA).
	void Diffuse(cRGB *lcColor);


    /// Will set the Specular light color for the light source (RGBA).
	void Specular(float lfR=0.0f,float lfG=0.0f,float lfB=0.0f,float lfA=1.0f);
	/// Will set the Specular light color for the light source (RGBA).
	void Specular(cRGBA &lcColor);
	/// Will set the Specular light color for the light source (RGBA).
	void Specular(cRGBA *lcColor);
	/// Will set the Specular light color for the light source (RGBA).
	void Specular(cRGB &lcColor);
	/// Will set the Specular light color for the light source (RGBA).
	void Specular(cRGB *lcColor);

	// Will bind this light to light number liLight in OpenGL. Should only be Used by Light Handler
	virtual void PrepareLight(uint32 liLight);

	///Will Set the value for the attenuation factor.
	void Attenuation(float liAttenuation);

	///Will Set the order of the attenuation (0=constant, 1=linear or 2=Quadratic).
	void AttenuationType(uint8 liOrder);

	///This will Receive Signals from Other Objects.
	void Signal(SIGNAL lsSignal);

};
#endif

#endif
