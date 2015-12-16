
#include "../../WTBamboo.h"

cVoxelModel::cVoxelModel(){}

cVoxelModel::cVoxelModel(vRenderNode *lpRenderer) : cModel(lpRenderer){}

cVoxelModel::cVoxelModel(cCamera *lpCamera) : cModel(lpCamera){}

void cVoxelModel::GenerateVoxelMesh(cMesh *lpMesh)
{
	mcVoxelModel = cVoxelOctTreeBase<uint8>::GenerateTree(lpMesh);
	Mesh(mcVoxelModel->GenerateMeshFromTree());
}