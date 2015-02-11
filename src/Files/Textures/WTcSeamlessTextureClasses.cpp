
#include "../../WTBamboo.h"

using namespace std;

cSeamPair::cSeamPair()
{

};

void cSeamData::SwapDirection()
{
    c2DVf lfTemp=mvStart;
    mvStart=mvEnd;
    mvEnd=lfTemp;
};

cSeamPair &cSeamPair::operator=(cSeamPair &lpOther)
{
    Data[0]=lpOther.Data[0];
    Data[1]=lpOther.Data[1];
    return *this;
};

void cSeamData::CalculateVectors(bool CW)
{
    Vector=mvStart-mvEnd;
    if(CW) Perpendicular=Vector.PerpendicularRH();
    else Perpendicular=Vector.PerpendicularLH();
};

cSeamData &cSeamData::operator=(cSeamData &lpOther)
{
    mvStart=lpOther.mvStart;
    mvEnd=lpOther.mvEnd;
    miTemplate=lpOther.miTemplate;
    Vector=lpOther.Vector;
    Perpendicular=lpOther.Perpendicular;
    return *this;
};

cSeamTranslation::cSeamTranslation()
{
    mvCentre=c2DVf(0.0f,0.0f);
    mfAngle=0.0f;
}

void cSeamTranslation::operator=(cSeamTranslation lpOther)
{
    mvCentre=lpOther.mvCentre;
    mfAngle=lpOther.mfAngle;

};
void cSeamTranslation::operator=(c2DVf &lpOther)
{
    mvCentre=lpOther;
};
void cSeamTranslation::operator=(float &lpOther)
{
    mfAngle=lpOther;
};

cSeamTranslationList::cSeamTranslationList(SEAM_ID_TYPE liTemplates)
{
 mpTranslations=new cSeamTranslation[liTemplates];
 miTemplates=liTemplates;
};

cSeamTranslation &cSeamTranslationList::operator[](SEAM_ID_TYPE liTemplate)
{
    return mpTranslations[liTemplate];
};

cSeamPair::cSeamPair(c2DVf lvStart1,c2DVf lvEnd1,bool CW1, SEAM_ID_TYPE liTemplate1,c2DVf lvStart2,c2DVf lvEnd2,bool CW2, SEAM_ID_TYPE liTemplate2)
{
    Data[0].mvStart=lvStart1;
    Data[0].mvEnd=lvEnd1;
    Data[0].miTemplate=liTemplate1;
    Data[0].CalculateVectors(CW1);


    Data[1].mvStart=lvStart2;
    Data[1].mvEnd=lvEnd2;
    Data[1].miTemplate=liTemplate2;
    Data[1].CalculateVectors(CW2);

};

SEAM_ID_TYPE cSeamPair::ClosestSeamID(c2DVf Position)
{
     c2DVf Vector=Position-Data[0].mvStart;
    float lfMagnitude=Vector.Magnitude();
    float lfAlong=Vector.Dot(Data[0].Vector);
    float lfDist1;

    if(lfAlong>0.0f && lfAlong*lfMagnitude<1.0f) lfDist1=Vector.Dot(Data[0].Perpendicular);
    else lfDist1=10.0f;


    Vector=Position-Data[1].mvStart;
    lfMagnitude=Vector.Magnitude();
    lfAlong=Vector.Dot(Data[1].Vector);
    float lfDist2;

    if(lfAlong>0.0f && lfAlong*lfMagnitude<1.0f) lfDist2=Vector.Dot(Data[1].Perpendicular);
    else lfDist2=10.0f;

    if(lfDist2<lfDist1) return Data[1].miTemplate;
    else return Data[0].miTemplate;
};

bool cSeamPair::SeamMirror(SEAM_ID_TYPE liBase,SEAM_ID_TYPE liOther)
{
    if((Data[0].miTemplate==liBase && Data[1].miTemplate==liOther) || (Data[1].miTemplate==liBase && Data[0].miTemplate==liOther) ) return 1;
    return 0;
};


cSeamTranslation::cSeamTranslation(c2DVf lvCentre,float lfAngle)
{
    mvCentre=lvCentre;
    mfAngle=lfAngle;
};

cSeamTranslation cSeamPair::Map(cSeamTranslation lfTranslation,SEAM_ID_TYPE liTemplate)
{
    uint8 liBase=2;
    uint8 liOther=2;
    if(liTemplate==Data[0].miTemplate) {liBase=0; liOther=1;}
    if(liTemplate==Data[1].miTemplate) {liBase=1; liOther=0;}
    if(liBase==2) return cSeamTranslation(c2DVf(100.0f,100.0f),0.0f);

    c2DVf BaseVectorToPoint=lfTranslation.mvCentre-Data[liBase].mvStart;

    float lfAlong=BaseVectorToPoint.Dot(Data[liBase].Vector);
    float lfPerp=BaseVectorToPoint.Dot(Data[liBase].Perpendicular);

    c2DVf ResultPosition=Data[liOther].mvStart+Data[liOther].Vector*lfAlong-Data[liOther].Perpendicular*lfPerp;

    return cSeamTranslation(ResultPosition,Data[liBase].Vector.SignedAngle(Data[liOther].Vector)+lfTranslation.mfAngle);
};

float cSeamPair::Distance(c2DVf Position)
{
    c2DVf Vector=Position-Data[0].mvStart;
    float lfMagnitude=Vector.Magnitude();
    float lfAlong=Vector.Dot(Data[0].Vector);
    float lfDist1;

    if(lfAlong>0.0f && lfAlong*lfMagnitude<1.0f) lfDist1=Vector.Dot(Data[0].Perpendicular);
    else lfDist1=10.0f;



    Vector=Position-Data[1].mvStart;
    lfMagnitude=Vector.Magnitude();
    lfAlong=Vector.Dot(Data[1].Vector);
    float lfDist2;

    if(lfAlong>0.0f && lfAlong*lfMagnitude<1.0f) lfDist2=Vector.Dot(Data[1].Perpendicular);
    else lfDist2=10.0f;

    if(lfDist2<lfDist1) return lfDist2;
    else return lfDist1;

};

cSeamList::cSeamList(uint8 liTextures, cTexture **lpTextures)
{
    mpMap=new cSeamAreaMap*[liTextures];
    miTextures=liTextures;
    for(uint8 liCount=0;liCount<liTextures;++liCount)
    {
        mpMap[liCount]=new cSeamAreaMap(lpTextures[liCount]);
    }
};

void cSeamList::GenerateAreaMap()
{
    for(uint8 liCount=0;liCount<miTextures;++liCount)
    {
        mpMap[liCount]->GenerateMap(this);
    }
}

cSeamList::~cSeamList()
{
    delete mpMap;
    mpMap=0;
}

void cSeamList::MapTexture(cTexture **lpTextures,c2DVf lfPosition)
{
 uint32 liClosest=Items();
 float lfClosest=10.0f;
 for(uint32 liCount=0;liCount<Items();++liCount)
 {
     float lfTemp=mpList[liCount].Distance(lfPosition);
    if(lfClosest>lfTemp)
    {
        liClosest=liCount;
        lfClosest=lfTemp;
    }
 }

 if(liClosest==Items()) return;

 SEAM_ID_TYPE liBaseSeam=mpList[liClosest].ClosestSeamID(lfPosition);

 cSeamTranslation *lpTranslation = new cSeamTranslation[miSeamSets];
 bool *lbTranslation = new bool[miSeamSets];
 for(SEAM_ID_TYPE liLoop=0;liLoop<miSeamSets;++liLoop)
 {
     lbTranslation[liLoop]=false;
 }
 lbTranslation[liBaseSeam]=true;
 lpTranslation[liBaseSeam]=lfPosition;

 bool lbRepeat=true;
 while(lbRepeat)
 {
     lbRepeat=false;
     for(SEAM_ID_TYPE liCount=0;liCount<miSeamSets;++liCount)
     {
         if(lbTranslation[liCount])
         {
             for(SEAM_ID_TYPE liLoop=0;liLoop<miSeamSets;++liLoop)
             {
                 if(liLoop!=liCount && !lbTranslation[liLoop])
                 {
                    int32 liSeam=FindSeamMirror(liCount,liLoop,lpTranslation[liCount].mvCentre);
                    if(liSeam>=0)
                    {
                        lpTranslation[liLoop]=mpList[liSeam].Map(lpTranslation[liCount],liCount);
                        lbTranslation[liLoop]=true;
                        lbRepeat=true;
                    }
                 }
             }
         }
     }
 }

 for(uint8 liCount=0;liCount<miTextures;++liCount)
 {
     for(SEAM_ID_TYPE liLoop=0;liLoop<miSeamSets;++liLoop)
     {
        mpMap[liCount]->WriteTexture(lpTextures[liCount],liLoop,lpTranslation[liLoop]);
     }
 }

 delete []lbTranslation;
 delete []lpTranslation;
};

int32 cSeamList::FindSeamMirror(SEAM_ID_TYPE liBase,SEAM_ID_TYPE liOther,c2DVf lfPosition)
{
 int32 liClosest=Items();
 float lfDistance=20.0f;
    for(uint32 liLoop=0;liLoop<Items();++liLoop)
    {
        if(mpList[liLoop].SeamMirror(liBase,liOther))
        {
            float lfTemp=mpList[liLoop].Distance(lfPosition);
            if(lfTemp<lfDistance)
            {
                liClosest=liLoop;
                lfDistance=lfTemp;
            }
        }
    }

    if(liClosest<Items()) return liClosest;
    else return -1;
};

cSeamAreaMap::cSeamAreaMap(cTexture *lpTexture)
{
    mpTexture=lpTexture;
    mpMap=new SEAM_ID_TYPE[lpTexture->Width()*lpTexture->Height()];
};

cSeamAreaMap::~cSeamAreaMap()
{
    delete []mpMap;
    mpMap=0;
};



void cSeamAreaMap::GenerateMap(cSeamList *lpList)
{
    memset(mpMap,SEAM_VOID_VALUE,sizeof(SEAM_ID_TYPE)*mpTexture->Width()*mpTexture->Height());

 for(uint32 liCount=0;liCount<lpList->Items();++liCount)
 {

     DrawLine(lpList->Item(liCount).Data[0].mvStart[0],lpList->Item(liCount).Data[0].mvStart[1],
          lpList->Item(liCount).Data[0].mvEnd[0],lpList->Item(liCount).Data[0].mvEnd[1],
          lpList->Item(liCount).Data[0].miTemplate);

     DrawLine(lpList->Item(liCount).Data[1].mvStart[0],lpList->Item(liCount).Data[1].mvStart[1],
          lpList->Item(liCount).Data[1].mvEnd[0],lpList->Item(liCount).Data[1].mvEnd[1],
          lpList->Item(liCount).Data[1].miTemplate);
 }

 SEAM_ID_TYPE *lpTemp=new SEAM_ID_TYPE[mpTexture->Width()*mpTexture->Height()];
 memcpy(lpTemp,mpMap,sizeof(SEAM_ID_TYPE)*mpTexture->Width()*mpTexture->Height());

 bool lbUpdated=true;
 while(lbUpdated)
 {
     lbUpdated=false;
     for(uint32 liX=0;liX<mpTexture->Width();++liX)
     {
         for(uint32 liY=0;liY<mpTexture->Height();++liY)
         {
            if(GetPixel(liX,liY)==SEAM_VOID_VALUE)
            {
                if(GetPixel(liX-1,liY)!=SEAM_VOID_VALUE) {lpTemp[liY*mpTexture->Width()+liX]=GetPixel(liX-1,liY); continue;}
                if(GetPixel(liX,liY-1)!=SEAM_VOID_VALUE) {lpTemp[liY*mpTexture->Width()+liX]=GetPixel(liX,liY-1); continue;}
                if(GetPixel(liX+1,liY)!=SEAM_VOID_VALUE) {lpTemp[liY*mpTexture->Width()+liX]=GetPixel(liX+1,liY); continue;}
                if(GetPixel(liX,liY+1)!=SEAM_VOID_VALUE) {lpTemp[liY*mpTexture->Width()+liX]=GetPixel(liX,liY-1); continue;}
                lbUpdated=true;
            }
         }
     }
  memcpy(mpMap,lpTemp,sizeof(SEAM_ID_TYPE)*mpTexture->Width()*mpTexture->Height());
 }
 delete []lpTemp;
};

SEAM_ID_TYPE cSeamAreaMap::GetPixel(uint32 liX,uint32 liY)
{
 if(liX<0 || liX>=mpTexture->Width() || liY<0 || liY>=mpTexture->Height()) return SEAM_VOID_VALUE;
 return mpMap[liY*mpTexture->Width()+liX];
};

void cSeamAreaMap::WriteTexture(cTexture *lpWrite,SEAM_ID_TYPE liSeam,cSeamTranslation lpTranslation)
{
    c2DVi Centre(lpTranslation.mvCentre[0]*mpTexture->Width(),lpTranslation.mvCentre[1]*mpTexture->Height());
    c2DVi Range;
    float lfCos=cos(lpTranslation.mfAngle);
    float lfSin=sin(lpTranslation.mfAngle);

    Range[0]=(lpWrite->Width()*lfCos+lpWrite->Height()*lfSin)*0.5;
    Range[1]=(lpWrite->Width()*lfSin+lpWrite->Height()*lfCos)*0.5;

    int32 liXStart,liXEnd;
    int32 liYStart,liYEnd;

    liXStart=Centre[0]-Range[0];
    liXEnd=Centre[0]+Range[0];
    liYStart=Centre[1]-Range[1];
    liYEnd=Centre[1]+Range[1];

    if(liXStart<0) liXStart=0;
    if(liXEnd>mpTexture->Width()) liXEnd=mpTexture->Width();
    if(liYStart<0) liXStart=0;
    if(liYEnd>mpTexture->Height()) liYEnd=mpTexture->Height();

    c2DVi PixelStart;
    PixelStart[0]=liXStart;
    PixelStart[1]=liYStart;
    c2DVi PixelPos;

    PixelPos[0]=PixelStart[0];

    liXStart-=Centre[0];
    liYStart-=Centre[1];

    liXEnd-=Centre[0];
    liYEnd-=Centre[1];

    for(int32 liX=liXStart;liX<liXEnd;++liX)
    {
        PixelPos[1]=PixelStart[1];
        for(int32 liY=-liYStart;liY<liYEnd;++liY)
        {
            c2DVi liRel;
            liRel=GetTextureCoordinates(lpWrite,c2DVi(liX,liY),lpTranslation.mfAngle);
//            mpTexture->Write(cRGBA(lpWrite->GetPixel(liRel)),PixelPos);
            if(lpWrite->Depth()==24) mpTexture->Write(cRGB(lpWrite->GetPixel(liRel)),PixelPos);
            if(lpWrite->Depth()==32) mpTexture->Write(cRGBA(lpWrite->GetPixel(liRel)),PixelPos);
            ++PixelPos[1];
        }
        ++PixelPos[0];
    }

}

c2DVi cSeamAreaMap::GetTextureCoordinates(cTexture *lpGet,c2DVi liRelPos,float lfAngle)
{
    c2DVi Return;
    float lfCos=cos(lfAngle);
    float lfSin=sin(lfAngle);
    Return[0]=liRelPos[1]*lfSin-liRelPos[0]*lfCos;
    Return[1]=liRelPos[1]*lfCos-liRelPos[0]*lfSin;
    Return[0]+=lpGet->Width()*0.5;
    Return[0]+=lpGet->Height()*0.5;
    return Return;
}

void cSeamAreaMap::WriteToTexture(c2DVi liPos,SEAM_ID_TYPE liSeam,cRGBA Color)
{
    if(InSeamArea(liPos,liSeam)) mpTexture->Write(Color,liPos);
}

void cSeamAreaMap::WriteToTexture(c2DVi liPos,SEAM_ID_TYPE liSeam,cRGB Color)
{
    if(InSeamArea(liPos,liSeam)) mpTexture->Write(Color,liPos);
}

bool cSeamAreaMap::InSeamArea(c2DVi lvLocation,SEAM_ID_TYPE liSeam)
{
 if(mpMap[lvLocation[1]*mpTexture->Width()+lvLocation[0]]==liSeam) return 1;
 return 0;
};

void cSeamAreaMap::DrawLine( const float x1s, const float y1s, const float x2s, const float y2s, SEAM_ID_TYPE liSeam)
{
    float x1,x2,y1,y2;
    x1=x1s;
    x2=x2s;
    y1=y1s;
    y2=y2s;
        // Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if(steep)
	{
	    float lfTemp;
	    lfTemp=x1;
	    x1=y1;
	    y1=lfTemp;

	    lfTemp=y2;
	    y2=x2;
	    x2=lfTemp;
		//std::swap(x1, y1);
		//std::swap(x2, y2);
	}

	if(x1 > x2)
	{
	    float lfTemp;
	    lfTemp=x1;
	    x1=x2;
	    x2=lfTemp;

	    lfTemp=y1;
	    y1=y2;
	    y2=lfTemp;
		//std::swap(x1, x2);
		//std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for(int x=(int)x1; x<maxX; x++)
	{
		if(steep)
                {
                        SetPixel(y,x, liSeam);
                }
		else
                {
                        SetPixel(x,y, liSeam);
                }

                error -= dy;
	        if(error < 0)
	        {
		        y += ystep;
		        error += dx;
	        }
	}
}

void cSeamAreaMap::SetPixel(int liX,int liY,SEAM_ID_TYPE liSeam)
{
 mpMap[liY*mpTexture->Width()+liX]=liSeam;
}

void cSeamList::GenerateSeamList(cMesh *lpMesh)
{
    FindSeams(lpMesh);
/*
    cSeamPair lpTemp;

    for(uint32 liFace=0;liFace<lpMesh->Faces();++liFace)
    {
        FACE_TYPE *lpFaceData=lpMesh->Face(liFace);

        for(uint32 liOther=0;liOther<liFace;++liOther)
        {

            FACE_TYPE *lpOtherData=lpMesh->Face(liOther);
            uint8 liFound=0;
            uint8 liContained[6];

            if(lpMesh->VertexMatch(lpFaceData[0],lpOtherData[0],0.001f) && !lpMesh->UVMatch(lpFaceData[0],lpOtherData[0],0.001f)){ liContained[liFound*2]=0; liContained[liFound*2+1]=0; ++liFound; }
            if(lpMesh->VertexMatch(lpFaceData[0],lpOtherData[1],0.001f) && !lpMesh->UVMatch(lpFaceData[0],lpOtherData[1],0.001f)){ liContained[liFound*2]=0; liContained[liFound*2+1]=1; ++liFound; }
            if(lpMesh->VertexMatch(lpFaceData[0],lpOtherData[2],0.001f) && !lpMesh->UVMatch(lpFaceData[0],lpOtherData[2],0.001f)){ liContained[liFound*2]=0; liContained[liFound*2+1]=2; ++liFound; }

            if(lpMesh->VertexMatch(lpFaceData[1],lpOtherData[0],0.001f) && !lpMesh->UVMatch(lpFaceData[1],lpOtherData[0],0.001f)){ liContained[liFound*2]=1; liContained[liFound*2+1]=0; ++liFound; }
            if(lpMesh->VertexMatch(lpFaceData[1],lpOtherData[1],0.001f) && !lpMesh->UVMatch(lpFaceData[1],lpOtherData[1],0.001f)){ liContained[liFound*2]=1; liContained[liFound*2+1]=1; ++liFound; }
            if(lpMesh->VertexMatch(lpFaceData[1],lpOtherData[2],0.001f) && !lpMesh->UVMatch(lpFaceData[1],lpOtherData[2],0.001f)){ liContained[liFound*2]=1; liContained[liFound*2+1]=2; ++liFound; }

            if(lpMesh->VertexMatch(lpFaceData[2],lpOtherData[0],0.001f) && !lpMesh->UVMatch(lpFaceData[2],lpOtherData[0],0.001f)){ liContained[liFound*2]=2; liContained[liFound*2+1]=0; ++liFound; }
            if(lpMesh->VertexMatch(lpFaceData[2],lpOtherData[1],0.001f) && !lpMesh->UVMatch(lpFaceData[2],lpOtherData[1],0.001f)){ liContained[liFound*2]=2; liContained[liFound*2+1]=1; ++liFound; }
            if(lpMesh->VertexMatch(lpFaceData[2],lpOtherData[2],0.001f) && !lpMesh->UVMatch(lpFaceData[2],lpOtherData[2],0.001f)){ liContained[liFound*2]=2; liContained[liFound*2+1]=2; ++liFound; }

            if(liFound==2 && (liContained[0]!=liContained[2] && liContained[0]!=liContained[3] && liContained[1]!=liContained[2] && liContained[1]!=liContained[3]))
            {
                printf("liContained : %u %u\n",liContained[0],liContained[1]);
                printf("FAce : %u %u\n",lpFaceData[liContained[0]],lpFaceData[liContained[1]]);
                lpTemp.Data[0].mvStart=c2DVf(lpMesh->UV(lpFaceData[liContained[0]]));
                lpTemp.Data[0].mvEnd=c2DVf(lpMesh->UV(lpFaceData[liContained[1]]));
                lpTemp.Data[0].miTemplate=SEAM_VOID_VALUE;

                printf("liContained : %u %u\n",liContained[2],liContained[3]);
                printf("FAce : %u %u\n",lpFaceData[liContained[2]],lpFaceData[liContained[3]]);
                lpTemp.Data[1].mvStart=c2DVf(lpMesh->UV(lpFaceData[liContained[2]]));
                lpTemp.Data[1].mvEnd=c2DVf(lpMesh->UV(lpFaceData[liContained[3]]));
                lpTemp.Data[1].miTemplate=SEAM_VOID_VALUE;

                Add(&lpTemp);
            }

            if(liFound==2 &&
               (liContained[0]!=liContained[2] && liContained[0]!=liContained[3] && liContained[1]!=liContained[2] && liContained[1]!=liContained[3]) &&
               (liContained[0]!=liContained[4] && liContained[0]!=liContained[5] && liContained[1]!=liContained[4] && liContained[1]!=liContained[5]) &&
               (liContained[2]!=liContained[4] && liContained[2]!=liContained[5] && liContained[3]!=liContained[4] && liContained[3]!=liContained[5]))
            {
                printf("3 match\n");
                lpTemp.Data[0].mvStart=c2DVf(lpMesh->UV(lpFaceData[liContained[0]]));
                lpTemp.Data[0].mvEnd=c2DVf(lpMesh->UV(lpFaceData[liContained[1]]));
                lpTemp.Data[0].miTemplate=SEAM_VOID_VALUE;

                lpTemp.Data[1].mvStart=c2DVf(lpMesh->UV(lpFaceData[liContained[2]]));
                lpTemp.Data[1].mvEnd=c2DVf(lpMesh->UV(lpFaceData[liContained[3]]));
                lpTemp.Data[1].miTemplate=SEAM_VOID_VALUE;

                Add(&lpTemp);

                lpTemp.Data[0].mvStart=c2DVf(lpMesh->UV(lpFaceData[liContained[4]]));
                lpTemp.Data[0].mvEnd=c2DVf(lpMesh->UV(lpFaceData[liContained[5]]));
                lpTemp.Data[0].miTemplate=SEAM_VOID_VALUE;

                Add(&lpTemp);

                lpTemp.Data[1].mvStart=c2DVf(lpMesh->UV(lpFaceData[liContained[0]]));
                lpTemp.Data[1].mvEnd=c2DVf(lpMesh->UV(lpFaceData[liContained[1]]));
                lpTemp.Data[1].miTemplate=SEAM_VOID_VALUE;

                Add(&lpTemp);
            }

        }
    }
*/
    uint32 liTemplates=0;
        for(uint32 liCount=0;liCount<Items();++liCount)
        {
            if(mpList[liCount].Data[0].miTemplate==SEAM_VOID_VALUE)
            {
                mpList[liCount].Data[0].miTemplate=liTemplates;
                ExtendSeam(mpList[liCount].Data[0]);
                ++liTemplates;
            }
            if(mpList[liCount].Data[1].miTemplate==SEAM_VOID_VALUE)
            {
                mpList[liCount].Data[1].miTemplate=liTemplates;
                ExtendSeam(mpList[liCount].Data[1]);
                ++liTemplates;
            }
        }
    miSeamSets=liTemplates;

        for(uint32 liCount=0;liCount<liTemplates;++liCount)
        {

            c2DVf Centre;
            uint32 liSeams=0;
            for(uint32 liLoop=0;liLoop<Items();++liLoop)
            {
              if(mpList[liLoop].Data[0].miTemplate==liCount)
              {
                Centre+=mpList[liLoop].Data[0].mvStart;
                Centre+=mpList[liLoop].Data[0].mvEnd;
                ++liSeams;
              }
              if(mpList[liLoop].Data[1].miTemplate==liCount)
              {
                Centre+=mpList[liLoop].Data[1].mvStart;
                Centre+=mpList[liLoop].Data[1].mvEnd;
                ++liSeams;
              }
            }

            Centre*=1.0f/liSeams;
            double AngleSum=0.0;
                c2DVf lfStart;
                c2DVf lfEnd;
            for(uint32 liLoop=0;liLoop<Items();++liLoop)
            {
              if(mpList[liLoop].Data[0].miTemplate==liCount)
              {
                lfStart=mpList[liLoop].Data[0].mvStart-Centre;
                lfEnd=mpList[liLoop].Data[0].mvEnd-Centre;
                AngleSum+=lfStart.SignedAngle(lfEnd);
              }
              if(mpList[liLoop].Data[1].miTemplate==liCount)
              {
                lfStart=mpList[liLoop].Data[1].mvStart-Centre;
                lfEnd=mpList[liLoop].Data[1].mvEnd-Centre;
                AngleSum+=lfStart.SignedAngle(lfEnd);
              }
            }

            bool CW;
            bool Found=false;
            if(AngleSum>(2*WT_PI)-0.1f && AngleSum<(2*WT_PI)+0.1f) {Found=true; CW=true;}
            if(AngleSum>-0.1f-(2*WT_PI) && AngleSum<0.1f-(2*WT_PI)) {Found=true; CW=false;}

            if(!Found)
            {

            }
            else
            {
                for(uint32 liLoop=0;liLoop<Items();++liLoop)
                {
                  if(mpList[liLoop].Data[0].miTemplate==liCount){ mpList[liLoop].Data[0].CalculateVectors(CW);}
                  if(mpList[liLoop].Data[1].miTemplate==liCount){ mpList[liLoop].Data[1].CalculateVectors(CW);}
                }
            }

        }



}

void cSeamList::FindSeams(cMesh *lpMesh)
{
 for(uint32 liFace1=0;liFace1<lpMesh->Faces();++liFace1)
 {
     FACE_TYPE *lpFace1=lpMesh->Face(liFace1);
     for(uint32 liFace2=0;liFace2<liFace1;++liFace2)
     {
         FACE_TYPE *lpFace2=lpMesh->Face(liFace2);
        cSeamPair lsPair=lpMesh->UVSeam(lpFace1,lpFace2);
        if(lsPair.Data[0].miTemplate==SEAM_VOID_VALUE)
        {
            Add(&lsPair);
        }
     }
 }
}
/*
    uint8 liFlags=0;
    if(VertexMatch(mpFaces[Face1*3],mpFaces[Face2*3],0.001f) || VertexMatch(mpFaces[Face1*3],mpFaces[Face2*3+1],0.001f) || VertexMatch(mpFaces[Face1*3],mpFaces[Face2*3+2],0.001f) ) liFlags=liFlags|0x1;
    if(VertexMatch(mpFaces[Face1*3+1],mpFaces[Face2*3],0.001f) || VertexMatch(mpFaces[Face1*3+1],mpFaces[Face2*3+1],0.001f) || VertexMatch(mpFaces[Face1*3+1],mpFaces[Face2*3+2],0.001f) ) liFlags=liFlags|0x2;
    if(VertexMatch(mpFaces[Face1*3+2],mpFaces[Face2*3],0.001f) || VertexMatch(mpFaces[Face1*3+2],mpFaces[Face2*3+1],0.001f) || VertexMatch(mpFaces[Face1*3+2],mpFaces[Face2*3+2],0.001f) ) liFlags=liFlags|0x4;

    if(liFlags==3 || liFlags==5 || liFlags==6) return 1;*/


void cSeamList::ExtendSeam(cSeamData lpData)
{
    for(uint32 liLoop=0;liLoop<Items();++liLoop)
    {
        if(mpList[liLoop].Data[0].miTemplate==SEAM_VOID_VALUE)
        {
         if(lpData.mvStart==mpList[liLoop].Data[0].mvStart) {mpList[liLoop].Data[0].SwapDirection(); mpList[liLoop].Data[0].miTemplate=lpData.miTemplate; ExtendSeam(mpList[liLoop].Data[0]); break;}
         if(lpData.mvEnd==mpList[liLoop].Data[0].mvStart) {mpList[liLoop].Data[0].miTemplate=lpData.miTemplate; ExtendSeam(mpList[liLoop].Data[0]); break;}
         if(lpData.mvStart==mpList[liLoop].Data[0].mvEnd) {mpList[liLoop].Data[0].miTemplate=lpData.miTemplate; ExtendSeam(mpList[liLoop].Data[0]); break;}
         if(lpData.mvEnd==mpList[liLoop].Data[0].mvEnd) {mpList[liLoop].Data[0].SwapDirection(); mpList[liLoop].Data[0].miTemplate=lpData.miTemplate; ExtendSeam(mpList[liLoop].Data[0]); break;}
        }

        if(mpList[liLoop].Data[1].miTemplate==SEAM_VOID_VALUE)
        {
         if(lpData.mvStart==mpList[liLoop].Data[1].mvStart) {mpList[liLoop].Data[1].SwapDirection(); mpList[liLoop].Data[1].miTemplate=lpData.miTemplate; ExtendSeam(mpList[liLoop].Data[1]); break;}
         if(lpData.mvEnd==mpList[liLoop].Data[1].mvStart) {mpList[liLoop].Data[1].miTemplate=lpData.miTemplate; ExtendSeam(mpList[liLoop].Data[1]); break;}
         if(lpData.mvStart==mpList[liLoop].Data[1].mvEnd) {mpList[liLoop].Data[1].miTemplate=lpData.miTemplate; ExtendSeam(mpList[liLoop].Data[1]); break;}
         if(lpData.mvEnd==mpList[liLoop].Data[1].mvEnd) {mpList[liLoop].Data[1].SwapDirection(); mpList[liLoop].Data[1].miTemplate=lpData.miTemplate; ExtendSeam(mpList[liLoop].Data[1]); break;}
        }
    }
}



