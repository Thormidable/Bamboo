#ifndef __WTCBEAMMESH_H__
#define __WTCBEAMMESH_H__

#if WT_FULL_VERSION_BAMBOO

/**
*\brief A Procedurally generated cylindrical Renderable Object.
*This class will generate a cylinder with specified dimensions and segments. The origin for the cylinder is in the radial center of one end of the cylinder.
**/
class cBeamMesh : public cRenderObject
{
	float *VertexData;
	uint16 *VertexList;
	float mfRadius;
	float mfLength;
	uint16 miSegments;

	GLuint mBuffer1;
	GLuint mBuffer2;


public:
	///Constructor to Create a Beam with the specified Dimensions. Segments must be an even integer.
	cBeamMesh(float Radius=0.1f,float Length=1.0f,uint16 Segments=6,vRenderNode *lpNode=cCamera::Instance()->RenderList());
	cBeamMesh(float Radius,float Length,uint16 Segments,cCamera *lpNode);
	~cBeamMesh();
	///Sets the Length of the Cylinder.
	void Length(float Length);
	///Sets the Radius of the Cylinder.
	void Radius(float Radius);
	///Will regenerate the cylinder with the specified Specifications.
	void GenerateData(float Radius,float Length,uint16 Segments);

	///Returns the current Length of the Cylinder.
	float Length(){return mfLength;};
	///Returns the current Radius of the Cylinder.
	float Radius(){return mfRadius;};

	void BufferBeam();
	void RenderBeam();

	//Functions CAlled by cPainter or cRenerNode to Render this object.
	void RenderPainter();

    float GetSize();
	double GetSizeSq();
};


#endif

#endif
