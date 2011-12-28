#include "../../WTDivWin.h"

cModelListNode::~cModelListNode()
{
_PAINTER->Remove(mpPainterData);

}

cModelListNode::cModelListNode()
{
 mpMesh=0;
 mpTexture=0;
 mmMatrix.Identity();
 miLevel=0;
 mfSize=0.0f;
	mpPainterData= new cRenderPointer();
	_PAINTER->Add(mpPainterData);

}

void cModelListNode::LoadNode(cMeshTreeNode *lpNode)
{

	if(lpNode->miFormat&WT_MESHTREE_MESH)
		mpMesh=lpNode->Mesh();

	if(lpNode->miFormat&WT_MESHTREE_TEXTURE)
		mpTexture=lpNode->Texture();

	if(lpNode->miFormat&WT_MESHTREE_LEVEL)
		miLevel=lpNode->miLevel;

	if(lpNode->miFormat&WT_MESHTREE_ROTATION)
	{
		memcpy(&mmMatrix[0],lpNode->mpRotation,sizeof(float)*3);
		memcpy(&mmMatrix[4],&(lpNode->mpRotation[3]),sizeof(float)*3);
		memcpy(&mmMatrix[8],&(lpNode->mpRotation[6]),sizeof(float)*3);
	}

	if(lpNode->miFormat&WT_MESHTREE_POSITION)
		memcpy(&mmMatrix[12],lpNode->mpPosition,sizeof(float)*3);
}

float cModelList::lsPosition[16];

cModelList::~cModelList()
{
 if (mpList) {delete []mpList; mpList=0;}
}

cModelList::cModelList(uint32 liLength)
{
	Initialise(liLength);
}

cModelList::cModelList(cRenderNode *lpRenderer,uint32 liLength) : cRenderObject(lpRenderer){ Initialise(liLength); }


cModelList::cModelList(cMeshTree *lpTree)
{
	mpMeshTree=lpTree;
	LoadTree(lpTree);
}

cModelList::cModelList(cRenderNode *lpRenderer,cMeshTree *lpTree) : cRenderObject(lpRenderer)
{
	mpMeshTree=lpTree;
	LoadTree(lpTree);
}

void cModelList::LoadTree(cMeshTree *lpTree)
{
	uint32 liCount;
	mpMeshTree=lpTree;
	miLength=lpTree->Size();
	mpList=new cModelListNode[miLength];
	for(liCount=0;liCount<miLength;++liCount) { mpList[liCount].LoadNode(lpTree->NodeList(liCount)); }

	Identity();

}

void cModelList::Initialise(uint32 liLength)
{
 miLength=liLength;
 mpList=new cModelListNode[miLength];
 for(liLength=0;liLength<miLength;++liLength)
 {
  mpList[liLength].mpTexture=0;
  mpList[liLength].mpMesh=0;
  mpList[liLength].miLevel=0;
  mpList[liLength].mmMatrix.Identity();
 }
 Identity();
}

void cModelList::SetTexture(uint32 liPos, cTexture *lpTexture)
{
 if(liPos<miLength) mpList[liPos].mpTexture=lpTexture;
}

void cModelList::SetTransparency(uint32 liPos,bool lbAlpha)
{
    if(liPos<miLength) mpList[liPos].mbAlpha=lbAlpha;
}

void cModelList::SetShader(uint32 liPos, cShaderProgram *lpShader)
{
 if(liPos<miLength) mpList[liPos].mpShader=lpShader;
}

void cModelList::SetMesh(uint32 liPos, cMesh *lpMesh)
{
 if(liPos<miLength) mpList[liPos].mpMesh=lpMesh;
}

void cModelList::SetCommand(uint32 liPos,uint8 liCom)
{
 mpList[liPos].miLevel=liCom;
}


void cModelList::RenderToPainter()
{
  uint32 liListPos;
  miLevel=0;
  Display();
  UpdateMatrix();
  glPushMatrix();
 for(liListPos=0;liListPos<miLength;++liListPos)
 {
  if(mpList[liListPos].mpMesh)
  {
	// If need to add another level
	if(mpList[liListPos].miLevel>miLevel)
	{
		while(mpList[liListPos].miLevel>miLevel)
		{
			glPushMatrix();
			++miLevel;
		}
	}
	else
	{
		//If too many Levels
		if(mpList[liListPos].miLevel<miLevel)
		{
			while(mpList[liListPos].miLevel<miLevel)
			{
				glPopMatrix();
				--miLevel;
			}
		}
		else
		{
			// If Level is correct
			glPopMatrix();
			glPushMatrix();
		}
	}
	RenderNodePainter(liListPos);
  }
 }
 while(miLevel>0){ glPopMatrix(); --miLevel;}
//  UpdateSize();
AdditionalRenderFunctions();
  glPopMatrix();

}

void cModelList::RenderNodePainter(uint8 liListPos)
{
float Temp[16];
		mpList[liListPos].mmMatrix.UpdateMatrix();
		glGetFloatv(GL_MODELVIEW_MATRIX,Temp);

 mpList[liListPos].mpPainterData->SetObject(this);
 mpList[liListPos].mpPainterData->SetTexture(mpList[liListPos].mpTexture->TextureNumber());
 mpList[liListPos].mpPainterData->SetShader(mpList[liListPos].mpShader);
 mpList[liListPos].mpPainterData->SetAlpha(mpList[liListPos].mpShader);
 mpList[liListPos].mpPainterData->SetLevel(liListPos);


 mpList[liListPos].mpPainterData->RenderAgain();
		//cPainter::Instance()->Add(lcTemp);
}

void cModelList::RenderPainter(uint8 liLevel)//cMesh *lpMesh)
{
  PrepareMaterial();
  mpList[liLevel].mpMesh->RenderMesh();
}

void cModelList::RenderCode(cModelListNode *lpNode)
{
 glEnable(GL_TEXTURE_2D);

  lpNode->mmMatrix.UpdateMatrix();
  //mpList[liPos].UpdateMatrix();
  PrepareMaterial();

  lpNode->mpTexture->BindTexture();

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  if(lpNode->mpShader) lpNode->mpShader->Use();
  else _USE_FIXED_FUNCTION();

 lpNode->mpMesh->RenderMesh();

}



cMatrix4 &cModelList::GetMatrix(uint32 liPos)
{
  return mpList[liPos].mmMatrix;

}

uint32 cModelList::ListLength()
{
  return miLength;

}

/*
void cModelList::UpdateSize()
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
