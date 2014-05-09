#include "stdafx.h"
#include "../WTBamboo.h"


vRenderNode::vRenderNode()
{
 mpCamera=cCamera::Instance();
 mpRenderer=mpCamera->RenderList();
 mcOwnerNode=mpRenderer->Add(this);
};

vRenderNode::vRenderNode(cCamera *lpCamera)
{
 mpCamera=lpCamera;
 mpRenderer=mpCamera->RenderList();
 mcOwnerNode=mpRenderer->Add(this);
};

vRenderNode::vRenderNode(vRenderNode *lpRenderer)
{
 mpRenderer=lpRenderer;
 mpCamera=lpRenderer->Camera();
 mcOwnerNode=mpRenderer->Add(this);
};

vRenderNode::vRenderNode(bool lbTopLevel)
{
 (void) lbTopLevel;
 mpCamera=cCamera::Instance();
 mpRenderer=0;
 mcOwnerNode.Node=0;

};

vRenderNode::vRenderNode(bool lbTopLevel,cCamera *lpCamera)
{
(void) lbTopLevel;
 mpRenderer=0;
 mcOwnerNode.Node=0;
 mpCamera=lpCamera;
};

void vRenderNode::RenderPainter(){};


void vRenderNode::Stop()
{
	if(mpCollisionObject)
	{
		_KILL(mpCollisionObject);
		mpCollisionObject=0;
	}

	//StartKillAll();
}

void vRenderNode::OnSleep()
{
if(mpCollisionObject)
{
    _SLEEP(mpCollisionObject);
}
}

void vRenderNode::OnWake()
{

if(mpCollisionObject)
{
    _WAKE(mpCollisionObject);
}

}

vRenderNode::~vRenderNode()
{
    if(mpCollisionObject)
	{
		_KILL(mpCollisionObject);
		mpCollisionObject=0;
	}
	//StartKillAll();

}

cVariableStore* vRenderNode::Variables(){return 0;}


cRenderOwner vRenderNode::MoveItem(vRenderObject *lpObj)
{
 return MoveItem(lpObj,_CAMERA->RenderList());
};

vRenderNode *vRenderNode::GetBaseOfTree()
{
 if(Renderer() && Renderer()->Renderer())
 {
  vRenderNode *lpCur;
  lpCur=Renderer();
  while(lpCur->Renderer()->Renderer()) lpCur=lpCur->Renderer();
  return lpCur;
 }
 return this;
};


