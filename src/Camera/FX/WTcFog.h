#ifndef __WTCFOG_H__
#define __WTCFOG_H__

#if WT_FULL_VERSION_BAMBOO
/*
* \brief This class will create and control an OpenGL scenes fog effect.
*/
class cFog
{
 // boolean flag to determine whether the fog effect is currently used.
 bool lbOn;
 // the fog equation the fog effect will use. Use GL_EXP, it rocks. (or GL_EXP2 or GL_LINEAR)
 int32 mtMode;
 // Determines the RGBA color that the fog will fade to.
 float mpColor[4];
 // Determines the density of the fog. Determines how much the fog affects the screen colors.
 float mfDensity;
 // The distance from the camera that the fog effect starts.
 float mfStart;
 // The distance from the camera that the fog effect stops.
 float mfEnd;

public:
      // Creates a clear fog effect.
       cFog();
	// Creates a new fog object between distance lfStart and lfEnd.
       cFog(float lfStart,float lfEnd);
	// Will set the RGBA color of the fog.
       void SetColor(float lfRed,float lfGreen,float lfBlue,float lfAlpha);
	// Will set the fog equation the fog effect will use. (GL_EXP, GL_EXP2, GL_LINEAR)
       void SetMode(char ltMode);
	// Will set the effect the fog has on the screen colors. 1.0f is Opaque, 0.0f is completely transparent.
       void SetDensity(float lfDensity);
	// Will set the near and far distances, from the camera, of the fog effect.
       void SetRange(float lfStart,float lfEnd);
	// Will return whether the fog effect is on or off.
       bool On();
	// Will set the fog effect on.
       void SetOn();
	// Will set the fog effect off.
       void SetOff();

};
#endif

#endif
