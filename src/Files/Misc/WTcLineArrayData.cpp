#include "../../WTBamboo.h"
//#include <cmath>

cLineArrayData::cLineArrayData()
{
    glGenBuffers(1,&miBufferID);
}

cLineArrayData::~cLineArrayData()
{
    if(miBufferID) {glDeleteBuffers(1, &miBufferID);miBufferID=0;}
}


void cLineArrayData::RenderLines()
{
  if(lbBuffer) Buffer();
  else glBindBuffer(GL_ARRAY_BUFFER, miBufferID);

  glVertexPointer(3,GL_FLOAT,0,0);

  glDrawArrays(GL_LINE_STRIP,0,Items());
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
