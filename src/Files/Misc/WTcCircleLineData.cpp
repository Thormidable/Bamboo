#include "stdafx.h"
#include "../../WTBamboo.h"

cCircleLineData::cCircleLineData(cCircleLineData *lpOther) : cLineArrayData(lpOther)
{

};

cCircleLineData::cCircleLineData(float lfRadius, uint16 liSegments)
{
    GenerateCircle(lfRadius,liSegments);

}

cCircleLineData::~cCircleLineData()
{

}

void cCircleLineData::GenerateCircle(float lfRadius,uint16 liSegments)
{
    Init(liSegments+2);
	float theta = 2 * WT_PI / liSegments;
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = lfRadius;//we start at angle = 0
	float y = 0;

	for(int ii = 0; ii < liSegments; ii++)
	{
	    Add(c3DVf(x,0.0f,y));

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}

	Add(c3DVf(lfRadius,0.0f,0.0f));
	lbBuffer=true;
}

void cCircleLineData::Radius(float lfSize)
{
    float lfOld=mpList[0].X();
    lfSize=lfSize/lfOld;

    for(int ii = 0; ii < miItems; ii++)
	{
	    mpList[ii]*=lfSize;
	}
	lbBuffer=true;
}
