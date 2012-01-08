#include "../WTDivWin.h"

    float cRGB::R(){return color[0];};
    float cRGB::G(){return color[1];};
    float cRGB::B(){return color[2];};
    float *cRGB::Color(){return color;};
    float *cRGB::operator=(float*lpOther){memcpy(color,lpOther,sizeof(float)*3); return lpOther;};
    cRGB &cRGB::operator=(cRGB &lpOther){ memcpy(color,lpOther.Color(),sizeof(float)*3); return *this;};
    cRGB *cRGB::operator=(cRGB *lpOther){ memcpy(color,lpOther->Color(),sizeof(float)*3); return this;};
    cRGB &cRGB::operator=(cRGBA &lpOther){ memcpy(color,lpOther.Color(),sizeof(float)*3); return *this;};
    cRGB *cRGB::operator=(cRGBA *lpOther){ memcpy(color,lpOther->Color(),sizeof(float)*3); return this;};
    float &cRGB::operator[](uint32 liPos){return color[liPos];};

    float cRGBA::R(){return color[0];};
    float cRGBA::G(){return color[1];};
    float cRGBA::B(){return color[2];};
    float cRGBA::A(){return color[3];};
    float *cRGBA::Color(){return color;};
    float *cRGBA::operator=(float*lpOther){memcpy(color,lpOther,sizeof(float)*4); return lpOther;};
    cRGBA &cRGBA::operator=(cRGB &lpOther){ memcpy(color,lpOther.Color(),sizeof(float)*3); color[3]=1.0f; return *this;};
    cRGBA *cRGBA::operator=(cRGB *lpOther){ memcpy(color,lpOther->Color(),sizeof(float)*3); color[3]=1.0f; return this;};
    cRGBA &cRGBA::operator=(cRGBA &lpOther){ memcpy(color,lpOther.Color(),sizeof(float)*4); return *this;};
    cRGBA *cRGBA::operator=(cRGBA *lpOther){ memcpy(color,lpOther->Color(),sizeof(float)*4); return this;};
    float &cRGBA::operator[](uint32 liPos){return color[liPos];};

void cRGBA::Set(float lfR,float lfG,float lfB,float lfA)
{
 color[0]=lfR;
 color[1]=lfG;
 color[2]=lfB;
 color[3]=lfA;
}

void cRGB::Set(float lfR,float lfG,float lfB)
{
 color[0]=lfR;
 color[1]=lfG;
 color[2]=lfB;
}

cRGB::cRGB(float lfR,float lfG,float lfB)
{
    color[0]=lfR;
    color[1]=lfG;
    color[2]=lfB;
}

cRGB::cRGB(float *lfRGB)
{
    memcpy(color,lfRGB,sizeof(float)*3);
}

cRGBA::cRGBA(float lfR,float lfG,float lfB,float lfA)
{
    color[0]=lfR;
    color[1]=lfG;
    color[2]=lfB;
    color[2]=lfA;
}
cRGBA::cRGBA(float *lfRGB)
{
    memcpy(color,lfRGB,sizeof(float)*4);
}

cRGBA &cRGBA::operator=(c3DVf &lpOther)
{
memcpy(color,lpOther.v,sizeof(float)*3);
return *this;
};
cRGBA *cRGBA::operator=(c3DVf *lpOther)
{
    memcpy(color,lpOther->v,sizeof(float)*3);
    return this;
};
cRGBA &cRGBA::operator=(c4DVf &lpOther)
{
    memcpy(color,lpOther.v,sizeof(float)*4);
    return *this;
};
cRGBA *cRGBA::operator=(c4DVf *lpOther)
{
    memcpy(color,lpOther->v,sizeof(float)*4);
    return this;
};

cRGB &cRGB::operator=(c3DVf &lpOther)
{
    memcpy(color,lpOther.v,sizeof(float)*3);
    return *this;

}
cRGB *cRGB::operator=(c3DVf *lpOther)
{
    memcpy(color,lpOther->v,sizeof(float)*3);
    return this;
}
