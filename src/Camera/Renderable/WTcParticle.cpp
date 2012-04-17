#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

cElementArray *gpElementArray=0;

void cParticle::UpdateSpeed(float *lpTemp)
{
    Speed=lpTemp;
};


void cParticle::UpdatePos()
{
    Position+=Speed;
}

void cParticle::UpdateGravity()
{
    Speed[0]+=_PARTICLE_GRAV_X;
	Speed[1]+=_PARTICLE_GRAV_Y;
	Speed[2]+=_PARTICLE_GRAV_Z;

	Position+=Speed;
};

void cParticle::UpdateGravityAndWind()
{
    c3DVf lfTemp;
    lfTemp[0]=Speed[0]-_WIND_X;
	lfTemp[0]=lfTemp[0]*fabs(lfTemp[0]);
	lfTemp[1]=Speed[1]-_WIND_Y;
	lfTemp[0]=lfTemp[1]*fabs(lfTemp[1]);
	lfTemp[2]=Speed[2]-_WIND_Z;
	lfTemp[0]=lfTemp[2]*fabs(lfTemp[2]);

  	Speed[0]+=_PARTICLE_GRAV_X;
	Speed[1]+=_PARTICLE_GRAV_Y;
	Speed[2]+=_PARTICLE_GRAV_Z;

	Position+=(Speed+lfTemp*_WIND_FACTOR);

};

void cParticle::UpdateWind()
{
    c3DVf lfTemp;
    lfTemp[0]=Speed[0]-_WIND_X;
	lfTemp[0]=lfTemp[0]*fabs(lfTemp[0]);
	lfTemp[1]=Speed[1]-_WIND_Y;
	lfTemp[0]=lfTemp[1]*fabs(lfTemp[1]);
	lfTemp[2]=Speed[2]-_WIND_Z;
	lfTemp[0]=lfTemp[2]*fabs(lfTemp[2]);

	Position+=(Speed+lfTemp*_WIND_FACTOR);
};



void cParticle::Spawn(cParticleSettings &lpData)
{
	uint32 liCount;

	for(liCount=0;liCount<3;++liCount)
	{
		Color[liCount]=lpData.RGB[liCount]+RANDOM_NUMBER*lpData.RGB[4+liCount];
		Position[liCount]=lpData.Position[liCount]+RANDOM_NUMBER*lpData.Position[3+liCount];
	};
	if(lpData.Speed[4]) memcpy(Speed.v,ParticleArcSpeeds(lpData.Speed).v,sizeof(float)*3);
	else memcpy(Speed.v,ParticleBallSpeeds(lpData.Speed).v,sizeof(float)*3);

	Color[liCount]=lpData.RGB[3]+RANDOM_NUMBER*lpData.RGB[7];
	Life=lpData.Life[0]+RANDOM_NUMBER*lpData.Life[1];
	Size=lpData.Size[0]+RANDOM_NUMBER*lpData.Size[1];
};


void cParticle::SetColor(float *lpRGB){Color=lpRGB;};
void cParticle::SetColor(cRGB *lpRGB){Color=lpRGB;};
void cParticle::SetColor(cRGBA *lpRGB){Color=lpRGB;};
void cParticle::SetColor(cRGB &lpRGB){Color=lpRGB;};
void cParticle::SetColor(cRGBA &lpRGB){Color=lpRGB;};


	void cParticle::SetSize(float lpSize){Size=lpSize;};
	void cParticle::SetLife(float lpLife){Life=lpLife;};
	void cParticle::SetSpeed(float *lpSpeed){Speed=lpSpeed;};
	void cParticle::SetPosition(float *lpPos){Position=lpPos;};


cParticle cParticle::operator=(cParticle *lpOther)
{
    memcpy(this,lpOther,sizeof(cParticle));
    return *this;
};
cParticle cParticle::operator=(cParticle lpOther)
{
    memcpy(this,&lpOther,sizeof(cParticle));
    return *this;
};

cParticle::cParticle()
{
    Life=0.0f;
}


cParticleHandler::cParticleHandler() : cRenderObject(true)
{
	InitialiseParticleHandler(WT_MAX_PARTICLES);
}

cParticleHandler::cParticleHandler(uint32 liParticles) : cRenderObject(true)
{
	InitialiseParticleHandler(liParticles);
}

cParticleHandler::cParticleHandler(uint32 liParticles,cCamera *lpCamera) : cRenderObject(lpCamera,true)
{
	InitialiseParticleHandler(liParticles);
}

cParticleHandler::cParticleHandler(uint32 liParticles,vRenderNode *lpNode) : cRenderObject(lpNode,true)
{
	InitialiseParticleHandler(liParticles);
}

cParticleHandler::cParticleHandler(vRenderNode *lpNode) : cRenderObject(lpNode,true)
{
    InitialiseParticleHandler(WT_MAX_PARTICLES);
};

cParticleHandler::cParticleHandler(cCamera *lpCamera) : cRenderObject(lpCamera,true)
{

	InitialiseParticleHandler(WT_MAX_PARTICLES);

};

void cParticleHandler::InitialiseParticleHandler(uint32 liParticles)
{
	lbRefresh=false;
	Init(liParticles);
	Transparency(1);

	mpAttributes=new cManualInterleavedAttributeArray(5);

	mpAttributes->AddComponent(new cInterleavedVertexArray(3));
	mpAttributes->AddComponent(new cInterleavedFloatArray(4,"Bb_Color"));
	mpAttributes->AddComponent(new cInterleavedFloatArray(1,"Bb_Size"));
	mpAttributes->AddComponent(new cInterleavedFloatArray(3,"Bb_Speed"));
	mpAttributes->AddComponent(new cInterleavedFloatArray(1,"Bb_Life"));

	mpAttributes->Elements(0);
	mpAttributes->PointData((char*)mpList);

	mpAttributeLinker=new cAttributeLinker(mpAttributes);

};

uint32 cParticleHandler::LivingParticles()
{
 return Items();
};

cParticle *cParticleHandler::NewParticle()
{
 if(miSpaces<=1+miItems) ChangeSize(miSpaces*1.5);
 {
     ++miItems;
     return &mpList[miItems-1];
 }
};

void cParticleHandler::Refresh()
{
		uint32 liCount;
		uint32 liFound=0;
		for(liCount=0;liCount<Items();++liCount)
		{
            mpList[liCount].Life-=WT_FRAME_TIME;
            if(mpList[liCount].Life>0.0f)
            {
                if(liFound!=liCount) mpList[liFound]=mpList[liCount];
                ++liFound;
            }
		}
		miItems=liFound;
};


void cParticleHandler::RenderPainter()
{
	Refresh();
	SetShaderVariables();

/*
		for(uint32 liCount=0;liCount<Items();++liCount)
	{
        mpList[liCount].UpdatePos();
	}

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3,GL_FLOAT,sizeof(cParticle),mpList[0].Position.v);
    glColorPointer(4,GL_FLOAT,sizeof(cParticle),mpList[0].Color.Color());

    glDrawArrays(GL_POINTS,0,Items());

    glDisableClientState(GL_COLOR_ARRAY);
*/

	for(uint32 liCount=0;liCount<Items();++liCount)
	{
        mpList[liCount].UpdatePos();
	}


//	if(mpAttributeLinker->ProgramID()!=mpShader->ID())
	{
	    mpAttributeLinker->ShaderAndAttributeArray(mpShader,mpAttributes);
		//mpAttributeLinker->Shader(mpShader);

	}

	mpAttributes->Elements(Items());
	mpAttributes->PointData((char*)mpList);

    //glEnable(GL_COLOR);
    //glEnableClientState(GL_COLOR_ARRAY);
	mpAttributes->Buffer();

    mpAttributeLinker->Write();
/*
	if(miSpaces>gpElementArray->Elements())
	{
		gpElementArray->PointData(ExpandCountingArray(gpElementArray->Data(),gpElementArray->Elements(),miSpaces));
		gpElementArray->Elements(miSpaces);
		gpElementArray->Buffer();
	}

	gpElementArray->Render(Items());
*/
    glDrawArrays(GL_POINTS,0,Items());
 //   glDisableClientState(GL_COLOR_ARRAY);

/*
    glBegin(GL_POINTS);
	uint32 liCount;
	for(liCount=0;liCount<Items();++liCount)
	{
        mpList[liCount].UpdatePos();

        glColor4fv(mpList[liCount].Color.Color());
        glVertex3fv(mpList[liCount].Position.v);

	}
    glEnd();
*/

	float lpTemp[4]={1.0f,1.0f,1.0f,1.0f};
	glColor4fv(lpTemp);

}


c3DVf ParticleArcSpeeds(c3DVf Vector,float lfSpeedRange, float lfAngleRange)
{
    memcpy(cParticleSettings::sfStore,Vector.v,sizeof(float)*3);
    cParticleSettings::sfStore[3]=lfSpeedRange;
    cParticleSettings::sfStore[4]=lfAngleRange;

    return c3DVf(ParticleArcSpeeds(cParticleSettings::sfStore));
};

c3DVf ParticleBallSpeeds(float lfSpeed,float lfSpeedRange)
{
  cParticleSettings::sfStore[0]=lfSpeed;
  cParticleSettings::sfStore[1]=lfSpeedRange;

  return c3DVf(ParticleBallSpeeds(cParticleSettings::sfStore));

};

c3DVf ParticleArcSpeeds(float *lpSpeedInfo)
{
   c3DVf Normal;
   c3DVf lpSpeedData(lpSpeedInfo);
   lpSpeedData*=1.0f+ZEROED_RANDOM_NUMBER*lpSpeedInfo[3];

    Normal[1]=ZEROED_RANDOM_NUMBER;
    Normal[0]=ZEROED_RANDOM_NUMBER;
    Normal[2]=ZEROED_RANDOM_NUMBER;

    c3DVf cross_vector = Normal*lpSpeedData;
    Normal=cross_vector*lpSpeedData;


float h = cos( RANDOM_NUMBER*lpSpeedInfo[4]);
float phi = 2 * 3.14159f * RANDOM_NUMBER;
float z = h + ( 1 - h ) * RANDOM_NUMBER;
float sinT = sqrt( 1 - z * z );
float x = cos( phi ) * sinT;
float y = sin( phi ) * sinT;

c3DVf perturbed = Normal * x + cross_vector * y + lpSpeedData * z;
perturbed*=sqrt(lpSpeedInfo[0]*lpSpeedInfo[0]+lpSpeedInfo[1]*lpSpeedInfo[1]+lpSpeedInfo[2]*lpSpeedInfo[2]);
return perturbed;

};


c3DVf ParticleSideVelocity(float *lpSpeedInfo)
{
    c3DVf Normal;
   c3DVf lpSpeedData(lpSpeedInfo);
   lpSpeedData*=(1.0f+ZEROED_RANDOM_NUMBER*lpSpeedInfo[3]);

    Normal[1]=ZEROED_RANDOM_NUMBER;
    Normal[0]=ZEROED_RANDOM_NUMBER;
    Normal[2]=ZEROED_RANDOM_NUMBER;

    c3DVf cross_vector = Normal*lpSpeedData;
    Normal=cross_vector*lpSpeedData;

float h = cos(0.5*3.14159*ZEROED_RANDOM_NUMBER);
float phi = 2 * 3.14159f * RANDOM_NUMBER;
float z = h + ( 1 - h ) * RANDOM_NUMBER;
float x = cos( phi );
float y = sin( phi );

c3DVf perturbed = Normal * x * lpSpeedInfo[4] + cross_vector * y * lpSpeedInfo[4] + lpSpeedData * z;
//perturbed*=sqrt(lpSpeedInfo[0]*lpSpeedInfo[0]+lpSpeedInfo[1]*lpSpeedInfo[1]+lpSpeedInfo[2]*lpSpeedInfo[2]);
return perturbed;

};

c3DVf ParticleSideVelocity(c3DVf lpSpeedInfo,float lfSpeedRange, float lfSideSpeed)
{
    float lfTemp[6];
    memcpy(lfTemp,lpSpeedInfo.v,sizeof(float)*3);
    lfTemp[3]=lfSpeedRange;
    lfTemp[4]=lfSideSpeed;

    return (ParticleSideVelocity(lfTemp));
}


c3DVf ParticleBallSpeeds(float *lpSpeedData)
{
    lpSpeedData[0]=lpSpeedData[0]*(1.0f+ZEROED_RANDOM_NUMBER*lpSpeedData[1]);

    float lfRandomYaw=RANDOM_NUMBER*3.14159*2;
    float lfRandomPitch=RANDOM_NUMBER*3.14159*2;
    float lfCosPitch=cos(lfRandomPitch);
    c3DVf Vector(cos(lfRandomYaw)*lfCosPitch*lpSpeedData[0],sin(lfRandomPitch)*lpSpeedData[0],sin(lfRandomYaw)*lfCosPitch*lpSpeedData[0]);

    return Vector;
};

c3DVf GenerateUniformRandomVector()
{
    float lfRandomYaw=RANDOM_NUMBER*3.14159*2;
    float lfRandomPitch=RANDOM_NUMBER*3.14159*2;
    float lfCosPitch=cos(lfRandomPitch);
    c3DVf Vector(cos(lfRandomYaw)*lfCosPitch,sin(lfRandomPitch),sin(lfRandomYaw)*lfCosPitch);
    return Vector;
};

#endif
