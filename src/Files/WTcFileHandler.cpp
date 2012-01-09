#include "../WTBamboo.h"

cFileHandler::cFileHandler()
{
	mpFiles=0;
	mpCursor=0;
}



cFileHandler::~cFileHandler()
{
	trace("Deleting mpFiles");
	delete mpFiles; mpFiles=0;
	trace("Deleting mpFiles");
}

cFileHandler *cFileHandler::mpInstance=0;

cFileHandler *cFileHandler::Instance()
{
	if(!mpInstance) {mpInstance=new cFileHandler; mpInstance->mpFiles=0;}
	return mpInstance;
}

void cFileHandler::Reload(){}

void cFileHandler::Unload(){}

cLinkedNode<vFile> *cFileHandler::Add(vFile *lpNew)
{
	if (!mpFiles) {
		mpFiles=new cLinkedList<vFile>(lpNew);
		return mpFiles->Start();
	}
	return mpFiles->Insert(lpNew);
}

void cFileHandler::Delete(cLinkedNode<vFile> *lpNode)
{
	if(mpFiles) mpFiles->Delete(lpNode);
}
