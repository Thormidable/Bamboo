#ifndef __WTCSPOTLIGHT_H__
#define __WTCSPOTLIGHT_H__

class cSpotLight : public cLight
{

 // Stores the Direction of the spotlight
 float mpDirection[4];

public:

    cSpotLight();
  // This will set the Global Direction the Spot light will point in. X,Y,Z,Cutoff
  void Direction(float lfX,float lfY,float lfZ,float lfA);

	// Will bind this light to light number liLight in OpenGL.
	void PrepareLight(uint32 liLight);


};
#endif
