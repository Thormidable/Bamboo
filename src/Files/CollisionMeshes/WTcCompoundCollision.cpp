
#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

cCompoundCollision::cCompoundCollision() {};
cCompoundCollision::cCompoundCollision(uint32 liSize) : cLimitedPointerList<cCompoundCollisionNode>(liSize){};
cCompoundCollision::~cCompoundCollision(){DeleteAll();};
cCompoundCollision *cCompoundCollision::Compound(){return this;};

bool cCompoundCollision::Owns(vCollisionData *lpData)
{
 for(uint16 liCount=0;liCount<miItems;++liCount)
 {
  if(mpList[liCount]->mpObject==lpData || (mpList[liCount]->Compound() && mpList[liCount]->Compound()->Owns(lpData))) return 1;
 }
 return 0;
};

void cCompoundCollision::Update(cMatrix4 &New)
{
 #pragma warning (This should recalculate the size of the object.)

};

uint8 cCompoundCollision::Type(){return WT_COLLISION_COMPOUND;}
vCollisionData *cCompoundCollision::operator[](uint32 liPos)
{
    return mpList[liPos]->mpObject;
};

vCollisionData *cCompoundCollision::GetObject(uint32 liPos)
{
    return mpList[liPos]->mpObject;
}

cCompoundCollisionNode::cCompoundCollisionNode()
{
    //mpObject=0;
};

cCompoundCollisionNodeMobile::cCompoundCollisionNodeMobile()
{
    mmCollisionMatrix.Identity();
    mmTotalMatrix.Identity();
};
cCompoundCollisionNode::~cCompoundCollisionNode()
{
    ClearProcedural();
};
void cCompoundCollision::AddType(vCollisionData *lpOther)
{
 if(lpOther)
 {
   if(miItems>=miSpaces-1) ChangeSize(miSpaces*1.5);
   mpList[miItems]=new cCompoundCollisionNode;
   mpList[miItems]->mpObject=lpOther;
   if(mfSize<mpList[miItems]->mpObject->CollisionSize()) mfSize=mpList[miItems]->mpObject->CollisionSize();
   ++miItems;
 }
};

cSphereCollision *cCompoundCollision::AddType(float lfSize)
{
 cSphereCollision *lpSphere=new cSphereCollision();
 lpSphere->SetSize(lfSize);
 AddType(lpSphere);
 return lpSphere;
};

cBeamCollision *cCompoundCollision::AddType(float lfLength,float lfRadius)
{
    cBeamCollision *lpTemp=new cBeamCollision;
    lpTemp->BuildObject(lfLength,lfRadius);
    AddType(lpTemp);
    if(mfSize<lfLength) mfSize=lfLength;
    return lpTemp;
};
cMeshCollision *cCompoundCollision::AddType(float *lpBounds)
{
    cMeshCollision *lpTemp=new cMeshCollision;
    lpTemp->BuildObject(lpBounds);
    AddType(lpTemp);
    return lpTemp;
};
cMeshCollision *cCompoundCollision::AddType(float lfXP,float lfXN,float lfYP,float lfYN,float lfZP,float lfZN)
{
    cMeshCollision *lpTemp=new cMeshCollision;
    float Temp[6]={lfXP,lfXN,lfYP,lfYN,lfZP,lfZN};
    lpTemp->BuildObject(Temp);
    AddType(lpTemp);
    return lpTemp;
};
cBeamCollision *cCompoundCollision::AddType(cBeam *lpBeam)
{
 if(lpBeam)
 {
    cBeamCollision *lpTemp=new cBeamCollision;
    lpTemp->BuildObject(lpBeam->Length(),lpBeam->Radius());
    AddType(lpTemp);
    return lpTemp;
 }
 return 0;
};

uint8 cCompoundCollision::GetType(uint32 liPos)
{
    return mpList[liPos]->mpObject->Type();
}

void cCompoundCollisionNodeMobile::UpdateMatrices(cMatrix4 &lcBase)
{
    mmTotalMatrix=lcBase;
    mmTotalMatrix.Multiply(mmCollisionMatrix);
}

uint8 cCompoundCollisionNode::Type()
{
    return mpObject->Type();
}

cMatrix4 &cCompoundCollisionNode::CacheMatrix()
{
    return cMatrix4::mpTemp;
};

cMatrix4 &cCompoundCollisionNodeMobile::CacheMatrix()
{
    return mmTotalMatrix;
};
#endif
