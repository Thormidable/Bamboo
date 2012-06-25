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
	TRACE("Deleting FileName: " << mpFileName);
}


char *cFile::FileName()
{
	return mpFileName;
}

void cFile::Load(){}

void cFile::FileName(string lsFileName)
{
    strcpy(mpFileName,lsFileName.c_str());
};

void cFile::Stop()
{
	mpFileHandler->Delete(mpNode);

};
