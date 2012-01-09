#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

	cParticleSettings &cParticleSettings::operator=(cParticleSettings &lpOther)
	{
		memcpy(RGB,lpOther.RGB,sizeof(float)*8);
		memcpy(Position,lpOther.Position,sizeof(float)*6);
		memcpy(Speed,lpOther.Speed,sizeof(float)*6);
		memcpy(Size,lpOther.Size,sizeof(float)*2);
		memcpy(Fade,lpOther.Fade,sizeof(float)*2);
		return this[0];
	};

	void cParticleSettings::SetColours(float *lpRGB){memcpy(RGB,lpRGB,sizeof(float)*8);};
	void cParticleSettings::SetSizes(float *lpSize){memcpy(Size,lpSize,sizeof(float)*2);};
	void cParticleSettings::SetFades(float *lpFade){memcpy(Fade,lpFade,sizeof(float)*2);};
	void cParticleSettings::SetSpeeds(float *lpSpeed){memcpy(Speed,lpSpeed,sizeof(float)*6);};
	void cParticleSettings::SetPositions(float *lpPos){memcpy(Position,lpPos,sizeof(float)*6);};

void cParticleGroup::Refresh()
{
	uint32 THERE_SHOULD_BE_SOME_CODE_HERE;

	uint32 liCount;
	uint32 liFound=0;
	for(liCount=0;liCount<miParticles;++liCount)
	{

		if(mpParticles[liCount]->Life<=0.0f)
		{
			if(mbRespawn) mpParticles[liCount]->Spawn(Data);
			else{ delete mpParticles[liCount]; mpParticles[liCount]=0;}
		}
		else
		{
			mpParticles[liCount]->UpdatePos();
			mpParticles[liFound++]=mpParticles[liCount];
		}
	}
	if(!mbRespawn) miParticles=liFound;


};




void cParticleGroup::RenderPainter(uint8 liLevel)
{
	( void) liLevel;
	RenderPainter();
}

void cParticleGroup::RenderPainter()
{

//	 AdditionalRenderFunctions();
	SetShaderVariables();

	 uint32 MAKE_THIS_A_SHADER_FUNCTION_TO_MAKE_POINT_SIZE_WORK;

	 //_CAMERA->ResetGLMatrix();
	 uint32 liCount;
	 uint32 liFound=0;


	 glBegin(GL_POINTS);
	 for(liCount=0;liCount<miParticles;++liCount)
	 {
		 if(mpParticles[liCount]->Life<=0.0f)
		 {
			 if(mbRespawn) mpParticles[liFound++]->Spawn(Data);
			 else{ delete mpParticles[liCount]; mpParticles[liCount]=0;}
		}
		else
		{
			mpParticles[liCount]->UpdatePos();
			mpParticles[liCount]->UpdateFade();
			mpParticles[liFound++]=mpParticles[liCount];


			glColor4fv(mpParticles[liCount]->Color.Color());
			glVertex3f(mpParticles[liCount]->Position[0],mpParticles[liCount]->Position[1],mpParticles[liCount]->Position[2]);

		}
	 }
	 glEnd();

	 if(!mbRespawn) miParticles=liFound;

}


void cParticleGroup::RenderToPainter()
{
	Refresh();

	UpdateMatrix();

	mpPainterData->SetObject(this);
	mpPainterData->SetTexture(0);
	SetOtherRenderVariables();
	mpPainterData->RenderAgain();


}


cParticleGroup::cParticleGroup(uint32 liParticles,cRenderNode* lpNode=0) : cRenderObject(lpNode)
{
	miParticles=liParticles;
	mpParticles=new cParticleForGroup*[miParticles];
	memset(mpParticles,0,sizeof(cParticleForGroup*)*miParticles);
};


void cParticleGroup::RespawnAll()
{
	uint32 liCount;
	for(liCount=0;liCount<miParticles;++liCount)
	{
		if(!mpParticles[liCount]) mpParticles[liCount]=new cParticleForGroup;

		mpParticles[liCount]->Spawn(Data);
	}
};


void cParticleForGroup::UpdatePos()
{
	Position[0]+=Speed[0]*WT_TIME_IND;
	Position[1]+=Speed[1]*WT_TIME_IND;
	Position[2]+=Speed[2]*WT_TIME_IND;
}


void cParticleForGroup::Spawn(cParticleSettings &lpData)
{
	uint32 liCount;

	for(liCount=0;liCount<3;++liCount)
	{
		Color[liCount]=lpData.RGB[liCount]+RANDOM_NUMBER*lpData.RGB[3+liCount];
		Position[liCount]=lpData.Position[liCount]+RANDOM_NUMBER*lpData.Position[3+liCount];
		Speed[liCount]=lpData.Speed[liCount]+RANDOM_NUMBER*lpData.Speed[3+liCount];
	};
	FadeSpeed=lpData.Fade[0]+RANDOM_NUMBER*lpData.Fade[1];
	Size=lpData.Size[0]+RANDOM_NUMBER*lpData.Size[1];
	Life=1.0f;
};


cParticleGroup::~cParticleGroup()
{
 uint32 liCount;
 for(liCount=0;liCount<miParticles;++liCount)
 {
  if(mpParticles[liCount]) delete mpParticles[liCount];
 }
 delete []mpParticles;
 mpParticles=0;
 miParticles=0;
}

void cParticleForGroup::SetColor(float *lpRGB){Color=lpRGB;};
void cParticleForGroup::SetColor(cRGB *lpRGB){Color=lpRGB;};
void cParticleForGroup::SetColor(cRGBA *lpRGB){Color=lpRGB;};
void cParticleForGroup::SetColor(cRGB &lpRGB){Color=lpRGB;};
void cParticleForGroup::SetColor(cRGBA &lpRGB){Color=lpRGB;};


	void cParticleForGroup::SetSize(float lpSize){Size=lpSize;};
	void cParticleForGroup::SetFade(float lpFade){FadeSpeed=lpFade;};
	void cParticleForGroup::SetSpeed(float *lpSpeed){memcpy(Speed,lpSpeed,sizeof(float)*3);};
	void cParticleForGroup::SetPosition(float *lpPos){memcpy(Position,lpPos,sizeof(float)*3);};
    void cParticleForGroup::UpdateFade(){Life-=FadeSpeed*WT_TIME_IND;};

#endif
