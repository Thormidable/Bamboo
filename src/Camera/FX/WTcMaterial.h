#ifndef __WTCMATERIAL_H__
#define __WTCMATERIAL_H__

/// A class to store material data for an object. Defines the 'reflectiveness' of the surface.
class cMaterial
{
 // The RGBA color for the specular reflection of the material.
 float mpSpecular[4];
 // The shininess of the material. set from 0 - 1.0f
 float mpShine[1];


 public:
	/// Will create a new material object.
        cMaterial();
	/// Will set the RGBA color of Specular reflections of this material (RGBA).
        void SetSpecular(float lfRed,float lfGreen,float lfBlue,float lfAlpha);
	/// Will set the shininess of this material (0.0f - 1.0f).
        void SetShine(float lfShine);
	/// Will bind the material to OpenGL ready to be used. Once all the material variables are set, call this to prepare the material.
        void PrepareMaterial();


};

#endif
