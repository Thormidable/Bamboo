#include "../../WTBamboo.h"

float v2DPolygon::mpVertex[12]=
{
 1.0f,0.0f,0.0f,
 1.0f,1.0f,0.0f,
 0.0f,1.0f,0.0f,
 0.0f,0.0f,0.0f};

uint16 v2DPolygon::mpFaces[6]=
{
 0,1,2,0,2,3
};
float v2DPolygon::mpTextCoords[8]=
{
 1.0f,0.0f,
 1.0f,1.0f,
 0.0f,1.0f,
 0.0f,0.0f
};

float v2DPolygon::mpNormals[12]=
{
 0.0f,0.0f,1.0f,
 0.0f,0.0f,1.0f,
 0.0f,0.0f,1.0f,
 0.0f,0.0f,1.0f
};

void v2DPolygon::SetTextCoords(float liRange)
{
mpTextCoords[7]=mpTextCoords[6]=mpTextCoords[4]=mpTextCoords[1]=liRange;
mpTextCoords[5]=mpTextCoords[3]=mpTextCoords[2]=mpTextCoords[0]=liRange+0.015625;
}

void v2DPolygon::ResetTextCoords()
{
mpTextCoords[7]=mpTextCoords[6]=mpTextCoords[4]=mpTextCoords[1]=0.0f;
mpTextCoords[5]=mpTextCoords[3]=mpTextCoords[2]=mpTextCoords[0]=1.0f;
}

void v2DPolygon::SizeArrays(float lfSize)
{
 mpVertex[0]=mpVertex[3]=mpVertex[4]=mpVertex[7]=lfSize;
}
