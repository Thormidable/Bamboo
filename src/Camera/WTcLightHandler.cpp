#include "../WTDivWin.h"

cLightHandler::cLightHandler()
{
  SetupLights();mpLightList=0;mpTemp=new cLightSpot[WT_OPENGL_LIGHTS];
  
};

cLightHandler::~cLightHandler()
{
  DeleteAll();mpInstance=0;
  delete []mpTemp; mpTemp=0;
  
};

cLightHandler* cLightHandler::mpInstance=0;

cLightHandler* cLightHandler::Instance()
{
  if(!mpInstance) {mpInstance=new cLightHandler; return mpInstance;}
  return mpInstance;
}

void cLightHandler::SetupLights()
{
 float lpPointer[4]={0.5f,0.5f,0.5f,0.0f};
 trace("cLightHandler::SetupLights");
 glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lpPointer);
 glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
// glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,0.0f);
 
 glEnable(GL_LIGHTING);

}

cMinLN<vLight> *cLightHandler::Add(vLight *lpNew)
{
	trace("cLightHandler::Add")
	if (!mpLightList)
	{
		mpLightList=new cMinLL<vLight>(lpNew);
		mpLightList->mpStart->mpData->SetID(mpLightList->Size());
		return mpLightList->mpStart;
	}
	mpLightList->InsertE(lpNew);
	mpLightList->mpEnd->mpData->SetID(mpLightList->Size());
	return mpLightList->mpEnd;
}

void cLightHandler::DeleteAll()
{
	trace("cLightHandler::DeleteAll");
	if(mpLightList) {delete mpLightList; mpLightList=0;}
}

void cLightHandler::Remove(cMinLN<vLight> *lpOld)
{
	mpLightList->Delete(lpOld);
}

void cLightHandler::PrepareLight()
{
trace("cLightHandler::PrepareLights");
 cMinLN<vLight> *lpCursor=mpLightList->mpStart;
 while(lpCursor)
 {
  lpCursor->mpData->PrepareLight();
  lpCursor=lpCursor->Next();
 }
}

void cLightHandler::PrepareLight(cMatrix4 *lpObject)
{
 if(mpLightList->Size()>WT_OPENGL_LIGHTS)
 {
    trace("cLightHandler::PrepareLight(Object)");
    double lfDist;
    cLightSpot *lpLarge;
    uint32 liCount;

    cMinLN<vLight> *lpCursor=mpLightList->mpStart;
    
    liCount=0;
    while(lpCursor && liCount<WT_OPENGL_LIGHTS)
    {
      lfDist=lpObject->DistanceSq(lpCursor->mpData->Position());
      mpTemp[liCount].mfDist=lfDist;
      mpTemp[liCount].mpLight=lpCursor->mpData;
      ++liCount;
      lpCursor=lpCursor->Next();
    }

    while(lpCursor)
      {
      lfDist=lpObject->DistanceSq(lpCursor->mpData->Position());
    
      if(lfDist<lpLarge->mfDist) 
      {
	lpLarge->mfDist=lfDist;
	lpLarge->mpLight=lpCursor->mpData;
	for(liCount=1;liCount<WT_OPENGL_LIGHTS;++liCount){if(mpTemp[liCount].mfDist>lpLarge->mfDist) {lpLarge=&mpTemp[liCount]; break;}}
      }
      lpCursor=lpCursor->Next();
    }

    for(liCount=0;liCount<WT_OPENGL_LIGHTS;++liCount)
    {
      if(mpTemp[liCount].mpLight) mpTemp[liCount].mpLight->PrepareLight(liCount);
    }
 }
 else PrepareLight();
}
