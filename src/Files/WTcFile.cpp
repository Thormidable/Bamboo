#include "../WTBamboo.h"
#include <fstream>
#include <cstdio>


using namespace std;

cFile::cFile()
{
	memset(mpFileName,0,64*sizeof(uint8));
	mpFileName[0]=0;

	mpFileHandler=cFileHandler::Instance();
	mpNode=mpFileHandler->Add(this);

}

cFile::~cFile()
{
	printf("FileName %s\n",mpFileName);
}

void cFile::Delete()
{
	mpFileHandler->Delete(mpNode);
}

char *cFile::FileName()
{
	return mpFileName;
}

void cFile::Load(){}

