#ifndef __WTCMESSAGEFEED_H__
#define __WTCMESSAGEFEED_H__

#if WT_FULL_VERSION_BAMBOO

class cMessageFeed;

class cMessageFeedItem
{
    friend class cMessageFeed;
    float mfDelay;
    public:

        cMessageFeedItem(string lsMessage,float lfDelay=2.0f,cFont *lpFont=_GET_FONT_FILE("Ecliptic"),cRGBA lcColor=cRGBA(0.0f,0.0f,0.0f,1.0f),float lfSize=15.0f,cCamera *lpCamera=_CAMERA);
        ~cMessageFeedItem();
        bool Update(c3DVf &lfPos);
        void Resize(float lfSize);

        string msMessage;
        cText *mpText;
};

class cMessageFeed : public cProcess
{
    float mfItemSize;
    float mfBoxSize;
    uint8 miItems;
    uint8 miSpaces;
    uint8 miTransparency;
    bool mbHide;
public:
    cFont *mpFont;
    cRGBA mpFontColor;
    cImage *mpBox;
    cRGBA mpBoxColor;
    cMessageFeedItem **mpItems;
	
        cMessageFeed(uint8 liItems,cTexture *lpBox,cRGBA lsBoxColor=cRGBA(0.0f,1.0f,1.0f,1.0f),cFont *lpFont=_GET_FONT_FILE("Ecliptic"),cRGBA lsFontColor=cRGBA(0.0f,0.0f,0.0f,1.0f),c2DVf lfPos=c2DVf(gpWindow->RenderAreaWidth()*0.5,gpWindow->RenderAreaHeight()*0.5),cCamera *lpCamera=_CAMERA);
        void Font(cFont *lpFont,cRGBA lsColor=cRGBA(0.0f,0.0f,0.0f,1.0f));
        void Box(cTexture *lpBox,cRGBA lsColor=cRGBA(0.0f,1.0f,1.0f,1.0f));
        void Position(c3DVf lfPos);
        void Position(c2DVf lfPos);
        void Position(float lfX,float lfY);
        void AddMessage(string lsMessage,float lfDelay=2.0f);
        void Run();
        void Stop();
        void UpdatePosition();
        void ItemsWide(uint8 liWidth);
        void ItemHeight(float lfHeight);
        void Transparency(uint8 liTrans);
        float BoxWidth();
        float ItemHeight();
        uint8 Items();
        uint8 Spaces();
        void Spaces(uint8 liSpaces);
	void HideWhenEmpty(bool lbState);
        ~cMessageFeed();

};

#endif

#endif
