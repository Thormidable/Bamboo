
#pragma once

/**
* \brief A standard Textured Model renderable object.
*/
class cVoxelModel :public cModel
{

	
public:
 /// cModel constructor
 cVoxelModel();
 /// cModel constructor. Will be owned by lpRenderer.
 cVoxelModel(vRenderNode *lpRenderer);
 /// cModel constructor. Will be owned by the cRenderNode of the cCamera lpCamera.
 cVoxelModel(cCamera *lpCamera);

 void GenerateVoxelMesh(cMesh *lpMesh);

 cVoxelOctTree<uint8> mcVoxelModel;
};

