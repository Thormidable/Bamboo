#include "stdafx.h"
#include "../../WTBamboo.h"

#if WT_FULL_VERSION_BAMBOO

cMessageFeedItem::cMessageFeedItem(string lsMessage,float lfDelay,cFont *lpFont,cRGBA lcColor,float lfSize,cCamera *lpCamera)
{
   mpText=_CREATE(cText(lpCamera));
   mpText->Shader("TextProgram");
   mpText->SetUniform("TextColor",lcColor.Color());
   mpText->Size(lfSize);
   mpText->AddFont(lpFont);
   mpText->Text(lsMessage);
   mpText->Transparency(2);
   mfDelay=lfDelay;
   msMessage=lsMessage;
};

bool cMessageFeedItem::Update(c3DVf &lfPos)
{
    mfDelay-=WT_FRAME_TIME;
    if(mfDelay<0.0f) return 0;
    mpText->Position(lfPos.v);
    return 1;
}

cMessageFeedItem::~cMessageFeedItem()
{
 _KILL(mpText);
 mpText=0;
}

void cMessageFeedItem::Resize(float lfSize)
{
    mpText->Size(lfSize);
};

cMessageFeed::cMessageFeed(uint8 liItems,cTexture *lpBox,cRGBA lsBoxColor,cFont *lpFont,cRGBA lsFontColor,c2DVf lfPos,cCamera *lpCamera)
{
    mfItemSize=15.0f;
    mfBoxSize=325.0f;
    miTransparency=1;
    miSpaces=liItems;
    miItems=0;
    mpItems=new cMessageFeedItem*[miSpaces];

    mpBox=new cImage(lpCamera);
    mpBox->Shader("Image2DUniformColorProgram");
    mpBox->AddTexture(lpBox);
    mpBoxColor=lsBoxColor;
    mpBox->SetUniform("UniformColor",mpBoxColor.Color());
    mpBox->Width(mfBoxSize);
    mpBox->Height(mfItemSize*(miSpaces+3));
	mpBox->Transparency(miTransparency);

    mpBox->Position(lfPos.v);

    mpFont=lpFont;
    mpFontColor=lsFontColor;

};

void cMessageFeed::Transparency(uint8 liTrans)
{
    miTransparency=liTrans;
    mpBox->Transparency(miTransparency);
}

void cMessageFeed::Font(cFont *lpFont,cRGBA lsFontColor)
{
    mpFont=lpFont;
    mpFontColor=lsFontColor;
};

void cMessageFeed::Box(cTexture *lpBox,cRGBA lsBoxColor)
{
    mpBox->ClearTextureStack();
    mpBox->AddTexture(lpBox);
    mpBoxColor=lsBoxColor;
};

void cMessageFeed::Position(c3DVf lfPos)
{
    mpBox->Position(lfPos.v);
}
void cMessageFeed::Position(c2DVf lfPos)
{
    mpBox->Position(lfPos[0],lfPos[1],0.0f);
};
void cMessageFeed::Position(float lfX,float lfY)
{
    mpBox->Position(lfX,lfY,0.0f);
};
void cMessageFeed::AddMessage(string lsMessage,float lfDelay)
{
    if(miItems<miSpaces)
    {
        mpItems[miItems]=new cMessageFeedItem(lsMessage,lfDelay,mpFont,mpFontColor,mfItemSize,mpBox->Camera());
        mpItems[miItems++]->mpText->Transparency(miTransparency+1);
    }
    else
    {
        delete mpItems[0];
        memmove(mpItems,&mpItems[1],sizeof(cMessageFeedItem*)*(miItems-1));
        mpItems[miItems-1]=new cMessageFeedItem(lsMessage,lfDelay,mpFont,mpFontColor,mfItemSize,mpBox->Camera());
        mpItems[miItems-1]->mpText->Transparency(miTransparency+1);
    }
};

void cMessageFeed::Run()
{
 c3DVf lfPos=mpBox->Position();
 lfPos[0]+=mfItemSize-mfBoxSize*0.5;
 lfPos[1]+=(mfItemSize*(miSpaces-2))*0.5f;
 uint8 liSpare=0;
 for(uint8 liCount=0;liCount<miItems;++liCount)
 {
     if(!mpItems[liCount]->Update(lfPos))
     {
         delete mpItems[liCount];
     }
     else
     {
        if(liCount!=liSpare){mpItems[liSpare]=mpItems[liCount];}
        ++liSpare;
     }
     lfPos[1]-=mfItemSize;
 }
 miItems=liSpare;

 if(!miItems && mbHide)
 {
  _SLEEP(mpBox);
 }
 else
 {
  _WAKE(mpBox);
 }
};

void cMessageFeed::Stop()
{

};


void cMessageFeed::ItemsWide(uint8 liWidth)
{
    mfBoxSize=liWidth*mfItemSize;
    mpBox->Width(mfBoxSize);
};

void cMessageFeed::ItemHeight(float lfHeight)
{
  for(uint8 liCount=0;liCount<miItems;++liCount)
  {
   mpItems[liCount]->Resize(lfHeight);
  }
  mpBox->Height(mfItemSize*(miSpaces+3));
  mpBox->Width(mfBoxSize);
  mfItemSize=lfHeight;
};

cMessageFeed::~cMessageFeed()
{
    _KILL(mpBox);
    uint8 liCount;
 for(liCount=0;liCount<miItems;++liCount)
 {
  delete mpItems[liCount];
  mpItems[liCount]=0;
 }

 while(liCount<miSpaces)
 {
     mpItems[liCount++]=0;
 }

 delete []mpItems;
 mpItems=0;
};

void cMessageFeed::UpdatePosition()
{
 mpBox->Position(_WINDOW->RenderAreaWidth()-mfBoxSize*0.5,_WINDOW->RenderAreaHeight()-mfItemSize*(miSpaces+1)*0.5,0.0f);
}

float cMessageFeed::BoxWidth(){return mfBoxSize;};
float cMessageFeed::ItemHeight(){return mfItemSize;};
uint8 cMessageFeed::Items(){return miItems;};
uint8 cMessageFeed::Spaces(){return miSpaces;};
void cMessageFeed::Spaces(uint8 liSpaces)
{
    cMessageFeedItem **lpTemp=new cMessageFeedItem*[liSpaces];
    if(miItems<liSpaces)
    {
        memcpy(lpTemp,mpItems,sizeof(cMessageFeedItem*)*miItems);
    }
    else
    {
        memcpy(lpTemp,mpItems,sizeof(cMessageFeedItem*)*liSpaces);

        for(uint8 liCount=liSpaces;liCount<miItems;++liCount)
        {
            delete mpItems[liCount];
        }
        miItems=liSpaces;
    }
    memset(mpItems,0,sizeof(cMessageFeedItem*)*miSpaces);

    delete []mpItems;
    mpItems=lpTemp;

    miSpaces=liSpaces;
};

void cMessageFeed::HideWhenEmpty(bool lbState)
{
  mbHide=lbState;
};

#endif
