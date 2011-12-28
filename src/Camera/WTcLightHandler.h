#ifndef __WTCLIGHTHANDLER_H__
#define __WTCLIGHTHANDLER_H__

class cLightSpot
{
 public:
  vLight* mpLight;
  double mfDist;
};

/** \brief cLightHandler will control the OpenGL Lights. It will turn off lights not required or possible for different renderings to increase speed and circumvent the OpenGL limit of active lights.
 * OpenGL has a limited number of lights that can be used at any one time. This handler identifies the lights which will have the greatest effect on the current object and prepares the optimal selection
 * of lights for rendering the scene.
 */
class cLightHandler
{
 static cLightHandler* mpInstance;
 cLightHandler();

 cMinLL<vLight> *mpLightList;

 cLightSpot *mpTemp;

public:

  ~cLightHandler();

  //Initialises OpenGL Lights
  static void SetupLights();
  ///This function will return a pointer to the current cLightHandler Object.
  static cLightHandler* Instance();

  //Add a new vLight Object to the handler.
  cMinLN<vLight> *Add(vLight *lpNew);

 ///Will Prepare all the Lights for Rendering generally.
 void PrepareLight();
 ///Will Prepare the Lights for Rendering a specific Object.
 void PrepareLight(cMatrix4 *mpObj);

 // Will Remove the Light owned by node mpNode fom the LightList.
void Remove(cMinLN<vLight> *lpOld);

 /// Will Delete all the processes in the current Light list.
 void DeleteAll();

};

#endif
