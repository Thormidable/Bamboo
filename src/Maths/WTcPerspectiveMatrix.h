#ifndef __WTCPERSPECTIVEMATRIX_H__
#define __WTCPERSPECTIVEMATRIX_H__

class cPerspectiveMatrix : public cMatrix4
{
	/// This variable can be thought of as the lens effect. 0.5f - 1.0f can be considered normal. 0.1f -0.5f is a fisheye lens.
    float mfWidth;
 	/// This variable stores the closest that the Perspective Matrix will render polygons.
    float mfNear;
	/// This variable stores the furthest that the perspective Matrix will render polygons.
	float mfFar;
	float mfRatio;
	float mfHeight;
public:

    void Width(float lfWidth);
    float Width();

    void Near(float lfNear);
    float Near();

    void NearFar(float lfNear,float lfFar);

    void Far(float lfFar);
    float Far();

    void Ratio(float lfRatio);
    float Ratio();

    void Height(float lfHeight);
    float Height();

 	void Frustum();
 	void Orthographic();

	cPerspectiveMatrix();
	void Setup(float lfZoom,float lfRatio,float lfNear,float lfFar);

	void Frustum(float Width, float Height, float Near, float Far);
	void Orthographic(float Width, float Height, float Near, float Far);
	void Frustum(float Right, float Left, float Top, float Bottom, float Near, float Far);
	void Orthographic(float Right, float Left, float Top, float Bottom, float Near, float Far);
	void Frustum(float *lpValues);
	void Orthographic(float *lpValues);
	void Frustum2(float *lpValues);
	void Orthographic2(float *lpValues);
	inline void Viewport();

};

#endif
