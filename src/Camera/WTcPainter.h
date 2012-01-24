
#ifndef __WTCPAINTER_H__
#define __WTCPAINTER_H__

#define WT_PAINTER_COMMANDLESS 0

/*
* When WT_USE_PAINTER_ALGORITHM is set to true. cRenderObjects will render to this class instead of screen.
* Once all the cRenderObjects have been rendered into this class it will use an optimised Radix sort to sort them to create an efficient rendering order.
*/
class cPainter
{
 // This is a pointer to the current instance of cPainter.
 static cPainter *mpInstance;
 cPainter();

 // This is a pointer which will point to an array of buckets to group objects as they are sorted.
 cRenderPointer **mpBucket;
 // This is the size of the list of cRenderObjects.
 uint32 miSize;
 // This is the current number of items in mpList.
 uint32 miPos;


 // This is a pointer to the actual list of cRenderObjects.
 cRenderPointer **mpList;

public:
 ~cPainter();

 static void *lpValue;
 // This will return the current instance of the cPainter algorithm, if there is no current instance a new one will be created. This should always be used and NOT cPainter();
 static cPainter *Instance();

//This function will add the cRenderPointer Object pointed to by lfData.
void Add(cRenderPointer *lfData);

 //void Remove(cRenderPointer **lfSlot);
void Remove(cRenderPointer *lfSlot);
 // This will reset the rendering states in OpenGL to everything off for plain simple objects.
 void Reset();
 // This will resize the array of cRenderPointer to change the number of cRenderObjects that can be held.
 void Resize(uint32 liSize);
 // This will sort the array mpList based on object shader program.
 void SortByShader();
 // This will sort the array mpList based on object distance from the camera.
 void SortByDistance();
 // This will sort the array mpList based on the texture assigned to slot liTexSlot
 void SortByTexture(uint8 liTexSlot);
 // This will sort the array mpList based on the alpha value that each object uses.
 void SortByAlpha();
 // This will comapre the ShaderProgram of the next object with the previous object and will set the correct shader or fixed function to use.
 void ShaderState(cShaderProgram *mpCurrent,cShaderProgram *mpLast);
 //This will control Depth Testing for transparent and other objects.
 void DepthState(bool mpCurrent,bool mpLast);
 // This will actually render an object from mpList to the screen.
 void Render();



};


#endif
