#include "../../WTDivWin.h"

cParticle::cParticle()
{
	 cParticleHandler::Instance()->Add(this);
	FadeSpeed=0.0f;
};

cParticle::~cParticle()
{
	
};

void cParticle::AdditionalKillFunctionality()
{
Life=0.0f;
}

void cParticle::AdditionalSleepFunctionality()
{
 cParticleHandler::Instance()->Remove(this);
}

void cParticle::AdditionalWakeFunctionality()
{
 cParticleHandler::Instance()->Add(this);
}


cParticleHandler *cParticleHandler::spthis;


cParticleHandler::cParticleHandler()
{
	lbRefresh=false;
	miParticles=0;
	miMaxParticles=WT_MAX_PARTICLES;
	mpParticles=new cParticle*[WT_MAX_PARTICLES];
}

cParticleHandler *cParticleHandler::Instance()
{
	if(!spthis) spthis=new cParticleHandler;
	return spthis;
	
};

void cParticleHandler::Resize(uint32 liSize)
{
	miMaxParticles=liSize;
	cParticle **lpTemp=new cParticle*[liSize];
	memcpy(lpTemp,mpParticles,sizeof(cParticle*)*miParticles);
	delete []mpParticles; mpParticles=lpTemp;
};

void cParticleHandler::DeleteAll()
{
	uint32 liCount;
	for(liCount=0;liCount<miParticles;++liCount)
	{
		delete mpParticles[liCount];
	}
	miParticles=0;
	delete []mpParticles;
	mpParticles=0;
}

void cParticleHandler::Add(cParticle *lpPart)
{
	if(miParticles>=miMaxParticles){Resize(miMaxParticles*2);}
	mpParticles[miParticles++]=lpPart;
};


void cParticleHandler::Delete(cParticle *lpPart)
{
	delete lpPart;
}

void cParticleHandler::Remove(uint32 liParticle)
{
--miParticles;
if(liParticle<miParticles)
{
	memcpy(&mpParticles[liParticle],&mpParticles[liParticle+1],sizeof(cParticle*)*miParticles-liParticle);
}
}

void cParticleHandler::Remove(cParticle *lpPart)
{
 uint32 liCount;
 for(liCount=0;liCount<miParticles;++liCount)
 {
  if(mpParticles[liCount]==lpPart) Remove(liCount);
 }

}

void cParticleHandler::Refresh()
{
	if(lbRefresh)
	{
		uint32 liCount;
		uint32 liFound=0;
		for(liCount=0;liCount<miParticles;++liCount)
		{
			if(mpParticles[liCount])
			{
				if(!mpParticles[liCount]->Life>0.0f){delete mpParticles[liCount];}
				else
				{
					mpParticles[liFound++]=mpParticles[liCount];
				}
			}
		}
		miParticles=liFound;
		lbRefresh=false;
	}
};


void cParticleHandler::RenderPainter()
{
	Refresh();
	SetShaderVariables();
	glBegin(GL_POINTS);
	uint32 liCount;
	for(liCount=0;liCount<miParticles;++liCount)
	{
		
		if(WT_PARTICLE_HANDLER_UPDATE_PARTICLE_POSITIONS) mpParticles[liCount]->UpdatePos();
		
		glColor4fv(mpParticles[liCount]->Color);
		glVertex3fv(mpParticles[liCount]->Position);
		
	}
	glEnd();
	float lpTemp[4]={1.0f,1.0f,1.0f,1.0f};
	glColor4fv(lpTemp);
}

void cParticleHandler::RenderPainter(uint8 liLevel)
{
(void) liLevel;
RenderPainter();
}


void cParticleHandler::RenderToPainter()
{
	
	_CAMERA->Identity();

	float Temp[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,Temp);
	
	//mpPainterData->SetMatrix(Temp);
	mpPainterData->SetObject(this);
	mpPainterData->SetShader(mpShader);
	mpPainterData->RenderAgain();
}

void cParticleHandler::Render()
{
	Refresh();
	_CAMERA->Identity();
	uint32 liCount;
	  if(mpShader) mpShader->Use();
	else _USE_FIXED_FUNCTION();

	SetShaderVariables();
	
	glBegin(GL_POINTS);
	for(liCount=0;liCount<miParticles;++liCount)
	{
		if(WT_PARTICLE_HANDLER_UPDATE_PARTICLE_POSITIONS) mpParticles[liCount]->UpdatePos();
		
		glColor4fv(mpParticles[liCount]->Color);
		glVertex3fv(mpParticles[liCount]->Position);
		
	};
	glEnd();
	float lpTemp[4]={1.0f,1.0f,1.0f,1.0f};
	glColor4fv(lpTemp);
};


void cGravityParticle::UpdatePos()
{
	Speed[0]+=_PARTICLE_GRAV_X;
	Speed[1]+=_PARTICLE_GRAV_Y;
	Speed[2]+=_PARTICLE_GRAV_Z;
	
	Position[0]+=Speed[0];
	Position[1]+=Speed[1];
	Position[2]+=Speed[2];
}

void cWindAndGravityParticle::UpdatePos()
{
    float lfTemp[3];
    
	lfTemp[0]=Speed[0]-_WIND_X;
	lfTemp[0]=lfTemp[0]*fabs(lfTemp[0]);
	lfTemp[1]=Speed[1]-_WIND_Y;
	lfTemp[0]=lfTemp[1]*fabs(lfTemp[1]);
	lfTemp[2]=Speed[2]-_WIND_Z;
	lfTemp[0]=lfTemp[2]*fabs(lfTemp[2]);
	
  	Speed[0]+=_PARTICLE_GRAV_X;
	Speed[1]+=_PARTICLE_GRAV_Y;
	Speed[2]+=_PARTICLE_GRAV_Z;
	
	Position[0]+=Speed[0]+lfTemp[0]*WT_TIME_IND*_WIND_FACTOR;
	Position[1]+=Speed[1]+lfTemp[1]*WT_TIME_IND*_WIND_FACTOR;
	Position[2]+=Speed[2]+lfTemp[2]*WT_TIME_IND*_WIND_FACTOR;
}

void cParticle::UpdateSpeed(float *lpTemp)
{
	Speed[0]=lpTemp[0];
	Speed[1]=lpTemp[1];
	Speed[2]=lpTemp[2];
};


void cParticle::UpdatePos()
{
	Position[0]+=Speed[0];
	Position[1]+=Speed[1];
	Position[2]+=Speed[2];
	
}

cParticleHandler::~cParticleHandler()
{
  DeleteAll();
  
};
