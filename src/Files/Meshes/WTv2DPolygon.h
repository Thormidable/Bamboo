#ifndef __WTV2DPOLYGON_H__
#define __WTV2DPOLYGON_H__
/// This stores mesh data for a single square quadrilateral. This is used for cTextureText.
class v2DPolygon
{
public:
 /// This stores the vertex position array for this polygon.
 static float mpVertex[12];
/// This stores the face array for this polygon. 
static uint16 mpFaces[6];
/// This stores the vertex texture co-ordinates for this polygon. 
 static float mpTextCoords[8];
/// This stores the vertex normals data for this polygon. 
 static float mpNormals[12];

 /// This will scale the polygon to lfsize.
 static void SizeArrays(float lfSize);
 /// This will position the texture co-ordinates for a single character in a 1x64 character font texture. 
 static void SetTextCoords(float liRange);
 /// This will reset the texture co-ordinates to use the entire texture.
 static void ResetTextCoords();

};

#endif
