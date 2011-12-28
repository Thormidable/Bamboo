#ifndef __WTVLIGHT_H__
#define __WTVLIGHT_H__
/*
 A virtual class for cLight
*/
class vLight
{



public:
	//Non-virtual destructor to actualise class.
	~vLight(){};
	// Will bind this light source for use in OpenGL.
        virtual void PrepareLight()=0;
	// Will bind this light to light number liLight in OpenGL.
	virtual void PrepareLight(uint32 liLight)=0;
	// Will Return the position of the Light source
	virtual float *Position()=0;
	// Will Set the Lights ID (Light number will render with
	virtual void SetID(uint8 liLightID)=0;

};

#endif