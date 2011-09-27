#ifndef __WTCMESHTREE_H__
#define __WTCMESHTREE_H__

#define WT_MESHTREE_MESH 0x1
#define WT_MESHTREE_TEXTURE 0x2
#define WT_MESHTREE_LEVEL 0x4
#define WT_MESHTREE_POSITION 0x8
#define WT_MESHTREE_ROTATION 0x10
#define WT_MESHTREE_TOPVALUE 0x20

using namespace std;
/**
*\brief This will load the information from an IMF file to be handed to a cMeshTree()
*This object will store the data for a cMeshTree() object from an IMF file.
*/
class cMeshTreeArray
{
public:
 ///This will point to an array of cMeshTreeNode() objects.
 cMeshTreeNode *mpList;
 ///This is the number of cMeshTreeNode() objects in the tree.
 uint32 miTreeLength;
 ///This will point to an array storing the string reference for this object.
 char *mpRef;
 ///This is a public constructor, it will initialise the data for this class.
 cMeshTreeArray();
 ///This is a public deconstructor.
 ~cMeshTreeArray();
};
/**
*\brief This will store the data for a cModelList()

*/
class cMeshTree : public vMeshTree
{
  ///This points to an Array of cMeshTreeNode() objects.
   cMeshTreeNode *mpList;
  /// This stores the length of the Tree!!! SOD.
   uint32 miTreeLength;

public:
 ///This will extract the data from the cMeshTreeArray() lpArray.
 cMeshTree(cMeshTreeArray *lpArray);

 ~cMeshTree();

 /// This is actually the length of the Tree!!! SOD.
 uint32 Size(){return miTreeLength;};
  ///This will return a pointer to the first item of mpList.
 cMeshTreeNode *NodeList(){return mpList;};
 ///This will return a pointer to the cMeshTreeNode in position liCount in mpList.
 cMeshTreeNode *NodeList(uint32 liCount){return &mpList[liCount];};
 ///This will return the spatial size of this cMeshTree()
 float GetSize(){return mfSize;};
 ///This will calculate the spatial size of this cMeshTree()
 float FindSize();
};

#endif
