#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

cNodeListNode::~cNodeListNode()
{
mpObject=0;
}

cNodeListNode::cNodeListNode(vRenderObject *lpObject,uint8 liLevel)
{
    mpObject=lpObject;
    miLevel=liLevel;
}

cNodeListNode::cNodeListNode()
{
  mpObject=0;
  miLevel=0;
}

void cNodeListNode::LoadNode(cMeshTreeNode *lpNode)
{
cModel *lpObject=dynamic_cast<cModel*>(mpObject);
if(lpObject)
{

if(lpNode->miFormat&WT_MESHTREE_SHADER)
		lpObject->Shader(lpNode->ShaderProgram());

	if(lpNode->miFormat&WT_MESHTREE_MESH)
		lpObject->Mesh(lpNode->Mesh());

	if(lpNode->miFormat&WT_MESHTREE_TEXTURE)
	{
		lpObject->AddTexture("Texture0",lpNode->Texture());
	}

	if(lpNode->miFormat&WT_MESHTREE_LEVEL)
		miLevel=lpNode->miLevel;

    //Set it to be Identity.
	lpObject->Identity();

	if(lpNode->miFormat&WT_MESHTREE_ROTATION)
	{
	    //Yaw
	    lpObject->RotateY(lpNode->mpRotation[0]);
	    //Pitch
	    lpObject->RotateX(lpNode->mpRotation[1]);
	    //Roll
	    lpObject->RotateZ(lpNode->mpRotation[2]);
	}

	if(lpNode->miFormat&WT_MESHTREE_POSITION)
        lpObject->Position(lpNode->mpPosition);

}
}

void cNodeList::LoadTree(string lcTree)
{
 LoadTree(_GET_MODELLIST_FILE(lcTree.c_str()));
}

float cNodeList::lsPosition[16];

cNodeList::~cNodeList()
{
    DeleteAll();
    mpCamera=0;
}


void cNodeList::DeleteAll()
{
	mpList.DeleteAll();
}



cNodeList::cNodeList(uint32 liLength)
{
 mpCamera=cCamera::Instance();
 mpRenderer=cCamera::Instance()->RenderList();
 mcOwnerNode=mpRenderer->Add(this);

	InitialiseList(liLength);
}

cNodeList::cNodeList(cMeshTree *lpTree,cCamera *lpCamera)
{
  mpCamera=lpCamera;
  mpRenderer=lpCamera->RenderList();
  mcOwnerNode=mpRenderer->Add(this);

	mpMeshTree=lpTree;
	LoadTree(lpTree);
};
cNodeList::cNodeList(uint32 liLength,cCamera *lpCamera)
{
  mpCamera=lpCamera;
  mpRenderer=lpCamera->RenderList();
  mcOwnerNode=mpRenderer->Add(this);

 Identity();
 InitialiseList(liLength);
};

cNodeList::cNodeList(uint32 liLength,vRenderNode *lpRenderer)
{
  mpRenderer=lpRenderer;
  mpCamera=mpRenderer->Camera();
  mcOwnerNode=lpRenderer->Add(this);

 Identity();
 InitialiseList(liLength);
}

cNodeList::cNodeList(bool lpTopLevel,uint32 liLength,cCamera *lpCamera)
{
  mpRenderer=0;
  mcOwnerNode.Node=0;
  mpCamera=lpCamera;

   Identity();
 InitialiseList(liLength);

};

cNodeList::cNodeList(cMeshTree *lpTree)
{
    mpCamera=cCamera::Instance();
	 mpRenderer=mpCamera->RenderList();

 	mcOwnerNode=mpRenderer->Add(this);
	mpMeshTree=lpTree;
	LoadTree(lpTree);
	Identity();
}

cNodeList::cNodeList(cMeshTree *lpTree,vRenderNode *lpRenderer)
{

  mpRenderer=lpRenderer;
  mcOwnerNode=lpRenderer->Add(this);
  mpCamera=mpRenderer->Camera();

	mpMeshTree=lpTree;
	LoadTree(lpTree);
	Identity();
}

void cNodeList::LoadTree(cMeshTree *lpTree)
{
    InitialiseList(lpTree->TreeSize());
    uint32 liCount;
    for(liCount=0;liCount<lpTree->TreeSize();++liCount)
    {
      new cModel(this);
      mpList[liCount]->LoadNode(lpTree->NodeList(liCount));
    }
}

void cNodeList::InitialiseList(uint32 liLength)
{
 mpList.Init(liLength);

 Identity();
}

cRenderOwner cNodeList::Add(vRenderObject *lpNew,uint8 miLevel)
{
	cRenderOwner mcOwner;
	mcOwner.List=new cNodeListNode(lpNew,miLevel);
    mpList.Add(mcOwner.List);
	return mcOwner;
}

void cNodeList::Remove(cRenderOwner lpCurrent)
{
    mpList.Remove(lpCurrent.List);
}

void cNodeList::StartKillAll()
{
    KillAll();
    if(mpRenderer) mpRenderer->Remove(mcOwnerNode);
    else trace("This is the Camera cNodeList. Cannot Delete.");
}

void cNodeList::KillAll()
{
    uint32 liCount;
    for(liCount=0;liCount<mpList.Items();++liCount)
    {
        mpList[liCount]->mpObject->KillAll();
        delete mpList[liCount];
        mpList.ZeroItem(liCount);
    }
    mpList.SetItems(0);


}


void cNodeList::RecalculateTotalMatrix()
{
uint32 liListPos;
 for(liListPos=0;liListPos<mpList.Items();++liListPos)
 {
  if(mpList[liListPos]->mpObject)
  {
	mpList[liListPos]->mpObject->RecalculateTotalMatrix();
  }
 }

}


void cNodeList::CalculateMatrices()
{
  uint32 liListPos;
  miLevel=0;

  UpdateMatrix();
  UpdateCache();

  _MATRIX_STACK->Push();

 for(liListPos=0;liListPos<mpList.Items();++liListPos)
 {

  if(mpList[liListPos]->mpObject)
  {

	// If need to add another level
	if(mpList[liListPos]->miLevel>miLevel)
	{
		while(mpList[liListPos]->miLevel>miLevel)
		{
			_MATRIX_STACK->Push();
			++miLevel;
		}
	}
	else
	{
		if(mpList[liListPos]->miLevel<miLevel)
		{
			while(mpList[liListPos]->miLevel<miLevel)
			{
				_MATRIX_STACK->Pop();
				--miLevel;
			}
		}
		else
		{
				// If Level is correct
				_MATRIX_STACK->Pop();
				_MATRIX_STACK->Push();
		}
	}
	mpList[liListPos]->mpObject->UpdateMatrix();
	mpList[liListPos]->mpObject->CalculateMatrices();
  }
 }
 while(miLevel>0){ _MATRIX_STACK->Pop(); --miLevel;}

//AdditionalRenderFunctions();
  _MATRIX_STACK->Pop();

}


void cNodeList::RenderToPainter()
{
  uint32 liListPos;
  miLevel=0;

  UpdateMatrix();
  UpdateCache();

  _MATRIX_STACK->Push();

 for(liListPos=0;liListPos<mpList.Items();++liListPos)
 {

  if(mpList[liListPos]->mpObject)
  {

	// If need to add another level
	if(mpList[liListPos]->miLevel>miLevel)
	{
		while(mpList[liListPos]->miLevel>miLevel)
		{
			_MATRIX_STACK->Push();
			++miLevel;
		}
	}
	else
	{
		if(mpList[liListPos]->miLevel<miLevel)
		{
			while(mpList[liListPos]->miLevel<miLevel)
			{
				_MATRIX_STACK->Pop();
				--miLevel;
			}
		}
		else
		{
				// If Level is correct
				_MATRIX_STACK->Pop();
				_MATRIX_STACK->Push();
		}
	}


	mpList[liListPos]->mpObject->RenderToPainter();
	mpList[liListPos]->mpObject->UpdateCache();


  }
 }
 while(miLevel>0){ _MATRIX_STACK->Pop(); --miLevel;}

//AdditionalRenderFunctions();
  _MATRIX_STACK->Pop();

}


vRenderObject *cNodeList::GetListItem(uint16 liPos)
{
    return mpList[liPos]->mpObject;
}

uint8 cNodeList::GetItemLevel(uint16 liPos)
{
    return mpList[liPos]->miLevel;
}


uint32 cNodeList::ListLength()
{
  return mpList.Items();

}

/*
void cNodeList::UpdateSize()
{
  float lfPos[miLength][4];
 uint32 liListPos;
 uint32 miLevel=0;
for(liListPos=0;liListPos<miLength;++liListPos)
 {
	  miLevel=mpList[liListPos].miLevel;
	  lfPos[miLevel][0]=lfPos[miLevel-1][0]+mpList[liListPos].mmMatrix.Position()[0];
	  lfPos[miLevel][1]=lfPos[miLevel-1][1]+mpList[liListPos].mmMatrix.Position()[1];
	  lfPos[miLevel][2]=lfPos[miLevel-1][2]+mpList[liListPos].mmMatrix.Position()[2];
	  lfPos[miLevel][3]=lfPos[miLevel][0]*lfPos[miLevel][0]+lfPos[miLevel][1]*lfPos[miLevel][1]+lfPos[miLevel][2]*lfPos[miLevel][2];
	    if(mpList[liListPos].mpMesh)
	    {
	      if(lfPos[miLevel][3]+mpList[liListPos].Mesh()->GetSize()>mfSize) mfSize=lfPos[miLevel][3]+mpList[liListPos].Mesh()->GetSize();
	    }
 }

}
*/


cRenderOwner cNodeList::Add(vRenderObject *lpNew){return Add(lpNew,0);};


 void cNodeList::SetLevel(uint16 liPos,uint8 liCom)
 {
  mpList[liPos]->miLevel=liCom;
 }


#endif
