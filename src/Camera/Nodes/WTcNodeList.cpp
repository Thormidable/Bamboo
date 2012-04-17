#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

cNodeListNode::~cNodeListNode()
{
delete mpObject;
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


cNodeList::cNodeList(const char *lsTree)
{
 mpMeshTree=_GET_MODELLIST_FILE(lsTree);
 LoadTree(mpMeshTree);
};
cNodeList::cNodeList(const char *lpTree,vRenderNode *lpRenderer) : vRenderNode(lpRenderer)
{
	mpMeshTree=_GET_MODELLIST_FILE(lpTree);
	LoadTree(mpMeshTree);
};

cNodeList::cNodeList(const char *lpTree,cCamera *lpCamera) : vRenderNode(lpCamera)
{
	mpMeshTree=_GET_MODELLIST_FILE(lpTree);
	LoadTree(mpMeshTree);
};

cNodeList::cNodeList(uint32 liLength)
{
 InitialiseList(liLength);
}

cNodeList::cNodeList(cMeshTree *lpTree,cCamera *lpCamera) : vRenderNode(lpCamera)
{
 	mpMeshTree=lpTree;
	LoadTree(lpTree);
};
cNodeList::cNodeList(uint32 liLength,cCamera *lpCamera) : vRenderNode(lpCamera)
{
 InitialiseList(liLength);
};

cNodeList::cNodeList(uint32 liLength,vRenderNode *lpRenderer) : vRenderNode(lpRenderer)
{
 InitialiseList(liLength);
}

cNodeList::cNodeList(bool lpTopLevel,uint32 liLength,cCamera *lpCamera) : vRenderNode(lpTopLevel,lpCamera)
{
 InitialiseList(liLength);
};

cNodeList::cNodeList(cMeshTree *lpTree)
{
	mpMeshTree=lpTree;
	LoadTree(lpTree);
	Identity();
}

cNodeList::cNodeList(cMeshTree *lpTree,vRenderNode *lpRenderer)  : vRenderNode(lpRenderer)
{
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
	mcOwner.Node=0;
    mpList.Add(mcOwner.List);
	return mcOwner;
}

void cNodeList::Delete(cRenderOwner lpCurrent)
{
    mpList.Delete(lpCurrent.List);
}

void cNodeList::StartKillAll()
{
    KillAll();
    if(mpRenderer) mpRenderer->Delete(mcOwnerNode);
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
	mmTotalCache=_COMBINED_MATRIX;
	mmTotalCache.Multiply(mmCache);
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


cRenderOwner cNodeList::Add(vRenderObject *lpNew){return Add(lpNew,0);};


 void cNodeList::SetLevel(uint16 liPos,uint8 liCom)
 {
  mpList[liPos]->miLevel=liCom;
 }


 cMatrix4 *cNodeList::CalculateGlobalMatrix()
 {


	if(Renderer())
	{
		cMatrix4 *lpMat=Renderer()->CalculateGlobalMatrix();
		if(lpMat)
		{
			mmCache=Renderer()->CalculateGlobalMatrix();
			_MATRIX_STACK->Push();
			_MATRIX_STACK->SetMatrix(mmCache.Matrix());
			CalculateMatrices();
			_MATRIX_STACK->Pop();
     		return 0;
		}
		return 0;
	}
	else
	{
		_MATRIX_STACK->Push();
		_MATRIX_STACK->SetMatrix(mmCache.Matrix());
		CalculateMatrices();
		_MATRIX_STACK->Pop();
     	return 0;
	}
 }

cRenderOwner cNodeList::MoveItem(vRenderObject *lpObj, vRenderNode *lpRenderer)
{
 mpList.StripItem(lpObj->RenderOwner().List);
 return lpRenderer->Add(lpObj);
};


void cNodeList::MoveAll(vRenderNode *lpRender)
{
 for(uint32 liListPos=0;liListPos<mpList.Items();++liListPos)
 {
	vRenderObject *lpObj=mpList[liListPos]->mpObject;
	lpObj->RenderOwner(lpRender->Add(lpObj));
	mpList.ZeroItem(liListPos);
 }
 mpList.SetItems(0);
};

vRenderObject *cNodeList::FindStart()
{
 miCursor=0;
 if(mpList.Items())
 {
  return mpList[0]->mpObject;
 }
 return 0;
};

vRenderObject *cNodeList::FindNext()
{
 ++miCursor;
 if(miCursor<mpList.Items())
 {
  return mpList[miCursor]->mpObject;
 }
 return 0;
};

bool cNodeList::ContainsItems()
{
 return mpList.Items();
};

float cNodeList::GetSize()
{
 float lfSize=0.0f;
 if(mpList.Items())
 {
  for(uint32 liCount=0;liCount<mpList.Items();++liCount)
  {
      float lfTemp=mpList[liCount]->mpObject->GetSize()+mpList[liCount]->mpObject->Distance();
      if(lfTemp>lfSize) lfSize=lfTemp;
  }
 }
    return lfSize;
};

double cNodeList::GetSizeSq()
{
 double lfSize=0.0f;
 if(mpList.Items())
 {
  for(uint32 liCount=0;liCount<mpList.Items();++liCount)
  {
      double lfTemp=mpList[liCount]->mpObject->GetSize()+mpList[liCount]->mpObject->DistanceSq();
      if(lfTemp>lfSize) lfSize=lfTemp;
  }
 }
 return lfSize;
};

void cNodeList::TreeProcessUserSignal(SIGNAL lsSignal,void *lpData)
{
 if(mpProcess) mpProcess->UserSignal(lsSignal,lpData);
 if(mpList.Items())
 {
  for(uint32 liCount=0;liCount<mpList.Items();++liCount)
  {
      mpList[liCount]->mpObject->TreeProcessUserSignal(lsSignal,lpData);
  }
 }
};

void cNodeList::TreeProcessSignal(SIGNAL lsSignal)
{
 if(mpProcess) mpProcess->Signal(lsSignal);
 if(mpList.Items())
 {
  for(uint32 liCount=0;liCount<mpList.Items();++liCount)
  {
       mpList[liCount]->mpObject->TreeProcessSignal(lsSignal);
  }
 }
}


#endif

