#include "../WTBamboo.h"

vRenderNode* vRenderNode::Renderer(){return mpRenderer;};
void vRenderNode::RenderPainter(){};
void vRenderNode::UpdateCache()
{
	mmCache=_MATRIX_STACK->Current();
	mmTotalCache=_COMBINED_MATRIX;
	mmTotalCache.Multiply(mmCache);
}
float* vRenderNode::GetPos(){return Position();};
float* vRenderNode::GetCachedGlobalMatrix(){return mmCache.Matrix();}

void vRenderNode::Stop()
{

}

cCamera *vRenderNode::Camera()
{
    return mpCamera;
}

cVariableStore* vRenderNode::Variables(){return 0;}


