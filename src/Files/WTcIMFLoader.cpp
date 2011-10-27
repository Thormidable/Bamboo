#include "../WTDivWin.h"

using namespace std;

void cIMF::LoadIMF(const char *lpPath)
{
	printf("Load File %s\n",lpPath);
	uint32 liTemp;

	ifstream FileStream;
	FileStream.open(lpPath,ios::binary);

	if(!FileStream.is_open())
	{
		string msg("LoadIMF couldn't open ");
		msg=msg+lpPath;
		trace(msg);
		throw CException(msg);
		return;
	}

	while(!FileStream.eof())
	{


		FileStream.read((char *) &liTemp,sizeof(uint32));
		if(liTemp==IMF_TYPE_EOF) break;

		if(liTemp==IMF_TYPE_MODEL)
		{
			trace("Type Model")
			cMeshArray lpDataStore;
			lpDataStore.LoadIMF(FileStream);
			new cMesh(&lpDataStore);
		}
		else if(liTemp==IMF_TYPE_TEXTURE)
		{
			trace("Type Texture")
			cTextureArray lpTexture;
			FileStream.ignore(sizeof(uint32));

			FileStream.read((char *) &liTemp,sizeof(uint32));
			lpTexture.mpRef=new char[liTemp+1];
			FileStream.read((char *) lpTexture.mpRef,liTemp*sizeof(char));
			lpTexture.mpRef[liTemp]=0;

			FileStream.read((char *) &(lpTexture.miWidth),sizeof(uint32));
			FileStream.read((char *) &(lpTexture.miHeight),sizeof(uint32));
			FileStream.read((char *) &(lpTexture.miDepth),sizeof(uint32));

			lpTexture.mpData=new uint8[lpTexture.miWidth*lpTexture.miHeight*lpTexture.miDepth>>3];
			FileStream.read((char *) lpTexture.mpData,lpTexture.miWidth*lpTexture.miHeight*lpTexture.miDepth>>3);

			new cTexture(&lpTexture);
		}
		else if(liTemp==IMF_TYPE_FONT)
		{
			trace("Type Font")
			cTextureArray lpTexture;
			FileStream.ignore(sizeof(uint32));

			FileStream.read((char *) &liTemp,sizeof(uint32));
			lpTexture.mpRef=new char[liTemp+1];
			FileStream.read((char *) lpTexture.mpRef,liTemp*sizeof(char));
			lpTexture.mpRef[liTemp]=0;

			FileStream.read((char *) &(lpTexture.miWidth),sizeof(uint32));
			FileStream.read((char *) &(lpTexture.miDepth),sizeof(uint32));

			lpTexture.mpData=new uint8[64*lpTexture.miWidth*lpTexture.miWidth*lpTexture.miDepth>>3];
			FileStream.read((char *) lpTexture.mpData,64*lpTexture.miWidth*lpTexture.miWidth*lpTexture.miDepth>>3);

			new cFont(&lpTexture);
		}
		else if(liTemp==IMF_TYPE_TREE)
		{
			trace("Type Tree")
			cMeshTreeArray lpTree;

			//Skip uint32 holding the Size of Block
			FileStream.ignore(sizeof(uint32));

			//Read The Objects Reference
			FileStream.read((int8 *) &liTemp,sizeof(uint32));
			lpTree.mpRef=new char[liTemp+1];
			FileStream.read((int8 *) lpTree.mpRef,sizeof(int8)*liTemp);
			lpTree.mpRef[liTemp]=0;

			//Read the Tree length and assign memory
			FileStream.read((int8 *) &(lpTree.miTreeLength),sizeof(uint32));
			lpTree.mpList=new cMeshTreeNode[lpTree.miTreeLength];

			//Read all the Tree nodes
			for(liTemp=0;liTemp<lpTree.miTreeLength;++liTemp)
			{
				lpTree.mpList[liTemp].ReadIMF(FileStream);
			}

			new cMeshTree(&lpTree);
		}
		else if(liTemp==IMF_TYPE_MATRIX_LANDSCAPE)
		{
			trace("Type Matrix Landscape")
			cmLandscapeArray lpLandscape;
			liTemp=0;



			//Ignore Block Size
			FileStream.ignore(sizeof(uint32));

			//Read the Reference
			FileStream.read((int8 *) &liTemp,sizeof(uint32));
			lpLandscape.mpRef=new char[liTemp+1];
			FileStream.read((int8*)lpLandscape.mpRef,sizeof(int8)*liTemp);
			lpLandscape.mpRef[liTemp]=0;

			//Extract the number of tiles in the landscape
			FileStream.read((int8 *) &lpLandscape.miXSteps,sizeof(uint32));
			FileStream.read((int8 *) &lpLandscape.miZSteps,sizeof(uint32));

			//Extract the Tile Sizes for the landscape
			FileStream.read((int8 *) &lpLandscape.mfXSize,sizeof(float));
			FileStream.read((int8 *) &lpLandscape.mfZSize,sizeof(float));

			//Extract the Height Range for the Landscape
			FileStream.read((int8 *) &lpLandscape.mfHeightRange,sizeof(float));

			//Extract the vertex positions for the Landscape
			lpLandscape.mpVertex=new float[lpLandscape.miXSteps*lpLandscape.miZSteps*3];
			FileStream.read((int8 *) lpLandscape.mpVertex,sizeof(float)*3*lpLandscape.miXSteps*lpLandscape.miZSteps);


			new cLandscapeMeshFile(&lpLandscape);

		}
		else if(liTemp==IMF_TYPE_SHADER)
		{
			trace("Type Shader Object")
			cShaderArray lShaderArray;
			lShaderArray.LoadIMF(FileStream);
			new cShader(&lShaderArray);
		}
		else if(liTemp == IMF_TYPE_SHADER_PROGRAM)
		{
			trace("Type Shader Program Object");
			cShaderProgram *lpProgram = new cShaderProgram;
			lpProgram->LoadIMF(FileStream);
		}
		else if(liTemp == IMF_TYPE_COLLISION_OBJECT)
		{
		    trace("Type Collision Mesh")
		    //cCollisionArray lpArray;
		    //lpArray.LoadIMF(FileStream);
		    //new cCollisionMesh(&lpArray);
		    cMeshFileCollision *lpTemp;
		    lpTemp=new cMeshFileCollision();
		    lpTemp->LoadIMF(FileStream);
		}
		else
		{
			trace("Type not found")
			//If FileType not recognised
			FileStream.read((char *) &liTemp,sizeof(uint32));
			FileStream.ignore(liTemp);
		}
	}

	FileStream.close();
}


