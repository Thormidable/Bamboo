#include "../WTBamboo.h"


uint16 cMatrixStack::miDepth=0;

cMatrixStack *cMatrixStack::mpInstance=0;

cMatrixStack::cMatrixStack(uint16 liDepth) : cLimitedList<cMatrix4>(liDepth)
{
	miDepth=liDepth;
	UpdateCurrent();
	mmCurrent->Identity();
}

cMatrixStack *cMatrixStack::Instance()
{
	if(!mpInstance) mpInstance=new cMatrixStack(_MATRIX_STACK_DEPTH);
	return mpInstance;
}

float *cMatrixStack::GetMatrix(uint16 liPos)
{
	if(liPos<miItems) return mpList[liPos].Matrix();
	return 0;
}

void cMatrixStack::Pop()
{
	if(miItems) {--miItems; UpdateCurrent();}
};

void cMatrixStack::Push()
{
 	mpList[++miItems]=mmCurrent;
	UpdateCurrent();
};

void cMatrixStack::UpdateCurrent()
{
	mmCurrent=&mpList[miItems];
};

void cMatrixStack::Multiply(float *lpMatrix)
{
 mmCurrent->operator=(mmCurrent->operator*(lpMatrix));
};

void cMatrixStack::SetMatrix(float *lpOther)
{
 mmCurrent->operator=(lpOther);
}

cMatrix4 *cMatrixStack::Current()
{
 return mmCurrent;
}

void cMatrixStack::SetDepth(uint16 liDepth)
{
 if(mpInstance) {mpInstance->ChangeSize(liDepth); mpInstance->UpdateCurrent();}
 miDepth=liDepth;

}

void cMatrixStack::Identity()
{
 mmCurrent->Identity();
}

void cMatrixStack::Translate(float lpx,float lpy,float lpz)
{
 //mmCurrent->GAdvance(lpx,lpy,lpz);
 mmCurrent->Translate(lpx,lpy,lpz);
}

