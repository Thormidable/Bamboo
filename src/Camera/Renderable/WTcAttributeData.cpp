
#include "../../WTBamboo.h"
cTBNVectors::cTBNVectors(cMesh *lpMesh)
 {
	Tangent=new cAttributeData<c3DVf>(lpMesh->Verteces(),"Bb_Tangent");
	Bitangent=new cAttributeData<c3DVf>(lpMesh->Verteces(),"Bb_Binormal");
	Normal=new cAttributeData<c3DVf>(lpMesh->Verteces(),"Bb_Normal");
	GenerateTBNVectors(lpMesh);
 };

 cTBNVectors::~cTBNVectors()
 {
    delete Tangent;
    delete Bitangent;
    delete Normal;
    Tangent=Bitangent=Normal;
 };

 void cTBNVectors::LinkToShader(cRenderObject *lpObj)
 {
	Tangent->LinkToShader(lpObj);
	Bitangent->LinkToShader(lpObj);
	Normal->LinkToShader(lpObj);
 };

void cTBNVectors::GenerateTBNVectors(cMesh *lpMesh)
 {
	if(lpMesh->UVData())
	{
	for(uint32 liCount=0;liCount<lpMesh->Faces();++liCount)
	{
		c3DVf lpVertex[3];

		lpVertex[0]=lpMesh->Normal(lpMesh->Face(liCount,0));
		lpVertex[1]=lpMesh->Normal(lpMesh->Face(liCount,1));
		lpVertex[2]=lpMesh->Normal(lpMesh->Face(liCount,2));
/*
        printf("\n\nNormal 0 : %f %f %f\n",lpVertex[0].X(),lpVertex[0].Y(),lpVertex[0].Z());
        printf("Normal 1 : %f %f %f\n",lpVertex[1].X(),lpVertex[1].Y(),lpVertex[1].Z());
        printf("Normal 2 : %f %f %f\n",lpVertex[2].X(),lpVertex[2].Y(),lpVertex[2].Z());
*/
		lpVertex[0]=lpMesh->Vertex(lpMesh->Face(liCount,0));
		lpVertex[1]=lpMesh->Vertex(lpMesh->Face(liCount,1));
		lpVertex[2]=lpMesh->Vertex(lpMesh->Face(liCount,2));
/*
        printf("Vertex 0 : %f %f %f\n",lpVertex[0].X(),lpVertex[0].Y(),lpVertex[0].Z());
        printf("Vertex 1 : %f %f %f\n",lpVertex[1].X(),lpVertex[1].Y(),lpVertex[1].Z());
        printf("Vertex 2 : %f %f %f\n",lpVertex[2].X(),lpVertex[2].Y(),lpVertex[2].Z());
*/
		c2DVf lpUV[3];
		lpUV[0]=lpMesh->UV(lpMesh->Face(liCount,0));
		lpUV[1]=lpMesh->UV(lpMesh->Face(liCount,1));
		lpUV[2]=lpMesh->UV(lpMesh->Face(liCount,2));

/*
        printf("UV 0 : %f %f\n",lpUV[0].X(),lpUV[0].Y());
        printf("UV 1 : %f %f\n",lpUV[1].X(),lpUV[1].Y());
        printf("UV 2 : %f %f\n",lpUV[2].X(),lpUV[2].Y());
*/
		c3DVf v2v1=lpVertex[1]-lpVertex[0];
		c3DVf v3v1=lpVertex[2]-lpVertex[0];

		// printf("V0->V1 : %f %f %f\n",v2v1.X(),v2v1.Y(),v2v1.Z());
		// printf("V0->V2 : %f %f %f\n",v3v1.X(),v3v1.Y(),v3v1.Z());

		float c2c1_T = lpUV[1].X()-lpUV[0].X();
		float c2c1_B = lpUV[1].Y()-lpUV[0].Y();

		float c3c1_T = lpUV[2].X()-lpUV[0].X();
		float c3c1_B = lpUV[2].Y()-lpUV[0].Y();

		//printf("UV0 ->UV1 : %f %f\n",c2c1_T,c2c1_B);
		//printf("UV0 ->UV2 : %f %f\n",c3c1_T,c3c1_B);


		float lfDenominator=c2c1_T*c3c1_B-c3c1_T*c2c1_B;
       // printf("lfDenominator : %f\n",lfDenominator);
		if(lfDenominator==0.0f)
		{

			Tangent->Get(lpMesh->Face(liCount,2))=Tangent->Get(lpMesh->Face(liCount,1))=Tangent->Get(lpMesh->Face(liCount,0))=c3DVf(1.0f,0.0f,0.0f);
			Bitangent->Get(lpMesh->Face(liCount,2))=Bitangent->Get(lpMesh->Face(liCount,1))=Bitangent->Get(lpMesh->Face(liCount,0))=c3DVf(0.0f,1.0f,0.0f);
			Normal->Get(lpMesh->Face(liCount,2))=Normal->Get(lpMesh->Face(liCount,1))=Normal->Get(lpMesh->Face(liCount,0))=c3DVf(0.0f,0.0f,1.0f);
		}
		else
		{
			lfDenominator=1.0f/lfDenominator;

			lpVertex[0]=c3DVf(c3c1_B*v2v1.X()-c2c1_B*v3v1.X(),
												   c3c1_B*v2v1.Y()-c2c1_B*v3v1.Y(),
												   c3c1_B*v2v1.Z()-c2c1_B*v3v1.Z());

			lpVertex[1]=c3DVf(c2c1_T*v3v1.X()-c3c1_T*v2v1.X(),
												   	 c2c1_T*v3v1.Y()-c3c1_T*v2v1.Y(),
												   	 c2c1_T*v3v1.Z()-c3c1_T*v2v1.Z());

            lpVertex[0]*=lfDenominator;
            lpVertex[1]*=lfDenominator;
			lpVertex[0].Normalise();
			lpVertex[1].Normalise();

			lpVertex[2]=lpVertex[0]*lpVertex[1];

			lpVertex[2].Normalise();

			if(lpMesh->NormalData())
			{
			    if(lpVertex[2].Dot(&(lpMesh->NormalData()[lpMesh->Face(liCount,0)*3]))<0.0f)
			    {
			        lpVertex[2].Invert();
			    }
			}
/*
			printf("Tangent : %f %f %f\n",lpVertex[0].X(),lpVertex[0].Y(),lpVertex[0].Z());
			printf("Binormal : %f %f %f\n",lpVertex[1].X(),lpVertex[1].Y(),lpVertex[1].Z());
			printf("Normal : %f %f %f\n",lpVertex[2].X(),lpVertex[2].Y(),lpVertex[2].Z());
*/
			Tangent->Get(lpMesh->Face(liCount,0))+=lpVertex[0];
			Bitangent->Get(lpMesh->Face(liCount,0))+=lpVertex[1];
			Normal->Get(lpMesh->Face(liCount,0))+=lpVertex[2];

			Tangent->Get(lpMesh->Face(liCount,1))+=lpVertex[0];
			Bitangent->Get(lpMesh->Face(liCount,1))+=lpVertex[1];
			Normal->Get(lpMesh->Face(liCount,1))+=lpVertex[2];

			Tangent->Get(lpMesh->Face(liCount,2))+=lpVertex[0];
			Bitangent->Get(lpMesh->Face(liCount,2))+=lpVertex[1];
			Normal->Get(lpMesh->Face(liCount,2))+=lpVertex[2];

		}

	}

	for(uint32 liCount=0;liCount<lpMesh->Verteces();++liCount)
	{

	    Tangent->Get(liCount).Normalise();
	    Bitangent->Get(liCount).Normalise();
	    Normal->Get(liCount).Normalise();
	}

	}

 };

/*
	if(lpMesh->UVData())
	{
	for(uint32 liCount=0;liCount<lpMesh->Faces();++liCount)
	{
		c3DVf lpVertex[3];
		lpVertex[0]=lpMesh->Vertex(lpMesh->Face(liCount,0));
		lpVertex[1]=lpMesh->Vertex(lpMesh->Face(liCount,1));
		lpVertex[2]=lpMesh->Vertex(lpMesh->Face(liCount,2));

		c2DVf lpUV[3];
		lpUV[0]=lpMesh->UV(lpMesh->Face(liCount,0));
		lpUV[1]=lpMesh->UV(lpMesh->Face(liCount,1));
		lpUV[2]=lpMesh->UV(lpMesh->Face(liCount,2));

		c3DVf v2v1=lpVertex[1]-lpVertex[0];
		c3DVf v3v1=lpVertex[2]-lpVertex[0];

		// printf("V0->V1 : %f %f %f\n",v2v1.X(),v2v1.Y(),v2v1.Z());
		// printf("V0->V2 : %f %f %f\n",v3v1.X(),v3v1.Y(),v3v1.Z());

		float c2c1_T = lpUV[1].X()-lpUV[0].X();
		float c2c1_B = lpUV[1].Y()-lpUV[0].Y();

		float c3c1_T = lpUV[2].X()-lpUV[0].X();
		float c3c1_B = lpUV[2].Y()-lpUV[0].Y();

		//printf("UV0 ->UV1 : %f %f\n",c2c1_T,c2c1_B);
		//printf("UV0 ->UV2 : %f %f\n",c3c1_T,c3c1_B);


		float lfDenominator=c2c1_T*c3c1_B-c3c1_T*c2c1_B;
       // printf("lfDenominator : %f\n",lfDenominator);
		if(lfDenominator==0.0f)
		{

			Tangent->Get(lpMesh->Face(liCount,2))=Tangent->Get(lpMesh->Face(liCount,1))=Tangent->Get(lpMesh->Face(liCount,0))=c3DVf(1.0f,0.0f,0.0f);
			Bitangent->Get(lpMesh->Face(liCount,2))=Bitangent->Get(lpMesh->Face(liCount,1))=Bitangent->Get(lpMesh->Face(liCount,0))=c3DVf(0.0f,1.0f,0.0f);
			Normal->Get(lpMesh->Face(liCount,2))=Normal->Get(lpMesh->Face(liCount,1))=Normal->Get(lpMesh->Face(liCount,0))=c3DVf(0.0f,0.0f,1.0f);
		}
		else
		{
			lfDenominator=1.0f/lfDenominator;

			lpVertex[0]=c3DVf(c3c1_B*v2v1.X()-c2c1_B*v3v1.X(),
												   c3c1_B*v2v1.Y()-c2c1_B*v3v1.Y(),
												   c3c1_B*v2v1.Z()-c2c1_B*v3v1.Z());

			lpVertex[1]=c3DVf(c2c1_T*v3v1.X()-c3c1_T*v2v1.X(),
												   	 c2c1_T*v3v1.Y()-c3c1_T*v2v1.Y(),
												   	 c2c1_T*v3v1.Z()-c3c1_T*v2v1.Z());

            lpVertex[0]*=lfDenominator;
            lpVertex[1]*=lfDenominator;
			lpVertex[0].Normalise();
			lpVertex[1].Normalise();

			lpVertex[2]=lpVertex[0]*lpVertex[1];

			lpVertex[2].Normalise();

			Tangent->Get(lpMesh->Face(liCount,0))+=lpVertex[0];
			Bitangent->Get(lpMesh->Face(liCount,0))+=lpVertex[1];
			Normal->Get(lpMesh->Face(liCount,0))+=lpVertex[2];

			Tangent->Get(lpMesh->Face(liCount,1))+=lpVertex[0];
			Bitangent->Get(lpMesh->Face(liCount,1))+=lpVertex[1];
			Normal->Get(lpMesh->Face(liCount,1))+=lpVertex[2];

			Tangent->Get(lpMesh->Face(liCount,2))+=lpVertex[0];
			Bitangent->Get(lpMesh->Face(liCount,2))+=lpVertex[1];
			Normal->Get(lpMesh->Face(liCount,2))+=lpVertex[2];

		}

	}

	for(uint32 liCount=0;liCount<lpMesh->Verteces();++liCount)
	{

	    Tangent->Get(liCount).Normalise();
	    Bitangent->Get(liCount).Normalise();
	    Normal->Get(liCount).Normalise();
	}

*/


























cAttributeArrayComponentData::cAttributeArrayComponentData(uint8 liItems,string lsName)
{
    miItems=liItems;
	msName=lsName;
};

uint8 cAttributeArrayComponentData::Items(){return miItems;};
string cAttributeArrayComponentData::Name(){return msName;};

uint32 cInterleavedFloatArray::Size(){ return sizeof(float)*miItems; };
uint32 cInterleavedDoubleArray::Size(){ return sizeof(double)*miItems; };
uint32 cInterleavedInt8Array::Size() { return sizeof(int8)*miItems; };
uint32 cInterleavedInt16Array::Size(){ return sizeof(int16)*miItems;};
uint32 cInterleavedInt32Array::Size(){ return sizeof(int32)*miItems;};
uint32 cInterleavedUint8Array::Size(){ return sizeof(uint8)*miItems;};
uint32 cInterleavedUint16Array::Size(){ return sizeof(uint16)*miItems;};
uint32 cInterleavedUint32Array::Size(){ return sizeof(uint32)*miItems;};

void cInterleavedFloatArray ::Write(int32 liID,char *liStart,uint16 liElementSize){if(liID>=0){  glEnableVertexAttribArray(liID); glVertexAttribPointer(liID,miItems,GL_FLOAT,false,liElementSize,liStart); }};
void cInterleavedDoubleArray::Write(int32 liID,char *liStart,uint16 liElementSize){if(liID>=0){  glEnableVertexAttribArray(liID); glVertexAttribPointer(liID,miItems,GL_DOUBLE,false,liElementSize,liStart); }};
void cInterleavedInt8Array  ::Write(int32 liID,char *liStart,uint16 liElementSize){if(liID>=0){  glEnableVertexAttribArray(liID); glVertexAttribPointer(liID,miItems,GL_BYTE,false,liElementSize,liStart); }};
void cInterleavedInt16Array ::Write(int32 liID,char *liStart,uint16 liElementSize){if(liID>=0){  glEnableVertexAttribArray(liID); glVertexAttribPointer(liID,miItems,GL_SHORT,false,liElementSize,liStart); }};
void cInterleavedInt32Array ::Write(int32 liID,char *liStart,uint16 liElementSize){if(liID>=0){  glEnableVertexAttribArray(liID); glVertexAttribPointer(liID,miItems,GL_INT,false,liElementSize,liStart); }};
void cInterleavedUint8Array ::Write(int32 liID,char *liStart,uint16 liElementSize){if(liID>=0){  glEnableVertexAttribArray(liID); glVertexAttribPointer(liID,miItems,GL_UNSIGNED_BYTE,false,liElementSize,liStart); }};
void cInterleavedUint16Array::Write(int32 liID,char *liStart,uint16 liElementSize){if(liID>=0){  glEnableVertexAttribArray(liID); glVertexAttribPointer(liID,miItems,GL_UNSIGNED_SHORT,false,liElementSize,liStart); }};
void cInterleavedUint32Array::Write(int32 liID,char *liStart,uint16 liElementSize){if(liID>=0){ glEnableVertexAttribArray(liID); glVertexAttribPointer(liID,miItems,GL_UNSIGNED_INT,false,liElementSize,liStart); }};


 cInterleavedFloatArray:: cInterleavedFloatArray(uint8 liItems,string lsName) : cAttributeArrayComponentData(liItems,lsName){ };
 cInterleavedDoubleArray::cInterleavedDoubleArray(uint8 liItems,string lsName) : cAttributeArrayComponentData(liItems,lsName){ };
  cInterleavedInt8Array::  cInterleavedInt8Array(uint8 liItems,string lsName) : cAttributeArrayComponentData(liItems,lsName){ };
 cInterleavedInt16Array:: cInterleavedInt16Array(uint8 liItems,string lsName) : cAttributeArrayComponentData(liItems,lsName){ };
 cInterleavedInt32Array:: cInterleavedInt32Array(uint8 liItems,string lsName) : cAttributeArrayComponentData(liItems,lsName){ };
 cInterleavedUint8Array:: cInterleavedUint8Array(uint8 liItems,string lsName) : cAttributeArrayComponentData(liItems,lsName){ };
cInterleavedUint16Array::cInterleavedUint16Array(uint8 liItems,string lsName) : cAttributeArrayComponentData(liItems,lsName){ };
cInterleavedUint32Array::cInterleavedUint32Array(uint8 liItems,string lsName) : cAttributeArrayComponentData(liItems,lsName){ };

    cInterleavedVertexArray::cInterleavedVertexArray(uint8 liItems) : cAttributeArrayComponentData(liItems,"Bb_Vertex"){  };
    void cInterleavedVertexArray::Write(int32 liID,char *liStart,uint16 liElementSize)
    {
		(void) liID;
        glVertexPointer(miItems,GL_FLOAT,liElementSize,liStart);
	};
    	uint32 cInterleavedVertexArray::Size(){return miItems*sizeof(float);};

    cInterleavedNormalArray::cInterleavedNormalArray() : cAttributeArrayComponentData(3,"Bb_Normal"){  };
    void cInterleavedNormalArray::Write(int32 liID,char *liStart,uint16 liElementSize)
    {
		(void) liID;
        glNormalPointer(GL_FLOAT,liElementSize-Size(),liStart);
    };
    uint32 cInterleavedNormalArray::Size(){return 3*sizeof(float);};

    cInterleavedTexCoordArray::cInterleavedTexCoordArray(uint8 liItems) : cAttributeArrayComponentData(liItems,"Bb_MultiTexCoord0"){  };
    void cInterleavedTexCoordArray::Write(int32 liID,char *liStart,uint16 liElementSize)
    {
		(void) liID;
        glTexCoordPointer(miItems,GL_FLOAT,liElementSize-Size(),liStart);
	};
    uint32 cInterleavedTexCoordArray::Size(){return miItems*sizeof(float);};

    cInterleavedColorArray::cInterleavedColorArray(uint8 liItems): cAttributeArrayComponentData(liItems,"Bb_Color"){ };
    void cInterleavedColorArray::Write(int32 liID,char *liStart,uint16 liElementSize)
        {
            (void) liID;
            glColorPointer(miItems,GL_FLOAT,liElementSize,liStart);
         };
    uint32 cInterleavedColorArray::Size(){return miItems*sizeof(float);};






















cInterleavedAttributeArray::cInterleavedAttributeArray(uint32 liElements)
{
    miElements=liElements;
    Init(5);
    mpData=0;
    miElementSize=0;
    glGenBuffers(1, &miBuffer);
}

cInterleavedAttributeArray::~cInterleavedAttributeArray()
{
glDeleteBuffers(1,&miBuffer);
}

void cInterleavedAttributeArray::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
	glBufferData(GL_ARRAY_BUFFER, miElementSize*miElements , mpData, GL_STATIC_DRAW);
};


cAttributeArrayComponentData *cInterleavedAttributeArray::Component(uint16 liPos){return mpList[liPos];};
uint16 cInterleavedAttributeArray::Components(){return Items();};

uint16 cInterleavedAttributeArray::operator[](string lsName)
{
    for(uint16 liCount=0;liCount<Items();++liCount)
    {
        if(mpList[liCount]->Name()==lsName)
        {
            return liCount+1;
        }
    }
    return 0;
};

uint16 cInterleavedAttributeArray::Component(string lsName)
{
    for(uint16 liCount=0;liCount<Items();++liCount)
    {
        if(mpList[liCount]->Name()==lsName)
        {
            return liCount+1;
        }
    }
    return 0;
};

void cInterleavedAttributeArray::Write(int32 *mpAttributeIDs)
{

    glBindBuffer(GL_ARRAY_BUFFER, miBuffer);
    char* liStart=0;
    for(uint16 liCount=0;liCount<Items();++liCount)
    {
        mpList[liCount]->Write(mpAttributeIDs[liCount],liStart,miElementSize);
        liStart+=mpList[liCount]->Size();
    }

};










    cManualInterleavedAttributeArray::cManualInterleavedAttributeArray(uint32 liElements) : cInterleavedAttributeArray(liElements)
	{
    };

    cManualInterleavedAttributeArray::~cManualInterleavedAttributeArray()
    {
        mpData=0;
    };

    void cManualInterleavedAttributeArray::AddComponent(cAttributeArrayComponentData *lpComponent)
    {
        miElementSize+=lpComponent->Size();
        Add(lpComponent);
    };

    void cManualInterleavedAttributeArray::AddComponents(uint16 liComponents,cAttributeArrayComponentData **lpComponent)
    {
        for(uint16 liCount=0;liCount<liComponents;++liCount)
        {
            miElementSize+=lpComponent[liCount]->Size();
            Add(lpComponent[liCount]);
        }
    };

    void cManualInterleavedAttributeArray::PointData(char *lpData)
    {
        mpData=lpData;
    };

    void cManualInterleavedAttributeArray::Elements(uint32 liElements)
    {
        miElements=liElements;
    };

    void cManualInterleavedAttributeArray::DeleteComponent(string lsName)
    {
        uint32 liComponent=Component(lsName);

        if(liComponent)
        {
            miElementSize-=mpList[--liComponent]->Size();
            Delete(liComponent);
        }
    };

    void cManualInterleavedAttributeArray::DeleteComponent(uint16 liComponent)
    {
        miElementSize-=mpList[liComponent]->Size();
        Delete(liComponent);
    };

















    cAutoInterleavedAttributeArray::cAutoInterleavedAttributeArray(uint32 liElements) : cInterleavedAttributeArray(liElements)
    {

    };

    cAutoInterleavedAttributeArray::~cAutoInterleavedAttributeArray()
    {
      delete []mpData;
      mpData=0;
    };

    void cAutoInterleavedAttributeArray::Elements(uint32 liElements)
    {
        char *lpTemp=mpData;
        lpTemp=new char[miElementSize*liElements];
        memcpy(lpTemp,mpData,miElementSize*miElements);
        delete []mpData;
        mpData=lpTemp;
    };

    void cAutoInterleavedAttributeArray::AddComponent(cAttributeArrayComponentData *lpComponent,char *lpData)
    {
        uint32 liCompSize=lpComponent->Size();
        char *lpTemp=mpData;
        lpTemp=new char[(miElementSize+liCompSize)*miElements];

        char *lpTempPos,*mpDataPos,*lpDataPos;
        lpTempPos=lpTemp;
        mpDataPos=mpData;
        lpDataPos=lpData;
        for(uint16 liCount=0;liCount<miElements;++liCount)
        {
            memcpy(lpTempPos,mpDataPos,miElementSize);
            lpTempPos+=miElementSize;
            lpDataPos+=miElementSize;

            memcpy(lpTempPos,lpDataPos,liCompSize);
            lpTempPos+=liCompSize;
            lpData+=liCompSize;
        }
        delete []mpData;
        mpData=lpTemp;

        miElementSize+=liCompSize;
        Add(lpComponent);
    };

    void cAutoInterleavedAttributeArray::AddComponents(uint16 liComponents,cAttributeArrayComponentData **lpComponent,char *lpData)
    {
        uint32 liCompSize=0;
        for(uint16 liCount=0;liCount<liComponents;++liCount)
        {
            liCompSize+=lpComponent[liCount]->Size();
        }

        char *lpTemp=mpData;
        lpTemp=new char[(miElementSize+liCompSize)*miElements];

        char *lpTempPos,*mpDataPos,*lpDataPos;
        lpTempPos=lpTemp;
        mpDataPos=mpData;
        lpDataPos=lpData;
        for(uint16 liCount=0;liCount<miElements;++liCount)
        {
            memcpy(lpTempPos,mpDataPos,miElementSize);
            lpTempPos+=miElementSize;
            lpDataPos+=miElementSize;

            memcpy(lpTempPos,lpDataPos,liCompSize);
            lpTempPos+=liCompSize;
            lpData+=liCompSize;
        }
        delete []mpData;
        mpData=lpTemp;

        for(uint16 liCount=0;liCount<liComponents;++liCount)
        {
            Add(lpComponent[liCount]);
        }

        miElementSize+=liCompSize;
    };

    void cAutoInterleavedAttributeArray::UpdateComponentData(uint16 liComponent,char *lpData)
    {
        uint32 liCompSize=mpList[liComponent]->Size();
        uint32 liCompStart=0;
        for(uint16 liCount=0;liCount<liComponent;++liCount)
        {
            liCompStart+=mpList[liComponent]->Size();
        }
        char *mpDataPos,*lpDataPos;
        mpDataPos=(char*)mpData;
        mpDataPos+=liCompStart;

        lpDataPos=(char*)lpData;
        for(uint16 liCount=0;liCount<miElements;++liCount)
        {
            memcpy(mpDataPos,lpDataPos,miElementSize);
            mpDataPos+=miElementSize;
            lpDataPos+=liCompSize;
        }
    };

    void cAutoInterleavedAttributeArray::UpdateComponentData(string lsName,char *lpData)
    {
        uint32 liComponent=Component(lsName);
        if(liComponent) UpdateComponentData(--liComponent,lpData);
    };

    void cAutoInterleavedAttributeArray::DeleteComponent(uint16 liComponent)
    {
        RemoveComponentsData(liComponent);
        Delete(liComponent);
    };
    void cAutoInterleavedAttributeArray::DeleteComponent(string lsName)
    {
      uint32 liComponent=Component(lsName);
        if(liComponent)
        {
          RemoveComponentsData(--liComponent);
          Delete(liComponent);
        }
    };

    void cAutoInterleavedAttributeArray::RemoveComponentsData(uint16 liComponent)
    {
      uint16 liPreSize=0;

      for(uint16 liCount=0;liCount<liComponent;++liCount)
      {
          liPreSize+=mpList[liCount]->Size();
      }

      uint16 liPostStart=liPreSize+mpList[liComponent]->Size();
      uint16 liPostSize=miElementSize-liPostStart;

      uint32 liNewSize=miElementSize-mpList[liComponent]->Size();
      char *lpTemp=new char[liNewSize*miElements];
      char *lpTempPos,*mpDataPos;
      lpTempPos=lpTemp;
      mpDataPos=mpData;

      for(uint16 liCount=0;liCount<miElements;++liCount)
      {
          if(liPreSize) memcpy(lpTempPos,mpDataPos,liPreSize);
          lpTempPos+=liPreSize;
          mpDataPos+=liPostStart;
          if(liPostSize) memcpy(lpTempPos,mpDataPos,liPostSize);
          lpTempPos+=liPostSize;
          mpDataPos+=liPostSize;
      }

      delete []mpData;
      mpData=lpTemp;
      miElementSize=liNewSize;
    };































cAttributeLinker::cAttributeLinker(cInterleavedAttributeArray *lpArray,cShaderProgram *lpProgram)
{
    mpArray=lpArray;
    mpAttributeIDs=new int32[mpArray->Components()];
	if(lpProgram)
	{
		miProgramID=lpProgram->ID();
    	for(uint16 liCount=0;liCount<mpArray->Components();++liCount)
    	{
        	mpAttributeIDs[liCount]=glGetAttribLocation(miProgramID,mpArray->Component(liCount)->Name().c_str());
    	}
	}
	else
	{
		miProgramID=-1;
	}
};

void cAttributeLinker::ShaderAndAttributeArray(cShaderProgram *lpProgram,cInterleavedAttributeArray *lpArray)
{
    miProgramID=lpProgram->ID();
    mpArray=lpArray;
    mpAttributeIDs=new int32[mpArray->Components()];
    for(uint16 liCount=0;liCount<mpArray->Components();++liCount)
    {
        mpAttributeIDs[liCount]=glGetAttribLocation(miProgramID,mpArray->Component(liCount)->Name().c_str());
    }
};

    void cAttributeLinker::Shader(cShaderProgram *lpProgram)
    {
        miProgramID=lpProgram->ID();
        for(uint16 liCount=0;liCount<mpArray->Components();++liCount)
        {
            mpAttributeIDs[liCount]=glGetAttribLocation(miProgramID,mpArray->Component(liCount)->Name().c_str());
        }
    };

    void cAttributeLinker::AttributeArray(cInterleavedAttributeArray *lpArray)
    {
        mpArray=lpArray;
        delete []mpAttributeIDs;
        mpAttributeIDs=new int32[mpArray->Components()];
        for(uint16 liCount=0;liCount<mpArray->Components();++liCount)
        {
            mpAttributeIDs[liCount]=glGetAttribLocation(miProgramID,mpArray->Component(liCount)->Name().c_str());
        }
    };

    void cAttributeLinker::AttributeArrayUpdated()
    {
        delete []mpAttributeIDs;
        mpAttributeIDs=new int32[mpArray->Components()];
        for(uint16 liCount=0;liCount<mpArray->Components();++liCount)
        {
            mpAttributeIDs[liCount]=glGetAttribLocation(miProgramID,mpArray->Component(liCount)->Name().c_str());
        }
    };

    void cAttributeLinker::Write()
    {
            mpArray->Write(mpAttributeIDs);
    };

    cAttributeLinker::~cAttributeLinker()
    {
        delete []mpAttributeIDs;
        mpAttributeIDs=0;
        miProgramID=0;
        mpArray=0;
    };

	int32 cAttributeLinker::ProgramID()
	{
		return miProgramID;
	};








	cElementArray::cElementArray(){ miElements=0; mpData=0; glGenBuffers(1,&miBuffer); };
	cElementArray::~cElementArray(){ glDeleteBuffers(1,&miBuffer); };
	void cElementArray::PointData(uint16 *lpData){ mpData=lpData; };
	void cElementArray::Elements(uint32 liElements){ miElements=liElements; };
	uint16 *cElementArray::Data(){ return mpData;};
	uint32 cElementArray::Elements(){ return miElements;};
	void cElementArray::Buffer(){ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, miBuffer);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16)*miElements, mpData, GL_STATIC_DRAW);};
	void cElementArray::Render(){ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, miBuffer);	glDrawElements(GL_POINTS,miElements,GL_UNSIGNED_SHORT,0);};
	void cElementArray::Render(uint32 liElements){ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, miBuffer);	glDrawElements(GL_POINTS,liElements,GL_UNSIGNED_SHORT,0);};
	//void cElementArray::Render(uint32 liElements){ glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, miBuffer);	glDrawArrays(GL_POINTS,liElements,GL_UNSIGNED_SHORT);};
