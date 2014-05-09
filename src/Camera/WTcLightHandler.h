#ifndef __WTCLIGHTHANDLER_H__
#define __WTCLIGHTHANDLER_H__

#if WT_FULL_VERSION_BAMBOO

class cLightSpot
{
 public:
  cLightSpot();
  vLight* mpLight;
  double mfDist;
  bool mbLightState;
};

/** \brief cLightHandler will control the OpenGL Lights. It will turn off lights not required or possible for different renderings to increase speed and circumvent the OpenGL limit of active lights.
 * OpenGL has a limited number of lights that can be used at any one time. This handler identifies the lights which will have the greatest effect on the current object and prepares the optimal selection
 * of lights for rendering the scene.
 */
class cLightHandler
{
 uint32 miAwake;
 static cLightHandler* mpInstance;
 cLightHandler();

 cLinkedList<vLight> *mpLightList;

 cLightSpot *mpLightSlots;

public:

  ~cLightHandler();

  //Initialises OpenGL Light States
  static void SetupLights();
  ///This function will return a pointer to the current cLightHandler Object.
  static cLightHandler* Instance();

  //Add a new vLight Object to the handler.
  cLinkedNode<vLight> *Add(vLight *lpNew);

 ///Will Prepare all the Lights for Rendering generally.
 void PrepareLight();
 ///Will Prepare the Lights for Rendering a specific Object.
 void PrepareLight(cMatrix4 *mpObj);

 // Will Remove the Light owned by node mpNode fom the LightList.
void Remove(cLinkedNode<vLight> *lpOld);

 /// Will Delete all the processes in the current Light list.
 void DeleteAll();

 //Will Enable and Disable all the OpenGL lights
 void SetLightStates();

 //Will return true if there are any lights.
 bool AnyLights();

 //Will increase the number of awake lights to avoid having to count
 void MoreAwake();
 //Will decrease the number of awake lights to avoid having to count
 void MoreAsleep();

 void GlobalAmbient(float *lpPoint);
 void GlobalAmbient(cRGBA *lpPoint);
 void GlobalAmbient(cRGBA lpPoint);

};

#endif

#endif
