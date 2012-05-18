#ifndef __WTCSEAMLESSTEXTURECLASSES_H__
#define __WTCSEAMLESSTEXTURECLASSES_H__


class cSeamTranslation
{
public:
    cSeamTranslation();
    cSeamTranslation(c2DVf lvCentre,float lfAngle);
    c2DVf mvCentre;
    float mfAngle;

    void operator=(cSeamTranslation lpOther);
    void operator=(c2DVf &lpOther);
    void operator=(float &lpOther);
};

class cSeamTranslationList
{
    cSeamTranslation *mpTranslations;
    SEAM_ID_TYPE miTemplates;
public:
    cSeamTranslationList(SEAM_ID_TYPE liTemplates);
    cSeamTranslation &operator[](SEAM_ID_TYPE liTemplate);

};

class cSeamData
{
public:
    c2DVf mvStart,mvEnd;
    SEAM_ID_TYPE miTemplate;
    c2DVf Vector;
    c2DVf Perpendicular;

    cSeamData &operator=(cSeamData &lpOther);
    void CalculateVectors(bool CW);
    void SwapDirection();
};

class cSeamPair
{
public:

    cSeamPair();
    cSeamPair(c2DVf lvStart1,c2DVf lvEnd1,bool CW1, SEAM_ID_TYPE liTemplate1,c2DVf lvStart2,c2DVf lvEnd2,bool CW2, SEAM_ID_TYPE liTemplate2);
    cSeamPair &operator=(cSeamPair &lpOther);

    cSeamData Data[2];

    cSeamTranslation Map(cSeamTranslation lfTranslation,SEAM_ID_TYPE liTemplate);
    float Distance(c2DVf Position);
    SEAM_ID_TYPE ClosestSeamID(c2DVf Position);

    bool SeamMirror(SEAM_ID_TYPE liBase,SEAM_ID_TYPE liOther);


};

class cSeamList;

class cSeamAreaMap
{
    cTexture *mpTexture;
    SEAM_ID_TYPE *mpMap;

public:
    cSeamAreaMap(cTexture *lpTexture);
    ~cSeamAreaMap();

    void GenerateMap(cSeamList *lpList);

    void WriteTexture(cTexture *lpWrite,SEAM_ID_TYPE liSeam,cSeamTranslation lpTranslation);
    void WriteToTexture(c2DVi liPos,SEAM_ID_TYPE liSeam,cRGBA Color);
    void WriteToTexture(c2DVi liPos,SEAM_ID_TYPE liSeam,cRGB Color);
    bool InSeamArea(c2DVi lvLocation,SEAM_ID_TYPE liSeam);
    SEAM_ID_TYPE GetPixel(uint32 liX,uint32 liY);

    void DrawLine( const float x1, const float y1, const float x2, const float y2,SEAM_ID_TYPE liSeam);
    void SetPixel(int liX,int liY,SEAM_ID_TYPE liValue);

    c2DVi GetTextureCoordinates(cTexture *lpGet,c2DVi liRelPos,float lfAngle);

};

class cMesh;

class cSeamList : public  cLimitedList<cSeamPair>
{
    cSeamAreaMap **mpMap;
    uint8 miTextures;
    SEAM_ID_TYPE miSeamSets;
public:

    cSeamList(uint8 liTextures, cTexture **lpTextures);
    ~cSeamList();

    void GenerateAreaMap();
    void GenerateSeamList(cMesh *lpMesh);
    void FindSeams(cMesh *lpMesh);

    void MapTexture(cTexture **lpTextures, c2DVf lfPosition);

    int32 FindSeamMirror(SEAM_ID_TYPE liBase,SEAM_ID_TYPE liOther,c2DVf lfPosition);

    //void BuildTemplate(uint32 liFace,SEAM_ID_TYPE SeamID,bool *lbDone);
    void ExtendSeam(cSeamData lpData);

    void BlendTexture(cTexture *lpTextures,c2DVf lfPosition);


};


#endif
