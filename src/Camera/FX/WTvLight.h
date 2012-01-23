#ifndef __WTVLIGHT_H__
#define __WTVLIGHT_H__

#if WT_FULL_VERSION_BAMBOO

/*
 A virtual class for cLight
*/
class vLight: public cSignal
{



public:
	//Non-virtual destructor to actualise class.
	~vLight(){};

	// Will bind this light to light number liLight in OpenGL.
	virtual void PrepareLight(uint32 liLight)=0;
	// Will Return the position of the Light source
	virtual float *Position()=0;

};

#endif

#endif
