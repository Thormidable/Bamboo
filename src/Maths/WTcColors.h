#ifndef __WTCCOLORS_H__
#define __WTCCOLORS_H__

class cRGB;

/**
* \brief this is a Color Variable. It can Store 4 components: Red, Green, Blue and Alpha. Alpha of 0.0f is Transparent.
* This is a standardised 4 component color vector. It can be passed to functions to represent a color. It can also be used and assigned as if a standard variable.
* If this is passed a cRGB Color the Alpha will be assumed to be 1.0f;
*/
class cRGBA
{
float color[4];
public:
	///Constructor which allows 0-4 components to be set.
    cRGBA(float lfR=0.0f,float lfG=0.0f,float lfB=0.0f,float lfA=1.0f);
	///Constructor taking a pointer to an array of four floats
    cRGBA(float *lfRGB);

    cRGBA(c3DVf lfOther);
    cRGBA(c4DVf lfOther);
    ///Returns the Red component of the color.
    float R();
	///Returns the Blue component of the color.
    float G();
	///Returns the Green component of the color.
    float B();
	///Returns the Alpha component of the color.
    float A();
	///Sets the Red Component.
	void R(float lfR);
	///Sets the Green Component.
	void G(float lfG);
	///Sets the Blue Component.
	void B(float lfB);
	///Sets the Alpha Component.
	void A(float lfA);
	///Returns a float pointer to the array of components
    float *Color();

	///Array operator to allow the user to access components by position. R=0, G=1, B=2, A=3.
    float &operator[](uint32);
    ///Set the values with floats
    void Set(float lfR=0.0f,float lfG=0.0f,float lfB=0.0f,float lfA=1.0f);

    cRGBA operator=(float *lpOther);
    cRGBA operator=(cRGB lpOther);
    cRGBA operator=(cRGB *lpOther);
    cRGBA operator=(cRGBA lpOther);
    cRGBA operator=(cRGBA *lpOther);

    cRGBA operator+(float lfOther);
    cRGBA operator+(float *lpOther);
    cRGBA operator+(cRGB lpOther);
    cRGBA operator+(cRGB *lpOther);
    cRGBA operator+(cRGBA lpOther);
    cRGBA operator+(cRGBA *lpOther);
    cRGBA operator+(c3DVf lpOther);
    cRGBA operator+(c3DVf *lpOther);

    cRGBA operator-(float lfOther);
    cRGBA operator-(float *lpOther);
    cRGBA operator-(cRGB lpOther);
    cRGBA operator-(cRGB *lpOther);
    cRGBA operator-(cRGBA lpOther);
    cRGBA operator-(cRGBA *lpOther);
    cRGBA operator-(c3DVf lpOther);
    cRGBA operator-(c3DVf *lpOther);

    cRGBA operator*(float lfOther);
    cRGBA operator*(float *lpOther);
    cRGBA operator*(cRGB lpOther);
    cRGBA operator*(cRGB *lpOther);
    cRGBA operator*(cRGBA lpOther);
    cRGBA operator*(cRGBA *lpOther);
    cRGBA operator*(c3DVf lpOther);
    cRGBA operator*(c3DVf *lpOther);

    cRGBA operator/(float lfOther);
    cRGBA operator/(float *lpOther);
    cRGBA operator/(cRGB lpOther);
    cRGBA operator/(cRGB *lpOther);
    cRGBA operator/(cRGBA lpOther);
    cRGBA operator/(cRGBA *lpOther);
    cRGBA operator/(c3DVf lpOther);
    cRGBA operator/(c3DVf *lpOther);


      cRGBA operator+=(float lfOther);
    cRGBA operator+=(float *lpOther);
    cRGBA operator+=(cRGB lpOther);
    cRGBA operator+=(cRGB *lpOther);
    cRGBA operator+=(cRGBA lpOther);
    cRGBA operator+=(cRGBA *lpOther);
    cRGBA operator+=(c3DVf lpOther);
    cRGBA operator+=(c3DVf *lpOther);

    cRGBA operator-=(float lfOther);
    cRGBA operator-=(float *lpOther);
    cRGBA operator-=(cRGB lpOther);
    cRGBA operator-=(cRGB *lpOther);
    cRGBA operator-=(cRGBA lpOther);
    cRGBA operator-=(cRGBA *lpOther);
    cRGBA operator-=(c3DVf lpOther);
    cRGBA operator-=(c3DVf *lpOther);

    cRGBA operator*=(float lfOther);
    cRGBA operator*=(float *lpOther);
    cRGBA operator*=(cRGB lpOther);
    cRGBA operator*=(cRGB *lpOther);
    cRGBA operator*=(cRGBA lpOther);
    cRGBA operator*=(cRGBA *lpOther);
    cRGBA operator*=(c3DVf lpOther);
    cRGBA operator*=(c3DVf *lpOther);

    cRGBA operator/=(float lfOther);
    cRGBA operator/=(float *lpOther);
    cRGBA operator/=(cRGB lpOther);
    cRGBA operator/=(cRGB *lpOther);
    cRGBA operator/=(cRGBA lpOther);
    cRGBA operator/=(cRGBA *lpOther);
    cRGBA operator/=(c3DVf lpOther);
    cRGBA operator/=(c3DVf *lpOther);


};

/**
* \brief This is a Color Variable. It can Store 3 components: Red, Green, Blue. It is assumed the color is opaque.
* This is a standardised 3 component color vector. It can be passed to functions to represent a color. It can also be used and assigned as if a standard variable.
* If this is passed a cRGBA Color the Alpha will be discarded.
*/
class cRGB
{
float color[3];
public:
		///Constructor which allows 0-3 components to be set.
    cRGB(float lfR=0.0f,float lfG=0.0f,float lfB=0.0f);
	///Constructor taking a pointer to an array of three floats
    cRGB(float *lfRGB);

    cRGB(c3DVf lfOther);
    cRGB(c4DVf lfOther);
    ///Returns the Red component of the color.
    float R();
	///Returns the Blue component of the color.
    float G();
	///Returns the Green component of the color.
    float B();
	///Sets the Red Component.
	void R(float lfR);
	///Sets the Green Component.
	void G(float lfG);
	///Sets the Blue Component.
	void B(float lfB);
	///Returns a float pointer to the array of components
    float *Color();

    cRGB operator=(float *lpOther);
    cRGB operator=(cRGB lpOther);
    cRGB operator=(cRGB *lpOther);
    cRGB operator=(cRGBA lpOther);
    cRGB operator=(cRGBA *lpOther);

    cRGB operator+(float lfOther);
    cRGB operator+(float *lpOther);
    cRGB operator+(cRGB lpOther);
    cRGB operator+(cRGB *lpOther);
    cRGB operator+(cRGBA lpOther);
    cRGB operator+(cRGBA *lpOther);

    cRGB operator-(float lfOther);
    cRGB operator-(float *lpOther);
    cRGB operator-(cRGB lpOther);
    cRGB operator-(cRGB *lpOther);
    cRGB operator-(cRGBA lpOther);
    cRGB operator-(cRGBA *lpOther);

    cRGB operator*(float lfOther);
    cRGB operator*(float *lpOther);
    cRGB operator*(cRGB lpOther);
    cRGB operator*(cRGB *lpOther);
    cRGB operator*(cRGBA lpOther);
    cRGB operator*(cRGBA *lpOther);
    cRGB operator*(c3DVf lpOther);
    cRGB operator*(c3DVf *lpOther);

    cRGB operator/(float lfOther);
    cRGB operator/(float *lpOther);
    cRGB operator/(cRGB lpOther);
    cRGB operator/(cRGB *lpOther);
    cRGB operator/(cRGBA lpOther);
    cRGB operator/(cRGBA *lpOther);
    cRGB operator/(c3DVf lpOther);
    cRGB operator/(c3DVf *lpOther);


    cRGB operator+=(float lfOther);
    cRGB operator+=(float *lpOther);
    cRGB operator+=(cRGB lpOther);
    cRGB operator+=(cRGB *lpOther);
    cRGB operator+=(cRGBA lpOther);
    cRGB operator+=(cRGBA *lpOther);

    cRGB operator-=(float lfOther);
    cRGB operator-=(float *lpOther);
    cRGB operator-=(cRGB lpOther);
    cRGB operator-=(cRGB *lpOther);
    cRGB operator-=(cRGBA lpOther);
    cRGB operator-=(cRGBA *lpOther);

    cRGB operator*=(float lfOther);
    cRGB operator*=(float *lpOther);
    cRGB operator*=(cRGB lpOther);
    cRGB operator*=(cRGB *lpOther);
    cRGB operator*=(cRGBA lpOther);
    cRGB operator*=(cRGBA *lpOther);
    cRGB operator*=(c3DVf lpOther);
    cRGB operator*=(c3DVf *lpOther);

    cRGB operator/=(float lfOther);
    cRGB operator/=(float *lpOther);
    cRGB operator/=(cRGB lpOther);
    cRGB operator/=(cRGB *lpOther);
    cRGB operator/=(cRGBA lpOther);
    cRGB operator/=(cRGBA *lpOther);
    cRGB operator/=(c3DVf lpOther);
    cRGB operator/=(c3DVf *lpOther);


		///Array operator to allow the user to access components by position. R=0, G=1, B=2;
    float &operator[](uint32);
    ///Set the values with floats
    void Set(float lfR=0.0f,float lfG=0.0f,float lfB=0.0f);
};

#endif

