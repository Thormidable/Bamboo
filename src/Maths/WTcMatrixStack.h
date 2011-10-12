#ifndef __WTCMATRIXSTACK_H__
#define __WTCMATRIXSTACK_H__

class cMatrixStack : public cLimitedList<cMatrix4>
{
	static uint16 miDepth;
	static cMatrixStack *mpInstance;
	cMatrix4 *mmCurrent;
	cMatrixStack(uint16 liDepth);
	void UpdateCurrent();
public:

	static cMatrixStack *Instance();
	float *GetMatrix(uint16 liPos);
	void Pop();
	void Push();
	void Identity();
	void Translate(float lpx,float lpy,float lpz);
	void Multiply(float *lpMatrix);
	void SetMatrix(float *lpOther);
	static void SetDepth(uint16 liDepth);
	cMatrix4 *Current();
};



#endif
