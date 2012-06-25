#include "../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

cLightHandler::cLightHandler()
{
  SetupLights();
  mpLightList=0;
  mpLightSlots=new cLightSpot[WT_OPENGL_LIGHTS];
  miAwake=0;


};

cLightSpot::cLightSpot()
{
  mpLight=0;
  mbLightState=false;
}

void cLightHandler::MoreAwake(){++miAwake;};
void cLightHandler::MoreAsleep(){--miAwake;};

cLightHandler::~cLightHandler()
{
  DeleteAll();mpInstance=0;
  delete []mpLightSlots; mpLightSlots=0;

};

bool cLightHandler::AnyLights(){return miAwake;};

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

cLinkedNode<vLight> *cLightHandler::Add(vLight *lpNew)
{
	//trace("cLightHandler::Add")
	if (!mpLightList)
	{
		mpLightList=new cLinkedList<vLight>(lpNew);
		return mpLightList->Start();
	}
	mpLightList->Insert(lpNew);
	return mpLightList->End();
}

void cLightHandler::DeleteAll()
{
	trace("cLightHandler::DeleteAll");
	if(mpLightList) {delete mpLightList; mpLightList=0;}
}

void cLightHandler::Remove(cLinkedNode<vLight> *lpOld)
{
	mpLightList->Delete(lpOld);
}

void cLightHandler::PrepareLight()
{
 //trace("cLightHandler::PrepareLights");
 uint32 liCount=0;
 cLinkedNode<vLight> *lpCursor=mpLightList->Start();
 while(lpCursor)
 {
  if(lpCursor->Data()->Awake()) lpCursor->Data()->PrepareLight(liCount++);
  lpCursor=lpCursor->Next();
 }
}

void cLightHandler::SetLightStates()
{
 uint32 liCount;
 for(liCount=0;liCount<miAwake;++liCount)
 {
     if(!mpLightSlots[liCount].mbLightState)
     {
         glEnable(GL_LIGHT0+liCount);
         mpLightSlots[liCount].mbLightState=true;
     }
 }

 while(liCount<miAwake)
 {
    if(mpLightSlots[liCount].mbLightState)
    {
        glDisable(GL_LIGHT0+liCount);
        mpLightSlots[liCount].mbLightState=false;
    }
 }

}

void cLightHandler::PrepareLight(cMatrix4 *lpObject)
{
 if(miAwake>WT_OPENGL_LIGHTS)
 {
    //trace("cLightHandler::PrepareLight(Object)");
    double lfDist;
    cLightSpot *lpLarge;
    uint32 liCount;

    cLinkedNode<vLight> *lpCursor=mpLightList->Start();

    liCount=0;
    while(lpCursor && liCount<WT_OPENGL_LIGHTS)
    {
      if(lpCursor->Data()->Awake())
      {
        lfDist=lpObject->DistanceSq(lpCursor->Data()->Position());
        mpLightSlots[liCount].mfDist=lfDist;
        mpLightSlots[liCount].mpLight=lpCursor->Data();
        ++liCount;
      }
      lpCursor=lpCursor->Next();
    }

    lpLarge=&mpLightSlots[0];

    while(lpCursor)
      {
          if(lpCursor->Data()->Awake())
          {


          lfDist=lpObject->DistanceSq(lpCursor->Data()->Position());

          if(lfDist<lpLarge->mfDist)
          {
            lpLarge->mfDist=lfDist;
            lpLarge->mpLight=lpCursor->Data();
            for(liCount=1;liCount<WT_OPENGL_LIGHTS;++liCount)
            {
                if(mpLightSlots[liCount].mfDist>lpLarge->mfDist) {lpLarge=&mpLightSlots[liCount]; break;}
            }
           }
          }
              lpCursor=lpCursor->Next();
       }

    for(liCount=0;liCount<WT_OPENGL_LIGHTS;++liCount)
    {
      if(mpLightSlots[liCount].mpLight) mpLightSlots[liCount].mpLight->PrepareLight(liCount);
    }
 }
 else PrepareLight();
}

#endif
