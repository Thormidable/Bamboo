#ifndef __WTVLANDSCAPEMESH_H__
#define __WTVLANDSCAPEMESH_H__
/// This is the virtual base class for cmLandscape.
class vmLandscape//: public cMesh
{

public:


	vmLandscape(){};

	virtual void RenderMesh()=0;
	/// This will prepare absent data for the landscape. Normal, UV and Face data.
	virtual void PrepareLandscape()=0;
	
	/// This will return the interpolated height at the local position lfX,lfZ relative to the landscapes 0,0 corner.
	virtual float GetHeightLocal(float lfX,float lfZ)=0;
	/// This will return the height of the vertex numbered liX,liZ in the vertex position array.
	virtual float GetVertexHeight(uint32 liX,uint32 liZ)=0;
	
	/// This will set the height of the vertex numbered liX,liZ in the vertex position array.
	virtual void SetHeight(uint32 liX,uint32 liZ,float lfHeight)=0;
	/// This will update the vertex normal array based on the current vertex positions.
	virtual void CreateNormalArray()=0;

	/// This will randomise the landscape to a maximum height of liHeight. Then each vertex will be smoothed based on the heights of all verteces within liSize segments.
	virtual void Randomize(float liHeight,uint8 liSize)=0;
	/// This will randomise the landscape to a maximum height of liheight.
	virtual void Randomize(float liHeight)=0;
	/// This will randomise the landscape by randomly bisecting the landscape Lines times. Each bisection raises the land on one side by lfLandscapeHeight. 
	virtual void Randomize(uint32 Lines,float lfLandscapeHeight)=0;

	/// This will return miXSize.
	virtual uint32 Width()=0;
	/// This will return miZSize.
	virtual uint32 Length()=0;

};

#endif
