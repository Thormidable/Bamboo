#include "../../WTDivWin.h"

cBeamMesh::~cBeamMesh()
{
	delete []VertexList;
	VertexList=0;
	delete []VertexData;
	VertexData=0;

}

cBeamMesh::cBeamMesh(float Radius,float Length,uint16 Segments,cRenderNode *lpNode): cRenderObject(lpNode)
{
	VertexData=0; VertexList=0; GenerateData(Radius,Length,Segments);
	mpShader=0;
}; 


void cBeamMesh::RenderBeam()
{

	glDisable(GL_NORMAL_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer2);
	
	
	glVertexPointer(3,GL_FLOAT,0,0);
 	
	glDrawElements(GL_TRIANGLE_STRIP,miSegments*4-1,GL_UNSIGNED_SHORT,0);

	glEnable(GL_NORMAL_ARRAY);
}

void cBeamMesh::BufferBeam()
{
	//if (!mpBufferIDs) mpBufferIDs= new uint32[2];
	glGenBuffers(1,&mBuffer1);
	glGenBuffers(1,&mBuffer2);
	
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(miSegments*6), VertexData, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16)*(miSegments*4-1), VertexList, GL_STATIC_DRAW);
	
}


void cBeamMesh::RenderPainter(uint8 liLevel)
{
(void) liLevel;

	//PrepareMaterial();
	//AdditionalRenderFunctions();
	SetShaderVariables();
	RenderBeam();
}

void cBeamMesh::RenderToPainter()
{

	//float Temp[16];
	UpdateMatrix();
	
	//glGetFloatv(GL_MODELVIEW_MATRIX,Temp);
	//cRenderPointer lcTemp;

	mpPainterData->SetObject(this);
	//mpPainterData->SetMatrix(Temp);
	mpPainterData->SetTexture(0);
	mpPainterData->SetShader(mpShader);
	mpPainterData->RenderAgain();

	//cPainter::Instance()->Add(lcTemp);
}

void cBeamMesh::Render()
{
	glDisable(GL_TEXTURE_2D);
	
	if(VertexData && VertexList)
	{
		UpdateMatrix();
		
		//PrepareMaterial();
		
		//mpTexture->BindTexture();
		
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//glEnableClientState(GL_NORMAL_ARRAY);
		
		
		if(mpShader) mpShader->Use();
		else _USE_FIXED_FUNCTION();

		AdditionalRenderFunctions();
		
		RenderBeam();
		
	}
	
};


void cBeamMesh::Radius(float Radius)
{
	mfRadius=Radius;
	
	VertexData[4]=Radius;
	
	uint32 liCount;
	uint32 liCount3;
	float Angle=2*3.141592/miSegments;
	for(liCount=0;liCount<miSegments;++liCount)
	{
		liCount3=liCount*12;
		
		VertexData[6+liCount3]=Radius*sin(Angle*(liCount+1));
		VertexData[7+liCount3]=Radius*cos(Angle*(liCount+1));
		
		VertexData[9+liCount3]=Radius*sin(Angle*liCount);
		VertexData[10+liCount3]=Radius*cos(Angle*liCount);
		
		VertexData[12+liCount3]=Radius*sin(Angle*(liCount+1));
		VertexData[13+liCount3]=Radius*cos(Angle*(liCount+1));
	}
	BufferBeam();
};

void cBeamMesh::Length(float Length)
{
	mfLength=Length;
	uint32 liCount;
	uint32 liCount3;
	for(liCount=0;liCount<miSegments;++liCount)
	{
		liCount3=liCount*12;
		if(liCount%2)
		{
			VertexData[8+liCount3]=Length;
		}
		else
		{
			VertexData[11+liCount3]=Length;
			VertexData[14+liCount3]=Length;
			VertexData[17+liCount3]=Length;
		}
		
	}
	
	BufferBeam();
};


void cBeamMesh::GenerateData(float Radius,float Length,uint16 Segments)
{
	mfRadius=Radius;
	mfLength=Length;
	miSegments=Segments;
	if(VertexData) delete VertexData;
	
	VertexData=new float[Segments*6];
	
	uint32 liCount;
	uint32 liCount3;
	float Angle=2*3.141592/Segments;
	for(liCount=0;liCount<Segments;++liCount)
	{
		liCount3=liCount*3;
			//4   =     2
		VertexData[liCount3]=Radius*sin(Angle*(liCount));
		VertexData[liCount3+1]=Radius*cos(Angle*(liCount));
		VertexData[liCount3+2]=0.0f;

		liCount3=Segments*3+liCount3;
		
		VertexData[liCount3]=Radius*sin(Angle*(liCount));
		VertexData[liCount3+1]=Radius*cos(Angle*(liCount));
		VertexData[liCount3+2]=Length;
	}


	
	
	liCount3=(Segments*4-1);
	if(VertexList) delete []VertexList;
	VertexList=new uint16[liCount3];

	VertexList[0]=0;
	
	//Build Ends
	for(liCount=1;liCount*2<Segments;++liCount)
	{
		liCount3=liCount*2;
		VertexList[liCount*2-1]=Segments-liCount;
		VertexList[liCount*2]=liCount;

 		VertexList[Segments*4-2-liCount*2+1]=2*Segments-liCount;
 		VertexList[Segments*4-2-liCount*2]=Segments+liCount;
	}
	

	
	int16 HalfSegments=Segments>>1;
//build walls

	for(liCount=0;liCount<Segments;++liCount)
	{
		if(liCount>=HalfSegments){HalfSegments=-HalfSegments;}
		VertexList[Segments+liCount*2-1]=HalfSegments+liCount;
		VertexList[Segments+liCount*2]=Segments+HalfSegments+liCount;
		
	}

	VertexList[Segments*3-1]=Segments+(Segments>>1);
	VertexList[Segments*4-2]=Segments;
	
	BufferBeam();
}
/*
 * float cBeamMesh::Verteces[78]=
 * {
 * 0.0f,0.0f,0.0f,
 * 0.0f,Radius,0.0f,
 * 
 * Radius*sin(60),Radius*cos(60),0.0f,
 * Radius*sin(0),Radius*cos(0),WT_BEAM_LENGTH,
 * Radius*sin(60),Radius*cos(60),WT_BEAM_LENGTH,
 * 
 * 0.0f,0.0f,WT_BEAM_LENGTH,
 * Radius*sin(120),Radius*cos(120),WT_BEAM_LENGTH,
 * Radius*sin(60),Radius*cos(60),0.0f,
 * Radius*sin(120),Radius*cos(120),0.0f,
 * 
 * 0.0f,0.0f,0.0f,
 * Radius*sin(180),Radius*cos(180),0.0f,
 * Radius*sin(120),Radius*cos(120),WT_BEAM_LENGTH,
 * Radius*sin(180),Radius*cos(180),WT_BEAM_LENGTH,
 * 
 * 0.0f,0.0f,WT_BEAM_LENGTH,
 * Radius*sin(240),Radius*cos(240),WT_BEAM_LENGTH,
 * Radius*sin(180),Radius*cos(180),0.0f,
 * Radius*sin(240),Radius*cos(240),0.0f,
 * 
 * 0.0f,0.0f,0.0f,
 * Radius*sin(300),Radius*cos(300),0.0f,
 * Radius*sin(240),Radius*cos(240),WT_BEAM_LENGTH,
 * Radius*sin(300),Radius*cos(300),WT_BEAM_LENGTH,
 * 
 * 0.0f,0.0f,WT_BEAM_LENGTH,
 * Radius*sin(360),Radius*cos(360),WT_BEAM_LENGTH,
 * Radius*sin(300),Radius*cos(300),0.0f,
 * Radius*sin(3600),Radius*cos(360),0.0f
 * 
 * 0.0f,0.0f,0.0f
 };
 
 float cBeamMesh::VertexList[26]=
 {
	 0,1,2,3,4,5,6,7,8,9,10,
	 11,12,13,14,15,16,17,
	 18,19,20,21,22,23,24,25
 };
 */
