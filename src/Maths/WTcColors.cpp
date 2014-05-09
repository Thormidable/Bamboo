#include "stdafx.h"
#include "../WTBamboo.h"

cRGBA::cRGBA(uint8 *lfRGBA)
{
    color[0]=lfRGBA[0]/255;
    color[1]=lfRGBA[1]/255;
    color[2]=lfRGBA[2]/255;
    color[3]=lfRGBA[3]/255;
};

cRGB::cRGB(uint8 *lfRGB)
{
    color[0]=lfRGB[0]/255;
    color[1]=lfRGB[1]/255;
    color[2]=lfRGB[2]/255;
};

    float cRGB::R(){return color[0];};
    float cRGB::G(){return color[1];};
    float cRGB::B(){return color[2];};
    float *cRGB::Color(){return color;};
    cRGB cRGB::operator=(float*lpOther){memcpy(color,lpOther,sizeof(float)*3); return lpOther;};
    cRGB cRGB::operator=(cRGB lpOther){ memcpy(color,lpOther.Color(),sizeof(float)*3); return *this;};
    cRGB cRGB::operator=(cRGB *lpOther){ memcpy(color,lpOther->Color(),sizeof(float)*3); return *this;};
    cRGB cRGB::operator=(cRGBA lpOther){ memcpy(color,lpOther.Color(),sizeof(float)*3); return *this;};
    cRGB cRGB::operator=(cRGBA *lpOther){ memcpy(color,lpOther->Color(),sizeof(float)*3); return *this;};
    float &cRGB::operator[](uint32 liPos){return color[liPos];};

    float cRGBA::R(){return color[0];};
    float cRGBA::G(){return color[1];};
    float cRGBA::B(){return color[2];};
    float cRGBA::A(){return color[3];};
    float *cRGBA::Color(){return color;};
    cRGBA cRGBA::operator=(float*lpOther){memcpy(color,lpOther,sizeof(float)*4); return lpOther;};
    cRGBA cRGBA::operator=(cRGB lpOther){ memcpy(color,lpOther.Color(),sizeof(float)*3); color[3]=1.0f; return *this;};
    cRGBA cRGBA::operator=(cRGB *lpOther){ memcpy(color,lpOther->Color(),sizeof(float)*3); color[3]=1.0f; return *this;};
    cRGBA cRGBA::operator=(cRGBA lpOther){ memcpy(color,lpOther.Color(),sizeof(float)*4); return *this;};
    cRGBA cRGBA::operator=(cRGBA *lpOther){ memcpy(color,lpOther->Color(),sizeof(float)*4); return *this;};
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
    color[3]=lfA;
}
cRGBA::cRGBA(float *lfRGB)
{
    memcpy(color,lfRGB,sizeof(float)*4);
}


void cRGB::R(float lfR){color[0]=lfR;};
void cRGB::G(float lfG){color[1]=lfG;};
void cRGB::B(float lfB){color[2]=lfB;};
void cRGBA::R(float lfR){color[0]=lfR;};
void cRGBA::G(float lfG){color[1]=lfG;};
void cRGBA::B(float lfB){color[2]=lfB;};
void cRGBA::A(float lfA){color[3]=lfA;};

cRGB::cRGB(c3DVf lfOther)
{
    memcpy(color,lfOther.v,sizeof(float)*3);
};

cRGBA::cRGBA(c4DVf lfOther)
{
    memcpy(color,lfOther.v,sizeof(float)*4);
};
cRGB::cRGB(c4DVf lfOther)
{
    memcpy(color,lfOther.v,sizeof(float)*3);
};

cRGBA::cRGBA(c3DVf lfOther)
{
    memcpy(color,lfOther.v,sizeof(float)*3);
    color[3]=1.0f;
};

    cRGBA cRGBA::operator+(float lpOther)
    {
        cRGBA lfReturn;
        lfReturn[0]=R()+lpOther;
        lfReturn[1]=G()+lpOther;
        lfReturn[2]=B()+lpOther;
        lfReturn[3]=A()+lpOther;
        return lfReturn;
    };
    cRGBA cRGBA::operator+(float *lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()+lpOther[0];
        lfReturn[1]=G()+lpOther[1];
        lfReturn[2]=B()+lpOther[2];
        lfReturn[3]=A()+lpOther[3];
        return lfReturn;
    };
    cRGBA cRGBA::operator+(cRGB lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()+lpOther[0];
        lfReturn[1]=G()+lpOther[1];
        lfReturn[2]=B()+lpOther[2];
        lfReturn[3]=A();
        return lfReturn;
    };
    cRGBA cRGBA::operator+(cRGB *lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()+lpOther->R();
        lfReturn[1]=G()+lpOther->G();
        lfReturn[2]=B()+lpOther->B();
        lfReturn[3]=A();
        return lfReturn;
    };
    cRGBA cRGBA::operator+(cRGBA lpOther)
            {
        cRGBA lfReturn;
        lfReturn[0]=R()+lpOther[0];
        lfReturn[1]=G()+lpOther[1];
        lfReturn[2]=B()+lpOther[2];
        lfReturn[3]=A()+lpOther[3];
        return lfReturn;
    };
    cRGBA cRGBA::operator+(cRGBA *lpOther)
            {
        cRGBA lfReturn;
        lfReturn[0]=R()+lpOther->R();
        lfReturn[1]=G()+lpOther->G();
        lfReturn[2]=B()+lpOther->B();
        lfReturn[3]=A()+lpOther->A();
        return lfReturn;
    };








    cRGBA cRGBA::operator-(float lpOther)
    {
        cRGBA lfReturn;
        lfReturn[0]=R()-lpOther;
        lfReturn[1]=G()-lpOther;
        lfReturn[2]=B()-lpOther;
        lfReturn[3]=A()-lpOther;
        return lfReturn;
    };
    cRGBA cRGBA::operator-(float *lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()-lpOther[0];
        lfReturn[1]=G()-lpOther[1];
        lfReturn[2]=B()-lpOther[2];
        lfReturn[3]=A()-lpOther[3];
        return lfReturn;
    };
    cRGBA cRGBA::operator-(cRGB lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()-lpOther[0];
        lfReturn[1]=G()-lpOther[1];
        lfReturn[2]=B()-lpOther[2];
        lfReturn[3]=A();
        return lfReturn;
    };
    cRGBA cRGBA::operator-(cRGB *lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()-lpOther->R();
        lfReturn[1]=G()-lpOther->G();
        lfReturn[2]=B()-lpOther->B();
        lfReturn[3]=A();
        return lfReturn;
    };
    cRGBA cRGBA::operator-(cRGBA lpOther)
            {
        cRGBA lfReturn;
        lfReturn[0]=R()-lpOther[0];
        lfReturn[1]=G()-lpOther[1];
        lfReturn[2]=B()-lpOther[2];
        lfReturn[3]=A()-lpOther[3];
        return lfReturn;
    };
    cRGBA cRGBA::operator-(cRGBA *lpOther)
            {
        cRGBA lfReturn;
        lfReturn[0]=R()-lpOther->R();
        lfReturn[1]=G()-lpOther->G();
        lfReturn[2]=B()-lpOther->B();
        lfReturn[3]=A()-lpOther->A();
        return lfReturn;
    };



    cRGBA cRGBA::operator*(float lpOther)
    {
        cRGBA lfReturn;
        lfReturn[0]=R()*lpOther;
        lfReturn[1]=G()*lpOther;
        lfReturn[2]=B()*lpOther;
        lfReturn[3]=A()*lpOther;
        return lfReturn;
    };
    cRGBA cRGBA::operator*(float *lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()*lpOther[0];
        lfReturn[1]=G()*lpOther[1];
        lfReturn[2]=B()*lpOther[2];
        lfReturn[3]=A()*lpOther[3];
        return lfReturn;
    };
    cRGBA cRGBA::operator*(cRGB lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()*lpOther[0];
        lfReturn[1]=G()*lpOther[1];
        lfReturn[2]=B()*lpOther[2];
        lfReturn[3]=A();
        return lfReturn;
    };
    cRGBA cRGBA::operator*(cRGB *lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()*lpOther->R();
        lfReturn[1]=G()*lpOther->G();
        lfReturn[2]=B()*lpOther->B();
        lfReturn[3]=A();
        return lfReturn;
    };
    cRGBA cRGBA::operator*(cRGBA lpOther)
            {
        cRGBA lfReturn;
        lfReturn[0]=R()*lpOther[0];
        lfReturn[1]=G()*lpOther[1];
        lfReturn[2]=B()*lpOther[2];
        lfReturn[3]=A()*lpOther[3];
        return lfReturn;
    };
    cRGBA cRGBA::operator*(cRGBA *lpOther)
            {
        cRGBA lfReturn;
        lfReturn[0]=R()*lpOther->R();
        lfReturn[1]=G()*lpOther->G();
        lfReturn[2]=B()*lpOther->B();
        lfReturn[3]=A()*lpOther->A();
        return lfReturn;
    };

    cRGBA cRGBA::operator/(float lpOther)
    {
        cRGBA lfReturn;
        lfReturn[0]=R()/lpOther;
        lfReturn[1]=G()/lpOther;
        lfReturn[2]=B()/lpOther;
        lfReturn[3]=A()/lpOther;
        return lfReturn;
    };
    cRGBA cRGBA::operator/(float *lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()/lpOther[0];
        lfReturn[1]=G()/lpOther[1];
        lfReturn[2]=B()/lpOther[2];
        lfReturn[3]=A()/lpOther[3];
        return lfReturn;
    };
    cRGBA cRGBA::operator/(cRGB lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()/lpOther[0];
        lfReturn[1]=G()/lpOther[1];
        lfReturn[2]=B()/lpOther[2];
        lfReturn[3]=A();
        return lfReturn;
    };
    cRGBA cRGBA::operator/(cRGB *lpOther)
        {
        cRGBA lfReturn;
        lfReturn[0]=R()/lpOther->R();
        lfReturn[1]=G()/lpOther->G();
        lfReturn[2]=B()/lpOther->B();
        lfReturn[3]=A();
        return lfReturn;
    };
    cRGBA cRGBA::operator/(cRGBA lpOther)
            {
        cRGBA lfReturn;
        lfReturn[0]=R()/lpOther[0];
        lfReturn[1]=G()/lpOther[1];
        lfReturn[2]=B()/lpOther[2];
        lfReturn[3]=A()/lpOther[3];
        return lfReturn;
    };
    cRGBA cRGBA::operator/(cRGBA *lpOther)
            {
        cRGBA lfReturn;
        lfReturn[0]=R()/lpOther->R();
        lfReturn[1]=G()/lpOther->G();
        lfReturn[2]=B()/lpOther->B();
        lfReturn[3]=A()/lpOther->A();
        return lfReturn;
    };









    cRGB cRGB::operator+(float lpOther)
    {
        cRGB lfReturn;
        lfReturn[0]=R()+lpOther;
        lfReturn[1]=G()+lpOther;
        lfReturn[2]=B()+lpOther;
        return lfReturn;
    };
    cRGB cRGB::operator+(float *lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()+lpOther[0];
        lfReturn[1]=G()+lpOther[1];
        lfReturn[2]=B()+lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator+(cRGB lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()+lpOther[0];
        lfReturn[1]=G()+lpOther[1];
        lfReturn[2]=B()+lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator+(cRGB *lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()+lpOther->R();
        lfReturn[1]=G()+lpOther->G();
        lfReturn[2]=B()+lpOther->B();
        return lfReturn;
    };
    cRGB cRGB::operator+(cRGBA lpOther)
            {
        cRGB lfReturn;
        lfReturn[0]=R()+lpOther[0];
        lfReturn[1]=G()+lpOther[1];
        lfReturn[2]=B()+lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator+(cRGBA *lpOther)
            {
        cRGB lfReturn;
        lfReturn[0]=R()+lpOther->R();
        lfReturn[1]=G()+lpOther->G();
        lfReturn[2]=B()+lpOther->B();
        return lfReturn;
    };






    cRGB cRGB::operator-(float lpOther)
    {
        cRGB lfReturn;
        lfReturn[0]=R()-lpOther;
        lfReturn[1]=G()-lpOther;
        lfReturn[2]=B()-lpOther;
        return lfReturn;
    };
    cRGB cRGB::operator-(float *lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()-lpOther[0];
        lfReturn[1]=G()-lpOther[1];
        lfReturn[2]=B()-lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator-(cRGB lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()-lpOther[0];
        lfReturn[1]=G()-lpOther[1];
        lfReturn[2]=B()-lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator-(cRGB *lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()-lpOther->R();
        lfReturn[1]=G()-lpOther->G();
        lfReturn[2]=B()-lpOther->B();
        return lfReturn;
    };
    cRGB cRGB::operator-(cRGBA lpOther)
            {
        cRGB lfReturn;
        lfReturn[0]=R()-lpOther[0];
        lfReturn[1]=G()-lpOther[1];
        lfReturn[2]=B()-lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator-(cRGBA *lpOther)
            {
        cRGB lfReturn;
        lfReturn[0]=R()-lpOther->R();
        lfReturn[1]=G()-lpOther->G();
        lfReturn[2]=B()-lpOther->B();
        return lfReturn;
    };


    cRGB cRGB::operator*(float lpOther)
    {
        cRGB lfReturn;
        lfReturn[0]=R()*lpOther;
        lfReturn[1]=G()*lpOther;
        lfReturn[2]=B()*lpOther;
        return lfReturn;
    };
    cRGB cRGB::operator*(float *lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()*lpOther[0];
        lfReturn[1]=G()*lpOther[1];
        lfReturn[2]=B()*lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator*(cRGB lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()*lpOther[0];
        lfReturn[1]=G()*lpOther[1];
        lfReturn[2]=B()*lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator*(cRGB *lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()*lpOther->R();
        lfReturn[1]=G()*lpOther->G();
        lfReturn[2]=B()*lpOther->B();
        return lfReturn;
    };
    cRGB cRGB::operator*(cRGBA lpOther)
            {
        cRGB lfReturn;
        lfReturn[0]=R()*lpOther[0];
        lfReturn[1]=G()*lpOther[1];
        lfReturn[2]=B()*lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator*(cRGBA *lpOther)
            {
        cRGB lfReturn;
        lfReturn[0]=R()*lpOther->R();
        lfReturn[1]=G()*lpOther->G();
        lfReturn[2]=B()*lpOther->B();
        return lfReturn;
    };



    cRGB cRGB::operator/(float lpOther)
    {
        cRGB lfReturn;
        lfReturn[0]=R()/lpOther;
        lfReturn[1]=G()/lpOther;
        lfReturn[2]=B()/lpOther;
        return lfReturn;
    };
    cRGB cRGB::operator/(float *lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()/lpOther[0];
        lfReturn[1]=G()/lpOther[1];
        lfReturn[2]=B()/lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator/(cRGB lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()/lpOther[0];
        lfReturn[1]=G()/lpOther[1];
        lfReturn[2]=B()/lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator/(cRGB *lpOther)
        {
        cRGB lfReturn;
        lfReturn[0]=R()/lpOther->R();
        lfReturn[1]=G()/lpOther->G();
        lfReturn[2]=B()/lpOther->B();
        return lfReturn;
    };
    cRGB cRGB::operator/(cRGBA lpOther)
            {
        cRGB lfReturn;
        lfReturn[0]=R()/lpOther[0];
        lfReturn[1]=G()/lpOther[1];
        lfReturn[2]=B()/lpOther[2];
        return lfReturn;
    };
    cRGB cRGB::operator/(cRGBA *lpOther)
            {
        cRGB lfReturn;
        lfReturn[0]=R()/lpOther->R();
        lfReturn[1]=G()/lpOther->G();
        lfReturn[2]=B()/lpOther->B();
        return lfReturn;
    };






    cRGB cRGB::operator+=(float lpOther)
    {
        color[0]+=lpOther;
        color[1]+=lpOther;
        color[2]+=lpOther;
        return *this;
    };
    cRGB cRGB::operator+=(float *lpOther)
        {

        color[0]+=lpOther[0];
        color[1]+=lpOther[1];
        color[2]+=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator+=(cRGB lpOther)
        {

        color[0]+=lpOther[0];
        color[1]+=lpOther[1];
        color[2]+=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator+=(cRGB *lpOther)
    {
        color[0]+=lpOther->R();
        color[1]+=lpOther->G();
        color[2]+=lpOther->B();
        return *this;
    };
    cRGB cRGB::operator+=(cRGBA lpOther)
            {

        color[0]+=lpOther[0];
        color[1]+=lpOther[1];
        color[2]+=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator+=(cRGBA *lpOther)
            {

        color[0]+=lpOther->R();
        color[1]+=lpOther->G();
        color[2]+=lpOther->B();
        return *this;
    };



      cRGB cRGB::operator-=(float lpOther)
    {
        color[0]-=lpOther;
        color[1]-=lpOther;
        color[2]-=lpOther;
        return *this;
    };
    cRGB cRGB::operator-=(float *lpOther)
        {

        color[0]-=lpOther[0];
        color[1]-=lpOther[1];
        color[2]-=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator-=(cRGB lpOther)
        {

        color[0]-=lpOther[0];
        color[1]-=lpOther[1];
        color[2]-=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator-=(cRGB *lpOther)
    {
        color[0]-=lpOther->R();
        color[1]-=lpOther->G();
        color[2]-=lpOther->B();
        return *this;
    };
    cRGB cRGB::operator-=(cRGBA lpOther)
            {

        color[0]-=lpOther[0];
        color[1]-=lpOther[1];
        color[2]-=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator-=(cRGBA *lpOther)
            {

        color[0]-=lpOther->R();
        color[1]-=lpOther->G();
        color[2]-=lpOther->B();
        return *this;
    };

      cRGB cRGB::operator*=(float lpOther)
    {
        color[0]*=lpOther;
        color[1]*=lpOther;
        color[2]*=lpOther;
        return *this;
    };
    cRGB cRGB::operator*=(float *lpOther)
        {

        color[0]*=lpOther[0];
        color[1]*=lpOther[1];
        color[2]*=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator*=(cRGB lpOther)
        {

        color[0]*=lpOther[0];
        color[1]*=lpOther[1];
        color[2]*=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator*=(cRGB *lpOther)
    {
        color[0]*=lpOther->R();
        color[1]*=lpOther->G();
        color[2]*=lpOther->B();
        return *this;
    };
    cRGB cRGB::operator*=(cRGBA lpOther)
            {

        color[0]*=lpOther[0];
        color[1]*=lpOther[1];
        color[2]*=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator*=(cRGBA *lpOther)
            {

        color[0]*=lpOther->R();
        color[1]*=lpOther->G();
        color[2]*=lpOther->B();
        return *this;
    };

      cRGB cRGB::operator/=(float lpOther)
    {
        color[0]/=lpOther;
        color[1]/=lpOther;
        color[2]/=lpOther;
        return *this;
    };
    cRGB cRGB::operator/=(float *lpOther)
        {

        color[0]/=lpOther[0];
        color[1]/=lpOther[1];
        color[2]/=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator/=(cRGB lpOther)
        {

        color[0]/=lpOther[0];
        color[1]/=lpOther[1];
        color[2]/=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator/=(cRGB *lpOther)
    {
        color[0]/=lpOther->R();
        color[1]/=lpOther->G();
        color[2]/=lpOther->B();
        return *this;
    };
    cRGB cRGB::operator/=(cRGBA lpOther)
            {

        color[0]/=lpOther[0];
        color[1]/=lpOther[1];
        color[2]/=lpOther[2];
        return *this;
    };
    cRGB cRGB::operator/=(cRGBA *lpOther)
            {

        color[0]/=lpOther->R();
        color[1]/=lpOther->G();
        color[2]/=lpOther->B();
        return *this;
    };


















    cRGBA cRGBA::operator+=(float lpOther)
    {
        color[0]+=lpOther;
        color[1]+=lpOther;
        color[2]+=lpOther;
        color[3]+=lpOther;
        return *this;
    };
    cRGBA cRGBA::operator+=(float *lpOther)
        {

        color[0]+=lpOther[0];
        color[1]+=lpOther[1];
        color[2]+=lpOther[2];
        color[3]+=lpOther[3];
        return *this;
    };
    cRGBA cRGBA::operator+=(cRGB lpOther)
        {

        color[0]+=lpOther[0];
        color[1]+=lpOther[1];
        color[2]+=lpOther[2];
        return *this;
    };
    cRGBA cRGBA::operator+=(cRGB *lpOther)
    {
        color[0]+=lpOther->R();
        color[1]+=lpOther->G();
        color[2]+=lpOther->B();
        return *this;
    };
    cRGBA cRGBA::operator+=(cRGBA lpOther)
            {

        color[0]+=lpOther[0];
        color[1]+=lpOther[1];
        color[2]+=lpOther[2];
        color[3]+=lpOther[3];
        return *this;
    };
    cRGBA cRGBA::operator+=(cRGBA *lpOther)
            {

        color[0]+=lpOther->R();
        color[1]+=lpOther->G();
        color[2]+=lpOther->B();
        color[3]+=lpOther->A();
        return *this;
    };



      cRGBA cRGBA::operator-=(float lpOther)
    {
        color[0]-=lpOther;
        color[1]-=lpOther;
        color[2]-=lpOther;
        color[3]-=lpOther;
        return *this;
    };
    cRGBA cRGBA::operator-=(float *lpOther)
        {

        color[0]-=lpOther[0];
        color[1]-=lpOther[1];
        color[2]-=lpOther[2];
        color[3]-=lpOther[3];
        return *this;
    };
    cRGBA cRGBA::operator-=(cRGB lpOther)
        {

        color[0]-=lpOther[0];
        color[1]-=lpOther[1];
        color[2]-=lpOther[2];
        return *this;
    };
    cRGBA cRGBA::operator-=(cRGB *lpOther)
    {
        color[0]-=lpOther->R();
        color[1]-=lpOther->G();
        color[2]-=lpOther->B();
        return *this;
    };
    cRGBA cRGBA::operator-=(cRGBA lpOther)
            {

        color[0]-=lpOther[0];
        color[1]-=lpOther[1];
        color[2]-=lpOther[2];
        color[3]-=lpOther[3];
        return *this;
    };
    cRGBA cRGBA::operator-=(cRGBA *lpOther)
            {

        color[0]-=lpOther->R();
        color[1]-=lpOther->G();
        color[2]-=lpOther->B();
        color[3]-=lpOther->A();
        return *this;
    };

      cRGBA cRGBA::operator*=(float lpOther)
    {
        color[0]*=lpOther;
        color[1]*=lpOther;
        color[2]*=lpOther;
        color[3]*=lpOther;
        return *this;
    };
    cRGBA cRGBA::operator*=(float *lpOther)
        {

        color[0]*=lpOther[0];
        color[1]*=lpOther[1];
        color[2]*=lpOther[2];
        color[3]*=lpOther[3];
        return *this;
    };
    cRGBA cRGBA::operator*=(cRGB lpOther)
        {

        color[0]*=lpOther[0];
        color[1]*=lpOther[1];
        color[2]*=lpOther[2];
        return *this;
    };
    cRGBA cRGBA::operator*=(cRGB *lpOther)
    {
        color[0]*=lpOther->R();
        color[1]*=lpOther->G();
        color[2]*=lpOther->B();
        return *this;
    };
    cRGBA cRGBA::operator*=(cRGBA lpOther)
            {

        color[0]*=lpOther[0];
        color[1]*=lpOther[1];
        color[2]*=lpOther[2];
        color[3]*=lpOther[3];
        return *this;
    };
    cRGBA cRGBA::operator*=(cRGBA *lpOther)
            {

        color[0]*=lpOther->R();
        color[1]*=lpOther->G();
        color[2]*=lpOther->B();
        color[3]*=lpOther->A();
        return *this;
    };

      cRGBA cRGBA::operator/=(float lpOther)
    {
        color[0]/=lpOther;
        color[1]/=lpOther;
        color[2]/=lpOther;
        color[3]/=lpOther;
        return *this;
    };
    cRGBA cRGBA::operator/=(float *lpOther)
        {

        color[0]/=lpOther[0];
        color[1]/=lpOther[1];
        color[2]/=lpOther[2];
        color[3]/=lpOther[3];
        return *this;
    };
    cRGBA cRGBA::operator/=(cRGB lpOther)
        {

        color[0]/=lpOther[0];
        color[1]/=lpOther[1];
        color[2]/=lpOther[2];
        return *this;
    };
    cRGBA cRGBA::operator/=(cRGB *lpOther)
    {
        color[0]/=lpOther->R();
        color[1]/=lpOther->G();
        color[2]/=lpOther->B();
        return *this;
    };
    cRGBA cRGBA::operator/=(cRGBA lpOther)
            {

        color[0]/=lpOther[0];
        color[1]/=lpOther[1];
        color[2]/=lpOther[2];
        color[3]/=lpOther[3];
        return *this;
    };
    cRGBA cRGBA::operator/=(cRGBA *lpOther)
            {

        color[0]/=lpOther->R();
        color[1]/=lpOther->G();
        color[2]/=lpOther->B();
        color[3]/=lpOther->A();
        return *this;
    };

bool cRGBA::operator==(float *lpOther)
{
    return (!memcmp(lpOther,this,sizeof(cRGBA)));
};
bool cRGBA::operator==(cRGBA lpOther)
{
    return (!memcmp(&lpOther,this,sizeof(cRGBA)));
};
bool cRGBA::operator==(cRGBA *lpOther)
{
    return (!memcmp(lpOther,this,sizeof(cRGBA)));
};

bool cRGB::operator==(float *lpOther)
{
    return (!memcmp(lpOther,this,sizeof(cRGB)));
};
bool cRGB::operator==(cRGB lpOther)
{
    return (!memcmp(&lpOther,this,sizeof(cRGB)));
};
bool cRGB::operator==(cRGB *lpOther)
{
    return (!memcmp(lpOther,this,sizeof(cRGB)));
};
