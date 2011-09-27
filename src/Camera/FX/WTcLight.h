#ifndef __WTCLIGHT_H__
#define __WTCLIGHT_H__
/// Creates an OpenGL light effect
class cLight : public vLight
{
protected:

  uint8 miLightID;

 // A vector for the lights position.
 float mpPosition[4];
 // A RGBA color for the ambient light from the source.
 float mpAmbient[4];
 // A RGBA color for the diffuse light from the source.
 float mpDiffuse[4];
 // A RGBA color for the Specular color of the source.
 float mpSpecular[4];

 // Stores the Attenuation Factor for the light source.
 float miAttenuation;
 //Stores the Attenuation Type. 0=constant. 1=linear. 2=Quadratic.
 uint32 miAttenuationType;

 static cLightHandler *mpLightHandler;
 cMinLN<vLight> *mpNode;

  public:
	/// Constructor, will create a new light source.
        cLight();
	// Destructor will delete the current light source.
	~cLight();

	/// Will Move the light to Global position lfX,lfY,lfZ. 
        void Position(float lfX,float lfY,float lfZ);
	
	/// Will Return the Current position of the light.
	float *Position(){return mpPosition;};

	/// Will set the Ambient light color for the light source (RGBA).
	void Ambient(float lfR,float lfG,float lfB,float lfA);

	///Will set the Diffuse light color for the light source (RGBA).
	void Diffuse(float lfR,float lfG,float lfB,float lfA);

	///Will set the Specular light color for the light source (RGBA).
	void Specular(float lfR,float lfG,float lfB,float lfA);
	
	/// Will bind this light source for use in OpenGL. Once all the Lights Variables are set, call this to preapre the light.
        virtual void PrepareLight();

	// Will bind this light to light number liLight in OpenGL. Should only be Used by Light Handler
	virtual void PrepareLight(uint32 liLight);

	///Will Set the value for the attenuation factor.
	void Attenuation(float liAttenuation);

	///Will Set the order of the attenuation (0=constant, 1=linear or 2=Quadratic).
	void AttenuationType(uint8 liOrder);

	///Will Set the Lights ID (The OpenGL light number this light will render to by default).
	void SetID(uint8 liLightID);

};

#endif
