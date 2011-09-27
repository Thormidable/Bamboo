#ifndef __WTMATRIXTEMPLATE_H__
#define __WTMATRIXTEMPLATE_H__

class cMatrix
{
 int miRows,miColumns;
 float *mpData;
public:

 cMatrix(int liRow,int liColumn);

 void operator=(cMatrix &lVal);
 void operator=(float &lVal);
 void operator=(const float lVal);

 cMatrix operator+(cMatrix &lVal);
 cMatrix operator+(float &lVal);
 cMatrix operator+(const float lVal);

 cMatrix operator-(cMatrix &lVal);
 cMatrix operator-(float &lVal);
 cMatrix operator-(const float lVal);
 
 cMatrix operator*(cMatrix &lVal);
 cMatrix operator*(float &lVal);
 cMatrix operator*(const float lVal);

 cMatrix operator/(cMatrix &lVal);
 cMatrix operator/(float &lVal);
 cMatrix operator/(const float lVal);
 
 bool Equivalent(cMatrix &lVal){return (lVal.miRows==miRows && lVal.miColumns==miColumns);};
 
 cMatrix Determinant();
 cMatrix Transpose();

};

cMatrix cMatrix::Transpose()
{
 cMatrix *lpTemp=new cMatrix(miColumns,miRows);
 int liRow,liColumn;
 
 for (liRow=0;liRow<miRows;++liRow)
 {
  for (liColumn=0;liColumn<miColumns;++liColumn)
  {
   lpTemp->mpData[liRow*miColumns+miColumn]=mpData[miRows*liColumn+miRow];
  }
 }
  return lpTemp;
}

cMatrix cMatrix::Determinant(cMatrix lMatrix)
{

};

void cMatrix::operator=(cMatrix &lVal)
{
 if (Equivalent(lVal))
 {
  int liLoop;
  for (liLoop=0;liLoop<miRows*miColumns;++liLoop;)
  {mpData[liLoop]=lVal.mpData[liLoop];}
 }

}

void cMatrix::operator=(float &lVal)
{
 int liLoop;
 for(liLoop=0;liLoop<miRows*miColumns;++liLoop)
 {
  mpData[liLoop]=lVal;
 }
}

void cMatrix::operator=(const float lVal)
{
 int liLoop;
 for(liLoop=0;liLoop<miRows*miColumns;++liLoop)
 {
  mpData[liLoop]=lVal;
 }
}

cMatrix cMatrix::operator+(cMatrix &lVal)
{
 if (Equivalent(lVal))
 {
  int liLoop;
   cMatrix *mpTemp=new cMatrix(miRows,miColumns);
  for(liLoop=0;liLoop<miRows*miColumns;++liLoop)
  {
   mpTemp->mpData[liLoop]=mpData[liLoop]+lVal.mpData[liLoop];
  }
  return *mpTemp;
 }
 return 0;
}

cMatrix cMatrix::operator+(float &lVal)
{
 int liLoop;
 cMatrix *mpTemp=new cMatrix(miRows,miColumns);
 for (liLoop=0;liLoop<miRows*miColumns;++liLoop)
 {
  mpTemp->mpData[liLoop]=mpData[liLoop]+lVal;
 }
 return *mpTemp;
}

cMatrix cMatrix::operator+(const float lVal)
{
 int liLoop;
 cMatrix *mpTemp=new cMatrix(miRows,miColumns);
 for (liLoop=0;liLoop<miRows*miColumns;++liLoop)
 {
  mpTemp->mpData[liLoop]=mpData[liLoop]+lVal;
 }
 return *mpTemp;
}

cMatrix cMatrix::operator-(cMatrix &lVal)
{
 if (Equivalent(lVal))
 {
  int liLoop;
   cMatrix *mpTemp=new cMatrix(miRows,miColumns);
  for(liLoop=0;liLoop<miRows*miColumns;++liLoop)
  {
   mpTemp->mpData[liLoop]=mpData[liLoop]-lVal.mpData[liLoop];
  }
  return *mpTemp;
 }
 return 0;
}

cMatrix cMatrix::operator-(float &lVal)
{
 int liLoop;
 cMatrix *mpTemp=new cMatrix(miRows,miColumns);
 for (liLoop=0;liLoop<miRows*miColumns;++liLoop)
 {
  mpTemp->mpData[liLoop]=mpData[liLoop]-lVal;
 }
 return *mpTemp;
}

cMatrix cMatrix::operator-(const float lVal)
{
 int liLoop;
 cMatrix *mpTemp=new cMatrix(miRows,miColumns);
 for (liLoop=0;liLoop<miRows*miColumns;++liLoop)
 {
  mpTemp->mpData[liLoop]=mpData[liLoop]-lVal;
 }
 return *mpTemp;
}


cMatrix operator*(cMatrix &lVal)
{
if (miColumns==lVal.miRows)
{
 double ldTemp;
 int liCount,liStep,liStep2,liLittleStep,liElement;
 cMatrix *lpTemp=new cMatrix(miRows,lVal.miColumns)

 for(liCount=0;liCount<miRows*miColumns;++liCount) {lpTemp->mpData[liCount]=0;}
 
 liStep=0;
 liLittleStep=0;
for(liElement=0;liElement<miColumns;++liElement)
{
 for(liStep2=0;liStep2<miRows*miColumns;++miCount)
 {
  for(liCount=0;liCount<miRows;++liCount)
  {
   lpTemp->mpData[liElement*miRows+liStep]+=mpData[liStep]*lVal.mpData[liLittleStep];
   
   ++liStep;
   if (liStep==miRows*miColumns) liStep=0;
  }
  ++liLittleStep;
 }
}

 return lpTemp;
}
return 0;
}

cMatrix operator*(float &lVal)
{
 int liLoop;
 cMatrix *mpTemp=new cMatrix(miRows,miColumns);
 for (liLoop=0;liLoop<miRows*miColumns;++liLoop)
 {
  mpTemp->mpData[liLoop]=mpData[liLoop]*lVal;
 }
 return *mpTemp;
}

cMatrix operator*(const float lVal)
{
 int liLoop;
 cMatrix *mpTemp=new cMatrix(miRows,miColumns);
 for (liLoop=0;liLoop<miRows*miColumns;++liLoop)
 {
  mpTemp->mpData[liLoop]=mpData[liLoop]*lVal;
 }
 return *mpTemp;
}




cMatrix operator/(cMatrix &lVal)
{
if (miColumns==lVal.miRows)
{
 double ldTemp;
 int liCount,liStep,liStep2,liLittleStep,liElement;
 cMatrix *lpTemp=new cMatrix(miRows,lVal.miColumns)

 for(liCount=0;liCount<miRows*miColumns;++liCount) {lpTemp->mpData[liCount]=0;}

 liStep=0;
 liLittleStep=0;
for(liElement=0;liElement<miColumns;++liElement)
{
 for(liStep2=0;liStep2<miRows*miColumns;++miCount)
 {
  for(liCount=0;liCount<miRows;++liCount)
  {
   lpTemp->mpData[liElement*miRows+liStep]+=mpData[liStep]/lVal.mpData[liLittleStep];

   ++liStep;
   if (liStep==miRows*miColumns) liStep=0;
  }
  ++liLittleStep;
 }
}

 return lpTemp;
}
return 0;
}

cMatrix operator/(float &lVal)
{
 int liLoop;
 cMatrix *mpTemp=new cMatrix(miRows,miColumns);
 for (liLoop=0;liLoop<miRows*miColumns;++liLoop)
 {
  mpTemp->mpData[liLoop]=mpData[liLoop]/lVal;
 }
 return *mpTemp;
}

cMatrix operator/(const float lVal)
{
 int liLoop;
 cMatrix *mpTemp=new cMatrix(miRows,miColumns);
 for (liLoop=0;liLoop<miRows*miColumns;++liLoop)
 {
  mpTemp->mpData[liLoop]=mpData[liLoop]/lVal;
 }
 return *mpTemp;
}




cMatrix::cMatrix(int liRows,int liColumns)
{
 miRows=liRows;
 miColumns=liColumns;
 mpData=new float[miRows*miColumn];
}




#endif
