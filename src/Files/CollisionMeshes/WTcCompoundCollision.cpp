#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

cCompoundCollision::cCompoundCollision(){};
cCompoundCollision::cCompoundCollision(uint32 liSize) : cLimitedPointerList<cCompoundCollisionNode>(liSize){};
cCompoundCollision::~cCompoundCollision(){};
cCompoundCollision *cCompoundCollision::Compound(){return this;};

void cCompoundCollision::Update(cMatrix4 &New)
{
 #warning comment This should recalculate the size of the object.

};


vCollisionData *cCompoundCollision::operator[](uint32 liPos)
{
    return mpList[liPos]->mpCollisionData;
};
cMatrix4 &cCompoundCollision::GetMatrix(uint32 liPos)
{
    return mpList[liPos]->mmCollisionMatrix;
};


cCompoundCollisionNode::cCompoundCollisionNode()
{
    mpCollisionData=0;
    miType=WT_COLLISION_NO_TYPE;
    mmCollisionMatrix.Identity();
};
cCompoundCollisionNode::~cCompoundCollisionNode()
{
    ClearProcedural();
};
void cCompoundCollision::AddType(vCollisionData *lpOther)
{
   if(miItems>=miSpaces) ChangeSize(miSpaces*1.5);
   mpList[miItems]=new cCompoundCollisionNode;
   mpList[miItems]->mpCollisionData=lpOther;
   ++miItems;
};

cSphereCollision *cCompoundCollision::AddType(float lfSize)
{
 AddType(new cSphereCollision());
 mpList[miItems-1]->mpCollisionData->SetSize(lfSize);
 return mpList[miItems-1]->mpCollisionData->Sphere();
};

cBeamCollision *cCompoundCollision::AddType(float lfLength,float lfRadius)
{
    cBeamCollision *lpTemp=new cBeamCollision;
    AddType(lpTemp);
    lpTemp->BuildObject(lfLength,lfRadius);
    return lpTemp;
};
cMeshCollision *cCompoundCollision::AddType(float *lpBounds)
{
    cMeshCollision *lpTemp=new cMeshCollision;
    AddType(lpTemp);
    lpTemp->BuildObject(lpBounds);
    return lpTemp;
};
cMeshCollision *cCompoundCollision::AddType(float lfXP,float lfXN,float lfYP,float lfYN,float lfZP,float lfZN)
{
    cMeshCollision *lpTemp=new cMeshCollision;
    AddType(lpTemp);
    float Temp[6]={lfXP,lfXN,lfYP,lfYN,lfZP,lfZN};
    lpTemp->BuildObject(Temp);
    return lpTemp;
};
cBeamCollision *cCompoundCollision::AddType(cBeamMesh *lpBeam)
{
    cBeamCollision *lpTemp=new cBeamCollision;
    AddType(lpTemp);
    lpTemp->BuildObject(lpBeam->Length(),lpBeam->Radius());
    return lpTemp;
};

#endif
