
#include "../../WTBamboo.h"


cLineArrayData::cLineArrayData()
{
    glGenBuffers(1,&miBufferID);
	lbBuffer=false;
}

cLineArrayData::~cLineArrayData()
{
    if(miBufferID) {glDeleteBuffers(1, &miBufferID);miBufferID=0;}
}


void cLineArrayData::RenderLines()
{
  if(lbBuffer) Buffer();
  else glBindBuffer(GL_ARRAY_BUFFER, miBufferID);

 //glDisableClientState(GL_NORMAL_ARRAY);

  glVertexPointer(3,GL_FLOAT,0,0);

  glDrawArrays(GL_LINE_STRIP,0,Items());

 // glEnableClientState(GL_NORMAL_ARRAY);

}

void cLineArrayData::Add(c3DVf lfPoint)
{
    lbBuffer=true;
    cLimitedList<c3DVf>::Add(&lfPoint);
}

void cLineArrayData::Add(float *lfPoint)
{
    lbBuffer=true;
	c3DVf lfTemp(lfPoint);
    cLimitedList<c3DVf>::Add(&lfTemp);
}

void cLineArrayData::Buffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, miBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(c3DVf)*Items(), mpList, GL_STATIC_DRAW);

	lbBuffer=false;
}

void cLineArrayData::Equals(cLineArrayData *lpOther)
{
    cLimitedList<c3DVf>::operator=(lpOther);
    lbBuffer=true;
};

void cLineArrayData::operator=(cLineArrayData *lpOther)
{
    cLimitedList<c3DVf>::operator=(lpOther);
    lbBuffer=true;
};

void cLineArrayData::operator=(cLineArrayData &lpOther)
{
    lbBuffer=true;
    cLimitedList<c3DVf>::operator=(lpOther);
};

cLineArrayData::cLineArrayData(cLineArrayData *lpOther)
{
    glGenBuffers(1,&miBufferID);
    cLimitedList<c3DVf>::operator=(lpOther);
    lbBuffer=true;
};

